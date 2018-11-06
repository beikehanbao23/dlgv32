// SinusoidalProjection.h: interface for the SinusoidalProjection class.
//
// Developer by: Mike Childs
//      Started: 4/5/98
//////////////////////////////////////////////////////////////////////

#ifndef _SINUSOIDALPROJECTION_H_
#define _SINUSOIDALPROJECTION_H_

#include "PseudocylindricalProjection.h"

class SinusoidalProjection : public PseudocylindricalProjection  
{
public:
	SinusoidalProjection( double sphereRadius, double centralMeridian,
                          double falseEasting, double falseNorthing,
                          DATUM d, UNIT u,
                          DATUM geoDatum = DEFAULT_DATUM, UNIT geoUnit = ARC_DEGREES );
    SinusoidalProjection( const SinusoidalProjection& p );

    // Accessors
    PROJSYS getProjectionSystem() const;

    // Cloning
    Projection* clone() const;

    // String override
    string toString() const;
};

inline PROJSYS
SinusoidalProjection::getProjectionSystem() const
{
    return SNSOID;
}

inline string
SinusoidalProjection::toString() const
{
    string str = "Sinusoidal Projection\r\n";
    str += PseudocylindricalProjection::toString();
    return str;
}

#endif
