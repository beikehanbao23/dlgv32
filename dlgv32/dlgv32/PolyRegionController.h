// PolyRegionController.h - header file for PolyRegionController class
//
// Developed by: Mike Childs
//      Started: 2/28/97
//

#ifndef _POLYREGIONCONTROLLER_H_
#define _POLYREGIONCONTROLLER_H_

#include "StdAfx.h"
#include "Controller.h"
#include "RubberBandLine.h"
#include "Dlgv32View.h"
#include "GraphicsLib/Point2D.h"

class PolyRegionController : public Controller
{
public:
	// Constructors
	PolyRegionController( CDlgv32View* ptrView );

	// Overrides
	void OnLButtonDown( UINT nFlags, CPoint point );
	void OnRButtonDown( UINT nFlags, CPoint point );
	void OnMouseMove  ( UINT nFlags, CPoint point );
	void cleanup();
	void reset();
	void erase();
	CString getText();

protected:
	// Member data
	CArray< Point2D, Point2D > d_points;
	BOOL d_dragging;
	BOOL d_erased;
	BOOL d_newSegment;
	UINT d_numPoints;
	RubberBandLine d_line;

	// Helper functions
	void draw( BOOL drawAll = FALSE );
	BOOL ptsCollinear();
};

inline CString
PolyRegionController::getText()
{	
	return CString( "PRGN" );
}

#endif
