// RobinsonProjection.cpp: implementation of the RobinsonProjection class.
//
// Developed by: Mike Childs
//      Started: 4/5/98
//////////////////////////////////////////////////////////////////////

#include "RobinsonProjection.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RobinsonProjection::RobinsonProjection( double sphereRadius, double centralMeridian,
                                        double falseEasting, double falseNorthing,
                                        DATUM d, UNIT u, DATUM geoDatum, UNIT geoUnit )
: PseudocylindricalProjection(sphereRadius, centralMeridian, falseEasting, falseNorthing,
                              d, u, geoDatum, geoUnit )
{
}

RobinsonProjection::RobinsonProjection( const RobinsonProjection& p )
: PseudocylindricalProjection(p)
{
}

// Cloning
Projection*
RobinsonProjection::clone() const
{
    return ( new RobinsonProjection( *this ) );
}