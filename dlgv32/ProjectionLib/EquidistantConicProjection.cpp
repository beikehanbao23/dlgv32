// EquidistantConicProjection.cpp: implementation of the EquidistantConicProjection class.
//
// Developed by: Mike Childs
//      Started: 4/6/98
//////////////////////////////////////////////////////////////////////

#include "EquidistantConicProjection.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// Type A Constructor
EquidistantConicProjection::EquidistantConicProjection( double stdpar, 
                                                        double sMajor, double sMinor, 
                                                        double centMer, double originLat,
                                                        double fe, double fn, 
                                                        DATUM d, UNIT u,
                                                        DATUM geoDatum, UNIT geoUnit )
: ConicProjection( sMajor, sMinor, centMer, originLat, fe, fn, d, u, geoDatum, geoUnit )
{
    setStandardParallel( stdpar );
    d_projParams[8] = 0;
}

// Type B Constructor
EquidistantConicProjection::EquidistantConicProjection( double stdpr1, double stdpr2, 
                                                        double sMajor, double sMinor, 
                                                        double centMer, double originLat,
                                                        double fe, double fn, 
                                                        DATUM d, UNIT u,
                                                        DATUM geoDatum, UNIT geoUnit )
: ConicProjection( sMajor, sMinor, centMer, originLat, fe, fn, d, u, geoDatum, geoUnit )
{
    setFirstStandardParallel( stdpr1 );
    setSecondStandardParallel( stdpr2 );
    d_projParams[8] = 1;
}

EquidistantConicProjection::EquidistantConicProjection( const EquidistantConicProjection& p )
: ConicProjection(p)
{
    if ( this != &p )
    {
        setFirstStandardParallel( p.getFirstStandardParallel() );
        setSecondStandardParallel( p.getSecondStandardParallel() );
        setStandardParallel( p.getStandardParallel() );
        d_projParams[8] = p.d_projParams[8];
    }
}

// Comparison functions
bool
EquidistantConicProjection::operator==( const Projection& p ) const
{
    // Check to see if the projection passed in is Equidistant Conic
    if ( EQUIDC == p.getProjectionSystem() )
    {
        const EquidistantConicProjection* pRHS = dynamic_cast<const EquidistantConicProjection*>(&p);
        if ( NULL != pRHS )
        {
            if ( getFirstStandardParallel()  == pRHS->getFirstStandardParallel()  &&
                 getSecondStandardParallel() == pRHS->getSecondStandardParallel() &&
                 getStandardParallel()       == pRHS->getStandardParallel()       &&
                 d_projParams[8]             == pRHS->d_projParams[8] )
            {
                return ConicProjection::operator==( *pRHS );
            }
        }
    }

    return false;
}

// Cloning
Projection*
EquidistantConicProjection::clone() const
{
    return ( new EquidistantConicProjection( *this ) );
}

// String override
string
EquidistantConicProjection::toString() const
{
    string str = "Equidistant Conic Projection\r\n";
    str += ConicProjection::toString();

    if ( 0 == d_projParams[8] )
    {
        str += "STANDARD PARALLEL: ";
        str += packedDMSToString( getStandardParallel(), true );
    }
    else
    {
        str += "FIRST STANDARD PARALLEL: ";
        str += packedDMSToString( getFirstStandardParallel(), true );
        str += "\r\nSECOND STANDARD PARALLEL: ";
        str += packedDMSToString( getSecondStandardParallel(), true );
    }

    return str;
}

bool 
EquidistantConicProjection::checkCoordinateRange( double latitude, double longitude ) const
{
    if ( !Projection::checkCoordinateRange( latitude, longitude ) )
    {
        return false;
    }
    return true;
/*
    double deltaN = ( 90.0 - packedDMSToDouble( getSecondStandardParallel() ) ) / 20.0;
    double deltaS = ( packedDMSToDouble( getFirstStandardParallel() ) + 90.0 ) / 20.0;
    double maxLat = 90.0 - deltaN * deltaN;
    double minLat = -90 + deltaS * deltaS;  
    return ( latitude <= maxLat && latitude >= minLat );
    */
}
