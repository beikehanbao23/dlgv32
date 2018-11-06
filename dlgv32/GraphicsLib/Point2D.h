// Point2D.h - header file for Point2D class
//
// Developed by: Mike Childs
//      Started: 2/5/97
//

#ifndef _POINT2D_H_
#define _POINT2D_H_

class Point2D
{
public:
	// Constructors/Destructors
	Point2D();
    Point2D( double x, double y );
    Point2D( const Point2D& point );
    virtual ~Point2D();

	// Operator overloads
    virtual bool operator==( const Point2D& point ) const;
    virtual bool operator<( const Point2D& point ) const;
	virtual bool operator!=( const Point2D& point ) const;
    virtual Point2D& operator=( const Point2D& point );
	virtual Point2D operator+( const Point2D& point ) const;
	virtual Point2D operator-( const Point2D& point ) const;
	virtual Point2D operator*( double scalar ) const;
	virtual Point2D operator-() const;

    // Accessors
    double getX() const;
    double getY() const;
    void   getXY( double& x, double& y ) const;

    // Modifiers
    void setX( double x );
    void setY( double y );
    void setXY( double x, double y );

protected:
    double d_x, d_y;
};

// Inline Function Definitions

inline double
Point2D::getX() const
{
   return d_x;
}

inline void
Point2D::setX( double x )
{
   d_x = x;
}

inline double
Point2D::getY() const
{
   return d_y;
}

inline void
Point2D::setY( double y )
{
   d_y = y;
}

inline void
Point2D::getXY( double& x, double& y ) const
{
   x = d_x;
   y = d_y;
}

inline void
Point2D::setXY( double x, double y )
{
   d_x = x;
   d_y = y;
}

#endif
