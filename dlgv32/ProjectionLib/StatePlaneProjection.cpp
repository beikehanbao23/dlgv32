// StatePlaneProjection.cpp: implementation of the StatePlaneProjection class
//
// Developed by: Mike Childs
//      Started: 3/18/98
//////////////////////////////////////////////////////////////////////

#include "StatePlaneProjection.h"
#include "DatumConvertor.h"

// GCTPC includes
#include "gctpc/gctp.h"
#include "gctpc/gctpc.h"
#include "gctpc/for_init.h"
#include "gctpc/inv_init.h"
#include "gctpc/proj.h"
#include "gctpc/untfz.h"

#ifndef NULL
#define NULL 0
#endif

// Static member initialization
string StatePlaneProjection::d_strNAD27ParamFilename;
string StatePlaneProjection::d_strNAD83ParamFilename;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

StatePlaneProjection::StatePlaneProjection( long zone,
                                            DATUM d, UNIT u, 
                                            DATUM geoDatum, UNIT geoUnit )
: Projection(d,u,geoDatum,geoUnit), ZonedProjection(zone)
{

}


StatePlaneProjection::StatePlaneProjection( const StatePlaneProjection& p )
: Projection(p), ZonedProjection(p)
{
}

StatePlaneProjection::~StatePlaneProjection()
{
}

// Operator overloads
bool
StatePlaneProjection::operator==( const Projection& p ) const
{
    // Check to see if the projection passed in is UTM
    if ( SPCS == p.getProjectionSystem() )
    {
        const StatePlaneProjection* pRHS = dynamic_cast<const StatePlaneProjection*>(&p);
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
StatePlaneProjection::setZone( long zone )
{
    // Make sure the zone number is valid before setting it
    if ( ( zone < 101 || zone > 5400 ) )
    {
        // Invalid zone number, use zero instead
        zone = 0;
    }

    ZonedProjection::setZone( zone );
}

// Projection functions
bool
StatePlaneProjection::projectToGeo( double x, double y, 
                                    double& latitude, double& longitude ) const
{
    double inparm[15];  // input parameter array
	long   iflg;		// error flag

    // Initialize the projection parameter arrays to all zeroes
    for ( int i = 0; i < 15; i++ )
    {
        inparm[i] = 0.0;
    }

    // Initialize the state plane inverse transformation
    InverseTransFunc inv_trans[MAXPROJ + 1];
    inv_init( getProjectionSystem(), getZone(), inparm, 
              DatumConvertor::getDatumEllipsoid( getDatum() ), 
              (char*)d_strNAD27ParamFilename.c_str(),
              (char*)d_strNAD83ParamFilename.c_str(),
              &iflg, inv_trans );

    // Convert the x and y to meters
    double factor;
    untfz( getUnit(), METERS, &factor );
    x *= factor;
    y *= factor;    
    
    // do the inverse transformation
    stplninv( x, y, &longitude, &latitude );

    // Convert the input coordinates from radians to the correct units
    untfz( RADIANS, getGeoUnit(), &factor );
    longitude *= factor;
    latitude *= factor;

    // Convert the datums
    return convertDatum( latitude, longitude, getDatum(), getGeoDatum() );
}

bool
StatePlaneProjection::projectFromGeo( double latitude, double longitude,
                                      double& x, double& y ) const
{
    // Convert the datums
    if ( !convertDatum( latitude, longitude, getGeoDatum(), getDatum() ) )
    {
        return false;
    }

	double outparm[15];	// output parameter array
	long   iflg;		// error flag

    // Initialize the projection parameter arrays to all zeroes
    for ( int i = 0; i < 15; i++ )
    {
        outparm[i] = 0.0;
    }
 
    // Initialize the state plane forward transformation
    ForwardTransFunc for_trans[MAXPROJ + 1];
    for_init( getProjectionSystem(), getZone(), outparm, 
              DatumConvertor::getDatumEllipsoid( getDatum() ), 
              (char*)d_strNAD27ParamFilename.c_str(),
              (char*)d_strNAD83ParamFilename.c_str(),
              &iflg, for_trans );

    // Convert the input coordinates to radians
    double factor;
    untfz( getGeoUnit(), RADIANS, &factor );
    longitude *= factor;
    latitude *= factor;

    // do the forward transformation
    stplnfor( longitude, latitude, &x, &y );

    // Convert the x and y from meters to the correct units
    untfz( METERS, getUnit(), &factor );
    x *= factor;
    y *= factor;

    return true;
}

// Cloning
Projection*
StatePlaneProjection::clone() const
{
    return ( new StatePlaneProjection( *this ) );
}

string
StatePlaneProjection::toString() const
{
    string str = "State Plane Projection\r\n";
    str += Projection::toString();
    str += "STATE PLANE ZONE: ";

    char strZone[10];
    sprintf( strZone, "%d", getZone() );
    str += strZone;

    return str;
}

bool 
StatePlaneProjection::checkCoordinateRange( double latitude, double longitude ) const
{
    if ( !Projection::checkCoordinateRange( latitude, longitude ) )
    {
        return false;
    }

    return ( latitude <= 89.0 && latitude >= -89.0 );
}

