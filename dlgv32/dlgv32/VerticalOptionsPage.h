#if !defined(AFX_VERTICALOPTIONSPAGE_H__78CCD9D2_9F2A_11D1_BE39_006097096D7B__INCLUDED_)
#define AFX_VERTICALOPTIONSPAGE_H__78CCD9D2_9F2A_11D1_BE39_006097096D7B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// VerticalOptionsPage.h : header file
//

#include "ps_PixelShader.h"

// Forward declaration
class PropertySheetApplyHandler;
class RasterOverlay;

/////////////////////////////////////////////////////////////////////////////
// VerticalOptionsPage dialog

class VerticalOptionsPage : public CPropertyPage
{
	DECLARE_DYNCREATE(VerticalOptionsPage)

// Construction
public:
	VerticalOptionsPage();
	~VerticalOptionsPage();

    bool isModified() const;
    void setApplyHandler( PropertySheetApplyHandler* pApplyHandler );
    void setElevationRange( int minElevation, int maxElevation );
    void setOverlay( RasterOverlay* pOverlay );
    void setShaders( ps_PixelShader**   ppCurrentShader,
                     ps_DaylightShader* pDaylightShader,
                     ps_GradientShader* pGradientShader,
                     ps_HSVShader*      pHSVShader,
                     ps_ColorRampShader* pColorRampShader );
    void setVerticalUnitString( const CString& strVerticalUnits );

// Dialog Data
	//{{AFX_DATA(VerticalOptionsPage)
	enum { IDD = IDD_VERTICAL_OPTIONS };
	CSliderCtrl	d_vertExagControl;
	CSliderCtrl	d_ambientLightingSlider;
	CSliderCtrl	d_waterLevelSlider;
	CSliderCtrl	d_waterAlphaSlider;
	CComboBox	d_shadersComboBox;
	CSpinButtonCtrl	d_azimuthSpinner;
	CSpinButtonCtrl	d_altitudeSpinner;
	CString	d_strWaterLevel;
	BOOL	d_bWaterOn;
	BOOL	d_bLightingEnabled;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(VerticalOptionsPage)
	public:
	virtual BOOL OnApply();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(VerticalOptionsPage)
	afx_msg void OnVerticalOptionsWaterColor();
	afx_msg void OnDeltaposVerticalOptionsAltitudeSpinner(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposVerticalOptionsAzimuthSpinner(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVerticalOptionsWaterOn();
	afx_msg void OnVerticalOptionsEnableLighting();
	afx_msg void OnSelchangeVerticalOptionsShader();
	afx_msg void OnChangeVerticalOptionsAzimuth();
	afx_msg void OnChangeVerticalOptionsAltitude();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    // Member data
    bool               d_bIsModified;
    bool               d_bSetup;
    COLORREF           d_waterColor;
    CString            d_strVerticalUnits;
    int                d_minElevation;
    int                d_maxElevation;
    ps_ColorRampShader* d_pColorRampShader;
    ps_DaylightShader* d_pDaylightShader;
    ps_GradientShader* d_pGradientShader;
    ps_HSVShader*      d_pHSVShader;
    ps_PixelShader**   d_ppCurrentShader;
    PropertySheetApplyHandler* d_pApplyHandler;
    RasterOverlay*     d_pOverlay;
};

inline bool
VerticalOptionsPage::isModified() const
{
    return d_bIsModified;
}

inline void
VerticalOptionsPage::setApplyHandler( PropertySheetApplyHandler* pApplyHandler )
{
    ASSERT( NULL != pApplyHandler );
    d_pApplyHandler = pApplyHandler;
}

inline void
VerticalOptionsPage::setElevationRange( int minElevation, int maxElevation )
{
    ASSERT( minElevation < maxElevation );
    d_minElevation = minElevation;
    d_maxElevation = maxElevation;
}

inline void
VerticalOptionsPage::setOverlay( RasterOverlay* pOverlay )
{
    d_pOverlay = pOverlay;
}

inline void
VerticalOptionsPage::setShaders( ps_PixelShader**   ppCurrentShader, 
                                 ps_DaylightShader* pDaylightShader,
                                 ps_GradientShader* pGradientShader,
                                 ps_HSVShader*      pHSVShader,
                                 ps_ColorRampShader* pColorRampShader )
{
    ASSERT( NULL != ppCurrentShader );
    ASSERT( NULL != *ppCurrentShader );

    d_ppCurrentShader = ppCurrentShader;
    d_pDaylightShader = pDaylightShader;
    d_pGradientShader = pGradientShader;
    d_pHSVShader = pHSVShader;
    d_pColorRampShader = pColorRampShader;

    // Get the water and surface colors
    const ps_Pixel& waterCol = (*ppCurrentShader)->getWaterColor();
    d_waterColor = RGB( waterCol.red, waterCol.green, waterCol.blue );
    d_strWaterLevel.Format( "%d ", static_cast<int>( (*ppCurrentShader)->getWaterLevel() ) );
    d_strWaterLevel += d_strVerticalUnits;
    d_bWaterOn = (*d_ppCurrentShader)->isWaterEnabled();
    d_bLightingEnabled = (*d_ppCurrentShader)->isLightingEnabled();

}


inline void
VerticalOptionsPage::setVerticalUnitString( const CString& strVerticalUnits )
{
    d_strVerticalUnits = strVerticalUnits;
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VERTICALOPTIONSPAGE_H__78CCD9D2_9F2A_11D1_BE39_006097096D7B__INCLUDED_)
