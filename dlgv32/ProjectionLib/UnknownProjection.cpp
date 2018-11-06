// UnknownProjection.cpp: implementation of the UnknownProjection class.
//
// Developed by: Mike Childs
//      Started: 4/6/98
//////////////////////////////////////////////////////////////////////

#include "UnknownProjection.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

UnknownProjection::UnknownProjection( double left, double bottom, double right, double top )
: Projection(UNKNOWN_DATUM, UNKNOWN_UNIT, UNKNOWN_DATUM, ARC_DEGREES)
{
    setExtents( left, bottom, right, top );
}

UnknownProjection::UnknownProjection( const UnknownProjection& p )
: Projection(p)
{
    if ( this != &p )
    {
        d_left = p.d_left;
        d_bottom = p.d_bottom;
        d_right = p.d_right;
        d_top = p.d_top;
    }
}

// Comparison functions
bool 
UnknownProjection::operator==( const Projection& p ) const
{
    const UnknownProjection* pRHS = dynamic_cast<const UnknownProjection*>(&p);
    if ( NULL != pRHS )
    {
        if ( d_left   == pRHS->d_left   &&
             d_bottom == pRHS->d_bottom &&
             d_right  == pRHS->d_right  &&
             d_top    == pRHS->d_top )
        {
            return Projection::operator==( p );
        }
    }

    return false;
}

// toString override
string
UnknownProjection::toString() const
{
    return "Unknown Projection";
}

// Projection functions
bool
UnknownProjection::projectToGeo( double x, double y, 
                               double& latitude, double& longitude ) const
{
    // Scale the x between -180 and 180 and the y between -90 and 90
    double hRatio = ( x - d_left ) / ( d_right - d_left );
    double vRatio = ( y - d_bottom ) / ( d_top - d_bottom );
    if ( hRatio < 0.0 || vRatio < 0.0 || hRatio > 1.0 || vRatio > 1.0 )
    {
        return false;
    }

    longitude = 360.0 * hRatio - 180.0;
    latitude = 180 * vRatio - 90.0;
    return true;
}

bool 
UnknownProjection::projectFromGeo( double latitude, double longitude,
                                 double& x, double& y ) const
{
    double hRatio = ( longitude + 180.0 ) / 360.0;
    double vRatio = ( latitude + 90.0 ) / 180.0;
    if ( hRatio < 0.0 || vRatio < 0.0 || hRatio > 1.0 || vRatio > 1.0 )
    {
        return false;
    }

    x = ( d_right - d_left ) * hRatio + d_left;
    y = ( d_top - d_bottom ) * vRatio + d_bottom;
    return true;
}

Projection*
UnknownProjection::clone() const
{
    return ( new UnknownProjection( *this ) );
}