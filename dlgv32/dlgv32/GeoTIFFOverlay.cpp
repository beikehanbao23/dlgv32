// GeoTIFFOverlay.cpp - implementation for GeoTIFFOverlay class
//
// Developed by: Mike Childs
//      Started: 2/10/97
//


#include <iostream>
#include "GeoTIFFOverlay.h"
#include "libgeotiff/libxtiff/xtiffio.h"
#include "CoordinateTransforms.h"
#include "TIFFPropertySheet.h"
#include "GeoTIFFProjectionMapper.h"

// Projection includes
#include "ProjectionLib/GeographicProjection.h"
#include "ProjectionLib/UTMProjection.h"

using namespace std;

GeoTIFFOverlay::GeoTIFFOverlay( CString& filename )
: TIFFOverlay(filename), d_modelTiePoint(0), d_pixelScale(0), 
  d_citationGeoKey(NULL), d_PCScitationGeoKey(NULL), d_modelTiePointCount(0),
  d_pixelScaleCount(0), d_notGeoTIFF( FALSE ), d_verticalCSTypeGeoKey(0), 
  d_verticalUnitsGeoKey(0), d_verticalCitationGeoKey(NULL)
{
}

GeoTIFFOverlay::~GeoTIFFOverlay()
{
	// Free memory used by citations
	if ( NULL != d_citationGeoKey )
	{
		_TIFFfree( d_citationGeoKey );
	}

	if ( NULL != d_PCScitationGeoKey )
	{
		_TIFFfree( d_PCScitationGeoKey );
	}

  if ( NULL != d_verticalCitationGeoKey )
  {
     _TIFFfree( d_verticalCitationGeoKey );
  }

	// NOTE: the memory used by the model tie point and the pixel scale
	// is not freed because that memory is allocated by the TIFF library 
	// itself and freed by it.  Therefore this is NOT a memory leak.
}

BOOL GeoTIFFOverlay::load()
{
	GTIF *gtif = (GTIF*)0;

	// Load the TIFF stuff
	if ( !TIFFOverlay::load() )
	{
		// Abort the load
		return FALSE;
	}

	// Open GeoTIFF key parser
	gtif = GTIFNew( tif );

	// Abort the load if the GeoTIFF key parser couldn't be opened
	if ( !gtif )
	{
     d_notGeoTIFF = TRUE;
     return FALSE;
  }

	// Get the GeoTIFF directory info
	GTIFDirectoryInfo( gtif, d_version, 0 );

	// Abort the load if the GeoTIFF version if too new.  Currently, a
	// major revision number greater than one is too new.  This should
	// be changed when a new version of libgeotiff is used.
	if ( d_version[1] > 1 )
	{
    d_notGeoTIFF = TRUE;
		return FALSE;
	}

	// Get model type geokey.  Abort the load if there isn't one
	if ( !GTIFKeyGet( gtif, GTModelTypeGeoKey, &d_modelTypeGeoKey, 0, 1 ) )
	{
    AfxMessageBox( "No model type" );
    d_notGeoTIFF = TRUE;
		return FALSE;
	}

	// Get raster type (pixel is area or pixel is point )
	GTIFKeyGet( gtif, GTRasterTypeGeoKey, &d_rasterTypeGeoKey, 0, 1 );

  // Get the vertical CS Type and vertical units
  GTIFKeyGet( gtif, VerticalCSTypeGeoKey, &d_verticalCSTypeGeoKey, 0, 1 );
  GTIFKeyGet( gtif, VerticalUnitsGeoKey, &d_verticalUnitsGeoKey, 0, 1 );

  // Get the vertical citation
  int size;
	tagtype_t type;
	int cit_length = GTIFKeyInfo( gtif, VerticalCitationGeoKey, &size, &type );
	if ( cit_length > 0 )
	{
		d_verticalCitationGeoKey = (char*)_TIFFmalloc( cit_length * sizeof(char) );
		GTIFKeyGet( gtif, VerticalCitationGeoKey, d_verticalCitationGeoKey, 0, 
                cit_length );
	}

  // Get the PCS citation if there is one
	cit_length = GTIFKeyInfo( gtif, PCSCitationGeoKey, &size, &type );
	if ( cit_length > 0 )
	{
		d_PCScitationGeoKey = (char*)_TIFFmalloc( cit_length * sizeof(char) );
		GTIFKeyGet( gtif, PCSCitationGeoKey, d_PCScitationGeoKey, 0, cit_length );
	}

  // Get the model tiepoints
  if ( !readModelTiePoints( tif ) )
  {
    AfxMessageBox( "Error reading model tie points" );
    d_notGeoTIFF = TRUE;
  	return FALSE;
  }

  // Get the pixel scale
  if ( !readPixelScale( tif ) )
  {
     AfxMessageBox( "Error reading pixel scale" );
     d_notGeoTIFF = TRUE;
     return FALSE;
  }

  // Calculate the vertical pixel scale if this is a vertical GeoTIFF
  if ( isVertical() )
  {        
    // Set the vertical units
    switch ( d_verticalUnitsGeoKey )
    {
      case Linear_Meter:
        setVerticalUnits( METERS, d_pixelScale[2] );
        break;
      case Linear_Foot:
      case Linear_Foot_US_Survey:
      case Linear_Foot_Modified_American:
      case Linear_Foot_Clarke:
      case Linear_Foot_Indian:
        setVerticalUnits( US_FEET, d_pixelScale[2] );
        break;
    }

    readMinMaxSampleValues( tif );

    // Recalculate the global min/max values
    recalculateMinMaxSampleValue();
  }

  // If a native projection was set by the TIFFOverlay load, delete it
  if ( NULL != d_pProjection )
  {
    delete d_pProjection;
  }

  // Get the native projection
  d_pProjection = GeoTIFFProjectionMapper::getProjection( gtif );

  // Abort the load if a projection wasn't retrieved
  if ( NULL == d_pProjection )
  {
    AfxMessageBox( "Unable to setup projection, aborting load..." );
    d_notGeoTIFF = TRUE;
    return FALSE;
  }

  // Set the global projection if one hasn't yet been set
  if ( NULL == CoordinateTransforms::getProjection() )
  {
    CoordinateTransforms::setProjection( d_pProjection );
  }

	// Close GeoTIFF key parser
	GTIFFree( gtif );

	// Set loaded flag
	d_loaded = TRUE;

	// Calculate bounding rectangle
	calculateBoundingRect();

  // Setup the global projection changed stuff
  handleProjectionChanged();

  // Update all the overlayss texture mapped layers lists if necessary
  if ( isVertical() )
  {
    updateAllTextureMappedLayers();
  }

	return TRUE;
}

bool GeoTIFFOverlay::readModelTiePoints( TIFF* pTIFF )
{
	// Get model tie point.  Abort the load if there isn't one
	return ( TIFFGetField( pTIFF, TIFFTAG_GEOTIEPOINTS, &d_modelTiePointCount,
                         &d_modelTiePoint ) );
}

bool GeoTIFFOverlay::readPixelScale( TIFF* pTIFF )
{
	// Get pixel scale information.  Abort the load if there isn't any
	if ( !TIFFGetField( pTIFF, TIFFTAG_GEOPIXELSCALE, &d_pixelScaleCount, 
                      &d_pixelScale ) )
  {
    return false;
  }

  // Make sure the z field is one if necessary
  if ( 0.0 == d_pixelScale[2] )
  {
    d_pixelScale[2] = 1.0;
  }

  return true;
}

void GeoTIFFOverlay::showPropertiesDialog()
{
  // Create the dialog if necessary
  if ( NULL == d_pPropertySheet )
  {
    d_pPropertySheet = new TIFFPropertySheet( "GeoTIFF Metadata", this, this );
    d_pPropertySheet->Create( AfxGetMainWnd() );
  }

  // Show the dialog
  d_pPropertySheet->ShowWindow( SW_SHOWNORMAL );
}

void GeoTIFFOverlay::calculateBoundingRect()
{
	// Check to make sure that enough info exists
	if ( d_modelTiePointCount > 0 && d_pixelScaleCount > 0 )
	{
    double rasterLeft = d_modelTiePoint[0];
    double rasterTop  = d_modelTiePoint[1];

    // Adjust raster top and left if this is a PixelIsPoint TIFF
    if ( RasterPixelIsPoint == d_rasterTypeGeoKey )
    {
      rasterLeft += 0.5;
      rasterTop  += 0.5;
    }

		double modelLeft   = d_modelTiePoint[3] - rasterLeft * d_pixelScale[0];
    double modelTop    = d_modelTiePoint[4] + rasterTop  * d_pixelScale[1];
    double modelRight  = modelLeft + d_imageWidth * d_pixelScale[0];
    double modelBottom = modelTop - d_imageLength * d_pixelScale[1];

		d_boundingRect.setPoints( modelLeft, modelBottom, modelRight, modelTop );
	}
	else // Just calculate rectangle based on TIFF data only
	{
		TIFFOverlay::calculateBoundingRect();
	}
}

CString GeoTIFFOverlay::modelTypeToString() const
{
  // Conver the model type to a string
  switch ( d_modelTypeGeoKey )
  {
  case 0:
	  return "Undefined Model";
  case 1:
	  return "Projection Coordinate System";
	case 2:
    return "Geographic lat-long system";
	case 3:
	  return "Geocentric (X,Y,Z) system";
	case 32767:
    return "User-defined system";
	default:
    return "Unknown model";
  }
}

bool GeoTIFFOverlay::isVertical() const
{
  return ( 0 != d_verticalCSTypeGeoKey && 0 != d_verticalUnitsGeoKey );
}

CString GeoTIFFOverlay::getVerticalUnitString() const
{
  switch ( d_verticalUnitsGeoKey )
  {
  case Linear_Meter:
    return "meters";
  case Linear_Foot:
    return "feet";
  case Linear_Foot_US_Survey:
    return "US Survey feet"; 
  case Linear_Foot_Modified_American:
    return "modified American feet";
  case Linear_Foot_Clarke:
    return "Clarke feet";
  case Linear_Foot_Indian:
    return "Indian feet";
  case Linear_Link:
    return "links";
  case Linear_Link_Benoit:
    return "Benoit links";
  case Linear_Link_Sears:
    return "Sears links";
  case Linear_Chain_Benoit:
    return "Benoit chains";
  case Linear_Chain_Sears:
    return "Sears chains";
  case Linear_Yard_Sears:
    return "Sears yards";
  case Linear_Yard_Indian:
    return "Indian yards";
  case Linear_Fathom:
    return "fathoms";
  case Linear_Mile_International_Nautical:
    return "International Nautical miles";
  default:
    return "";
  }
}


