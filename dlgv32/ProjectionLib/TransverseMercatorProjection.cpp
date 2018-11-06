// TransverseMercatorProjection.cpp: implementation of the TransverseMercatorProjection class.
//
// Developed by: Mike Childs
//      Started: 4/5/98
//////////////////////////////////////////////////////////////////////

#include "TransverseMercatorProjection.h"
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

TransverseMercatorProjection::TransverseMercatorProjection( double scaleFactor, 
                                                            double sMajor, 
                                                            double sMinor, 
                                                            double centMer, 
                                                            double originLat, 
                                                            double fe, 
                                                            double fn, 
                                                            DATUM d, UNIT u, 
                                                            DATUM geoDatum, UNIT geoUnit )
: MercatorProjection(sMajor,sMinor,centMer,originLat,fe,fn,d,u,geoDatum,geoUnit)
{
    setCentralMeridianScaleFactor( scaleFactor );
}

TransverseMercatorProjection::TransverseMercatorProjection( const TransverseMercatorProjection& p )
: MercatorProjection(p)
{
    if ( this != &p )
    {
        setCentralMeridianScaleFactor( p.getCentralMeridianScaleFactor() );
    }
}

// Comparison functions
bool 
TransverseMercatorProjection::operator==( const Projection& p ) const
{
    const TransverseMercatorProjection* pRHS = dynamic_cast<const TransverseMercatorProjection*>(&p);
    if ( NULL != pRHS )
    {
        if ( getCentralMeridianScaleFactor() == pRHS->getCentralMeridianScaleFactor() )
        {
            return MercatorProjection::operator==( p );
        }
    }

    return false;
}

// toString override
string
TransverseMercatorProjection::toString() const
{
    string str = "Transverse Mercator Projection\r\n";
    str += Projection::toString();
    str += "CENTRAL MERIDIAN: ";
    str += packedDMSToString( getCentralMeridian(), false );
    str += "\r\nORIGIN LATITUDE: ";
    str += packedDMSToString( getOriginLatitude(), true );

    char strFalseEasting[40];
    sprintf( strFalseEasting, "\r\nFALSE EASTING: %g", getFalseEasting() );
    str += strFalseEasting;

    char strFalseNorthing[40];
    sprintf( strFalseNorthing, "\r\nFALSE NORTHING: %g", getFalseNorthing() );
    str += strFalseNorthing;

    char strSemiMajorAxis[40];
    sprintf( strSemiMajorAxis, "\r\nSEMI-MAJOR AXIS: %g", getSemiMajorAxis() );
    str += strSemiMajorAxis;

    char strSemiMinorAxis[40];
    sprintf( strSemiMinorAxis, "\r\nSEMI-MINOR AXIS: %g", getSemiMinorAxis() );
    str += strSemiMinorAxis;

    char strScale[40];
    sprintf( strScale, "\r\nCENT. MER. SCALE FACTOR: %g", getCentralMeridianScaleFactor() );
    str += strScale;

    return str;
}

// Projection functions
bool 
TransverseMercatorProjection::projectToGeo( double x, double y, 
                                            double& latitude, double& longitude ) const
{
	long   iflg;		// error flag
    
    // Initialize the inverse transformation
    InverseTransFunc inv_trans[MAXPROJ + 1];
    inv_init( getProjectionSystem(), 0, const_cast<double*>(d_projParams), 
              DatumConvertor::getDatumEllipsoid( getDatum() ), 
              NULL, NULL, &iflg, inv_trans );

    // Convert the x and y to meters
    double factor;
    untfz( getUnit(), METERS, &factor );
    x *= factor;
    y *= factor;    
    
    // do the inverse transformation
    tminv( x, y, &longitude, &latitude );

    // Convert the input coordinates from radians to the correct units
    untfz( RADIANS, getGeoUnit(), &factor );
    longitude *= factor;
    latitude *= factor;

    // Convert the datums
    return convertDatum( latitude, longitude, getDatum(), getGeoDatum() );
}

bool
TransverseMercatorProjection::projectFromGeo( double latitude, double longitude,
                                              double& x, double& y ) const
{ 
    // Convert the datums
    if ( !convertDatum( latitude, longitude, getGeoDatum(), getDatum() ) )
    {
        return false;
    }

    long   iflg;
    
    // Initialize the UTM forward transformation
    ForwardTransFunc for_trans[MAXPROJ + 1];
    for_init( getProjectionSystem(), 0, const_cast<double*>(d_projParams), 
              DatumConvertor::getDatumEllipsoid( getDatum() ), 
              NULL, NULL, &iflg, for_trans );

    // Convert the input coordinates to radians
    double factor;
    untfz( getGeoUnit(), RADIANS, &factor );
    longitude *= factor;
    latitude *= factor;

    // do the forward transformation
    tmfor( longitude, latitude, &x, &y );

    // Convert the x and y from meters to the correct units
    untfz( METERS, getUnit(), &factor );
    x *= factor;
    y *= factor;

    return true;
}

// Cloning
Projection*
TransverseMercatorProjection::clone() const
{
    return ( new TransverseMercatorProjection( *this ) );
}
