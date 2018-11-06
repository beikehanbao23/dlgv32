// UTMProjection.cpp: implementation of the UTMProjection class.
//
// Developed by: Mike Childs
//      Started: 1/17/98
//////////////////////////////////////////////////////////////////////

#include "UTMProjection.h"
#include "DatumConvertor.h"

// GCTPC includes
#include "gctpc/gctpc.h"
#include "gctpc/gctp.h"
#include "gctpc/for_init.h"
#include "gctpc/inv_init.h"
#include "gctpc/proj.h"
#include "gctpc/untfz.h"

#ifndef NULL
#define NULL 0
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

UTMProjection::UTMProjection( long zone,
                              DATUM d, UNIT u, 
                              DATUM geoDatum, UNIT geoUnit )
: Projection(d,u,geoDatum,geoUnit), ZonedProjection(zone), 
  d_latInZone(0.0), d_lonInZone(0.0)
{

}

UTMProjection::UTMProjection( double latInZone, double lonInZone,
                              DATUM d, UNIT u, 
                              DATUM geoDatum, UNIT geoUnit )
: Projection(d,u,geoDatum,geoUnit), ZonedProjection(0), 
  d_latInZone(latInZone), d_lonInZone(lonInZone)
{
}

UTMProjection::UTMProjection( const UTMProjection& p )
: Projection(p), ZonedProjection(p)
{
    if ( this != &p )
    {
        d_latInZone = p.d_latInZone;
        d_lonInZone = p.d_lonInZone;
    }
}

UTMProjection::~UTMProjection()
{
}

// Operator overloads
bool
UTMProjection::operator==( const Projection& p ) const
{
    // Check to see if the projection passed in is UTM
    if ( UTM == p.getProjectionSystem() )
    {
        const UTMProjection* pRHS = dynamic_cast<const UTMProjection*>(&p);
        if ( NULL != pRHS )
        {
            if ( getZone() == pRHS->getZone() )
            {
                return Projection::operator==(p);
            }
        }
    }

    return false;
}

// Modifiers
void
UTMProjection::setZone( long zone )
{
    // Make sure the zone number is valid before setting it
    if ( ( zone < -60 || zone > 60 ) )
    {
        // Invalid zone number, use zero instead
        zone = 0;
    }

    ZonedProjection::setZone( zone );
}

// Projection functions
bool 
UTMProjection::projectToGeo( double x, double y, 
                             double& latitude, double& longitude ) const
{
    double inparm[15];  // input parameter array
	long   iflg;		// error flag

    // Initialize the projection parameter arrays to all zeroes
    for ( int i = 0; i < 15; i++ )
    {
        inparm[i] = 0.0;
    }

    // If a zone wasn't specified, use the lat and lon passed in
    if ( 0 == getZone() )
    {
        inparm[0] = d_lonInZone;
        inparm[1] = d_latInZone;
    }
    
    // Initialize the UTM inverse transformation
    InverseTransFunc inv_trans[MAXPROJ + 1];
    inv_init( getProjectionSystem(), getZone(), inparm, 
        DatumConvertor::getDatumEllipsoid( getDatum() ), 
        NULL, NULL, &iflg, inv_trans );

    // Convert the x and y to meters
    double factor;
    untfz( getUnit(), METERS, &factor );
    x *= factor;
    y *= factor;    
    
    // do the inverse transformation
    utminv( x, y, &longitude, &latitude );

    // Convert the input coordinates from radians to the correct units
    untfz( RADIANS, getGeoUnit(), &factor );
    longitude *= factor;
    latitude *= factor;

    // Convert the datums
    return convertDatum( latitude, longitude, getDatum(), getGeoDatum() );
}

bool
UTMProjection::projectFromGeo( double latitude, double longitude,
                               double& x, double& y ) const
{
    // Convert the datums
    if ( !convertDatum( latitude, longitude, getGeoDatum(), getDatum() ) )
    {
        return false;
    }

	double outparm[15];	// output parameter array
    long   iflg;

    // Initialize the projection parameter arrays to all zeroes
    for ( int i = 0; i < 15; i++ )
    {
        outparm[i] = 0.0;
    }

    // If a zone wasn't specified, use the lat and lon passed in
    if ( 0 == getZone() )
    {
        outparm[0] = d_lonInZone;
        outparm[1] = d_latInZone;
    }
    
    // Initialize the UTM forward transformation
    ForwardTransFunc for_trans[MAXPROJ + 1];
    for_init( getProjectionSystem(), getZone(), outparm, 
        DatumConvertor::getDatumEllipsoid( getDatum() ), 
        NULL, NULL, &iflg, for_trans );

    // Convert the input coordinates to radians
    double factor;
    untfz( getGeoUnit(), RADIANS, &factor );
    longitude *= factor;
    latitude *= factor;

    // do the forward transformation
    utmfor( longitude, latitude, &x, &y );

    // Convert the x and y from meters to the correct units
    untfz( METERS, getUnit(), &factor );
    x *= factor;
    y *= factor;

    return true;
}

// Cloning
Projection*
UTMProjection::clone() const
{
    return ( new UTMProjection( *this ) );
}

string
UTMProjection::toString() const
{
    string str = "UTM Projection\r\n";
    str += Projection::toString();
    str += "UTM ZONE: ";

    char strZone[10];
    sprintf( strZone, "%d", getZone() );

    str += strZone;
    return str;
}

bool 
UTMProjection::checkCoordinateRange( double latitude, double longitude ) const
{
    if ( !Projection::checkCoordinateRange( latitude, longitude ) )
    {
        return false;
    }

    // UTM is only valid between 84N and 80S
    return ( latitude <= 84.0 && latitude >= -80.0 );
}
