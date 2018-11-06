// UnknownProjection.h: interface for the UnknownProjection class.
//
// Developed by: Mike Childs
//      Started: 4/6/98
//////////////////////////////////////////////////////////////////////

#ifndef _UNKNOWNPROJECTION_H_
#define _UNKNOWNPROJECTION_H_

#include "Projection.h"

class UnknownProjection : public Projection  
{
public:
	UnknownProjection( double left, double bottom, double right, double top );
    UnknownProjection( const UnknownProjection& p );

    // Accessors
    PROJSYS getProjectionSystem() const;
    void getExtents( double& left, double& bottom, double& right, double& top ) const;

    // Modifiers
    void setExtents( double left, double bottom, double right, double top );

    // Projection functions
    bool projectToGeo( double x, double y, 
                       double& latitude, double& longitude ) const;
    bool projectFromGeo( double latitude, double longitude,
                         double& x, double& y ) const;

    // Operator overloads
    bool operator==( const Projection& p ) const;

    // toString override
    virtual string toString() const;

    // clone override
    Projection* clone() const;

protected:
    // Data members
    double d_left, d_bottom, d_right, d_top;
};

inline PROJSYS
UnknownProjection::getProjectionSystem() const
{
    return UNKNOWN_PROJSYS;
}

inline void
UnknownProjection::getExtents( double& left, double& bottom, double& right, double& top ) const
{
    left = d_left;
    bottom = d_bottom;
    right = d_right;
    top = d_top;
}

inline void
UnknownProjection::setExtents( double left, double bottom, double right, double top )
{
    d_left = left;
    d_bottom = bottom;
    d_right = right;
    d_top = top;
}

#endif
