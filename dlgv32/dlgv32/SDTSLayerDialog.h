#if !defined(AFX_SDTSLAYERDIALOG_H__B1278F51_0383_11D1_87F9_006097096B03__INCLUDED_)
#define AFX_SDTSLAYERDIALOG_H__B1278F51_0383_11D1_87F9_006097096B03__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
using namespace std;
#include <vector>
// SDTSLayerDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SDTSLayerDialog dialog

// Forward declarations
class sb_CatalogSpatialDom;

// Utility class declaration
class SDTSModuleInfo
{
public:
    SDTSModuleInfo( sb_CatalogSpatialDom* pCatSEntry );

    CString getAGOB()  { return d_strAGOB; };
    CString getMap()   { return d_strMap;  };
    CString getTheme() { return d_strTheme; };

protected:
    CString d_strAGOB;
    CString d_strMap;
    CString d_strTheme;
};

class SDTSLayerDialog : public CDialog
{
// Construction
public:
	SDTSLayerDialog( CString strCATSFilename, CWnd* pParent = NULL );
    ~SDTSLayerDialog();
	const vector<SDTSModuleInfo*>& GetSelected( void );
    void populateLayers( const CString& strCATSFilename, const CString& strName );
    bool isRasterTransfer() const;

// Dialog Data
	//{{AFX_DATA(SDTSLayerDialog)
	enum { IDD = IDD_SDTS_LAYER_DIALOG };
	CListBox	m_manifoldList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SDTSLayerDialog)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    // Data members
    vector<sb_CatalogSpatialDom*> d_pLineEntries;
    vector<SDTSModuleInfo*>       d_pSelectedModules;
    int*                          d_pSelectedEntries;
    int                           d_numSelected;
    bool                          d_bRasterTransfer;

	// Generated message map functions
	//{{AFX_MSG(SDTSLayerDialog)
	afx_msg void OnSelchangeLayerList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

inline bool
SDTSLayerDialog::isRasterTransfer() const
{
    return d_bRasterTransfer;
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDTSLAYERDIALOG_H__B1278F51_0383_11D1_87F9_006097096B03__INCLUDED_)
