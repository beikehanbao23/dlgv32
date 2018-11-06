#if !defined(AFX_SDTSLOADERDIALOG_H__A4FDF021_FFA7_11D0_87F9_006097096B03__INCLUDED_)
#define AFX_SDTSLOADERDIALOG_H__A4FDF021_FFA7_11D0_87F9_006097096B03__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SDTSLoaderDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SDTSLoaderDialog dialog

class SDTSLoaderDialog : public CDialog
{
// Construction
public:
	SDTSLoaderDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SDTSLoaderDialog)
	enum { IDD = IDD_SDTS_LOADER_DIALOG };
	CListCtrl	m_manifoldList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SDTSLoaderDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SDTSLoaderDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDTSLOADERDIALOG_H__A4FDF021_FFA7_11D0_87F9_006097096B03__INCLUDED_)
