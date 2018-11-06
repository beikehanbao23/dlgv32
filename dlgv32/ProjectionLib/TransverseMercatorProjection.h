// TransverseMercatorProjection.h: interface for the TransverseMercatorProjection class.
//
// Developed by: Mike Childs
//      Started: 4/5/98
//////////////////////////////////////////////////////////////////////

#ifndef _TRANSVERSEMERCATORPROJECTION_H_
#define _TRANSVERSEMERCATORPROJECTION_H_

#include "MercatorProjection.h"

class TransverseMercatorProjection : public MercatorProjection  
{
public:
	TransverseMercatorProjection( double scaleFactor, double sMajor, double sMinor, 
                                  double centMer, double originLat, double fe, double fn, 
                                  DATUM d, UNIT u,
                                  DATUM geoDatum = DEFAULT_DATUM, UNIT geoUnit = ARC_DEGREES );
    TransverseMercatorProjection( const TransverseMercatorProjection& p );

    // Accessors
    PROJSYS getProjectionSystem() const;
    double getCentralMeridianScaleFactor() const;

    // Modifiers
    void setCentralMeridianScaleFactor( double scaleFactor );
        /* Set the scale factor at the central meridian */

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
};

inline PROJSYS
TransverseMercatorProjection::getProjectionSystem() const
{
    return TM;
}

inline double
TransverseMercatorProjection::getCentralMeridianScaleFactor() const
{
    return d_projParams[2];
}

inline void
TransverseMercatorProjection::setCentralMeridianScaleFactor( double scaleFactor )
{
    d_projParams[2] = scaleFactor;
}

#endif
