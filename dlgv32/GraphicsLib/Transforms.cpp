// Transforms.cpp - implementation file for Transforms class
//
// Developed by: Mike Childs
//      Started: 2/7/97
//

#include "Transforms.h"
#include <math.h>

void
Transforms::translate( Point2D& point, const Point2D& by )
// Translate <point> by <by>
{
	point = point + by;
}

void
Transforms::translate( Point2D& point, double dx, double dy )
// Translate the point <point> by (<dx>, <dy>)
{
	translate( point, Point2D( dx, dy ) );
}

void
Transforms::translate( double& x, double& y, double dx, double dy )
// Translate the point (<x>, <y>) by (<dx>, <dy>)
{
	x += dx;
	y += dy;
}

void
Transforms::translate( Point3D& point, const Point3D& by )
{
	point = point + by;
}

void
Transforms::translate( double& x, double& y, double& z,
					   double dx, double dy, double dz )
{
	x += dx;
	y += dy;
	z += dz;
}

void
Transforms::rotate( Point2D& point, double theta, const Point2D& about )
// Rotate <point> <theta> radians about the point <about>
{
	// Translate <point> so that <about> is the origin
	translate( point, -about );

	// Rotate translated <point> by <theta>
	double sin_theta, cos_theta, tempX, tempY;
	sin_theta = sin( theta );
	cos_theta = cos( theta );
	tempX = point.getX() * cos_theta - point.getY() * sin_theta;
	tempY = point.getY() * cos_theta + point.getX() * sin_theta;
	point.setXY( tempX, tempY );

	// Translate the new <point> back by <about> to reset the origin position
	translate( point, about );
}

void
Transforms::rotate( double& x, double& y, double theta, double ax, double ay )
// Rotate the point (<x>, <y>) by <theta> about the point (<ax>, <ay>)
{
	Point2D point( x, y ), about( ax, ay );
	rotate( point, theta, about );
	point.getXY( x, y );
}

void
Transforms::rotateX( Point3D& point, double theta, const Point3D& about )
// Rotate <point> by <theta> about the X-axis relative to <about>
{
	// Translate <point> so that <about> is origin
	translate( point, -about );

	// Rotate translate <point> by <theta> about the x-axis
	double sin_theta, cos_theta, tempX, tempY, tempZ;
	sin_theta = sin( theta ); 
	cos_theta = cos( theta );
	point.getXYZ( tempX, tempY, tempZ );
	point.setY( tempY * cos_theta - tempZ * sin_theta );
	point.setZ( tempZ * cos_theta + tempY * sin_theta );

	// Translate the new <point> back by <about> to reset the origin position
	translate( point, about );
}

void
Transforms::rotateX( double& x, double& y, double& z, double theta,
					 double ax, double ay, double az )
// Rotate <point> by <theta> about the X-axis relative to <about>
{
	Point3D point( x, y, z ), about( ax, ay, az );
	rotateX( point, theta, about );
	point.getXYZ( x, y, z );
}

void
Transforms::rotateY( Point3D& point, double theta, const Point3D& about )
// Rotate <point> by <theta> about the Y-axis relative to <about>
{
	// Translate <point> so that <about> is origin
	translate( point, -about );

	// Rotate translate <point> by <theta> about the y-axis
	double sin_theta, cos_theta, tempX, tempY, tempZ;
	sin_theta = sin( theta ); 
	cos_theta = cos( theta );
	point.getXYZ( tempX, tempY, tempZ );
	point.setX( tempX * cos_theta + tempZ * sin_theta );
	point.setZ( tempZ * cos_theta - tempX * sin_theta );

	// Translate the new <point> back by <about> to reset the origin position
	translate( point, about );
}

void
Transforms::rotateY( double& x, double& y, double& z, double theta,
					 double ax, double ay, double az )
// Rotate <point> by <theta> about the Y-axis relative to <about>
{
	Point3D point( x, y, z ), about( ax, ay, az );
	rotateY( point, theta, about );
	point.getXYZ( x, y, z );
}

void
Transforms::rotateZ( Point3D& point, double theta, const Point3D& about )
// Rotate <point> by <theta> about the Z-axis relative to <about>
{
	// Translate <point> so that <about> is origin
	translate( point, -about );

	// Rotate translate <point> by <theta> about the z-axis
	double sin_theta, cos_theta, tempX, tempY, tempZ;
	sin_theta = sin( theta ); 
	cos_theta = cos( theta );
	point.getXYZ( tempX, tempY, tempZ );
	point.setX( tempX * cos_theta - tempY * sin_theta );
	point.setY( tempY * cos_theta + tempX * sin_theta );

	// Translate the new <point> back by <about> to reset the origin position
	translate( point, about );
}

void
Transforms::rotateZ( double& x, double& y, double& z, double theta,
					 double ax, double ay, double az )
// Rotate <point> by <theta> about the Z-axis relative to <about>
{
	Point3D point( x, y, z ), about( ax, ay, az );
	rotateZ( point, theta, about );
	point.getXYZ( x, y, z );
}

void
Transforms::scale( Point2D& point, double scaleX, double scaleY, const Point2D& about )
// Scale <point> by [ <scaleX> <scaleY> ] with respect to <about>
{
	// Translate <point> so that <about> is the origin
	translate( point, -about );

	// Scale <point> by scale factors
	point.setX( point.getX() * scaleX );
	point.setY( point.getY() * scaleY );

	// Translate the new <point> back by <about> to reset the origin position
	translate( point, about );
}

void
Transforms::scale( double& x, double& y, double scaleX, double scaleY, double ax, double ay )
// Scale the point (<x>, <y>) by [ <scaleX> <scaleY> ] with respect to the point (<ax>, <ay>)
{
	Point2D point( x, y ), about( ax, ay );
	scale( point, scaleX, scaleY, about );
	point.getXY( x, y );
}

void
Transforms::scale( Point3D& point, double scaleX, double scaleY, double scaleZ,
				   const Point3D& about )
// Scale <point> by [ <scaleX> <scaleY> <scaleZ> ] wrt <about>
{
	// Translate <point> so that <about> is the origin
	translate( point, -about );

	// Scale <point> by scale factors
	point.setX( point.getX() * scaleX );
	point.setY( point.getY() * scaleY );
	point.setZ( point.getZ() * scaleZ );

	// Translate the new <point> back by <about> to reset the origin position
	translate( point, about );
}

void
Transforms::scale( double& x, double& y, double& z, 
				   double sx, double sy, double sz,
				   double ax, double ay, double az )
// Scale the point (<x>, <y>, <z> ) by [ <sx> <sy> <sz> ] 
// with respect to the point (<ax>, <ay>, <az> )
{
	Point3D point( x, y, z ), about( ax, ay, az );
	scale( point, sx, sy, sz, about );
	point.getXYZ( x, y, z );
}

void
Transforms::reflectXAxis( Point2D& point )
// Reflect <point> about the x-axis
{
	// Negate the y-component of <point>
	point.setY( -point.getY() );
}

void
Transforms::reflectXAxis( double& x, double& y )
// Reflect the point (<x>, <y>) about the x-axis
{
	y = -y;
}

void
Transforms::reflectYAxis( Point2D& point )
// Reflect <point> about the y-axis
{
	// Negate the x-component of <point>
	point.setX( -point.getX() );
}

void
Transforms::reflectYAxis( double& x, double& y )
// Reflect the point (<x>, <y>) about the y-axis
{
	x = -x;
}

void
Transforms::reflectOrigin( Point2D& point )
// Reflect <point> about the origin
{
	// Negate both of the points coordinates
	point = -point;
}

void 
Transforms::reflectOrigin( double& x, double& y )
// Reflect the point (<x>, <y>) about the origin
{
	x = -x;
	y = -y;
}

void
Transforms::reflectXeqY( Point2D& point )
// Reflecte <point> about the line x=y
{
	point.setXY( point.getY(), point.getX() );
}

void
Transforms::reflectXeqY( double& x, double& y )
// Reflect the point ( <x>, <y> ) about the line x=y
{
	double temp;
	temp = x;
	x = y;
	y = temp;
}
	
void
Transforms::reflectPoint( Point2D& point, const Point2D& about )
// Reflect <point> about <about>
{
	// Translate <point> so that <about> is the origin
	translate( point, -about );

	// Reflect <point> as though <about> was the origin
	reflectOrigin( point );

	// Translate the new <point> back by <about> to reset the origin position
	translate( point, about );
}

void
Transforms::reflectPoint( double& x, double& y, double ax, double ay )
// Reflect the point (<x>, <y>) about the point (<ax>, <ay>)
{
	Point2D point( x, y ), about( ax, ay );
	reflectPoint( point, about );
	point.getXY( x, y );
}

void
Transforms::reflectXY( Point3D& point )
// Reflect <point> in the XY plane
{
	point.setZ( -point.getZ() );
}

void
Transforms::reflectXY( double& x, double& y, double& z )
// Reflect the point ( <x>, <y>, <z> ) in the XY plane
{
	z = -z;
}

void
Transforms::reflectXZ( Point3D& point )
// Reflect <point> in the XZ plane
{
	point.setY( -point.getY() );
}

void
Transforms::reflectXZ( double& x, double& y, double& z )
// Reflect the point ( <x>, <y>, <z> ) in the XZ plane
{
	y = -y;
}

void
Transforms::reflectYZ( Point3D& point )
// Reflect <point> in the YZ plane
{
	point.setX( -point.getX() );
}

void
Transforms::reflectYZ( double& x, double& y, double& z )
// Reflect the point ( <x>, <y>, <z> ) in the YZ plane
{
	x = -x;
}


Point2D
Transforms::project3Dto2D( const Point3D& pt3D, double l, double alpha )
// Project the 3D point <pt3D> onto a 2D coordinate system using the
// parameters <l> and <alpha>.  The projection assumes a right-handed
// 3D coordinate system.
{
	double xp, yp;
	xp = pt3D.getX() - l * cos(alpha) * pt3D.getZ();
	yp = pt3D.getY() - l * sin(alpha) * pt3D.getZ();
	return ( Point2D( xp, yp ) );
}