// dlgv32.h : main header file for the DLGV32 application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include <iostream>
#include "resource.h"       // main symbols

#ifdef _WIN32
	using namespace std;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgv32App:
// See dlgv32.cpp for the implementation of this class
//

class CDlgv32App : public CWinApp
{
public:
	CDlgv32App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgv32App)
	public:
	virtual BOOL InitInstance();
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDlgv32App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
