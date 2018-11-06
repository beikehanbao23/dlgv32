#if !defined(AFX_DLGOCONTROLPOINTSPROPERTYPAGE_H__8C79AAB1_4F33_11D1_BE18_006097096D7B__INCLUDED_)
#define AFX_DLGOCONTROLPOINTSPROPERTYPAGE_H__8C79AAB1_4F33_11D1_BE18_006097096D7B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DLGOControlPointsPropertyPage.h : header file
//

#include "dlg/DLGHeader.hxx"

/////////////////////////////////////////////////////////////////////////////
// DLGOControlPointsPropertyPage dialog

class DLGOControlPointsPropertyPage : public CPropertyPage
{
	DECLARE_DYNCREATE(DLGOControlPointsPropertyPage)

// Construction
public:
	void initSpinner();
	DLGOControlPointsPropertyPage();
	DLGOControlPointsPropertyPage( const DLGHeader& header );
	~DLGOControlPointsPropertyPage();

// Dialog Data
	//{{AFX_DATA(DLGOControlPointsPropertyPage)
	enum { IDD = IDD_DLGO_CONTROLPOINTS };
	CSpinButtonCtrl	d_spinner;
	CString	d_strLabel;
	CString	d_strID;
	CString	d_strLatitude;
	CString	d_strLongitude;
	CString	d_strX;
	CString	d_strY;
	CString	d_strNumber;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(DLGOControlPointsPropertyPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void updateControlPoints( int number );
	DLGHeader d_header;
	// Generated message map functions
	//{{AFX_MSG(DLGOControlPointsPropertyPage)
	afx_msg void OnDeltaposDlgoControlpointSpin(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOCONTROLPOINTSPROPERTYPAGE_H__8C79AAB1_4F33_11D1_BE18_006097096D7B__INCLUDED_)
