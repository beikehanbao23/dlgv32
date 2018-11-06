// Point2D.cpp - implementation file for Point2D class
//
// Developed by: Mike Childs
//      Started: 2/5/97
//

#include "Point2D.h"

Point2D::Point2D()
{
	d_x = 0.0;
    d_y = 0.0;
}

Point2D::Point2D( double x, double y )
{
    d_x = x;
    d_y = y;
}

Point2D::Point2D( const Point2D& point )
{
    operator=( point );
}

Point2D::~Point2D()
{
}

Point2D&
Point2D::operator=( const Point2D& point )
// Assignment
{
	if ( &point != this )
    {
		d_x = point.d_x;
        d_y = point.d_y;
    }

    return *this;
}

bool
Point2D::operator==( const Point2D& point ) const
// Equals
{
	if ( ( d_x == point.d_x ) &&
         ( d_y == point.d_y ) )
	{
		return true;
	}

    return false;
}

bool
Point2D::operator!=( const Point2D& point ) const
// Not equals
{
	return !operator==( point );
}

bool
Point2D::operator<( const Point2D& point ) const
// Less than
{
    if ( d_x < point.d_x )
	{
		return true;
	}

    if ( (d_x == point.d_x ) &&
         (d_y <  point.d_y) )
	{
        return true;
	}

    return false;
}

Point2D
Point2D::operator+( const Point2D& point ) const
// Addition
{
	double tempX, tempY;
	tempX = d_x + point.getX();
	tempY = d_y + point.getY();
	return ( Point2D( tempX, tempY ) );
}

Point2D
Point2D::operator-( const Point2D& point ) const
// Subtraction
{
	double tempX, tempY;
	tempX = d_x - point.getX();
	tempY = d_y - point.getY();
	return ( Point2D( tempX, tempY ) );
}

Point2D
Point2D::operator-() const
// Unary negation
{
	return ( Point2D( -d_x, -d_y ) );
}

Point2D
Point2D::operator*( double scalar ) const
// Scalar multiplication
{
	double tempX, tempY;
	tempX = d_x * scalar;
	tempY = d_y * scalar;
	return ( Point2D( tempX, tempY ) );
}
