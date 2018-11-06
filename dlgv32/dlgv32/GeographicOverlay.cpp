// GeographicOverlay.cpp - implementation file for GeographicOverlay class
//
// Developed by: Mike Childs
//      Started: 10/22/96
//

#include "StdAfx.h"
#include <malloc.h>
#include "GeographicOverlay.h"
#include "CoordinateTransforms.h"
#include "GeoRegionPoly.h"

#ifdef _WIN32
	using namespace std;
#endif

GeographicOverlay::GeographicOverlay(CString& filename)
: GraphicsObject(), d_filename(filename), d_loaded(FALSE), d_show(TRUE), 
  d_pProjection(NULL), d_bReproject(false), d_globalBoundingRect(0,0,0,0)
{
}

// Destructor
GeographicOverlay::~GeographicOverlay()
{
	removeAllClippingRegions();

  // Reclaim space used by native projection
  delete d_pProjection;

  // Return unused heap space to the operating system
  _heapmin();
}

void GeographicOverlay::showPropertiesDialog()
{
  AfxMessageBox( "No metadata is currently available" );
}

BOOL GeographicOverlay::showOptionsDialog( CDlgv32Doc* pDoc )
{
	return FALSE; // default returns FALSE
}

int GeographicOverlay::pick ( const CRect& pickRect,
          			              CTypedPtrArray< CPtrArray, OverlayComponent* > *oc_list,
			                        int start, const CRect& clientRect, 
                              int maxToPick )
{
	return 0;	// default returns 0
}

CRgn* GeographicOverlay::getCRgn( CDC* pDC )
{
	// Return NULL if no regions are selected
	if ( d_geoRegions.begin() == d_geoRegions.end() )
		return NULL;

	CRgn* rgn = new CRgn;
	CRgn* tempRgn;
	rgn->CreateRectRgn(0, 0, 0, 0);
	vector<GeoRegion*>::iterator i;
	for ( i = d_geoRegions.begin(); i != d_geoRegions.end(); i++ )
	{
		tempRgn = (*i)->toCRgn( pDC );
		if ( i == d_geoRegions.begin() )
		{
			rgn->CopyRgn( tempRgn );
		}
		else
		{
			int combineMode = (*i)->getCombineMode();
			if ( combineMode == RGN_COPY )
			{
				rgn->CopyRgn( tempRgn );
			}
			else
			{
				rgn->CombineRgn( rgn, tempRgn, (*i)->getCombineMode() );
			}
		}
		delete tempRgn;
	}

	return rgn;
}

void GeographicOverlay::removeAllClippingRegions()
{
	// Reclaim space used by GeoRegions
	GeoRegion* rgn;
	for ( vector<GeoRegion*>::iterator i = d_geoRegions.begin(); 
        i != d_geoRegions.end(); i++ )
	{
		rgn = *i;
		delete rgn;
	}

	// Remove all regions from the vector
	d_geoRegions.erase( d_geoRegions.begin(), d_geoRegions.end() );
}

void GeographicOverlay::addGeoRegion( GeoRegion* rgn )
{
	// Remove all of the clipping regions if the combine mode
	// of the new one is copy
	if ( rgn->getCombineMode() == RGN_COPY )
	{
		removeAllClippingRegions();
	}

	// Add the new clipping region
	d_geoRegions.push_back( rgn );
}

Rectangle2D GeographicOverlay::calculateInvalidRect(CDC* pDC, 
                                                    CRect* pClipRect )
{
	// Get the clipping rectangle from the device context unless
	// a clipping rectangle was passed in
	CRect *clipRect;
	if ( pClipRect == NULL )
	{
		clipRect = new CRect();
		pDC->GetClipBox(clipRect);
		clipRect->NormalizeRect();
	}
	else
	{
		clipRect = new CRect( pClipRect );
	}

  // Convert the clipping rectangle to ground ref system coordinates
  Rectangle2D grsClipRect = CoordinateTransforms::LPtoGndRefSys( *clipRect );
	delete clipRect;

	// Find the intersection of the clipping rectangle
	// and the logical bounding rect of the overlay
	Rectangle2D intersectRect;
  if ( getGlobalBoundingRect().isNormalized() )
  {
    intersectRect.intersectRect( grsClipRect, getGlobalBoundingRect() );
  }
  else
  {
    intersectRect = grsClipRect;
  }

	// Find the intersection of the current intersect rect and the
	// overlays clipping region, if it has one
	CRgn* pClipRgn = getCRgn( pDC );
	if ( NULL != pClipRgn )
	{
		// Intersect the clip region with a region the size of
		// the clipping rectangle
		CRgn clipRectRgn;
    CRect lpIntersectRect =
      CoordinateTransforms::GndRefSystoLP( intersectRect );
		clipRectRgn.CreateRectRgnIndirect( &lpIntersectRect );
		pClipRgn->CombineRgn( pClipRgn, &clipRectRgn, RGN_AND );

		// Select the clip region into the DC
		pDC->SelectClipRgn( pClipRgn, RGN_COPY );
		
		// Make the clipping rectangle be the intersection of
		// the clipping rectangle and the region bounding box
		CRect clipRgnRect;
		pClipRgn->GetRgnBox( &clipRgnRect );
		pDC->DPtoLP( &clipRgnRect );
		clipRgnRect.NormalizeRect();
    Rectangle2D grsClipRgnRect = 
      CoordinateTransforms::LPtoGndRefSys( clipRgnRect );
		intersectRect.intersectRect( intersectRect, grsClipRgnRect );

		// Reclaim the space used by the clipping region
		delete pClipRgn;
	}

	intersectRect.normalize();

	// Return the intersection
	return intersectRect;
}

void GeographicOverlay::handleProjectionChanged()
{
  if ( NULL == CoordinateTransforms::getProjection() )
  {
    d_bReproject = false;
    d_globalBoundingRect = getBoundingRect();
    return;
  }

  // Check to see whether or not the native and global projections
  // are the same
  if ( *getNativeProjection() == *CoordinateTransforms::getProjection() )
  {
    d_bReproject = false;
    d_globalBoundingRect = getBoundingRect();
  }
  else
  {
    // Make the geounit and geodatum of the native projection the same as
    // those for the global projection
    const Projection& globalProj = *CoordinateTransforms::getProjection();
    d_pProjection->setGeoDatum( globalProj.getGeoDatum() );
    d_pProjection->setGeoUnit( globalProj.getGeoUnit() );

    // Set the reproject flag
    d_bReproject = true;

    // Calculate the native to global (reverse) projection mesh
    recalculateProjectionMesh( d_reverseProjectionMesh, getBoundingRect(),
                               *getNativeProjection(), globalProj );

    // Calculate the global bounding rectangle
    calculateGlobalBoundingRect();

    // Calculate the global to native (forward) projection mesh
    recalculateProjectionMesh( d_projectionMesh, getGlobalBoundingRect(),
                               globalProj, *getNativeProjection() );
  }

  // TODO: Update the clipping regions to handle new projection
}

void GeographicOverlay::recalculateProjectionMesh( ProjectionMesh& mesh,
                                                   const Rectangle2D& sourceRect,
                                                   const Projection&  sourceProj,
                                                   const Projection&  goalProj  )
{
  ASSERT( d_bReproject );

  // Set the bounds of the projection mesh
  double left, right, bottom, top;
  sourceRect.getPoints( left, bottom, right, top );
  mesh.setSourceMeshBounds( left, bottom, right, top );

  // Set the size of the mesh grid
  short meshWidth, meshHeight;
  getProjectionMeshSize( meshWidth, meshHeight );
  mesh.setMeshSize( meshWidth, meshHeight );

  // Project all the points in the mesh
  mesh.calculateMesh( sourceProj, goalProj );
}

void GeographicOverlay::calculateGlobalBoundingRect()
{
  ASSERT( d_bReproject );

  // Get the bounding coordinates
  double left, right, bottom, top;
  d_reverseProjectionMesh.getProjectedBoundingRect(left, bottom, right, top);

  // Create the bounding rect
  d_globalBoundingRect.setPoints( left, bottom, right, top );

  // Inflate the rectangle to account for intergrid anomalies
  d_globalBoundingRect.inflateRect( d_globalBoundingRect.width() / 100.0,
                                    d_globalBoundingRect.height() / 100.0 );
}

CString GeographicOverlay::getFilenameWithoutPath() const
{
  return d_filename.Right( d_filename.GetLength() -
  		                     d_filename.ReverseFind( '\\' ) - 1 );
}