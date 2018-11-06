// PickDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPickDialog dialog

#ifndef _PICKDIALOG_H_
#define _PICKDIALOG_H_

#include "StdAfx.h"
#include "resource.h"

class CPickDialog : public CDialog
{
// Construction
public:
  void initColumns();
  void setColumnTitles( const CString& strCol1, const CString& strCol2 );
  void addRow( const CString& strCol1, const CString& strCol2 );
  void addMajorMinorPair( short major, short minor );
  void clearColumns();
	BOOL Create( UINT nIDTemplate = CPickDialog::IDD, CWnd* pParentWnd = NULL );
	BOOL created() const;
  void setEntityDesc( const CString& strEntityDesc );
	~CPickDialog();
	CPickDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPickDialog)
	enum { IDD = IDD_PICK_DIALOG };
	CListCtrl	d_attribCodeList;
	CString	d_ID;
	CString	d_elemType;
	CString	d_category;
	CString	d_DCUName;
	CString	d_strEntityDesc;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPickDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    void setColumnTitle( UINT column, const CString& strTitle );
    void resizeColumns();
	BOOL d_created;

	// Generated message map functions
	//{{AFX_MSG(CPickDialog)
	//}}AFX_MSG 
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};

#endif
