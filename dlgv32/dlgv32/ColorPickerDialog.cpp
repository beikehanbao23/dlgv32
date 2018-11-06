// ColorPickerDialog.cpp : implementation file
//

#include "stdafx.h"
#include "dlgv32.h"
#include "ColorPickerDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ColorPickerDialog dialog


ColorPickerDialog::ColorPickerDialog(CWnd* pParent /*=NULL*/)
	: CDialog(ColorPickerDialog::IDD, pParent), d_selColor(0)
{
	//{{AFX_DATA_INIT(ColorPickerDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ColorPickerDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ColorPickerDialog)
	DDX_Control(pDX, IDC_TRANS_COLOR_LIST, d_colorListBox);
	//}}AFX_DATA_MAP

	for ( int i = 0; i < d_colorListBox.getNumColors(); i++ )
	{
		// Add an empty string to the list box
		d_colorListBox.AddString( "" );
	}

}


BEGIN_MESSAGE_MAP(ColorPickerDialog, CDialog)
	//{{AFX_MSG_MAP(ColorPickerDialog)
	ON_LBN_SELCHANGE(IDC_TRANS_COLOR_LIST, OnSelchangeTransColorList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void ColorPickerDialog::OnSelchangeTransColorList() 
{
	// Set selected color to color of currently selected item, 
	// or white if nothing is selected
	int sel = d_colorListBox.GetCurSel();
	if ( sel != LB_ERR )
	{
		d_selColor = d_colorListBox.getColor( sel );
	}
	else
	{
		d_selColor = RGB(255,255,255);
	}	
}
