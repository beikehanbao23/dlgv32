#if !defined(AFX_DLGOHEADERPROPERTYPAGE_H__0A3C01D0_4F23_11D1_BE18_006097096D7B__INCLUDED_)
#define AFX_DLGOHEADERPROPERTYPAGE_H__0A3C01D0_4F23_11D1_BE18_006097096D7B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DLGOHeaderPropertyPage.h : header file
//

// Forward declarations
class DLGHeader;
class Projection;

/////////////////////////////////////////////////////////////////////////////
// DLGOHeaderPropertyPage dialog

class DLGOHeaderPropertyPage : public CPropertyPage
{
	DECLARE_DYNCREATE(DLGOHeaderPropertyPage)

// Construction
public:
	DLGOHeaderPropertyPage();
	DLGOHeaderPropertyPage( const DLGHeader& header, const Projection* pProj );
	~DLGOHeaderPropertyPage();

// Dialog Data
	//{{AFX_DATA(DLGOHeaderPropertyPage)
	enum { IDD = IDD_DLGO_HEADERINFO };
	CString	d_strBanner;
	CString	d_strDateQualifier;
	CString	d_strDCUName;
	CString	d_strLevelCode;
	CString	d_strResolution;
	CString	d_strSourceDate;
	CString	d_strSourceScale;
	CString	d_strVDatum;
	CString	d_strProjection;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(DLGOHeaderPropertyPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(DLGOHeaderPropertyPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOHEADERPROPERTYPAGE_H__0A3C01D0_4F23_11D1_BE18_006097096D7B__INCLUDED_)
