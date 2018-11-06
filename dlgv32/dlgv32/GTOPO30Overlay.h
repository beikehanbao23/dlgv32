// GTOPO30Overlay.h - interface for GTOPO30Overlay class
//
// Developed by: Mike Childs
//      Started: 2/12/98

#ifndef _GTOPO30OVERLAY_H_
#define _GTOPO30OVERLAY_H_

#include "RasterOverlay.h"
#include "DoubleByteGridFile.h"

class GTOPO30Overlay : public RasterOverlay
{
public:
	// Constructors/Destructors
	GTOPO30Overlay( CString& strFilename );
	virtual ~GTOPO30Overlay();

	// Overrides
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
    bool showBadElevations() const;

    // Helper functions
    bool parseHeaderFile();
    bool parseProjectionFile();

private:
    // Member data
    long    d_imageWidth;
    long    d_imageHeight;
    short   d_noDataValue;
    double  d_leftLongitude;
    double  d_topLatitude;
    double  d_horizontalSpacing;
    double  d_verticalSpacing;
    CString d_strDataFileName;
    CString d_strProjectionFileName;
    DoubleByteGridFile d_dataFile;
};

inline float
GTOPO30Overlay::getVerticalPixelScale() const
{
    // Samples are spaced 1 kilometer apart
    return 1000.0F;
}

inline void
GTOPO30Overlay::getMinMaxSampleValue( float& min, float& max ) const
{
    min = -407.0;
    max = 8752.0;
}

inline long
GTOPO30Overlay::getImageHeight() const
{
    return d_imageHeight;
}

inline long
GTOPO30Overlay::getImageWidth() const
{
    return d_imageWidth;
}

inline void 
GTOPO30Overlay::getProjectionMeshSize( short& width, short& height ) const
{
    width = getImageWidth() / 40;
    height = getImageHeight() / 40;
}

inline bool
GTOPO30Overlay::isVertical() const
{
    return true;
}

inline bool
GTOPO30Overlay::getElevation( long row, long col, float& elev ) const
{
    row = min( row, d_imageHeight - 1 );
    row = max( row, 0 );
    col = min( col, d_imageWidth - 1 );
    col = max( col, 0 );

    // Get the elevation and account for the reversed byte order
    elev = d_dataFile.getBigEndianValue( row * d_imageWidth + col );
    return ( elev != d_noDataValue );
}

inline COLORREF
GTOPO30Overlay::getBadElevationColor() const
{
    return RGB(0,0,255);
}

inline bool
GTOPO30Overlay::showBadElevations() const
{
    return true;
}

#endif
