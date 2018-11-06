// TerrainBaseOverlay.cpp - implementation for TerrainBaseOverlay class
//
// Developed by: Mike Childs
//      Started: 3/11/98

#include "TerrainBaseOverlay.h"
#include "ProjectionLib/GeographicProjection.h"
#include <fstream>
#include <math.h>
using namespace std;

// Constructors/Destructors
TerrainBaseOverlay::TerrainBaseOverlay( CString& strFilename )
: RasterOverlay( strFilename ), d_noDataValue(-9999)
{
    // Get the name of the data file to be loaded and the projection file
    CString strBase = strFilename.Left( strFilename.ReverseFind( '.' ) + 1 );
    d_strHeaderFileName = strBase + "hdr";
}

TerrainBaseOverlay::~TerrainBaseOverlay()
{
}

// Overrides
BOOL 
TerrainBaseOverlay::load()
{
    // Parse the header file
    if ( !parseHeaderFile() )
    {
        // Abort load
        AfxMessageBox( "An error occured while reading the TerrainBase header file. "
                       "The load will be aborted." );
        return FALSE;
    }

    // Create a file mapping of the data file
    if ( !d_dataFile.create( getFilename() ) )
    {
        CString strMessage = "Error opening data file: ";
        strMessage += getFilename();
        strMessage += ". Load will be aborted.";
        AfxMessageBox( strMessage );
        return FALSE;
    }

    // Calculate the bounding rectangle
    calculateBoundingRect();

    // Setup the global projection changed stuff
    handleProjectionChanged();

    // Recalculate the global min/max values
    recalculateMinMaxSampleValue();

    d_loaded = TRUE;
    return TRUE;
}

void 
TerrainBaseOverlay::calculateBoundingRect()
{
    // Calculate bounding rect using pixel is point
    double left   = d_left - d_horizontalSpacing / 2.0;
    double top    = d_top  + d_verticalSpacing   / 2.0;
    double right  = left + d_horizontalSpacing * d_imageWidth;
    double bottom = top  - d_verticalSpacing * d_imageHeight;
    d_boundingRect.setPoints( left, bottom, right, top );
}

// Helpers
bool
TerrainBaseOverlay::parseHeaderFile()
{
    // Open the header file
    ifstream hdrFile;
    hdrFile.open( d_strHeaderFileName );

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

    // Create the projection
    d_pProjection = new GeographicProjection( WGS_84 );

    // Setup the global projection if one hasn't been setup yet
    if ( NULL == CoordinateTransforms::getProjection() )
    {
        CoordinateTransforms::setProjection( d_pProjection );
    }

    return true;
}
