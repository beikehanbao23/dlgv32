// HotineObliqueMercatorProjection.h: interface for the HotineObliqueMercatorProjection class.
//
// Developed by: Mike Childs
//      Started: 4/6/98
//////////////////////////////////////////////////////////////////////

#ifndef _HOTINEOBLIQUEMERCATORPROJECTION_H_
#define _HOTINEOBLIQUEMERCATORPROJECTION_H_

#include "MercatorProjection.h"

class HotineObliqueMercatorProjection : public MercatorProjection  
{
public:
    // Hotine A Constructor
    HotineObliqueMercatorProjection( double scaleFactor, double long1, double lat1,
                                     double long2, double lat2, double sMajor,
                                     double sMinor, double originLat, double fe, double fn,
                                     DATUM d, UNIT u,
                                     DATUM geoDatum = DEFAULT_DATUM, UNIT geoUnit = ARC_DEGREES );

    // Hotine B Constructor
	HotineObliqueMercatorProjection( double scaleFactor, double aziAng, 
                                     double sMajor, double sMinor, 
                                     double aziPt, double originLat, 
                                     double fe, double fn, 
                                     DATUM d, UNIT u,
                                     DATUM geoDatum = DEFAULT_DATUM, UNIT geoUnit = ARC_DEGREES );
    HotineObliqueMercatorProjection( const HotineObliqueMercatorProjection& p );

    // Accessors
    PROJSYS getProjectionSystem() const;
    double getProjectionCenterScaleFactor() const;
    double getAzimuthAngle() const;
    double getAzimuthPoint() const;
    double getLongitude1() const;
    double getLongitude2() const;
    double getLatitude1() const;
    double getLatitude2() const;

    // Modifiers
    void setProjectionCenterScaleFactor( double scaleFactor );
        /* Set the scale factor at the center of the projection */

    void setAzimuthAngle( double aziAng );
        /* Set the azimuth angle east of north of center line */

    void setAzimuthPoint( double aziPt );
        /* Set the longitude of point on central meridian where azimuth occurs */

    void setLongitude1( double long1 );
        /* Sets the longitude of first point on center line */

    void setLongitude2( double long2 );
        /* Sets the longitude of second point on center line */

    void setLatitude1( double lat1 );
        /* Sets the latitude of first point on center line */

    void setLatitude2( double lat2 );
        /* Sets the latitude of second point on center line */

    // Operator overloads
    bool operator==( const Projection& p ) const;

    // toString override
    virtual string toString() const;

    // Cloning
    virtual Projection* clone() const;
};

inline PROJSYS
HotineObliqueMercatorProjection::getProjectionSystem() const
{
    return HOM;
}

inline double
HotineObliqueMercatorProjection::getProjectionCenterScaleFactor() const
{
    return d_projParams[2];
}

inline void
HotineObliqueMercatorProjection::setProjectionCenterScaleFactor( double scaleFactor )
{
    d_projParams[2] = scaleFactor;
}

inline double 
HotineObliqueMercatorProjection::getAzimuthAngle() const
{
    return d_projParams[3];
}
    
inline void 
HotineObliqueMercatorProjection::setAzimuthAngle( double aziAng )
{
    d_projParams[3] = aziAng;
}
    
inline double
HotineObliqueMercatorProjection::getAzimuthPoint() const
{
    return getCentralMeridian();
}
    
inline void
HotineObliqueMercatorProjection::setAzimuthPoint( double aziPt )
{
    setCentralMeridian( aziPt );
}
    
inline double 
HotineObliqueMercatorProjection::getLongitude1() const
{
    return d_projParams[8];
}
    
inline void 
HotineObliqueMercatorProjection::setLongitude1( double long1 )
{
    d_projParams[8] = long1;
}
    
inline double 
HotineObliqueMercatorProjection::getLongitude2() const
{
    return d_projParams[10];
}
    
inline void
HotineObliqueMercatorProjection::setLongitude2( double long2 )
{
    d_projParams[10] = long2;
}
    
inline double 
HotineObliqueMercatorProjection::getLatitude1() const
{
    return d_projParams[9];
}
    
inline void
HotineObliqueMercatorProjection::setLatitude1( double lat1 )
{
    d_projParams[9] = lat1;
}
    
inline double 
HotineObliqueMercatorProjection::getLatitude2() const
{
    return d_projParams[11];
}

inline void
HotineObliqueMercatorProjection::setLatitude2( double lat2 )
{
    d_projParams[11] = lat2;
}

#endif
