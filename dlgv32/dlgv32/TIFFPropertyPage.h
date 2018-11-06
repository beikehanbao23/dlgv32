#if !defined(AFX_TIFFPROPERTYPAGE_H__9CDFF081_4CB4_11D1_BE15_006097096D7B__INCLUDED_)
#define AFX_TIFFPROPERTYPAGE_H__9CDFF081_4CB4_11D1_BE15_006097096D7B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// TIFFPropertyPage.h : header file
//
#include "resource.h"

// Forward declarations
class TIFFOverlay;

/////////////////////////////////////////////////////////////////////////////
// TIFFPropertyPage dialog

class TIFFPropertyPage : public CPropertyPage
{
	DECLARE_DYNCREATE(TIFFPropertyPage)

// Construction
public:
    TIFFPropertyPage();
	TIFFPropertyPage( TIFFOverlay* pTIFF );
	~TIFFPropertyPage();

// Dialog Data
	//{{AFX_DATA(TIFFPropertyPage)
	enum { IDD = IDD_TIFF_METADATA };
	CString	d_strPhotometricInterp;
	CString	d_strBPP;
	CString	d_strRowsPerStrip;
	CString	d_strCopyright;
	CString	d_strDateTime;
	CString	d_strDescription;
	CString	d_strLength;
	CString	d_strWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(TIFFPropertyPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(TIFFPropertyPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIFFPROPERTYPAGE_H__9CDFF081_4CB4_11D1_BE15_006097096D7B__INCLUDED_)
