// DistanceController.cpp - implementation file for Distancecontroller class
//
// Developed by: Mike Childs
//      Started: 11/13/96
//

#include <math.h>
#include "StdAfx.h"
#include "DistanceController.h"
#include "Dlgv32View.h"
#include "CoordinateTransforms.h"
#include "DistanceDialog.h"

DistanceController::DistanceController( CDlgv32View* ptrView )
: Controller( ptrView ), d_findingDistance(FALSE), d_units(0) // distance in 
                                                              // meters
{
	d_hCursor = AfxGetApp()->LoadCursor( IDC_X_CURSOR );
}

void 
DistanceController::OnLButtonDown( UINT nFlags, CPoint point )
{
	// Call the parent classes version
	Controller::OnLButtonDown( nFlags, point );
	
	// Get a device context from the view
	CClientDC dc( getView() );
	getView()->OnPrepareDC( &dc );

	// Set the starting point if the user isn't currently finding the
	// distance between two points
	if ( !d_findingDistance )
	{
		// Convert point from device coordinates to logical coordinates
		dc.DPtoLP( &point );

		// Convert the point from logical coordinates to ground ref sys
		// coordinates
		double end_x, end_y;
		end_x = point.x;
		end_y = point.y;
		CoordinateTransforms::LPtoGndRefSys( end_x, end_y );

		// Set the points in the rubber band line to the point clicked
		d_line.setStartPoint( end_x, end_y );
		d_line.setEndPoint  ( end_x, end_y );
	}
	// Show the distance if the user just finished finding the distance
	// between two points
	else
	{
		// Erase the last rubber band line
		d_line.erase( &dc );

		// Convert the current point to gnd ref sys coordinates
		double end_x, end_y;
		dc.DPtoLP( &point );
		end_x = point.x;
		end_y = point.y;
		CoordinateTransforms::LPtoGndRefSys( end_x, end_y );

		// Convert the starting point to GndRefSys
		double start_x, start_y;
		d_line.getStartPoint( start_x, start_y );

    // Convert the start and stop points to lat, lon
    double lat1, lon1, lat2, lon2;
    CoordinateTransforms::GndRefSystoLatLong( start_x, start_y, lat1, lon1 );
    CoordinateTransforms::GndRefSystoLatLong( end_x, end_y, lat2, lon2 );
		
		// Display a message box with the distance
		CDistanceDialog dlg;
		dlg.d_units = d_units;
    dlg.setDistanceMeters(CoordinateTransforms::calculateGreatCircleDistance(lat1, lon1, 
                                                                             lat2, lon2 ) );
		dlg.DoModal();
		d_units = dlg.d_units;
	}

	// Update the state of the controller
	d_findingDistance = !d_findingDistance;
}

void DistanceController::OnMouseMove( UINT nFlags, CPoint point )
{
	// Call the parent classes version
	Controller::OnMouseMove( nFlags, point );
	
	// Draw the line connecting the points if finding a distance
	if ( d_findingDistance )
	{
		// Get a device context from the view
		CClientDC dc( getView() );
		getView()->OnPrepareDC( &dc );

		// Erase last rubber band line
		d_line.erase( &dc );
		
		// Convert point from device coordinates to logical coordinates
		dc.DPtoLP( &point );

		// Convert point from logical coordinates to gnd ref sys coordinates
		double end_x, end_y;
		end_x = point.x;
		end_y = point.y;
		CoordinateTransforms::LPtoGndRefSys( end_x, end_y );

		// Save the current point in the rubber band line
		d_line.setEndPoint( end_x, end_y );

		// Draw the rubber band line
		d_line.draw( &dc );
	}
}

void DistanceController::cleanup()
{
	// Get a device context from the view
	CClientDC dc( getView() );
	getView()->OnPrepareDC( &dc );

	// Erase rubber band line
	d_line.erase( &dc );
}

void DistanceController::erase()
{
	cleanup();
}
