// RubberBandLine.cpp - implementation file for RubberBandLine class
//
// Developed by: Mike Childs
//      Started: 12/5/96
//

#include "RubberBandLine.h"
#include "CoordinateTransforms.h"

RubberBandLine::RubberBandLine()
: GraphicsObject(), d_startX(0), d_startY(0), d_endX(0), d_endY(0), d_drawn(FALSE)
{
}

void
RubberBandLine::draw( CDC* pDC )
{
	// Set the drawing mode to NOT XOR
	int oldROP;
	oldROP = pDC->SetROP2( R2_NOT );

	// Create points in logical coordinates
	double sx, sy, ex, ey;
	sx = d_startX;
	sy = d_startY;
	ex = d_endX;
	ey = d_endY;
	CoordinateTransforms::GndRefSystoLP( sx, sy );
	CoordinateTransforms::GndRefSystoLP( ex, ey );

	// Draw the rubber band line
	pDC->MoveTo( sx, sy );
	pDC->LineTo( ex, ey );

	// Restore the DC to its previous state
	pDC->SetROP2( oldROP );

	// Set drawn flag
	d_drawn = TRUE;

	return;
}

void
RubberBandLine::erase( CDC* pDC )
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