// LambertAzimuthalProjection.cpp: implementation of the LambertAzimuthalProjection class.
//
// Developed by: Mike Childs
//      Started: 4/4/98
//////////////////////////////////////////////////////////////////////

#include "LambertAzimuthalProjection.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LambertAzimuthalProjection::LambertAzimuthalProjection( double centralLongitude, double centralLatitude,
                                                        double falseEasting, double falseNorthing,
                                                        double sphereRadius, DATUM d, UNIT u,
                                                        DATUM geoDatum, UNIT geoUnit )
: AzimuthalProjection(centralLongitude, centralLatitude, falseEasting, falseNorthing,
                      sphereRadius, d, u, geoDatum, geoUnit )
{
    // Set the bad degree radius
    d_badDegreeRadius = 24.0;
}

LambertAzimuthalProjection::LambertAzimuthalProjection( const LambertAzimuthalProjection& p )
: AzimuthalProjection(p)
{
}

// Cloning
Projection*
LambertAzimuthalProjection::clone() const
{
    return ( new LambertAzimuthalProjection( *this ) );
}