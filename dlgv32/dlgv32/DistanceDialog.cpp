// DistanceDialog.cpp : implementation file
//

#include "stdafx.h"
#include "dlgv32.h"
#include "DistanceDialog.h"

#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// CDistanceDialog dialog

CDistanceDialog::CDistanceDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDistanceDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDistanceDialog)
	d_units = -1;
	d_distance = _T("");
	//}}AFX_DATA_INIT
}


void CDistanceDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDistanceDialog)
	DDX_Control(pDX, IDC_DISTANCE, d_distanceCtl);
	DDX_Radio(pDX, IDC_METERS, d_units);
	DDX_Text(pDX, IDC_DISTANCE, d_distance);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDistanceDialog, CDialog)
	//{{AFX_MSG_MAP(CDistanceDialog)
	ON_BN_CLICKED(IDC_METERS, OnMeters)
	ON_BN_CLICKED(IDC_FEET, OnFeet)
	ON_BN_CLICKED(IDC_KILOMETERS, OnKilometers)
	ON_BN_CLICKED(IDC_Miles, OnMiles)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDistanceDialog message handlers

void 
CDistanceDialog::OnMeters() 
{
	d_units = 0;

	// Update display
	setDistanceMeters( d_distMeters );

	// Update the text box text
	d_distanceCtl.SetWindowText( d_distance );
	UpdateData();
}

void 
CDistanceDialog::setDistanceMeters( double dist )
{
	double new_distance;	// distance in new units

	d_distMeters = dist;

	// Determine number of digits to display
	int digits;
	if ( dist > 0 )
	{
		digits = log10(dist) + 2;
		if ( digits > 6 )
			digits = 6;
	}
	else
	{
		digits = 2;
	}
	
	switch ( d_units )
	{
		case 0:	// meters
		{
			new_distance = dist;
			break;
		}
		case 1: // kilometers
		{
			new_distance = dist / 1000.0;
			break;
		}
		case 2: // feet
		{
			new_distance = dist * 100.0 / ( 2.54 * 12.0);
			break;
		}
		case 3: // miles
		{
			new_distance = dist * 100.0 / ( 2.54 * 12.0 * 5280.0 );
			break;
		}
	}

	// Set text of static control
	char buffer[10];
	_gcvt( new_distance, digits, buffer );	// Convert distance to a char array
	d_distance = CString( "Distance = " ) + CString( buffer );

	return;
}


void CDistanceDialog::OnFeet() 
{
	d_units = 2;

	// Update display
	setDistanceMeters( d_distMeters );

	// Update the text box text
	d_distanceCtl.SetWindowText( d_distance );
	UpdateData();
}

void CDistanceDialog::OnKilometers() 
{
	d_units = 1;

	// Update display
	setDistanceMeters( d_distMeters );

	// Update the text box text
	d_distanceCtl.SetWindowText( d_distance );
	UpdateData();
}

void CDistanceDialog::OnMiles() 
{
	d_units = 3;

	// Update display
	setDistanceMeters( d_distMeters );

	// Update the text box text
	d_distanceCtl.SetWindowText( d_distance );
	UpdateData();
}
