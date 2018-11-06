// PanController.h - header file for PanController class
//
// Developed by: Mike Childs
//      Started: 10/24/96
//

#ifndef _PANCONTROLLER_H_
#define _PANCONTROLLER_H_

#include "Controller.h"

// The PanController class provides the following functionality:
//   a)  when the user holds down the left mouse button and moves the mouse,
//       he will drag the current document along with him in effect panning the
//       view
// The user of this class need only call the OnLButtonDown, OnMouseMove, and
// OnLButtonUp member functions from the functions with the same name in the
// CView-derived class to achieve this functionality
class PanController : public Controller
{
public:
	// Overridden functions
	PanController( CDlgv32View* ptrView );
	void OnLButtonDown( UINT nFlags, CPoint point );
	void OnMouseMove( UINT nFlags, CPoint point );
	void OnLButtonUp( UINT nFlags, CPoint point );
	CString getText();
};

inline CString
PanController::getText()
{
	return CString( "PAN " );
}

#endif
