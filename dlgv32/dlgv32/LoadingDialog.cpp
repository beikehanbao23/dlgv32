// LoadingDialog.cpp : implementation file
//

#include "stdafx.h"
#include "dlgv32.h"
#include "LoadingDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoadingDialog dialog


CLoadingDialog::CLoadingDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CLoadingDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoadingDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	Create( CLoadingDialog::IDD );
}


void CLoadingDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoadingDialog)
	DDX_Control(pDX, IDC_PROGRESS1, d_progressControl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoadingDialog, CDialog)
	//{{AFX_MSG_MAP(CLoadingDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoadingDialog message handlers
