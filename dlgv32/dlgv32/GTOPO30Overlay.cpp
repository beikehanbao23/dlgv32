// GTOPO30Overlay.cpp - implementation of GTOPO30Overlay class
//
// Developed by: Mike Childs
//      Started: 2/12/98

#include "GTOPO30Overlay.h"
#include "CoordinateTransforms.h"
#include "ProjectionLib/GeographicProjection.h"
#include "ProjectionLib/PolarStereographicProjection.h"
#include <fstream>
#include <math.h>
using namespace std;

// Constructors/Destructors
GTOPO30Overlay::GTOPO30Overlay( CString& strFilename )
: RasterOverlay( strFilename )
{
    // Get the name of the data file to be loaded and the projection file
    CString strBase = strFilename.Left( strFilename.ReverseFind( '.' ) + 1 );
    d_strDataFileName = strBase + "dem";
    d_strProjectionFileName = strBase + "prj";
}

GTOPO30Overlay::~GTOPO30Overlay()
{
}

// Overrides
BOOL 
GTOPO30Overlay::load()
{
    // Parse the header file
    if ( !parseHeaderFile() )
    {
        // Abort load
        AfxMessageBox( "An error occured while reading the GTOPO30 header file. "
                       "The load will be aborted." );
        return FALSE;
    }

    // Parse the projection file
    if ( !parseProjectionFile() )
    {
        AfxMessageBox( "An error occured while processing the projection "
                       "file.  A geographic projection in WGS84 will be used." );
    }

    // Create a file mapping of the data file
    if ( !d_dataFile.create( d_strDataFileName ) )
    {
        CString strMessage = "Error opening data file: ";
        strMessage += d_strDataFileName;
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
GTOPO30Overlay::calculateBoundingRect()
{
    // Calculate bounding rect using pixel is point
    double left   = d_leftLongitude - d_horizontalSpacing / 2.0;
    double top    = d_topLatitude   + d_verticalSpacing   / 2.0;
    double right  = left + d_horizontalSpacing * d_imageWidth;
    double bottom = top  - d_verticalSpacing * d_imageHeight;
    d_boundingRect.setPoints( left, bottom, right, top );
}

// Helpers
bool
GTOPO30Overlay::parseHeaderFile()
{
    // Open the header file
    ifstream hdrFile;
    hdrFile.open( getFilename() );

    if ( !hdrFile )
    {
        return false;
    }

    // Parse the file
    char strName[30];
    char strValue[30];

    // Read the byte order
    hdrFile >> strName >> strValue;

    // Read the layout
    hdrFile >> strName >> strValue;

    // Read the number of rows
    hdrFile >> strName >> strValue;
    d_imageHeight = atol( strValue );

    // Read the number of columns
    hdrFile >> strName >> strValue;
    d_imageWidth = atol( strValue );

    // Read the number of bands
    hdrFile >> strName >> strValue;

    // Read the number of bits per pixel
    hdrFile >> strName >> strValue;

    // Read the band row bytes
    hdrFile >> strName >> strValue;

    // Read the total row bytes
    hdrFile >> strName >> strValue;

    // Read the band gap bytes
    hdrFile >> strName >> strValue;

    // Read the no data value
    hdrFile >> strName >> strValue;
    d_noDataValue = atoi( strValue );

    // Read the upper left x coordinate
    hdrFile >> strName >> strValue;
    d_leftLongitude = atof( strValue );

    // Read the upper left y coordinate
    hdrFile >> strName >> strValue;
    d_topLatitude = atof( strValue );

    // Read the x pixel spacing
    hdrFile >> strName >> strValue;
    d_horizontalSpacing = atof( strValue );

    // Read the y pixel spacing
    hdrFile >> strName >> strValue;
    d_verticalSpacing = atof( strValue );

    // Close the file
    hdrFile.close();

    return true;
}

bool
GTOPO30Overlay::parseProjectionFile()
{
    PROJSYS p = GEO;
    DATUM d = WGS_84;
    UNIT u = ARC_DEGREES;
    bool bSuccess = true;

    // Open the header file
    ifstream prjFile;
    prjFile.open( d_strProjectionFileName );

    if ( prjFile )
    {
        // Parse the file
        char strName[30];
        char strValue[30];

        // Read in the projection type
        prjFile >> strName >> strValue;
        if ( 0 == strcmp( strValue, "POLAR" ) )
        {
            p = PS;
        }

        // Read in the datum
        prjFile >> strName >> strValue;

        // Read in the vertical units
        prjFile >> strName >> strValue;

        // Read in the horizontal units
        prjFile >> strName >> strValue;
        if ( 0 == strcmp( strValue, "METERS" ) )
        {
            u = METERS;
        }

        // Read in the Spheroid
        prjFile >> strName >> strValue;

        // Read in the X-shift
        double xShift;
        prjFile >> strName >> xShift;

        // Read in the Y-shift
        double yShift;
        prjFile >> strName >> yShift;

        prjFile.close();
    }
    else
    {
        bSuccess = false;
    }

    // Create the projection
    switch ( p )
    {
        case GEO:
            d_pProjection = new GeographicProjection( d, u );
            break;
        case PS:
            d_pProjection = new PolarStereographicProjection( 0, -71000000, 0.0, 0.0, 0, 0, d, u );
            break;
    }
    
    // Setup the global projection if one hasn't been setup yet
    if ( NULL == CoordinateTransforms::getProjection() )
    {
        CoordinateTransforms::setProjection( d_pProjection );
    }

    return bSuccess;
}
