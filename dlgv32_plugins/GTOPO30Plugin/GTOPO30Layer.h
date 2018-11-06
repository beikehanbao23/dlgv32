// GTOPO30Layer.h - interface for GTOPO30Layer class
//
// Developed by: Mike Childs
//      Started: 4/20/98

#ifndef _GTOPO30LAYER_H_
#define _GTOPO30LAYER_H_

#include "RasterPluginLayer.h"
#include "DoubleByteGridFile.h"
#include <string>
using namespace std;

class GTOPO30Layer : public RasterPluginLayer
{
public:
	// Constructors/Destructors
	GTOPO30Layer( int layerID, const char* strFilename, HINSTANCE hInst );
	virtual ~GTOPO30Layer();

	// Overrides
	void getBoundingRect( double& left, double& bottom, double& right, double& top ) const;
    void getBadElevationColor( unsigned char& r, unsigned char& g, unsigned char& b ) const;
    bool getElevation( long row, long col, float& elev ) const;
    long getImageHeight() const;
    long getImageWidth() const;
    void getMinMaxSampleValue( float& min, float& max ) const;
    void getProjection( PROJSYS& projSys, DATUM& datum, UNIT& unit, int& zone, double* pParams ) const;
    float getVerticalPixelScale() const;
    UNIT getVerticalUnits() const;
    bool isVertical() const;
	bool load();
    bool showBadElevations() const;

protected:
    // Helpers
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
    string  d_strDataFileName;
    string  d_strProjectionFileName;
    DoubleByteGridFile d_dataFile;

    // Projection data
    PROJSYS d_projSys;
    DATUM   d_datum;
    UNIT    d_units;
};

inline void
GTOPO30Layer::getBadElevationColor( unsigned char& r, unsigned char& g, unsigned char& b ) const
{
    r = 0;
    g = 0;
    b = 255;
}

inline bool
GTOPO30Layer::getElevation( long row, long col, float& elev ) const
{
    row = min( row, d_imageHeight - 1 );
    row = max( row, 0 );
    col = min( col, d_imageWidth - 1 );
    col = max( col, 0 );

    // Get the elevation and account for the reversed byte order
    elev = d_dataFile.getBigEndianValue( row * d_imageWidth + col );
    return ( elev != d_noDataValue );
}

inline void
GTOPO30Layer::getMinMaxSampleValue( float& min, float& max ) const
{
    min = -407.0;
    max = 8752.0;
}

inline float
GTOPO30Layer::getVerticalPixelScale() const
{
    // Samples are spaced 1 kilometer apart
    return 1000.0F;
}

inline UNIT
GTOPO30Layer::getVerticalUnits() const
{
    return METERS;
}

inline long
GTOPO30Layer::getImageHeight() const
{
    return d_imageHeight;
}

inline long
GTOPO30Layer::getImageWidth() const
{
    return d_imageWidth;
}

inline bool
GTOPO30Layer::isVertical() const
{
    return true;
}

inline bool
GTOPO30Layer::showBadElevations() const
{
    return true;
}

#endif