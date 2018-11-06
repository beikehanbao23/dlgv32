// GeoRegionPoly.cpp - implementation file for GeoRegionPoly class
//
// Developed by: Mike Childs
//      Started: 2/26/97
//

#include "GeoRegionPoly.h"
#include "CoordinateTransforms.h"
#include "GraphicsLib/Point2D.h"

GeoRegionPoly::GeoRegionPoly()
: GeoRegion(), d_points(0), d_numPoints(0)
{
}

GeoRegionPoly::GeoRegionPoly( Point2D* pts, UINT numPoints )
: GeoRegion(), d_numPoints(numPoints)
{
	d_points = new Point2D[numPoints];

	for ( int i = 0; i < numPoints; i++ )
	{
		d_points[i] = pts[i];
	}
}

GeoRegionPoly::GeoRegionPoly( const GeoRegionPoly& polyRgn )
{
	operator=( polyRgn );
}

GeoRegionPoly::~GeoRegionPoly()
{
	delete[] d_points;
}

GeoRegionPoly& GeoRegionPoly::operator=( const GeoRegionPoly& polyRgn )
{
	if ( &polyRgn != this )
	{
		// Deallocate memory used by points
		delete[] d_points;

		d_numPoints = polyRgn.d_numPoints;
		d_points = new Point2D[d_numPoints];

		for ( int i = 0; i < d_numPoints; i++ )
		{
			d_points[i] = polyRgn.d_points[i];
		}
	}

	return *this;
}

CRgn* GeoRegionPoly::toCRgn( CDC* pDC ) const
{
	// Create an array of CPoint objects which contain the points
	// of the region mapped to the device coordinate system
	CPoint* pts = new CPoint[d_numPoints];
	double x, y;
	for ( int i = 0; i < d_numPoints; i++ )
	{
		d_points[i].getXY( x, y );
		CoordinateTransforms::GndRefSystoLP( x, y );
		pts[i] = CPoint( x, y );
		pDC->LPtoDP( &pts[i] );
	}

	// Create a CRgn out of the points
	CRgn* rgn = new CRgn;
	rgn->CreatePolygonRgn( pts, d_numPoints, WINDING );

	// Retrieve space used by logical points
	delete[] pts;

	return rgn;
}

void GeoRegionPoly::setPoints( Point2D* pts, UINT numPoints )
{
	// Deallocate space used by current points
	delete[] d_points;

	d_numPoints = numPoints;
	d_points = new Point2D[numPoints];
	for ( int i = 0; i < numPoints; i++ )
	{
		d_points[i] = pts[i];
	}
}
