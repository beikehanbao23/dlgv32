// VerticalOptionsPage.cpp : implementation file
//

#include "stdafx.h"
#include "dlgv32.h"
#include "VerticalOptionsPage.h"
#include "ps_PixelShader.h"
#include "PropertySheetApplyHandler.h"
#include "RasterOverlay.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// VerticalOptionsPage property page

IMPLEMENT_DYNCREATE(VerticalOptionsPage, CPropertyPage)

VerticalOptionsPage::VerticalOptionsPage() 
: CPropertyPage(VerticalOptionsPage::IDD), d_minElevation(0), d_maxElevation(100),
  d_bSetup(true), d_bIsModified(false)
{
	//{{AFX_DATA_INIT(VerticalOptionsPage)
	d_strWaterLevel = _T("");
	d_bWaterOn = FALSE;
	d_bLightingEnabled = FALSE;
	//}}AFX_DATA_INIT
}

VerticalOptionsPage::~VerticalOptionsPage()
{
}

void VerticalOptionsPage::DoDataExchange(CDataExchange* pDX)
{
    // Initialize the member variables
    ASSERT( NULL != *d_ppCurrentShader );

    CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(VerticalOptionsPage)
	DDX_Control(pDX, IDC_VERTICAL_OPTIONS_VERT_EXAG, d_vertExagControl);
	DDX_Control(pDX, IDC_VERTICAL_OPTIONS_AMBIENT_LIGHT, d_ambientLightingSlider);
	DDX_Control(pDX, IDC_VERTICAL_OPTIONS_WATER_LEVEL, d_waterLevelSlider);
	DDX_Control(pDX, IDC_VERTICAL_OPTIONS_WATER_ALPHA, d_waterAlphaSlider);
	DDX_Control(pDX, IDC_VERTICAL_OPTIONS_SHADER, d_shadersComboBox);
	DDX_Control(pDX, IDC_VERTICAL_OPTIONS_AZIMUTH_SPINNER, d_azimuthSpinner);
	DDX_Control(pDX, IDC_VERTICAL_OPTIONS_ALTITUDE_SPINNER, d_altitudeSpinner);
	DDX_Text(pDX, IDC_VERTICAL_OPTIONS_WATER_LEVEL_TEXT, d_strWaterLevel);
	DDX_Check(pDX, IDC_VERTICAL_OPTIONS_WATER_ON, d_bWaterOn);
	DDX_Check(pDX, IDC_VERTICAL_OPTIONS_ENABLE_LIGHTING, d_bLightingEnabled);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(VerticalOptionsPage, CPropertyPage)
	//{{AFX_MSG_MAP(VerticalOptionsPage)
	ON_BN_CLICKED(IDC_VERTICAL_OPTIONS_WATER_COLOR, OnVerticalOptionsWaterColor)
	ON_NOTIFY(UDN_DELTAPOS, IDC_VERTICAL_OPTIONS_ALTITUDE_SPINNER, OnDeltaposVerticalOptionsAltitudeSpinner)
	ON_NOTIFY(UDN_DELTAPOS, IDC_VERTICAL_OPTIONS_AZIMUTH_SPINNER, OnDeltaposVerticalOptionsAzimuthSpinner)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_VERTICAL_OPTIONS_WATER_ON, OnVerticalOptionsWaterOn)
	ON_BN_CLICKED(IDC_VERTICAL_OPTIONS_ENABLE_LIGHTING, OnVerticalOptionsEnableLighting)
	ON_CBN_SELCHANGE(IDC_VERTICAL_OPTIONS_SHADER, OnSelchangeVerticalOptionsShader)
	ON_EN_CHANGE(IDC_VERTICAL_OPTIONS_AZIMUTH, OnChangeVerticalOptionsAzimuth)
	ON_EN_CHANGE(IDC_VERTICAL_OPTIONS_ALTITUDE, OnChangeVerticalOptionsAltitude)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// VerticalOptionsPage message handlers

BOOL VerticalOptionsPage::OnApply() 
{
    if ( !d_bIsModified )
    {
        return CPropertyPage::OnApply();
    }

    // Set the current shader
    CString strText;
    d_shadersComboBox.GetLBText( d_shadersComboBox.GetCurSel(), strText );
    if ( strText == "Daylight Shader" )
    {
        *d_ppCurrentShader = d_pDaylightShader;
    }
    else if ( strText == "Gradient Shader" )
    {
        *d_ppCurrentShader = d_pGradientShader;
    }
    else if ( strText == "HSV Shader" )
    {
        *d_ppCurrentShader = d_pHSVShader;
    }
    else if ( strText == "Color Ramp Shader" )
    {
        *d_ppCurrentShader = d_pColorRampShader;
    }

    // If the light direction has changed, invalidate all the intensity caches
    float altitude, azimuth;
    (*d_ppCurrentShader)->getLightDirection( altitude, azimuth );
    if ( altitude != d_altitudeSpinner.GetPos() || azimuth != d_azimuthSpinner.GetPos() )
    {
        RasterOverlay::invalidateAllIntensityCaches();
    }

    // Set the water and light direction values for each shader
    if ( NULL != d_pDaylightShader )
    {
        d_pDaylightShader->setAmbientLightLevel( static_cast<float>( d_ambientLightingSlider.GetPos() ) / 100.0 );
        d_pDaylightShader->setWaterAlpha( d_waterAlphaSlider.GetPos() );
        d_pDaylightShader->setWaterLevel( d_waterLevelSlider.GetPos() );
        d_pDaylightShader->enableWater( static_cast<bool>(d_bWaterOn) );
        d_pDaylightShader->enableLighting( static_cast<bool>(d_bLightingEnabled) );
        d_pDaylightShader->setWaterColor( ps_Pixel( GetRValue( d_waterColor ),
                                                    GetGValue( d_waterColor ),
                                                    GetBValue( d_waterColor ) ) );
        d_pDaylightShader->setLightDirection( d_altitudeSpinner.GetPos(),
                                              d_azimuthSpinner.GetPos()  );
    }

    if ( NULL != d_pGradientShader )
    {
        d_pGradientShader->setAmbientLightLevel( static_cast<float>( d_ambientLightingSlider.GetPos() ) / 100.0 );
        d_pGradientShader->setWaterAlpha( d_waterAlphaSlider.GetPos() );
        d_pGradientShader->setWaterLevel( d_waterLevelSlider.GetPos() );
        d_pGradientShader->enableWater( static_cast<bool>(d_bWaterOn) );
        d_pGradientShader->enableLighting( static_cast<bool>(d_bLightingEnabled) );
        d_pGradientShader->setWaterColor( ps_Pixel( GetRValue( d_waterColor ),
                                                    GetGValue( d_waterColor ),
                                                    GetBValue( d_waterColor ) ) );
        d_pGradientShader->setLightDirection( d_altitudeSpinner.GetPos(),
                                              d_azimuthSpinner.GetPos()  );
    }

    if ( NULL != d_pHSVShader )
    {
        d_pHSVShader->setAmbientLightLevel( static_cast<float>( d_ambientLightingSlider.GetPos() ) / 100.0 );
        d_pHSVShader->setWaterAlpha( d_waterAlphaSlider.GetPos() );
        d_pHSVShader->setWaterLevel( d_waterLevelSlider.GetPos() );
        d_pHSVShader->enableWater( static_cast<bool>(d_bWaterOn) );
        d_pHSVShader->enableLighting( static_cast<bool>(d_bLightingEnabled) );
        d_pHSVShader->setWaterColor( ps_Pixel( GetRValue( d_waterColor ),
                                               GetGValue( d_waterColor ),
                                               GetBValue( d_waterColor ) ) );
        d_pHSVShader->setLightDirection( d_altitudeSpinner.GetPos(),
                                         d_azimuthSpinner.GetPos()  );
    }

    if ( NULL != d_pColorRampShader )
    {
        d_pColorRampShader->setAmbientLightLevel( static_cast<float>( d_ambientLightingSlider.GetPos() ) / 100.0 );
        d_pColorRampShader->setWaterAlpha( d_waterAlphaSlider.GetPos() );
        d_pColorRampShader->setWaterLevel( d_waterLevelSlider.GetPos() );
        d_pColorRampShader->enableWater( static_cast<bool>(d_bWaterOn) );
        d_pColorRampShader->enableLighting( static_cast<bool>(d_bLightingEnabled) );
        d_pColorRampShader->setWaterColor( ps_Pixel( GetRValue( d_waterColor ),
                                                     GetGValue( d_waterColor ),
                                                     GetBValue( d_waterColor ) ) );
        d_pColorRampShader->setLightDirection( d_altitudeSpinner.GetPos(),
                                               d_azimuthSpinner.GetPos()  );
    }
    
    // Set the vertical exaggeration of the overlay
    RasterOverlay::setVerticalExaggeration( d_vertExagControl.GetPos() / 10.0 );

    // Reset the modified flag
    SetModified( FALSE );
    d_bIsModified = false;

    // Clear all the raster stored area buffers
    RasterOverlay::invalidateAllCaches();

    // Call the parent apply handler
    d_pApplyHandler->handleApply();
	
	return CPropertyPage::OnApply();
}

BOOL VerticalOptionsPage::OnSetActive() 
{
    if ( d_bSetup )
    {
        d_bSetup = false;

        // Clear the combo box
        d_shadersComboBox.ResetContent();

        // Add strings to the combo box for each shader        
        if ( NULL != d_pColorRampShader )
        {
            int pos = d_shadersComboBox.AddString( "Color Ramp Shader" );
            if ( d_pColorRampShader == *d_ppCurrentShader )
            {
                d_shadersComboBox.SetCurSel( pos );
            }
        }

        if ( NULL != d_pDaylightShader )
        {
            int pos = d_shadersComboBox.AddString( "Daylight Shader" );
            if ( d_pDaylightShader == *d_ppCurrentShader )
            {
                d_shadersComboBox.SetCurSel( pos );
            }
        }

        if ( NULL != d_pGradientShader )
        {
            int pos = d_shadersComboBox.AddString( "Gradient Shader" );
            if ( d_pGradientShader == *d_ppCurrentShader )
            {
                d_shadersComboBox.SetCurSel( pos );
            }
        }

        if ( NULL != d_pHSVShader )
        {
            int pos = d_shadersComboBox.AddString( "HSV Shader" );
            if ( d_pHSVShader == *d_ppCurrentShader )
            {
                d_shadersComboBox.SetCurSel( pos );
            }
        }

        // Setup the water alpha control
        d_waterAlphaSlider.SetRange( 0, 255, TRUE );
        d_waterAlphaSlider.SetPos( (*d_ppCurrentShader)->getWaterAlpha() );

        // Setup the water level control
        d_waterLevelSlider.SetRange( d_minElevation, d_maxElevation, TRUE );
        d_waterLevelSlider.SetPos( static_cast<int>((*d_ppCurrentShader)->getWaterLevel()) );

        // Setup the ambient lighting control
        d_ambientLightingSlider.SetRange( 0, 100, TRUE );
        d_ambientLightingSlider.SetPos( static_cast<int>((*d_ppCurrentShader)->getAmbientLightLevel() * 100.0 ) );

        // Setup the vertical exaggeration control
        d_vertExagControl.SetRange( 1, 100, TRUE );
        d_vertExagControl.SetPos( static_cast<int>( RasterOverlay::getVerticalExaggeration() * 10.0 ) );
	    
        // Get the values for the altitude and azimuth
        float altitude, azimuth;
        (*d_ppCurrentShader)->getLightDirection( altitude, azimuth );

        // Setup the spinner controls
        d_altitudeSpinner.SetRange( 0, 90 );
        d_altitudeSpinner.SetPos( static_cast<int>(altitude) );
        d_azimuthSpinner.SetRange( 0, 360 );
        d_azimuthSpinner.SetPos( static_cast<int>(azimuth) );
    }
	
	return CPropertyPage::OnSetActive();
}

void VerticalOptionsPage::OnVerticalOptionsWaterColor() 
{
    CColorDialog dlg( d_waterColor );
    
    if ( IDOK == dlg.DoModal() )
    {
        // Get the color and set the modified flag
        if ( d_waterColor != dlg.GetColor() )
        {
            d_waterColor = dlg.GetColor();
            SetModified( TRUE );
            d_bIsModified = true;
        }
    }	
}

void VerticalOptionsPage::OnDeltaposVerticalOptionsAltitudeSpinner(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
    SetModified(TRUE);	
    d_bIsModified = true;
	*pResult = 0;
}

void VerticalOptionsPage::OnDeltaposVerticalOptionsAzimuthSpinner(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
    SetModified(TRUE);	
    d_bIsModified = true;
	*pResult = 0;
}

void VerticalOptionsPage::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
    // Cast the supposed scrollbar object to a Slider control since that's what it really
    // is
    CSliderCtrl* pSlider = dynamic_cast<CSliderCtrl*>(pScrollBar);
    if ( NULL != pSlider )
    {
        // Check to see if the slider changed was the water level
        if ( pSlider == &d_waterLevelSlider )
        {
            d_strWaterLevel.Format( "%d ", pSlider->GetPos() );
            d_strWaterLevel += d_strVerticalUnits;
        }

        // Update the data
        UpdateData( FALSE );

        // Set the modified flag
        SetModified( TRUE );
        d_bIsModified = true;
    }
	
	CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}

void VerticalOptionsPage::OnVerticalOptionsWaterOn() 
{
    // Set the modified flag
    SetModified( TRUE );
    d_bIsModified = true;
    d_bWaterOn = !d_bWaterOn;
}

void VerticalOptionsPage::OnVerticalOptionsEnableLighting() 
{
    // Set the modified flag
    SetModified( TRUE );
    d_bIsModified = true;
    d_bLightingEnabled = !d_bLightingEnabled;
}

void VerticalOptionsPage::OnSelchangeVerticalOptionsShader() 
{
    // Set the modified flag
    SetModified( TRUE );
    d_bIsModified = true;
}

void VerticalOptionsPage::OnChangeVerticalOptionsAzimuth() 
{
    // Set the modified flag
    SetModified( TRUE );
    d_bIsModified = true;
}

void VerticalOptionsPage::OnChangeVerticalOptionsAltitude() 
{
    // Set the modified flag
    SetModified( TRUE );
    d_bIsModified = true;
}
