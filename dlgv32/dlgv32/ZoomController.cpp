// ZoomController.cpp - implementation for ZoomController class
//
// Developed by: Mike Childs
//      Started: 10/24/96
//

#include "StdAfx.h"
#include "ZoomController.h"
#include "Dlgv32Doc.h"
#include "Dlgv32View.h"
#include "CoordinateTransforms.h"
#include "resource.h"
#include "GraphicsLib\CoordinateMapping.h"

ZoomController::ZoomController( CDlgv32View* ptrView )
: Controller( ptrView ),
  d_pDragRect(0), d_dragging(FALSE), d_drawingRect(FALSE)
{
	d_hCursor = AfxGetApp()->LoadCursor( IDC_ZOOM_CURSOR );
}

ZoomController::~ZoomController()
{
	// Deallocate storage for drag rectangle
	delete d_pDragRect;
}

void ZoomController::OnLButtonDown( UINT nFlags, CPoint point )
{
	// Call the parent classes version
	Controller::OnLButtonDown( nFlags, point );

	// Reset the controller
	reset();

	// Set the dragging flag
	d_dragging = TRUE;

	// Set the start point to the point clicked
	d_startPoint = point;
}

void ZoomController::OnMouseMove( UINT nFlags, CPoint point )
{
	// Call the parent classes version
	Controller::OnLButtonDown( nFlags, point );
	
	// If the left mouse button isn't down, do nothing
	if ( ! d_dragging )
	{
		return;
	}
	
	// Create a rectangle between the starting point and the current point
	CRect currentDragRect( d_startPoint, point );
	currentDragRect.NormalizeRect();
	
	// Get a device context from the view
	CClientDC dc( getView() );
	getView()->OnPrepareDC( &dc );

  // Starting drawing a rectangle if either the height or the width
  // of the rectangle around the current point and the start point is
	// greater than 3 pixels
	if ( ( currentDragRect.Height() > 4 && currentDragRect.Width() > 1 ) ||
	     ( currentDragRect.Height() > 1 && currentDragRect.Width() > 4 ) )
	{
		d_drawingRect = TRUE;

    // Set the drag rectangle to the current drag rectangle and
    // erase the last drag rectangle if there was one
    if ( NULL == d_pDragRect )
    { 
	    d_pDragRect = new DragRectangle( currentDragRect );
    }
    else
    {
	    d_pDragRect->erase( &dc );
	    d_pDragRect->setRect( currentDragRect );
    }

    // Draw the drag rectangle
    d_pDragRect->draw( &dc );
  }
  else
  {
    // The rectangle is too small, erase the old one if there is one and
    // set the drawing rect flag
    d_drawingRect = FALSE;

	  if ( NULL != d_pDragRect )
	  { 
		  d_pDragRect->erase( &dc );
      delete d_pDragRect;
      d_pDragRect = NULL;
	  }
  }
}

void ZoomController::OnLButtonUp( UINT nFlags, CPoint point )
{
	// Get the view's document
	CDlgv32Doc* doc;
	doc = getView()->GetDocument();

	// Get a device context from the view
	CClientDC dc( getView() );
	getView()->OnPrepareDC( &dc );

	// If drawing a rectangle, zoom into that rectangle
	if ( d_drawingRect )
	{
		// Erase the drag rectangle
		d_pDragRect->erase( &dc );

		// Get the client rectangle from the view
		CRect clientRect;
		getView()->GetClientRect( &clientRect );
		clientRect.NormalizeRect();

		// Create a rectangle from the current point and the start point
		CRect dragRect( point, d_startPoint );
		dragRect.NormalizeRect();

		// Calculate the factor to zoom by
		double width_zoom, height_zoom, zoom;
		width_zoom  = clientRect.Width()  / dragRect.Width();
		height_zoom = clientRect.Height() / dragRect.Height();
		zoom = ( width_zoom < height_zoom ) ? width_zoom : height_zoom;

		// Convert the drag rectangle to GndRefSys coordinates
		dc.DPtoLP( &dragRect );
		Rectangle2D GndRefSys_DragRect = 
      CoordinateTransforms::LPtoGndRefSys( dragRect );

		// Change the projection object to use drag rectangle
		double x1, y1, x2, y2;
		GndRefSys_DragRect.getPoints( x1, y1, x2, y2 );
		CoordinateTransforms::getCurrentMapping()->setWindowExtents( x1, y1,
                                                                 x2, y2 );

		// Center on the center of the rectangle
		double cen_x, cen_y;
		cen_x = ( x1 + x2 ) / 2;
		cen_y = ( y1 + y2 ) / 2;
		CoordinateTransforms::getCurrentMapping()->pan( cen_x, cen_y );

	}
	else
	{
		// Convert point from device coordinates to GndRefSys
		double x, y;
		dc.DPtoLP( &point );
		x = point.x;
		y = point.y;
		CoordinateTransforms::LPtoGndRefSys( x, y );
	
		// Zoom in by a factor of 2 and center on point clicked
		CoordinateTransforms::getCurrentMapping()->zoomTo( 2.0, x, y );
	}

	// Redraw the client area
	getView()->Invalidate();

		// Reset values of dragging flags
	d_dragging = d_drawingRect = FALSE;

	return;
}

void ZoomController::OnRButtonDown( UINT nFlags, CPoint point )
{
	// Call base class version of overloaded function
	Controller::OnRButtonDown( nFlags, point );

	// Reset the controller
	reset();

	// Get the document from the view
	CDlgv32Doc* doc;
	doc = getView()->GetDocument();

	// Convert point from device coordinates to GndRefSys
	double x, y;
	CClientDC dc( getView() );
	getView()->OnPrepareDC( &dc );
	dc.DPtoLP( &point );
	x = point.x;
	y = point.y;
	CoordinateTransforms::LPtoGndRefSys( x, y );
	
	// Zoom out by a factor of two and center on point clicked
	CoordinateTransforms::getCurrentMapping()->zoomTo( -2.0, x, y );

	// Redraw the client area
	getView()->Invalidate();
}

void ZoomController::cleanup()
{
	// Call the parent class' version
	Controller::cleanup();

	// Reset the controller
	reset();

	return;
}

void ZoomController::reset()
{
	// Call the parent class' version
	Controller::reset();

	// Get a device context from the view
	CClientDC dc( getView() );
	getView()->OnPrepareDC( &dc );

	// Erase the last rectangle if you were drawing one
	if ( d_drawingRect )
	{
		d_pDragRect->erase( &dc );
	}		

	// Reset the value of the member variables
	d_dragging = d_drawingRect = FALSE;
	delete d_pDragRect;
	d_pDragRect = 0;

	return;
}

void ZoomController::erase()
{
	// Get a device context from the view
	CClientDC dc( getView() );
	getView()->OnPrepareDC( &dc );

	// Erase the last rectangle if you were drawing one
	if ( d_drawingRect )
	{
		d_pDragRect->erase( &dc );
	}		
}