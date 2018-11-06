// USGSDEMOverlay.h - interface for USGSDEMOverlay class
//
// Developed by: Mike Childs
//      Started: 2/11/98

#ifndef _USGSDEMOVERLAY_H_
#define _USGSDEMOVERLAY_H_

#include "RasterOverlay.h"

// DEM library includes
#include "dem/DEMGrid.hxx"

class USGSDEMOverlay : public RasterOverlay
{
public:
	// Constructors/Destructors
	USGSDEMOverlay( CString& strFilename );
	virtual ~USGSDEMOverlay();

	// Overrides
    CString getDescription() const;
    bool isVertical() const;
	BOOL load();
	void calculateBoundingRect();
    long getImageHeight() const;
    long getImageWidth() const;

protected:
    // Overrides
    void getMinMaxSampleValue( float& min, float& max ) const;
    bool getElevation( long row, long col, float& elev ) const;

private:
    // Member data
    DEMGrid   d_grid;
};

inline void
USGSDEMOverlay::getMinMaxSampleValue( float& min, float& max ) const
{
    min = d_grid.getHeader().getMinimumElev();
    max = d_grid.getHeader().getMaximumElev();
}

inline long
USGSDEMOverlay::getImageHeight() const
{
    return d_grid.getHeight();
}

inline long
USGSDEMOverlay::getImageWidth() const
{
    return d_grid.getWidth();
}

inline bool
USGSDEMOverlay::isVertical() const
{
    return true;
}

#endif