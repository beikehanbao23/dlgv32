// DLGOPropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "dlgv32.h"
#include "DLGOPropertySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DLGOPropertySheet

IMPLEMENT_DYNAMIC(DLGOPropertySheet, CPropertySheet)

DLGOPropertySheet::DLGOPropertySheet( UINT nIDCaption, const DLGHeader& header, 
                                      const Projection* pProj,
                                      CWnd* pParentWnd, UINT iSelectPage )
: CPropertySheet(nIDCaption, pParentWnd, iSelectPage),
  d_headerPage(header,pProj), d_controlPointsPage(header),
  d_categoryPage(header)
{
  // Add the header info page
  AddPage( &d_headerPage );

  // Add the control points page
  AddPage( &d_controlPointsPage );

  // Add the category page
  AddPage( &d_categoryPage );
}

DLGOPropertySheet::DLGOPropertySheet( LPCTSTR pszCaption, 
                                      const DLGHeader& header, 
                                      const Projection* pProj, 
                                      CWnd* pParentWnd, UINT iSelectPage )
: CPropertySheet(pszCaption, pParentWnd, iSelectPage),
  d_headerPage(header,pProj), d_controlPointsPage(header),
  d_categoryPage(header)
{
  // Add the header info page
  AddPage( &d_headerPage );

  // Add the control points page
  AddPage( &d_controlPointsPage );

  // Add the category page
  AddPage( &d_categoryPage );
}

DLGOPropertySheet::~DLGOPropertySheet()
{
}


BEGIN_MESSAGE_MAP(DLGOPropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(DLGOPropertySheet)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void DLGOPropertySheet::OnClose() 
{
	// Just hide the window
    ShowWindow( SW_HIDE );
}
