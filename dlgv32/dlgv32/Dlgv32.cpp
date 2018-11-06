// dlgv32.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "dlgv32.h"

#include "MainFrm.h"
#include "dlgv32Doc.h"
#include "dlgv32View.h"
#include "DeveloperInfoDialog.h"
#include "DLGOverlay.h"

//#define _BETA_	// enables beta warning, comment out for production releases

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgv32App

BEGIN_MESSAGE_MAP(CDlgv32App, CWinApp)
	//{{AFX_MSG_MAP(CDlgv32App)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	//ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	//ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)

	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgv32App construction

CDlgv32App::CDlgv32App()
{
#ifdef _BETA_
	// Notify the user if a new version is likely available for
	// download if this is a beta version.
	CTime currentTime = CTime::GetCurrentTime();
	CTime badTime( 1998, 7, 1, 0, 0, 0 );
	if ( currentTime > badTime )
	{
		CString message;
		UINT flags = MB_OK | MB_ICONWARNING;
		message  = "This beta version of DLG Viewer has EXPIRED!  We ";
		message += "expire beta versions of our software in an attempt ";
		message += "to eliminate versions known to contain untested ";
		message += "features.  If you wish to continue using DLG Viewer, ";
		message += "please download either the latest beta version ";
		message += "which will also eventually expire) or the latest ";
		message += "production version (which will NOT expire) from ";
		message += "ftp://ftpmcmc.er.usgs.gov/release/viewers/dlgv32.";
		::MessageBox( NULL, message, "Beta Expired!", flags );

		// Exit the program
		::ExitProcess(1);
	}
	else
	{
		CString message;
		UINT flags = MB_OK | MB_ICONINFORMATION;
		message  = "This is a BETA version of DLG Viewer.  'Beta' means ";
		message += "that it is untested.  It may have serious, even ";
		message += "fatal bugs.  It may also have features that will ";
		message += "not appear in the final release.  Use at your own ";
		message += "risk.\n\n";
		message += "We release beta versions in an attempt to find as many ";
		message += "bugs as possible before distributing DLG Viewer to a ";
		message += "wider audience.  You can help us by reporting any ";
		message += "problems you have with this version to dlgview@mailrmon1.er.usgs.gov.  ";
		message += "Please include the following version number:  3.5b1.\n\n";
		message += "This version of DLG Viewer will expire (cease to ";
		message += "function) on July 1, 1998. At that time, download ";
		message += "either the latest beta version (which will also ";
		message += "eventually expire) or the latest production version ";
		message += "(which will NOT expire) from ";
		message += "ftp://ftpmcmc.er.usgs.gov/release/viewers/dlgv32.";
		::MessageBox( NULL, message, "Warning - Beta Version", flags );
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDlgv32App object

CDlgv32App theApp;

/////////////////////////////////////////////////////////////////////////////
// CDlgv32App initialization

BOOL CDlgv32App::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Set the base registry key to:
	// "HKEY_CURRENT_USER\SOFTWARE\USGS-NMD-MCMC-RTA-SES"
	SetRegistryKey( "USGS-NMD-MCMC-RTA-SES" );
	
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CDlgv32Doc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CDlgv32View));
	AddDocTemplate(pDocTemplate);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Set the windows title
	CString title = "DLG Viewer";
	m_pMainWnd->SetWindowText( title );

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CDlgv32App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

CDocument* CDlgv32App::OpenDocumentFile(LPCTSTR lpszFileName) 
{
	// Get a pointer to the document template
	POSITION docTempPos = GetFirstDocTemplatePosition();
	CSingleDocTemplate* pTemp = (CSingleDocTemplate*)GetNextDocTemplate( docTempPos );

	// Get a pointer to the first document
	POSITION docPos = pTemp->GetFirstDocPosition();
	CDlgv32Doc* pDoc = (CDlgv32Doc*)pTemp->GetNextDoc( docPos );

	// If the document already exists, just call my version of
	// OnOpenDocument, otherwise, call the framework stuff and then
	// call my version of it
	if ( pDoc != NULL )
	{
		pDoc->OnOpenDocument( lpszFileName );	
		return pDoc;
	}
	else
	{
		return CWinApp::OpenDocumentFile(lpszFileName);
	}
}

BOOL CDlgv32App::OnIdle(LONG lCount) 
{
	// Let the framework do all of its idle processing first
	if ( CWinApp::OnIdle( lCount ) )
	{
		return TRUE;
	}

	// Call the view's OnIdle handler
	CFrameWnd* pFrameWnd = dynamic_cast<CFrameWnd*>(AfxGetMainWnd() );
	if ( pFrameWnd != NULL )
	{
		CDlgv32View* pView = dynamic_cast<CDlgv32View*>(pFrameWnd->GetActiveView() );
		if ( pView != NULL )
		{
			return pView->OnIdle( lCount );
		}
	}

	return FALSE;
}

void CAboutDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if ( nFlags & MK_CONTROL )
	{
		// Show extended about box
		DeveloperInfoDialog dlg;
		dlg.DoModal();
	}
	
	CDialog::OnLButtonDown(nFlags, point);
}
