// ShaderOptionsPage.cpp : implementation file
//

#include "stdafx.h"
#include "dlgv32.h"
#include "ShaderOptionsPage.h"
#include "ps_PixelShader.h"
#include "PropertySheetApplyHandler.h"
#include "RasterOverlay.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ShaderOptionsPage property page

IMPLEMENT_DYNCREATE(ShaderOptionsPage, CPropertyPage)

ShaderOptionsPage::ShaderOptionsPage() 
: CPropertyPage(ShaderOptionsPage::IDD), d_bIsModified(false), d_bSetup(true)
{
	//{{AFX_DATA_INIT(ShaderOptionsPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

ShaderOptionsPage::~ShaderOptionsPage()
{
}

void ShaderOptionsPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ShaderOptionsPage)
	DDX_Control(pDX, IDC_SHADER_OPTIONS_HSV_RANGE, d_hsvRangeControl);
	DDX_Control(pDX, IDC_SHADER_OPTIONS_HSV_VALUE, d_hsvValueControl);
	DDX_Control(pDX, IDC_SHADER_OPTIONS_HSV_SATURATION, d_hsvSaturationControl);
	DDX_Control(pDX, IDC_SHADER_OPTIONS_HSV_LOW_COLOR_START, d_hsvLowColorStartControl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ShaderOptionsPage, CPropertyPage)
	//{{AFX_MSG_MAP(ShaderOptionsPage)
	ON_BN_CLICKED(IDC_SHADER_OPTIONS_DAYLIGHT_SURFACE_COLOR, OnShaderOptionsDaylightSurfaceColor)
	ON_BN_CLICKED(IDC_SHADER_OPTIONS_GRADIENT_SET_HI_COLOR, OnShaderOptionsGradientSetHiColor)
	ON_BN_CLICKED(IDC_SHADER_OPTIONS_GRADIENT_SET_LO_COLOR, OnShaderOptionsGradientSetLoColor)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ShaderOptionsPage message handlers

void 
ShaderOptionsPage::setShaders( ps_DaylightShader* pDaylightShader,
                               ps_GradientShader* pGradientShader,
                               ps_HSVShader*      pHSVShader )
{
    d_pDaylightShader = pDaylightShader;
    d_pGradientShader = pGradientShader;
    d_pHSVShader      = pHSVShader;

    // Get the settings from the shaders
    const ps_Pixel& dlCol = pDaylightShader->getColor();
    d_daylightSurfaceColor = RGB( dlCol.red, dlCol.green, dlCol.blue );
    const ps_Pixel& lowCol = pGradientShader->getLowColor();
    d_gradientLowColor = RGB( lowCol.red, lowCol.green, lowCol.blue );
    const ps_Pixel& hiCol = pGradientShader->getHighColor();
    d_gradientHighColor = RGB( hiCol.red, hiCol.green, hiCol.blue );
}

BOOL ShaderOptionsPage::OnApply() 
{
    if ( !d_bIsModified )
    {
        return CPropertyPage::OnApply();
    }

    // Set the colors for the shader
    d_pDaylightShader->setColor( ps_Pixel( GetRValue( d_daylightSurfaceColor ),
                                           GetGValue( d_daylightSurfaceColor ),
                                           GetBValue( d_daylightSurfaceColor ) ) );
    d_pGradientShader->setLowColor( ps_Pixel( GetRValue( d_gradientLowColor ),
                                              GetGValue( d_gradientLowColor ),
                                              GetBValue( d_gradientLowColor ) ) );
    d_pGradientShader->setHighColor( ps_Pixel( GetRValue( d_gradientHighColor ),
                                               GetGValue( d_gradientHighColor ),
                                               GetBValue( d_gradientHighColor ) ) );
    d_pHSVShader->setLowColorStart( d_hsvLowColorStartControl.GetPos() );
    d_pHSVShader->setValue( d_hsvValueControl.GetPos() / 100.0 );
    d_pHSVShader->setSaturation( d_hsvSaturationControl.GetPos() / 100.0 );
    d_pHSVShader->setRange( d_hsvRangeControl.GetPos() );

    // Reset the modified flag
    SetModified( FALSE );
    d_bIsModified = false;

    // Clear all the raster stored area buffers
    RasterOverlay::invalidateAllCaches();

    // Call the parent apply handler
    d_pApplyHandler->handleApply();

    return CPropertyPage::OnApply();
}

void ShaderOptionsPage::OnShaderOptionsDaylightSurfaceColor() 
{
    CColorDialog dlg( d_daylightSurfaceColor );
    
    if ( IDOK == dlg.DoModal() )
    {
        // Get the color and set the modified flag
        if ( d_daylightSurfaceColor != dlg.GetColor() )
        {
            d_daylightSurfaceColor = dlg.GetColor();
            SetModified( TRUE );
            d_bIsModified = true;
        }
    }		
}

void ShaderOptionsPage::OnShaderOptionsGradientSetHiColor() 
{
    CColorDialog dlg( d_gradientHighColor );
    
    if ( IDOK == dlg.DoModal() )
    {
        // Get the color and set the modified flag
        if ( d_gradientHighColor != dlg.GetColor() )
        {
            d_gradientHighColor = dlg.GetColor();
            SetModified( TRUE );
            d_bIsModified = true;
        }
    }		
}

void ShaderOptionsPage::OnShaderOptionsGradientSetLoColor() 
{
    CColorDialog dlg( d_gradientLowColor );
    
    if ( IDOK == dlg.DoModal() )
    {
        // Get the color and set the modified flag
        if ( d_gradientLowColor != dlg.GetColor() )
        {
            d_gradientLowColor = dlg.GetColor();
            SetModified( TRUE );
            d_bIsModified = true;
        }
    }		
}

BOOL ShaderOptionsPage::OnSetActive() 
{
    // Setup the HSV Low Color Start control
    d_hsvLowColorStartControl.SetRange( 0, 360, TRUE );
    d_hsvLowColorStartControl.SetPos( static_cast<int>( d_pHSVShader->getLowColorStart() ) );
	
    // Setup the HSV Saturation control
    d_hsvSaturationControl.SetRange( 0, 100, TRUE );
    d_hsvSaturationControl.SetPos( static_cast<int>( d_pHSVShader->getSaturation() * 100.0 ) );

    // Setup the HSV Value control
    d_hsvValueControl.SetRange( 0, 100, TRUE );
    d_hsvValueControl.SetPos( static_cast<int>( d_pHSVShader->getValue() * 100.0 ) );
    
    // Setup the HSV Range control
    d_hsvRangeControl.SetRange( 1, 360 * 4, TRUE );
    d_hsvRangeControl.SetPos( static_cast<int>( d_pHSVShader->getRange() ) );

    return CPropertyPage::OnSetActive();
}

void ShaderOptionsPage::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
    SetModified( TRUE );
    d_bIsModified = true;
	
	CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}
