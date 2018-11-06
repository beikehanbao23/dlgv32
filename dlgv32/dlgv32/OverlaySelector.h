// OverlaySelector.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// OverlaySelector dialog

#include "GeographicOverlay.h"
#include "resource.h"
#include <list>
using namespace std;

class OverlaySelector : public CDialog
{
// Construction
public:
	OverlaySelector(CWnd* pParent = NULL);   // standard constructor  
	~OverlaySelector();
	void setOverlays( list<GeographicOverlay*>& overlays );
	void getSelected( int*& pSelected, int& numSelected );

// Dialog Data
	//{{AFX_DATA(OverlaySelector)
	enum { IDD = IDD_CLIPPING_REGION_SELECTOR };
	CButton	d_okButton;
	CButton	d_deselectAllButton;
	CButton	d_selectAllButton;
	CListBox	d_overlaysList;
	int		d_combineMode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(OverlaySelector)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
  list<GeographicOverlay*>* d_pOverlays;
	int d_numSelected;
	int* d_pSelected;

	// Generated message map functions
	//{{AFX_MSG(OverlaySelector)
	afx_msg void OnSelectAllOverlays();
	afx_msg void OnDeselectAll();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
