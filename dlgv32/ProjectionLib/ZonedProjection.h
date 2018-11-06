// ZonedProjection.h: interface for the ZonedProjection class.
//
// Developed by: Mike Childs
//      Started: 1/17/98
//////////////////////////////////////////////////////////////////////

#ifndef _ZONEDPROJECTION_H_
#define _ZONEDPROJECTION_H_

class ZonedProjection  
{
public:
	ZonedProjection( long zone );
    ZonedProjection( const ZonedProjection& p );
	virtual ~ZonedProjection();

    // Accessors
    long getZone() const;

    // Modifiers
    virtual void setZone( long zone );
        /* Sets the zone for the projection.  This function can be
           overriden in derived classes to provide additional error
           checking */

private:
    // Data members
    long d_zone;
};

inline long
ZonedProjection::getZone() const
{
    return d_zone;
}

inline void
ZonedProjection::setZone( long zone )
{
    d_zone = zone;
}

#endif