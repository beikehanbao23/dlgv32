// OrthographicProjection.h: interface for the OrthographicProjection class.
//
// Developer by: Mike Childs
//      Started: 4/4/98
//////////////////////////////////////////////////////////////////////

#ifndef _ORTHOGRAPHICPROJECTION_H_
#define _ORTHOGRAPHICPROJECTION_H_

#include "AzimuthalProjection.h"

class OrthographicProjection : public AzimuthalProjection  
{
public:
	OrthographicProjection( double centralLongitude, double centralLatitude,
                            double falseEasting, double falseNorthing,
                            double sphereRadius, DATUM d, UNIT u,
                            DATUM geoDatum = DEFAULT_DATUM, UNIT geoUnit = ARC_DEGREES );
    OrthographicProjection( const OrthographicProjection& p );

    // Accessors
    PROJSYS getProjectionSystem() const;

    // Cloning
    Projection* clone() const;

    // String override
    string toString() const;
};

inline PROJSYS
OrthographicProjection::getProjectionSystem() const
{
    return ORTHO;
}

inline string
OrthographicProjection::toString() const
{
    string str = "Orthographic Projection\r\n";
    str += AzimuthalProjection::toString();
    return str;
}

#endif
