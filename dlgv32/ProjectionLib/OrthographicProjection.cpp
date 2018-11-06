// OrthographicProjection.cpp: implementation of the OrthographicProjection class.
//
// Developed by: Mike Childs
//      Started: 4/4/98
//////////////////////////////////////////////////////////////////////

#include "OrthographicProjection.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

OrthographicProjection::OrthographicProjection( double centralLongitude, double centralLatitude,
                                                double falseEasting, double falseNorthing,
                                                double sphereRadius, DATUM d, UNIT u,
                                                DATUM geoDatum, UNIT geoUnit )
: AzimuthalProjection(centralLongitude, centralLatitude, falseEasting, falseNorthing,
                      sphereRadius, d, u, geoDatum, geoUnit )
{
    // Set bad radius
    d_badDegreeRadius = 65.0;
}

OrthographicProjection::OrthographicProjection( const OrthographicProjection& p )
: AzimuthalProjection(p)
{
}

// Cloning
Projection*
OrthographicProjection::clone() const
{
    return ( new OrthographicProjection( *this ) );
}