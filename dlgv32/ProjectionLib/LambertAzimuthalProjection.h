// LambertAzimuthalProjection.h: interface for the LambertAzimuthalProjection class.
//
// Developer by: Mike Childs
//      Started: 4/4/98
//////////////////////////////////////////////////////////////////////

#ifndef _LAMBERTAZIMUTHALPROJECTION_H_
#define _LAMBERTAZIMUTHALPROJECTION_H_

#include "AzimuthalProjection.h"

class LambertAzimuthalProjection : public AzimuthalProjection  
{
public:
	LambertAzimuthalProjection( double centralLongitude, double centralLatitude,
                                double falseEasting, double falseNorthing,
                                double sphereRadius, DATUM d, UNIT u,
                                DATUM geoDatum = DEFAULT_DATUM, UNIT geoUnit = ARC_DEGREES );
    LambertAzimuthalProjection( const LambertAzimuthalProjection& p );

    // Accessors
    PROJSYS getProjectionSystem() const;

    // Cloning
    Projection* clone() const;

    // String override
    string toString() const;
};

inline PROJSYS
LambertAzimuthalProjection::getProjectionSystem() const
{
    return LAMAZ;
}

inline string
LambertAzimuthalProjection::toString() const
{
    string str = "Lambert Azimuthal Projection\r\n";
    str += AzimuthalProjection::toString();
    return str;
}

#endif
