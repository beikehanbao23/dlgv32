// DragRectangle.cpp - implementation file for DragRectangle class
//
// Developed by: Mike Childs
//      Started: 12/4/96
//

#include "DragRectangle.h"

DragRectangle::DragRectangle( CRect& rect )
: GraphicsObject(), d_drawn(FALSE), d_dragRect(rect)
{
}

void DragRectangle::setRect( CRect& rect )
{
	d_dragRect = rect;
	d_drawn    = FALSE; // reset drawn flag
}

void DragRectangle::draw( CDC* pDC )
{
	// Set the drawing mode to NOT
	int oldROP;
	oldROP = pDC->SetROP2( R2_NOT );

	// Draw the drag rectangle
	CPoint topLeft = d_dragRect.TopLeft();
	int width = d_dragRect.Width();
	int height = d_dragRect.Height();
	pDC->MoveTo( topLeft.x,         topLeft.y );
	pDC->LineTo( topLeft.x + width, topLeft.y );
	pDC->LineTo( topLeft.x + width, topLeft.y + height );
	pDC->LineTo( topLeft.x,         topLeft.y + height );
	pDC->LineTo( topLeft.x,         topLeft.y );	

	// Restore the DC to its previous state
	pDC->SetROP2( oldROP );

	// Set drawn flag
	d_drawn = TRUE;

	return;
}

void DragRectangle::erase( CDC* pDC )
{
	// draw over the rectangle if it's drawn
	if ( d_drawn )
	{
		draw( pDC );
	}

	// Reset drawn flag
	d_drawn = FALSE;

	return;
}
