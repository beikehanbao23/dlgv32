// DistanceController.h - header file for DistanceController class
//
// Developed by: Mike Childs
//      Started: 11/13/96
//

#ifndef _DISTANCECONTROLLER_H_
#define _DISTANCECONTROLLER_H_

#include "Controller.h"
#include "../dlg/DLGPoint.hxx"
#include "RubberBandLine.h"

// The DistanceZoomController class provides the following functionality:
//    a) When the left mouse button is pressed a starting point is
//       established
//    b) When the mouse is moved after a the left button is pressed down
//       a line is drawn from the starting point to the current point
//    c) When the left mouse button is pressed again a dialog is displayed
//       showing the distance (in meters) between the starting and ending
//       points 
// The users of this class need only call the OnLButtonDown and OnMouseMove
// member functions from the CView-derived class to use this functionality
class DistanceController : public Controller
{
public:
	// Overridden functions
	DistanceController( CDlgv32View* ptrView );
	void OnLButtonDown( UINT nFlags, CPoint point );
	void OnMouseMove  ( UINT nFlags, CPoint point );
	void cleanup();
	void erase();
	CString getText();

protected:
  // Member data
	int d_units;
	RubberBandLine d_line;
	BOOL           d_findingDistance;
};

inline CString
DistanceController::getText()
{
	return CString( "DIST" );
}

#endif

