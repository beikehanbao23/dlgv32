// DeveloperInfoDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DeveloperInfoDialog dialog

class DeveloperInfoDialog : public CDialog
{
// Construction
public:
	DeveloperInfoDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DeveloperInfoDialog)
	enum { IDD = IDD_EASTEREGG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DeveloperInfoDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DeveloperInfoDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
