// GeoRegionElliptical.h - header file for GeoRegionElliptical class
//
// Developed by: Mike Childs
//      Started: 2/27/97
//

#ifndef _GEOREGIONELLIPTICAL_H_
#define _GEOREGIONELLIPTICAL_H_

#include "StdAfx.h"
#include "GeoRegion.h"
#include "GraphicsLib/Rectangle2D.h"

class GeoRegionElliptical : public GeoRegion
{
public:
	// Constructor/Destructor
	GeoRegionElliptical();
	GeoRegionElliptical( const Rectangle2D& boundingRect );

	// Modifiers
	void setBoundingRect( const Rectangle2D& boundingRect );

	// Overrides
	CRgn* toCRgn( CDC* pDC ) const;

private:
	Rectangle2D d_boundingRect;
};

inline void
GeoRegionElliptical::setBoundingRect( const Rectangle2D& boundingRect )
{
	d_boundingRect = boundingRect;
}

#endif