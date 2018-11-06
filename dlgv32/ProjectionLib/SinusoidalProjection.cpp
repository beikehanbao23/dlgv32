// SinusoidalProjection.cpp: implementation of the SinusoidalProjection class.
//
// Developed by: Mike Childs
//      Started: 4/5/98
//////////////////////////////////////////////////////////////////////

#include "SinusoidalProjection.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SinusoidalProjection::SinusoidalProjection( double sphereRadius, double centralMeridian,
                                            double falseEasting, double falseNorthing,
                                            DATUM d, UNIT u, DATUM geoDatum, UNIT geoUnit )
: PseudocylindricalProjection(sphereRadius, centralMeridian, falseEasting, falseNorthing,
                              d, u, geoDatum, geoUnit )
{
}

SinusoidalProjection::SinusoidalProjection( const SinusoidalProjection& p )
: PseudocylindricalProjection(p)
{
}

// Cloning
Projection*
SinusoidalProjection::clone() const
{
    return ( new SinusoidalProjection( *this ) );
}