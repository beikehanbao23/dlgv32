// LoadingDialog.h - interface for LoadingDialog class
//
// Developed by: Mike Childs
//      Started: 4/20/98

#ifndef _LOADINGDIALOG_H_
#define _LOADINGDIALOG_H_

#include <windows.h>

class LoadingDialog
{
public:
    // Construction/Destruction
    LoadingDialog();
    ~LoadingDialog();

    // Creation
    bool create( HINSTANCE hInst );

    // Display
    void show( const char* strTitle );
    void destroy();

    // Progress setting
    void incrementPos();
    void setRange( int low, int high );
    void setPos( int pos );

private:
    HWND d_hDialog;
};

#endif