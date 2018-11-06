// GraphicsObject.cpp - Implementation of GraphicsObject class
//
// Developed by: Mike Childs
//      Started: 10/18/96
//

#include "GraphicsObject.h"

// Initialize static member data
COLORREF GraphicsObject::d_bgColor = PALETTERGB(0,0,0);

GraphicsObject::GraphicsObject()
   : d_boundingRect( 0.0, 0.0, 0.0, 0.0 )
{
}

GraphicsObject::~GraphicsObject()
{
	// This does nothing in the base class
}

void
GraphicsObject::draw( CDC* pDC, CRect* clipRect )
{
	// The base implementation does nothing
}

void
GraphicsObject::calculateBoundingRect()
{
	// This does nothing in the base class
}