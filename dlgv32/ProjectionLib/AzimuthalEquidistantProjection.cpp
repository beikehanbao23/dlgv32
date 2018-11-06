// AzimuthalEquidistantProjection.cpp: implementation of the AzimuthalEquidistantProjection class.
//
// Developed by: Mike Childs
//      Started: 4/3/98
//////////////////////////////////////////////////////////////////////

#include "AzimuthalEquidistantProjection.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AzimuthalEquidistantProjection::AzimuthalEquidistantProjection( double centralLongitude, double centralLatitude,
                                                  double falseEasting, double falseNorthing,
                                                  double sphereRadius, DATUM d, UNIT u,
                                                  DATUM geoDatum, UNIT geoUnit )
: AzimuthalProjection(centralLongitude, centralLatitude, falseEasting, falseNorthing,
                      sphereRadius, d, u, geoDatum, geoUnit )
{
}

AzimuthalEquidistantProjection::AzimuthalEquidistantProjection( const AzimuthalEquidistantProjection& p )
: AzimuthalProjection(p)
{
}

// Cloning
Projection*
AzimuthalEquidistantProjection::clone() const
{
    return ( new AzimuthalEquidistantProjection( *this ) );
}