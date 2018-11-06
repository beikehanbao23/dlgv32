// RobinsonProjection.h: interface for the RobinsonProjection class.
//
// Developer by: Mike Childs
//      Started: 4/5/98
//////////////////////////////////////////////////////////////////////

#ifndef _ROBINSONPROJECTION_H_
#define _ROBINSONPROJECTION_H_

#include "PseudocylindricalProjection.h"

class RobinsonProjection : public PseudocylindricalProjection  
{
public:
	RobinsonProjection( double sphereRadius, double centralMeridian,
                        double falseEasting, double falseNorthing,
                        DATUM d, UNIT u,
                        DATUM geoDatum = DEFAULT_DATUM, UNIT geoUnit = ARC_DEGREES );
    RobinsonProjection( const RobinsonProjection& p );

    // Accessors
    PROJSYS getProjectionSystem() const;

    // Cloning
    Projection* clone() const;

    // String override
    string toString() const;
};

inline PROJSYS
RobinsonProjection::getProjectionSystem() const
{
    return ROBIN;
}

inline string
RobinsonProjection::toString() const
{
    string str = "Robinson Projection\r\n";
    str += PseudocylindricalProjection::toString();
    return str;
}

#endif
