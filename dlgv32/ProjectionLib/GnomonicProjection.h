// GnomonicProjection.h: interface for the GnomonicProjection class.
//
// Developer by: Mike Childs
//      Started: 4/3/98
//////////////////////////////////////////////////////////////////////

#ifndef _GNOMONICPROJECTION_H_
#define _GNOMONICPROJECTION_H_

#include "AzimuthalProjection.h"

class GnomonicProjection : public AzimuthalProjection  
{
public:
	GnomonicProjection( double centralLongitude, double centralLatitude,
                        double falseEasting, double falseNorthing,
                        double sphereRadius, DATUM d, UNIT u,
                        DATUM geoDatum = DEFAULT_DATUM, UNIT geoUnit = ARC_DEGREES );
    GnomonicProjection( const GnomonicProjection& p );

    // Accessors
    PROJSYS getProjectionSystem() const;

    // Cloning
    Projection* clone() const;

    // String override
    string toString() const;
};

inline PROJSYS
GnomonicProjection::getProjectionSystem() const
{
    return GNOMON;
}

inline string
GnomonicProjection::toString() const
{
    string str = "Gnomonic Projection\r\n";
    str += AzimuthalProjection::toString();
    return str;
}

#endif
