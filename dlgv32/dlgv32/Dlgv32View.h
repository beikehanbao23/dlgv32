// dlgv32View.h : interface of the CDlgv32View class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _DLGV32VIEW_H_
#define _DLGV32VIEW_H_

// Forward declarations
class CDlgv32Doc;
class Controller;

class CDlgv32View : public CView
{
protected:
	// Protected data members
	Controller* d_pCurrentController;
	Controller* d_pPanController;
	Controller* d_pZoomController;
	Controller* d_pDistanceController;
	Controller* d_pPickController;
	Controller* d_pPolyRegionController;
  CPalette*   d_pHalftonePalette;

	// Protected constructor
	CDlgv32View();

	// MFC specific macro call
	DECLARE_DYNCREATE(CDlgv32View)

// Attributes
public:
	void cleanupControllers();
	CDlgv32Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgv32View)
	//}}AFX_VIRTUAL
	virtual void OnDraw( CDC* pDC );
	virtual BOOL PreCreateWindow( CREATESTRUCT& cs );
	virtual void OnPrepareDC( CDC* pDC, CPrintInfo* pInfo = NULL );
	virtual void OnUpdate( CView* pSender, LPARAM lHint, CObject* pHint );
	virtual void OnPrint( CDC* pDC, CPrintInfo* pInfo );
	virtual BOOL OnPreparePrinting( CPrintInfo* pInfo );
	virtual void OnBeginPrinting( CDC* pDC, CPrintInfo* pInfo );
	virtual void OnEndPrinting( CDC* pDC, CPrintInfo* pInfo );
	virtual BOOL OnIdle( UINT lCount );

// Implementation
public:
	// Virtual destructor
	virtual ~CDlgv32View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CDlgv32View)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnToolsZoom();
	afx_msg void OnUpdateToolsZoom(CCmdUI* pCmdUI);
	afx_msg void OnToolsPan();
	afx_msg void OnUpdateToolsPan(CCmdUI* pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnToolsDistance();
	afx_msg void OnUpdateToolsDistance(CCmdUI* pCmdUI);
	afx_msg void OnToolsPick();
	afx_msg void OnUpdateToolsPick(CCmdUI* pCmdUI);
	afx_msg void OnBgColor();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnToolsPolyregion();
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	//}}AFX_MSG
	
	afx_msg BOOL OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT message );
	afx_msg void OnToolsPolyRegion();
	afx_msg void OnUpdateToolsPolyRegion(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCurrentTool(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCurrentMousePosGndRefSys(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCurrentMousePosLatLong(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
private:
  void   drawOverlays( CDC* pDC, CRect* pClipRect, int first, int last );
	CPoint d_currentMousePos;
  bool   d_bIsWin95;
};

#ifndef _DEBUG  // debug version in dlgv32View.cpp
inline CDlgv32Doc* CDlgv32View::GetDocument()
   { return (CDlgv32Doc*)m_pDocument; }
#endif

#endif
/////////////////////////////////////////////////////////////////////////////
