// Point3D.cpp - implementation file for Point3D class
//
// Developed by: Mike Childs
//      Started: 2/9/97
//

#include "Point3D.h"

Point3D::Point3D()
{
	d_x = 0.0;
    d_y = 0.0;
	d_y = 0.0;
}

Point3D::Point3D( double x, double y, double z )
{
    d_x = x;
    d_y = y;
	d_z = z;
}

Point3D::Point3D( const Point3D& point )
{
    operator=( point );
}

Point3D::~Point3D()
{
}

Point3D&
Point3D::operator=( const Point3D& point )
// Assignment
{
	if ( &point != this )
    {
		d_x = point.d_x;
        d_y = point.d_y;
		d_z = point.d_z;
    }

    return *this;
}

bool
Point3D::operator==( const Point3D& point ) const
// Equals
{
	if ( ( d_x == point.d_x ) &&
         ( d_y == point.d_y ) &&
		 ( d_z == point.d_z ) )
	{
		return true;
	}

    return false;
}

bool
Point3D::operator!=( const Point3D& point ) const
// Not equals
{
	return !operator==( point );
}

bool
Point3D::operator<( const Point3D& point ) const
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

	if ( ( d_x == point.d_x ) &&
		 ( d_y == point.d_y ) &&
		 ( d_z <  point.d_z ) )
	{
		return true;
	}

    return false;
}

Point3D
Point3D::operator+( const Point3D& point ) const
// Addition
{
	double tempX, tempY, tempZ;
	tempX = d_x + point.getX();
	tempY = d_y + point.getY();
	tempZ = d_z + point.getZ();
	return Point3D( tempX, tempY, tempZ );
}

Point3D
Point3D::operator-( const Point3D& point ) const
// Subtraction
{
	double tempX, tempY, tempZ;
	tempX = d_x - point.getX();
	tempY = d_y - point.getY();
	tempZ = d_z - point.getZ();
	return Point3D( tempX, tempY, tempZ );
}

Point3D
Point3D::operator-() const
// Unary negation
{
	return Point3D( -d_x, -d_y, -d_z );
}

Point3D
Point3D::operator*( double scalar ) const
// Scalar multiplication
{
	double tempX, tempY, tempZ;
	tempX = d_x * scalar;
	tempY = d_y * scalar;
	tempZ = d_y * scalar;
	return Point3D( tempX, tempY, tempZ );
}
