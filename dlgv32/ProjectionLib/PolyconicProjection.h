// PolyconicProjection.h: interface for the PolyconicProjection class.
//
// Developer by: Mike Childs
//      Started: 4/4/98
//////////////////////////////////////////////////////////////////////

#ifndef _POLYCONICPROJECTION_H_
#define _POLYCONICPROJECTION_H_

#include "ConicProjection.h"

class PolyconicProjection : public ConicProjection  
{
public:
	PolyconicProjection( double sMajor, double sMinor, double centMer, 
                         double originLat, double fe, double fn, 
                         DATUM d, UNIT u, 
                         DATUM geoDatum = DEFAULT_DATUM, UNIT geoUnit = ARC_DEGREES );
    PolyconicProjection( const PolyconicProjection& p );

    // Accessors
    PROJSYS getProjectionSystem() const;

    // Cloning
    Projection* clone() const;

    // String override
    string toString() const;

protected:
    // Overrides
    virtual bool checkCoordinateRange( double latitude, double longitude ) const;
};

inline PROJSYS
PolyconicProjection::getProjectionSystem() const
{
    return POLYC;
}

inline string
PolyconicProjection::toString() const
{
    string str = "Polyconic Projection\r\n";
    str += ConicProjection::toString();
    return str;
}

#endif
