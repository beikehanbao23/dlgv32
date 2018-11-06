#if !defined(AFX_SDTSDLG_STATPAGE_H__7632A791_2A1D_11D1_BDF0_006097096D7B__INCLUDED_)
#define AFX_SDTSDLG_STATPAGE_H__7632A791_2A1D_11D1_BDF0_006097096D7B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SDTSDLG_StatPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SDTSDLG_StatPage dialog

class SDTSDLG_StatPage : public CPropertyPage
{
	DECLARE_DYNCREATE(SDTSDLG_StatPage)

// Construction
public:
	void SetValues( long numAreas, long numNodes, long numDegLines, long numLines,
                    long numPolygons );
	SDTSDLG_StatPage();
	~SDTSDLG_StatPage();

// Dialog Data
	//{{AFX_DATA(SDTSDLG_StatPage)
	enum { IDD = IDD_SDTSDLG_STAT };
	CString	m_strNumDegLines;
	CString	m_strNumLines;
	CString	m_strNumAreas;
	CString	m_strNumNodes;
	//}}AFX_DATA
    CString m_strNumPolygons;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(SDTSDLG_StatPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(SDTSDLG_StatPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDTSDLG_STATPAGE_H__7632A791_2A1D_11D1_BDF0_006097096D7B__INCLUDED_)
