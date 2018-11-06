// PanController.cpp - implemenation file for PanController class
//
// Developed by: Mike Childs
//      Started: 10/24/96
//

#include "StdAfx.h"
#include "PanController.h"
#include "Dlgv32View.h"
#include "GraphicsLib\CoordinateMapping.h"
#include "CoordinateTransforms.h"
#include "resource.h"

PanController::PanController( CDlgv32View* ptrView )
: Controller( ptrView )
{
	// Load the cursor for the pan controller
	d_hCursor = AfxGetApp()->LoadCursor( IDC_PAN_CURSOR );
}

void PanController::OnLButtonDown( UINT nFlags, CPoint point )
{
	// Capture the mouse until button up
	getView()->SetCapture();

	// Call base class version of overridden function
	Controller::OnLButtonDown( nFlags, point );
}

void PanController::OnLButtonUp( UINT nFlags, CPoint point )
{
	// If the view didn't capture the mouse, then the user
	// isn't dragging in this window
	if ( getView()->GetCapture() != getView() )
	{
		return;
	}


	// Release the mouse capture established at the beginning of the mouse drag
	ReleaseCapture();

	// Convert point from device coordinates to GndRefSys
	double x, y;
	CClientDC dc( getView() );
	getView()->OnPrepareDC( &dc );
	dc.DPtoLP( &point );
	x = point.x;
	y = point.y;
	CoordinateTransforms::LPtoGndRefSys( x, y );

	// Pan to the current point
	CoordinateTransforms::getCurrentMapping()->pan( x, y );

	// Invalidate the view so that it will be redrawn
	getView()->Invalidate();
	
	// Call base class version of overridden function
	Controller::OnLButtonUp( nFlags, point );
}

void PanController::OnMouseMove( UINT nFlags, CPoint point )
{
	// If the view didn't capture the mouse, then the user
	// isn't dragging in this window
	if ( getView()->GetCapture() != getView() )
	{
		return;
	}

	// Call base class version of overridden function
	Controller::OnMouseMove( nFlags, point );
}
	
