// LoadingDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoadingDialog dialog

#include "resource.h"

class CLoadingDialog : public CDialog
{
// Construction
public:
	CLoadingDialog(CWnd* pParent = NULL);   // standard constructor
    ~CLoadingDialog() { DestroyWindow(); };

// Dialog Data
	//{{AFX_DATA(CLoadingDialog)
	enum { IDD = IDD_LOADING_DIALOG };
	CProgressCtrl	d_progressControl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoadingDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLoadingDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
