#if !defined(AFX_GEOTIFFVERTICALMETADATAPAGE_H__BEFABE71_B865_11D1_BE3F_006097096D7B__INCLUDED_)
#define AFX_GEOTIFFVERTICALMETADATAPAGE_H__BEFABE71_B865_11D1_BE3F_006097096D7B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GeoTIFFVerticalMetadataPage.h : header file
//

class GeoTIFFOverlay; // Forward declaration

/////////////////////////////////////////////////////////////////////////////
// GeoTIFFVerticalMetadataPage dialog

class GeoTIFFVerticalMetadataPage : public CPropertyPage
{
	DECLARE_DYNCREATE(GeoTIFFVerticalMetadataPage)

// Construction
public:
	GeoTIFFVerticalMetadataPage();
	~GeoTIFFVerticalMetadataPage();

    void setOverlay( GeoTIFFOverlay* pOverlay );

// Dialog Data
	//{{AFX_DATA(GeoTIFFVerticalMetadataPage)
	enum { IDD = IDD_GEOTIFF_VERTICAL_METADATA };
	CString	d_strMaxElevation;
	CString	d_strMinElevation;
	CString	d_strVerticalCitation;
	CString	d_strVerticalDatum;
	CString	d_strVerticalUnits;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(GeoTIFFVerticalMetadataPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(GeoTIFFVerticalMetadataPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GEOTIFFVERTICALMETADATAPAGE_H__BEFABE71_B865_11D1_BE3F_006097096D7B__INCLUDED_)
