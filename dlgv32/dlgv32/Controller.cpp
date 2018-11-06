// Controller.cpp - implementation file for Controller class
//
// Developed by: Mike Childs
//      Started: 10/24/96
//

#include "Controller.h"
#include "Dlgv32View.h"

Controller::Controller()
: d_ptrView(0)
{
	d_hCursor = AfxGetApp()->LoadStandardCursor( IDC_ARROW );
}

Controller::Controller( CDlgv32View* ptrView )
: d_ptrView(ptrView)
{
	d_hCursor = AfxGetApp()->LoadStandardCursor( IDC_ARROW );
}
