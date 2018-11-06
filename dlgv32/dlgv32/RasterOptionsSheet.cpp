// RasterOptionsSheet.cpp : implementation file
//

#include "stdafx.h"
#include "dlgv32.h"
#include "RasterOptionsSheet.h"
#include "RasterOverlay.h"
#include "Dlgv32Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RasterOptionsSheet

IMPLEMENT_DYNAMIC(RasterOptionsSheet, CPropertySheet)

RasterOptionsSheet::RasterOptionsSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

RasterOptionsSheet::RasterOptionsSheet( LPCTSTR pszCaption, 
                                        RasterOverlay* pOverlay, 
                                        ps_DaylightShader* pDaylightShader,
                                        ps_GradientShader* pGradientShader,
                                        ps_HSVShader*      pHSVShader,
                                        ps_ColorRampShader* pColorRampShader,
                                        CDlgv32Doc*        pDoc,
                                        CWnd* pParentWnd, UINT iSelectPage)
:CPropertySheet(pszCaption, pParentWnd, iSelectPage), d_pDoc(pDoc), d_pOverlay(pOverlay)
{
    // Add the raster options page
    d_rasterOptionsPage.setOverlay( pOverlay );
    d_rasterOptionsPage.setSlider( 0, 20, pOverlay->getColorIntensity() );
    d_rasterOptionsPage.setApplyHandler( this );
 	
    // Setup the colors if a paletted image
	if ( pOverlay->getBitsPerPixel() <= 8 )
	{
		d_rasterOptionsPage.setColors( pOverlay->d_bmi.bmiColors, 
                                       pOverlay->getNumImportantColors() );
	}
    AddPage( &d_rasterOptionsPage );

    // Add the vertical stuff if the TIFF is vertical
    if ( pOverlay->isVertical() )
    {
        // Setup and add the vertical options page
        d_verticalOptionsPage.setVerticalUnitString( "meters" );
        d_verticalOptionsPage.setElevationRange( pOverlay->d_shaderInfo.minZ,
                                                 pOverlay->d_shaderInfo.maxZ );
        d_verticalOptionsPage.setOverlay( pOverlay );
        d_verticalOptionsPage.setShaders( &(pOverlay->d_pShader), pDaylightShader, 
                                          pGradientShader, pHSVShader, pColorRampShader );
        d_verticalOptionsPage.setApplyHandler( this );
        AddPage( &d_verticalOptionsPage );

        // Setup and add the shader options page
        d_shaderOptionsPage.setShaders( pDaylightShader, pGradientShader, pHSVShader );
        d_shaderOptionsPage.setApplyHandler( this );
        AddPage( &d_shaderOptionsPage );
    }
}

RasterOptionsSheet::~RasterOptionsSheet()
{
}


BEGIN_MESSAGE_MAP(RasterOptionsSheet, CPropertySheet)
	//{{AFX_MSG_MAP(RasterOptionsSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RasterOptionsSheet message handlers

void
RasterOptionsSheet::handleApply()
{
    if ( d_rasterOptionsPage.isModified() )
    {
        d_rasterOptionsPage.OnApply();
    }

    if ( d_shaderOptionsPage.isModified() )
    {
        d_shaderOptionsPage.OnApply();
    }

    if ( d_verticalOptionsPage.isModified() )
    {
        d_verticalOptionsPage.OnApply();
    }

    // Redraw the overlays
    d_pDoc->redraw();
}