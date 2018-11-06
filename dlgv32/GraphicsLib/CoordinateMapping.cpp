// CoordinateMapping.cpp - implementation file for CoordinateMapping class
//
// Developed by: Mike Childs
//      Started: 2/5/97
//

#include "CoordinateMapping.h"
#include <math.h>

// Constructor
CoordinateMapping::CoordinateMapping( bool maintainAspect )
: d_window(0.0, 0.0, 0.0, 0.0),
  d_viewport(0.0, 0.0, 0.0, 0.0),
  d_maintainAspectRatio(maintainAspect),
  d_a(1.0), d_b(1.0), d_c(0.0), d_d(0.0)
{
}


void
CoordinateMapping::mapToViewport( Point2D& point ) const
// Map <point> from world-space tp the viewport
{
	double winWidth   = d_window.width();
	double winHeight  = d_window.height();

	if ( winWidth != 0 )
	{
		//tempX = ( point.getX() - winLeft ) * ( d_viewport.width()  / winWidth  ) + viewLeft;
        point.setX( d_a * point.getX() + d_c );
	}

	if ( winHeight != 0 )
	{
		//tempY = ( point.getY() - winBottom ) * ( d_viewport.height() / winHeight ) + viewBottom;
        point.setY( d_b * point.getY() + d_d );
	}

	//point.setXY( tempX, tempY );
}

void
CoordinateMapping::mapToWindow( Point2D& point ) const
// Map <point> from viewport to world-space
{
	double tempX(0), tempY(0);
	double viewWidth  = d_viewport.width();
	double viewHeight = d_viewport.height();
	double viewLeft   = d_viewport.getLowerLeft().getX();
	double viewBottom = d_viewport.getLowerLeft().getY();
	double winLeft    = d_window.getLowerLeft().getX();
	double winBottom  = d_window.getLowerLeft().getY();

	if ( viewWidth != 0 )
	{
		tempX = ( point.getX() - viewLeft ) * ( d_window.width()  / viewWidth  ) + winLeft;
	}

	if ( viewHeight != 0 )
	{
		tempY = ( point.getY() - viewBottom ) * ( d_window.height() / viewHeight ) + winBottom;
	}

	point.setXY( tempX, tempY );
}

void
CoordinateMapping::mapToViewport( double& scalar ) const
// The aspect ratio should be maintained
{
	// Abort if the aspect ratio isn't being maintained
	if ( !d_maintainAspectRatio )
	{
		return;
	}

	// Compute if the window isn't bad
	if ( d_window.width() != 0 )
	{
		scalar *= fabs( d_viewport.width() / d_window.width() );
	}
}

void
CoordinateMapping::mapToWindow( double& scalar ) const
// The aspect ratio should be maintained
{
	// Abort if the aspect ratio isn't being maintained
	if ( !d_maintainAspectRatio )
	{
		return;
	}

	// Compute if the viewport isn't bad
	if ( d_viewport.width() != 0 )
	{
		scalar *= fabs( d_window.width() / d_viewport.width() );
	}
}

bool
CoordinateMapping::pointInWindow( const Point2D& pt ) const
{
	if ( pt.getX() >= d_window.left()  &&
		 pt.getX() <= d_window.right() &&
		 pt.getY() >= d_window.bottom()  &&
		 pt.getY() <= d_window.top() )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void
CoordinateMapping::recalculate()
{
	// Abort if either rectangle has a zero height or width
	if ( d_viewport.height() == 0 || d_window.height() == 0 || 
         d_viewport.width()  == 0 || d_window.width()  == 0 )
	{
		return;
	}

	// Maintain the aspect ratio
	if ( d_maintainAspectRatio )
	{
		double viewportWidth  = d_viewport.width();
		double viewportHeight = d_viewport.height();
		double windowWidth    = d_window.width();
		double windowHeight   = d_window.height();

		// calculate the aspect ratios
		double aspectViewport, aspectWindow;
		aspectViewport = fabs( viewportWidth / viewportHeight );
		aspectWindow   = fabs( windowWidth   / windowHeight   );

		if ( aspectViewport > aspectWindow )	// Window needs widened
		{
			double newWindowWidth = windowHeight * aspectViewport;
			d_window.inflateRect( ( newWindowWidth - windowWidth ) / 2.0, 0 );
		}
		else
		{
			double newWindowHeight = windowWidth / aspectViewport;
			d_window.inflateRect( 0, ( newWindowHeight - windowHeight ) / 2.0 );
		}
	}

	double viewportWidth  = d_viewport.width();
	double viewportHeight = d_viewport.height();
	double windowWidth    = d_window.width();
	double windowHeight   = d_window.height();

    // Calculate helper values
    d_a = viewportWidth / windowWidth;
    d_b = viewportHeight / windowHeight;
    d_c = ( -d_window.left() * viewportWidth ) / windowWidth + d_viewport.left();
    d_d = ( -d_window.bottom() * viewportHeight ) / windowHeight + d_viewport.bottom();
}

void 
CoordinateMapping::zoomBy( double factor )
{
	// Abort if attempt to zoom by zero
	if ( factor == 0.0 )
	{
		return;
	}

	// Zoom the window
	if ( factor < 0.0 )
	{
		d_window.scale( -factor, -factor );
	}
	else
	{
		d_window.scale( 1.0 / factor, 1.0 / factor );
	}

    recalculate();
}

void 
CoordinateMapping::pan( const Point2D& newCenter )
{
	// Translate window to new center
	Point2D center = d_window.getCenter();
	d_window.translate( newCenter - center );
    recalculate();
}

void 
CoordinateMapping::zoomTo( double factor, const Point2D& newCenter )
{
	zoomBy( factor );
	pan( newCenter );
}

