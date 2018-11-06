// PickController.h - header file for PickController class
//
// Developed by: Mike Childs
//      Started: 11/15/96
//

#ifndef _PICKCONTROLLER_H_
#define _PICKCONTROLLER_H_

#include "StdAfx.h"			// Standard MFC include file
#include "Controller.h"		// Include file for base class
#include "DragRectangle.h"

class CDlgv32View;      // forward declaration of CView-derived class
class OverlayComponent; // forward declaration of OverlayComponent class

// The PickController class provides the following functionality
//   a) when the user clicks the left mouse button, all GraphicsObjects within
//      PICK_APERTURE of where the mouse button was pressed are selected and 
//      the first object in the list is highlighted.  The user can cycle 
//      through the selected elements with the right mouse button.  When a
//      GraphicsObject is highlighted a dialog box displays information about
//      it.
// The user of this class need only call the OnLButtonDown and OnRButtonDown
// member functions with the same name in the CView-derived class to use this
// functionality.  The user should also call cleanup() whenever another 
// controller is selected.
class PickController : public Controller
{
public:
	// Overridden functions
	PickController( CDlgv32View* ptrView );
	~PickController();
	void OnLButtonDown( UINT nFlags, CPoint point );
	void OnLButtonUp  ( UINT nFlags, CPoint point );
	void OnRButtonDown( UINT nFlags, CPoint point );
	void OnMouseMove  ( UINT nFlags, CPoint point );
	void cleanup();
	void reset();
	void erase();
	CString getText();

protected:
	// Member data
	CTypedPtrArray< CPtrArray, OverlayComponent* > d_pickList;
	DragRectangle* d_pDragRect;
	int    d_numPicked;
	int    d_currentPicked;
	CPoint d_startPoint;
	CPoint d_lastMousePos;
	BOOL   d_dragging;
	BOOL   d_drawingRect;
	const int PICK_APERTURE;
};

inline CString
PickController::getText()
{
	return CString( "PICK" );
}

#endif
