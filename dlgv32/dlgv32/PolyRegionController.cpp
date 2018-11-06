// PolyRegionController.cpp - implementation file for PolyRegionController class
//
// Developed by: Mike Childs
//      Started: 2/28/97
//

#include "PolyRegionController.h"
#include "CoordinateTransforms.h"
#include "GeoRegionPoly.h"
#include "GeographicOverlay.h"
#include "Dlgv32Doc.h"
#include "OverlaySelector.h"
#include "GraphicsLib/Point2D.h"

PolyRegionController::PolyRegionController( CDlgv32View* ptrView )
: Controller(ptrView), d_dragging(FALSE), d_numPoints(0), d_erased(FALSE)
{
	d_hCursor = AfxGetApp()->LoadCursor( IDC_POLY_SELECTOR_CURSOR );
}

void PolyRegionController::OnLButtonDown( UINT nFlags, CPoint point )
{
	// Call the parent classes version
	Controller::OnLButtonDown( nFlags, point );

	// Get a DC from the view
	CClientDC dc( getView() );
	getView()->OnPrepareDC( &dc );

	// Convert <point> to GndRefSys coordinates
	dc.DPtoLP( &point );
	double x(point.x), y(point.y);
	CoordinateTransforms::LPtoGndRefSys( x, y );

	// Erase the last rubber band line unless this is
	// the first point
	if ( d_numPoints > 0 )
	{
		d_line.erase( &dc );
	}
	
	// Add the new point to the array of points
	d_points.SetAtGrow( d_numPoints, Point2D( x, y ) );

	// Increment the number of points
	d_numPoints++;

	// Draw the points needed to be redrawn
	draw( d_erased );

	// Set the starting point for the rubber band line
	d_line.setStartPoint( x, y );

	// Set dragging flag
	d_dragging = TRUE;

	// Reset starting new segment flag
	d_newSegment = TRUE;
}

void PolyRegionController::OnRButtonDown( UINT nFlags, CPoint point )
{
	// Apply the region if it is valid
	if ( d_numPoints >= 3 )
	{
		// Get a pointer to the document
		CDlgv32Doc* pDoc = getView()->GetDocument();

		// Check to make sure points aren't collinear
		if ( ptsCollinear() )
		{
			AfxMessageBox( "The points you have specified are collinear" );
			reset();
			return;
		}

		// Get a list of the loaded overlays from the document
    OverlayFactory& overlays = pDoc->getOverlayFactory();

		// Determine which overlays to apply the region to
		OverlaySelector dlg;
		dlg.setOverlays( overlays.getOverlays() );
		dlg.d_combineMode = 0;	// Default is OR
		
		if ( dlg.DoModal() == IDOK )
		{
			// Get the selected overlays
			int numSelected;
			int* pSelected;
			dlg.getSelected( pSelected, numSelected );

			// Get the combine mode
			int combineMode;
			switch ( dlg.d_combineMode )
			{
				case 0:	// RGN_OR
					combineMode = RGN_OR;
					break;
				case 1: // RGN_AND
					combineMode = RGN_AND;
					break;
				case 2: // RGN_COPY
					combineMode = RGN_COPY;
					break;
				case 3: // RGN_DIFF
					combineMode = RGN_DIFF;
					break;
				case 4: // RGN_XOR
					combineMode = RGN_XOR;
					break;
				default:
					combineMode = RGN_OR;
					break;
			}

			// Create an array of the polygon points
			Point2D* points = new Point2D[d_numPoints];
			for ( int i = 0; i < d_numPoints; i++ )
			{
				points[i] = d_points[i];
			}

			if ( numSelected > 0 )
			{
				// Apply the region to the selected overlays
				GeoRegionPoly* rgn;
				for ( int i = 0; i < numSelected; i++ )
				{
					rgn = new GeoRegionPoly( points, d_numPoints );
					rgn->setCombineMode( combineMode );
					overlays.getOverlay( pSelected[i] )->addGeoRegion( rgn );
				}

				// Redraw all of the overlays
				getView()->Invalidate();
			}
			delete[] points;
		}
	}
	else
	{
		AfxMessageBox( "At least three points must be specified" );
	}

	// Reset the controller
	reset();
}

void PolyRegionController::OnMouseMove( UINT nFlags, CPoint point )
{
	// Do nothing if not dragging
	if ( !d_dragging )
	{
		return;
	}

	// Get a device context from the view
	CClientDC dc( getView() );
	getView()->OnPrepareDC( &dc );

	// Convert the point to GndRefSys coordinates
	dc.DPtoLP( &point );
	double x(point.x), y(point.y);
	CoordinateTransforms::LPtoGndRefSys( x, y );

	// If everything is erased redraw it all
	if ( d_erased )
	{
		draw( TRUE );
	}
	
	// Erase the last rubber band line if this isn't the
	// start of a new segment
	if ( !d_newSegment )
	{
		d_line.erase( &dc );
	}
	else
	{
		d_newSegment = FALSE;
	}

	// Set the end point of the rubber band line
	d_line.setEndPoint( x, y );

	// Draw the new rubber band line
	d_line.draw( &dc );	
}

void PolyRegionController::cleanup()
{
	// Call the parent class' version
	Controller::cleanup();

	// Erase the lines
	erase();

	CClientDC dc( getView() );
	getView()->OnPrepareDC( &dc );
	
	// Erase the rubber band line
	d_line.erase( &dc );
}

void PolyRegionController::reset()
{
	// Call the parent class' version
	Controller::reset();

	// Cleanup the controller
	cleanup();

	// Reset the number of points to zero
	d_numPoints = 0;
	
	// Reset the dragging flag
	d_dragging = FALSE;

	// Remove all of the elements from the point array
	d_points.RemoveAll();
}

void PolyRegionController::erase()
{
	// Do nothing if everything has already been erased
	if ( d_erased )
	{
		return;
	}

	// Get a DC from the view
	CClientDC dc( getView() );
	getView()->OnPrepareDC( &dc );

	// Draw over all the lines
	draw( TRUE );

	// Erase the rubber band line
	d_line.erase( &dc );
}

void PolyRegionController::draw( BOOL drawAll )
{
	// Do nothing if there aren't at least two points
	if ( d_numPoints < 2 )
	{
		return;
	}

	// Get a DC from the view
	CClientDC dc( getView() );
	getView()->OnPrepareDC( &dc );
	
	UINT startPoint;
	if ( drawAll )
	{
		startPoint = 0;
		d_erased = !d_erased; // Flip erased flag
	}
	else
	{
		startPoint = d_numPoints - 2;
	}

	// Create a CPoint array to hold the polyline to be drawn
	CPoint *pts = new CPoint[d_numPoints - startPoint];

	// Fill the pts array
	double x, y;
	for ( int i = startPoint; i < d_numPoints; i++ )
	{
		// Get the GndRefSys points
		d_points[i].getXY( x, y );

		// Convert it to logical coordinates
		CoordinateTransforms::GndRefSystoLP( x, y );
		pts[i - startPoint] = CPoint( x, y );
	}

	// Set the drawing mode to NOT
	int oldROP2 = dc.SetROP2( R2_NOT );

	// Draw the polyline
	dc.Polyline( pts, d_numPoints - startPoint );

	// Restore the DC to its previous setting
	dc.SetROP2( oldROP2 );

	// Reclaim memory used by polyline points
	delete[] pts;
}

BOOL PolyRegionController::ptsCollinear()
{
	if ( d_numPoints < 3 )
		return TRUE;

	double m, m1, dy, dx;
	BOOL fVert = FALSE;
	dy = d_points[1].getY() - d_points[0].getY();
	dx = d_points[1].getX() - d_points[0].getX();
	if ( dx == 0.0 )
	{
		fVert = TRUE;
	}
	else
	{
		m  = dy / dx;
	}

	for ( int i = 2; i < d_numPoints; i++ )
	{
		dy = d_points[i].getY() - d_points[i-1].getY();
		dx = d_points[i].getX() - d_points[i-1].getX();
		if ( fVert )
		{
			if ( dx != 0.0 )
				return FALSE;
		}
		else
		{
			if ( dx == 0.0 )
				return FALSE;
			m1 = dy / dx;
			if ( m1 != m )
				return FALSE;
		}
	}

	return TRUE;
}
