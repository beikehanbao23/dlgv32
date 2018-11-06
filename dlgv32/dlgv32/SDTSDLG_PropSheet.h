#if !defined(AFX_SDTSDLG_PROPSHEET_H__9C695113_27B8_11D1_BDEE_006097096D7B__INCLUDED_)
#define AFX_SDTSDLG_PROPSHEET_H__9C695113_27B8_11D1_BDEE_006097096D7B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Page includes
#include "SDTSDLG_AHDRPage.h"
#include "SDTSDLG_DataQualityPage.h"
#include "SDTSDLG_IdenPage.h"
#include "SDTSDLG_StatPage.h"

// SDTSDLG_PropSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SDTSDLG_PropSheet

// Forward declarations
class sb_AttAccuracy;
class sb_Completeness;
class sb_Ident;
class sb_Lineage;
class sb_LogicalConsis;
class sb_PosAccuracy;
class SDTS_AttModule;

class SDTSDLG_PropSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(SDTSDLG_PropSheet)

// Construction
public:
	SDTSDLG_PropSheet( LPCTSTR pszCaption, sb_Ident* pIdent, const CString& strProjection,
                       long numAreas, long numNodes, 
                       long numDegLines, long numLines, long numPolygons,
                       sb_AttAccuracy** ppDQAA, sb_Completeness** ppDQCG,
                       sb_Lineage** ppDQHL, sb_LogicalConsis** ppDQLC,
                       sb_PosAccuracy** ppDQPA, SDTS_AttModule** ppAHDR, int ahdrRecNum,
                       CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SDTSDLG_PropSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~SDTSDLG_PropSheet();

	// Generated message map functions
protected:
	void SetupPages( sb_Ident* pIdent, const CString& strProjection, long numAreas, 
                     long numNodes, long numDegLines, long numLines, long numPolygons,
                     sb_AttAccuracy** ppDQAA, sb_Completeness** ppDQCG,
                     sb_Lineage** ppDQHL, sb_LogicalConsis** ppDQLC,
                     sb_PosAccuracy** ppDQPA, SDTS_AttModule** ppAHDR, int ahdrRecNum );

    // Pages
    SDTSDLG_AHDRPage        d_ahdrPage;
    SDTSDLG_DataQualityPage d_dataQualityPage;
	SDTSDLG_IdenPage        d_idenPage;
    SDTSDLG_StatPage        d_statPage;
	//{{AFX_MSG(SDTSDLG_PropSheet)
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDTSDLG_PROPSHEET_H__9C695113_27B8_11D1_BDEE_006097096D7B__INCLUDED_)
