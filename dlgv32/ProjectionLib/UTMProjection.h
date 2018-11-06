// UTMProjection.h: interface for the UTMProjection class.
//
// Developed by: Mike Childs
//      Started: 1/17/98
//////////////////////////////////////////////////////////////////////

#ifndef _UTMPROJECTION_H_
#define _UTMPROJECTION_H_

#include "Projection.h"
#include "ZonedProjection.h"

class UTMProjection : public Projection, public ZonedProjection 
{
public:
    // Construction/Destruction
    UTMProjection( long zone, 
                   DATUM d, UNIT u, 
                   DATUM geoDatum = DEFAULT_DATUM, UNIT geoUnit = ARC_DEGREES );
    UTMProjection( double latInZone, double lonInZone, 
                   DATUM d, UNIT u,
                   DATUM geoDatum = DEFAULT_DATUM, UNIT geoUnit = ARC_DEGREES );
    UTMProjection( const UTMProjection& p );
	virtual ~UTMProjection();

    // Accessors
    PROJSYS getProjectionSystem() const;

    // Modifiers
    void setZone( long zone );

    // Projection functions
    bool projectToGeo( double x, double y, 
                       double& latitude, double& longitude ) const;
    bool projectFromGeo( double latitude, double longitude,
                         double& x, double& y ) const;

    // String overload
    string toString() const;

    // Operator overloads
    bool operator==( const Projection& p ) const;

    // Cloning
    Projection* clone() const;

protected:
    // Overrides
    bool checkCoordinateRange( double latitude, double longitude ) const;

private:
    // Data members
    double d_latInZone;
    double d_lonInZone;
};

inline PROJSYS
UTMProjection::getProjectionSystem() const
{
    return UTM;
}

#endif
