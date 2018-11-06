// SDTSLayerDialog.cpp : implementation file
//

#include "stdafx.h"
#include "dlgv32.h"
#include "SDTSLayerDialog.h"

#include <fstream>
using namespace std;

// SDTS includes
#include "sdtsxx/io/sio_8211DirEntry.h"
#include "sdtsxx/container/sc_Record.h"
#include "sdtsxx/io/sio_Reader.h"
#include "sdtsxx/builder/sb_CatalogSpatialDom.hxx"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SDTSLayerDialog dialog

SDTSModuleInfo::SDTSModuleInfo( sb_CatalogSpatialDom* pCatSEntry )
{
    d_strAGOB  = pCatSEntry->getAggregateObj().c_str();
    d_strAGOB.TrimRight();
    d_strMap   = pCatSEntry->getMap().c_str();
    d_strMap.TrimRight();
    d_strTheme = pCatSEntry->getTheme().c_str();
    d_strTheme.TrimRight();

    if ( d_strAGOB.IsEmpty() )
    {
        d_strAGOB = "01";
    }
}

SDTSLayerDialog::SDTSLayerDialog( CString strCATSFilename, CWnd* pParent )
: CDialog(SDTSLayerDialog::IDD, pParent), d_numSelected(0), d_pSelectedEntries(NULL),
  d_bRasterTransfer(false)
{
	//{{AFX_DATA_INIT(SDTSLayerDialog)
	//}}AFX_DATA_INIT

    // Populate the layer dialog with the line layer modules
    populateLayers( strCATSFilename, "Line" );

    // If there were no line layers, try the point-node layers
    if ( 0 == d_pLineEntries.size() )
    {
        populateLayers( strCATSFilename, "Point-Node" );

        // If there were no point-node layers, test for cell modules
        if ( 0 == d_pLineEntries.size() )
        {
            populateLayers( strCATSFilename, "Cell" );

            if ( 0 != d_pLineEntries.size() )
            {
                d_bRasterTransfer = true;
            }
        }
    }
}

void
SDTSLayerDialog::populateLayers( const CString& strCATSFilename, const CString& strName )
{
    // Populate the layer dialog with layer info from the CATS module
    ifstream ddf( strCATSFilename, ios::binary );

    if ( !ddf )
    {
        return;
	}

	sio_8211Reader        reader( ddf );
    sc_Record             record;
    sb_CatalogSpatialDom* pCatSEntry = NULL;
	CString			      strCatSEntryType;				
	for ( sio_8211ForwardIterator i( reader ); !i.done(); ++i )									
    {	
		// Get records from the CATS file
        i.get( record );

		pCatSEntry = new sb_CatalogSpatialDom( record );

		// Get the type of the entry
        strCatSEntryType = pCatSEntry->getType().c_str();
		strCatSEntryType.TrimRight();

		// Add the entry to the line entries if it's a line
        if ( 0 == strCatSEntryType.CompareNoCase( strName ) ) 
        {
            d_pLineEntries.push_back( pCatSEntry );
		}
        else
        {
            delete pCatSEntry;
        }
	}

    ddf.close();
}

SDTSLayerDialog::~SDTSLayerDialog()
{
    delete[] d_pSelectedEntries;
    
    // Delete all CatS entries
    for ( vector<sb_CatalogSpatialDom*>::iterator i = d_pLineEntries.begin();
          i != d_pLineEntries.end(); i++ )
    {
        delete *i;
    }

    // Delete all module info entries
    for ( vector<SDTSModuleInfo*>::iterator j = d_pSelectedModules.begin();
          j != d_pSelectedModules.end(); j++ )
    {
        delete *j;
    }
}       

void SDTSLayerDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SDTSLayerDialog)
	DDX_Control(pDX, IDC_LAYER_LIST, m_manifoldList);
	//}}AFX_DATA_MAP

    // Create a text string based on each of the line entries and
    // add it to the layers list
    CString strText;
    CString strMapName;
    for ( vector<sb_CatalogSpatialDom*>::iterator i = d_pLineEntries.begin();
          i != d_pLineEntries.end(); i++ )
    {
        strMapName = (*i)->getMap().c_str();
        strMapName.TrimRight();

        strText.Format( "<%s> - %s - %s", (*i)->getAggregateObj().c_str(),
                        strMapName, (*i)->getTheme().c_str() );
        strText.TrimRight();

        m_manifoldList.AddString( strText );
    }
}


BEGIN_MESSAGE_MAP(SDTSLayerDialog, CDialog)
	//{{AFX_MSG_MAP(SDTSLayerDialog)
	ON_LBN_SELCHANGE(IDC_LAYER_LIST, OnSelchangeLayerList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SDTSLayerDialog message handlers

const vector<SDTSModuleInfo*>& SDTSLayerDialog::GetSelected()
{
    // Clear the vector of selected entries
    d_pSelectedModules.clear();

    // Create a vector of selected modules
    SDTSModuleInfo* pModuleInfo = NULL;
    int index;
    for ( int i = 0; i < d_numSelected; i++ )
    {
        index = d_pSelectedEntries[i];
        pModuleInfo = new SDTSModuleInfo( d_pLineEntries[index] );
        d_pSelectedModules.push_back( pModuleInfo );
    }

    return d_pSelectedModules;
}

void SDTSLayerDialog::OnSelchangeLayerList() 
{
	// Delete current list of selected entries
    delete[] d_pSelectedEntries;

    // Get the currently selected entries
    d_numSelected = m_manifoldList.GetSelCount();
    d_pSelectedEntries = new int[d_numSelected];
	m_manifoldList.GetSelItems( d_numSelected, d_pSelectedEntries );
}

int SDTSLayerDialog::DoModal() 
{    
    // If there is just one layer, select it
    if ( 1 == d_pLineEntries.size() )
    {
        d_pSelectedEntries = new int[1];
        d_pSelectedEntries[0] = 0;
        d_numSelected = 1;
        return IDOK;
    }
    // If there aren't any layers, show an error
    else if ( 0 == d_pLineEntries.size() )
    {
        AfxMessageBox( "No line, point-node, or raster modules in the transfer." );
        return IDCANCEL;
    }
	
	return CDialog::DoModal();
}
