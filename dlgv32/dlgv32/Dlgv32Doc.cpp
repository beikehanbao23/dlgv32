// dlgv32Doc.cpp : implementation of the CDlgv32Doc class
//

#include "StdAfx.h"
#include "dlgv32.h"

#include "dlgv32Doc.h"
#include "dlgv32View.h"
#include "CoordinateTransforms.h"
#include "MainPropertiesDialog.h"
#include "RasterOverlay.h"
#include "GraphicsLib\CoordinateMapping.h"
#include "GraphicsLib\Rectangle2D.h"
#include "ProjectionLib\StatePlaneProjection.h"

#include <fstream>
#include <iostream>

using namespace std;


// Overlay type includes
#include "DLGOverlay.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgv32Doc

IMPLEMENT_DYNCREATE(CDlgv32Doc, CDocument)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CDlgv32Doc, CDocument)
	//{{AFX_MSG_MAP(CDlgv32Doc)
	ON_COMMAND(ID_FILE_OPEN_NEW, OnFileOpenNew)
	ON_COMMAND(ID_FILE_OPEN_CURRENT, OnFileOpenCurrent)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN_CURRENT, OnUpdateFileOpenCurrent)
	ON_COMMAND(ID_FILE_UNLOAD_ALL, OnFileUnloadAll)
	ON_UPDATE_COMMAND_UI(ID_FILE_UNLOAD_ALL, OnUpdateFileUnloadAll)
	ON_COMMAND(ID_ZOOM_IN, OnZoomIn)
	ON_COMMAND(ID_ZOOM_OUT, OnZoomOut)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_OUT, OnUpdateZoomOut)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_IN, OnUpdateZoomIn)
	ON_COMMAND(ID_VIEW_FULLVIEW, OnViewFullview)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FULLVIEW, OnUpdateViewFullview)
	ON_COMMAND(ID_TOOLS_CONTROLCENTER, OnToolsControlcenter)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_CONTROLCENTER, OnUpdateToolsControlcenter)
	ON_UPDATE_COMMAND_UI(ID_HELP_FINDER, OnUpdateHelpFinder)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgv32Doc construction/destruction

CDlgv32Doc::CDlgv32Doc()
: d_pControlCenter(0), d_drawNow(TRUE)
{
	// Give the CoordinateTransform class a pointer to the projection
	CoordinateTransforms::setCurrentMapping( new CoordinateMapping(TRUE) );

  // Get the CoordinateTransforms class a projection changed callback method
  CoordinateTransforms::setProjectionChangedFunction( handleProjectionChanged,
                                                      this );

	// Get the values for hiding lines/nodes/etc. from the Registry
	DWORD temp;
	temp = AfxGetApp()->GetProfileInt( "", "HideAllDLGNodes", FALSE );
	DLGOverlay::setHideAllNodes( temp );
	temp = AfxGetApp()->GetProfileInt( "", "HideAllDLGAreas", FALSE);
	DLGOverlay::setHideAllAreas( temp );
	temp = AfxGetApp()->GetProfileInt( "", "HideAllDLGLines", FALSE);
	DLGOverlay::setHideAllLines( temp );

	// Get the filter index to use initially in the open file box
	d_filterIndex = AfxGetApp()->GetProfileInt( "", "FilterIndex", 0);

	// Get the initial directory to use in the open file box
	d_initialDirectory = AfxGetApp()->GetProfileString( "", "InitialDir", "");

  // Get the installation directory
  CString strInstallDir = AfxGetApp()->GetProfileString( "", "InstallDir", "");
  CString strNAD27SPName = strInstallDir + "\\nad27sp";
  CString strNAD83SPName = strInstallDir + "\\nad83sp";
    
  // Set the state plane parameter file names
  StatePlaneProjection::setNAD27ParameterFilename((const char*)strNAD27SPName);
  StatePlaneProjection::setNAD83ParameterFilename((const char*)strNAD83SPName);
}

CDlgv32Doc::~CDlgv32Doc()
{
	// Free memory used by projection
	delete CoordinateTransforms::getCurrentMapping();

	// Free memory used by overlays
	freeOverlays();

	// Free memory used by control center dialog
	delete d_pControlCenter;

	// Save the values for hiding lines/nodes/etc. in the Registry
	AfxGetApp()->WriteProfileInt( "", "HideAllDLGNodes",
                                DLGOverlay::getHideAllNodes() );
	AfxGetApp()->WriteProfileInt( "", "HideAllDLGAreas", 
                                DLGOverlay::getHideAllAreas() );
	AfxGetApp()->WriteProfileInt( "", "HideAllDLGLines", 
                                DLGOverlay::getHideAllLines() );

	// Save the current filter index from the open file dialog box
	AfxGetApp()->WriteProfileInt( "", "FilterIndex", d_filterIndex );

	// Save the initial directory to use in the open file dialog box
	AfxGetApp()->WriteProfileString( "", "InitialDir", d_initialDirectory );
}

BOOL CDlgv32Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDlgv32Doc serialization

void CDlgv32Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDlgv32Doc diagnostics

#ifdef _DEBUG
void CDlgv32Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDlgv32Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDlgv32Doc commands

BOOL CDlgv32Doc::OnOpenDocument(LPCTSTR lpszPathName) 
// This function is called when the user opens an overlay
{
	// Show a wait cursor
	HCURSOR hOldCursor = ::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));

  // Get the number of overlays loaded when we enter the function
  int oldNumOverlaysLoaded = d_overlays.getNumOverlaysLoaded();
  int oldRasterCount = d_overlays.getNumRasterOverlaysLoaded();

	// Check to see if a file with the same name has already
	// been loaded.  If one has, give the user the option of
	// aborting the load
	CString strFilename( lpszPathName );
  list<GeographicOverlay*>& overlays = d_overlays.getOverlays();
  for (list<GeographicOverlay*>::iterator i = overlays.begin();
       i != overlays.end(); i++ )
	{
		if ( !strFilename.CompareNoCase( (*i)->getFilename() ) )
		{
			CString strText = "An overlay with the filename ";
			strText += strFilename;
			strText += " has already been loaded.  Do you wish to ";
			strText += "abort the load of this overlay?";
			if ( IDYES == AfxMessageBox( strText, MB_YESNO | MB_ICONEXCLAMATION ) )
			{
        // Restore the old cursor
	      ::SetCursor( hOldCursor );

        return FALSE;
			}
			else
			{
				// break out of loop if user wants to load it
				break;
			}
		}
	}

	// Save the directory of the file for later use in open dialog box
	d_initialDirectory = getDirectory( strFilename );

  // Load the overlays
  if ( 0 == d_overlays.loadOverlay( (LPCTSTR)strFilename ) )
  {
      AfxMessageBox( "Error opening overlay" );
      ::SetCursor( hOldCursor );
      return FALSE;
  }

  // Update the current bounding rectangle
  calculateBoundingRect();

  // Initalize the projection's world space window if there weren't any
  // overlays before
  if ( 0 == oldNumOverlaysLoaded )
  {
    double x1, y1, x2, y2;
    d_boundingRect.getPoints( x1, y1, x2, y2 );
	  CoordinateTransforms::getCurrentMapping()->setWindowExtents(x1,y1,x2,y2);
  }

  // Update the control center if it is visible
  if ( d_pControlCenter != NULL )
  {
    d_pControlCenter->setOverlays( d_overlays );
  }

	// Set the windows title if the window is valid
	CWnd* pMainWnd = AfxGetMainWnd();
	if ( pMainWnd->GetSafeHwnd() )
	{
		pMainWnd->SetWindowText( "DLG Viewer" );
	}

  // Get the current overlay counts
  int curOverlayCount = d_overlays.getNumOverlaysLoaded();
  int curRasterCount = d_overlays.getNumRasterOverlaysLoaded();

  if ( d_drawNow )
	{
		// If this is a new overlay from the MRU or an overlay
		// selected from the explorer, draw it full view
		if ( 0 == oldNumOverlaysLoaded )
		{
			OnViewFullview();
		}
		// If only vector overlays were loaded, just draw the new ones
		else if ( curRasterCount == oldRasterCount )
		{
			// Get the client rectangle
			CRect clientRect;
			POSITION pos = GetFirstViewPosition();
			CView* pView = GetNextView( pos );
			pView->GetClientRect( &clientRect );

			// Convert the client rectangle to logical coordinates
			CClientDC dc( pView );
			pView->OnPrepareDC( &dc );
			dc.DPtoLP( &clientRect );
			clientRect.NormalizeRect();

			// Just draw the overlay(s) loaded this time
      list<GeographicOverlay*>& overlays = d_overlays.getOverlays();
      int counter = 0;
      for ( list<GeographicOverlay*>::iterator i = overlays.begin(); i != overlays.end();
            i++, counter++ )
      {
        if ( counter >= oldNumOverlaysLoaded )
        {
           (*i)->draw( &dc, &clientRect );
        }
      }
    }
		else // If a raster was loaded, redraw everything
		{
			// Redraw everything
			UpdateAllViews( NULL );
		}
	}

  // Restore the old cursor
	::SetCursor( hOldCursor );    
    
  return TRUE;
}

void CDlgv32Doc::freeOverlays()
{
  // Free all the overlays
  d_overlays.removeAllOverlays();

  // Reset the CoordinateTransforms parameters
  CoordinateTransforms::setProjection( NULL );
}

void CDlgv32Doc::calculateBoundingRect()
{
	double ov_x1, ov_y1, ov_x2, ov_y2;
	double min_x, min_y, max_x, max_y;

  list<GeographicOverlay*>& overlays = d_overlays.getOverlays();
  for ( list<GeographicOverlay*>::iterator i = overlays.begin();
        i != overlays.end(); i++ )
	{
    // Get the overlays bounding rectangle
    Rectangle2D boundRect = (*i)->getGlobalBoundingRect();

		// Get the corners of the overlays bounding rectangle
		boundRect.getPoints( ov_x1, ov_y1, ov_x2, ov_y2 );
			
		// If this is the first overlay, initialize the bounding
		// rectangle to this overlays bounding rectangle
		if ( i == overlays.begin() )
		{
			min_x = ov_x1;
			max_x = ov_x2;
			min_y = ov_y1;
			max_y = ov_y2;
		}
		// If this isn't the first overlay, check to see if any
		// of the current overlays bounds are outside of the
		// bounding rectangle
		else
		{
			if ( ov_x1 < min_x )
			{
				min_x = ov_x1;
			}
			
			if ( ov_x2 > max_x )
			{
				max_x = ov_x2;
			}

			if ( ov_y1 < min_y )
			{
				min_y = ov_y1;
			}

			if ( ov_y2 > max_y )
			{
				max_y = ov_y2;
			}
		}
	}

	d_boundingRect.setPoints( min_x, min_y, max_x, max_y );
}

void CDlgv32Doc::OnFileOpenNew() 
// This function is called when the user opens an overlay to be
// viewed by itself.
{
	// Create a file open dialog box
	CFileDialog openDialog( TRUE, NULL, NULL, 
                          OFN_HIDEREADONLY | OFN_FILEMUSTEXIST |
                          OFN_PATHMUSTEXIST | OFN_ALLOWMULTISELECT, 
                          d_overlays.getFilterString() );
	
	// Set the filter index
	openDialog.m_ofn.nFilterIndex = d_filterIndex;

	// Set the directory to start looking in
	if ( !d_initialDirectory.IsEmpty() )
	{
		openDialog.m_ofn.lpstrInitialDir = d_initialDirectory;
	}
	else
	{
		openDialog.m_ofn.lpstrInitialDir = NULL;
	}

	if ( openDialog.DoModal() == IDOK )
	{
    // Free all the currently open overlays
    freeOverlays();

		// Get the filter index
		d_filterIndex = openDialog.m_ofn.nFilterIndex;
		
		// Get the position of the first filename
		POSITION filenamePosition = openDialog.GetStartPosition();
		CString  filename;

		// Reset the draw now flag
		d_drawNow = FALSE;
		
		// Open each file selected
		while ( filenamePosition != NULL )
		{
			// Get the next pathname
			filename = openDialog.GetNextPathName( filenamePosition );

			// Add the selected overlay to the recently used file list
			AfxGetApp()->AddToRecentFileList( filename );

			// Call OnOpenDocument to do the rest
			OnOpenDocument( filename );
		}

		// redraw the image with the new overlay and zoomed to full view
		OnViewFullview();
	}

	// Set the draw now flag
	d_drawNow = TRUE;
	
	return;
}

void CDlgv32Doc::OnFileOpenCurrent() 
// This function is called when the user opens an overlay to be
// viewed along with the overlays currently being viewed
{
	// Create a file open dialog box
	CFileDialog openDialog( TRUE, NULL, NULL, 
                          OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | 
                          OFN_PATHMUSTEXIST | OFN_ALLOWMULTISELECT, 
                          d_overlays.getFilterString() );
	
	// Set the filter index
	openDialog.m_ofn.nFilterIndex = d_filterIndex;

	// Set the directory to start looking in
	if ( !d_initialDirectory.IsEmpty() )
	{
		openDialog.m_ofn.lpstrInitialDir = d_initialDirectory;
	}
	else
	{
		openDialog.m_ofn.lpstrInitialDir = NULL;
	}

	if ( openDialog.DoModal() == IDOK )
	{
		// Get the filter index
		d_filterIndex = openDialog.m_ofn.nFilterIndex;

		// Get the position of the first filename
		POSITION filenamePosition = openDialog.GetStartPosition();
		CString  filename;

		// Open each file selected
		while ( filenamePosition != NULL )
		{
			// Get the next pathname
			filename = openDialog.GetNextPathName( filenamePosition );

			// Add the selected overlay to the recently used file list
			AfxGetApp()->AddToRecentFileList( filename );

			// Call OnOpenDocument to do the rest
			OnOpenDocument( filename );
		}
	}
	
	return;
}

void CDlgv32Doc::OnUpdateFileOpenCurrent(CCmdUI* pCmdUI) 
{
	// Enable the control if there is already at least one
	// overlay loaded, otherwise disable it
	pCmdUI->Enable( d_overlays.getNumOverlaysLoaded() > 0 );	
}

void CDlgv32Doc::OnFileUnloadAll() 
// This function removes all overlays from the screen and frees the
// memory used by them
{
	// Get the view for this document
	POSITION pos = GetFirstViewPosition();
	CView* pView = GetNextView( pos );

	// Have the view clean up its controllers
	((CDlgv32View*)pView)->cleanupControllers();

	// Free the memory taken up by the old overlays
	freeOverlays();
	
	// Update the control center if it is open
	if ( d_pControlCenter )
	{
		d_pControlCenter->setOverlays( d_overlays );
	}

	// Clear the view window.
	DeleteContents();	

	// redraw the screen, erasing all overlays that were there
	UpdateAllViews(NULL);
}

void CDlgv32Doc::OnUpdateFileUnloadAll(CCmdUI* pCmdUI) 
{
	// Enable the control if there is already at least one
	// overlay loaded, otherwise disable it
	pCmdUI->Enable( d_overlays.getNumOverlaysLoaded() > 0 );
}

void CDlgv32Doc::OnZoomIn() 
{
	// Update the projection to account for the new zoom
	CoordinateTransforms::getCurrentMapping()->zoomBy( 2.0 );

	// Update the view
	UpdateAllViews( NULL );
}

void CDlgv32Doc::OnZoomOut() 
{
	// Update the projection to account for the new zoom
	CoordinateTransforms::getCurrentMapping()->zoomBy( -2.0 );

	// Update the view
	UpdateAllViews( NULL );
}

void CDlgv32Doc::OnUpdateZoomOut(CCmdUI* pCmdUI) 
{
	// Enable the control if there is already at least one
	// overlay loaded, otherwise disable it
	pCmdUI->Enable( d_overlays.getNumOverlaysLoaded() > 0 );	
}

void CDlgv32Doc::OnUpdateZoomIn(CCmdUI* pCmdUI) 
{
	// Enable the control if there is already at least one
	// overlay loaded, otherwise disable it
	pCmdUI->Enable( d_overlays.getNumOverlaysLoaded() > 0 );	
}

void CDlgv32Doc::OnViewFullview() 
{
	// Get the bounding rectangle points
	double x1, y1, x2, y2;
	d_boundingRect.getPoints( x1, y1, x2, y2 );

	// Set the mapping to the bounding rect
	CoordinateTransforms::getCurrentMapping()->setWindowExtents(x1,y1,x2,y2);

	// Zoom the mapping out by 5%
	CoordinateTransforms::getCurrentMapping()->zoomBy( -1.05 );

	// Redraw the client area
	UpdateAllViews( NULL );
}

void CDlgv32Doc::OnUpdateViewFullview(CCmdUI* pCmdUI) 
{
	// Enable the control if there is already at least one
	// overlay loaded, otherwise disable it
	pCmdUI->Enable( d_overlays.getNumOverlaysLoaded() > 0 );	
}

int
CDlgv32Doc::pick( const CRect& pickRect, 
                  CTypedPtrArray< CPtrArray, OverlayComponent* > *oc_list,
			            int start, const CRect& clientRect, int maxToPick )
{
  list<GeographicOverlay*>& overlays = d_overlays.getOverlays();
  for ( list<GeographicOverlay*>::iterator i = overlays.begin();
        i != overlays.end(); i++ )
	{
		start += (*i)->pick( pickRect, oc_list, start, clientRect );
	}

	return start;
}

bool
CDlgv32Doc::getBrowseText( const CRect& pickRect, const CRect& clientRect, 
                           CString& strBrowse ) const
{
  // Try and get the browse text from each overlay until we're successful
  const list<GeographicOverlay*>& overlays = d_overlays.getOverlays();
  for (list<GeographicOverlay*>::const_reverse_iterator i = overlays.rbegin(); 
       i != overlays.rend(); i++ )
  {
    if ( (*i)->getBrowseText( pickRect, clientRect, strBrowse ) )
    {
      return true;
    }
  }

  return false;
}

void CDlgv32Doc::OnToolsControlcenter() 
{
	// If the control center is already open, just bring it to front
	if ( d_pControlCenter )
	{
		d_pControlCenter->ShowWindow( SW_SHOWNORMAL );
		d_pControlCenter->BringWindowToTop();
		return;
	}
	
	// Get the first view attached to the document
	POSITION pos = GetFirstViewPosition();
	CView* pView = GetNextView( pos );

	// Setup the dialog
	d_pControlCenter = new CMainPropertiesDialog( pView );
	d_pControlCenter->setOverlays( d_overlays );
	d_pControlCenter->d_hideAllNodesButton.SetCheck(DLGOverlay::getHideAllNodes());
	d_pControlCenter->d_hideAllAreasButton.SetCheck(DLGOverlay::getHideAllAreas());
	d_pControlCenter->d_hideAllLinesButton.SetCheck(DLGOverlay::getHideAllLines());
	d_pControlCenter->UpdateWindow();

	return;
}

void CDlgv32Doc::OnUpdateToolsControlcenter(CCmdUI* pCmdUI) 
{
	// Enable the control if there is already at least one
	// overlay loaded, otherwise disable it
	pCmdUI->Enable( d_overlays.getNumOverlaysLoaded() > 0 );	
}


void CDlgv32Doc::OnUpdateHelpFinder(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( TRUE );	
}

void
CDlgv32Doc::redraw()
{
	// Have the view clean up its controllers
	POSITION pos = GetFirstViewPosition();
	CView* pView = GetNextView( pos );
	((CDlgv32View*)pView)->cleanupControllers();

	// Recalculate the bounding rectangle and redraw
	calculateBoundingRect();
	UpdateAllViews( NULL );
}

void CDlgv32Doc::OnControlCenterApply()
{
	// Update the number of overlays loaded

  // Reset the projection if all overlays are now closed
  if ( 0 == d_overlays.getNumOverlaysLoaded() )
  {
    CoordinateTransforms::setProjection( NULL );
  }

	// Redraw the overlays if something was modified
	if ( d_pControlCenter->getModifiedFlag() )
	{
		// Have the view clean up its controllers
		POSITION pos = GetFirstViewPosition();
		CView* pView = GetNextView( pos );
		((CDlgv32View*)pView)->cleanupControllers();

		// Set the new hide settings for DLG Overlays
		DLGOverlay::setHideAllNodes(d_pControlCenter->d_hideAllNodesButton.GetCheck() );
		DLGOverlay::setHideAllAreas(d_pControlCenter->d_hideAllAreasButton.GetCheck() );
		DLGOverlay::setHideAllLines(d_pControlCenter->d_hideAllLinesButton.GetCheck() );

		// Recalculate the bounding rectangle and redraw
		calculateBoundingRect();
		UpdateAllViews( NULL );

		// Reset modified flag
		d_pControlCenter->setModifiedFlag( FALSE );
	}
}

void CDlgv32Doc::OnControlCenterDone()
{
	// Return if Control Center pointer NULL
	if ( !d_pControlCenter )
	{
		return;
	}
	
	OnControlCenterApply();

	// Destroy the Control Center dialog
	delete d_pControlCenter;
	d_pControlCenter = 0;
}

CString 
CDlgv32Doc::getDirectory( const CString& filename ) const
{
	int pos;

	// Find the last occurence of the backslash character
	if ( ( pos = filename.ReverseFind( '\\' ) ) != -1 )
	{
		return filename.Left( pos );
	}
	else
	{
		return "";
	}
}

void 
CDlgv32Doc::handleProjectionChanged( LPVOID pArg, const Projection* pOldProjection )
{
  CDlgv32Doc* pDoc = reinterpret_cast<CDlgv32Doc*>(pArg);
  ASSERT( NULL != pDoc );

  // Tell each of the document's overlays that the projection has been changed
  list<GeographicOverlay*>& overlays = pDoc->d_overlays.getOverlays();
  for ( list<GeographicOverlay*>::iterator i = overlays.begin();
        i != overlays.end(); i++ )
	{
		(*i)->handleProjectionChanged( /* pOldProjection */ );
	}
}
