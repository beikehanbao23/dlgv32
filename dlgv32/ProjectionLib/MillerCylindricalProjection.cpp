// MillerCylindricalProjection.cpp: implementation of the MillerCylindricalProjection class.
//
// Developed by: Mike Childs
//      Started: 4/5/98
//////////////////////////////////////////////////////////////////////

#include "MillerCylindricalProjection.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MillerCylindricalProjection::MillerCylindricalProjection( double sphereRadius, double centralMeridian,
                                                          double falseEasting, double falseNorthing,
                                                          DATUM d, UNIT u, DATUM geoDatum, UNIT geoUnit )
: PseudocylindricalProjection(sphereRadius, centralMeridian, falseEasting, falseNorthing,
                              d, u, geoDatum, geoUnit )
{
}

MillerCylindricalProjection::MillerCylindricalProjection( const MillerCylindricalProjection& p )
: PseudocylindricalProjection(p)
{
}

// Cloning
Projection*
MillerCylindricalProjection::clone() const
{
    return ( new MillerCylindricalProjection( *this ) );
}