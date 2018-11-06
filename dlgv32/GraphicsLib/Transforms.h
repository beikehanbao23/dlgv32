// Tranforms.h - header file for Transforms class
//
// Developed by: Mike Childs
//      Started: 2/5/97
//

#ifndef _TRANSFORMS_H_
#define _TRANSFORMS_H_

#include "Point2D.h"
#include "Point3D.h"

class Transforms
{
public:
	static void translate( Point2D& point, const Point2D& by );
	static void translate( Point2D& point, double dx, double dy );
	static void translate( double& x, double& y, double dx, double dy );
	static void translate( Point3D& point, const Point3D& by );
	static void translate( double& x, double& y, double& z,
						   double dx, double dy, double dz );
	static void rotate( Point2D& point, double theta, 
		                const Point2D& about = Point2D(0,0) );
	static void rotate( double& x, double& y, double theta, 
		                double ax = 0, double ay = 0 );
	static void rotateX( Point3D& point, double theta, 
		                 const Point3D& about = Point3D(0,0,0) );
	static void rotateX( double& x, double& y, double& z, double theta,
		                 double ax = 0, double ay = 0, double az = 0 );
	static void rotateY( Point3D& point, double theta, 
		                 const Point3D& about = Point3D(0,0,0) );
	static void rotateY( double& x, double& y, double& z, double theta,
		                 double ax = 0, double ay = 0, double az = 0 );
	static void rotateZ( Point3D& point, double theta, 
		                 const Point3D& about = Point3D(0,0,0) );
	static void rotateZ( double& x, double& y, double& z, double theta,
		                 double ax = 0, double ay = 0, double az = 0 );
	static void scale( Point2D& point, double scaleX, double scaleY, 
		               const Point2D& about = Point2D(0,0) );
	static void scale( double& x, double& y, double scaleX, double scaleY, 
		               double ax, double ay );
	static void scale( Point3D& point, double scaleX, double scaleY, double scaleZ,
		               const Point3D& about = Point3D(0,0,0) );
	static void scale( double& x, double& y, double& z, 
					   double sx, double sy, double sz,
		               double ax, double ay, double az );
	static void reflectXAxis( Point2D& point );
	static void reflectXAxis( double& x, double& y );
	static void reflectYAxis( Point2D& point );
	static void reflectYAxis( double& x, double& y );
	static void reflectOrigin( Point2D& point );
	static void reflectOrigin( double& x, double& y );
	static void reflectXeqY( Point2D& point );
	static void reflectXeqY( double& x, double& y );
	static void reflectPoint( Point2D& point, const Point2D& about );
	static void reflectPoint( double& x, double& y, double ax, double ay );
	static void reflectXY( Point3D& point );
	static void reflectXY( double& x, double& y, double& z );
	static void reflectXZ( Point3D& point );
	static void reflectXZ( double& x, double& y, double& z );
	static void reflectYZ( Point3D& point ); 
	static void reflectYZ( double& x, double& y, double& z );
	static Point2D project3Dto2D( const Point3D& pt3D, double l, double alpha );
};

#endif