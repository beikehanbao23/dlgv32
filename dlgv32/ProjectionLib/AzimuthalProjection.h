// AzimuthalProjection.h: interface for the AzimuthalProjection class.
//
// Developed by: Mike Childs
//      Started: 1/18/98
//////////////////////////////////////////////////////////////////////

#ifndef _AZIMUTHALPROJECTION_H_
#define _AZIMUTHALPROJECTION_H_

#include "Projection.h"

class AzimuthalProjection : public Projection  
{
public:
	AzimuthalProjection( double centralLongitude, double centralLatitude,
                         double falseEasting, double falseNorthing,
                         double sphereRadius, DATUM d, UNIT u,
                         DATUM geoDatum = DEFAULT_DATUM, UNIT geoUnit = ARC_DEGREES );
    AzimuthalProjection( const AzimuthalProjection& p );

    // Accessors
    double getCentralLatitude() const;
        /* Returns the latitude of the center of the projection
           The angle will be returned in packed degrees/minutes/seconds
           format (DDDMMMSSS.SS) */

    double getCentralLongitude() const;
        /* Returns the longitude of the center of the projection
           The angle will be returned in packed degrees/minutes/seconds
           format (DDDMMMSSS.SS) */

    double getFalseEasting() const;
        /* Returns the false easting */

    double getFalseNorthing() const;
        /* Returns the false northing */

    double getSphereRadius() const;
        /* Returns the radius of the reference sphere */

    // Modifers
    virtual void setCentralLatitude( double centralLatitude );
        /* Sets latitude of center of projection. 
           The angle should be entered in packed degrees/minutes/seconds
           format (DDDMMMSSS.SS) */

    virtual void setCentralLongitude( double centralLongitude );
        /* Sets longitude of center of projection 
           The angle should be entered in packed degrees/minutes/seconds
           format (DDDMMMSSS.SS) */

    virtual void setFalseEasting( double falseEasting );
        /* Sets false easting */

    virtual void setFalseNorthing( double falseNorthing );
        /* Sets false northing */

    virtual void setSphereRadius( double sphereRadius );
        /* Sets the radius of the reference sphere.  If zero, 6370997 meters is used. */

    // Projection functions
    bool projectToGeo( double x, double y, 
                       double& latitude, double& longitude ) const;
    bool projectFromGeo( double latitude, double longitude,
                         double& x, double& y ) const;

    // Operator overloads
    bool operator==( const Projection& p ) const;

    // toString override
    virtual string toString() const;

protected:
    // Overrides
    virtual bool checkCoordinateRange( double latitude, double longitude ) const;

    double d_projectionParameters[15];
    double d_badDegreeRadius;
};

inline double
AzimuthalProjection::getCentralLatitude() const
{
    return d_projectionParameters[5];
}

inline double
AzimuthalProjection::getCentralLongitude() const
{
    return d_projectionParameters[4];
}

inline double
AzimuthalProjection::getFalseEasting() const
{
    return d_projectionParameters[6];
}

inline double
AzimuthalProjection::getFalseNorthing() const
{
    return d_projectionParameters[7];
}

inline double
AzimuthalProjection::getSphereRadius() const
{
    return d_projectionParameters[0];
}

inline void
AzimuthalProjection::setCentralLatitude( double centralLatitude )
{
    d_projectionParameters[5] = centralLatitude;
}

inline void
AzimuthalProjection::setCentralLongitude( double centralLongitude )
{
    d_projectionParameters[4] = centralLongitude;
}

inline void
AzimuthalProjection::setFalseEasting( double falseEasting )
{
    d_projectionParameters[6] = falseEasting;
}

inline void
AzimuthalProjection::setFalseNorthing( double falseNorthing )
{
    d_projectionParameters[7] = falseNorthing;
}

inline void
AzimuthalProjection::setSphereRadius( double sphereRadius )
{
    d_projectionParameters[0] = sphereRadius;
}

#endif
