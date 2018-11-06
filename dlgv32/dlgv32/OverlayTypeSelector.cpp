// OverlayTypeSelector.cpp : implementation file
//

#include "stdafx.h"
#include "dlgv32.h"
#include "OverlayTypeSelector.h"
#include "OverlayFactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// OverlayTypeSelector dialog


OverlayTypeSelector::OverlayTypeSelector(CWnd* pParent /*=NULL*/)
: CDialog(OverlayTypeSelector::IDD, pParent), d_pTypeInfoList(NULL),
  d_selectedIndex(0)
{
	//{{AFX_DATA_INIT(OverlayTypeSelector)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void OverlayTypeSelector::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(OverlayTypeSelector)
	DDX_Control(pDX, IDC_OVERLAY_TYPE_LIST, d_typesListBox);
	//}}AFX_DATA_MAP
	// Clear list control

  ASSERT( NULL != d_pTypeInfoList );
  d_typesListBox.ResetContent();
	
	// Add filenames of all overlays to list box
  int curPos = 0;
  for ( vector<OverlayTypeInfo*>::const_iterator i = d_pTypeInfoList->begin();
        i != d_pTypeInfoList->end(); i++ )
	{
		d_typesListBox.InsertString( curPos++, (*i)->d_strName.c_str() );
	}

  // Select the appropriate element
  d_typesListBox.SetCurSel( d_selectedIndex );
}


BEGIN_MESSAGE_MAP(OverlayTypeSelector, CDialog)
	//{{AFX_MSG_MAP(OverlayTypeSelector)
	ON_LBN_SELCHANGE(IDC_OVERLAY_TYPE_LIST, OnSelchangeOverlayTypeList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// OverlayTypeSelector message handlers

void OverlayTypeSelector::OnSelchangeOverlayTypeList() 
{
  // Update the selected index
  d_selectedIndex = d_typesListBox.GetCurSel();
}
