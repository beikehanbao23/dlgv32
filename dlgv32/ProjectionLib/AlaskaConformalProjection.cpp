// AlaskaConformalProjection.cpp: implementation of the 
// AlaskaConformalProjection class.
//
// Developed by: Mike Childs
//      Started: 4/5/98
//////////////////////////////////////////////////////////////////////

#include "AlaskaConformalProjection.h"
#include "DatumConvertor.h"

// GCTPC includes
#include "gctpc/gctpc.h"
#include "gctpc/gctp.h"
#include "gctpc/for_init.h"
#include "gctpc/inv_init.h"
#include "gctpc/proj.h"
#include "gctpc/untfz.h"

#ifndef NULL
#define NULL 0
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AlaskaConformalProjection::AlaskaConformalProjection( double sMajor,
                                                      double sMinor, 
                                                      double fe, double fn, 
                                                      DATUM d, UNIT u, 
                                                      DATUM geoDatum,
                                                      UNIT geoUnit )
: TransverseMercatorProjection(0.0,sMajor,sMinor,0.0,0.0,fe,fn,d,u,geoDatum,
                               geoUnit)
{
}

AlaskaConformalProjection::AlaskaConformalProjection( const AlaskaConformalProjection& p )
: TransverseMercatorProjection(p)
{
}

// toString override
string
AlaskaConformalProjection::toString() const
{
  string str = "Alaska Conformal Projection\r\n";
  str += Projection::toString();

  char strFalseEasting[40];
  sprintf( strFalseEasting, "\r\nFALSE EASTING: %g", getFalseEasting() );
  str += strFalseEasting;

  char strFalseNorthing[40];
  sprintf( strFalseNorthing, "\r\nFALSE NORTHING: %g", getFalseNorthing() );
  str += strFalseNorthing;

  char strSemiMajorAxis[40];
  sprintf( strSemiMajorAxis, "\r\nSEMI-MAJOR AXIS: %g", getSemiMajorAxis() );
  str += strSemiMajorAxis;

  char strSemiMinorAxis[40];
  sprintf( strSemiMinorAxis, "\r\nSEMI-MINOR AXIS: %g", getSemiMinorAxis() );
  str += strSemiMinorAxis;

  return str;
}

// Projection functions
bool 
AlaskaConformalProjection::projectToGeo( double x, double y, 
                                         double& latitude, double& longitude ) const
{
	long iflg;		// error flag
    
  // Initialize the inverse transformation
  InverseTransFunc inv_trans[MAXPROJ + 1];
  inv_init( getProjectionSystem(), 0, const_cast<double*>(d_projParams), 
            DatumConvertor::getDatumEllipsoid( getDatum() ), 
            NULL, NULL, &iflg, inv_trans );

  // Convert the x and y to meters
  double factor;
  untfz( getUnit(), METERS, &factor );
  x *= factor;
  y *= factor;    
    
  // do the inverse transformation
  alconinv( x, y, &longitude, &latitude );

  // Convert the input coordinates from radians to the correct units
  untfz( RADIANS, getGeoUnit(), &factor );
  longitude *= factor;
  latitude *= factor;

  // Convert the datums
  return convertDatum( latitude, longitude, getDatum(), getGeoDatum() );
}

bool
AlaskaConformalProjection::projectFromGeo( double latitude, double longitude,
                                           double& x, double& y ) const
{ 
  // Convert the datums
  if ( !convertDatum( latitude, longitude, getGeoDatum(), getDatum() ) )
  {
    return false;
  }

  long   iflg;
    
  // Initialize the UTM forward transformation
  ForwardTransFunc for_trans[MAXPROJ + 1];
  for_init( getProjectionSystem(), 0, const_cast<double*>(d_projParams), 
            DatumConvertor::getDatumEllipsoid( getDatum() ), 
            NULL, NULL, &iflg, for_trans );

  // Convert the input coordinates to radians
  double factor;
  untfz( getGeoUnit(), RADIANS, &factor );
  longitude *= factor;
  latitude *= factor;

  // do the forward transformation
  alconfor( longitude, latitude, &x, &y );

  // Convert the x and y from meters to the correct units
  untfz( METERS, getUnit(), &factor );
  x *= factor;
  y *= factor;

  return true;
}

// Cloning
Projection*
AlaskaConformalProjection::clone() const
{
    return ( new AlaskaConformalProjection( *this ) );
}
