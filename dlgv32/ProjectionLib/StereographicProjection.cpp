// StereographicProjection.cpp: implementation of the StereographicProjection class.
//
// Developed by: Mike Childs
//      Started: 1/18/98
//////////////////////////////////////////////////////////////////////

#include "StereographicProjection.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

StereographicProjection::StereographicProjection( double centralLongitude, double centralLatitude,
                                                  double falseEasting, double falseNorthing,
                                                  double sphereRadius, DATUM d, UNIT u,
                                                  DATUM geoDatum, UNIT geoUnit )
: AzimuthalProjection(centralLongitude, centralLatitude, falseEasting, falseNorthing,
                      sphereRadius, d, u, geoDatum, geoUnit )
{
}

StereographicProjection::StereographicProjection( const StereographicProjection& p )
: AzimuthalProjection(p)
{
}

// Cloning
Projection*
StereographicProjection::clone() const
{
    return ( new StereographicProjection( *this ) );
}