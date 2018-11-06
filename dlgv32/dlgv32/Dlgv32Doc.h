// dlgv32Doc.h : interface of the CDlgv32Doc class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _DLGV32DOC_H_
#define _DLGV32DOC_H_

#include "GraphicsLib/Rectangle2D.h"
#include "OverlayFactory.h"
#include <fstream>
using namespace std;

// Forward declarations
class OverlayComponent;	
class CMainPropertiesDialog;
class Projection;

class CDlgv32Doc : public CDocument
{
protected: // create from serialization only
	BOOL                   d_drawNow;
	CMainPropertiesDialog* d_pControlCenter;
	OverlayFactory         d_overlays;
	Rectangle2D            d_boundingRect;
	
	// Variables for saving the state of the open file dialog box
	CString d_initialDirectory;
	DWORD   d_filterIndex;

	// Protected constructor
	CDlgv32Doc();

	// Protected member functions
	void calculateBoundingRect();
	void freeOverlays();

	DECLARE_DYNCREATE(CDlgv32Doc)

public:
  OverlayFactory& getOverlayFactory();
	void OnControlCenterDone();
	void OnControlCenterApply();
	int  pick( const CRect& pickRect, 
        	   CTypedPtrArray< CPtrArray, OverlayComponent* > *oc_list,
			       int start, const CRect& clientRect, int maxToPick = -1 );
  void redraw();
  bool getBrowseText( const CRect& pickRect, const CRect& clientRect, 
                      CString& strBrowse ) const;

  // Projection changed callback function
  static void handleProjectionChanged( LPVOID pArg, 
                                       const Projection* pOldProjection );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgv32Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDlgv32Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CDlgv32Doc)
	afx_msg void OnFileOpenNew();
	afx_msg void OnFileOpenCurrent();
	afx_msg void OnUpdateFileOpenCurrent(CCmdUI* pCmdUI);
	afx_msg void OnFileUnloadAll();
	afx_msg void OnUpdateFileUnloadAll(CCmdUI* pCmdUI);
	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();
	afx_msg void OnUpdateZoomOut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoomIn(CCmdUI* pCmdUI);
	afx_msg void OnViewFullview();
	afx_msg void OnUpdateViewFullview(CCmdUI* pCmdUI);
	afx_msg void OnToolsControlcenter();
	afx_msg void OnUpdateToolsControlcenter(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHelpFinder(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	// Helper functions
	CString getDirectory( const CString& filename ) const;
};

/////////////////////////////////////////////////////////////////////////////

// inline function definitions
inline OverlayFactory&
CDlgv32Doc::getOverlayFactory()
{
    return d_overlays;
}

#endif