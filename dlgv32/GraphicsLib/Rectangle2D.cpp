// Rectangle2D.cpp - implementation file for Rectangle2D class
//
// Developed by: Mike Childs
//      Started: 10/18/96
//

#include "Rectangle2D.h"
#include "Transforms.h"

Rectangle2D::Rectangle2D()
{
	d_x1 = d_y1 = d_x2 = d_y2 = 0.0;
}

Rectangle2D::Rectangle2D(double x1, double y1, double x2, double y2)
{
	setPoints(x1, y1, x2, y2);
}

Rectangle2D::Rectangle2D(const Rectangle2D& rect)
{
	operator=(rect);
}

Rectangle2D& 
Rectangle2D::operator=(const Rectangle2D& rect)
{
	if (&rect != this)
	{
		d_x1 = rect.d_x1;
		d_x2 = rect.d_x2;
		d_y1 = rect.d_y1;
		d_y2 = rect.d_y2;
	}

	return *this;
}

bool
Rectangle2D::operator==(const Rectangle2D& rect)
{
	if ( (d_x1 == rect.d_x1) && (d_x2 == rect.d_x2) &&
		 (d_y1 == rect.d_y1) && (d_y2 == rect.d_y2) )
    {
		return true;
    }

	return false;
}

double 
Rectangle2D::height() const
{
	return ( d_y2 - d_y1 );
}

double 
Rectangle2D::width() const
{
	return ( d_x2 - d_x1 );
}

void
Rectangle2D::inflateRect( double cx, double cy )
{
	d_x1 -= cx;
	d_x2 += cx;
	d_y1 -= cy;
	d_y2 += cy;
}

void
Rectangle2D::translate( const Point2D& by )
// Translate the rectangle by <by>
{
	Transforms::translate( d_x1, d_y1, by.getX(), by.getY() );
	Transforms::translate( d_x2, d_y2, by.getX(), by.getY() );
}

void
Rectangle2D::translate( double dx, double dy )
// Translate the rectangle by [ <dx>, <dy> ]
{
	translate( Point2D( dx, dy ) );
}
void
Rectangle2D::reflectXAxis()
// Reflect the rectangle in the XAxis
{
	Transforms::reflectXAxis( d_x1, d_y1 );
	Transforms::reflectXAxis( d_x2, d_y2 );
	normalize();
}

void
Rectangle2D::reflectYAxis()
// Reflect the rectangle in the YAxis
{
	Transforms::reflectYAxis( d_x1, d_y1 );
	Transforms::reflectYAxis( d_x2, d_y2 );
}

void
Rectangle2D::reflectOrigin()
// Reflect the rectangle in the origin
{
	Transforms::reflectOrigin( d_x1, d_y1 );
	Transforms::reflectOrigin( d_x2, d_y2 );
}

void
Rectangle2D::normalize()
// Ensure the rectangle is of the forms ( lowerLeft, upperRight )
{
	if ( d_x2 < d_x1 )
	{
		double tmp = d_x1;
		d_x1 = d_x2;
		d_x2 = tmp;
	}

	if ( d_y1 > d_y2 )
	{
		double tmp = d_y1;
		d_y1 = d_y2;
		d_y2 = tmp;
	}
}

bool
Rectangle2D::pointInRect( const Point2D& pt ) const
{
	return pointInRect( pt.getX(), pt.getY() );
}

bool
Rectangle2D::pointInRect( double x, double y ) const
{
	if ( ( x >= d_x1 ) && ( x <= d_x2 ) &&
		 ( y >= d_y1 ) && ( y <= d_y2 ) )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool
Rectangle2D::intersectRect( const Rectangle2D& rect1, const Rectangle2D& rect2 )
// Rectangle becomes the intersection of <rect1> and <rect2>.  Returns
// FALSE if there is no intersection, TRUE otherwise.
// Preconditions: <rect1> and <rect2> are normalized
{
	double r1x1, r1x2, r1y1, r1y2;
	double r2x1, r2x2, r2y1, r2y2;

	// Get the points
	rect1.getPoints( r1x1, r1y1, r1x2, r1y2 );
	rect2.getPoints( r2x1, r2y1, r2x2, r2y2 );

	double xmin, xmax, ymin, ymax;
	xmin = ( r1x1 > r2x1 ) ? r1x1 : r2x1;	// <xmin> = MAX( r1x1, r2x1 )
	xmax = ( r1x2 < r2x2 ) ? r1x2 : r2x2;	// <xmax> = MIN( r1x2, r2x2 )
	ymin = ( r1y1 > r2y1 ) ? r1y1 : r2y1;	// <ymin> = MAX( r1y1, r2y1 )
	ymax = ( r1y2 < r2y2 ) ? r1y2 : r2y2;	// <ymax> = MIN( r1y2, r2y2 )

	if ( ( xmin > xmax ) || ( ymin > ymax ) )
	{
		// Set rectangle to all zeroes
		d_x1 = d_y1 = d_x2 = d_y2 = 0.0;
		return false;
	}
	else
	{
		// Set rectangle to ( <xmin>, <ymin>, <xmax>, <ymax> )
		d_x1 = xmin;
		d_x2 = xmax;
		d_y1 = ymin;
		d_y2 = ymax;
		return true;
	}
}

Point2D
Rectangle2D::getCenter() const
{
	return Point2D( ( d_x1 + d_x2 ) / 2.0, ( d_y1 + d_y2 ) / 2.0 );
}

void
Rectangle2D::scale( double sx, double sy )
{
	Point2D center = getCenter();
	double cenX, cenY;
	center.getXY( cenX, cenY );
	Transforms::scale( d_x1, d_y1, sx, sy, cenX, cenY );
	Transforms::scale( d_x2, d_y2, sx, sy, cenX, cenY );
}