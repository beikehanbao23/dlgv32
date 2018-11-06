// DLGOControlPointsPropertyPage.cpp : implementation file
//

#include "stdafx.h"
#include "dlgv32.h"
#include "DLGOControlPointsPropertyPage.h"
#include "CoordinateTransforms.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DLGOControlPointsPropertyPage property page

IMPLEMENT_DYNCREATE(DLGOControlPointsPropertyPage, CPropertyPage)

DLGOControlPointsPropertyPage::DLGOControlPointsPropertyPage() 
: CPropertyPage(DLGOControlPointsPropertyPage::IDD)
{
	//{{AFX_DATA_INIT(DLGOControlPointsPropertyPage)
	d_strLabel = _T("");
	d_strID = _T("");
	d_strLatitude = _T("");
	d_strLongitude = _T("");
	d_strX = _T("");
	d_strY = _T("");
	d_strNumber = _T("");
	//}}AFX_DATA_INIT
}

DLGOControlPointsPropertyPage::DLGOControlPointsPropertyPage( const DLGHeader& header ) 
: CPropertyPage(DLGOControlPointsPropertyPage::IDD), d_header(header)
{
}

DLGOControlPointsPropertyPage::~DLGOControlPointsPropertyPage()
{
}

void DLGOControlPointsPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DLGOControlPointsPropertyPage)
	DDX_Control(pDX, IDC_DLGO_CONTROLPOINT_SPIN, d_spinner);
	DDX_Text(pDX, IDC_DLGO_CONTROLPOINT_LABEL, d_strLabel);
	DDX_Text(pDX, IDC_DLGO_CONTROLPOINT_ID, d_strID);
	DDX_Text(pDX, IDC_DLGO_CONTROLPOINT_LATITUDE, d_strLatitude);
	DDX_Text(pDX, IDC_DLGO_CONTROLPOINT_LONGITUDE, d_strLongitude);
	DDX_Text(pDX, IDC_DLGO_CONTROLPOINT_X, d_strX);
	DDX_Text(pDX, IDC_DLGO_CONTROLPOINT_Y, d_strY);
	DDX_Text(pDX, IDC_DLGO_CONTROLPOINT_NUMBER, d_strNumber);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DLGOControlPointsPropertyPage, CPropertyPage)
	//{{AFX_MSG_MAP(DLGOControlPointsPropertyPage)
	ON_NOTIFY(UDN_DELTAPOS, IDC_DLGO_CONTROLPOINT_SPIN, OnDeltaposDlgoControlpointSpin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLGOControlPointsPropertyPage message handlers

void DLGOControlPointsPropertyPage::OnDeltaposDlgoControlpointSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

  // Get the new control point index
  int newNum = pNMUpDown->iPos + pNMUpDown->iDelta;
  if ( newNum < 0 )
  {
    newNum = 0;
  }
  else if ( newNum >= d_header.getNumSidesInCellPoly() )
  {
    newNum = d_header.getNumSidesInCellPoly() - 1;
  }

  // Update the dialog
  d_strNumber.Format( "%d", newNum );
  updateControlPoints( newNum );

  *pResult = 0;
}

void DLGOControlPointsPropertyPage::initSpinner()
{
  // Initialize the control point spinner
  d_spinner.SetRange( 0, d_header.getNumSidesInCellPoly() - 1 );
  d_spinner.SetPos( 0 );
  d_strNumber = "0";
  updateControlPoints( 0 );
}

BOOL DLGOControlPointsPropertyPage::OnSetActive() 
{
  // Initialize the spinner
  initSpinner();
	
	return CPropertyPage::OnSetActive();
}

void DLGOControlPointsPropertyPage::updateControlPoints(int number)
{
  ASSERT( number >= 0 && number < d_header.getNumSidesInCellPoly() );

  // Get the control points
  DLGControlPoint controlPoint;
  d_header.getControlPointInfo( number, controlPoint );

  // Populate the dialog variables
  d_strID.Format( "%ld", controlPoint.id );
  d_strLabel = controlPoint.label.c_str();
  d_strLatitude = CoordinateTransforms::LatToString( controlPoint.latitude );
  d_strLongitude = CoordinateTransforms::LongitudeToString( controlPoint.longitude );
  d_strX.Format( "%.0f", controlPoint.x );
  d_strY.Format( "%.0f", controlPoint.y );

  // Update the dialog
  UpdateData( FALSE );
}
