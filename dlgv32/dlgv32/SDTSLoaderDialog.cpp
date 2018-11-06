// SDTSLoaderDialog.cpp : implementation file
//

#include "stdafx.h"
#include "dlgv32.h"
#include "SDTSLoaderDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SDTSLoaderDialog dialog


SDTSLoaderDialog::SDTSLoaderDialog(CWnd* pParent /*=NULL*/)
	: CDialog(SDTSLoaderDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(SDTSLoaderDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void SDTSLoaderDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SDTSLoaderDialog)
	DDX_Control(pDX, IDC_SDTS_FILELIST, m_manifoldList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SDTSLoaderDialog, CDialog)
	//{{AFX_MSG_MAP(SDTSLoaderDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SDTSLoaderDialog message handlers
