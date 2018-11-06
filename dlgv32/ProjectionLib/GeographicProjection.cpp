// GeographicProjection.cpp: implementation of the GeographicProjection class.
//
// Developed by: Mike Childs
//      Started: 1/17/98
//////////////////////////////////////////////////////////////////////

#include "GeographicProjection.h"
#include "DatumConvertor.h"

// GCTPC includes
#include "gctpc/gctpc.h"
#include "gctpc/proj.h"
#include "gctpc/untfz.h"

#ifndef NULL
#define NULL 0
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GeographicProjection::GeographicProjection( DATUM d, UNIT u, DATUM geoDatum, UNIT geoUnit )
: Projection(d,u,geoDatum,geoUnit)
{

}

GeographicProjection::GeographicProjection( const GeographicProjection& p )
: Projection(p)
{
}

GeographicProjection::~GeographicProjection()
{

}

bool
GeographicProjection::projectToGeo( double x, double y,
                                    double& latitude, double& longitude ) const
{
    // Test for simple case where units and datums are equal
    if ( ( getDatum() == getGeoDatum() ) && ( getUnit() == getGeoUnit() ) )
    {
        latitude = y;
        longitude = x;
    }
    else
    {
        // Conver the units
        double factor;
        untfz( getUnit(), getGeoUnit(), &factor );
        latitude = y * factor;
        longitude = x * factor;

        // Convert the datums
        return convertDatum( latitude, longitude, getDatum(), getGeoDatum() );
    }

    return true;
}

bool
GeographicProjection::projectFromGeo( double latitude, double longitude,
                                      double& x, double& y ) const
{
    // Test for simple case where units and datums are equal
    if ( ( getDatum() == getGeoDatum() ) && ( getUnit() == getGeoUnit() ) )
    {
        x = longitude;
        y = latitude;
    }
    else
    {
        // Convert the datums
        if ( !convertDatum( latitude, longitude, getGeoDatum(), getDatum() ) )
        {
            return false;
        }

        // Convert the units
        double factor;
        untfz( getGeoUnit(), getUnit(), &factor );
        y = latitude * factor;
        x = longitude * factor;
    }

    return true;
}

// Cloning
Projection*
GeographicProjection::clone() const
{
    return ( new GeographicProjection( *this ) );
}