// Controller.h - header file for Controller class
//
// Developed by: Mike Childs
//      Started: 10/24/96
//

#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "StdAfx.h"

class CDlgv32View; // forward declaration of CView class (should this be Cdlgv32View?)

// The Controller class is an abstract class used to define the generic interface
// for all Controller-based classes.  A Controller provides functionality based on
// mouse clicks, and drags.  The constructor for the Conroller class takes as
// an argument a pointer to the CView class utilizing it.
class Controller
{
public:
	// Constructors
	Controller( void );
	Controller( CDlgv32View* ptrView );

	// Virtual member functions
	virtual ~Controller() {};	// Virtual destructor
	virtual BOOL OnIdle( UINT lCount );
	virtual void OnMouseMove( UINT nFlags, CPoint point );
	virtual void OnLButtonDown( UINT nFlags, CPoint point );
	virtual void OnRButtonDown( UINT nFlags, CPoint point );
	virtual void OnLButtonUp( UINT nFlags, CPoint point );
	virtual void OnRButtonUp( UINT nFlags, CPoint point );
	virtual void cleanup();
	virtual void reset();
	virtual void erase();
	virtual CString getText();

	// Non polymorphic member functions
	HCURSOR getCursor();

protected:
	// Accessor function for Controller-derived class
	CDlgv32View* getView();

	// member data
	CDlgv32View* d_ptrView;
	HCURSOR      d_hCursor;
};

inline BOOL
Controller::OnIdle( UINT lCount )
{
	return FALSE;
}

inline void
Controller::OnMouseMove( UINT nFlags, CPoint point )
{
	// This function does nothing in the base class
}

inline void
Controller::OnLButtonDown( UINT nFlags, CPoint point )
{
	// This function does nothing in the base class
}

inline void
Controller::OnRButtonDown( UINT nFlags, CPoint point )
{
	// This function does nothing in the base class
}

inline void
Controller::OnLButtonUp( UINT nFlags, CPoint point )
{
	// This function does nothing in the base class
}

inline void
Controller::OnRButtonUp( UINT nFlags, CPoint point )
{
	// This function does nothing in the base class
}

inline void
Controller::cleanup()
{
	// This function does nothing in the base class
}

inline void
Controller::reset()
{
	// This function does nothing in the base class
}

inline void
Controller::erase()
{
	// This functions does nothing in the base class
}

inline CDlgv32View*
Controller::getView()
{
	return d_ptrView;
}

inline CString
Controller::getText()
{
	return CString( "N/A " );
}

inline HCURSOR
Controller::getCursor()
{
	return d_hCursor;
}

#endif
