// CoordinateTransforms.h - header file for CoordinateTransforms class
//
// Developed by: Mike Childs
//      Started: 12/3/96
//

#ifndef _COORDINATE_TRANSFORMS_H_
#define _COORDINATE_TRANSFORMS_H_

#include "StdAfx.h"
#include "GraphicsLib/Rectangle2D.h"
#include "ProjectionLib/Projection.h"

// Forward declarations
class CoordinateMapping;

// Function type declaration
typedef void (PROJ_CHANGED_FUNC)(LPVOID pArg, const Projection* pOldProjection);

class CoordinateTransforms
{
public:
	// Public class-wide (static) member functions
	static PROJSYS getGndRefSys();
	static DATUM   getDatum();
	static CoordinateMapping* getCurrentMapping();
	static void   setCurrentMapping( CoordinateMapping* proj );
	static CRect  GndRefSystoLP( const Rectangle2D& rect );
	static void   GndRefSystoLP( double& x, double& y );
	static double LPtoGndRefSys( double scalar );
	static void   LPtoGndRefSys( double& x, double& y);
	static Rectangle2D LPtoGndRefSys( const CRect& rect );
	static void   GndRefSystoLatLong( double  x,   double  y,
                                    double& lat, double& longitude );
	static CString GndRefSystoLatLong( double x, double y );
	static CString LatLongToString( double lat, double longitude );
	static CString LatToString( double lat );
	static CString LongitudeToString( double longitude );
	static CString projectionToString( PROJSYS proj );

  // Projection functions
  static bool projectPoint( double& x, double& y,
                            const Projection& from,
                            const Projection& to );
  /* Project the point (<x>.<y>) from the projection system <from> to
     the projection system <to> */

  static bool projectToGlobal( double& x, double& y, const Projection& proj );
  /* Projects the point (<x>,<y>) from the projection system <proj>
     to the global projection */

  static bool projectFromGlobal(double& x, double& y, const Projection& proj);
  /* Projects the point (<x>,<y>) from the global projection system to
     the projection system <proj> */

  static void projectRectangleToGlobal( Rectangle2D& rect,
                                        const Projection& proj );
  /* Projects the rectangle <rect> to global projection coordinates from the
     projection specified by <proj>. */

  static void projectRectangleFromGlobal( Rectangle2D& rect,
                                          const Projection& proj );
  /* Projects the rectangle <rect> from global coordinates to the
     projection specified by <proj>. */

  static double calculateGreatCircleDistance( double lat1, double lon1,
                                              double lat2, double lon2 );
  /* Calculates the distance in meters between two points on the earth's
     surface.  The coordinates of the points are given in decimal degrees */

  // Projection accessor
  static const Projection* getProjection();
  /* Returns a const pointer to the global projection currently in use */

  // Projection modifier
  static void setProjection( Projection* pProjection );
  /* This function sets the current global projection to <pProjection>. */

  // Projection callback function
  static void setProjectionChangedFunction(PROJ_CHANGED_FUNC* pProjChangedFunc,
                                           LPVOID pArg );
  /* This method sets the function that will be called whenever the
     global projection is changed.  <pArg> will be passed to that
     function when it is called */

protected:
  // Helper functions
  static void projectRectangle( Rectangle2D& rect, 
                                const Projection& from,
                                const Projection& to );

	// Protected class-wide (static) variables
	static CoordinateMapping* d_currentMapping;
  static Projection*        d_pProjection;
  static PROJ_CHANGED_FUNC* d_pProjChangedFunc;
  static LPVOID             d_pProjChangedFuncArg;
};

inline void
CoordinateTransforms::setProjectionChangedFunction(PROJ_CHANGED_FUNC* pProjChangedFunc,
                                                   LPVOID pArg )
{
  d_pProjChangedFunc = pProjChangedFunc;
  d_pProjChangedFuncArg = pArg;
}

inline void
CoordinateTransforms::setCurrentMapping( CoordinateMapping* pMapping )
{
  d_currentMapping = pMapping;
}

inline const Projection*
CoordinateTransforms::getProjection()
{
  return d_pProjection;
}

inline CoordinateMapping*
CoordinateTransforms::getCurrentMapping()
{
	return d_currentMapping;
}

inline PROJSYS
CoordinateTransforms::getGndRefSys()
{
	return d_pProjection->getProjectionSystem();
}


inline DATUM  
CoordinateTransforms::getDatum()
{
	return d_pProjection->getDatum();
}

#endif