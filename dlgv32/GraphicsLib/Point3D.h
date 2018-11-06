// Point3D.h - header file for Point3D class
//
// Developed by: Mike Childs
//      Started: 2/9/97
//

#ifndef _POINT3D_H_
#define _POINT3D_H_

class Point3D
{
public:
	Point3D();
    Point3D( double x, double y, double z );
    Point3D( const Point3D& point );
    virtual ~Point3D();

    virtual bool operator==( const Point3D& point ) const;
    virtual bool operator<( const Point3D& point ) const;
	virtual bool operator!=( const Point3D& point ) const;
    virtual Point3D& operator=( const Point3D& point );
	virtual Point3D operator+( const Point3D& point ) const;
	virtual Point3D operator-( const Point3D& point ) const;
	virtual Point3D operator*( double scalar ) const;
	virtual Point3D operator-() const;

    // Accessors
    double getX() const;
    double getY() const;
	double getZ() const;
    void   getXYZ( double& x, double& y, double& z ) const;

    // Modifiers
    void setX( double x );
    void setY( double y );
	void setZ( double z );
    void setXYZ( double x, double y, double z );

protected:
    double d_x, d_y, d_z;
};

// Inline Function Definitions

inline double
Point3D::getX() const
{
   return d_x;
}

inline void
Point3D::setX( double x )
{
   d_x = x;
}

inline double
Point3D::getY() const
{
   return d_y;
}

inline void
Point3D::setY( double y )
{
   d_y = y;
}

inline double
Point3D::getZ() const
{
	return d_z;
}

inline void
Point3D::setZ( double z )
{
	d_z = z;
}

inline void
Point3D::getXYZ( double& x, double& y, double& z ) const
{
   x = d_x;
   y = d_y;
   z = d_z;
}

inline void
Point3D::setXYZ( double x, double y, double z )
{
   d_x = x;
   d_y = y;
   d_z = z;
}

#endif
