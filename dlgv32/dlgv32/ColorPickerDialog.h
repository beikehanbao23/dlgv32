// ColorPickerDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ColorPickerDialog dialog

#ifndef _COLORPICKERDIALOG_H_
#define _COLORPICKERDIALOG_H_

#include "StdAfx.h"
#include "resource.h"
#include "ColorListBox.h"

class ColorPickerDialog : public CDialog
{
// Construction
public:
	COLORREF d_selColor;
	ColorPickerDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ColorPickerDialog)
	enum { IDD = IDD_COLOR_PICKER };
	ColorListBox	d_colorListBox;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ColorPickerDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(ColorPickerDialog)
	afx_msg void OnSelchangeTransColorList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif