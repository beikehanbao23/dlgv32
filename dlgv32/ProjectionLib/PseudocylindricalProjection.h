// PseudocylindricalProjection.h: interface for the PseudocylindricalProjection class.
//
// Developed by: Mike Childs
//      Started: 4/5/98
//////////////////////////////////////////////////////////////////////

#ifndef _PSEUDOCYLINDRICALPROJECTION_H_
#define _PSEUDOCYLINDRICALPROJECTION_H_

#include "Projection.h"

class PseudocylindricalProjection : public Projection  
{
public:
	PseudocylindricalProjection( double sphereRadius, double centMer,
                                 double falseEasting, double falseNorthing,
                                 DATUM d, UNIT u,
                                 DATUM geoDatum = DEFAULT_DATUM, UNIT geoUnit = ARC_DEGREES );
    PseudocylindricalProjection( const PseudocylindricalProjection& p );

    // Accessors
    double getCentralMeridian() const;
        /* Returns the longitude of the central meridian of the projection.
           The angle will be returned in packed degrees/minutes/seconds
           format (DDDMMMSSS.SS) */

    double getFalseEasting() const;
        /* Returns the false easting */

    double getFalseNorthing() const;
        /* Returns the false northing */

    double getSphereRadius() const;
        /* Returns the radius of the reference sphere */

    // Modifers
    virtual void setCentralMeridian( double centralMeridian );
        /* Sets longitude of central meridian of the projection.
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
    double d_projParams[15];
};

inline double
PseudocylindricalProjection::getCentralMeridian() const
{
    return d_projParams[4];
}

inline double
PseudocylindricalProjection::getFalseEasting() const
{
    return d_projParams[6];
}

inline double
PseudocylindricalProjection::getFalseNorthing() const
{
    return d_projParams[7];
}

inline double
PseudocylindricalProjection::getSphereRadius() const
{
    return d_projParams[0];
}

inline void
PseudocylindricalProjection::setCentralMeridian( double centralMeridian )
{
    d_projParams[4] = centralMeridian;
}

inline void
PseudocylindricalProjection::setFalseEasting( double falseEasting )
{
    d_projParams[6] = falseEasting;
}

inline void
PseudocylindricalProjection::setFalseNorthing( double falseNorthing )
{
    d_projParams[7] = falseNorthing;
}

inline void
PseudocylindricalProjection::setSphereRadius( double sphereRadius )
{
    d_projParams[0] = sphereRadius;
}

#endif
