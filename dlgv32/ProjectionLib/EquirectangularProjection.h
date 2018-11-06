// EquirectangularProjection.h: interface for the EquirectangularProjection class.
//
// Developer by: Mike Childs
//      Started: 4/5/98
//////////////////////////////////////////////////////////////////////

#ifndef _EquirectangularPROJECTION_H_
#define _EquirectangularPROJECTION_H_

#include "PseudocylindricalProjection.h"

class EquirectangularProjection : public PseudocylindricalProjection  
{
public:
	EquirectangularProjection( double trueScaleLat, double sphereRadius, double centralMeridian,
                               double falseEasting, double falseNorthing,
                               DATUM d, UNIT u,
                               DATUM geoDatum = DEFAULT_DATUM, UNIT geoUnit = ARC_DEGREES );
    EquirectangularProjection( const EquirectangularProjection& p );

    // Accessors
    PROJSYS getProjectionSystem() const;
    double getTrueScaleLatitude() const;

    // Modifiers
    void setTrueScaleLatitude( double trueScaleLat );
        /* Sets the true scale latitude.  The latitude must be in packed DMS
           (DDDMMMSSS.SSS) format. */

    // Operator overloads
    bool operator==( const Projection& rhs ) const;

    // Cloning
    Projection* clone() const;

    // String override
    string toString() const;
};

inline PROJSYS
EquirectangularProjection::getProjectionSystem() const
{
    return EQRECT;
}

inline string
EquirectangularProjection::toString() const
{
    string str = "Equirectangular Projection\r\n";
    str += PseudocylindricalProjection::toString();
    str += "\r\nTRUE SCALE LATITUDE: ";
    str += packedDMSToString( getTrueScaleLatitude(), true );
    return str;
}

inline double
EquirectangularProjection::getTrueScaleLatitude() const
{
    return d_projParams[5];
}

inline void
EquirectangularProjection::setTrueScaleLatitude( double trueScaleLat )
{
    d_projParams[5] = trueScaleLat;
}

#endif
