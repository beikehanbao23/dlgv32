// TerrainBaseLayer.cpp - implementation for TerrainBaseLayer class
//
// Developed by: Mike Childs
//      Started: 4/20/98

#include "TerrainBaseLayer.h"
#include <fstream>
#include <math.h>
#include <stdlib.h>
using namespace std;

// Constructors/Destructors
TerrainBaseLayer::TerrainBaseLayer( int layerID, const char* strFilename, HINSTANCE hInst )
: RasterPluginLayer( layerID, strFilename, hInst ), d_noDataValue(-9999)
{
    // Get the name of the data file to be loaded and the projection file
    char strDrive[_MAX_DRIVE];
    char strDir[_MAX_DIR];
    char strFname[_MAX_FNAME];
    _splitpath( strFilename, strDrive, strDir, strFname, NULL );
    d_strHeaderFileName = strDrive;
    d_strHeaderFileName += strDir;
    d_strHeaderFileName += strFname;
    d_strHeaderFileName += ".hdr";
}

TerrainBaseLayer::~TerrainBaseLayer()
{
}

// Overrides
bool 
TerrainBaseLayer::load()
{
    // Parse the header file
    if ( !parseHeaderFile() )
    {
        // Abort load
        ::MessageBox( ::GetActiveWindow(), 
                      "An error occured while reading the TerrainBase header file. The load will be aborted.",
                      "ERROR", MB_OK );
        return false;
    }

    // Create a file mapping of the data file
    if ( !d_dataFile.create( getFilename().c_str() ) )
    {
        string strMessage = "Error opening data file: ";
        strMessage += getFilename();
        strMessage += ". Load will be aborted.";
        ::MessageBox( ::GetActiveWindow(), strMessage.c_str(), "ERROR", MB_OK );
        return false;
    }

    return true;
}

void 
TerrainBaseLayer::getBoundingRect( double& left, double& bottom, double& right, double& top ) const
{
    // Calculate bounding rect using pixel is point
    left   = d_left - d_horizontalSpacing / 2.0;
    top    = d_top  + d_verticalSpacing   / 2.0;
    right  = left + d_horizontalSpacing * d_imageWidth;
    bottom = top  - d_verticalSpacing * d_imageHeight;
}

// Helpers
bool
TerrainBaseLayer::parseHeaderFile()
{
    // Open the header file
    ifstream hdrFile;
    hdrFile.open( d_strHeaderFileName.c_str() );

    if ( !hdrFile )
    {
        return false;
    }

    // Parse the file
    char strName[41];
    char strValue[81];
    char strTemp[3];

    // Read the file title
    hdrFile.get( strName, 40, '=' );
    hdrFile.get( strTemp, 2 );
    hdrFile.get( strValue, 80 );
    d_strDescription = strValue;

    // Read the palette type
    hdrFile.get( strName, 40, '=' );
    hdrFile.get( strTemp, 2 );
    hdrFile.get( strValue, 80 );

    // Read the data type
    hdrFile.get( strName, 40, '=' );
    hdrFile.get( strTemp, 2 );
    hdrFile.get( strValue, 80 );

    // Read the data byte order
    hdrFile.get( strName, 40, '=' );
    hdrFile.get( strTemp, 2 );
    hdrFile.get( strValue, 80 );

    // Read the upper map y
    hdrFile.get( strName, 40, '=' );
    hdrFile.get( strTemp, 2 );
    hdrFile.get( strValue, 80 );
    d_top = atof( strValue );

    // Read the lower map y
    hdrFile.get( strName, 40, '=' );
    hdrFile.get( strTemp, 2 );
    hdrFile.get( strValue, 80 );
    d_bottom = atof( strValue );

    // Read the left map x
    hdrFile.get( strName, 40, '=' );
    hdrFile.get( strTemp, 2 );
    hdrFile.get( strValue, 80 );
    d_left = atof( strValue );

    // Read the right map x
    hdrFile.get( strName, 40, '=' );
    hdrFile.get( strTemp, 2 );
    hdrFile.get( strValue, 80 );
    d_right = atof( strValue );

    // Read the number of rows
    hdrFile.get( strName, 40, '=' );
    hdrFile.get( strTemp, 2 );
    hdrFile.get( strValue, 80 );
    d_imageHeight = atol( strValue );

    // Read the number of columns
    hdrFile.get( strName, 40, '=' );
    hdrFile.get( strTemp, 2 );
    hdrFile.get( strValue, 80 );
    d_imageWidth = atol( strValue );

    // Read the grid size(x)
    hdrFile.get( strName, 40, '=' );
    hdrFile.get( strTemp, 2 );
    hdrFile.get( strValue, 80 );
    d_horizontalSpacing = atof( strValue );

    // Read the grid size(y)
    hdrFile.get( strName, 40, '=' );
    hdrFile.get( strTemp, 2 );
    hdrFile.get( strValue, 80 );
    d_verticalSpacing = atof( strValue );

    // Read the grid units
    hdrFile.get( strName, 40, '=' );
    hdrFile.get( strTemp, 2 );
    hdrFile.get( strValue, 80 );

    // Read the grid origin
    hdrFile.get( strName, 40, '=' );
    hdrFile.get( strTemp, 2 );
    hdrFile.get( strValue, 80 );

    // Read the grid cell registration
    hdrFile.get( strName, 40, '=' );
    hdrFile.get( strTemp, 2 );
    hdrFile.get( strValue, 80 );

    // Read the map projection
    hdrFile.get( strName, 40, '=' );
    hdrFile.get( strTemp, 2 );
    hdrFile.get( strValue, 80 );

    // Read the missing flag
    hdrFile.get( strName, 40, '=' );
    hdrFile.get( strTemp, 2 );
    hdrFile.get( strValue, 80 );
    d_noDataValue = atoi( strValue );

    // Read the max elevation
    hdrFile.get( strName, 40, '=' );
    hdrFile.get( strTemp, 2 );
    hdrFile.get( strValue, 80 );
    d_maxElevation = atoi( strValue );

    // Read the min Elevation
    hdrFile.get( strName, 40, '=' );
    hdrFile.get( strTemp, 2 );
    hdrFile.get( strValue, 80 );
    d_minElevation = atoi( strValue );

    // Read the elevation unit
    hdrFile.get( strName, 40, '=' );
    hdrFile.get( strTemp, 2 );
    hdrFile.get( strValue, 80 );

    // Close the file
    hdrFile.close();

    return true;
}

void
TerrainBaseLayer::getProjection( PROJSYS& projSys, DATUM& datum, UNIT& unit, int& zone, double* pParams ) const
{
    projSys = GEO;
    datum = WGS_84;
    unit = ARC_DEGREES;
}