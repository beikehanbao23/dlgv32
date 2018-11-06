// DLGOptionsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DLGOptionsDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CDLGOptionsDialog dialog

CDLGOptionsDialog::CDLGOptionsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDLGOptionsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLGOptionsDialog)
	m_nAreaShape = -1;
	m_nNodeShape = -1;
	d_hideAreas = FALSE;
	d_hideNodes = FALSE;
	d_hideLines = FALSE;
	//}}AFX_DATA_INIT
}


void CDLGOptionsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLGOptionsDialog)
	DDX_Control(pDX, IDC_DLG_LINE_WIDTH, d_lineWidthSlider);
	DDX_Radio(pDX, IDC_AREA_SHAPE_CIRCLE, m_nAreaShape);
	DDX_Radio(pDX, IDC_NODE_SHAPE_CIRCLE, m_nNodeShape);
	DDX_Check(pDX, IDC_HIDE_AREAS_OVERLAY, d_hideAreas);
	DDX_Check(pDX, IDC_HIDE_NODES_OVERLAY, d_hideNodes);
	DDX_Check(pDX, IDC_HIDE_LINES_OVERLAY, d_hideLines);
	//}}AFX_DATA_MAP

	d_lineWidthSlider.SetRange( d_sliderMin, d_sliderMax );
	d_lineWidthSlider.SetPos( d_sliderInitPos );
	d_lineWidthSlider.SetTicFreq( 1 );
}


BEGIN_MESSAGE_MAP(CDLGOptionsDialog, CDialog)
	//{{AFX_MSG_MAP(CDLGOptionsDialog)
	ON_BN_CLICKED(IDC_LINE_COLOR, OnLineColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLGOptionsDialog message handlers

void CDLGOptionsDialog::OnLineColor() 
{
	CColorDialog colorDlg( m_colorLine );

	// invoke the dialog box
	if ( colorDlg.DoModal() == IDOK )
	{
		// retreive the user selected color
		m_colorLine = colorDlg.GetColor();
	}
	
}

void CDLGOptionsDialog::setSlider( int min, int max, int initpos )
{
	d_sliderMin = min;
	d_sliderMax = max;

	if ( initpos < min || initpos > max )
	{
		initpos = ( min + max ) / 2;
	}

	d_sliderInitPos = initpos;
}

void CDLGOptionsDialog::OnOK() 
{
	// Update the slider position
	d_sliderInitPos = d_lineWidthSlider.GetPos();
	
	CDialog::OnOK();
}

int CDLGOptionsDialog::getSliderPos()
{
	return d_sliderInitPos;
}
