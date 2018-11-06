// dlgv32View.cpp : implementation of the CDlgv32View class
//

#include "stdafx.h"
#include "dlgv32.h"

#include "dlgv32Doc.h"
#include "dlgv32View.h"
#include "MainFrm.h"
#include "CoordinateTransforms.h"
#include "GraphicsObject.h"
#include "ZoomController.h"
#include "PanController.h"
#include "DistanceController.h"
#include "PickController.h"
#include "PolyRegionController.h"
#include "GraphicsLib\CoordinateMapping.h"
#include "MC_SBAR.h"
#include "RasterOverlay.h"

IMPLEMENT_DYNCREATE(CDlgv32View, CView)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgv32View


BEGIN_MESSAGE_MAP(CDlgv32View, CView)
	//{{AFX_MSG_MAP(CDlgv32View)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_SIZE()
	ON_COMMAND(ID_TOOLS_ZOOM, OnToolsZoom)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_ZOOM, OnUpdateToolsZoom)
	ON_COMMAND(ID_TOOLS_PAN, OnToolsPan)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_PAN, OnUpdateToolsPan)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_TOOLS_DISTANCE, OnToolsDistance)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_DISTANCE, OnUpdateToolsDistance)
	ON_COMMAND(ID_TOOLS_PICK, OnToolsPick)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_PICK, OnUpdateToolsPick)
	ON_COMMAND(ID_BG_COLOR, OnBgColor)
	ON_WM_ERASEBKGND()
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnUpdateFilePrintPreview)
	//}}AFX_MSG_MAP

	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview) 
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_TOOLS_POLYREGION, OnToolsPolyRegion)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_POLYREGION, OnUpdateToolsPolyRegion)
	ON_UPDATE_COMMAND_UI(ID_CURRENT_TOOL, OnUpdateCurrentTool)
	ON_UPDATE_COMMAND_UI(ID_MOUSE_POS_LATLONG, OnUpdateCurrentMousePosLatLong)
	ON_UPDATE_COMMAND_UI(ID_MOUSE_POS_UTM, OnUpdateCurrentMousePosGndRefSys)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgv32View construction/destruction

CDlgv32View::CDlgv32View()
: d_pCurrentController(NULL), d_pZoomController(NULL),
  d_pPanController(NULL),     d_pDistanceController(NULL),
  d_pPickController(NULL),    d_pPolyRegionController(NULL),
  d_currentMousePos(0, 0),    d_pHalftonePalette(NULL),
  d_bIsWin95(false)
{
	// Make zoom controller the default
	OnToolsZoom();

	// Get the values for the background color from the registry
	GraphicsObject::setBgColor( AfxGetApp()->GetProfileInt( "", "BGColor", 0) );

  // Determine if we're running on Win95
	OSVERSIONINFO vsInfo;
	vsInfo.dwOSVersionInfoSize = sizeof( vsInfo );
	if ( ::GetVersionEx( &vsInfo ) )
	{
		if ( vsInfo.dwPlatformId != VER_PLATFORM_WIN32_NT )
		{
      d_bIsWin95 = true;
		}
	}
}

CDlgv32View::~CDlgv32View()
{
	// Free memory used by controllers
	delete d_pZoomController;
	delete d_pPanController;
	delete d_pDistanceController;
	delete d_pPickController;
	delete d_pPolyRegionController;

  // Free memory used by the halftone palette
  delete d_pHalftonePalette;

  // Save the current background color in the registry
  AfxGetApp()->WriteProfileInt( "", "BGColor", GraphicsObject::getBgColor() );

}

BOOL CDlgv32View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDlgv32View drawing

void CDlgv32View::OnDraw(CDC* pDC)
// This function is called whenever a WM_PAINT message is received.
{
	// Show a wait cursor
	HCURSOR hOldCursor = ::SetCursor( AfxGetApp()->LoadStandardCursor( IDC_WAIT ) );
	
  // Get the document
  CDlgv32Doc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
    
  // Use the halftone palette if this is a palette based device
  CPalette* pOldPalette = NULL;
  if ( pDC->GetDeviceCaps( RASTERCAPS ) & RC_PALETTE )
  {
    // Create a halftone palette if necessary
    if ( NULL == d_pHalftonePalette )
    {
      d_pHalftonePalette = new CPalette();
      d_pHalftonePalette->CreateHalftonePalette( pDC );
    }
        
    // Select and realize the palette into the DC
    pOldPalette = pDC->SelectPalette( d_pHalftonePalette, FALSE );
    pDC->RealizePalette();
  }
    
  // Get the invalid rectangle
  CRect clipBox;
  pDC->GetClipBox( &clipBox );
    
  // Set DC to the current background color
  pDC->SetBkColor( GraphicsObject::getBgColor() );

  // Get the overlay counts
  int rasterCount = pDoc->getOverlayFactory().getNumRasterOverlaysLoaded();
  int layerCount = pDoc->getOverlayFactory().getNumOverlaysLoaded();
    
  // Draw depending on which platform we're on
  if ( !d_bIsWin95 || ( 0 == rasterCount ) )
  {
    drawOverlays( pDC, &clipBox, 0, layerCount - 1 );
  }
  else
  {
    // We have to do this stuff for Win95 because it apparently has problems
    // creating or displaying more than 3 bitmaps per paint message
    static UINT timesDrawn = 0;
	     
    // Draw the appropriate overlays
    drawOverlays( pDC, &clipBox, 0, min( timesDrawn * 3 + 2, rasterCount - 1 ) );

	  // Increment number of times drawn
	  timesDrawn++;

	  // Redraw if we haven't yet drawn all the raster layers
	  if ( timesDrawn <= ( rasterCount - 1 ) / 3 )
	  {
		  // Redraw the clipping rectangle
		  InvalidateRect( clipBox );

		  // Redraw the status bar
		  ((CMainFrame*)AfxGetMainWnd())->GetStatusBar()->Invalidate();
	  }
	  else
	  {
      // Rest the number of times drawn
		  timesDrawn = 0;

      // Draw all the vector overlays
      drawOverlays( pDC, &clipBox, rasterCount, layerCount - 1 );
	  }
  }

  // Restore the old palette if necessary
  if ( NULL != pOldPalette )
  {
    pDC->SelectPalette( pOldPalette, FALSE );
  }

	// Restore the old cursor
	::SetCursor( hOldCursor );
}

void
CDlgv32View::drawOverlays( CDC* pDC, CRect* pClipRect, int first, int last )
{
  // Get the document
  CDlgv32Doc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);

  // Get the overlays
  list<GeographicOverlay*>& overlays = 
    pDoc->getOverlayFactory().getOverlays();

  // Draw all the overlays between <first> and <last>
  int index = 0;
  for ( list<GeographicOverlay*>::iterator i = overlays.begin();
        i != overlays.end(); i++, index++ )
  {
    if ( index >= first && index <= last )
    {
      (*i)->draw( pDC, pClipRect );
    }
  }
}

/////////////////////////////////////////////////////////////////////////////
// CDlgv32View diagnostics

#ifdef _DEBUG
void CDlgv32View::AssertValid() const
{
	CView::AssertValid();
}

void CDlgv32View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDlgv32Doc* CDlgv32View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDlgv32Doc)));
	return (CDlgv32Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDlgv32View printing

BOOL
CDlgv32View::OnPreparePrinting( CPrintInfo* pInfo )
{
	// Default preparation
	return DoPreparePrinting( pInfo );
}

void CDlgv32View::OnBeginPrinting( CDC* pDC, CPrintInfo* pInfo )
{
	// TODO: add extra initialization before printing
}

void CDlgv32View::OnEndPrinting( CDC* pDC, CPrintInfo* pInfo )
{
	// TODO: print cleanup
}

void CDlgv32View::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// Get the page rectangle in pixels
	int width_pix  = pDC->GetDeviceCaps( HORZRES );
	int height_pix = pDC->GetDeviceCaps( VERTRES );

  // Get the page rectangle in inches
  int width_in  = static_cast<float>( pDC->GetDeviceCaps( HORZSIZE ) ) / 25.4;
  int height_in = static_cast<float>( pDC->GetDeviceCaps( VERTSIZE ) ) / 25.4;
	
	// Get the current mapping
	CoordinateMapping* pMapping = CoordinateTransforms::getCurrentMapping();

	// Save the current viewport
	double v_x1, v_x2, v_y1, v_y2;
	pMapping->getViewportExtents( v_x1, v_y1, v_x2, v_y2 );

	// Save the current window (world-space)
	double w_x1, w_x2, w_y1, w_y2;
	pMapping->getWindowExtents( w_x1, w_y1, w_x2, w_y2 );

	// Set the viewport to the page rectangle and make sure the last
	// requested window is used for computing things
	pMapping->setViewportExtents( 0, height_pix, width_pix, 0 );

	// Get the old background color
	COLORREF oldBgColor = GraphicsObject::getBgColor();

	// Set the current background color to white
	GraphicsObject::setBgColor( PALETTERGB( 255, 255, 255 ) );

  // Get the overlays
  list<GeographicOverlay*>& overlays = 
    GetDocument()->getOverlayFactory().getOverlays();

  if ( 0 == GetDocument()->getOverlayFactory().getNumRasterOverlaysLoaded() )
  {
    OnDraw( pDC );
  }
  else if ( !d_bIsWin95 )
  {
    // Incrementally draw the overlays on WinNT at full resolution
    int numSegments = 3;
    int ySpacing = height_pix / numSegments + 0.5;

    CRect clipRect;
    int top, bottom;
    for ( int i = 0; i < numSegments; i++ )
    {
      // Calculate the clipping rectangle for this segment
      top = i * ySpacing;
      bottom = min( height_pix, top + ySpacing );
      clipRect.SetRect( 0, top, width_pix, bottom );

      // Draw each overlay
      for ( list<GeographicOverlay*>::iterator iter = overlays.begin();
            iter != overlays.end(); iter++ )
      {
        (*iter)->draw( pDC, &clipRect );
      }
    }
  }
  else
  {
     // On Win95 we have to print at a lower DPI because Win95 can't handle
     // bitmaps over a certain size (around 4MB)

     // Calculate the size of bitmap to draw to based on a certain dpi
     int dpi = 250;
     int width_dots  = width_in * dpi;
     int height_dots = height_in * dpi;

     // Set the viewport to the page rectangle and make sure the last
	   // requested window is used for computing things
	   pMapping->setViewportExtents( 0, height_dots, width_dots, 0 );

     // Create a memory DC
     CDC dcMem;
     dcMem.CreateCompatibleDC( pDC );

     // Use the halftone palette if this is a palette based device
     CPalette* pOldPalette = NULL;
     if ( dcMem.GetDeviceCaps( RASTERCAPS ) & RC_PALETTE )
     {
       // Create a halftone palette
       CPalette pal;
       pal.CreateHalftonePalette( pDC );

       // Select and realize the palette into the DC
       pOldPalette = pDC->SelectPalette( &pal, FALSE );
       pDC->RealizePalette();
     }

     // Create a bitmap to draw to and select it into the memory DC
     CBitmap bitmap;
     bitmap.CreateCompatibleBitmap( pDC, width_dots, height_dots );
     CBitmap* pOldBitmap = dcMem.SelectObject( &bitmap );

     // Fill the DC with a white rectangle
     CBrush whiteBrush( PALETTERGB(255,255,255) );
     dcMem.FillRect( CRect( 0, 0, width_dots, height_dots ), &whiteBrush );

	   // Draw the overlays
     CRect clipRect( 0, 0, width_dots, height_dots );
     drawOverlays( &dcMem, &clipRect, 0, overlays.size() - 1 );

     // Blt the memory bitmap to the display
     pDC->StretchBlt( 0, 0, width_pix, height_pix, &dcMem, 0, 0, width_dots,
                      height_dots, SRCCOPY );

     // Restore the DCs
     dcMem.SelectObject( pOldBitmap );
     if ( NULL != pOldPalette )
     {
        pDC->SelectPalette( pOldPalette, FALSE );
     }
  }

	// Restore the old background color
	GraphicsObject::setBgColor( oldBgColor );

  // Restore old viewport
	pMapping->setViewportExtents( v_x1, v_y1, v_x2, v_y2 );

	// Restore old window
	pMapping->setWindowExtents( w_x1, w_y1, w_x2, w_y2 );
}

/////////////////////////////////////////////////////////////////////////////
// CDlgv32View message handlers

void 
CDlgv32View::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// This function is called before CView::OnDraw is called
	
	// Call the base classes version of this function
	CView::OnPrepareDC(pDC, pInfo);

	// Set the device contexts mapping mode.  The mode will be one of the following:
	//   MM_HIMETRIC - each logical unit gets mapped to 0.01 mm on the device
	//                 and the axis are oriented such that y increases up
	//   MM_LOMETRIC - each logical unit gets mapped to 0.1  mm on the device
	//                 and the axis are oriented such that y increases up
	//   MM_TEXT     - each logical unit gets mapped to 1 device pixel
	//				   and the axis are oriented such that y increases down
	pDC->SetMapMode( MM_TEXT );
}

void 
CDlgv32View::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	Invalidate();	// Invalidate the entire client area	
}

void 
CDlgv32View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// Let the current controller handle it if it isn't null
	if ( d_pCurrentController != 0 )
	{
		d_pCurrentController->OnLButtonDown( nFlags, point );
	}
	
	CView::OnLButtonDown(nFlags, point);
}

void 
CDlgv32View::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// Let the current controller handle it if it isn't null
	if ( d_pCurrentController != 0 )
	{
		d_pCurrentController->OnRButtonDown( nFlags, point );
	}
	
	CView::OnRButtonDown(nFlags, point);
}

void CDlgv32View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

	// Update the viewport of the mapping
	CRect clientRect;
	GetClientRect( &clientRect );
	CoordinateTransforms::getCurrentMapping()->setViewportExtents( 0,
                                                     clientRect.Height(),
		                                                 clientRect.Width(), 0 );
}

void CDlgv32View::OnToolsZoom() 
{
	// Cleanup the current controller if it exists otherwise
	// create one
	if ( d_pCurrentController != 0 )
	{
		d_pCurrentController->cleanup();
	}

	// Create the controller if it doesn't exist
	if ( d_pZoomController == 0 )
	{
		d_pZoomController = new ZoomController( this );
	}
	
	// Set the current controller to the zoom controller
	d_pCurrentController = d_pZoomController;	
}

void CDlgv32View::OnUpdateToolsZoom(CCmdUI* pCmdUI) 
{
	if ( d_pCurrentController == d_pZoomController )
	{
		pCmdUI->SetCheck();
	}
	else
	{
		pCmdUI->SetCheck( 0 );
	}
}

void CDlgv32View::OnToolsPan() 
{
	// Cleanup the current controller if it exists otherwise
	// create one
	if ( d_pCurrentController != 0 )
	{
		d_pCurrentController->cleanup();
	}

	// Create the controller if it doesn't exist
	if ( d_pPanController == 0 )
	{
		d_pPanController = new PanController( this );
	}
	
	// Set the current controller to the pan controller
	d_pCurrentController = d_pPanController;	
}

void CDlgv32View::OnUpdateToolsPan(CCmdUI* pCmdUI) 
{
	if ( d_pCurrentController == d_pPanController )
	{
		pCmdUI->SetCheck();
	}
	else
	{
		pCmdUI->SetCheck( 0 );
	}
}

void CDlgv32View::OnMouseMove(UINT nFlags, CPoint point) 
{
	// Let the current controller handle it if it isn't null
	if ( d_pCurrentController != 0 )
	{
		d_pCurrentController->OnMouseMove( nFlags, point );

		// Capture the mouse if we haven't already
		if ( this != GetCapture() )
		{
			SetCapture();
		}
		// Release the capture if the mouse is outside of the client rect
		else if ( OnNcHitTest( point ) != HTCLIENT )
		{
			d_pCurrentController->erase();
			ReleaseCapture();
		}
	}

	// Update the current mouse position for use on status bar
	d_currentMousePos = point;
	
	CView::OnMouseMove(nFlags, point);
}

void CDlgv32View::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// Let the current controller handle it if it isn't null
	if ( d_pCurrentController != 0 )
	{
		d_pCurrentController->OnLButtonUp( nFlags, point );
	}
	
	CView::OnLButtonUp(nFlags, point);
}

void CDlgv32View::OnUpdateCurrentTool(CCmdUI* pCmdUI)
{
	pCmdUI->Enable();

	// Set the text to whatever the current controller is
	if ( d_pCurrentController != 0 )
	{
		pCmdUI->SetText( d_pCurrentController->getText() );
	}
}

void CDlgv32View::OnUpdateCurrentMousePosLatLong(CCmdUI* pCmdUI)
{
	int overlaysLoaded = 
    GetDocument()->getOverlayFactory().getNumOverlaysLoaded();

	// Enable the status bar pane if at least one overlay is loaded
	// otherwise exit the update handler
	pCmdUI->Enable( overlaysLoaded > 0 );

	if ( overlaysLoaded == 0 )
	{
		return;		
	}

	// Return if the mouse isn't currently in the client area
	CRect clientRect;
	GetClientRect( &clientRect );
	if ( !clientRect.PtInRect( d_currentMousePos ) )
	{
		return;
	}

	if ( NULL != CoordinateTransforms::getProjection() )
	{
		// Convert point from device coordinates to GndRefSys
		double x, y;
		CPoint mousePos( d_currentMousePos );
		CClientDC dc( this );
		OnPrepareDC( &dc );
		dc.DPtoLP( &mousePos );
		x = mousePos.x;
		y = mousePos.y;
		CoordinateTransforms::LPtoGndRefSys( x, y );

		// Set the text on the status bar
		pCmdUI->SetText( CoordinateTransforms::GndRefSystoLatLong( x, y ) );
	}
	else
	{
		pCmdUI->SetText( "UNKNOWN PROJ SYS" );
	}
}

void CDlgv32View::OnUpdateCurrentMousePosGndRefSys(CCmdUI* pCmdUI)
{
	int overlaysLoaded = 
    GetDocument()->getOverlayFactory().getNumOverlaysLoaded();

	// Enable the status bar pane if at least one overlay is loaded
	// otherwise exit the update handler
	pCmdUI->Enable( overlaysLoaded > 0 );

	if ( overlaysLoaded == 0 )
	{
		return;		
	}

	// Return if the mouse isn't currently in the client area
	CRect clientRect;
	GetClientRect( &clientRect );
	if ( !clientRect.PtInRect( d_currentMousePos ) )
	{
		return;
	}
	
	// Convert point from device coordinates to GndRefSys
	double x, y;
	CPoint mousePos( d_currentMousePos );
	CClientDC dc( this );
	OnPrepareDC( &dc );
	dc.DPtoLP( &mousePos );
	x = mousePos.x;
	y = mousePos.y;
	CoordinateTransforms::LPtoGndRefSys( x, y );

	// Make a coordinate pair out of the GndRefSys point
	CString strCoordinate;
  PROJSYS curProj = UNKNOWN_PROJSYS;
  if ( NULL != CoordinateTransforms::getProjection() )
  {
    curProj = CoordinateTransforms::getProjection()->getProjectionSystem();
  }
	strCoordinate.Format( "%s - ( %.2f, %.2f )", 
                        CoordinateTransforms::projectionToString( curProj ),
                        x, y );

	// Put the coordinates on the status bar
  pCmdUI->SetText( strCoordinate );
}

void CDlgv32View::OnToolsDistance() 
{
	// Cleanup the current controller if it exists otherwise
	// create one
	if ( d_pCurrentController != 0 )
	{
		d_pCurrentController->cleanup();
	}

	// Create the controller if it doesn't exist
	if ( d_pDistanceController == 0 )
	{
		d_pDistanceController = new DistanceController( this );
	}
	
	// Set the current controller to the pan controller
	d_pCurrentController = d_pDistanceController;	
}

void CDlgv32View::OnUpdateToolsDistance(CCmdUI* pCmdUI) 
{
	if ( d_pCurrentController == d_pDistanceController )
	{
		pCmdUI->SetCheck();
	}
	else
	{
		pCmdUI->SetCheck( 0 );
	}
}

void CDlgv32View::OnToolsPick() 
{
	// Cleanup the current controller if it exists
	if ( d_pCurrentController != 0 )
	{
		d_pCurrentController->cleanup();
	}

	// Create the controller if it doesn't exist
	if ( d_pPickController == 0 )
	{
		d_pPickController = new PickController( this );
	}
	
	// Set the current controller to the pan controller
	d_pCurrentController = d_pPickController;	
}

void CDlgv32View::OnUpdateToolsPick(CCmdUI* pCmdUI) 
{
	if ( d_pCurrentController == d_pPickController )
	{
		pCmdUI->SetCheck();
	}
	else
	{
		pCmdUI->SetCheck( 0 );
	}
}

void CDlgv32View::OnToolsPolyRegion() 
{
	// Cleanup the current controller if it exists
	if ( NULL != d_pCurrentController )
	{
		d_pCurrentController->cleanup();
	}

	// Create the controller if it doesn't exist
	if ( NULL == d_pPolyRegionController )
	{
		d_pPolyRegionController = new PolyRegionController( this );
	}
	
	// Set the current controller to the pan controller
	d_pCurrentController = d_pPolyRegionController;	
}

void CDlgv32View::OnUpdateToolsPolyRegion(CCmdUI* pCmdUI) 
{
	if ( d_pCurrentController == d_pPolyRegionController )
	{
		pCmdUI->SetCheck();
	}
	else
	{
		pCmdUI->SetCheck( 0 );
	}
}

void CDlgv32View::cleanupControllers()
{
	if ( d_pZoomController != 0 )
	{
		d_pZoomController->cleanup();
	}

	if ( d_pPanController != 0 )
	{
		d_pPanController->cleanup();
	}

	if ( d_pDistanceController != 0 )
	{
		d_pDistanceController->cleanup();
	}

	if ( d_pPickController != 0 )
	{
		d_pPickController->cleanup();
	}

	if ( d_pPolyRegionController != 0 )
	{
		d_pPolyRegionController->cleanup();
	}
}

void CDlgv32View::OnBgColor() 
{
	CColorDialog colorDlg( GraphicsObject::getBgColor() & RGB(255,255,255) );

	// invoke the dialog box
	if ( colorDlg.DoModal() == IDOK )
	{
		// Get a device context from this view
		CClientDC dc( this );
		OnPrepareDC( &dc );

		// Set the background color to the user selected color
		COLORREF color = colorDlg.GetColor();
		color |= 0x02000000;	// Make palette RGB

    if ( GraphicsObject::getBgColor() != color )
    {
	    GraphicsObject::setBgColor( color );
      RasterOverlay::invalidateAllCaches();
    }
	}

	// Invalidate the view and update it
	Invalidate();
	UpdateWindow();

	return;	
}

BOOL CDlgv32View::OnEraseBkgnd(CDC* pDC) 
{
  // Set brush to desired background color
  CBrush backBrush( GraphicsObject::getBgColor() );

  // Save old brush
  CBrush* pOldBrush = pDC->SelectObject( &backBrush );

	// Get the clipping area
  CRect rect;
  pDC->GetClipBox(&rect);

	// BitBlt the pattern to the client rectangle
  pDC->PatBlt( rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY );
    
	// Restore the state of the DC
	pDC->SelectObject( pOldBrush );

	// Return true since it was handled
	return TRUE;
}

BOOL CDlgv32View::OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT message )
{
	// Set the cursor to that of the current controller if there is one
	// Otherwise call the default function
	if ( NULL != d_pCurrentController )
	{
		::SetCursor( d_pCurrentController->getCursor() );	
		return TRUE;
	}
	else
	{
		return CView::OnSetCursor( pWnd, nHitTest, message );
	}
}

void CDlgv32View::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( GetDocument()->getOverlayFactory().getNumOverlaysLoaded() >
    0 );	
}

void CDlgv32View::OnUpdateFilePrintPreview(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( GetDocument()->getOverlayFactory().getNumOverlaysLoaded() >
    0 );	
}

BOOL CDlgv32View::OnIdle( UINT lCount )
{
	static CPoint point(0,0);

	// Do nothing if the mouse hasn't moved
	if ( point == d_currentMousePos )
	{
		return FALSE;
	}
	else
	{
		point = d_currentMousePos;
	}

	// Get the view's document
	CDlgv32Doc* pDoc = GetDocument();

	// Create the default pick rectangle
	CRect pickRect( point.x - 10, point.y + 10,
                  point.x + 10, point.y - 10 );	
	pickRect.NormalizeRect();
		
	// Get the client rectangle from the view
	CRect clientRect;
	GetClientRect( &clientRect );

	// Get the status bar
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	MCStatusBar* pStatusBar = pMainFrame->GetStatusBar();

	// Get the browse string and show it if one was returned
  CString strBrowse;
	if ( pDoc->getBrowseText( pickRect, clientRect, strBrowse ) )
	{
		// Set the status bar's text
		pStatusBar->SetPaneText( 0, strBrowse );
		pStatusBar->UpdateWindow();
	}
	// Clear the status bar if nothing was picked
	else
	{
		// Set the status bar's text
		pStatusBar->SetPaneText( 0, "" );
		pStatusBar->UpdateWindow();
	}

    // Allow the current controller to do some idle processing
    if ( d_pCurrentController )
	{
		return d_pCurrentController->OnIdle( lCount );
	}

	return FALSE;
}
