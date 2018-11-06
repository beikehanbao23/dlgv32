// EquirectangularProjection.cpp: implementation of the EquirectangularProjection class.
//
// Developed by: Mike Childs
//      Started: 4/5/98
//////////////////////////////////////////////////////////////////////

#include "EquirectangularProjection.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EquirectangularProjection::EquirectangularProjection( double trueScaleLat, double sphereRadius, 
                                                      double centralMeridian,
                                                      double falseEasting, double falseNorthing,
                                                      DATUM d, UNIT u, DATUM geoDatum, UNIT geoUnit )
: PseudocylindricalProjection(sphereRadius, centralMeridian, falseEasting, falseNorthing,
                              d, u, geoDatum, geoUnit )
{
    setTrueScaleLatitude( trueScaleLat );
}

EquirectangularProjection::EquirectangularProjection( const EquirectangularProjection& p )
: PseudocylindricalProjection(p)
{
    setTrueScaleLatitude( p.getTrueScaleLatitude() );
}

// Comparison
bool
EquirectangularProjection::operator==( const Projection& rhs ) const
{
    const EquirectangularProjection* pRHS = dynamic_cast<const EquirectangularProjection*>(&rhs);
    if ( NULL != pRHS )
    {
        if ( getTrueScaleLatitude() == pRHS->getTrueScaleLatitude() )
        {
            return PseudocylindricalProjection::operator==(rhs);
        }
    }

    return false;
}

// Cloning
Projection*
EquirectangularProjection::clone() const
{
    return ( new EquirectangularProjection( *this ) );
}