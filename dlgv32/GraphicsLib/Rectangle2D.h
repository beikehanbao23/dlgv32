// Rectangle2D.h - header file for Rectangle2D class
//
// Developed by: Mike Childs
//      Started: 10/18/96
//

#ifndef _Rectangle2D_H_
#define _Rectangle2D_H_

#include "Point2D.h"

class Rectangle2D
{
public:
	// Constructors
	Rectangle2D();
	Rectangle2D(double x1, double y1, double x2, double y2);
	Rectangle2D(const Rectangle2D& rect);

	// Operator overloads
	virtual Rectangle2D& operator=(const Rectangle2D& rect);
	virtual bool operator==(const Rectangle2D& rect);

	// Accessors/Modifiers
	void setPoints( const Point2D& pt1, const Point2D& pt2 );
	void setPoints( double x1, double y1, double x2, double y2 );
	void getPoints( double& x1, double&y1, double &x2, double &y2 ) const;
	void setLowerLeft( double x1, double y1 );
	void setLowerLeft( const Point2D& pt );
	void getLowerLeft( double& x1, double& y1 ) const;
	Point2D getLowerLeft() const;
	void setUpperRight( const Point2D& pt );
	void setUpperRight( double x2, double y2 );
	void getUpperRight( double& x2, double &y2 ) const;
	Point2D getUpperRight() const;
	double left() const;
	double right() const;
	double top() const;
	double bottom() const;
	Point2D getCenter() const;

	// Informative
	double width() const;
	double height() const;
	bool pointInRect( const Point2D& pt ) const;
	bool pointInRect( double x, double y ) const;
    bool isEmpty() const;
    bool isNormalized() const;
	bool isNull() const;

	// Transformers
	void inflateRect( double cx, double cy );
	void inflateRect( double cxy );
	void translate( const Point2D& by );
	void translate( double dx, double dy );
	void scale( double sx, double sy );
	void reflectXAxis();
	void reflectYAxis();
	void reflectOrigin();
	bool intersectRect( const Rectangle2D& rect1, const Rectangle2D& rect2 );
	void normalize();

protected:
	double d_x1, d_y1, d_x2, d_y2;
};

// Inline function definitions

inline void
Rectangle2D::setPoints( const Point2D& pt1, const Point2D& pt2 )
{
	double x1, y1, x2, y2;
	pt1.getXY( x1, y1 );
	pt2.getXY( x2, y2 );
	setPoints( x1, y1, x2, y2 );
}

inline void
Rectangle2D::setPoints(double x1, double y1, double x2, double y2)
{
	d_x1 = x1;
	d_y1 = y1;
	d_x2 = x2;
	d_y2 = y2;
}

inline void
Rectangle2D::getPoints(double& x1, double& y1, double& x2, double& y2) const
{
	x1 = d_x1;
	y1 = d_y1;
	x2 = d_x2;
	y2 = d_y2;
}

inline void
Rectangle2D::setLowerLeft( const Point2D& pt )
{
	double x, y;
	pt.getXY( x, y );
	setLowerLeft( x, y );
}

inline void
Rectangle2D::setLowerLeft(double x1, double y1)
{
	d_x1 = x1;
	d_y1 = y1;
}

inline void
Rectangle2D::getLowerLeft(double& x1, double& y1) const
{
	x1 = d_x1;
	y1 = d_y1;
}

inline Point2D
Rectangle2D::getLowerLeft() const
{
	return Point2D( d_x1, d_y1 );
}

inline void
Rectangle2D::setUpperRight( const Point2D& pt )
{
	double x, y;
	pt.getXY( x, y );
	setUpperRight( x, y );
}

inline void
Rectangle2D::setUpperRight(double x2, double y2)
{
	d_x2 = x2;
	d_y2 = y2;
}

inline void
Rectangle2D::getUpperRight(double& x2, double& y2) const
{
	x2 = d_x2;
	y2 = d_y2;
}

inline Point2D
Rectangle2D::getUpperRight() const
{
	return Point2D( d_x2, d_y2 );
}

inline void
Rectangle2D::inflateRect( double cxy )
{
	inflateRect( cxy, cxy );
}

inline double
Rectangle2D::left() const
{
	return d_x1;
}

inline double
Rectangle2D::right() const
{
	return d_x2;
}

inline double
Rectangle2D::top() const
{
	return d_y2;
}

inline double
Rectangle2D::bottom() const
{
	return d_y1;
}

inline bool
Rectangle2D::isEmpty() const
{
    return ( width() <= 0.0 || height() <= 0.0 );
}

inline bool
Rectangle2D::isNormalized() const
{
    return ( d_x1 <= d_x2 && d_y1 <= d_y2 );
}

inline bool
Rectangle2D::isNull() const
{
	return ( ( d_x1 == 0.0 ) && ( d_x2 == 0.0 ) && ( d_y1 == 0.0 ) && ( d_y2 == 0.0 ) );
}

#endif