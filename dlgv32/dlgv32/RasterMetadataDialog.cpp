// RasterMetadataDialog.cpp : implementation file
//

#include "stdafx.h"
#include "dlgv32.h"
#include "RasterMetadataDialog.h"
#include "RasterOverlay.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RasterMetadataDialog dialog


RasterMetadataDialog::RasterMetadataDialog(CWnd* pParent /*=NULL*/)
	: CDialog(RasterMetadataDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(RasterMetadataDialog)
	d_strDescription = _T("");
	d_strHeight = _T("");
	d_strMaxElevation = _T("");
	d_strMaxElevationLabel = _T("");
	d_strMinElevation = _T("");
	d_strMinElevationLabel = _T("");
	d_strVerticalUnits = _T("");
	d_strWidth = _T("");
	d_strVerticalUnitsLabel = _T("");
	d_strProjection = _T("");
	//}}AFX_DATA_INIT

    // Create the dialog
    Create( RasterMetadataDialog::IDD, pParent );
}

void
RasterMetadataDialog::setOverlay( RasterOverlay* pOverlay )
{
    d_strDescription = pOverlay->getDescription();
    d_strHeight.Format( "%ld", pOverlay->getImageHeight() );
    d_strProjection = pOverlay->getNativeProjection()->toString().c_str();
    d_strWidth.Format( "%ld", pOverlay->getImageWidth() );

    // If this is a vertical overlay, set up the vertical fields
    if ( pOverlay->isVertical() )
    {
        float min, max;
        pOverlay->getMinMaxSampleValue( min, max );
        d_strMinElevation.Format( "%g %s", min * pOverlay->d_verticalSpatialRes, 
                                  pOverlay->getVerticalUnitString() );
        d_strMaxElevation.Format( "%g %s", max * pOverlay->d_verticalSpatialRes, 
                                  pOverlay->getVerticalUnitString() );
        d_strVerticalUnits = pOverlay->getVerticalUnitString();
        d_strMinElevationLabel = "Minimum Elevation:";
        d_strMaxElevationLabel = "Maximum Elevation:";
        d_strVerticalUnitsLabel = "Vertical Units:";
    }

    // Put the new values in the labels
    UpdateData( FALSE );
}

void RasterMetadataDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RasterMetadataDialog)
	DDX_Text(pDX, IDC_RASTER_DESCRIPTION, d_strDescription);
	DDX_Text(pDX, IDC_RASTER_HEIGHT, d_strHeight);
	DDX_Text(pDX, IDC_RASTER_MAX_ELEVATION, d_strMaxElevation);
	DDX_Text(pDX, IDC_RASTER_MAX_ELEVATION_LABEL, d_strMaxElevationLabel);
	DDX_Text(pDX, IDC_RASTER_MIN_ELEVATION, d_strMinElevation);
	DDX_Text(pDX, IDC_RASTER_MIN_ELEVATION_LABEL, d_strMinElevationLabel);
	DDX_Text(pDX, IDC_RASTER_VERTICAL_UNITS, d_strVerticalUnits);
	DDX_Text(pDX, IDC_RASTER_WIDTH, d_strWidth);
	DDX_Text(pDX, IDC_RASTER_VERTICAL_UNITS_LABEL, d_strVerticalUnitsLabel);
	DDX_Text(pDX, IDC_RASTER_PROJECTION, d_strProjection);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RasterMetadataDialog, CDialog)
	//{{AFX_MSG_MAP(RasterMetadataDialog)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RasterMetadataDialog message handlers

void RasterMetadataDialog::OnClose() 
{
    // Just hide the window
    ShowWindow( SW_HIDE );
}
