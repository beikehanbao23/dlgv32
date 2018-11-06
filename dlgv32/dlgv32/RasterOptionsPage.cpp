// RasterOptionsPage.cpp : implementation file
//

#include "stdafx.h"
#include "dlgv32.h"
#include "RasterOptionsPage.h"
#include "ColorPickerDialog.h"
#include "TIFFOverlay.h"
#include "PropertySheetApplyHandler.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RasterOptionsPage property page

IMPLEMENT_DYNCREATE(RasterOptionsPage, CPropertyPage)

RasterOptionsPage::RasterOptionsPage() 
: CPropertyPage(RasterOptionsPage::IDD), d_pColors(NULL), d_pOverlay(NULL),
  d_sliderMin(0), d_sliderMax(20), d_bIsModified(false), d_bSetup(true)
{
	//{{AFX_DATA_INIT(RasterOptionsPage)
	d_bInterpolated = FALSE;
	//}}AFX_DATA_INIT
}

RasterOptionsPage::~RasterOptionsPage()
{
}

void RasterOptionsPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RasterOptionsPage)
	DDX_Control(pDX, IDC_RASTER_TEXTURE_MAP, d_textureMappedCheckbox);
	DDX_Control(pDX, IDC_RASTER_OPTIONS_TRANS_COLOR, d_setTransparentColorButton);
	DDX_Control(pDX, IDC_RASTER_OPTIONS_TRANSPARENT, d_setTransparentButton);
	DDX_Control(pDX, IDC_RASTER_OPTIONS_INTENSITY, d_intensitySlider);
	DDX_Check(pDX, IDC_RASTER_INTERPOLATE, d_bInterpolated);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RasterOptionsPage, CPropertyPage)
	//{{AFX_MSG_MAP(RasterOptionsPage)
	ON_BN_CLICKED(IDC_RASTER_OPTIONS_TRANSPARENT, OnRasterOptionsTransparent)
	ON_BN_CLICKED(IDC_RASTER_OPTIONS_TRANS_COLOR, OnRasterOptionsTransColor)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_RASTER_OPTIONS_DEFAULT_INTENSITY, OnRasterOptionsDefaultIntensity)
	ON_BN_CLICKED(IDC_RASTER_INTERPOLATE, OnRasterInterpolate)
	ON_BN_CLICKED(IDC_RASTER_TEXTURE_MAP, OnRasterTextureMap)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RasterOptionsPage message handlers

void RasterOptionsPage::OnRasterOptionsTransparent() 
{
    // Set the modified flag
    SetModified( TRUE );
    d_bIsModified = true;
}

void RasterOptionsPage::OnRasterOptionsTransColor() 
{
    // Show color picker dialog if colors are set
    if ( NULL != d_pColors )
    {
        ColorPickerDialog dlg;
        dlg.d_colorListBox.setColors( d_pColors, d_numColors );
        if ( IDOK == dlg.DoModal() )
        {
            if ( d_transparentColor != dlg.d_selColor )
            {
                d_transparentColor = dlg.d_selColor;
                SetModified( TRUE );
                d_bIsModified = true;
            }
        }
    }
    // Show windows color dialog for non-palette images
    else
    {
        CColorDialog dlg( d_transparentColor );
        if ( IDOK == dlg.DoModal() )
        {
            if ( d_transparentColor != dlg.GetColor() )
            {
                d_transparentColor = dlg.GetColor();
                SetModified( TRUE );
                d_bIsModified = true;
            }
        }
    }
}

void 
RasterOptionsPage::setColors( RGBQUAD* pColors, UINT numColors )
{
    d_pColors = pColors;
    d_numColors = numColors;
}

void 
RasterOptionsPage::setSlider( int min, int max, int initPos )
{
    d_sliderMin = min;
    d_sliderMax = max;

    if ( initPos < min || initPos > max )
    {
        initPos = ( min + max ) / 2;
    }

    d_sliderInitPos = initPos;
}

BOOL RasterOptionsPage::OnSetActive() 
{
    if ( d_bSetup )
    {
        d_bSetup = false;

        // Setup the intensity range
        d_intensitySlider.SetRange( d_sliderMin, d_sliderMax );
        d_intensitySlider.SetPos( d_sliderInitPos );

        // Set the transparency checkbox state
        d_setTransparentButton.SetCheck( d_pOverlay->isTransparent() );

        // Disable the texture mapped checkbox if the overlay is vertical
        if ( d_pOverlay->isVertical() )
        {
            d_textureMappedCheckbox.EnableWindow( FALSE );
        }
        else
        {
            d_textureMappedCheckbox.SetCheck( d_pOverlay->isTextureMapped() );
        }
    }

	return CPropertyPage::OnSetActive();
}

void RasterOptionsPage::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
    // Set the modified flag
    SetModified( TRUE );
    d_bIsModified = true;

	CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}

void RasterOptionsPage::OnRasterOptionsDefaultIntensity() 
{
    d_intensitySlider.SetPos( ( d_sliderMin + d_sliderMax ) / 2 );
    SetModified( TRUE );
    d_bIsModified = true;
}

BOOL RasterOptionsPage::OnApply() 
{
    ASSERT( NULL != d_pOverlay );

    if ( !d_bIsModified )
    {
        return CPropertyPage::OnApply();
    }

	bool bRedraw = false;

	UINT newPos = d_intensitySlider.GetPos();

	// Update the image if the slider was moved
	if ( newPos != d_pOverlay->getColorIntensity() )
	{
		// Get the new intensity value
		d_pOverlay->setColorIntensity( newPos );

		// Adjust the overlay's palette
		d_pOverlay->adjustPalette();

		// Reset the overlay's last clip rect
		d_pOverlay->invalidateCache();

        bRedraw = true;
	}

    // Update the image if the interpolation flag was changed
    if ( static_cast<bool>(d_textureMappedCheckbox.GetCheck() ) != 
         d_pOverlay->isTextureMapped() )
    {
        d_pOverlay->enableTextureMapping( d_textureMappedCheckbox.GetCheck() );
        bRedraw = true;
    }

    // Update the image if the texture mapped flag was changed
    if ( static_cast<bool>(d_bInterpolated) != d_pOverlay->isInterpolated() )
    {
        d_pOverlay->enableInterpolation( d_bInterpolated );
        d_pOverlay->invalidateCache();
        RasterOverlay::handleOverlayChanging( d_pOverlay );
        bRedraw = true;
    }

    // Determine the transparency of the image
    bool bChecked = static_cast<bool>( d_setTransparentButton.GetCheck() );
	if ( bChecked != d_pOverlay->isTransparent() ||
		 d_transparentColor != d_pOverlay->getTransparentColor() )
	{
		d_pOverlay->setTransparent( bChecked );
		d_pOverlay->setTransparentColor( d_transparentColor );

        // Invalidate the overlay's cache if it is currently being reprojected
        if ( d_pOverlay->d_bReproject )
        {
            d_pOverlay->invalidateCache();
        }

		bRedraw = true;
	}

    // Reset the modified flag
    SetModified( FALSE );
    d_bIsModified = false;

    if ( bRedraw )
    {
        d_pApplyHandler->handleApply();
    }

	return CPropertyPage::OnApply();
}

void RasterOptionsPage::OnRasterInterpolate() 
{
    // Set the modified flag
    SetModified( TRUE );
    d_bIsModified = true;
}

void RasterOptionsPage::OnRasterTextureMap() 
{
    // Set the modified flag
    SetModified( TRUE );
    d_bIsModified = true;
}
