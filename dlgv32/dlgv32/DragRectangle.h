// DragRectangle.h - header file for DragRectangle class
//
// Developed by: Mike Childs
//      Started: 12/4/96
//

#ifndef _DRAGRECTANGLE_H_
#define _DRAGRECTANGLE_H_

#include "StdAfx.h"
#include "GraphicsObject.h"

// The DragRectangle class implements a rectangle used for
// creating a rectangle that drags whenever the user moves the
// mouse.  The user of this class is responsible for initializing
// the drag rectangle in the constructor, drawing the drag rectangle
// when they need to, and erasing the drag rectangle before setting
// a new one.  The erase function does nothing if the drawn function
// has not first been called.
class DragRectangle : public GraphicsObject
{
public:
	// Constructor
	DragRectangle( CRect& rect );

	// Overriden functions
	void draw( CDC* pDC );

	// Class-specific functions
	void erase( CDC* pDC );
	void setRect( CRect& rect );
	const CRect& getRect();

protected:
	// Member data
	BOOL d_drawn;		// indicates if rectangle has been drawn and not erased
	CRect d_dragRect;
};

inline const CRect&
DragRectangle::getRect()
{
	return d_dragRect;
}

#endif 