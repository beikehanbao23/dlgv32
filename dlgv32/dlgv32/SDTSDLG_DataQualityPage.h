#if !defined(AFX_SDTSDLG_DATAQUALITYPAGE_H__9459C491_2D42_11D1_BDF1_006097096D7B__INCLUDED_)
#define AFX_SDTSDLG_DATAQUALITYPAGE_H__9459C491_2D42_11D1_BDF1_006097096D7B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SDTSDLG_DataQualityPage.h : header file
//

// Forward declarations
class sb_AttAccuracy;
class sb_Completeness;
class sb_Lineage;
class sb_LogicalConsis;
class sb_PosAccuracy;

/////////////////////////////////////////////////////////////////////////////
// SDTSDLG_DataQualityPage dialog

class SDTSDLG_DataQualityPage : public CPropertyPage
{
	DECLARE_DYNCREATE(SDTSDLG_DataQualityPage)

// Construction
public:
	SDTSDLG_DataQualityPage();
	~SDTSDLG_DataQualityPage();
    void SetValues( sb_AttAccuracy** ppDQAA, sb_Completeness** ppDQCG,
                    sb_Lineage** ppDQHL, sb_LogicalConsis** ppDQLC,
                    sb_PosAccuracy** ppDQPA );

// Dialog Data
	//{{AFX_DATA(SDTSDLG_DataQualityPage)
	enum { IDD = IDD_SDTSDLG_DATAQUALITY };
	CString	m_strDQAA;
	CString	m_strDQCG;
	CString	m_strDQHL;
	CString	m_strDQLC;
	CString	m_strDQPA;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(SDTSDLG_DataQualityPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(SDTSDLG_DataQualityPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    // Data members
    sb_AttAccuracy**   m_ppDQAA;
    sb_Completeness**  m_ppDQCG;
    sb_Lineage**       m_ppDQHL;
    sb_LogicalConsis** m_ppDQLC;
    sb_PosAccuracy**   m_ppDQPA;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDTSDLG_DATAQUALITYPAGE_H__9459C491_2D42_11D1_BDF1_006097096D7B__INCLUDED_)
