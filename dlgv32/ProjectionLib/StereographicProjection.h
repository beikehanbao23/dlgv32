// StereographicProjection.h: interface for the StereographicProjection class.
//
// Developer by: Mike Childs
//      Started: 1/18/98
//////////////////////////////////////////////////////////////////////

#ifndef _STEREOGRAPHICPROJECTION_H_
#define _STEREOGRAPHICPROJECTION_H_

#include "AzimuthalProjection.h"

class StereographicProjection : public AzimuthalProjection  
{
public:
	StereographicProjection( double centralLongitude, double centralLatitude,
                             double falseEasting, double falseNorthing,
                             double sphereRadius, DATUM d, UNIT u,
                             DATUM geoDatum = DEFAULT_DATUM, UNIT geoUnit = ARC_DEGREES );
    StereographicProjection( const StereographicProjection& p );

    // Accessors
    PROJSYS getProjectionSystem() const;

    // Cloning
    Projection* clone() const;

    // String override
    string toString() const;
};

inline PROJSYS
StereographicProjection::getProjectionSystem() const
{
    return STEREO;
}

inline string
StereographicProjection::toString() const
{
    string str = "Stereographic Projection\r\n";
    str += AzimuthalProjection::toString();
    return str;
}

#endif
