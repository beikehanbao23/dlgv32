// LambertConformalConicProjection.cpp: implementation of the LambertConformalConicProjection class.
//
// Developed by: Mike Childs
//      Started: 1/24/98
//////////////////////////////////////////////////////////////////////

#include "LambertConformalConicProjection.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LambertConformalConicProjection::LambertConformalConicProjection( double stdpr1, double stdpr2, double sMajor, 
                                              double sMinor, double centMer, double originLat,
                                              double fe, double fn, DATUM d, UNIT u,
                                              DATUM geoDatum, UNIT geoUnit )
: ConicProjection( sMajor, sMinor, centMer, originLat, fe, fn, d, u, geoDatum, geoUnit )
{
    setFirstStandardParallel( stdpr1 );
    setSecondStandardParallel( stdpr2 );
}

LambertConformalConicProjection::LambertConformalConicProjection( const LambertConformalConicProjection& p )
: ConicProjection(p)
{
    if ( this != &p )
    {
        setFirstStandardParallel( p.getFirstStandardParallel() );
        setSecondStandardParallel( p.getSecondStandardParallel() );
    }
}

// Comparison functions
bool
LambertConformalConicProjection::operator==( const Projection& p ) const
{
    // Check to see if the projection passed in is of the correct type
    if ( getProjectionSystem() == p.getProjectionSystem() )
    {
        const LambertConformalConicProjection* pRHS = dynamic_cast<const LambertConformalConicProjection*>(&p);
        if ( NULL != pRHS )
        {
            if ( getFirstStandardParallel()  == pRHS->getFirstStandardParallel() &&
                 getSecondStandardParallel() == pRHS->getSecondStandardParallel() )
            {
                return ConicProjection::operator==( *pRHS );
            }
        }
    }

    return false;
}

// Cloning
Projection*
LambertConformalConicProjection::clone() const
{
    return ( new LambertConformalConicProjection( *this ) );
}

// String override
string
LambertConformalConicProjection::toString() const
{
    string str = "Lambert Conformal Conic Projection\r\n";
    str += ConicProjection::toString();
    str += "\r\nFIRST STANDARD PARALLEL: ";
    str += packedDMSToString( getFirstStandardParallel(), true );
    str += "\r\nSECOND STANDARD PARALLEL: ";
    str += packedDMSToString( getSecondStandardParallel(), true );

    return str;
}

bool 
LambertConformalConicProjection::checkCoordinateRange( double latitude, double longitude ) const
{
    if ( !Projection::checkCoordinateRange( latitude, longitude ) )
    {
        return false;
    }

    double deltaN = ( 90.0 - packedDMSToDouble( getSecondStandardParallel() ) ) / 20.0;
    double deltaS = ( packedDMSToDouble( getFirstStandardParallel() ) + 90.0 ) / 20.0;
    double maxLat = 90.0 - deltaN * deltaN;
    double minLat = -90 + deltaS * deltaS;
    return ( latitude <= maxLat && latitude >= minLat );
}
