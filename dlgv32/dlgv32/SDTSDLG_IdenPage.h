#if !defined(AFX_SDTSDLG_IDENPAGE_H__9C695111_27B8_11D1_BDEE_006097096D7B__INCLUDED_)
#define AFX_SDTSDLG_IDENPAGE_H__9C695111_27B8_11D1_BDEE_006097096D7B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SDTSDLG_IdenPage.h : header file
//

// Forward declarations
class sb_Ident;

/////////////////////////////////////////////////////////////////////////////
// SDTSDLG_IdenPage dialog

class SDTSDLG_IdenPage : public CPropertyPage
{
	DECLARE_DYNCREATE(SDTSDLG_IdenPage)

// Construction
public:
	SDTSDLG_IdenPage();
	~SDTSDLG_IdenPage();
	void SetIden( sb_Ident* pIdent );
    void SetProjection( const CString& strProjection );

// Dialog Data
	//{{AFX_DATA(SDTSDLG_IdenPage)
	enum { IDD = IDD_SDTSDLG_IDEN };
	CString	m_strStandardID;
	CString	m_strCreationDate;
	CString	m_strDataID;
	CString	m_strDataStructure;
	CString	m_strMapDate;
	CString	m_strProfileID;
	CString	m_strProfileDocRef;
	CString	m_strProfileVer;
	CString	m_strStandardDocRef;
	CString	m_strStandardVer;
	CString	m_strTitle;
	CString	m_strComposites;
	CString	m_strExtSpatialRef;
	CString	m_strFeaturesLevel;
	CString	m_strRaster;
	CString	m_strScale;
	CString	m_strVectorGeometry;
	CString	m_strVectorTopology;
	CString	m_strProjection;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(SDTSDLG_IdenPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(SDTSDLG_IdenPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDTSDLG_IDENPAGE_H__9C695111_27B8_11D1_BDEE_006097096D7B__INCLUDED_)
