// PolyconicProjection.cpp: implementation of the PolyconicProjection class.
//
// Developed by: Mike Childs
//      Started: 4/4/98
//////////////////////////////////////////////////////////////////////

#include "PolyconicProjection.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PolyconicProjection::PolyconicProjection( double sMajor, double sMinor, 
                                          double centMer, double originLat,
                                          double fe, double fn, DATUM d, UNIT u,
                                          DATUM geoDatum, UNIT geoUnit )
: ConicProjection( sMajor, sMinor, centMer, originLat, fe, fn, d, u, geoDatum, geoUnit )
{
}

PolyconicProjection::PolyconicProjection( const PolyconicProjection& p )
: ConicProjection(p)
{
}

// Cloning
Projection*
PolyconicProjection::clone() const
{
    return ( new PolyconicProjection( *this ) );
}

// Range checking
bool
PolyconicProjection::checkCoordinateRange( double latitude, double longitude ) const
{
    if ( !Projection::checkCoordinateRange( latitude, longitude ) )
    {
        return false;
    }

    // Only show things in the same longitudinal hemisphere as the central meridian
    double center = packedDMSToDouble( getCentralMeridian() );
    double left = center - 90.0;
    double right = center + 90.0;

    if ( left < -180.0 && longitude > 0.0 )
    {
        longitude -= 360.0;
    }
    else if ( right > 180.0 && longitude < 0.0 )
    {
        longitude += 360.0;
    }

    return ( ( longitude >= left ) && ( longitude <= right ) );
}