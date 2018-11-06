// TerrainBaseLayer.h - interface for TerrainBaseLayer class
//
// Developed by: Mike Childs
//      Started: 4/20/98

#ifndef _TERRAINBASELAYER_H_
#define _TERRAINBASELAYER_H_

#include "RasterPluginLayer.h"
#include "DoubleByteGridFile.h"
#include <string>
using namespace std;

class TerrainBaseLayer : public RasterPluginLayer
{
public:
	// Constructors/Destructors
	TerrainBaseLayer( int layerID, const char* strFilename, HINSTANCE hInst );
	virtual ~TerrainBaseLayer();

	// Overrides
    const char* getDescription() const;
    bool isVertical() const;
	bool load();
	void getBoundingRect( double& left, double& bottom, double& right, double& top ) const;
    long getImageHeight() const;
    long getImageWidth() const;
    void getProjection( PROJSYS& projSys, DATUM& datum, UNIT& unit, int& zone, double* pParams ) const;
    float getVerticalPixelScale() const;
    UNIT getVerticalUnits() const;

protected:
    // Overrides
    void getMinMaxSampleValue( float& min, float& max ) const;
    bool getElevation( long row, long col, float& elev ) const;

    // Helpers
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
    string  d_strDescription;
    string  d_strHeaderFileName;
    DoubleByteGridFile d_dataFile;
};

inline const char*
TerrainBaseLayer::getDescription() const
{
    return d_strDescription.c_str();
}

inline bool
TerrainBaseLayer::getElevation( long row, long col, float& elev ) const
{
    row = min( row, d_imageHeight - 1 );
    row = max( row, 0 );
    col = min( col, d_imageWidth - 1 );
    col = max( col, 0 );

    // Get the elevation and account for the reversed byte order
    elev = d_dataFile.getLittleEndianValue( row * d_imageWidth + col );
    return ( elev != d_noDataValue );
}

inline void
TerrainBaseLayer::getMinMaxSampleValue( float& min, float& max ) const
{
    min = d_minElevation;
    max = d_maxElevation;
}

inline float
TerrainBaseLayer::getVerticalPixelScale() const
{
    // XXX - This is just for geographic
    return ( d_horizontalSpacing / 0.000008333333 );
}

inline UNIT
TerrainBaseLayer::getVerticalUnits() const
{
    return METERS;
}

inline long
TerrainBaseLayer::getImageHeight() const
{
    return d_imageHeight;
}

inline long
TerrainBaseLayer::getImageWidth() const
{
    return d_imageWidth;
}

inline bool
TerrainBaseLayer::isVertical() const
{
    return true;
}


#endif