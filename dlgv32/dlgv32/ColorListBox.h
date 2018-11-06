// ColorListBox.h : header file
//
// Developed by: Mike Childs
//      Started: 4/22/97
//

/////////////////////////////////////////////////////////////////////////////
// ColorListBox window

#ifndef _COLORLISTBOX_H_
#define _COLORLISTBOX_H_

#include "StdAfx.h"

class ColorListBox : public CListBox
{
// Construction
public:
	UINT getNumColors();
	COLORREF getColor( UINT numColor );
	void setColors( RGBQUAD colors[], UINT numColors );
	ColorListBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ColorListBox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ColorListBox();

	// Generated message map functions
protected:
	CString getColorString( UINT numColor );
	UINT d_numColors;
	RGBQUAD* d_pColors;
	//{{AFX_MSG(ColorListBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif