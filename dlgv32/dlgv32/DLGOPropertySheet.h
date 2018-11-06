#if !defined(AFX_DLGOPROPERTYSHEET_H__0A3C01D2_4F23_11D1_BE18_006097096D7B__INCLUDED_)
#define AFX_DLGOPROPERTYSHEET_H__0A3C01D2_4F23_11D1_BE18_006097096D7B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DLGOPropertySheet.h : header file
//

#include "DLGOHeaderPropertyPage.h"
#include "DLGOControlPointsPropertyPage.h"
#include "DLGOCategoryPropertyPage.h"

/////////////////////////////////////////////////////////////////////////////
// DLGOPropertySheet

class Projection; // Forward declaration

class DLGOPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(DLGOPropertySheet)

// Construction
public:
	DLGOPropertySheet( UINT nIDCaption, const DLGHeader& header, 
                     const Projection* pProj, 
                     CWnd* pParentWnd = NULL, UINT iSelectPage = 0 );
	DLGOPropertySheet( LPCTSTR pszCaption, const DLGHeader& header, 
                     const Projection* pProj,
                     CWnd* pParentWnd = NULL, UINT iSelectPage = 0 );

// Property pages
protected:
    DLGOHeaderPropertyPage        d_headerPage;
    DLGOControlPointsPropertyPage d_controlPointsPage;
    DLGOCategoryPropertyPage      d_categoryPage;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DLGOPropertySheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~DLGOPropertySheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(DLGOPropertySheet)
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOPROPERTYSHEET_H__0A3C01D2_4F23_11D1_BE18_006097096D7B__INCLUDED_)
