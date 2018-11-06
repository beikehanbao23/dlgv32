#if !defined(AFX_GEOTIFFPROPERTYPAGE_H__D6E289A1_4F0F_11D1_BE18_006097096D7B__INCLUDED_)
#define AFX_GEOTIFFPROPERTYPAGE_H__D6E289A1_4F0F_11D1_BE18_006097096D7B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GeoTIFFPropertyPage.h : header file
//

// Forward declarations
class GeoTIFFOverlay;

/////////////////////////////////////////////////////////////////////////////
// GeoTIFFPropertyPage dialog

class GeoTIFFPropertyPage : public CPropertyPage
{
	DECLARE_DYNCREATE(GeoTIFFPropertyPage)

// Construction
public:
	GeoTIFFPropertyPage();
    GeoTIFFPropertyPage( GeoTIFFOverlay* pGeoTIFF );
	~GeoTIFFPropertyPage();

// Dialog Data
	//{{AFX_DATA(GeoTIFFPropertyPage)
	enum { IDD = IDD_GEOTIFF_METADATA };
	CString	d_strGeoPixelScale;
	CString	d_strGeoTiepoint;
	CString	d_strModelType;
	CString	d_strPCSCitation;
	CString	d_strRasterType;
	CString	d_strProjection;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(GeoTIFFPropertyPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(GeoTIFFPropertyPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GEOTIFFPROPERTYPAGE_H__D6E289A1_4F0F_11D1_BE18_006097096D7B__INCLUDED_)
