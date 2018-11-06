#if !defined(AFX_RASTERMETADATADIALOG_H__BEFABE72_B865_11D1_BE3F_006097096D7B__INCLUDED_)
#define AFX_RASTERMETADATADIALOG_H__BEFABE72_B865_11D1_BE3F_006097096D7B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RasterMetadataDialog.h : header file
//

#include "resource.h"

class RasterOverlay; // Forward declaration

/////////////////////////////////////////////////////////////////////////////
// RasterMetadataDialog dialog

class RasterMetadataDialog : public CDialog
{
// Construction
public:
	RasterMetadataDialog(CWnd* pParent = NULL);   // standard constructor

    void setOverlay( RasterOverlay* pOverlay );

// Dialog Data
	//{{AFX_DATA(RasterMetadataDialog)
	enum { IDD = IDD_RASTER_METADATA };
	CString	d_strDescription;
	CString	d_strHeight;
	CString	d_strMaxElevation;
	CString	d_strMaxElevationLabel;
	CString	d_strMinElevation;
	CString	d_strMinElevationLabel;
	CString	d_strVerticalUnits;
	CString	d_strWidth;
	CString	d_strVerticalUnitsLabel;
	CString	d_strProjection;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RasterMetadataDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(RasterMetadataDialog)
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RASTERMETADATADIALOG_H__BEFABE72_B865_11D1_BE3F_006097096D7B__INCLUDED_)
