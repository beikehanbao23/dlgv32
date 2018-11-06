// AlbersConicProjection.cpp: implementation of the AlbersConicProjection class.
//
// Developed by: Mike Childs
//      Started: 1/24/98
//////////////////////////////////////////////////////////////////////

#include "AlbersConicProjection.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AlbersConicProjection::AlbersConicProjection( double stdpr1, double stdpr2, 
                                              double sMajor, 
                                              double sMinor, double centMer,
                                              double originLat,
                                              double fe, double fn, DATUM d,
                                              UNIT u,
                                              DATUM geoDatum, UNIT geoUnit )
: ConicProjection( sMajor, sMinor, centMer, originLat, fe, fn, d, u, geoDatum,
                   geoUnit )
{
  setFirstStandardParallel( stdpr1 );
  setSecondStandardParallel( stdpr2 );
}

AlbersConicProjection::AlbersConicProjection( const AlbersConicProjection& p )
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
AlbersConicProjection::operator==( const Projection& p ) const
{
  // Check to see if the projection passed in is Albers Conic
  if ( ALBERS == p.getProjectionSystem() )
  {
    const AlbersConicProjection* pRHS = 
      dynamic_cast<const AlbersConicProjection*>(&p);
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
AlbersConicProjection::clone() const
{
  return ( new AlbersConicProjection( *this ) );
}

// String override
string
AlbersConicProjection::toString() const
{
  string str = "Albers Conic Projection\r\n";
  str += ConicProjection::toString();
  str += "\r\nFIRST STANDARD PARALLEL: ";
  str += packedDMSToString( getFirstStandardParallel(), true );
  str += "\r\nSECOND STANDARD PARALLEL: ";
  str += packedDMSToString( getSecondStandardParallel(), true );

  return str;
}

bool 
AlbersConicProjection::checkCoordinateRange( double latitude, 
                                             double longitude ) const
{
  if ( !Projection::checkCoordinateRange( latitude, longitude ) )
  {
    return false;
  }

  double deltaN = ( 90.0 - packedDMSToDouble( getSecondStandardParallel() ) ) 
                    / 20.0;
  double deltaS = ( packedDMSToDouble( getFirstStandardParallel() ) + 90.0 )
                    / 20.0;
  double maxLat = 90.0 - deltaN * deltaN;
  double minLat = -90 + deltaS * deltaS;
  return ( latitude <= maxLat && latitude >= minLat );
}
