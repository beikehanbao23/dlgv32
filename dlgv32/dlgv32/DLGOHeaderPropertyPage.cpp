// DLGOHeaderPropertyPage.cpp : implementation file
//

#include "stdafx.h"
#include "dlgv32.h"
#include "DLGOHeaderPropertyPage.h"
#include "CoordinateTransforms.h"
#include "dlg/DLGHeader.hxx"
#include "ProjectionLib/Projection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DLGOHeaderPropertyPage property page

IMPLEMENT_DYNCREATE(DLGOHeaderPropertyPage, CPropertyPage)

DLGOHeaderPropertyPage::DLGOHeaderPropertyPage() 
: CPropertyPage(DLGOHeaderPropertyPage::IDD)
{
	//{{AFX_DATA_INIT(DLGOHeaderPropertyPage)
	d_strBanner = _T("");
	d_strDateQualifier = _T("");
	d_strDCUName = _T("");
	d_strLevelCode = _T("");
	d_strResolution = _T("");
	d_strSourceDate = _T("");
	d_strSourceScale = _T("");
	d_strVDatum = _T("");
	d_strProjection = _T("");
	//}}AFX_DATA_INIT
}

DLGOHeaderPropertyPage::DLGOHeaderPropertyPage( const DLGHeader& header,
                                                const Projection* pProj ) 
: CPropertyPage(DLGOHeaderPropertyPage::IDD)
{
	// Initialize the dialog box variables
	d_strBanner = header.getBanner().c_str();
	d_strDateQualifier = header.getDateQualifier().c_str();
	d_strDCUName = header.getDCU_Name().c_str();
	d_strLevelCode.Format( "%d", header.getLevelCode() );
	d_strResolution.Format( "%g", header.getResolution() );;
	d_strSourceDate = header.getOrigSourceMaterialDate().c_str();
	d_strSourceScale.Format( "%d", header.getOrigSourceMaterialScale() );

  // Get the vertical datum
  switch ( header.getVerticalDatum() )
  {
    case 0:
      d_strVDatum = "NAVD29";
      break;
    case 1:
      d_strVDatum = "NAVD87";
      break;
    default:
      d_strVDatum.Format( "%d", header.getVerticalDatum() );
      break;
  }

  // Get the projection string
  ASSERT( NULL != pProj );
  d_strProjection = pProj->toString().c_str();
}

DLGOHeaderPropertyPage::~DLGOHeaderPropertyPage()
{
}

void DLGOHeaderPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DLGOHeaderPropertyPage)
	DDX_Text(pDX, IDC_DLGO_BANNER, d_strBanner);
	DDX_Text(pDX, IDC_DLGO_DATE_QUALIFIER, d_strDateQualifier);
	DDX_Text(pDX, IDC_DLGO_DCU_NAME, d_strDCUName);
	DDX_Text(pDX, IDC_DLGO_LEVEL_CODE, d_strLevelCode);
	DDX_Text(pDX, IDC_DLGO_RESOLUTION, d_strResolution);
	DDX_Text(pDX, IDC_DLGO_SOURCE_DATE, d_strSourceDate);
	DDX_Text(pDX, IDC_DLGO_SOURCE_SCALE, d_strSourceScale);
	DDX_Text(pDX, IDC_DLGO_VDATUM, d_strVDatum);
	DDX_Text(pDX, IDC_DLGO_HEADER_PROJECTION, d_strProjection);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DLGOHeaderPropertyPage, CPropertyPage)
	//{{AFX_MSG_MAP(DLGOHeaderPropertyPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLGOHeaderPropertyPage message handlers
