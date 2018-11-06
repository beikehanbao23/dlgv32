// USGSDEMLayer.cpp - implementation of USGSDEMLayer class
//
// Developed by: Mike Childs
//      Started: 4/18/98

#include "USGSDEMLayer.h"
#include "LoadingDialog.h"
#include <fstream>
#include <stdlib.h>
using namespace std;

// Construction
USGSDEMLayer::USGSDEMLayer( int layerID, const char* strFilename, HINSTANCE hInst )
: RasterPluginLayer( layerID, strFilename, hInst ), d_spatialResZ(1.0)
{
}

// Destruction
USGSDEMLayer::~USGSDEMLayer()
{
}

// Loading
bool
USGSDEMLayer::load()
{
  // Create an input stream based on the filename
  ifstream dem;
  dem.open( getFilename().c_str(), ios::binary );

  // Abort if the DEM couldn't be successfully opened
  if ( !dem )
  {
    return false;
  }

  try
  {
    // Create and initialize a dialog to display load progress
	  LoadingDialog loadingDialog;
    loadingDialog.create( getInstance() );
	  string strTitle = "Loading ";
    char strFilename[_MAX_FNAME];
    _splitpath( getFilename().c_str(), NULL, NULL, strFilename, NULL );
	  strTitle += strFilename;
    strTitle += "...";
	  long size = d_grid.read( dem, true );
    long spacing = size / 100;
	  loadingDialog.setRange( 0, 100 );
	  loadingDialog.setPos( 0 );
	  loadingDialog.show( strTitle.c_str() );

    // Read in the DEM
    long curPos = size;
    while ( 0 < ( curPos = d_grid.read( dem, true ) ) )
    {
      if ( 0 == ( curPos % spacing ) )
      {
        loadingDialog.incrementPos();
      }
    }
  }
  catch ( ... )
  {
    dem.close();
    return false;
  }

  // Get the Z spatial res
  d_spatialResZ = d_grid.getHeader().getSpatialResZ();

  // Close the DEM file
  dem.close();

  return true;
}

UNIT
USGSDEMLayer::getVerticalUnits() const
{
  // Get the DEM header
  const DEMHeader& hdr = d_grid.getHeader();

  // Set the vertical units
  switch ( hdr.getElevationUnits() )
  {
    case 1:
      return US_FEET;
    case 2:
      return METERS;
  }

  return RasterPluginLayer::getVerticalUnits();
}

void
USGSDEMLayer::getProjection( PROJSYS& projSys, DATUM& datum, UNIT& unit, int& zone, double* pParams ) const
{
  // Get the DEM header
  const DEMHeader& hdr = d_grid.getHeader();

  // Get the horizontal datum
  datum = UNKNOWN_DATUM;
  switch ( hdr.getHorizDatum() )
  {
    case 1:
      datum = NAD27;
      break;
    case 2:
      datum = WGS_72;
      break;
    case 3:
      datum = WGS_84;
      break;            
    case 4:
      datum = NAD83;
      break;
    case 5:
      datum = OLD_HAWAIIAN_MEAN;
      break;
    case 6:
      datum = PUERTO_RICO;
      break;
  }

  // Get the units
  unit = UNKNOWN_UNIT;
  switch ( hdr.getGroundRefSysUnits() )
  {
    case 0:
      unit = RADIANS;
      break;
    case 1:
      unit = US_FEET;
      break;
    case 2:
      unit = METERS;
      break;
    case 3:
      unit = ARC_SECONDS;
      break;
  }

  // Get the projection system
  projSys = UNKNOWN_PROJSYS;
  switch ( hdr.getGroundRefSysCode() )
  {
    case 0:
      projSys = GEO;
      break;
    case 1:
      projSys = UTM;
      zone = hdr.getGroundRefSysZone();
      break;
    case 2:
      projSys = SPCS;
      zone = hdr.getGroundRefSysZone();
      break;
  }
}

void 
USGSDEMLayer::getBoundingRect( double& left, double& bottom, double& right, double& top ) const
{
  // Get the corners
  const DEMPointVector& corners = d_grid.getHeader().getDEMCorners();

  // Get the bounds of the DEM
  for ( int i = 0; i < corners.size(); i++ )
  {
    if ( 0 == i )
    {
      left = right = corners[i].getX();
      top = bottom = corners[i].getY();
    }
    else
    {
      left = min( left, corners[i].getX() );
      right = max( right, corners[i].getX() );
      top = max( top, corners[i].getY() );
      bottom = min( bottom, corners[i].getY() );
    }
  }
}

bool
USGSDEMLayer::getElevation( long row, long col, float& elev ) const
{
  row = min( row, getImageHeight() - 1 );
  row = max( row, 0 );
  col = min( col, getImageWidth() - 1 );
  col = max( col, 0 );

  short tmpElev = d_grid.getElevation( col, row );
  if ( tmpElev == d_grid.getMissingDataValue() )
  {
    return false;
  }

  elev = tmpElev * d_spatialResZ;
  return true;
}

const char*
USGSDEMLayer::getDescription() const
{
  return d_grid.getHeader().getQuadName().c_str();
}