// GeoRegion.h - header file for GeoRegion class
//
// Developed by: Mike Childs
//      Started: 2/26/97
//

#ifndef _GEOREGION_H_
#define _GEOREGION_H_

#include "StdAfx.h"

class GeoRegion
{
public:
	// Constructor
	GeoRegion( int combineMode = RGN_OR ) : d_combineMode(combineMode) {};
	
	// Overrideables
	virtual ~GeoRegion() { };
	virtual CRgn* toCRgn( CDC* pDC ) const = 0;

	// Accessors/Modifiers
	int  getCombineMode() const;
	void setCombineMode( int combineMode );

protected:
	int d_combineMode;
};

inline int
GeoRegion::getCombineMode() const
{
	return d_combineMode;
}

inline void
GeoRegion::setCombineMode( int combineMode )
{
	d_combineMode = combineMode;
}

#endif