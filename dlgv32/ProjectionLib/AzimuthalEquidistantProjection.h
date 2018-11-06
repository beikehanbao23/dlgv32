// AzimuthalEquidistantProjection.h: interface for the 
// AzimuthalEquidistantProjection class.
//
// Developer by: Mike Childs
//      Started: 4/3/98
//////////////////////////////////////////////////////////////////////

#ifndef _AZIMUTHALEQUIDISTANTPROJECTION_H_
#define _AZIMUTHALEQUIDISTANTPROJECTION_H_

#include "AzimuthalProjection.h"

class AzimuthalEquidistantProjection : public AzimuthalProjection  
{
public:
	AzimuthalEquidistantProjection( double centralLongitude, 
                                  double centralLatitude,
                                  double falseEasting, double falseNorthing,
                                  double sphereRadius, DATUM d, UNIT u,
                                  DATUM geoDatum = DEFAULT_DATUM,
                                  UNIT geoUnit = ARC_DEGREES );
  AzimuthalEquidistantProjection( const AzimuthalEquidistantProjection& p );

  // Accessors
  PROJSYS getProjectionSystem() const;

  // Cloning
  Projection* clone() const;

  // String override
  string toString() const;
};

inline PROJSYS
AzimuthalEquidistantProjection::getProjectionSystem() const
{
  return AZMEQD;
}

inline string
AzimuthalEquidistantProjection::toString() const
{
  string str = "Azimuthal Equidistant Projection\r\n";
  str += AzimuthalProjection::toString();
  return str;
}

#endif
