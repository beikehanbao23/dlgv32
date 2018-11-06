// TIFFPropertyPage.cpp : implementation file
//

#include "stdafx.h"
#include "dlgv32.h"
#include "TIFFPropertyPage.h"
#include "TIFFOverlay.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TIFFPropertyPage property page

IMPLEMENT_DYNCREATE(TIFFPropertyPage, CPropertyPage)

TIFFPropertyPage::TIFFPropertyPage( ) : CPropertyPage(TIFFPropertyPage::IDD)
{
	//{{AFX_DATA_INIT(TIFFPropertyPage)
	d_strPhotometricInterp = _T("");
	d_strBPP = _T("");
	d_strRowsPerStrip = _T("");
	d_strCopyright = _T("");
	d_strDateTime = _T("");
	d_strDescription = _T("");
	d_strLength = _T("");
	d_strWidth = _T("");
	//}}AFX_DATA_INIT
}

TIFFPropertyPage::TIFFPropertyPage( TIFFOverlay* pTIFF ) : CPropertyPage(TIFFPropertyPage::IDD)
{
	// Account for NULL values for copyright, datetime, & description
	if ( pTIFF->d_copyright )
	{
		d_strCopyright = pTIFF->d_copyright;
	}
	else
	{
		d_strCopyright = _T( "None given" );
	}

	if ( pTIFF->d_datetime )
	{
		d_strDateTime = pTIFF->d_datetime;
	}
	else
	{
		d_strDateTime = _T( "None given" );
	}

	if ( pTIFF->d_description )
	{
		d_strDescription = pTIFF->d_description;
	}
	else
	{
		d_strDescription = _T( "None given" );
	}

	// Populate the dialog
	d_strBPP.Format( "%u", pTIFF->getBitsPerPixel() );
	d_strLength.Format( "%d", pTIFF->d_imageLength );
	d_strRowsPerStrip.Format( "%d", pTIFF->d_rowsPerStrip );
	d_strWidth.Format( "%d", pTIFF->d_imageWidth );
	d_strPhotometricInterp = pTIFF->photoInterpToString();
}

TIFFPropertyPage::~TIFFPropertyPage()
{
}

void TIFFPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(TIFFPropertyPage)
	DDX_Text(pDX, IDC_PHOTOMETRIC_INTERP, d_strPhotometricInterp);
	DDX_Text(pDX, IDC_BITS_PER_SAMPLE, d_strBPP);
	DDX_Text(pDX, IDC_ROWS_PER_STRIP, d_strRowsPerStrip);
	DDX_Text(pDX, IDC_TIFF_COPYRIGHT, d_strCopyright);
	DDX_Text(pDX, IDC_TIFF_DATETIME, d_strDateTime);
	DDX_Text(pDX, IDC_TIFF_DESCRIPTION, d_strDescription);
	DDX_Text(pDX, IDC_TIFF_LENGTH, d_strLength);
	DDX_Text(pDX, IDC_TIFF_WIDTH, d_strWidth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(TIFFPropertyPage, CPropertyPage)
	//{{AFX_MSG_MAP(TIFFPropertyPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TIFFPropertyPage message handlers
