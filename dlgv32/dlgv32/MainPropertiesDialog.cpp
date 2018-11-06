// MainPropertiesDialog.cpp : implementation file
//

#include "stdafx.h"
#include "dlgv32.h"
#include "MainPropertiesDialog.h"
#include "Dlgv32View.h"
#include "Dlgv32Doc.h"
#include "OverlayFactory.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainPropertiesDialog dialog

CMainPropertiesDialog::CMainPropertiesDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMainPropertiesDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMainPropertiesDialog)
	//}}AFX_DATA_INIT

	d_pView = (CDlgv32View*)pParent;

	// Create the dialog
	Create( CMainPropertiesDialog::IDD, d_pView );
}

CMainPropertiesDialog::~CMainPropertiesDialog()
{
	DestroyWindow();
}

void CMainPropertiesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainPropertiesDialog)
	DDX_Control(pDX, IDC_PROPERTIES_BUTTON, d_propertiesButton);
	DDX_Control(pDX, IDC_OPTIONS_BUTTON, d_optionsButton);
	DDX_Control(pDX, IDC_CLOSE_OVERLAY, d_closeOverlayButton);
	DDX_Control(pDX, IDC_REMOVE_CLIPS, d_removeClipsButton);
	DDX_Control(pDX, IDC_HIDE_LINES_ALL, d_hideAllLinesButton);
	DDX_Control(pDX, IDC_HIDE_NODES_ALL, d_hideAllNodesButton);
	DDX_Control(pDX, IDC_HIDE_AREAS_ALL, d_hideAllAreasButton);
	DDX_Control(pDX, IDC_SHOW_OVERLAY, d_showOverlaysButton);
	DDX_Control(pDX, IDC_OVERLAY_LIST, d_overlaysList);
	//}}AFX_DATA_MAP

	return;
}


BEGIN_MESSAGE_MAP(CMainPropertiesDialog, CDialog)
	//{{AFX_MSG_MAP(CMainPropertiesDialog)
	ON_BN_CLICKED(IDC_PROPERTIES_BUTTON, OnPropertiesButton)
	ON_BN_CLICKED(IDC_OPTIONS_BUTTON, OnOptionsButton)
	ON_BN_CLICKED(IDC_SHOW_OVERLAY, OnShowOverlay)
	ON_LBN_SELCHANGE(IDC_OVERLAY_LIST, OnSelchangeOverlayList)
	ON_BN_CLICKED(IDC_CLOSE_OVERLAY, OnCloseOverlay)
	ON_BN_CLICKED(IDOK, OnDone)
	ON_BN_CLICKED(IDC_HIDE_AREAS_ALL, OnHideAreasAll)
	ON_BN_CLICKED(IDC_HIDE_NODES_ALL, OnHideNodesAll)
	ON_BN_CLICKED(IDC_HIDE_LINES_ALL, OnHideLinesAll)
	ON_BN_CLICKED(IDC_REMOVE_CLIPS, OnRemoveClips)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void
CMainPropertiesDialog::setOverlays( OverlayFactory& overlays )
{
	d_overlays = &overlays;

	// Clear list control
	d_overlaysList.ResetContent();
	
	// Add filenames of all overlays to list box
  list<GeographicOverlay*>& layers = overlays.getOverlays();
  int curPos = 0;
  for ( list<GeographicOverlay*>::iterator i = layers.begin();
        i != layers.end(); i++ )
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
	
  // Select the first overlay if at least one is loaded
  if ( d_overlays->getNumOverlaysLoaded() > 0 )
	{
    // Select the first element in the list
    d_overlaysList.SetSel( 0 );
    OnSelchangeOverlayList();
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMainPropertiesDialog message handlers

void CMainPropertiesDialog::OnPropertiesButton() 
{
	ASSERT( d_overlaysList.GetSelCount() == 1 );
	
	long currentSelection;

	// Get the index of the currently selected overlay
	currentSelection = d_overlaysList.GetCurSel();

	// If no list item is selected, then show the first one
	if ( currentSelection == LB_ERR )
	{
		currentSelection = 0;
	}

	// Show the properties dialog of the currently selected overlay
	if ( d_overlays->getNumOverlaysLoaded() > currentSelection )
	{
    d_overlays->getOverlay( currentSelection )->showPropertiesDialog();
	}

  // Reselect the overlay whose properties were shown
  d_overlaysList.SetSel( currentSelection );
  OnSelchangeOverlayList();
}

void CMainPropertiesDialog::OnOptionsButton() 
{
	ASSERT( d_overlaysList.GetSelCount() == 1 );

	long currentSelection;

	// Get the index of the currently selected overlay
	currentSelection = d_overlaysList.GetCurSel();

	// If no list item is selected, then show the first one
	if ( currentSelection == LB_ERR )
	{
		currentSelection = 0;
	}

	// Show the properties dialog of the currently selected overlay
	if ( d_overlays->getNumOverlaysLoaded() > currentSelection )
	{
		BOOL flag;
		flag = 
      d_overlays->getOverlay(currentSelection)->showOptionsDialog(d_pView->GetDocument());
		d_modified = d_modified || flag;
	}

	// Notify the document if anything changed
	if ( d_modified )
	{
		d_pView->GetDocument()->OnControlCenterApply();
	}

  // Reselect the overlay whose options were shown
  d_overlaysList.SetSel( currentSelection );
  OnSelchangeOverlayList();
}
 
void CMainPropertiesDialog::OnShowOverlay() 
{
	ASSERT( d_overlaysList.GetSelCount() == 1 );

	long currentSelection;

	// Get the index of the currently selected overlay
	currentSelection = d_overlaysList.GetCurSel();

	// If no list item is selected, then do nothing
	if ( currentSelection == LB_ERR )
	{
		return;
	}
	
	// Change the current show state of the overlay
  GeographicOverlay* pOverlay = d_overlays->getOverlay( currentSelection );
	BOOL overlayShowState = pOverlay->getShow(); 
	pOverlay->setShow( !overlayShowState ); 

	// Change the text of the changed overlay
	d_overlaysList.DeleteString( currentSelection );
	CString text;
	if ( !overlayShowState )
	{
		text = "(Displayed) ";
	}
	else
	{
		text = "  (Hidden)  ";
	}
	text += pOverlay->getDescription();
	d_overlaysList.InsertString( currentSelection, text );

	// Set the modified flag
	d_modified = TRUE;

  // Reselect the overlay whose state was just changed
  d_overlaysList.SetSel( currentSelection );
  OnSelchangeOverlayList();

	// Notify the document
	d_pView->GetDocument()->OnControlCenterApply();
}

void CMainPropertiesDialog::OnSelchangeOverlayList() 
{
	// Get the number of selected items
	int numSelected = d_overlaysList.GetSelCount();

	// Disable all of the buttons if no items are selected
	if ( numSelected == 0 )
	{
		d_propertiesButton.EnableWindow( FALSE );
		d_optionsButton.EnableWindow( FALSE );
		d_showOverlaysButton.EnableWindow( FALSE );
		d_closeOverlayButton.EnableWindow( FALSE );
		d_removeClipsButton.EnableWindow( FALSE );
	}
	// Enable all buttons if exactly one overlay is selected
	else if ( numSelected == 1 )
	{
		// Get the selected items
		int *pSelected = new int;
		d_overlaysList.GetSelItems( 1, pSelected );

		d_propertiesButton.EnableWindow( TRUE );
		d_optionsButton.EnableWindow( TRUE );
		d_showOverlaysButton.EnableWindow( TRUE );
		d_closeOverlayButton.EnableWindow( TRUE );
		d_removeClipsButton.EnableWindow( TRUE );

		// Set the text of the show overlay button
		if ( d_overlays->getOverlay( pSelected[0] )->getShow() )
		{
			d_showOverlaysButton.SetWindowText( "Hide Overlay" );
		}
		else
		{
			d_showOverlaysButton.SetWindowText( "Show Overlay" );
		}

		delete pSelected;
	}		
	// Enable the Remove Clips Button and Close Overlay buttons
	// if more than one overlay is selected
	else if ( numSelected > 1 )
	{
		d_propertiesButton.EnableWindow( FALSE );
		d_optionsButton.EnableWindow( FALSE );
		d_showOverlaysButton.EnableWindow( FALSE );
		d_closeOverlayButton.EnableWindow( TRUE );
		d_removeClipsButton.EnableWindow( TRUE );
	}
}

void CMainPropertiesDialog::OnCloseOverlay() 
{
	// Get the number of selected items
	int numSelected = d_overlaysList.GetSelCount();

	// Abort if no overlays selected
	if ( numSelected < 1 )
	{
		return;
	}

	// Cleanup the view's controllers
	d_pView->cleanupControllers();

	// Get the selected items
	int* pSelected = new int[numSelected];
	d_overlaysList.GetSelItems( numSelected, pSelected );

	for ( int i = 0; i < numSelected; i++ )
	{
		int currentSelection = pSelected[i];

		// Delete the string from the list box
		d_overlaysList.DeleteString( currentSelection );

    // Remove overlay
    d_overlays->removeOverlay( d_overlays->getOverlay( currentSelection ) );

		// Decrement all remaining selected items with indices
		// greater than the currently selected item
		for ( int j = i + 1; j < numSelected; j++ )
		{
			if ( pSelected[j] > currentSelection )
			{
				pSelected[j]--;
			}
		}
	}

	// Set the modified flag
	d_modified = TRUE;

	// Notify the document of the change
	d_pView->GetDocument()->OnControlCenterApply();

  // Select the first overlay if at least one is loaded
  if ( d_overlays->getNumOverlaysLoaded() > 0 )
	{
    // Select the first element in the list
    d_overlaysList.SetSel( 0 );
    OnSelchangeOverlayList();
	}
}

void CMainPropertiesDialog::setModifiedFlag( BOOL flag )
{
	d_modified = flag;
}

void CMainPropertiesDialog::OnDone() 
{
	// Notify the document
	d_pView->GetDocument()->OnControlCenterDone();	
}

void CMainPropertiesDialog::OnHideAreasAll() 
{
	// Set the modified flag
	d_modified = TRUE;

	// Notify the document of the change
	d_pView->GetDocument()->OnControlCenterApply();
}

void CMainPropertiesDialog::OnHideNodesAll() 
{
	// Set the modified flag
	d_modified = TRUE;

	// Notify the document of the change
	d_pView->GetDocument()->OnControlCenterApply();
}

void CMainPropertiesDialog::OnHideLinesAll() 
{
	// Set the modified flag
	d_modified = TRUE;

	// Notify the document of the change
	d_pView->GetDocument()->OnControlCenterApply();
}

void CMainPropertiesDialog::OnRemoveClips() 
{
	// Get the number of selected items
	int numSelected = d_overlaysList.GetSelCount();

	// Abort if no overlays selected
	if ( numSelected < 1 )
	{
		return;
	}

	// Get the selected items
	int* pSelected = new int[numSelected];
	d_overlaysList.GetSelItems( numSelected, pSelected );

	for ( int i = 0; i < numSelected; i++ )
	{
		int currentSelected = pSelected[i];

		// Remove clips from the clipping region
		d_overlays->getOverlay( currentSelected )->removeAllClippingRegions();
	}

	// Set the modified flag
	d_modified = TRUE;

	// Notify the document of the change
	d_pView->GetDocument()->OnControlCenterApply();
}
