#if !defined(AFX_RASTEROPTIONSPAGE_H__166EA743_9E96_11D1_BE39_006097096D7B__INCLUDED_)
#define AFX_RASTEROPTIONSPAGE_H__166EA743_9E96_11D1_BE39_006097096D7B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RasterOptionsPage.h : header file
//

#include "resource.h"
#include "RasterOverlay.h"

// Forward declarations
class PropertySheetApplyHandler;

/////////////////////////////////////////////////////////////////////////////
// RasterOptionsPage dialog

class RasterOptionsPage : public CPropertyPage
{
	DECLARE_DYNCREATE(RasterOptionsPage)

// Construction
public:
	RasterOptionsPage();
	~RasterOptionsPage();

    bool isModified() const;
    void setApplyHandler( PropertySheetApplyHandler* pApplyHandler );
    void setOverlay( RasterOverlay* pOverlay );
    void setColors( RGBQUAD* pColors, UINT numColors );
    void setSlider( int min, int max, int initPos );

// Dialog Data
	//{{AFX_DATA(RasterOptionsPage)
	enum { IDD = IDD_RASTER_OPTIONS };
	CButton	d_textureMappedCheckbox;
	CButton	d_setTransparentColorButton;
	CButton	d_setTransparentButton;
	CSliderCtrl	d_intensitySlider;
	BOOL	d_bInterpolated;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(RasterOptionsPage)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(RasterOptionsPage)
	afx_msg void OnRasterOptionsTransparent();
	afx_msg void OnRasterOptionsTransColor();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnRasterOptionsDefaultIntensity();
	afx_msg void OnRasterInterpolate();
	afx_msg void OnRasterTextureMap();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    // Data members
    bool     d_bIsModified;
    bool     d_bSetup;
    COLORREF d_transparentColor;
    UINT     d_numColors;
    RGBQUAD* d_pColors;
    int      d_sliderInitPos;
    int      d_sliderMax;
    int      d_sliderMin;
    RasterOverlay* d_pOverlay;
    PropertySheetApplyHandler* d_pApplyHandler;
};

inline bool
RasterOptionsPage::isModified() const
{
    return d_bIsModified;
}

inline void
RasterOptionsPage::setApplyHandler( PropertySheetApplyHandler* pApplyHandler )
{
    ASSERT( NULL != pApplyHandler );
    d_pApplyHandler = pApplyHandler;
}

inline void
RasterOptionsPage::setOverlay( RasterOverlay* pOverlay )
{
    d_pOverlay = pOverlay;
    d_transparentColor = pOverlay->getTransparentColor();
    d_bInterpolated = pOverlay->isInterpolated();
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RASTEROPTIONSPAGE_H__166EA743_9E96_11D1_BE39_006097096D7B__INCLUDED_)
