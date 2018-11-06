// ZoomController.h - header file for ZoomController class
//
// Developed by: Mike Childs
//      Started: 10/24/96
//

#ifndef _ZOOMCONTROLLER_H_
#define _ZOOMCONTROLLER_H_

#include "StdAfx.h"
#include "Controller.h"
#include "DragRectangle.h"

// The ZoomController class provides the following functionality:
//   a)  when the user clicks and releases the left mouse button 
//       without moving the cursor significantly the current view is
//       zoomed in on by a factor of 2 and is centered on the point clicked
//   b)  when the user clicks the right mouse button the current view is
//       zoomed out by a factor of 2 and is centered on the point clicked
//   c)  when the user holds down the left mouse button and drags the mouse
//       a drag box is created and updated as the mouse is moved.  When the
//       user releases the left mouse button the view is zoomed so that at 
//       least all of the area in the box is shown ( and centered on )
// Ths user of this class need only call the OnLButtonDown or OnRButtonDown 
// member functions from the CView-derived class to use this functionality
class ZoomController : public Controller
{
public:
	// Overridden functions
	ZoomController( CDlgv32View* ptrView );
	~ZoomController();
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
	CPoint d_startPoint;
	BOOL   d_dragging;
	BOOL   d_drawingRect;
	DragRectangle* d_pDragRect;
};

inline CString
ZoomController::getText()
{
	return CString( "ZOOM" );
}

#endif
