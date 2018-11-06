// GeographicProjection.h: interface for the GeographicProjection class.
//
// Developed by: Mike Childs
//      Started: 1/17/98
//////////////////////////////////////////////////////////////////////

#ifndef _GEOGRAPHICPROJECTION_H_
#define _GEOGRAPHICPROJECTION_H_

#include "Projection.h"

class GeographicProjection : public Projection  
{
public:
	GeographicProjection( DATUM d = NAD27, UNIT u = ARC_DEGREES,
                          DATUM geoDaum = DEFAULT_DATUM, UNIT geoUnit = ARC_DEGREES );
    GeographicProjection( const GeographicProjection& p );
	virtual ~GeographicProjection();
    
    // Accessors
    PROJSYS getProjectionSystem() const;

    // Projection functions 
    bool projectToGeo( double x, double y, 
                       double& latitude, double& longitude ) const;
    bool projectFromGeo( double latitude, double longitude,
                         double& x, double& y ) const;

    // String override
    string toString() const;

    // Cloning
    Projection* clone() const;
};

inline PROJSYS
GeographicProjection::getProjectionSystem() const
{
    return GEO;
}

inline string
GeographicProjection::toString() const
{
    string str = "Geographic Projection\r\n";
    str += Projection::toString();
    return str;
}

#endif
