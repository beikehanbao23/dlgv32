// CoordinateTransforms.cpp - implementation for CoordinateTransforms class
//
// Developed by: Mike Childs
//      Started: 12/3/96
//

#include "StdAfx.h"
#include "CoordinateTransforms.h"
#include "GraphicsLib/CoordinateMapping.h"

#include <math.h>
#include <limits.h>

// Constants
#define PI                 3.14159265
#define EARTH_RADIUS_MAJOR 6367000
#define EARTH_RADIUS_MINOR 6346000

// Initialization of static data members
CoordinateMapping* CoordinateTransforms::d_currentMapping = 0;
Projection* CoordinateTransforms::d_pProjection = NULL;
PROJ_CHANGED_FUNC* CoordinateTransforms::d_pProjChangedFunc = NULL;
LPVOID CoordinateTransforms::d_pProjChangedFuncArg = NULL;

void CoordinateTransforms::setProjection( Projection* pProjection )
{
  Projection* pOldProjection = d_pProjection;
  if ( NULL == pProjection )
  {
    d_pProjection = NULL;
  }
  else
  {
    d_pProjection = pProjection->clone();
  }

  // Call the projection changed callback function
  if ( NULL != d_pProjChangedFunc )
  {
    d_pProjChangedFunc( d_pProjChangedFuncArg, pOldProjection );
  }

  // Reclaim the memory used by the old projection
  delete pOldProjection;
}

void CoordinateTransforms::GndRefSystoLatLong( double  x, double  y,
                                               double& lat, double& longitude)
{
  if ( NULL != d_pProjection )
  {
    // Make sure decimal degrees are returned
    UNIT oldGeoUnits = d_pProjection->getGeoUnit();
    d_pProjection->setGeoUnit( ARC_DEGREES );
    d_pProjection->projectToGeo( x, y, lat, longitude );
    d_pProjection->setGeoUnit( oldGeoUnits );
  }
}

CString CoordinateTransforms::LatLongToString( double lat, double longitude )
{
  if ( lat > 90.0 || lat < -90.0 || longitude < -180.0 || longitude > 180.0 )
  {
    return "Coordinate out of range";
  }

	return ( LatToString( lat ) + ", " + LongitudeToString( longitude ) );
}

CString CoordinateTransforms::LatToString( double lat )
{
	char NSFlag = 'N';
	int degrees, minutes;
	double seconds;

	if ( lat < 0.0 )
	{
		NSFlag = 'S';
		lat = fabs( lat );
	}

	// Convert latitude to DMS
	seconds = lat * 3600;
	degrees = static_cast<int>( floor( seconds / 3600 ) );
	seconds -= degrees * 3600;
	minutes = static_cast<int>( floor( seconds / 60 ) );
	seconds -= minutes * 60;
	
	// Add the latitude to the string
	CString strLat;
	strLat.Format("%d° %02d\' %05.2f\" %c", degrees, minutes, seconds, NSFlag);
	
	return strLat;
}

CString CoordinateTransforms::LongitudeToString( double longitude )
{
	char EWFlag = 'E';
	CString strLongitude;
	int degrees, minutes;
	double seconds;

	if ( longitude < 0.0 )
	{
		EWFlag = 'W';
		longitude = fabs( longitude );
	}

	// Convert longitude to DMS
	seconds = longitude * 3600;
	degrees = static_cast<int>( floor( seconds / 3600 ) );
	seconds -= degrees * 3600;
	minutes = static_cast<int>( floor( seconds / 60 ) );
	seconds -= minutes * 60;
	
	// Add the longitude to the string
	strLongitude.Format("%d° %02d\' %05.2f\" %c", degrees, minutes, seconds,
                      EWFlag );
	
	return strLongitude;
}

CString CoordinateTransforms::GndRefSystoLatLong( double x, double y )
{
	double lat, longitude;
	GndRefSystoLatLong( x, y, lat, longitude );

	return LatLongToString( lat, longitude );
}

CRect CoordinateTransforms::GndRefSystoLP( const Rectangle2D& rect )
{
	double min_x, min_y, max_x, max_y;

	rect.getPoints( min_x, min_y, max_x, max_y );

	// Convert the points in the rectangle from GndRefSys to logical coordinates
	GndRefSystoLP( min_x, max_y );
	GndRefSystoLP( max_x, min_y );

	// Return a normalized version of the rectangle
	// (i.e. (lower_left, upper_right) form )
	CRect tmpRect((int)min_x, (int)( ceil( min_y ) ), (int)( ceil( max_x ) ), (int)( max_y ) );
	tmpRect.NormalizeRect();
	return tmpRect;
}

void CoordinateTransforms::GndRefSystoLP(double& x, double& y)
{
	d_currentMapping->mapToViewport( x, y );

	// The following checks are required to avoid extraneous lines in Windows 95.
	// The problem apparently doesn't occur in Windows NT because
	// it's graphics system is 32-bit and Windows 95 system is 
	// 16-bit. The extra 150 that I added on is to make sure that
	// when objects such as nodes are drawn the size of the object doesn't make
	// the logical coordinate exceed the limits for the short type
	if ( x > ( SHRT_MAX - 150 ) )
	{
		x = SHRT_MAX - 150;
	}
	else if ( x < ( SHRT_MIN + 150 ) )
	{
		x = SHRT_MIN + 150;
	}
	
	if ( y > ( SHRT_MAX - 150 ) )
	{
		y = SHRT_MAX - 150;
	}
	else if ( y < ( SHRT_MIN + 150 ) )
	{
		y = SHRT_MIN + 150;
	}
}

double CoordinateTransforms::LPtoGndRefSys( double scalar )
{
	d_currentMapping->mapToWindow( scalar );
	return scalar;
}

void CoordinateTransforms::LPtoGndRefSys( double& x, double& y)
{
	d_currentMapping->mapToWindow( x, y );
}

Rectangle2D CoordinateTransforms::LPtoGndRefSys( const CRect& rect )
{
	double x1, y1, x2, y2;
	CPoint topLeft, bottomRight;

	topLeft = rect.TopLeft();
	bottomRight = rect.BottomRight();

	x1 = topLeft.x;
	y1 = bottomRight.y;
	x2 = bottomRight.x;
	y2 = topLeft.y;

	LPtoGndRefSys( x1, y1 );
	LPtoGndRefSys( x2, y2 );

	return Rectangle2D( x1, y1, x2, y2 );
}

CString CoordinateTransforms::projectionToString( PROJSYS proj )
{
	switch ( proj )
	{
		case GEO:
			return "GEO";
		case UTM:
			return "UTM";
		case SPCS:
			return "SPCS";
		case ALBERS:
			return "ALB";
		case LAMCC:
			return "LAMCC";
		case MERCAT:
			return "MERCAT";
		case PS:
			return "PS";
		case POLYC:
			return "POLYC";
		case EQUIDC:
			return "EQUIDC";
		case TM:
			return "TM";
		case STEREO:
      return "STEREO";
    case LAMAZ:
			return "LAMAZ";
		case AZMEQD:
			return "AZMEQD";
		case GNOMON:
			return "GNOMON";
		case ORTHO:
			return "ORTHO";
		case GVNSP:
			return "GVNSP";
		case SNSOID:
			return "SNSOID";
		case EQRECT:
			return "EQRECT";
		case MILLER:
			return "MILLER";
		case VGRINT:
			return "VGRINT";
		case HOM:
			return "HOM";
		case ROBIN:
			return "ROBIN";
		case SOM:
			return "SOM";
		case ALASKA:
			return "ALASKA";
		case GOOD:
			return "GOOD";
		case MOLL:
			return "MOLL";
		case IMOLL:
			return "IMOLL";
		case HAMMER:
			return "HAMMER";
		case WAGIV:
			return "WAGVII";
		case OBLEQA:
			return "OBLEQA";
		case USER_DEFINED:
			return "USER";
		default:
			return "???";
	}
}

double 
CoordinateTransforms::calculateGreatCircleDistance( double lat1, double lon1, 
                                                    double lat2, double lon2 )
{
  // Convert all values to radians
  lon1 *= PI / 180;
  lat1 *= PI / 180;
  lon2 *= PI / 180;
  lat2 *= PI / 180;

  // Calculate the distance
  double s1 = sin( ( lat2 - lat1 ) / 2 );
  double s2 = sin( ( lon2 - lon1 ) / 2 );
  double a = s1 * s1 + cos( lat1 ) * cos( lat2 ) * s2 * s2;
  double c = 2 * asin( min( 1, sqrt( a ) ) );

  // Calculate the radius of the earth at this latitude
  double R = EARTH_RADIUS_MAJOR - ( EARTH_RADIUS_MAJOR - EARTH_RADIUS_MINOR ) * s1;

  // XXX Make the earth radius vary with latitude
  return ( R * c );
}

bool CoordinateTransforms::projectToGlobal(double& x, double& y,
                                           const Projection& proj )
{
  ASSERT( NULL != d_pProjection );

  // Make sure the geo datums and units are consistent
  DATUM oldDatum = d_pProjection->getGeoDatum();
  d_pProjection->setGeoDatum( proj.getGeoDatum() );
  d_pProjection->setGeoUnit( proj.getGeoUnit() );

  // Project the point
  bool bSuccess = projectPoint( x, y, proj, *d_pProjection );

  // Reset the global projection's geo datum
  d_pProjection->setGeoDatum( oldDatum );

  return bSuccess;
}

bool CoordinateTransforms::projectFromGlobal(double& x, double& y,
                                             const Projection& proj )
{
  ASSERT( NULL != d_pProjection );

  // Make sure the geo datums and units are consistent
  DATUM oldDatum = d_pProjection->getGeoDatum();
  d_pProjection->setGeoDatum( proj.getGeoDatum() );
  d_pProjection->setGeoUnit( proj.getGeoUnit() );

  // Project the point
  bool bSuccess = projectPoint( x, y, *d_pProjection, proj );

  // Reset the global projection's geo datum
  d_pProjection->setGeoDatum( oldDatum );

  return bSuccess;
}

void CoordinateTransforms::projectRectangleToGlobal(Rectangle2D& rect, 
                                                    const Projection& proj )
{
  if ( NULL == d_pProjection )
  {
    return;
  }

  // Make sure the geo datums and units are consistent
  DATUM oldDatum = d_pProjection->getGeoDatum();
  d_pProjection->setGeoDatum( proj.getGeoDatum() );
  d_pProjection->setGeoUnit( proj.getGeoUnit() );

  // Project the rectangle
  projectRectangle( rect, proj, *d_pProjection );

  // Reset the global projection's geo datum
  d_pProjection->setGeoDatum( oldDatum );
}

void CoordinateTransforms::projectRectangleFromGlobal(Rectangle2D& rect,
                                                      const Projection& proj )
{
  if ( NULL == d_pProjection )
  {
    return;
  }

  // Make sure the geo datums and units are consistent
  DATUM oldDatum = d_pProjection->getGeoDatum();
  d_pProjection->setGeoDatum( proj.getGeoDatum() );
  d_pProjection->setGeoUnit( proj.getGeoUnit() );

  // Project the rectangle
  projectRectangle( rect, *d_pProjection, proj );

  // Reset the global projection's geo datum
  d_pProjection->setGeoDatum( oldDatum );
}

bool CoordinateTransforms::projectPoint(double& x, double& y,
                                        const Projection& from,
                                        const Projection& to )
{
  // Project the point
  if ( from.projectToGeo( x, y, y, x ) )
  {
    if ( to.projectFromGeo( y, x, x, y ) )
    {
      return true;
    }
  }

  return false;
}

void CoordinateTransforms::projectRectangle(Rectangle2D& rect, 
                                            const Projection& from,
                                            const Projection& to )
{
  static const UINT HPOINTS = 15;
  static const UINT VPOINTS = 15;
  UINT i;
  double x, y;
  double left, right, bottom, top;

  if ( from == to )
  {
    return;
  }

  // Get the pre-projected bounds
  double nLeft, nBottom, nRight, nTop;
  rect.getPoints( nLeft, nBottom, nRight, nTop );

  // Find the max of the top projected
  double hSpacing = rect.width() / ( HPOINTS - 1 );
  for ( i = 0; i < HPOINTS; i++ )
  {
    x = nLeft + i * hSpacing;
    y = nTop;

    // Project the point
    projectPoint( x, y, from, to );

    if ( 0 == i )
    {
      top = y;
    }
    else
    {
      top = max( y, top );
    }
  }

  // Find the min of the bottom projected
  for ( i = 0; i < HPOINTS; i++ )
  {
    x = nLeft + i * hSpacing;
    y = nBottom;

    // Project the point
    projectPoint( x, y, from, to );

    if ( 0 == i )
    {
      bottom = y;
    }
    else
    {
      bottom = min( y, bottom );
    }
  }

  // Find the min of the left projected
  double vSpacing = rect.height() / ( VPOINTS - 1 );
  for ( i = 0; i < VPOINTS; i++ )
  {
    x = nLeft;
    y = nTop - vSpacing * i;

    // Project the point
    projectPoint( x, y, from, to );

    if ( 0 == i )
    {
      left = x;
    }
    else
    {
      left  = min( x, left );
    }
  }

  // Find the max of the right projected
  for ( i = 0; i < VPOINTS; i++ )
  {
    x = nRight;
    y = nTop - vSpacing * i;

    // Project the point
    projectPoint( x, y, from, to );

    if ( 0 == i )
    {
      right = x;
    }
    else
    {
      right = max( right, x );
    }
  }

  rect.setPoints( left, bottom, right, top );

  // Inflate the rectangle by 1% to handle pokies between grid points
  rect.inflateRect( rect.width() / 100.0, rect.height() / 100.0 );
}
