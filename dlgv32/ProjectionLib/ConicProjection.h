// ConicProjection.h: interface for the ConicProjection class.
//
// Developed by: Mike Childs
//      Started: 1/24/98
//////////////////////////////////////////////////////////////////////

#ifndef _CONICPROJECTION_H_
#define _CONICPROJECTION_H_

#include "Projection.h"

class ConicProjection : public Projection  
{
public:
	ConicProjection( double sMajor, double sMinor, double centMer, 
                   double originLat,
                   double fe, double fn, DATUM d, UNIT u,
                   DATUM geoDatum = DEFAULT_DATUM, 
                   UNIT geoUnit = ARC_DEGREES );
  ConicProjection( const ConicProjection& p );

  // Accessors
  double getSemiMajorAxis() const;
  double getSemiMinorAxis() const;
  double getCentralMeridian() const;
  double getOriginLatitude() const;
  double getFalseEasting() const;
  double getFalseNorthing() const;

  // Modifiers

  virtual void setSemiMajorAxis( double sMajor );
    /* Sets the semi-major axis of the ellipsoid.  If zero, Clarke 1866 in meters
       is assumed. */

  virtual void setSemiMinorAxis( double sMinor );
    /* ( sMinor < 0 ) -> eccentricity squared of the ellipsoid,
       ( sMinor = 0 ) -> spherical form is assumed
       ( sMinor > 0 ) -> semi-minor axis of the ellipsoid. */

  virtual void setCentralMeridian( double centMer );
    /* Sets the longitude of the central meridian 
       The angle should be entered in packed degrees/minutes/seconds
       format (DDDMMMSSS.SS) */

  virtual void setOriginLatitude( double originLat );
    /* Sets the latitude of the projection origin 
       The angle should be entered in packed degrees/minutes/seconds
       format (DDDMMMSSS.SS) */

  virtual void setFalseEasting( double fe );
    /* Sets the false easting in the same units as the semi-major axis */

  virtual void setFalseNorthing( double fn );
    /* Sets the false northing in the same units as the semi-major axis */

  // Projection functions
  bool projectToGeo( double x, double y, 
                     double& latitude, double& longitude ) const;
  bool projectFromGeo( double latitude, double longitude,
                       double& x, double& y ) const;

  // Operator overloads
  bool operator==( const Projection& p ) const;

  // toString override
  virtual string toString() const;

protected:
  // Data members
  double d_projParams[15];
};

inline double 
ConicProjection::getSemiMajorAxis() const
{
 return d_projParams[0];
}

inline double 
ConicProjection::getSemiMinorAxis() const
{
  return d_projParams[1];
}

inline double 
ConicProjection::getCentralMeridian() const
{
  return d_projParams[4];
}

inline double 
ConicProjection::getOriginLatitude() const
{
  return d_projParams[5];
}
    
inline double 
ConicProjection::getFalseEasting() const
{
  return d_projParams[6];
}
    
inline double 
ConicProjection::getFalseNorthing() const
{
  return d_projParams[7];
}

inline void 
ConicProjection::setSemiMajorAxis( double sMajor )
{
  d_projParams[0] = sMajor;
}
    
inline void 
ConicProjection::setSemiMinorAxis( double sMinor )
{
  d_projParams[1] = sMinor;
}
    
inline void 
ConicProjection::setCentralMeridian( double centMer )
{
  d_projParams[4] = centMer;
}
 
inline void 
ConicProjection::setOriginLatitude( double originLat )
{
  d_projParams[5] = originLat;
}

inline void 
ConicProjection::setFalseEasting( double fe )
{
  d_projParams[6] = fe;
}

inline void 
ConicProjection::setFalseNorthing( double fn )
{
  d_projParams[7] = fn;
}

#endif
