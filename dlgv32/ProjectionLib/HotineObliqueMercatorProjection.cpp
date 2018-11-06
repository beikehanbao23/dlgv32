// HotineObliqueMercatorProjection.cpp: implementation of the HotineObliqueMercatorProjection class.
//
// Developed by: Mike Childs
//      Started: 4/5/98
//////////////////////////////////////////////////////////////////////

#include "HotineObliqueMercatorProjection.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// Hotine A Constructor
HotineObliqueMercatorProjection::HotineObliqueMercatorProjection( double scaleFactor, 
                                                                  double long1,
                                                                  double lat1,
                                                                  double long2,
                                                                  double lat2,
                                                                  double sMajor, 
                                                                  double sMinor, 
                                                                  double originLat, 
                                                                  double fe, 
                                                                  double fn, 
                                                                  DATUM d, UNIT u, 
                                                                  DATUM geoDatum, UNIT geoUnit )
: MercatorProjection(sMajor,sMinor,0.0,originLat,fe,fn,d,u,geoDatum,geoUnit)
{
    setProjectionCenterScaleFactor( scaleFactor );
    setLongitude1( long1 );
    setLatitude1( lat1 );
    setLongitude2( long2 );
    setLatitude2( lat2 );
    
    // Denote HotineA
    d_projParams[12] = 0;
}

// Hotine B Constructor
HotineObliqueMercatorProjection::HotineObliqueMercatorProjection( double scaleFactor, 
                                                                  double aziAng,
                                                                  double sMajor,
                                                                  double sMinor,
                                                                  double aziPt,
                                                                  double originLat,
                                                                  double fe,
                                                                  double fn,
                                                                  DATUM d, UNIT u,
                                                                  DATUM geoDatum, UNIT geoUnit )
: MercatorProjection(sMajor,sMinor,0.0,originLat,fe,fn,d,u,geoDatum,geoUnit)
{
    setProjectionCenterScaleFactor( scaleFactor );
    setAzimuthAngle( aziAng );
    setAzimuthPoint( aziPt );

    // Denote HotineB
    d_projParams[12] = 1;
}

HotineObliqueMercatorProjection::HotineObliqueMercatorProjection( const HotineObliqueMercatorProjection& p )
: MercatorProjection(p)
{
    if ( this != &p )
    {
        setProjectionCenterScaleFactor( p.getProjectionCenterScaleFactor() );
        setAzimuthAngle( p.getAzimuthAngle() );
        setAzimuthPoint( p.getAzimuthPoint() );
        setLongitude1( p.getLongitude1() );
        setLongitude2( p.getLongitude2() );
        setLatitude1( p.getLatitude1() );
        setLatitude2( p.getLatitude2() );
        d_projParams[12] = p.d_projParams[12];
    }
}

// Comparison functions
bool 
HotineObliqueMercatorProjection::operator==( const Projection& p ) const
{
    const HotineObliqueMercatorProjection* pRHS = dynamic_cast<const HotineObliqueMercatorProjection*>(&p);
    if ( NULL != pRHS )
    {
        if ( getProjectionCenterScaleFactor() == pRHS->getProjectionCenterScaleFactor() &&
             getAzimuthAngle()                == pRHS->getAzimuthAngle()               &&
             getAzimuthPoint()                == pRHS->getAzimuthPoint()               &&
             getLongitude1()                  == pRHS->getLongitude1()                 &&
             getLongitude2()                  == pRHS->getLongitude2()                 &&
             getLatitude1()                   == pRHS->getLatitude1()                  &&
             getLatitude2()                   == pRHS->getLatitude2()                  &&
             d_projParams[12]                 == pRHS->d_projParams[12] )
        {
            return MercatorProjection::operator==( p );
        }
    }

    return false;
}

// toString override
string
HotineObliqueMercatorProjection::toString() const
{
    // Hotine A
    if ( 0 == d_projParams[12] )
    {
        string str = "Hotine Oblique Mercator A Projection\r\n";
        str += Projection::toString();
        str += "ORIGIN LATITUDE: ";
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
        sprintf( strScale, "\r\nCENTER PROJ SCALE FACTOR: %g", getProjectionCenterScaleFactor() );
        str += strScale;

        str += "\r\nLONGITUDE 1: ";
        str += packedDMSToString( getLongitude1(), false );
        str += "\r\nLATITUDE 1: ";
        str += packedDMSToString( getLatitude1(), true );
        str += "\r\nLONGITUDE 2: ";
        str += packedDMSToString( getLongitude2(), false );
        str += "\r\nLATITUDE 2: ";
        str += packedDMSToString( getLatitude2(), true );

        return str;
    }
    // Hotine B
    else
    {
        string str = "Hotine Oblique Mercator B Projection\r\n";
        str += Projection::toString();
        str += "ORIGIN LATITUDE: ";
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
        sprintf( strScale, "\r\nCENTER PROJ SCALE FACTOR: %g", getProjectionCenterScaleFactor() );
        str += strScale;

        str += "\r\nAZIMUTH ANGLE: ";
        str += packedDMSToString( getAzimuthAngle(), false );
        str += "\r\nAZIMUTH POINT: ";
        str += packedDMSToString( getAzimuthPoint(), false );

        return str;
    }
}

// Cloning
Projection*
HotineObliqueMercatorProjection::clone() const
{
    return ( new HotineObliqueMercatorProjection( *this ) );
}
