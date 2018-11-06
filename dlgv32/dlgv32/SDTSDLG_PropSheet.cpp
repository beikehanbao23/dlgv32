// SDTSDLG_PropSheet.cpp : implementation file
//

#include "stdafx.h"
#include "dlgv32.h"
#include "SDTSDLG_PropSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SDTSDLG_PropSheet

IMPLEMENT_DYNAMIC(SDTSDLG_PropSheet, CPropertySheet)

SDTSDLG_PropSheet::SDTSDLG_PropSheet( LPCTSTR pszCaption, sb_Ident* pIdent, const CString& strProjection,
                                      long numAreas, long numNodes, long numDegLines, 
                                      long numLines, long numPolygons, 
                                      sb_AttAccuracy** ppDQAA,  sb_Completeness** ppDQCG, 
                                      sb_Lineage** ppDQHL, sb_LogicalConsis** ppDQLC, 
                                      sb_PosAccuracy** ppDQPA, SDTS_AttModule** ppAHDR,
                                      int ahdrRecNum, CWnd* pParentWnd, UINT iSelectPage)
:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
    SetupPages( pIdent, strProjection, numAreas, numNodes, numDegLines, numLines, numPolygons,
                ppDQAA, ppDQCG, ppDQHL, ppDQLC, ppDQPA, ppAHDR, ahdrRecNum );

    // Remove Apply button
    m_psh.dwFlags |= PSH_NOAPPLYNOW;
}

SDTSDLG_PropSheet::~SDTSDLG_PropSheet()
{
}


BEGIN_MESSAGE_MAP(SDTSDLG_PropSheet, CPropertySheet)
	//{{AFX_MSG_MAP(SDTSDLG_PropSheet)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SDTSDLG_PropSheet message handlers

void 
SDTSDLG_PropSheet::SetupPages( sb_Ident* pIdent, const CString& strProjection,
                               long numAreas, long numNodes, long numDegLines, 
                               long numLines, long numPolygons, sb_AttAccuracy** ppDQAA, 
                               sb_Completeness** ppDQCG, sb_Lineage** ppDQHL, 
                               sb_LogicalConsis** ppDQLC, sb_PosAccuracy** ppDQPA,
                               SDTS_AttModule** ppAHDR, int ahdrRecNum )
{
    // Setup and add iden page
    d_idenPage.SetIden( pIdent );
    d_idenPage.SetProjection( strProjection );
    AddPage( &d_idenPage );

    // Setup and add transfer stats page
    d_statPage.SetValues( numAreas, numNodes, numDegLines, numLines, numPolygons );
    AddPage( &d_statPage );

    // Setup and add data quality pages
    d_dataQualityPage.SetValues( ppDQAA, ppDQCG, ppDQHL, ppDQLC, ppDQPA );
    AddPage( &d_dataQualityPage );

    // Setup and add AHDR page
    d_ahdrPage.setModule( ppAHDR, ahdrRecNum );
    AddPage( &d_ahdrPage );
}

void SDTSDLG_PropSheet::OnClose() 
{
    // Just hide window
    ShowWindow( SW_HIDE );
}
