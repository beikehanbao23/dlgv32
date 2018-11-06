// GeographicOverlay.h - header file for GeographicOverlay class
//
// Developed by: Mike Childs
//      Started: 10/18/96
//

#ifndef _GEOGRAPHICOVERLAY_H_
#define _GEOGRAPHICOVERLAY_H_

#include "StdAfx.h"
#include "GraphicsObject.h"
#include "CoordinateTransforms.h"
#include "GeoRegion.h"
#include "ProjectionMesh.h"
#include <vector>
using namespace std;

// Forward declarations
class CDlgv32Doc;
class OverlayComponent;
class Projection;

// GeographicOverlay class:
//		This class is an abstract base class which provides the basic
//		interface of a self-drawing overlay, such as a DLG or a DRG.  All
//		objects derived from this class are responsible for drawing themselves
//		when their draw method is invoked.
class GeographicOverlay : public GraphicsObject
{
public:
	// Construction
	GeographicOverlay( CString& filename );

	// Virtual Destructor
	virtual ~GeographicOverlay();

	// Polymorphic public member functions
	virtual void draw( CDC* pDC, CRect* pClipRect = NULL ) = 0;
	virtual void calculateBoundingRect() = 0;

  virtual CString getDescription() const;
  /* Returns a string description of the overlay.  Default is the filename */

  virtual void handleProjectionChanged();
  /* This method is called whenever the global projection has changed.
     Subclasses which require more than the base functionality should
     override this method. */

	virtual BOOL load();
	virtual BOOL showOptionsDialog( CDlgv32Doc* pDoc = NULL );
	virtual void showPropertiesDialog();
	virtual int  pick( const CRect& pickRect,
  		               CTypedPtrArray< CPtrArray, OverlayComponent* > *oc_list,
	    		           int start, const CRect& clientRect, int maxToPick = -1 );
  virtual bool getBrowseText( const CRect& pickRect, const CRect& clientRect,
                              CString& strBrowse ) const;

	// Non-polymorphic public member functions
	const CString& getFilename() const;
	void setFilename( CString& filename );
	BOOL getShow() const;
	void setShow( BOOL show );
	void addGeoRegion( GeoRegion* rgn );
	CRgn* getCRgn( CDC* pDC );
	void removeAllClippingRegions();
    
  const Projection* getNativeProjection() const;
  /* Returns a pointer to the projection native to this overlay */

  const Rectangle2D& getGlobalBoundingRect() const;
  /* Returns the bounding rectangle for the overlay in the coordinate
     system of the global space */

  // Fast reproject functions
  bool projectGlobalToNative( double& x, double& y ) const;
  bool projectNativeToGlobal( double& x, double& y ) const;

protected:
	// Polymorphic helper functions
	virtual Rectangle2D calculateInvalidRect( CDC* pDC, CRect* pClipRect );
  virtual void getProjectionMeshSize( short& width, short& height ) const;

  // Helper functions
  CString getFilenameWithoutPath() const;

	// Protected data members
  bool        d_bReproject;
  Projection* d_pProjection;
	CString d_filename;
	BOOL d_loaded;
	BOOL d_show;
	vector<GeoRegion*> d_geoRegions;

private:
  // Global bounding rectangle
  void calculateGlobalBoundingRect();
  Rectangle2D d_globalBoundingRect;

  // Projection mesh methods and member data
  void recalculateProjectionMesh( ProjectionMesh& mesh,
                                  const Rectangle2D& sourceRect,
                                  const Projection&  sourceProj,
                                  const Projection&  goalProj);
  ProjectionMesh d_projectionMesh;
  ProjectionMesh d_reverseProjectionMesh;
};

inline const Rectangle2D& GeographicOverlay::getGlobalBoundingRect() const
{
  return d_globalBoundingRect;
}

inline const Projection* GeographicOverlay::getNativeProjection() const
{
  return d_pProjection;
}

inline CString GeographicOverlay::getDescription() const
{
  return getFilename();
}

inline const CString& GeographicOverlay::getFilename() const
{
	return d_filename;
}

inline void GeographicOverlay::setFilename( CString& filename )
{
	d_filename = filename;
}

inline BOOL GeographicOverlay::load()
{
	d_loaded = TRUE;
	return TRUE;
}

inline BOOL GeographicOverlay::getShow() const
{
	return d_show;
}

inline void GeographicOverlay::setShow( BOOL show )
{
	d_show = show;
}

inline bool GeographicOverlay::getBrowseText(const CRect& pickRect, 
                                             const CRect& clientRect,
                                             CString& strBrowse ) const
{
  return false;
}

inline bool GeographicOverlay::projectGlobalToNative( double& x, double& y )
  const
{
  if ( !d_bReproject )
  {
    return true;
  }

  double xCopy = x;
  double yCopy = y;
  if ( !d_projectionMesh.projectPoint( x, y ) )
  {
    // Try the slow way
    if ( !CoordinateTransforms::projectFromGlobal( xCopy, yCopy, 
                                                   *getNativeProjection() ) )
    {
      return false;
    }

    x = xCopy;
    y = yCopy;
  }

  return true;
}

inline bool GeographicOverlay::projectNativeToGlobal( double& x, double& y )
  const
{
  if ( !d_bReproject )
  {
    return true;
  }

  double xCopy = x;
  double yCopy = y;
  if ( !d_reverseProjectionMesh.projectPoint( x, y ) )
  {
    // Try the slow way
    if ( !CoordinateTransforms::projectToGlobal( xCopy, yCopy,
                                                 *getNativeProjection() ) )
    {
      return false;
    }

    x = xCopy;
    y = yCopy;
  }

  return true;
}

inline void GeographicOverlay::getProjectionMeshSize(short& width, 
                                                     short& height ) const
{
  width = 16;
  height = 16;
}

#endif