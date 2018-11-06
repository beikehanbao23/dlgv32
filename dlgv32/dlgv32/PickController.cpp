// PickController.cpp - implementation file for PickController class
//
// Developed by: Mike Childs
//      Started: 11/15/96
//

#include "PickController.h"
#include "Dlgv32Doc.h"
#include "Dlgv32View.h"
#include "CoordinateTransforms.h"
#include "OverlayComponent.h"
#include "Mainfrm.h"

PickController::PickController( CDlgv32View* ptrView )
	: Controller( ptrView ),
	  d_numPicked(-1), // no objects are initially picked
	  d_pDragRect(0),
	  d_dragging(FALSE),
	  d_drawingRect(FALSE),
	  d_lastMousePos(0,0),
	  PICK_APERTURE(25)	// pick aperture 25 pixels wide
{
}

PickController::~PickController()
{
	// Deallocate storage for drag rectangle
	delete d_pDragRect;
	
	// Empty the list of selected GraphicsObjects
	d_pickList.RemoveAll();
	d_pickList.FreeExtra();
}

void PickController::OnLButtonDown( UINT nFlags, CPoint point )
{
	// Call the parent classes version
	Controller::OnLButtonDown( nFlags, point );
	
	// Reset the list of GraphicsObjects
	reset();

	// Set the dragging flag
	d_dragging = TRUE;

	// Set the start point to the point clicked
	d_startPoint = point;
}

void PickController::OnMouseMove( UINT nFlags, CPoint point )
{
	// Call the parent classes version
	Controller::OnLButtonDown( nFlags, point );

	// Set the last mouse position
	d_lastMousePos = point;

	// Abort if not dragging
	if ( !d_dragging )
	{
		return;
	}

	// Create a rectangle between the starting point and the current point
	CRect currentDragRect( d_startPoint, point );
	currentDragRect.NormalizeRect();
	
	if ( ! d_drawingRect )
	{
		// Starting drawing a rectangle if either the height of the width
		// of the rectangle around the current point and the start point is
		// greater than 5 pixels
		if ( ( currentDragRect.Height() > 5 && currentDragRect.Width() > 3 ) ||
		     ( currentDragRect.Height() > 3 && currentDragRect.Width() > 5 ) )
		{
			d_drawingRect = TRUE;
		}
		// Don't draw a rectangle if the users hasn't moved the mouse very
		// far from the start point
		else
		{
			return;
		}
	}

	// Get a device context from the view
	CClientDC dc( getView() );
	getView()->OnPrepareDC( &dc );

	// Create logical version of current drag rectangle
	dc.DPtoLP( &currentDragRect );
	currentDragRect.NormalizeRect();

	// Set the drag rectangle to the current drag rectangle and
	// erase the last drag rectangle if there was one
	if ( d_pDragRect == 0 )
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

	return;
}

void PickController::OnLButtonUp( UINT nFlags, CPoint point )
{
	// Get the view's document
	CDlgv32Doc* doc;
	doc = getView()->GetDocument();

	// Get a device context from the view
	CClientDC dc( getView() );
	getView()->OnPrepareDC( &dc );

	// Erase the last drawn drag rectangle if you were drawing one
	if ( d_drawingRect )
	{
		d_pDragRect->erase( &dc );
	}        

	// Convert the current point from device coordinates to logical coordinates
	dc.DPtoLP( &point );

	// Convert the starting point from device coordinates to logical coordinates
	dc.DPtoLP( &d_startPoint );

	// Get the client rectangle from the view
	CRect clientRect;
	getView()->GetClientRect( &clientRect );

	// Convert the client rectangle to logical coordinates
	dc.DPtoLP( &clientRect );
	clientRect.NormalizeRect();
	
	// Setup the pick rectangle
	CRect pickRect;		// This is the pick rectangle in logical coordinates
	if ( d_drawingRect )
	{
		pickRect = CRect( d_startPoint, point );
	}
	else
	{
		pickRect = CRect( point.x - PICK_APERTURE, point.y + PICK_APERTURE,
  			              point.x + PICK_APERTURE, point.y - PICK_APERTURE );
	}
	
	// Normalize the pick rectangle
	pickRect.NormalizeRect();
	
	// Tell the document to pick from the current pick rectangle
	d_numPicked = doc->pick( pickRect, &d_pickList, 0, clientRect );

	if ( d_numPicked > 0 )
	{
		// Highlight the first GraphicsObject picked if any were selected
		d_pickList[0]->highlight( TRUE );

		// Redraw the pick rectangle
		CRect curBoundingRect;
		curBoundingRect =
      CoordinateTransforms::GndRefSystoLP( d_pickList[0]->getBoundingRect());
		CRect invalidRect;
		invalidRect.UnionRect( &curBoundingRect, &pickRect );
		dc.LPtoDP( &invalidRect );
		invalidRect.NormalizeRect();
		invalidRect.InflateRect( 2, 2 );
		getView()->InvalidateRect( &invalidRect );
		getView()->UpdateWindow();

		// Show the attributes of the first GraphicsObject picked in the dialog box
		d_pickList[0]->showInfoDialog();
		
		// Set current highlighted to zero
		d_currentPicked = 0;
	}
	// If nothing picked, show an empty pick box
	else
	{
		OverlayComponent::showEmptyInfoDialog();
	}

	// Reset the dragging flags
	d_dragging = d_drawingRect = FALSE;

	return;
}

void PickController::OnRButtonDown( UINT nFlags, CPoint point )
{
	// Call the parent classes version
	Controller::OnRButtonDown( nFlags, point );

	// Do nothing if nothing is picked
	if ( !( d_numPicked > 0 ) )
	{
		return;
	}

	// Get a device context from the view
	CClientDC dc( getView() );
	getView()->OnPrepareDC( &dc );

	// Remove highlight from currently selected GraphicsObject
	d_pickList[d_currentPicked]->highlight( FALSE );

	// Get the bounding rectangle for the currently selected GraphicsObject
	Rectangle2D GndRefSysBoundingRect = 
    d_pickList[d_currentPicked]->getBoundingRect();
	CRect lastBoundingRect = 
    CoordinateTransforms::GndRefSystoLP( GndRefSysBoundingRect );
	
	// Update the currently picked item to the next one
	d_currentPicked = (d_currentPicked + 1) % d_numPicked;
	
	// Highlight the next GraphicsObject
	d_pickList[d_currentPicked]->highlight( TRUE );

	// Redraw the area around both the current highlighted GraphicsObject and the
	// last highlighted GraphicsObject
	GndRefSysBoundingRect = d_pickList[d_currentPicked]->getBoundingRect();
	CRect curBoundingRect =
    CoordinateTransforms::GndRefSystoLP( GndRefSysBoundingRect );
	CRect invalidRect;
	invalidRect.UnionRect( &curBoundingRect, &lastBoundingRect );
	dc.LPtoDP( &invalidRect );
	invalidRect.NormalizeRect();
	invalidRect.InflateRect( 2, 2 );
	getView()->InvalidateRect( &invalidRect );
	getView()->UpdateWindow();

	// Show the attributes of the currently picked GraphicsObject in the dialog
  // box
	d_pickList[d_currentPicked]->showInfoDialog();
		
	return;
}

void PickController::cleanup()
{
	// Call the parent classes version
	Controller::cleanup();
	
	// Reset the controller
	reset();

	return;
}

void PickController::reset()
{
	// Call the parent class' version
	Controller::reset();

	// Get a device context from the view
	CClientDC dc( getView() );
	getView()->OnPrepareDC( &dc );

	if ( d_numPicked > 0 )
	{
		// Remove highlight from currently picked object
		d_pickList[d_currentPicked]->highlight( FALSE );

		// Get the bounding rectangle for the currently selected GraphicsObject
		Rectangle2D GndRefSysBoundingRect =
      d_pickList[d_currentPicked]->getBoundingRect();
		CRect lastBoundingRect =
      CoordinateTransforms::GndRefSystoLP( GndRefSysBoundingRect );
		dc.LPtoDP( &lastBoundingRect );
		lastBoundingRect.NormalizeRect();
		lastBoundingRect.InflateRect( 2, 2 );

		// Redraw the area around the currently picked object
		getView()->InvalidateRect( &lastBoundingRect );
		getView()->UpdateWindow();
	}

	// Close the pick dialog
	OverlayComponent::closeInfoDialog();

	// Empty the list of selected GraphicsObjects
	d_pickList.RemoveAll();
	d_pickList.FreeExtra();

	// Erase the last rectangle if you were drawing
	if ( d_drawingRect )
	{
		d_pDragRect->erase( &dc );
	}		

	// Reset the value of the member variables
	d_numPicked = d_currentPicked = -1;
	d_dragging = d_drawingRect = FALSE;
	delete d_pDragRect;
	d_pDragRect = 0;
	return;
}

void PickController::erase()
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
