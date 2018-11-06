// DLGOCategoryPropertyPage.cpp : implementation file
//

#include "stdafx.h"
#include "dlgv32.h"
#include "DLGOCategoryPropertyPage.h"
#include "dlg/DLGHeader.hxx"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DLGOCategoryPropertyPage property page

IMPLEMENT_DYNCREATE(DLGOCategoryPropertyPage, CPropertyPage)

DLGOCategoryPropertyPage::DLGOCategoryPropertyPage() 
: CPropertyPage(DLGOCategoryPropertyPage::IDD)
{
	//{{AFX_DATA_INIT(DLGOCategoryPropertyPage)
	d_strActualAreas = _T("");
	d_strActualLines = _T("");
	d_strActualNodes = _T("");
	d_strALLinkage = _T("");
	d_strANLinkage = _T("");
	d_strAreaCoordList = _T("");
	d_strAreasRef = _T("");
	d_strCategoryID = _T("");
	d_strCategoryName = _T("");
	d_strFormatCodes = _T("");
	d_strLineCoordList = _T("");
	d_strLinesRef = _T("");
	d_strNALinkage = _T("");
	d_strNLLinkage = _T("");
	d_strNodesRef = _T("");
	//}}AFX_DATA_INIT
}

DLGOCategoryPropertyPage::DLGOCategoryPropertyPage( const DLGHeader& header ) 
: CPropertyPage(DLGOCategoryPropertyPage::IDD)
{
  ASSERT( header.getNumCategories() == 1 );

  // Get the first category (we currently assume only one category per DLG-O)
  DLGCategory cat;
  header.getCategoryInfo( 0, cat );

  // Populate the data fields
  d_strActualAreas.Format( "%ld", cat.numActualAreas );
  d_strActualLines.Format( "%ld", cat.numActualLines );
  d_strActualNodes.Format( "%ld", cat.numActualNodes );
  d_strALLinkage.Format( "%ld", cat.areaToLineLinkFlag );
  d_strANLinkage.Format( "%ld", cat.areaToNodeLinkFlag );
  d_strAreaCoordList.Format( "%ld", cat.areaCoordListFlag );
  d_strAreasRef.Format( "%ld", cat.numAreasReferenced );
  d_strCategoryID.Format( "%ld", cat.id );
  d_strCategoryName = cat.name.c_str();
  d_strFormatCodes.Format( "%ld", cat.formatCodes );
  d_strLineCoordList.Format( "%ld", cat.lineCoordListFlag );
  d_strLinesRef.Format( "%ld", cat.numLinesReferenced );
  d_strNALinkage.Format( "%ld", cat.nodeToAreaLinkFlag );
  d_strNLLinkage.Format( "%ld", cat.nodeToLineLinkFlag );
  d_strNodesRef.Format( "%ld", cat.numNodesReferenced );
}

DLGOCategoryPropertyPage::~DLGOCategoryPropertyPage()
{
}

void DLGOCategoryPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DLGOCategoryPropertyPage)
	DDX_Text(pDX, IDC_DLGO_ACTUAL_AREAS, d_strActualAreas);
	DDX_Text(pDX, IDC_DLGO_ACTUAL_LINES, d_strActualLines);
	DDX_Text(pDX, IDC_DLGO_ACTUAL_NODES, d_strActualNodes);
	DDX_Text(pDX, IDC_DLGO_AL_LINKAGE, d_strALLinkage);
	DDX_Text(pDX, IDC_DLGO_AN_LINKAGE, d_strANLinkage);
	DDX_Text(pDX, IDC_DLGO_AREA_COORD_LIST, d_strAreaCoordList);
	DDX_Text(pDX, IDC_DLGO_AREAS_REF, d_strAreasRef);
	DDX_Text(pDX, IDC_DLGO_CATEGORY_ID, d_strCategoryID);
	DDX_Text(pDX, IDC_DLGO_CATEGORY_NAME, d_strCategoryName);
	DDX_Text(pDX, IDC_DLGO_FORMAT_CODES, d_strFormatCodes);
	DDX_Text(pDX, IDC_DLGO_LINE_COORD_LIST, d_strLineCoordList);
	DDX_Text(pDX, IDC_DLGO_LINES_REF, d_strLinesRef);
	DDX_Text(pDX, IDC_DLGO_NA_LINKAGE, d_strNALinkage);
	DDX_Text(pDX, IDC_DLGO_NL_LINKAGE, d_strNLLinkage);
	DDX_Text(pDX, IDC_DLGO_NODES_REFERENCED, d_strNodesRef);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DLGOCategoryPropertyPage, CPropertyPage)
	//{{AFX_MSG_MAP(DLGOCategoryPropertyPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLGOCategoryPropertyPage message handlers
