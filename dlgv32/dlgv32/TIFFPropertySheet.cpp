// TIFFPropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "dlgv32.h"
#include "GeoTIFFOverlay.h"
#include "TIFFPropertySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TIFFPropertySheet

IMPLEMENT_DYNAMIC(TIFFPropertySheet, CPropertySheet)

TIFFPropertySheet::TIFFPropertySheet( UINT nIDCaption, TIFFOverlay* pTIFF, 
                                      GeoTIFFOverlay* pGeoTIFF, CWnd* pParentWnd, 
                                      UINT iSelectPage)
:CPropertySheet(nIDCaption, pParentWnd, iSelectPage), d_tiffPage(pTIFF), d_geoTIFFPage(pGeoTIFF)
{
    // Add the TIFF property page
    ASSERT( NULL != pTIFF );
    AddPage( &d_tiffPage );

    // Add the GeoTIFF property page if a GeoTIFF was passed in
    if ( NULL != pGeoTIFF )
    {
        AddPage( &d_geoTIFFPage );

        // Add the GeoTIFF vertical metadata page if it's a verital GeoTIFF
        if ( pGeoTIFF->isVertical() )
        {
            d_verticalPage.setOverlay( pGeoTIFF );
            AddPage( &d_verticalPage );
        }
    }

    // Remove Apply button
    m_psh.dwFlags |= PSH_NOAPPLYNOW;
}

TIFFPropertySheet::TIFFPropertySheet( LPCTSTR pszCaption, TIFFOverlay* pTIFF, 
                                      GeoTIFFOverlay* pGeoTIFF, CWnd* pParentWnd, 
                                      UINT iSelectPage)
:CPropertySheet(pszCaption, pParentWnd, iSelectPage), d_tiffPage(pTIFF), d_geoTIFFPage(pGeoTIFF)
{
    // Add the TIFF property page
    ASSERT( NULL != pTIFF );
    AddPage( &d_tiffPage );

    // Add the GeoTIFF property page if a GeoTIFF was passed in
    if ( NULL != pGeoTIFF )
    {
        AddPage( &d_geoTIFFPage );

        // Add the GeoTIFF vertical metadata page if it's a verital GeoTIFF
        if ( pGeoTIFF->isVertical() )
        {
            d_verticalPage.setOverlay( pGeoTIFF );
            AddPage( &d_verticalPage );
        }
    }

    // Remove Apply button
    m_psh.dwFlags |= PSH_NOAPPLYNOW;
}

TIFFPropertySheet::~TIFFPropertySheet()
{
}


BEGIN_MESSAGE_MAP(TIFFPropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(TIFFPropertySheet)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TIFFPropertySheet message handlers

void TIFFPropertySheet::OnClose() 
{
    ShowWindow( SW_HIDE );	
}
