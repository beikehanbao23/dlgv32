// GTOPO30Layer.cpp - implementation for GTOPO30Layer class
//
// Developed by: Mike Childs
//      Started: 4/20/98

#include "GTOPO30Layer.h"
#include <fstream>
#include <math.h>
#include <stdlib.h>
using namespace std;

// Constructors/Destructors
GTOPO30Layer::GTOPO30Layer( int layerID, const char* strFilename, HINSTANCE hInst )
: RasterPluginLayer( layerID, strFilename, hInst )
{
    // Get the name of the data file to be loaded and the projection file
    char strDrive[_MAX_DRIVE];
    char strDir[_MAX_DIR];
    char strFname[_MAX_FNAME];
    string strBase;
    _splitpath( strFilename, strDrive, strDir, strFname, NULL );
    strBase = strDrive;
    strBase += strDir;
    strBase += strFname;
    d_strDataFileName = strBase;
    d_strDataFileName += ".dem";
    d_strProjectionFileName = strBase;
    d_strProjectionFileName += ".prj";
}

GTOPO30Layer::~GTOPO30Layer()
{
}

// Overrides
bool
GTOPO30Layer::load()
{
    // Parse the header file
    if ( !parseHeaderFile() )
    {
        // Abort load
        ::MessageBox( ::GetActiveWindow(),
                      "An error occured while reading the GTOPO30 header file. The load will be aborted.",
                      "ERROR", MB_OK );
        return false;
    }

    // Parse the projection file
    if ( !parseProjectionFile() )
    {
        ::MessageBox( ::GetActiveWindow(), 
                      "An error occured while processing the projection file.  A geographic projection in WGS84 will be used.",
                      "WARNING", MB_OK );
    }

    // Create a file mapping of the data file
    if ( !d_dataFile.create( d_strDataFileName.c_str() ) )
    {
        string strMessage = "Error opening data file: ";
        strMessage += d_strDataFileName;
        strMessage += ". Load will be aborted.";
        ::MessageBox( ::GetActiveWindow(), strMessage.c_str(), "ERROR", MB_OK );
        return false;
    }

    return true;
}

void 
GTOPO30Layer::getBoundingRect( double& left, double& bottom, double& right, double& top ) const
{
    // Calculate bounding rect using pixel is point
    left   = d_leftLongitude - d_horizontalSpacing / 2.0;
    top    = d_topLatitude   + d_verticalSpacing   / 2.0;
    right  = left + d_horizontalSpacing * d_imageWidth;
    bottom = top  - d_verticalSpacing * d_imageHeight;
}

// Helpers
bool
GTOPO30Layer::parseHeaderFile()
{
    // Open the header file
    ifstream hdrFile;
    hdrFile.open( getFilename().c_str() );

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
GTOPO30Layer::parseProjectionFile()
{
    PROJSYS p = GEO;
    DATUM d = WGS_84;
    UNIT u = ARC_DEGREES;
    bool bSuccess = true;

    // Open the header file
    ifstream prjFile;
    prjFile.open( d_strProjectionFileName.c_str() );

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

    // Save the projection
    d_projSys = p;
    d_units = u;
    d_datum = d;

    return bSuccess;
}

void
GTOPO30Layer::getProjection( PROJSYS& projSys, DATUM& datum, UNIT& unit, int& zone, double* pParams ) const
{
    projSys = d_projSys;
    datum = d_datum;
    unit = d_units;

    if ( PS == projSys )
    {
        pParams[5] = -71000000;
    }
}