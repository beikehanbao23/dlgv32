// VanDerGrintenProjection.h: interface for the VanDerGrintenProjection class.
//
// Developer by: Mike Childs
//      Started: 4/5/98
//////////////////////////////////////////////////////////////////////

#ifndef _VanDerGrintenPROJECTION_H_
#define _VanDerGrintenPROJECTION_H_

#include "PseudocylindricalProjection.h"

class VanDerGrintenProjection : public PseudocylindricalProjection  
{
public:
	VanDerGrintenProjection( double originLat, double sphereRadius, double centralMeridian,
                             double falseEasting, double falseNorthing,
                             DATUM d, UNIT u,
                             DATUM geoDatum = DEFAULT_DATUM, UNIT geoUnit = ARC_DEGREES );
    VanDerGrintenProjection( const VanDerGrintenProjection& p );

    // Accessors
    PROJSYS getProjectionSystem() const;
    double getOriginLatitude() const;

    // Modifiers
    void setOriginLatitude( double originLat );
        /* Sets the origin latitude.  The latitude must be in packed DMS
           (DDDMMMSSS.SSS) format. */

    // Operator overloads
    bool operator==( const Projection& rhs ) const;

    // Cloning
    Projection* clone() const;

    // String override
    string toString() const;
};

inline PROJSYS
VanDerGrintenProjection::getProjectionSystem() const
{
    return VGRINT;
}

inline string
VanDerGrintenProjection::toString() const
{
    string str = "Van der Grinten Projection\r\n";
    str += PseudocylindricalProjection::toString();
    str += "\r\nORIGIN LATITUDE: ";
    str += packedDMSToString( getOriginLatitude(), true );
    return str;
}

inline double
VanDerGrintenProjection::getOriginLatitude() const
{
    return d_projParams[5];
}

inline void
VanDerGrintenProjection::setOriginLatitude( double originLat )
{
    d_projParams[5] = originLat;
}

#endif
