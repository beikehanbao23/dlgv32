// SDTSDLG_AHDRPage.cpp : implementation file
//

#include "stdafx.h"
#include "dlgv32.h"
#include "SDTSDLG_AHDRPage.h"
#include "SDTS_AttModule.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SDTSDLG_AHDRPage property page

IMPLEMENT_DYNCREATE(SDTSDLG_AHDRPage, CPropertyPage)

SDTSDLG_AHDRPage::SDTSDLG_AHDRPage() 
: CPropertyPage(SDTSDLG_AHDRPage::IDD), d_bInitialized(false)
{
	//{{AFX_DATA_INIT(SDTSDLG_AHDRPage)
	//}}AFX_DATA_INIT
}

SDTSDLG_AHDRPage::~SDTSDLG_AHDRPage()
{
}

void SDTSDLG_AHDRPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SDTSDLG_AHDRPage)
	DDX_Control(pDX, IDC_SDTSDLG_AHDR_BANNER, d_bannerTextControl);
	DDX_Control(pDX, IDC_SDTSDLG_AHDR_PAIRS, d_pairs);
	//}}AFX_DATA_MAP
    // Make sure a module pointer has been added
    ASSERT( NULL != d_ppAHDRModule );

    // Initialize the list view if necessary
    if ( !d_bInitialized )
    {
        initColumns();
        d_bInitialized = true;
    }

    // Delete all the rows currently in the list view
    d_pairs.DeleteAllItems();

    // Check to see if the AHDR module has finished loading
    if ( NULL != *d_ppAHDRModule )
    {
        // The AHDR module is loaded, get the appropriate record
        SDTS_AttRecord* pRecord = (*d_ppAHDRModule)->getRecord( d_recordNumber );

        // Make sure a valid record was returned
        if ( NULL != pRecord )
        {
            // A valid record was retrieved, get the label-value pairs
            vector<SDTSAtt_LabelValuePair> labelValuePairs;
            pRecord->getLabelValuePairs( labelValuePairs );

            // Have the dialog display the pairs
            setPairs( labelValuePairs );
        }
        else
        {
            // Display an invalid record error in the banner box
            d_bannerTextControl.SetWindowText( _T( "Invalid AHDR Record Number" ) );
        }
    }
    else
    {
        // The AHDR module isn't finished loading, display a message in the banner box
        d_bannerTextControl.SetWindowText( _T( "The AHDR module hasn't finished loading" ) );
    }
}


BEGIN_MESSAGE_MAP(SDTSDLG_AHDRPage, CPropertyPage)
	//{{AFX_MSG_MAP(SDTSDLG_AHDRPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SDTSDLG_AHDRPage message handlers

void 
SDTSDLG_AHDRPage::setPairs( const vector<SDTSAtt_LabelValuePair>& pairs )
{
    // Get the size of the list
    int size = d_pairs.GetItemCount();

	// Add each pair to list
    for ( vector<SDTSAtt_LabelValuePair>::const_iterator i = pairs.begin();
          i != pairs.end(); i++ )
    {
        // If this is the BANNER pair put the text in the banner control
        if ( "BANNER" == i->getLabel() )
        {
            d_bannerTextControl.SetWindowText( i->getValue().c_str() );
        }
        else
        {
            // Insert the label-value pair at the end of the list
	        d_pairs.InsertItem( size, i->getLabel().c_str() );
	        d_pairs.SetItemText( size, 1, i->getValue().c_str() );
            size++;
        }
    }
    
    resizeColumns();
}

void 
SDTSDLG_AHDRPage::resizeColumns()
{
	// Determine width of the List View
	CRect listViewSize;
	int   width;
	d_pairs.GetClientRect( &listViewSize );
	listViewSize.NormalizeRect();
	width = listViewSize.Width();

    // Iterate through the list to find the widest text string in each column
    int count = d_pairs.GetItemCount();
    int maxWidthCol1 = 1;
    int maxWidthCol2 = 1;
    int curItemWidth = 0;
    for ( int i = 0; i < count; i++ )
    {
        curItemWidth = d_pairs.GetStringWidth( d_pairs.GetItemText( i, 0 ) );
        maxWidthCol1 = max( maxWidthCol1, curItemWidth );
        curItemWidth = d_pairs.GetStringWidth( d_pairs.GetItemText( i, 1 ) );
        maxWidthCol2 = max( maxWidthCol2, curItemWidth );
    }

	// Modify the widths of the columns so the columns take an appropriate portion of the
    // available width based on the width of the widest string in each column
    int col1Width = width * maxWidthCol1 / ( maxWidthCol1 + maxWidthCol2 );
	LV_COLUMN column;
	column.mask = LVCF_WIDTH;
	column.cx   = col1Width;
	d_pairs.SetColumn( 0, &column );
    column.cx = width - col1Width; // Add 1 if the width is odd
	d_pairs.SetColumn( 1, &column );
}

void 
SDTSDLG_AHDRPage::initColumns()
{
	// Determine width of the List View
	CRect listViewSize;
	int   width;
	d_pairs.GetClientRect( &listViewSize );
	listViewSize.NormalizeRect();
	width = listViewSize.Width();

	// Insert the columns into the ListView
	d_pairs.InsertColumn( 0, "LABEL", LVCFMT_CENTER, width / 2, 1 );
	d_pairs.InsertColumn( 1, "VALUE", LVCFMT_CENTER, (width / 2) + width % 2 );		                                        

	// Make first column be centered
	LV_COLUMN column;
	column.mask = LVCF_FMT;
	column.fmt  = LVCFMT_CENTER;
	d_pairs.SetColumn( 0, &column );
}
