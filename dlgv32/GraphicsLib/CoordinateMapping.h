// CoordinateMapping.h - header file for CoordinateMapping class
//
// Developed by: Mike Childs
//      Started: 2/5/97
//

#ifndef _COORDINATEMAPPING_H_
#define _COORDINATEMAPPING_H_

#include "Point2D.h"
#include "Rectangle2D.h"

class CoordinateMapping
{
public:
	// Constructor
	CoordinateMapping( bool maintainAspect = true );

	// Accessors/Modifiers
	void setWindowExtents( const Rectangle2D& windowExtents );
	void setWindowExtents( double x1, double y1, double x2, double y2 );
	void getWindowExtents( double& x1, double& y1, double& x2, double& y2 ) const;
	Rectangle2D getWindowExtents() const;
	void setViewportExtents( const Rectangle2D& viewportExtents );
	void setViewportExtents( double x1, double y1, double x2, double y2 );
	void getViewportExtents( double& x1, double& y1, double& x2, double& y2 ) const;
	Rectangle2D getViewportExtents() const;
	void setMaintainAspectRatio( bool maintainAspect = true );
	bool getMaintainAspectRatio() const;

	// Misc. functions
	void mapToViewport( double& x, double& y ) const;
	void mapToViewport( Point2D& point ) const;
	void mapToViewport( double& scalar ) const;	// scalar map
	void mapToWindow  ( double& x, double& y ) const;
	void mapToWindow  ( Point2D& point ) const;
	void mapToWindow  ( double& scalar ) const;	// scalar map
	bool pointInWindow( const Point2D& pt ) const;
	bool pointInWindow( double x, double y ) const;
	void zoomBy( double factor );
	void pan( const Point2D& newCenter );
	void pan( double newCenterX, double newCenterY );
	void zoomTo( double factor, const Point2D& newCenter );
	void zoomTo( double factor, double newCenterX, double newCenterY );

protected:
	void recalculate();
	Rectangle2D d_viewport;
	Rectangle2D d_window;
	bool    d_maintainAspectRatio;

private:
    double d_a, d_b, d_c, d_d;
};

inline void
CoordinateMapping::setWindowExtents( const Rectangle2D& windowExtents )
{
	d_window = windowExtents;
	d_window.normalize();

	recalculate();
}

inline void
CoordinateMapping::setWindowExtents( double x1, double y1, double x2, double y2 )
{
	setWindowExtents( Rectangle2D( x1, y1, x2, y2 ) );
}

inline void
CoordinateMapping::getWindowExtents( double& x1, double& y1,double& x2, double& y2 ) const
{
	x1 = d_window.left();
	y1 = d_window.bottom();
	x2 = d_window.right();
	y2 = d_window.top();
}

inline Rectangle2D
CoordinateMapping::getWindowExtents() const
{
	return d_window;
}

inline void
CoordinateMapping::setViewportExtents( const Rectangle2D& viewportExtents )
{
	d_viewport = viewportExtents;
	recalculate();
}

inline void
CoordinateMapping::setViewportExtents( double x1, double y1, double x2, double y2 )
{
	setViewportExtents( Rectangle2D( x1, y1, x2, y2 ) );
}

inline void
CoordinateMapping::getViewportExtents( double& x1, double& y1, double& x2, double& y2 ) const
{
	x1 = d_viewport.left();
	y1 = d_viewport.bottom();
	x2 = d_viewport.right();
	y2 = d_viewport.top();
}

inline Rectangle2D
CoordinateMapping::getViewportExtents() const
{
	return d_viewport;
}

inline bool
CoordinateMapping::pointInWindow( double x, double y ) const
{
	return pointInWindow( Point2D( x, y ) );
}

inline void
CoordinateMapping::setMaintainAspectRatio( bool maintainAspect )
{
	d_maintainAspectRatio = maintainAspect;
    recalculate();
}

inline bool
CoordinateMapping::getMaintainAspectRatio() const
{
	return d_maintainAspectRatio;
}

inline void 
CoordinateMapping::pan( double newCenterX, double newCenterY )
{
	pan( Point2D( newCenterX, newCenterY ) );
}

inline void 
CoordinateMapping::zoomTo( double factor, double newCenterX, double newCenterY )
{
	zoomTo( factor, Point2D( newCenterX, newCenterY ) );
}

inline void
CoordinateMapping::mapToViewport( double& x, double& y ) const
{
	Point2D point( x, y );
	mapToViewport( point );
	point.getXY( x, y );
}

inline void
CoordinateMapping::mapToWindow( double& x, double& y ) const
{
	Point2D point( x, y );
	mapToWindow( point );
	point.getXY( x, y );
}

#endif