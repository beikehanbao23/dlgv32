// DLGOptionsDialog.h : header file
//

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CDLGOptionsDialog dialog

class CDLGOptionsDialog : public CDialog
{
// Construction
public:
	int getSliderPos();
	void setSlider( int min, int max, int initpos );
	int d_sliderMax;
	COLORREF m_colorLine;
	CDLGOptionsDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDLGOptionsDialog)
	enum { IDD = IDD_DLG_OPTIONS };
	CSliderCtrl	d_lineWidthSlider;
	int		m_nAreaShape;
	int		m_nNodeShape;
	BOOL	d_hideAreas;
	BOOL	d_hideNodes;
	BOOL	d_hideLines;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDLGOptionsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int d_sliderInitPos;
	int d_sliderMin;

	// Generated message map functions
	//{{AFX_MSG(CDLGOptionsDialog)
	afx_msg void OnLineColor();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
