// OverlaySelector.cpp : implementation file
//

#include "stdafx.h"
#include "dlgv32.h"
#include "OverlaySelector.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// OverlaySelector dialog


OverlaySelector::OverlaySelector(CWnd* pParent /*=NULL*/)
	: CDialog(OverlaySelector::IDD, pParent), d_pOverlays(NULL),
	  d_numSelected(0), d_pSelected(0)
{
	//{{AFX_DATA_INIT(OverlaySelector)
	d_combineMode = -1;
	//}}AFX_DATA_INIT
}

OverlaySelector::~OverlaySelector()
{
	delete[] d_pSelected;
}

void OverlaySelector::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(OverlaySelector)
	DDX_Control(pDX, IDOK, d_okButton);
	DDX_Control(pDX, IDC_DESELECT_ALL, d_deselectAllButton);
	DDX_Control(pDX, IDC_SELECT_ALL_OVERLAYS, d_selectAllButton);
	DDX_Control(pDX, IDC_OVERLAYS_TO_CLIP_LIST, d_overlaysList);
	DDX_Radio(pDX, IDC_COMBO_MODE, d_combineMode);
	//}}AFX_DATA_MAP

	// Clear list control
	d_overlaysList.ResetContent();

	// Return if the overlays haven't been set
	if ( NULL == d_pOverlays )
	{
		return;
	}
	
	// Add filenames of all overlays to list box
  int curPos = 0;
  for ( list<GeographicOverlay*>::iterator i = d_pOverlays->begin();
        i != d_pOverlays->end(); i++ )
	{
		CString text;
		if ( (*i)->getShow() )
		{
			text = "(Displayed) ";
		}
		else
		{
			text = "  (Hidden)   ";
		}

		text += (*i)->getDescription();
		d_overlaysList.InsertString( curPos++, text );
	}
}


BEGIN_MESSAGE_MAP(OverlaySelector, CDialog)
	//{{AFX_MSG_MAP(OverlaySelector)
	ON_BN_CLICKED(IDC_SELECT_ALL_OVERLAYS, OnSelectAllOverlays)
	ON_BN_CLICKED(IDC_DESELECT_ALL, OnDeselectAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// OverlaySelector message handlers

void OverlaySelector::setOverlays( list<GeographicOverlay*>& overlays )
{
	d_pOverlays = &overlays;
}

void OverlaySelector::OnSelectAllOverlays() 
{
	// Select all of the overlays
	d_overlaysList.SetSel( -1, TRUE );	
}

void OverlaySelector::OnDeselectAll() 
{
	// Deselect all of the overlays
	d_overlaysList.SetSel( -1, FALSE );	
}

void OverlaySelector::OnOK() 
{
	// Get number of items selected
	d_numSelected = d_overlaysList.GetSelCount();
	if ( d_numSelected > 0 )
	{
		d_pSelected = new int[d_numSelected];
		d_overlaysList.GetSelItems( d_numSelected, d_pSelected );
	}
	
	CDialog::OnOK();
}

void OverlaySelector::getSelected( int*& pSelected, int& numSelected )
{
	pSelected = d_pSelected;
	numSelected = d_numSelected;
}