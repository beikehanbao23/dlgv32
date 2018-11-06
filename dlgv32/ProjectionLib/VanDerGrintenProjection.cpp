// VanDerGrintenProjection.cpp: implementation of the VanDerGrintenProjection class.
//
// Developed by: Mike Childs
//      Started: 4/5/98
//////////////////////////////////////////////////////////////////////

#include "VanDerGrintenProjection.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

VanDerGrintenProjection::VanDerGrintenProjection( double originLat, double sphereRadius, 
                                                  double centralMeridian,
                                                  double falseEasting, double falseNorthing,
                                                  DATUM d, UNIT u, DATUM geoDatum, UNIT geoUnit )
: PseudocylindricalProjection(sphereRadius, centralMeridian, falseEasting, falseNorthing,
                              d, u, geoDatum, geoUnit )
{
    setOriginLatitude( originLat );
}

VanDerGrintenProjection::VanDerGrintenProjection( const VanDerGrintenProjection& p )
: PseudocylindricalProjection(p)
{
    setOriginLatitude( p.getOriginLatitude() );
}

// Comparison
bool
VanDerGrintenProjection::operator==( const Projection& rhs ) const
{
    const VanDerGrintenProjection* pRHS = dynamic_cast<const VanDerGrintenProjection*>(&rhs);
    if ( NULL != pRHS )
    {
        if ( getOriginLatitude() == pRHS->getOriginLatitude() )
        {
            return PseudocylindricalProjection::operator==(rhs);
        }
    }

    return false;
}

// Cloning
Projection*
VanDerGrintenProjection::clone() const
{
    return ( new VanDerGrintenProjection( *this ) );
}