// AlaskaConformalProjection.h: interface for the AlaskaConformalProjection 
// class.
//
// Developed by: Mike Childs
//      Started: 4/15/98
//////////////////////////////////////////////////////////////////////

#ifndef _ALASKACONFORMALPROJECTION_H_
#define _ALASKACONFORMALPROJECTION_H_

#include "TransverseMercatorProjection.h"

class AlaskaConformalProjection : public TransverseMercatorProjection  
{
public:
  AlaskaConformalProjection( double sMajor, double sMinor, 
                             double fe, double fn, 
                             DATUM d, UNIT u,
                             DATUM geoDatum = DEFAULT_DATUM,
                             UNIT geoUnit = ARC_DEGREES );
  AlaskaConformalProjection( const AlaskaConformalProjection& p );

  // Accessors
  PROJSYS getProjectionSystem() const;

  // Projection functions
  bool projectToGeo( double x, double y, 
                     double& latitude, double& longitude ) const;
  bool projectFromGeo( double latitude, double longitude,
                       double& x, double& y ) const;

  // toString override
  virtual string toString() const;

  // Cloning
  virtual Projection* clone() const;
};

inline PROJSYS
AlaskaConformalProjection::getProjectionSystem() const
{
  return ALASKA;
}

#endif
