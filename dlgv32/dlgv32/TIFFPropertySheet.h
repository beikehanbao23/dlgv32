#if !defined(AFX_TIFFPROPERTYSHEET_H__9CDFF082_4CB4_11D1_BE15_006097096D7B__INCLUDED_)
#define AFX_TIFFPROPERTYSHEET_H__9CDFF082_4CB4_11D1_BE15_006097096D7B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TIFFPropertySheet.h : header file
//

#include "TIFFPropertyPage.h"
#include "GeoTIFFPropertyPage.h"
#include "GeoTIFFVerticalMetadataPage.h"

/////////////////////////////////////////////////////////////////////////////
// TIFFPropertySheet

class TIFFPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(TIFFPropertySheet)

// Construction
public:
	TIFFPropertySheet( UINT nIDCaption, TIFFOverlay* pTIFF, GeoTIFFOverlay* pGeoTIFF = NULL,
                       CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	TIFFPropertySheet( LPCTSTR pszCaption, TIFFOverlay* pTIFF, GeoTIFFOverlay* pGeoTIFF = NULL,
                       CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

protected:
    // Data members
    TIFFPropertyPage    d_tiffPage;
    GeoTIFFPropertyPage d_geoTIFFPage;
    GeoTIFFVerticalMetadataPage d_verticalPage;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TIFFPropertySheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~TIFFPropertySheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(TIFFPropertySheet)
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIFFPROPERTYSHEET_H__9CDFF082_4CB4_11D1_BE15_006097096D7B__INCLUDED_)
