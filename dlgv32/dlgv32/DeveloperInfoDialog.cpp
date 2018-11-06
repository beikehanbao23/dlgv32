// DeveloperInfoDialog.cpp : implementation file
//

#include "stdafx.h"
#include "dlgv32.h"
#include "DeveloperInfoDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DeveloperInfoDialog dialog


DeveloperInfoDialog::DeveloperInfoDialog(CWnd* pParent /*=NULL*/)
	: CDialog(DeveloperInfoDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(DeveloperInfoDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DeveloperInfoDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DeveloperInfoDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DeveloperInfoDialog, CDialog)
	//{{AFX_MSG_MAP(DeveloperInfoDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DeveloperInfoDialog message handlers
