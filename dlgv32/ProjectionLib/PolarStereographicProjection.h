// PolarStereographicProjection.h - interface for PolarStereographicProjection class
//
// Developed by: Mike Childs
//      Started: 2/26/98

#ifndef _POLARSTEREOGRAPHICPROJECTION_H_
#define _POLARSTEREOGRAPHICPROJECTION_H_

#include "AzimuthalProjection.h"

class PolarStereographicProjection : public AzimuthalProjection
{
public:
	PolarStereographicProjection( double longPol, double trueScale,
                                  double sMajor,  double sMinor,
                                  double falseEasting, double falseNorthing,
                                  DATUM d, UNIT u,
                                  DATUM geoDatum = DEFAULT_DATUM, UNIT geoUnit = ARC_DEGREES );
    PolarStereographicProjection( const PolarStereographicProjection& p );

    // Accessors
    double getLongitudePole() const;
        /* Returns the longitude down the pole of the map */

    PROJSYS getProjectionSystem() const;

    double getSemiMajorAxis() const;
        /* Returns the semi-major axis */

    double getSemiMinorAxis() const;
        /* Returns the semi-minor axis */

    double getTrueScaleLatitude() const;
        /* Returns the latitude of the true scale */

    // Modifiers
    void setLongitudePole( double longPole );
        /* Sets the longitude down the pole of the map */

    void setSemiMajorAxis( double sMajor );
        /* Sets the semi-major axis */

    void setSemiMinorAxis( double sMinor );
        /* Sets the semi-minor axis */

    void setTrueScaleLatitude( double trueScale );
        /* Sets the latitude of the true scale */

    // String override
    string toString() const;

    // Cloning
    Projection* clone() const;

protected:
    // Overrides
    bool checkCoordinateRange( double latitude, double longitude ) const;
};

inline double
PolarStereographicProjection::getLongitudePole() const
{
    return getCentralLongitude();
}

inline PROJSYS
PolarStereographicProjection::getProjectionSystem() const
{
    return PS;
}

inline double
PolarStereographicProjection::getSemiMajorAxis() const
{
    return getSphereRadius();
}

inline double
PolarStereographicProjection::getSemiMinorAxis() const
{
    return d_projectionParameters[1];
}

inline double
PolarStereographicProjection::getTrueScaleLatitude() const
{
    return getCentralLatitude();
}

inline void
PolarStereographicProjection::setLongitudePole( double longPole )
{
    setCentralLongitude( longPole );
}

inline void
PolarStereographicProjection::setSemiMajorAxis( double sMajor )
{
    setSphereRadius( sMajor );
}

inline void
PolarStereographicProjection::setSemiMinorAxis( double sMinor )
{
    d_projectionParameters[1] = sMinor;
}

inline void
PolarStereographicProjection::setTrueScaleLatitude( double trueScale )
{
    setCentralLatitude( trueScale );
}

#endif
