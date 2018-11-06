// SDTSDLG_DataQualityPage.cpp : implementation file
//

#include "stdafx.h"
#include "dlgv32.h"
#include "SDTSDLG_DataQualityPage.h"

// SDTS includes
#include "sdtsxx/builder/sb_AttAccuracy.hxx"
#include "sdtsxx/builder/sb_Completeness.hxx"
#include "sdtsxx/builder/sb_Lineage.hxx"
#include "sdtsxx/builder/sb_LogicalConsis.hxx"
#include "sdtsxx/builder/sb_PosAccuracy.hxx"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SDTSDLG_DataQualityPage property page

IMPLEMENT_DYNCREATE(SDTSDLG_DataQualityPage, CPropertyPage)

SDTSDLG_DataQualityPage::SDTSDLG_DataQualityPage() 
: CPropertyPage(SDTSDLG_DataQualityPage::IDD), m_ppDQAA(NULL), m_ppDQCG(NULL),
  m_ppDQHL(NULL), m_ppDQLC(NULL), m_ppDQPA(NULL)
{
	//{{AFX_DATA_INIT(SDTSDLG_DataQualityPage)
	m_strDQAA = _T("");
	m_strDQCG = _T("");
	m_strDQHL = _T("");
	m_strDQLC = _T("");
	m_strDQPA = _T("");
	//}}AFX_DATA_INIT

    m_strDQAA = m_strDQCG = m_strDQHL = m_strDQLC = m_strDQPA = _T("Not yet loaded");
}

SDTSDLG_DataQualityPage::~SDTSDLG_DataQualityPage()
{
}

void 
SDTSDLG_DataQualityPage::SetValues( sb_AttAccuracy** ppDQAA, sb_Completeness** ppDQCG,
                                    sb_Lineage** ppDQHL, sb_LogicalConsis** ppDQLC,
                                    sb_PosAccuracy** ppDQPA )
{
    m_ppDQAA = ppDQAA;
    m_ppDQCG = ppDQCG;
    m_ppDQHL = ppDQHL;
    m_ppDQLC = ppDQLC;
    m_ppDQPA = ppDQPA;
}

void SDTSDLG_DataQualityPage::DoDataExchange(CDataExchange* pDX)
{
    // Make sure values have been set
    ASSERT( m_ppDQAA && m_ppDQCG && m_ppDQHL && m_ppDQLC && m_ppDQPA );

    if ( NULL != *m_ppDQAA )
    {
        m_strDQAA = (*m_ppDQAA)->getComment().c_str();
    }

    if ( NULL != *m_ppDQCG )
    {
        m_strDQCG = (*m_ppDQCG)->getComment().c_str();
    }

    if ( NULL != *m_ppDQHL )
    {
        m_strDQHL = (*m_ppDQHL)->getComment().c_str();
    }

    if ( NULL != *m_ppDQLC )
    {
        m_strDQLC = (*m_ppDQLC)->getComment().c_str();
    }

    if ( NULL != *m_ppDQPA )
    {
        m_strDQPA = (*m_ppDQPA)->getComment().c_str();
    }

	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SDTSDLG_DataQualityPage)
	DDX_Text(pDX, IDC_SDTSDLG_DQAA, m_strDQAA);
	DDX_Text(pDX, IDC_SDTSDLG_DQCG, m_strDQCG);
	DDX_Text(pDX, IDC_SDTSDLG_DQHL, m_strDQHL);
	DDX_Text(pDX, IDC_SDTSDLG_DQLC, m_strDQLC);
	DDX_Text(pDX, IDC_SDTSDLG_DQPA, m_strDQPA);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SDTSDLG_DataQualityPage, CPropertyPage)
	//{{AFX_MSG_MAP(SDTSDLG_DataQualityPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SDTSDLG_DataQualityPage message handlers
