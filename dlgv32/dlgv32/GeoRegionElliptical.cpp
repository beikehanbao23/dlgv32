// GeoRegionElliptical.cpp - implementation file for GeoRegionElliptical class
//
// Developed by: Mike Childs
//      Started: 2/28/97
//

#include "GeoRegionElliptical.h"
#include "CoordinateTransforms.h"

GeoRegionElliptical::GeoRegionElliptical()
: GeoRegion(), d_boundingRect(0,0,0,0)
{
}

GeoRegionElliptical::GeoRegionElliptical( const Rectangle2D& boundingRect )
: GeoRegion(), d_boundingRect(boundingRect)
{
}

CRgn*
GeoRegionElliptical::toCRgn( CDC* pDC ) const
{
	// Get a logical version of the bounding rectangle
	CRect logBoundRect = CoordinateTransforms::GndRefSystoLP( d_boundingRect );

	// Create an elliptical region
	CRgn* rgn = new CRgn;
	rgn->CreateEllipticRgnIndirect( &logBoundRect );

	return rgn;
}