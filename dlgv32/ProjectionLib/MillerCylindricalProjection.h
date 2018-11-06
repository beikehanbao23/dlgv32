// MillerCylindricalProjection.h: interface for the MillerCylindricalProjection class.
//
// Developer by: Mike Childs
//      Started: 4/5/98
//////////////////////////////////////////////////////////////////////

#ifndef _MILLERCYLINDRICALPROJECTION_H_
#define _MILLERCYLINDRICALPROJECTION_H_

#include "PseudocylindricalProjection.h"

class MillerCylindricalProjection : public PseudocylindricalProjection  
{
public:
	MillerCylindricalProjection( double sphereRadius, double centralMeridian,
                                 double falseEasting, double falseNorthing,
                                 DATUM d, UNIT u,
                                 DATUM geoDatum = DEFAULT_DATUM, UNIT geoUnit = ARC_DEGREES );
    MillerCylindricalProjection( const MillerCylindricalProjection& p );

    // Accessors
    PROJSYS getProjectionSystem() const;

    // Cloning
    Projection* clone() const;

    // String override
    string toString() const;
};

inline PROJSYS
MillerCylindricalProjection::getProjectionSystem() const
{
    return MILLER;
}

inline string
MillerCylindricalProjection::toString() const
{
    string str = "Miller Cylindrical Projection\r\n";
    str += PseudocylindricalProjection::toString();
    return str;
}

#endif
