// GnomonicProjection.cpp: implementation of the GnomonicProjection class.
//
// Developed by: Mike Childs
//      Started: 4/3/98
//////////////////////////////////////////////////////////////////////

#include "GnomonicProjection.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GnomonicProjection::GnomonicProjection( double centralLongitude, double centralLatitude,
                                        double falseEasting, double falseNorthing,
                                        double sphereRadius, DATUM d, UNIT u,
                                        DATUM geoDatum, UNIT geoUnit )
: AzimuthalProjection(centralLongitude, centralLatitude, falseEasting, falseNorthing,
                      sphereRadius, d, u, geoDatum, geoUnit )
{
}

GnomonicProjection::GnomonicProjection( const GnomonicProjection& p )
: AzimuthalProjection(p)
{
}

// Cloning
Projection*
GnomonicProjection::clone() const
{
    return ( new GnomonicProjection( *this ) );
}