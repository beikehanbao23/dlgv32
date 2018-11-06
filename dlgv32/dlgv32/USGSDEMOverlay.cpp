// USGSDEMOverlay.cpp - implementation of USGSDEMOverlay class
//
// Developed by: Mike Childs
//      Started: 2/11/98

#include "USGSDEMOverlay.h"
#include "CoordinateTransforms.h"
#include "LoadingDialog.h"
#include <fstream>
using namespace std;

// Projection includes
#include "ProjectionLib/GeographicProjection.h"
#include "ProjectionLib/StatePlaneProjection.h"
#include "ProjectionLib/UTMProjection.h"

// Construction
USGSDEMOverlay::USGSDEMOverlay( CString& strFilename )
: RasterOverlay( strFilename )
{
}

// Destruction
USGSDEMOverlay::~USGSDEMOverlay()
{
}

// Loading
BOOL
USGSDEMOverlay::load()
{
    // Create an input stream based on the filename
    ifstream dem;
    dem.open( getFilename(), ios::binary );

    // Abort if the DEM couldn't be successfully opened
    if ( !dem )
    {
        return FALSE;
    }

    try
    {
   	    // Create and initialize a dialog to display load progress
	    CLoadingDialog loadingDialog;
	    CString strTitle, strFilename;
	    strFilename = d_filename.Right( d_filename.GetLength() -
	   	                                d_filename.ReverseFind( '\\' ) - 1 );
	    strTitle = "Loading " + strFilename + "...";
	    loadingDialog.SetWindowText( strTitle );
	    long size = d_grid.read( dem, true );
        long spacing = size / 100;
	    loadingDialog.d_progressControl.SetRange( 0, 100 );
	    loadingDialog.d_progressControl.SetPos( 0 );

        // Read in the DEM
        long curPos = size;
        while ( 0 < ( curPos = d_grid.read( dem, true ) ) )
        {
            if ( 0 == ( curPos % spacing ) )
            {
                loadingDialog.d_progressControl.OffsetPos( 1 );
            }
        }
    }
    catch ( ... )
    {
        AfxMessageBox( "An error occurred while reading the USGS DEM.  The "
                       "load will be aborted." );
        dem.close();
        return FALSE;
    }

    dem.close();

    // Get the DEM header
    const DEMHeader& hdr = d_grid.getHeader();

    // Set the vertical units
    switch ( hdr.getElevationUnits() )
    {
        case 1:
            setVerticalUnits( US_FEET, d_grid.getHeader().getSpatialResZ() );
            break;
        case 2:
            setVerticalUnits( METERS,  d_grid.getHeader().getSpatialResZ() );
            break;
    }

    // Get the horizontal datum
    DATUM d = NO_DATUM;
    switch ( hdr.getHorizDatum() )
    {
        case 1:
            d = NAD27;
            break;
        case 2:
            d = WGS_72;
            break;
        case 3:
            d = WGS_84;
            break;            
        case 4:
            d = NAD83;
            break;
        case 5:
            d = OLD_HAWAIIAN_MEAN;
            break;
        case 6:
            d = PUERTO_RICO;
            break;
        default:
            // Unsupported datum
            AfxMessageBox( "This DEM had an invalid datum code.  The load "
                           "will be aborted." );
            return FALSE;
    }

    // Get the units
    UNIT u = UNKNOWN_UNIT;
    switch ( hdr.getGroundRefSysUnits() )
    {
        case 0:
            u = RADIANS;
            break;
        case 1:
            u = US_FEET;
            break;
        case 2:
            u = METERS;
            break;
        case 3:
            u = ARC_SECONDS;
            break;
        default:
            // Unknown units
            return false;
    }

    // Get the projection system
    switch ( hdr.getGroundRefSysCode() )
    {
        case 0:
            d_pProjection = new GeographicProjection( d, u );
            break;
        case 1:
            d_pProjection = new UTMProjection( hdr.getGroundRefSysZone(), d, u );
            break;
        case 2:
            d_pProjection = new StatePlaneProjection( hdr.getGroundRefSysZone(), d, u );
            break;
        default:
            // Unsupported projection system
            AfxMessageBox( "This DEM had an unsupported projection system code. "
                           "The load will be aborted." );
            return FALSE;
    }

    // Set the global projection system if one isn't already set
    if ( NULL == CoordinateTransforms::getProjection() )
    {
        CoordinateTransforms::setProjection( d_pProjection );
    }

    // Calculate the bounding rectangle
    calculateBoundingRect();

    // Do stuff to cope with global projection
    handleProjectionChanged();

    // Recalculate the global min/max values
    recalculateMinMaxSampleValue();

    // Set the loaded flag
    d_loaded = TRUE;

    return TRUE;
}

void 
USGSDEMOverlay::calculateBoundingRect()
{
    // Get the corners
    const DEMPointVector& corners = d_grid.getHeader().getDEMCorners();

    // Get southwest corner and northeast corner
    DEMPoint swCorner = corners[0];
    DEMPoint neCorner = corners[2];

    // Make the overlay pixel is point
    double left   = swCorner.getX();
    double right  = neCorner.getX();
    double bottom = swCorner.getY();
    double top    = neCorner.getY();
    double hSpacing = ( right - left ) / getImageWidth();
    double vSpacing = ( top - bottom ) / getImageHeight();
    left   -= hSpacing / 2.0;
    right  -= hSpacing / 2.0;
    top    += vSpacing / 2.0;
    bottom += vSpacing / 2.0;
    

    d_boundingRect.setPoints( left, bottom, right, top );
}

bool
USGSDEMOverlay::getElevation( long row, long col, float& elev ) const
{
    row = min( row, getImageHeight() - 1 );
    row = max( row, 0 );
    col = min( col, getImageWidth() - 1 );
    col = max( col, 0 );

    elev = d_grid.getElevation( col, row );

    return ( d_grid.getMissingDataValue() != elev );
}

CString
USGSDEMOverlay::getDescription() const
{
    CString strDesc;
    strDesc.Format( "<%s> %s", getFilenameWithoutPath(), d_grid.getHeader().getQuadName().c_str() );
    strDesc.TrimRight();
    return strDesc;
}