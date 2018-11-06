// GraphicsObject.h - header file for GraphicsObject class
//
// Developed by: Mike Childs
//      Started: 10/18/96
//

#ifndef _GRAPHICSOBJECT_H_
#define _GRAPHICSOBJECT_H_

#include "StdAfx.h"
#include "GraphicsLib/Rectangle2D.h"

// GraphicsObject class:
//		This class is an abstract base class which provides the basic
//		interface that a self-drawing class should have using MFC.  All
//		objects derived from this class are responsible for drawing themselves
//		when their draw method is invoked.  They are also expected to clip 
//    themselves as necessary.

class GraphicsObject
{
public:
	GraphicsObject();
	virtual ~GraphicsObject();

	// draw is a pure virtual function which must be
	// overridden in any derived classes.  The parameters it takes are:
	//     pDC  - a pointer to the device context on which to draw
	// clipRect - a CRect object which is the current clipping rectangle
	// Its function is to (re)draw the object or part of the object if necessary
	virtual void draw(CDC* pDC, CRect* pClipRect = NULL );

	// Rectangle2D getBoundingRect() simply returns a copy of 
	// the bounding rectangle of the GraphicsObject
	virtual const Rectangle2D& getBoundingRect() const;

	// Accessor functions for background color
	static void setBgColor( COLORREF color );
	static COLORREF getBgColor();

	// Call this to force the GraphicsObject to recalculate its bounding
	// rectangle.  This should be used when the mapping changes
	virtual void calculateBoundingRect();

protected:
	Rectangle2D     d_boundingRect;
	static COLORREF d_bgColor;

private:
    GraphicsObject( const GraphicsObject& go ) { };
    void operator=( const GraphicsObject& go ) { };
};

// Inline function declarations

inline const Rectangle2D&
GraphicsObject::getBoundingRect() const
{
	return d_boundingRect;
}

inline void
GraphicsObject::setBgColor( COLORREF color )
{
	d_bgColor = color;
}

inline COLORREF
GraphicsObject::getBgColor()
{
	return d_bgColor;
}

#endif