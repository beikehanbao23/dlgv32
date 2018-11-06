#if !defined(AFX_DLGOCATEGORYPROPERTYPAGE_H__735FB601_4FF5_11D1_BE19_006097096D7B__INCLUDED_)
#define AFX_DLGOCATEGORYPROPERTYPAGE_H__735FB601_4FF5_11D1_BE19_006097096D7B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DLGOCategoryPropertyPage.h : header file
//

// Forward declaration
class DLGHeader;

/////////////////////////////////////////////////////////////////////////////
// DLGOCategoryPropertyPage dialog

class DLGOCategoryPropertyPage : public CPropertyPage
{
	DECLARE_DYNCREATE(DLGOCategoryPropertyPage)

// Construction
public:
	DLGOCategoryPropertyPage();
    DLGOCategoryPropertyPage( const DLGHeader& header );
	~DLGOCategoryPropertyPage();

// Dialog Data
	//{{AFX_DATA(DLGOCategoryPropertyPage)
	enum { IDD = IDD_DLGO_CATEGORY_DIALOG };
	CString	d_strActualAreas;
	CString	d_strActualLines;
	CString	d_strActualNodes;
	CString	d_strALLinkage;
	CString	d_strANLinkage;
	CString	d_strAreaCoordList;
	CString	d_strAreasRef;
	CString	d_strCategoryID;
	CString	d_strCategoryName;
	CString	d_strFormatCodes;
	CString	d_strLineCoordList;
	CString	d_strLinesRef;
	CString	d_strNALinkage;
	CString	d_strNLLinkage;
	CString	d_strNodesRef;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(DLGOCategoryPropertyPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(DLGOCategoryPropertyPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOCATEGORYPROPERTYPAGE_H__735FB601_4FF5_11D1_BE19_006097096D7B__INCLUDED_)
