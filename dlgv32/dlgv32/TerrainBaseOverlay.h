// TerrainBaseOverlay.h - interface for TerrainBaseOverlay class
//
// Developed by: Mike Childs
//      Started: 3/11/98

#ifndef _TERRAINBASEOVERLAY_H_
#define _TERRAINBASEOVERLAY_H_

#include "RasterOverlay.h"
#include "DoubleByteGridFile.h"

class TerrainBaseOverlay : public RasterOverlay
{
public:
	// Constructors/Destructors
	TerrainBaseOverlay( CString& strFilename );
	virtual ~TerrainBaseOverlay();

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
    void getProjectionMeshSize( short& width, short& height ) const;
    float getVerticalPixelScale() const;
    COLORREF getBadElevationColor() const;

    // Helper functions
    bool parseHeaderFile();

private:
    // Member data
    long    d_imageWidth;
    long    d_imageHeight;
    short   d_minElevation;
    short   d_maxElevation;
    short   d_noDataValue;
    double  d_left, d_right, d_top, d_bottom;
    double  d_horizontalSpacing;
    double  d_verticalSpacing;
    CString d_strDescription;
    CString d_strHeaderFileName;
    DoubleByteGridFile d_dataFile;
};

inline CString
TerrainBaseOverlay::getDescription() const
{
    return CString( "<" + getFilenameWithoutPath() + "> " + d_strDescription );
}

inline float
TerrainBaseOverlay::getVerticalPixelScale() const
{
    // XXX - This is just for geographic
    return ( d_horizontalSpacing / 0.000008333333 );
}

inline void
TerrainBaseOverlay::getMinMaxSampleValue( float& min, float& max ) const
{
    min = d_minElevation;
    max = d_maxElevation;
}

inline long
TerrainBaseOverlay::getImageHeight() const
{
    return d_imageHeight;
}

inline long
TerrainBaseOverlay::getImageWidth() const
{
    return d_imageWidth;
}

inline bool
TerrainBaseOverlay::isVertical() const
{
    return true;
}

inline bool
TerrainBaseOverlay::getElevation( long row, long col, float& elev ) const
{
    row = min( row, d_imageHeight - 1 );
    row = max( row, 0 );
    col = min( col, d_imageWidth - 1 );
    col = max( col, 0 );

    // Get the elevation and account for the reversed byte order
    elev = d_dataFile.getLittleEndianValue( row * d_imageWidth + col );
    return ( elev != d_noDataValue );
}

inline COLORREF
TerrainBaseOverlay::getBadElevationColor() const
{
    return RGB(0,0,255);
}

inline void 
TerrainBaseOverlay::getProjectionMeshSize( short& width, short& height ) const
{
    width = getImageWidth() / 25;
    height = getImageHeight() / 25;
}

#endif