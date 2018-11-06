// MainPropertiesDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMainPropertiesDialog dialog

#ifndef _MAINPROPERTIESDIALOG_H_
#define _MAINPROPERTIESDIALOG_H_

#include "GeographicOverlay.h"

// Forward declarations
class OverlayFactory; 
class CDlgv32View;	

class CMainPropertiesDialog : public CDialog
{
// Construction
public:
	CMainPropertiesDialog(CWnd* pParent = NULL);   // standard constructor
	~CMainPropertiesDialog();
	void setModifiedFlag( BOOL flag );
	BOOL getModifiedFlag();

protected:
	// Member data
	BOOL d_modified;
    OverlayFactory* d_overlays;

public:
	// Accessor functions
	void setOverlays( OverlayFactory& overlays );

// Dialog Data
	//{{AFX_DATA(CMainPropertiesDialog)
	enum { IDD = IDD_MAIN_PROPERTIES_DIALOG };
	CButton	d_propertiesButton;
	CButton	d_optionsButton;
	CButton	d_closeOverlayButton;
	CButton	d_removeClipsButton;
	CButton	d_hideAllLinesButton;
	CButton	d_hideAllNodesButton;
	CButton	d_hideAllAreasButton;
	CButton	d_showOverlaysButton;
	CListBox	d_overlaysList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainPropertiesDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMainPropertiesDialog)
	afx_msg void OnPropertiesButton();
	afx_msg void OnOptionsButton();
	afx_msg void OnShowOverlay();
	afx_msg void OnSelchangeOverlayList();
	afx_msg void OnCloseOverlay();
	afx_msg void OnDone();
	afx_msg void OnHideAreasAll();
	afx_msg void OnHideNodesAll();
	afx_msg void OnHideLinesAll();
	afx_msg void OnRemoveClips();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CDlgv32View* d_pView;
};

inline BOOL 
CMainPropertiesDialog::getModifiedFlag()
{
	return d_modified;
}

#endif
