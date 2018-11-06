// RasterPluginOverlay.cpp - implementation of RasterPluginOverlay class
//
// Developed by: Mike Childs
//      Started: 4/10/98

#include "RasterPluginOverlay.h"
#include "CoordinateTransforms.h"

// Projection includes
#include "ProjectionLib/AlaskaConformalProjection.h"
#include "ProjectionLib/AlbersConicProjection.h"
#include "ProjectionLib/AzimuthalEquidistantProjection.h"
#include "ProjectionLib/EquidistantConicProjection.h"
#include "ProjectionLib/EquirectangularProjection.h"
#include "ProjectionLib/GeographicProjection.h"
#include "ProjectionLib/GnomonicProjection.h"
#include "ProjectionLib/HotineObliqueMercatorProjection.h"
#include "ProjectionLib/LambertAzimuthalProjection.h"
#include "ProjectionLib/LambertConformalConicProjection.h"
#include "ProjectionLib/MercatorProjection.h"
#include "ProjectionLib/MillerCylindricalProjection.h"
#include "ProjectionLib/OrthographicProjection.h"
#include "ProjectionLib/PolarStereographicProjection.h"
#include "ProjectionLib/PolyconicProjection.h"
#include "ProjectionLib/PseudocylindricalProjection.h"
#include "ProjectionLib/RobinsonProjection.h"
#include "ProjectionLib/SinusoidalProjection.h"
#include "ProjectionLib/StatePlaneProjection.h"
#include "ProjectionLib/StereographicProjection.h"
#include "ProjectionLib/TransverseMercatorProjection.h"
#include "ProjectionLib/UTMProjection.h"
#include "ProjectionLib/VanDerGrintenProjection.h"

// Static member init
int RasterPluginOverlay::d_overlayIDCounter = 0;

// Construction
RasterPluginOverlay::RasterPluginOverlay( CString& strFilename, const CString& strDLLName )
: RasterOverlay(strFilename),
  d_strDLLName(strDLLName),
  d_pPlugin(NULL),
  d_destroyOverlayFunc(NULL),
  d_getBadElevationColorFunc(NULL),
  d_getBoundingRectFunc(NULL),
  d_getDescriptionFunc(NULL),
  d_getElevationFunc(NULL),
  d_getImageHeightFunc(NULL),
  d_getImageWidthFunc(NULL),
  d_getMinMaxSampleValueFunc(NULL),
  d_getProjectionFunc(NULL),
  d_getRowColColorFunc(NULL),
  d_getVerticalPixelScaleFunc(NULL),
  d_isVerticalFunc(NULL),
  d_loadOverlayFunc(NULL),
  d_showBadElevationsFunc(NULL),
  d_showOptionsDialogFunc(NULL),
  d_showPropertiesDialogFunc(NULL),
  d_bIsVertical(false),
  d_imageWidth(0),
  d_imageHeight(0)
{
    // Set this overlay's ID
    d_overlayID = d_overlayIDCounter;

    // Increment the overlay ID counter
    d_overlayIDCounter++;
}

// Destruction
RasterPluginOverlay::~RasterPluginOverlay()
{
    // Destroy the overlay
    if ( NULL != d_destroyOverlayFunc )
    {
        (*d_destroyOverlayFunc)( d_overlayID );
    }

    // Free the DLL
    if ( NULL != d_pPlugin )
    {
        ::FreeLibrary( d_pPlugin );
    }
}

// Loading
BOOL
RasterPluginOverlay::load()
{
    // Get a handle to the DLL
    d_pPlugin = ::LoadLibrary( d_strDLLName );
    if ( NULL == d_pPlugin )
    {
        AfxMessageBox( "Unable to open DLL" );
        return FALSE;
    }

    // Get handles to the functions
    d_destroyOverlayFunc = (DESTROY_OVERLAY_FUNC)::GetProcAddress( d_pPlugin, "destroyOverlay" );
    d_getBadElevationColorFunc = (GET_BAD_ELEVATION_COLOR_FUNC)::GetProcAddress( d_pPlugin, "getBadElevationColor" );
    d_getBoundingRectFunc = (GET_BOUNDING_RECT_FUNC)::GetProcAddress( d_pPlugin, "getBoundingRect" );
    d_getDescriptionFunc = (GET_DESCRIPTION_FUNC)::GetProcAddress( d_pPlugin, "getDescription" );
    d_getElevationFunc = (GET_ELEVATION_FUNC)::GetProcAddress( d_pPlugin, "getElevation" );
    d_getImageHeightFunc = (GET_IMAGE_HEIGHT_FUNC)::GetProcAddress( d_pPlugin, "getImageHeight" );
    d_getImageWidthFunc = (GET_IMAGE_WIDTH_FUNC)::GetProcAddress( d_pPlugin, "getImageWidth" );
    d_getMinMaxSampleValueFunc = (GET_MIN_MAX_SAMPLE_VALUE_FUNC)::GetProcAddress( d_pPlugin, "getMinMaxSampleValue" );
    d_getProjectionFunc = (GET_PROJECTION_FUNC)::GetProcAddress( d_pPlugin, "getProjection" );
    d_getRowColColorFunc = (GET_ROW_COL_COLOR_FUNC)::GetProcAddress( d_pPlugin, "getRowColColor" );
    d_getVerticalPixelScaleFunc = (GET_VERTICAL_PIXEL_SCALE_FUNC)::GetProcAddress( d_pPlugin, "getVerticalPixelScale" );
    d_getVerticalUnitsFunc = (GET_VERTICAL_UNITS_FUNC)::GetProcAddress( d_pPlugin, "getVerticalUnits" );
    d_isVerticalFunc = (IS_VERTICAL_FUNC)::GetProcAddress( d_pPlugin, "isVertical" );
    d_loadOverlayFunc = (LOAD_OVERLAY_FUNC)::GetProcAddress( d_pPlugin, "loadOverlay" );
    d_showBadElevationsFunc = (SHOW_BAD_ELEVATIONS_FUNC)::GetProcAddress( d_pPlugin, "showBadElevations" );
    d_showOptionsDialogFunc = (SHOW_OPTIONS_DIALOG_FUNC)::GetProcAddress( d_pPlugin, "showOptionsDialog" );
    d_showPropertiesDialogFunc = (SHOW_PROPERTIES_DIALOG_FUNC)::GetProcAddress( d_pPlugin, "showPropertiesDialog" );

    // Make sure the essential functions have been overriden
    if ( NULL == d_destroyOverlayFunc )
    {
        AfxMessageBox( "Plugin Error: destroyOverlay not found" );
        return FALSE;
    }

    if ( NULL == d_getBoundingRectFunc )
    {
        AfxMessageBox( "Plugin Error: getBoundingRect not found" );
        return FALSE;
    }

    if ( NULL == d_getImageHeightFunc )
    {
        AfxMessageBox( "Plugin Error: getImageHeight not found" );
        return FALSE;
    }

    if ( NULL == d_getImageWidthFunc )
    {
        AfxMessageBox( "Plugin Error: getImageWidth not found" );
        return FALSE;
    }

    if ( NULL == d_getProjectionFunc )
    {
        AfxMessageBox( "Plugin Error: getProjection not found" );
        return FALSE;
    }

    if ( NULL == d_loadOverlayFunc )
    {
        AfxMessageBox( "Plugin Error: loadOverlay not found" );
        return FALSE;
    }

    if ( isVertical() )
    {
        if ( NULL == d_getElevationFunc )
        {
            AfxMessageBox( "Plugin Error: getElevation not found" );
            return FALSE;
        }

        if ( NULL == d_getMinMaxSampleValueFunc )
        {
            AfxMessageBox( "Plugin Error: getMinMaxSampleValue not found" );
            return FALSE;
        }
    }
    else
    {
        if ( NULL == d_getRowColColorFunc )
        {
            AfxMessageBox( "Plugin Error: getRowColColor not found" );
            return FALSE;
        }
    }

    // Load the overlay
    if ( !(*d_loadOverlayFunc)( d_overlayID, getFilename() ) )
    {
        AfxMessageBox( "Error loading overlay" );
        return FALSE;
    }

    // Get the image height and width
    d_imageHeight = (*d_getImageHeightFunc)( d_overlayID );
    d_imageWidth = (*d_getImageWidthFunc)( d_overlayID );

    // Determine whether or not the layer is vertical
    if ( NULL != d_isVerticalFunc )
    {
        d_bIsVertical = (*d_isVerticalFunc)( d_overlayID );
    }

    // Set the vertical units
    UNIT u = METERS;
    if ( NULL != d_getVerticalUnitsFunc )
    {
        u = (*d_getVerticalUnitsFunc)( d_overlayID );
    }
    setVerticalUnits( u );

    // Calculate the bounding rectangle
    calculateBoundingRect();

    // Get the native projeciton
    if ( !setupProjection() )
    {
        AfxMessageBox( "Error setting up projection." );
        return FALSE;
    }

    // Setup the global projection changed stuff
    handleProjectionChanged();

    // Recalculate the global min/max values
    recalculateMinMaxSampleValue();

    d_loaded = TRUE;
    return TRUE;
}

COLORREF
RasterPluginOverlay::getBadElevationColor() const
{
    if ( NULL != d_getBadElevationColorFunc )
    {
        unsigned char r, g, b;
        (*d_getBadElevationColorFunc)( d_overlayID, &r, &g, &b );
        return RGB( r, g, b );
    }

    return RasterOverlay::getBadElevationColor();
}

CString
RasterPluginOverlay::getDescription() const
{
    if ( NULL != d_getDescriptionFunc )
    {
        CString strDescPrefix;
        strDescPrefix.Format( "<%s> ", getFilenameWithoutPath() );
        const char* strDesc = (*d_getDescriptionFunc)( d_overlayID );
        if ( NULL != strDesc )
        {
            strDescPrefix += strDesc;
        }

        return strDescPrefix;
    }

    return RasterOverlay::getDescription();
}

bool
RasterPluginOverlay::showBadElevations() const
{
    if ( NULL != d_showBadElevationsFunc )
    {
        return ( (*d_showBadElevationsFunc)( d_overlayID ) );
    }

    return RasterOverlay::showBadElevations();
}

BOOL
RasterPluginOverlay::showOptionsDialog( CDlgv32Doc* pDoc )
{
    // TODO: Add this to options dialog 
    return RasterOverlay::showOptionsDialog( pDoc );
}

void
RasterPluginOverlay::showPropertiesDialog()
{
    if ( NULL != d_showPropertiesDialogFunc )
    {
        (*d_showPropertiesDialogFunc)( d_overlayID );
    }
    else
    {
        RasterOverlay::showPropertiesDialog();
    }
}

void
RasterPluginOverlay::calculateBoundingRect()
{
    // Get the bounding rect from the plugin
    ASSERT( NULL != d_getBoundingRectFunc );
    double left, right, bottom, top;
    (*d_getBoundingRectFunc)( d_overlayID, &left, &bottom, &right, &top );
    d_boundingRect.setPoints( left, bottom, right, top );
}

bool
RasterPluginOverlay::getElevation( long row, long col, float& elev ) const
{
    ASSERT( isVertical() );
    ASSERT( NULL != d_getElevationFunc );
    return ( (*d_getElevationFunc)( d_overlayID, row, col, &elev ) );
}

COLORREF
RasterPluginOverlay::getRowColColor( long row, long col )
{
    ASSERT( !isVertical() );
    ASSERT( NULL != d_getRowColColorFunc );
    unsigned char r, g, b;
    if ( (*d_getRowColColorFunc)( d_overlayID, row, col, &r, &g, &b ) )
    {
        return ( RGB(r,g,b) );
    }
    else
    {
        return getBgColor();
    }
}

void
RasterPluginOverlay::getMinMaxSampleValue( float& min, float& max ) const
{
    ASSERT( isVertical() );
    ASSERT( NULL != d_getMinMaxSampleValueFunc );
    (*d_getMinMaxSampleValueFunc)( d_overlayID, &min, &max );
}

float
RasterPluginOverlay::getVerticalPixelScale() const
{
    ASSERT( isVertical() );
    if ( NULL != d_getVerticalPixelScaleFunc )
    {
        return ( (*d_getVerticalPixelScaleFunc)( d_overlayID ) );
    }
    else
    {
        return RasterOverlay::getVerticalPixelScale();
    }
}

bool
RasterPluginOverlay::setupProjection()
{
    ASSERT( NULL != d_getProjectionFunc );
    PROJSYS projSys;
    DATUM   datum;
    UNIT    unit;
    int     zone = 0;
    double  params[15];

    // Initialize all the params to zero
    for ( int i = 0; i < 15; i++ )
    {
        params[i] = 0.0;
    }

    // Get the projection info from the plugin
    (*d_getProjectionFunc)( d_overlayID, &projSys, &datum, &unit, &zone, params );

    // Create a projection based on the info retrieved from the plugin
    switch ( projSys )
    {
        case GEO:
            d_pProjection = new GeographicProjection( datum, unit );
            break;
        case UTM:
            if ( 0 == zone )
            {
                d_pProjection = new UTMProjection( params[1], params[0], datum, unit );
            }
            else
            {
                d_pProjection = new UTMProjection( zone, datum, unit );
            }
            break;
        case SPCS:
            d_pProjection = new StatePlaneProjection( zone, datum, unit );
            break;
        case ALBERS:
            d_pProjection = new AlbersConicProjection( params[2], params[3],
                                                       params[0], params[1],
                                                       params[4], params[5],
                                                       params[6], params[7],
                                                       datum, unit );
            break;
        case LAMCC:
            d_pProjection = new LambertConformalConicProjection( params[2], params[3],
                                                                 params[0], params[1],
                                                                 params[4], params[5],
                                                                 params[6], params[7],
                                                                 datum, unit );
            break;
        case MERCAT:
            d_pProjection = new MercatorProjection( params[0], params[1],
                                                    params[4], params[5], 
                                                    params[6], params[7],
                                                    datum, unit );
            break;
        case PS:
            d_pProjection = new PolarStereographicProjection( params[4], params[5],
                                                              params[0], params[1],
                                                              params[6], params[7],
                                                              datum, unit );
            break;
        case POLYC:
            d_pProjection = new PolyconicProjection( params[0], params[1],
                                                     params[4], params[5],
                                                     params[6], params[7],
                                                     datum, unit );
            break;
        case EQUIDC:
            if ( 0 == params[8] )
            {
                d_pProjection = new EquidistantConicProjection( params[2], params[0],
                                                                params[1], params[4],
                                                                params[5], params[6],
                                                                params[7], datum, unit );
            }
            else
            {
                d_pProjection = new EquidistantConicProjection( params[2], params[3],
                                                                params[0], params[1],
                                                                params[4], params[5],
                                                                params[6], params[7],
                                                                datum, unit );
            }

            break;
        case TM:
            d_pProjection = new TransverseMercatorProjection( params[2], params[0],
                                                              params[1], params[4],
                                                              params[5], params[6],
                                                              params[7], datum, unit );
            break;
        case STEREO:
            d_pProjection = new StereographicProjection( params[4], params[5],
                                                         params[6], params[7],
                                                         params[0], datum, unit );
            break;
        case LAMAZ:
            d_pProjection = new LambertAzimuthalProjection( params[4], params[5],
                                                            params[6], params[7],
                                                            params[0], datum, unit );
            break;
        case AZMEQD:
            d_pProjection = new AzimuthalEquidistantProjection( params[4], params[5],
                                                                params[6], params[7],
                                                                params[0], datum, unit );
            break;
        case GNOMON:
            d_pProjection = new GnomonicProjection( params[4], params[5],
                                                    params[6], params[7],
                                                    params[0], datum, unit );
            break;
        case ORTHO:
            d_pProjection = new OrthographicProjection( params[4], params[5],
                                                        params[6], params[7],
                                                        params[0], datum, unit );
            break;
        case GVNSP:
            // TODO
            break;
        case SNSOID:
            d_pProjection = new SinusoidalProjection( params[0], params[4],
                                                      params[6], params[7],
                                                      datum, unit );
            break;
        case EQRECT:
            d_pProjection = new EquirectangularProjection( params[5], params[0],
                                                           params[4], params[6],
                                                           params[7], datum, unit );
            break;
        case MILLER:
            d_pProjection = new MillerCylindricalProjection( params[0], params[4],
                                                             params[6], params[7],
                                                             datum, unit );
            break;
        case VGRINT:
            d_pProjection = new VanDerGrintenProjection( params[5], params[0],
                                                         params[4], params[6],
                                                         params[7], datum, unit );
            break;
        case HOM:
            if ( 0 == params[12] )
            {
                d_pProjection = new HotineObliqueMercatorProjection( params[2], params[8],
                                                                     params[9], params[10],
                                                                     params[11], params[0],
                                                                     params[1], params[5],
                                                                     params[6], params[7],
                                                                     datum, unit );
            }
            else
            {
                d_pProjection = new HotineObliqueMercatorProjection( params[2], params[3],
                                                                     params[0], params[1],
                                                                     params[4], params[5],
                                                                     params[6], params[7],
                                                                     datum, unit );
            }

            break;
        case ROBIN:
            d_pProjection = new RobinsonProjection( params[0], params[4],
                                                    params[6], params[7],
                                                    datum, unit );
            break;
        case SOM:
            // TODO
            break;
        case ALASKA:
            d_pProjection = new AlaskaConformalProjection( params[0], params[1], 
                                                           params[6], params[7],
                                                           datum, unit );
            break;
        case GOOD:
            // TODO
            break;
        case MOLL:
            // TODO
            break;
        case IMOLL:
            // TODO
            break;
        case HAMMER:
            // TODO
            break;
        case WAGIV:
            // TODO
            break;
        case WAGVII:
            // TODO
            break;
        case OBLEQA:
            // TODO
            break;
        default:
            return false;
    }

    // Abort if the projection couldn't be created
    if ( NULL == d_pProjection )
    {
        return false;
    }

    // Setup the global projection if one hasn't been setup yet
    if ( NULL == CoordinateTransforms::getProjection() )
    {
        CoordinateTransforms::setProjection( d_pProjection );
    }

    return true;
}