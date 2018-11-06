// RubberBandLine.h - header file for RubberBandLine class
//
// Developed by: Mike Childs
//      Started: 12/5/96
//

#ifndef _RUBBERBANDLINE_H_
#define _RUBBERBANDLINE_H_

#include "StdAfx.h"
#include "GraphicsObject.h"

class RubberBandLine : public GraphicsObject
// The class RubberBandLine provides the functionality of
// a rubber-band line which moves without causing repaints.
// The coordinates stored must be in logical format.
{
public:
	// Overriden functions
	RubberBandLine();
	void draw( CDC* pDC );
	
	// RubberBandLine-specific functions
	void erase( CDC* pDC );
	void setEndPoint( double end_x, double end_y );
	void getEndPoint( double& end_x, double& end_y );
	void setStartPoint( double start_x, double start_y );
	void getStartPoint( double& start_x, double& start_y );

protected:
	double d_startX, d_startY;
	double d_endX, d_endY;
	BOOL   d_drawn;
};

inline void
RubberBandLine::setEndPoint( double end_x, double end_y )
{
	d_endX = end_x;
	d_endY = end_y;
}

inline void
RubberBandLine::setStartPoint( double start_x, double start_y )
{
	d_startX = start_x;
	d_startY = start_y;
}

inline void
RubberBandLine::getEndPoint( double& end_x, double& end_y )
{
	end_x = d_endX;
	end_y = d_endY;
}

inline void
RubberBandLine::getStartPoint( double& start_x, double& start_y )
{
	start_x = d_startX;
	start_y = d_startY;
}

#endif