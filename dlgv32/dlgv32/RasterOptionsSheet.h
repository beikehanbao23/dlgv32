#if !defined(AFX_RASTEROPTIONSSHEET_H__41481643_9D9C_11D1_BE39_006097096D7B__INCLUDED_)
#define AFX_RASTEROPTIONSSHEET_H__41481643_9D9C_11D1_BE39_006097096D7B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RasterOptionsSheet.h : header file
//

#include "RasterOptionsPage.h"
#include "ShaderOptionsPage.h"
#include "VerticalOptionsPage.h"
#include "PropertySheetApplyHandler.h"

// Forward declarations
class CDlgv32Doc;
class RasterOverlay;
class ps_ColorRampShader;
class ps_DaylightShader;
class ps_GradientShader;
class ps_HSVShader;

/////////////////////////////////////////////////////////////////////////////
// RasterOptionsSheet

class RasterOptionsSheet : public CPropertySheet, public PropertySheetApplyHandler
{
	DECLARE_DYNAMIC(RasterOptionsSheet)

// Construction
public:
	RasterOptionsSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	RasterOptionsSheet( LPCTSTR pszCaption, 
                        RasterOverlay*      pOverlay, 
                        ps_DaylightShader*  pDaylightShader,
                        ps_GradientShader*  pGradientShader,
                        ps_HSVShader*       pHSVShader,
                        ps_ColorRampShader* pColorRampShader,
                        CDlgv32Doc*         pDoc,
                        CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RasterOptionsSheet)
	//}}AFX_VIRTUAL

    void handleApply();

// Implementation
public:
	virtual ~RasterOptionsSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(RasterOptionsSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    CDlgv32Doc* d_pDoc;
    RasterOverlay* d_pOverlay;

    // Property pages
    RasterOptionsPage     d_rasterOptionsPage;
    ShaderOptionsPage     d_shaderOptionsPage;
    VerticalOptionsPage   d_verticalOptionsPage;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RASTEROPTIONSSHEET_H__41481643_9D9C_11D1_BE39_006097096D7B__INCLUDED_)
