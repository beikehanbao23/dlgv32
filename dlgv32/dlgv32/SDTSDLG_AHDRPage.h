#if !defined(AFX_SDTSDLG_AHDRPAGE_H__59E14481_8D0D_11D1_BE39_006097096D7B__INCLUDED_)
#define AFX_SDTSDLG_AHDRPAGE_H__59E14481_8D0D_11D1_BE39_006097096D7B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SDTSDLG_AHDRPage.h : header file
//

#include <vector>
#include "SDTS_AttRecord.h"

// Forward Declarations
class SDTS_AttModule;

/////////////////////////////////////////////////////////////////////////////
// SDTSDLG_AHDRPage dialog

class SDTSDLG_AHDRPage : public CPropertyPage
{
	DECLARE_DYNCREATE(SDTSDLG_AHDRPage)

// Construction
public:
	SDTSDLG_AHDRPage();
	~SDTSDLG_AHDRPage();
    void setModule( SDTS_AttModule** ppAHDR, int recNum );

// Dialog Data
	//{{AFX_DATA(SDTSDLG_AHDRPage)
	enum { IDD = IDD_SDTSDLG_AHDR };
	CStatic	d_bannerTextControl;
	CListCtrl	d_pairs;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(SDTSDLG_AHDRPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

    void initColumns();
    void resizeColumns();
    void setPairs( const vector<SDTSAtt_LabelValuePair>& pairs );

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(SDTSDLG_AHDRPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    bool d_bInitialized;
    int d_recordNumber;
    SDTS_AttModule** d_ppAHDRModule;
};

inline void
SDTSDLG_AHDRPage::setModule( SDTS_AttModule** ppAHDR, int recNum )
{
    d_ppAHDRModule = ppAHDR;
    d_recordNumber = recNum;
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDTSDLG_AHDRPAGE_H__59E14481_8D0D_11D1_BE39_006097096D7B__INCLUDED_)
