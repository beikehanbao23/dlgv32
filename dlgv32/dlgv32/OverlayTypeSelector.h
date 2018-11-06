#if !defined(AFX_OVERLAYTYPESELECTOR_H__959914E2_CE85_11D1_BE41_006097096D7B__INCLUDED_)
#define AFX_OVERLAYTYPESELECTOR_H__959914E2_CE85_11D1_BE41_006097096D7B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// OverlayTypeSelector.h : header file
//

#include "resource.h"
#include <vector>
using namespace std;

class OverlayTypeInfo; // Forward declaration

/////////////////////////////////////////////////////////////////////////////
// OverlayTypeSelector dialog

class OverlayTypeSelector : public CDialog
{
// Construction
public:
	OverlayTypeSelector(CWnd* pParent = NULL);   // standard constructor
  void setOverlayTypes( const vector<OverlayTypeInfo*>& typeInfoList );
  OverlayTypeInfo* getSelectedOverlayType() const;

// Dialog Data
	//{{AFX_DATA(OverlayTypeSelector)
	enum { IDD = IDD_OVERLAY_TYPE_SELECTOR };
	CListBox	d_typesListBox;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(OverlayTypeSelector)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(OverlayTypeSelector)
	afx_msg void OnSelchangeOverlayTypeList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

  const vector<OverlayTypeInfo*>* d_pTypeInfoList;
  int                             d_selectedIndex;
};

inline void
OverlayTypeSelector::setOverlayTypes( const vector<OverlayTypeInfo*>& 
                                      typeInfoList )
{
  d_pTypeInfoList = &typeInfoList;
}

inline OverlayTypeInfo*
OverlayTypeSelector::getSelectedOverlayType() const
{
  ASSERT( NULL != d_pTypeInfoList );
  ASSERT( d_selectedIndex >= 0 && 
          d_selectedIndex < d_pTypeInfoList->size() );
  return (*d_pTypeInfoList)[d_selectedIndex];
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OVERLAYTYPESELECTOR_H__959914E2_CE85_11D1_BE41_006097096D7B__INCLUDED_)
