// LoadingDialog.cpp - implementation of LoadingDialog class
//
// Developed by: Mike Childs
//      Started: 4/20/98

#include "LoadingDialog.h"
#include "resource.h"
#include <commctrl.h>

// Procedure for handling messages
BOOL CALLBACK LoadingDialogProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    return FALSE;
}

LoadingDialog::LoadingDialog()
: d_hDialog(NULL)
{
    ::InitCommonControls();
}

LoadingDialog::~LoadingDialog()
{
    if ( NULL != d_hDialog )
    {
        ::DestroyWindow( d_hDialog );
    }
}

bool
LoadingDialog::create( HINSTANCE hInst )
{
    d_hDialog = ::CreateDialog( hInst, MAKEINTRESOURCE( IDD_LOADING_DIALOG ),
                              ::GetActiveWindow(), (DLGPROC)LoadingDialogProc );

    return ( NULL != d_hDialog );
}

void
LoadingDialog::destroy()
{
    ::DestroyWindow( d_hDialog );
    d_hDialog = NULL;
}

void
LoadingDialog::incrementPos()
{
    HWND hProgBar = ::GetDlgItem( d_hDialog, IDC_PROGRESS );
    ::SendMessage( hProgBar, PBM_DELTAPOS, (WPARAM)1, 0 );
}

void
LoadingDialog::setPos( int pos )
{
    HWND hProgBar = ::GetDlgItem( d_hDialog, IDC_PROGRESS );
    ::SendMessage( hProgBar, PBM_SETPOS, (WPARAM)pos, 0 );
}

void
LoadingDialog::setRange( int low, int high )
{
    HWND hProgBar = ::GetDlgItem( d_hDialog, IDC_PROGRESS );
    ::SendMessage( hProgBar, PBM_SETRANGE, 0, MAKELPARAM( low, high ) );
}

void
LoadingDialog::show( const char* strTitle )
{
    // Get the bounding rectangle for the parent window
    RECT rectParent;
    ::GetWindowRect( ::GetParent( d_hDialog ), &rectParent );

    // Get the bounding rectangle for the loading dialog
    RECT rectDialog;
    ::GetWindowRect( d_hDialog, &rectDialog );

    // Determine where to positon the dialog
    int x = ( rectParent.right - rectParent.left ) - ( rectDialog.right - rectDialog.left );
    x /= 2;
    x += rectParent.left;
    int y = ( rectParent.bottom - rectParent.top ) - ( rectDialog.bottom - rectDialog.top );
    y /= 2;
    y += rectParent.top;

    // Center and show the dialog
    ::MoveWindow( d_hDialog, x, y,
                  rectDialog.right - rectDialog.left,
                  rectDialog.bottom - rectDialog.top, TRUE );
    ::SetWindowText( d_hDialog, strTitle );
    ::ShowWindow( d_hDialog, SW_SHOW );
}