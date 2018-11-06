// PolarStereographicProjection.cpp - implementation of PolarStereographicProjection class
//
// Developed by: Mike Childs
//      Started: 2/26/98

#include "PolarStereographicProjection.h"

PolarStereographicProjection::PolarStereographicProjection( double longPole, double trueScale,
                                                            double sMajor, double sMinor,
                                                            double falseEasting, double falseNorthing,
                                                            DATUM d, UNIT u,
                                                            DATUM geoDatum, UNIT geoUnit )
: AzimuthalProjection(longPole, trueScale, falseEasting, falseNorthing,
                      sMajor, d, u, geoDatum, geoUnit )
{
    setSemiMinorAxis( sMinor );
}

PolarStereographicProjection::PolarStereographicProjection( const PolarStereographicProjection& p )
: AzimuthalProjection(p)
{
    setSemiMinorAxis( p.getSemiMinorAxis() );
}

// Cloning
Projection*
PolarStereographicProjection::clone() const
{
    return ( new PolarStereographicProjection( *this ) );
}

// String stuff
string
PolarStereographicProjection::toString() const
{
    // The polar stereographic toString doesn't use the AzimuthalProjection toString
    // because the longitude pole is the same as the central longitude and the true
    // scale latitude is the same as the central latitude
    string str = "Polar Stereographic Projection\r\n";
    str += Projection::toString();
    str += "LONGITUDE POLE: ";
    str += packedDMSToString( getLongitudePole(), false );
    str += "\r\nTRUE SCALE LATITUDE: ";
    str += packedDMSToString( getTrueScaleLatitude(), true );

    char strFalseEasting[40];
    sprintf( strFalseEasting, "\r\nFALSE EASTING: %g", getFalseEasting() );
    str += strFalseEasting;
    
    char strFalseNorthing[40];
    sprintf( strFalseNorthing, "\r\nFALSE NORTHING: %g", getFalseNorthing() );
    str += strFalseNorthing;

    char strSphereRadius[40];
    sprintf( strSphereRadius, "\r\nSEMI-MAJOR AXIS: %g", getSemiMajorAxis() );
    str += strSphereRadius;

    char strSemiMinorAxis[40];
    sprintf( strSemiMinorAxis, "\r\nSEMI-MINOR AXIS: %g", getSemiMinorAxis() );
    str += strSemiMinorAxis;

    return str;
}

bool 
PolarStereographicProjection::checkCoordinateRange( double latitude, double longitude ) const
{
    if ( !Projection::checkCoordinateRange( latitude, longitude ) )
    {
        return false;
    }

    // Only allow coordinates up to 85 degrees latitude to the opposite pole
    if ( getTrueScaleLatitude() < 0.0 )
    {
        return ( latitude < 85.0 );
    }
    else
    {
        return ( latitude > -85.0 );
    }
}
