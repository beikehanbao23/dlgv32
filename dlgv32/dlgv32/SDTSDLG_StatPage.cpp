// SDTSDLG_StatPage.cpp : implementation file
//

#include "stdafx.h"
#include "dlgv32.h"
#include "SDTSDLG_StatPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SDTSDLG_StatPage property page

IMPLEMENT_DYNCREATE(SDTSDLG_StatPage, CPropertyPage)

SDTSDLG_StatPage::SDTSDLG_StatPage() : CPropertyPage(SDTSDLG_StatPage::IDD)
{
	//{{AFX_DATA_INIT(SDTSDLG_StatPage)
	m_strNumDegLines = _T("");
	m_strNumLines = _T("");
	m_strNumAreas = _T("");
	m_strNumNodes = _T("");
	//}}AFX_DATA_INIT
    m_strNumPolygons = _T("");
}

SDTSDLG_StatPage::~SDTSDLG_StatPage()
{
}

void SDTSDLG_StatPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SDTSDLG_StatPage)
	DDX_Text(pDX, IDC_SDTSDLG_STAT_NODEGLINES, m_strNumDegLines);
	DDX_Text(pDX, IDC_SDTSDLG_STAT_NOLINES, m_strNumLines);
	DDX_Text(pDX, IDC_SDTSDLG_STAT_NUMAREAS, m_strNumAreas);
	DDX_Text(pDX, IDC_SDTSDLG_STAT_NONODES, m_strNumNodes);
	//}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_SDTSDLG_STAT_NOPOLYGONS, m_strNumPolygons);
}


BEGIN_MESSAGE_MAP(SDTSDLG_StatPage, CPropertyPage)
	//{{AFX_MSG_MAP(SDTSDLG_StatPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SDTSDLG_StatPage message handlers

void SDTSDLG_StatPage::SetValues( long numAreas, long numNodes, long numDegLines, 
                                  long numLines, long numPolygons )
{
    m_strNumAreas.Format( "%ld", numAreas );
    m_strNumNodes.Format( "%ld", numNodes );
    m_strNumDegLines.Format( "%ld", numDegLines );
    m_strNumLines.Format( "%ld", numLines );
    m_strNumPolygons.Format( "%ld", numPolygons );
}
