// EquidistantConicProjection.h: interface for the EquidistantConicProjection 
// class.
//
// Developed by: Mike Childs
//      Started: 4/6/98
//////////////////////////////////////////////////////////////////////

#ifndef _EQUIDISTANTCONICPROJECTION_H_
#define _EQUIDISTANTCONICPROJECTION_H_

#include "ConicProjection.h"

class EquidistantConicProjection : public ConicProjection  
{
public:
  // Equidistant Conic A Constructor
  EquidistantConicProjection( double stdpar, double sMajor, double sMinor, 
                              double centMer, double originLat,
                              double fe, double fn, 
                              DATUM d, UNIT u,
                              DATUM geoDatum = DEFAULT_DATUM,
                              UNIT geoUnit = ARC_DEGREES );

  // Equidistant Conic B Constructor
	EquidistantConicProjection( double stdpr1, double stdpr2, 
                              double sMajor, double sMinor, 
                              double centMer, double originLat,
                              double fe, double fn, 
                              DATUM d, UNIT u,
                              DATUM geoDatum = DEFAULT_DATUM,
                              UNIT geoUnit = ARC_DEGREES );
  EquidistantConicProjection( const EquidistantConicProjection& p );

  // Accessors

  PROJSYS getProjectionSystem() const;
    /* Returns the projection system (Equidistant) */

  double getFirstStandardParallel() const;
    /* Returns the latitude of the 1st standard parallel (type B projection).
       The angle is returned in packed degrees/minutes/seconds
       format (DDDMMMSSS.SS) */

  double getSecondStandardParallel() const;
    /* Returns the latitude of the 2nd standard parallel (type B projection).
       The angle is returned in packed degrees/minutes/seconds
       format (DDDMMMSSS.SS) */

  double getStandardParallel() const;
    /* Returns the latitude of the standard parallel (type A projection).
       The angle is returned in packed degrees/minutes/seconds
       format (DDDMMMSSS.SS) */

  // Modifiers

  void setFirstStandardParallel( double stdpr1 );
    /* Sets the latitude of the 1st standard parallel (type B projection).
       The angle should be entered in packed degrees/minutes/seconds
       format (DDDMMMSSS.SS) */

  void setSecondStandardParallel( double stdpr2 );
    /* Sets the latitude of the 2nd standard parallel (type B projection).
       The angle should be entered in packed degrees/minutes/seconds
       format (DDDMMMSSS.SS) */

  virtual void setStandardParallel( double stdpar );
    /* Sets the latitude of the standard parallel (type A projection).
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
EquidistantConicProjection::getProjectionSystem() const
{
  return EQUIDC;
}

inline double 
EquidistantConicProjection::getFirstStandardParallel() const
{
  return d_projParams[2];
}

inline double 
EquidistantConicProjection::getSecondStandardParallel() const
{
  return d_projParams[3];
}

inline double
EquidistantConicProjection::getStandardParallel() const
{
  return d_projParams[2];
}

inline void 
EquidistantConicProjection::setFirstStandardParallel( double stdpr1 )
{
  d_projParams[2] = stdpr1;
}

inline void 
EquidistantConicProjection::setSecondStandardParallel( double stdpr2 )
{
  d_projParams[3] = stdpr2;
}

inline void
EquidistantConicProjection::setStandardParallel( double stdpar )
{
  d_projParams[2] = stdpar;
}

#endif
