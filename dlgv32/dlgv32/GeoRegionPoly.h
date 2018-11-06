// GeoRegionPoly.h - header file for GeoRegionPoly class
//
// Developed by: Mike Childs
//      Started: 2/26/97
//

#ifndef _GEOREGIONPOLY_H_
#define _GEOREGIONPOLY_H_

#include "StdAfx.h"
#include "GeoRegion.h"

class Point2D; // Forward declaration

class GeoRegionPoly : public GeoRegion
{
public:
	// Constructor/Destructor
	GeoRegionPoly();
	GeoRegionPoly( Point2D* pts, UINT numPoints );
	GeoRegionPoly( const GeoRegionPoly& polyRgn );
	~GeoRegionPoly();

	// Modifiers
	void setPoints( Point2D* pts, UINT numPoints );

	// Operator Overloads
	GeoRegionPoly& operator=( const GeoRegionPoly& polyRgn );

	// Overrides
	CRgn* toCRgn( CDC* pDC ) const;

private:
	Point2D* d_points;
	UINT     d_numPoints;
};

#endif