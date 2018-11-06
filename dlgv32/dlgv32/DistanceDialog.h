// DistanceDialog.h : header file
//

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CDistanceDialog dialog

class CDistanceDialog : public CDialog
{
// Construction
public:
	void setDistanceMeters( double dist );
	CDistanceDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDistanceDialog)
	enum { IDD = IDD_DISTANCE };
	CStatic	d_distanceCtl;
	int		d_units;
	CString	d_distance;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDistanceDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	double  d_distMeters;

	// Generated message map functions
	//{{AFX_MSG(CDistanceDialog)
	afx_msg void OnMeters();
	afx_msg void OnFeet();
	afx_msg void OnKilometers();
	afx_msg void OnMiles();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
