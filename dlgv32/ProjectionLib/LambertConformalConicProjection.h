// LambertConformalConicProjection.h: interface for the LambertConformalConicProjection class.
//
// Developed by: Mike Childs
//      Started: 1/24/98
//////////////////////////////////////////////////////////////////////

#ifndef _LAMBERTCONFORMALCONICPROJECTION_H_
#define _LAMBERTCONFORMALCONICPROJECTION_H_

#include "ConicProjection.h"

class LambertConformalConicProjection : public ConicProjection  
{
public:
    // Constructors/Destructors
	LambertConformalConicProjection( double stdpr1, double stdpr2, 
                                     double sMajor, double sMinor, 
                                     double centMer, double originLat,
                                     double fe, double fn, DATUM d, UNIT u,
                                     DATUM geoDatum = DEFAULT_DATUM, UNIT geoUnit = ARC_DEGREES );
    LambertConformalConicProjection( const LambertConformalConicProjection& p );

    // Accessors

    PROJSYS getProjectionSystem() const;
        /* Returns the projection system (LAMCC) */

    double getFirstStandardParallel() const;
        /* Returns the latitude of the 1st standard parallel.
           The angle is returned in packed degrees/minutes/seconds
           format (DDDMMMSSS.SS) */

    double getSecondStandardParallel() const;
        /* Returns the latitude of the 2nd standard parallel 
           The angle is returned in packed degrees/minutes/seconds
           format (DDDMMMSSS.SS) */

    // Modifiers

    virtual void setFirstStandardParallel( double stdpr1 );
        /* Sets the latitude of the 1st standard parallel.  Subclasses may
           override this to provide additional error checking. 
           The angle should be entered in packed degrees/minutes/seconds
           format (DDDMMMSSS.SS) */

    virtual void setSecondStandardParallel( double stdpr2 );
        /* Sets the latitude of the 2nd standard parallel.  Subclasses may
           override this to provide additional error checking. 
           The angle should be entered in packed degrees/minutes/seconds
           format (DDDMMMSSS.SS) */

    // Operator overloads
    bool operator==( const Projection& p ) const;

    // String override
    string toString() const;

    // Cloning
    Projection* clone() const;

protected:
    // Overrides
    bool checkCoordinateRange( double latitude, double longitude ) const;
};

inline PROJSYS 
LambertConformalConicProjection::getProjectionSystem() const
{
    return LAMCC;
}

inline double 
LambertConformalConicProjection::getFirstStandardParallel() const
{
    return d_projParams[2];
}

inline double 
LambertConformalConicProjection::getSecondStandardParallel() const
{
    return d_projParams[3];
}

inline void 
LambertConformalConicProjection::setFirstStandardParallel( double stdpr1 )
{
    d_projParams[2] = stdpr1;
}

inline void 
LambertConformalConicProjection::setSecondStandardParallel( double stdpr2 )
{
    d_projParams[3] = stdpr2;
}

#endif
