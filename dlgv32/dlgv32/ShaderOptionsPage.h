#if !defined(AFX_SHADEROPTIONSPAGE_H__78CCD9D3_9F2A_11D1_BE39_006097096D7B__INCLUDED_)
#define AFX_SHADEROPTIONSPAGE_H__78CCD9D3_9F2A_11D1_BE39_006097096D7B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ShaderOptionsPage.h : header file
//

// Forward declarations
class ps_DaylightShader;
class ps_GradientShader;
class ps_HSVShader;
class PropertySheetApplyHandler;

/////////////////////////////////////////////////////////////////////////////
// ShaderOptionsPage dialog

class ShaderOptionsPage : public CPropertyPage
{
	DECLARE_DYNCREATE(ShaderOptionsPage)

// Construction
public:
	ShaderOptionsPage();
	~ShaderOptionsPage();
    bool isModified() const;
    void setApplyHandler( PropertySheetApplyHandler* pApplyHandler );
    void setShaders( ps_DaylightShader* pDaylightShader,
                     ps_GradientShader* pGradientShader,
                     ps_HSVShader*      pHSVShader );

// Dialog Data
	//{{AFX_DATA(ShaderOptionsPage)
	enum { IDD = IDD_SHADER_OPTIONS };
	CSliderCtrl	d_hsvRangeControl;
	CSliderCtrl	d_hsvValueControl;
	CSliderCtrl	d_hsvSaturationControl;
	CSliderCtrl	d_hsvLowColorStartControl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(ShaderOptionsPage)
	public:
	virtual BOOL OnApply();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(ShaderOptionsPage)
	afx_msg void OnShaderOptionsDaylightSurfaceColor();
	afx_msg void OnShaderOptionsGradientSetHiColor();
	afx_msg void OnShaderOptionsGradientSetLoColor();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    // Data members
    bool               d_bIsModified;
    bool               d_bSetup;
    COLORREF           d_daylightSurfaceColor;
    COLORREF           d_gradientLowColor;
    COLORREF           d_gradientHighColor;
    ps_DaylightShader* d_pDaylightShader;
    ps_GradientShader* d_pGradientShader;
    ps_HSVShader*      d_pHSVShader;
    PropertySheetApplyHandler* d_pApplyHandler;
};

inline bool
ShaderOptionsPage::isModified() const
{
    return d_bIsModified;
}

inline void
ShaderOptionsPage::setApplyHandler( PropertySheetApplyHandler* pApplyHandler )
{
    ASSERT( NULL != pApplyHandler );
    d_pApplyHandler = pApplyHandler;
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHADEROPTIONSPAGE_H__78CCD9D3_9F2A_11D1_BE39_006097096D7B__INCLUDED_)
