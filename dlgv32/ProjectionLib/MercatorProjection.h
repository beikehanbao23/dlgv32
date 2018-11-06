// MercatorProjection.h: interface for the MercatorProjection class.
//
// Developed by: Mike Childs
//      Started: 4/4/98
//////////////////////////////////////////////////////////////////////

#ifndef _MERCATORPROJECTION_H_
#define _MERCATORPROJECTION_H_

#include "Projection.h"

class MercatorProjection : public Projection  
{
public:
	MercatorProjection( double sMajor, double sMinor, double centMer, double originLat,
                        double fe, double fn, DATUM d, UNIT u,
                        DATUM geoDatum = DEFAULT_DATUM, UNIT geoUnit = ARC_DEGREES );
    MercatorProjection( const MercatorProjection& p );

    // Accessors
    PROJSYS getProjectionSystem() const;
    double getSemiMajorAxis() const;
    double getSemiMinorAxis() const;
    double getCentralMeridian() const;
    double getOriginLatitude() const;
    double getFalseEasting() const;
    double getFalseNorthing() const;

    // Modifiers

    virtual void setSemiMajorAxis( double sMajor );
        /* Sets the semi-major axis of the ellipsoid.  If zero, Clarke 1866 in meters
           is assumed. */

    virtual void setSemiMinorAxis( double sMinor );
        /* ( sMinor < 0 ) -> eccentricity squared of the ellipsoid,
           ( sMinor = 0 ) -> spherical form is assumed
           ( sMinor > 0 ) -> semi-minor axis of the ellipsoid. */

    virtual void setCentralMeridian( double centMer );
        /* Sets the longitude of the central meridian 
           The angle should be entered in packed degrees/minutes/seconds
           format (DDDMMMSSS.SS) */

    virtual void setOriginLatitude( double originLat );
        /* Sets the latitude of the projection origin 
           The angle should be entered in packed degrees/minutes/seconds
           format (DDDMMMSSS.SS) */

    virtual void setFalseEasting( double fe );
        /* Sets the false easting in the same units as the semi-major axis */

    virtual void setFalseNorthing( double fn );
        /* Sets the false northing in the same units as the semi-major axis */

    // Projection functions
    bool projectToGeo( double x, double y, 
                       double& latitude, double& longitude ) const;
    bool projectFromGeo( double latitude, double longitude,
                         double& x, double& y ) const;

    // Operator overloads
    bool operator==( const Projection& p ) const;

    // toString override
    virtual string toString() const;

    // Cloning
    virtual Projection* clone() const;

protected:
    // Overrides
    virtual bool checkCoordinateRange( double latitude, double longitude ) const;

    // Data members
    double d_projParams[15];
};

inline PROJSYS
MercatorProjection::getProjectionSystem() const
{
    return MERCAT;
}

inline double 
MercatorProjection::getSemiMajorAxis() const
{
    return d_projParams[0];
}

inline double 
MercatorProjection::getSemiMinorAxis() const
{
    return d_projParams[1];
}

inline double 
MercatorProjection::getCentralMeridian() const
{
    return d_projParams[4];
}

inline double 
MercatorProjection::getOriginLatitude() const
{
    return d_projParams[5];
}
    
inline double 
MercatorProjection::getFalseEasting() const
{
    return d_projParams[6];
}
    
inline double 
MercatorProjection::getFalseNorthing() const
{
    return d_projParams[7];
}

inline void 
MercatorProjection::setSemiMajorAxis( double sMajor )
{
    d_projParams[0] = sMajor;
}
    
inline void 
MercatorProjection::setSemiMinorAxis( double sMinor )
{
    d_projParams[1] = sMinor;
}
    
inline void 
MercatorProjection::setCentralMeridian( double centMer )
{
    d_projParams[4] = centMer;
}
 
inline void 
MercatorProjection::setOriginLatitude( double originLat )
{
    d_projParams[5] = originLat;
}

inline void 
MercatorProjection::setFalseEasting( double fe )
{
    d_projParams[6] = fe;
}

inline void 
MercatorProjection::setFalseNorthing( double fn )
{
    d_projParams[7] = fn;
}

#endif
