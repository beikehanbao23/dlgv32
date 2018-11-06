// SDTSDLG_IdenPage.cpp : implementation file
//

#include "stdafx.h"
#include "dlgv32.h"
#include "SDTSDLG_IdenPage.h"

// SDTS includes
#include "sdtsxx/builder/sb_Ident.hxx"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SDTSDLG_IdenPage property page

IMPLEMENT_DYNCREATE(SDTSDLG_IdenPage, CPropertyPage)

SDTSDLG_IdenPage::SDTSDLG_IdenPage() 
: CPropertyPage(SDTSDLG_IdenPage::IDD)
{
	//{{AFX_DATA_INIT(SDTSDLG_IdenPage)
	m_strStandardID = _T("");
	m_strCreationDate = _T("");
	m_strDataID = _T("");
	m_strDataStructure = _T("");
	m_strMapDate = _T("");
	m_strProfileID = _T("");
	m_strProfileDocRef = _T("");
	m_strProfileVer = _T("");
	m_strStandardDocRef = _T("");
	m_strStandardVer = _T("");
	m_strTitle = _T("");
	m_strComposites = _T("");
	m_strExtSpatialRef = _T("");
	m_strFeaturesLevel = _T("");
	m_strRaster = _T("");
	m_strScale = _T("");
	m_strVectorGeometry = _T("");
	m_strVectorTopology = _T("");
	m_strProjection = _T("");
	//}}AFX_DATA_INIT
}

void
SDTSDLG_IdenPage::SetIden( sb_Ident* pIdent )
{
    // Initialize the data members from the ident module
    m_strStandardID = pIdent->getStandardIdent().c_str();
    m_strCreationDate = pIdent->getDataSetCreationDate().c_str();
    m_strDataID = pIdent->getDataID().c_str();
    m_strDataStructure = pIdent->getDataStruct().c_str();
    m_strMapDate = pIdent->getMapDate().c_str();
    m_strProfileID = pIdent->getProfileIdent().c_str();
    m_strProfileDocRef = pIdent->getProfileDocRef().c_str();
    m_strStandardDocRef = pIdent->getStandardDocRef().c_str();
    m_strStandardVer = pIdent->getStandardVer().c_str();
    m_strTitle = pIdent->getTitle().c_str();
    m_strComposites = pIdent->getComposites().c_str();
    m_strExtSpatialRef.Format( "%ld", pIdent->getExternSpatRef() );
    m_strFeaturesLevel.Format( "%ld", pIdent->getFeaturesLevel() );
    m_strRaster = pIdent->getRaster().c_str();
    m_strScale.Format( "%ld", pIdent->getScale() );
    m_strVectorGeometry = pIdent->getVectorGeom().c_str();
    m_strVectorTopology = pIdent->getVectorTopol().c_str();
}

void
SDTSDLG_IdenPage::SetProjection( const CString& strProjection )
{
    m_strProjection = strProjection;
}

SDTSDLG_IdenPage::~SDTSDLG_IdenPage()
{
}

void SDTSDLG_IdenPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SDTSDLG_IdenPage)
	DDX_Text(pDX, IDC_SDTDDLG_IDEN_STANDARDID, m_strStandardID);
	DDX_Text(pDX, IDC_SDTSDLG_IDEN_CREATIONDATE, m_strCreationDate);
	DDX_Text(pDX, IDC_SDTSDLG_IDEN_DATAID, m_strDataID);
	DDX_Text(pDX, IDC_SDTSDLG_IDEN_DATASTRUCT, m_strDataStructure);
	DDX_Text(pDX, IDC_SDTSDLG_IDEN_MAPDATE, m_strMapDate);
	DDX_Text(pDX, IDC_SDTSDLG_IDEN_PROFILEID, m_strProfileID);
	DDX_Text(pDX, IDC_SDTSDLG_IDEN_PROFILEDOCREF, m_strProfileDocRef);
	DDX_Text(pDX, IDC_SDTSDLG_IDEN_PROFILEVER, m_strProfileVer);
	DDX_Text(pDX, IDC_SDTSDLG_IDEN_STANDARDDOCREF, m_strStandardDocRef);
	DDX_Text(pDX, IDC_SDTSDLG_IDEN_STANDARDVER, m_strStandardVer);
	DDX_Text(pDX, IDC_SDTSDLG_IDEN_TITLE, m_strTitle);
	DDX_Text(pDX, IDC_SDTSDLG_IDEN_COMPOSITES, m_strComposites);
	DDX_Text(pDX, IDC_SDTSDLG_IDEN_EXTSPATIALREF, m_strExtSpatialRef);
	DDX_Text(pDX, IDC_SDTSDLG_IDEN_FEATURESLEVEL, m_strFeaturesLevel);
	DDX_Text(pDX, IDC_SDTSDLG_IDEN_RASTER, m_strRaster);
	DDX_Text(pDX, IDC_SDTSDLG_IDEN_SCALE, m_strScale);
	DDX_Text(pDX, IDC_SDTSDLG_IDEN_VECTORGEOMETRY, m_strVectorGeometry);
	DDX_Text(pDX, IDC_SDTSDLG_IDEN_VECTORTOPOLOGY, m_strVectorTopology);
	DDX_Text(pDX, IDC_SDTSDLG_IDEN_PROJECTION, m_strProjection);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SDTSDLG_IdenPage, CPropertyPage)
	//{{AFX_MSG_MAP(SDTSDLG_IdenPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
