// PickDialog.cpp : implementation file
//

#include "stdafx.h"
#include "dlgv32.h"
#include "PickDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPickDialog dialog


CPickDialog::CPickDialog(CWnd* pParent /*=NULL*/)
: CDialog(CPickDialog::IDD, pParent), d_created(FALSE)
{
	//{{AFX_DATA_INIT(CPickDialog)
	d_ID = _T("");
	d_elemType = _T("");
	d_category = _T("");
	d_DCUName = _T("");
	d_strEntityDesc = _T("");
	//}}AFX_DATA_INIT
}


void CPickDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPickDialog)
	DDX_Control(pDX, IDC_ATT_CODE_LIST, d_attribCodeList);
	DDX_Text(pDX, IDC_ELEMENT_ID, d_ID);
	DDX_Text(pDX, IDC_ELEMENT_TYPE, d_elemType);
	DDX_Text(pDX, IDC_PICK_CATEGORY, d_category);
	DDX_Text(pDX, IDC_PICK_DCU_NAME, d_DCUName);
	DDX_Text(pDX, IDC_ENTITY_DESC, d_strEntityDesc);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPickDialog, CDialog)
	//{{AFX_MSG_MAP(CPickDialog)
	//}}AFX_MSG_MAP
	ON_COMMAND(IDC_CLOSE_PICK_DIALOG, OnClose)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPickDialog message handlers

CPickDialog::~CPickDialog()
{
	DestroyWindow();
}

void
CPickDialog::OnClose()
{
	ShowWindow( SW_HIDE );
}

void CPickDialog::clearColumns()
{
	// Delete all items from the major-minor code list
	d_attribCodeList.DeleteAllItems();

  // Make sure the columns are properly sized
  resizeColumns();
}

void CPickDialog::addMajorMinorPair( short major, short minor )
{
  // Convert the values to strings
  CString strMajor, strMinor;
  strMajor.Format( "%d", major );
  strMinor.Format( "%d", minor );

  // Add the strings to the list
  addRow( strMajor, strMinor );
}

void CPickDialog::addRow( const CString& strCol1, const CString& strCol2 )
{
	// Add text to list
	int count = d_attribCodeList.GetItemCount();
	d_attribCodeList.InsertItem( 0, strCol1 );
	d_attribCodeList.SetItemText( 0, 1, strCol2 );
  resizeColumns();
}

void CPickDialog::resizeColumns()
{
	// Determine width of the List View
	CRect listViewSize;
	int   width;
	d_attribCodeList.GetClientRect( &listViewSize );
	listViewSize.NormalizeRect();
	width = listViewSize.Width();

  // Iterate through the list to find the widest text string in each column
  int count = d_attribCodeList.GetItemCount();
  int maxWidthCol1 = 1;
  int maxWidthCol2 = 1;
  int curItemWidth = 0;
  for ( int i = 0; i < count; i++ )
  {
    curItemWidth = 
      d_attribCodeList.GetStringWidth( d_attribCodeList.GetItemText( i, 0 ) );
    maxWidthCol1 = max( maxWidthCol1, curItemWidth );
    curItemWidth =
      d_attribCodeList.GetStringWidth( d_attribCodeList.GetItemText( i, 1 ) );
    maxWidthCol2 = max( maxWidthCol2, curItemWidth );
  }

	// Modify the widths of the columns so the columns take an appropriate 
  // portion of the available width based on the width of the widest string in
  // each column
  int col1Width = width * maxWidthCol1 / ( maxWidthCol1 + maxWidthCol2 );
	LV_COLUMN column;
	column.mask = LVCF_WIDTH;
	column.cx   = col1Width;
	d_attribCodeList.SetColumn( 0, &column );
  column.cx = width - col1Width; // Add 1 if the width is odd
	d_attribCodeList.SetColumn( 1, &column );
}

void CPickDialog::initColumns()
{
	// Determine width of the List View
	CRect listViewSize;
	int   width;
	d_attribCodeList.GetClientRect( &listViewSize );
	listViewSize.NormalizeRect();
	width = listViewSize.Width();

	// Insert the columns into the ListView
	d_attribCodeList.InsertColumn( 0, "Major Code", LVCFMT_CENTER, width / 2, 1);
	d_attribCodeList.InsertColumn( 1, "Minor Code", LVCFMT_CENTER, 
                                 (width / 2) + width % 2 );		                                        

	// Make first column be centered
	LV_COLUMN column;
	column.mask = LVCF_FMT;
	column.fmt  = LVCFMT_CENTER;
	d_attribCodeList.SetColumn( 0, &column );
}

void CPickDialog::setEntityDesc( const CString& strEntityDesc )
{
  d_strEntityDesc = strEntityDesc;
}

BOOL CPickDialog::created() const
{
	return d_created;
}

BOOL CPickDialog::Create( UINT nIDTemplate, CWnd* pParentWnd)
{
	BOOL result = CDialog::Create( nIDTemplate, pParentWnd );

	// Setup the columns in the major-minor code list control
	initColumns();

	// Set the created flag
	d_created = TRUE;

	return result;
}

void CPickDialog::setColumnTitles( const CString& strCol1, const CString& strCol2 )
{
  // Set each column title
  setColumnTitle( 0, strCol1 );
  setColumnTitle( 1, strCol2 );
}

void CPickDialog::setColumnTitle(UINT column, const CString& strTitle)
{
  LV_COLUMN col;
  col.mask = LVCF_TEXT;
  col.cchTextMax = strTitle.GetLength() + 1;
  col.pszText = new char[col.cchTextMax];
  strcpy( col.pszText, strTitle );
  d_attribCodeList.SetColumn( column, &col );
  delete[] col.pszText;
}
