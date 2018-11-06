// ZonedProjection.cpp: implementation of the ZonedProjection class.
//
// Developed by: Mike Childs
//      Started: 1/18/98
//////////////////////////////////////////////////////////////////////

#include "ZonedProjection.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZonedProjection::ZonedProjection( long zone )
{
    setZone( zone );
}

ZonedProjection::ZonedProjection( const ZonedProjection& p )
{
    if ( this != &p )
    {
        d_zone = p.d_zone;
    }
}

ZonedProjection::~ZonedProjection()
{
}
