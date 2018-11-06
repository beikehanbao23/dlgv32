// SDTSDLGOverlay.cpp - implementation for SDTSDLGOverlay class
//
// Developed by: Mike Childs
//      Started: 8/31/97

#include <stdlib.h> // for atol

#include "SDTSDLGOverlay.h"
#include "SDTSDLGPolylineGraphic.h"
#include "SDTSDLGPointGraphic.h"
#include "SDTSDLGDegLineGraphic.h"
#include "SDTSDLG_PropSheet.h"
#include "SDTS_AttModule.h"
#include "SDTS_AttModuleFactory.h"
#include "SDTS_MDEFFactory.h"
#include "SDTS_MDEFModule.h"
#include "LoadingDialog.h"
#include "MainFrm.h"
#include "MC_SBAR.h"
#include <fstream>
using namespace std;

// SDTS includes
#include "sdtsxx/io/sio_Reader.h"
#include "sdtsxx/io/sio_8211Converter.h"
#include "sdtsxx/builder/sb_AttAccuracy.hxx"
#include "sdtsxx/builder/sb_CatalogDir.hxx"
#include "sdtsxx/builder/sb_Completeness.hxx"
#include "sdtsxx/builder/sb_Composite.hxx"
#include "sdtsxx/builder/sb_ExtSpatialRef.hxx"
#include "sdtsxx/builder/sb_IntSpatialRef.hxx"
#include "sdtsxx/builder/sb_Ident.hxx"
#include "sdtsxx/builder/sb_Lineage.hxx"
#include "sdtsxx/builder/sb_LogicalConsis.hxx"
#include "sdtsxx/builder/sb_PointNode.hxx"
#include "sdtsxx/builder/sb_Polygon.hxx"
#include "sdtsxx/builder/sb_PosAccuracy.hxx"
#include "sdtsxx/builder/sb_SpatialDom.hxx"
#include "sdtsxx/builder/sb_TransferStats.hxx"
#include "sdtsxx/builder/sb_Utils.hxx"
#include "sdtsxx/container/sc_Record.h"

// Projection includes
#include "ProjectionLib/GeographicProjection.h"
#include "ProjectionLib/UTMProjection.h"

SDTSDLGOverlay::AttMapRecord::AttMapRecord( const CString& strName )
: d_strName(strName), d_pModule(NULL)
{
}

SDTSDLGOverlay::SDTSDLGOverlay( CString& strCATDFilename, const CString& strAGOB,
                                const CString& strMap,    const CString& strTheme, 
                                const CString& strPath )
: DLGOverlay(strCATDFilename), 
  d_strTheme(strTheme), d_strMap(strMap), d_strAGOB(strAGOB), d_strPath(strPath),
  d_pExternalRef(NULL), d_pInternalRef(NULL), d_pIdent(NULL), d_pSpatialDom(NULL),
  d_pDQAA(NULL), d_pDQCG(NULL), d_pDQHL(NULL), d_pDQLC(NULL), d_pDQPA(NULL),
  d_pAttModuleThread(NULL), d_pDataQualityThread(NULL), d_pAttHeaderThread(NULL),
  d_numNodes(0), d_numLines(0), d_numDegLines(0), d_numAreas(0), d_numPolygons(0),
  d_pMDEFModule(NULL), d_moduleVersion(0), d_bDestroying(false), d_bUnknownTheme(false),
  d_pAHDRModule(NULL), d_ahdrRecordNum(0), d_pPropertySheet(NULL)
{
    for ( int i = 0; i < 4; i++ )
    {
        d_pControlPoints[i] = NULL;
    }

    // Make the filename be a descriptive string    
    d_strDescription.Format( "<%s> <%s> - %s - %s", 
                             getFilenameWithoutPath(), strAGOB, strMap, strTheme );

    // Determine the attribute module names for this theme
    getAttModuleNameFromTheme();
}

SDTSDLGOverlay::~SDTSDLGOverlay()
{
  	// Show a wait cursor
	  HCURSOR hOldCursor = ::SetCursor( AfxGetApp()->LoadStandardCursor( IDC_WAIT ) );

    // Make sure no other threads try to start
    d_bDestroying = true;

    // Wait for the attribute header thread to finish loading
    if ( NULL != d_pAttHeaderThread )
    {
        ::WaitForSingleObject( d_pAttHeaderThread->m_hThread, INFINITE );
    }

    // Wait for the attribute module thread to finish loading
    if ( NULL != d_pAttModuleThread )
    {
        ::WaitForSingleObject( d_pAttModuleThread->m_hThread, INFINITE );
    }

    // Wait for the data quality thread to finish loading
    if ( NULL != d_pDataQualityThread )
    {
        ::WaitForSingleObject( d_pDataQualityThread->m_hThread, INFINITE );
    }

    // Release references to all open modules and delete members of map
    for ( list<AttMapRecord*>::iterator i = d_attModuleMap.begin();
          i != d_attModuleMap.end(); i++ )
    {
        if ( NULL != (*i)->d_pModule )
        {
            SDTS_AttModuleFactory::Release( (*i)->d_pModule );
        }

        delete *i;
    }

    // Reclaim space used by the MDEF module
    if ( NULL != d_pIdent && NULL != d_pMDEFModule )
    {
        SDTS_MDEFFactory::Release( d_pIdent->getScale() );
    }

    // Reclaim space used by the AHDR module
    if ( NULL != d_pAHDRModule )
    {
        SDTS_AttModuleFactory::Release( d_pAHDRModule );
    }

    // Reclaim space used by member data
    delete d_pDQAA;
    delete d_pDQCG;
    delete d_pDQHL;
    delete d_pDQLC;
    delete d_pDQPA;
    delete d_pExternalRef;
    delete d_pInternalRef;
    delete d_pIdent;
    delete d_pSpatialDom;

    // Delete all the polygons
    for ( vector<sb_Polygon*>::iterator j = d_pPolygons.begin(); 
          j != d_pPolygons.end(); j++ )
    {
        delete (*j);
    }

    for ( int k = 0; k < 4; k++ )
    {
        delete d_pControlPoints[k];
    }

    // Restore cursor
    ::SetCursor( hOldCursor );
}

BOOL 
SDTSDLGOverlay::load()
{
    // Show a loading dialog, the progress control will be used later
    CLoadingDialog dlgLoading;
    CString strTitle;
    strTitle.Format( "Loading %s...", d_filename );
    dlgLoading.SetWindowText( strTitle );

    // Get the necessary file names from the CATD file
    if ( !processCATD() )
    {
        // Abort load
        AfxMessageBox( "Unable to read CATD file\nAborting load..." );
        return FALSE;
    }

    // Load the transfer statistics
    if ( !loadTransferStats() )
    {
        // Abort load
        AfxMessageBox( "Unable to load transfer statistics module\n"
                       "The loading dialog will not be correct" );
    }

    // Setup the loading dialog
    int size =  4 + d_numLines + d_numNodes + d_numDegLines + d_numAreas + d_numPolygons;
    dlgLoading.d_progressControl.SetRange( 0, size );
    dlgLoading.d_progressControl.SetPos( 0 );

    // Load the external spatial reference data
    if ( !loadExternalRef() )
    {
        // Abort load
        AfxMessageBox( "Unable to load external spatial reference data\nAborting load..." );
        return FALSE;
    }

    // Update loading dialog
    dlgLoading.d_progressControl.OffsetPos( 1 );

    // Load the identification module
    if ( !loadIdent() )
    {
        // Abort load
        AfxMessageBox( "Unable to load Identifiaction module\nAborting load..." );
        return FALSE;
    }

    // Update loading dialog
    dlgLoading.d_progressControl.OffsetPos( 1 );

    // Setup the projection
    if ( !setupProjection() )
    {
        return FALSE;
    }

    // Load the internal spatial reference data
    if ( !loadInternalRef() )
    {
        // Abort load
        AfxMessageBox( "Unable to load internal spatial reference data\nAborting load..." );
        return FALSE;
    }

    // Update loading dialog
    dlgLoading.d_progressControl.OffsetPos( 1 );

    // Read in the control points
    if ( !loadControlPoints() )
    {
        // Abort load
        AfxMessageBox( "Unable to load control points\nAborting load..." );
        return FALSE;
    }
    // Update loading dialog
    dlgLoading.d_progressControl.OffsetPos( 1 );

    // Reserve space for all of the areas
    d_pAreas.reserve( d_numAreas );

    // Read in the areas
    if ( !readAreas( dlgLoading ) )
    {
        if ( 0 != d_numAreas )
        {
            // Abort load
            AfxMessageBox( "Error reading nodes\nAborting load..." );
            return FALSE;
        }
    }

    // Reserve space for all of the lines
    d_pLines.reserve( d_numLines + d_numDegLines );

    // Read in the lines
    if ( !readLines( dlgLoading ) )
    {
        if ( 0 != d_numLines )
        {
            // Abort load
            AfxMessageBox( "Error reading lines\nAborting load..." );
            return FALSE;
        }
    }

    // Read in the degenerate lines if there are any
    if ( !readDegLines( dlgLoading ) )
    {
        if ( 0 != d_numDegLines )
        {
            // Abort load
            AfxMessageBox( "Error reading degenerate lines\nAborting load..." );
            return FALSE;
        }
    }

    // Reserve space for all of the nodes
    d_pNodes.reserve( d_numNodes );

    // Read in the nodes
    if ( !readNodes( dlgLoading ) )
    {
        if ( 0 != d_numNodes )
        {
            // Abort load
            AfxMessageBox( "Error reading nodes\nAborting load..." );
            return FALSE;
        }
    }

    // Reserve space for the polygons
    d_pPolygons.reserve( d_numPolygons );

    // Read in the polygons
    if ( !readPolygons( dlgLoading ) )
    {
        if ( 0 != d_numPolygons )
        {
            // Abort load
            AfxMessageBox( "Error reading polygons\nAborting load..." );
            return FALSE;
        }
    }

    // Load the attribute modules
    if ( !loadAttributeModules() )
    {
        AfxMessageBox( "Error loading attribute modules,\n"
                       "Entity info will not be available" );
    }

    // Load the attribute header module
    if ( !loadAttributeHeaderModule() )
    {
        AfxMessageBox( "Error loading attribute header module" );
    }

    // Load the data quality modules
    if ( !loadDataQualityModules() )
    {
        AfxMessageBox( "Error loading data quality modules.\n"
                       "Data Quality information will not be available" );
    }

    // Set the color to the default for this overlay type
    d_color = getDefaultColor( d_strTheme.Left(4) );

    d_loaded = TRUE;
    calculateBoundingRect();
    
    // Handle the global projection
    handleProjectionChanged();

    return TRUE;
}

// Extracts necessary filenames from CATD file
bool
SDTSDLGOverlay::processCATD( void )
{
    ifstream ddf( getFilename(), ios::binary );

	  if ( !ddf )
    {
        return false;
    }

    sio_8211Reader	reader( ddf );				
	  sc_Record		record;
	  sb_CatalogDir*	pCatDEntry;
    CString         strCatDEntryName;
				
	  for ( sio_8211ForwardIterator iterator( reader ); !iterator.done(); ++iterator )									
    {			
		    // Get the next record from the CATD file
        iterator.get( record );

		    pCatDEntry = new sb_CatalogDir( record );

        // Get the name of the entry
        strCatDEntryName = pCatDEntry->getName().c_str();
        strCatDEntryName.TrimRight();

        // Check for an XRef module
        if ( 0 == strCatDEntryName.CompareNoCase( "XREF" ) )
        {
            d_strXRefFilename = pCatDEntry->getFile().c_str();
        }
        // Check for an Internal Spatial Reference module
        else if ( 0 == strCatDEntryName.CompareNoCase( "IREF" ) )
        {
            d_strIntRefFilename = pCatDEntry->getFile().c_str();
        }
        // Check for an identification module
        else if ( 0 == strCatDEntryName.CompareNoCase( "IDEN" ) )
        {
            d_strIdentFilename = pCatDEntry->getFile().c_str();
        }
        // Check for appropriate line modules
        else if ( 0 == strCatDEntryName.CompareNoCase( "LE" + d_strAGOB ) )
        {
            d_strLinesFilename = pCatDEntry->getFile().c_str();
        }
        // Check for appropriate NP modules
        else if ( 0 == strCatDEntryName.CompareNoCase( "NP" + d_strAGOB ) )
        {
            d_strNPFilename = pCatDEntry->getFile().c_str();
        }
        // Check for appropriate planar node modules
        else if ( 0 == strCatDEntryName.CompareNoCase( "NO" + d_strAGOB ) )
        {
            d_strNodesFilename = pCatDEntry->getFile().c_str();
        }
        // Check for the transfer stats file
        else if ( 0 == strCatDEntryName.CompareNoCase( "STAT" ) )
        {
            d_strTransferStatsFilename = pCatDEntry->getFile().c_str();
        }
        // Check for degenerate lines (entity points) filename
        else if ( 0 == strCatDEntryName.CompareNoCase( "NE" + d_strAGOB ) )
        {
            d_strDegLinesFilename = pCatDEntry->getFile().c_str();
        }
        // Check for areas filename
        else if ( 0 == strCatDEntryName.CompareNoCase( "NA" + d_strAGOB ) )
        {
            d_strAreasFilename = pCatDEntry->getFile().c_str();
        }
        // Check for polygon filename
        else if ( 0 == strCatDEntryName.CompareNoCase( "PC" + d_strAGOB ) )
        {
            d_strPolygonFilename = pCatDEntry->getFile().c_str();
        }
        // Check for spatial domain filename
        else if ( 0 == strCatDEntryName.CompareNoCase( "SPDM" ) )
        {
            d_strSpatialDomFilename = pCatDEntry->getFile().c_str();
        }
        // Check for the attribute primary header module
        else if ( 0 == strCatDEntryName.CompareNoCase( "AHDR" ) )
        {
            d_strAHDRFilename = pCatDEntry->getFile().c_str();
        }
        // Check for the FF01 module
        else if ( 0 == strCatDEntryName.CompareNoCase( "FF01" ) )
        {
            d_strFF01Filename = pCatDEntry->getFile().c_str();
        }
        // Check for data quality modules
        else if ( 0 == strCatDEntryName.CompareNoCase( "DQAA" ) )
        {
            d_strDQAAFilename = pCatDEntry->getFile().c_str();
        }
        else if ( 0 == strCatDEntryName.CompareNoCase( "DQCG" ) )
        {
            d_strDQCGFilename = pCatDEntry->getFile().c_str();
        }
        else if ( 0 == strCatDEntryName.CompareNoCase( "DQHL" ) )
        {
            d_strDQHLFilename = pCatDEntry->getFile().c_str();
        }
        else if ( 0 == strCatDEntryName.CompareNoCase( "DQLC" ) )
        {
            d_strDQLCFilename = pCatDEntry->getFile().c_str();
        }
        else if ( 0 == strCatDEntryName.CompareNoCase( "DQPA" ) )
        {
            d_strDQPAFilename = pCatDEntry->getFile().c_str();
        }
        else if ( 0 == strCatDEntryName.CompareNoCase( "MDEF" ) )
        {
            // Get the module version
            d_moduleVersion = atof( pCatDEntry->getModuleVer().c_str() );
        }
        // Check for the attribute modules
        else
        {
            CString strCatDEntryType = pCatDEntry->getType().c_str();
            strCatDEntryType.TrimRight();

            // If this is an attribute module, check through the list
            // of module names to look for
            if ( 0 == strCatDEntryType.CompareNoCase( "Attribute Primary" ) || 
                 0 == strCatDEntryType.CompareNoCase( "Attribute Secondary" ) )
            {
                // If the theme type was recognized, just complete the entries in
                // the list of attribute map records, otherwise add a new record
                // to the list of attribute map records
                if ( !d_bUnknownTheme )
                {
                    for ( list<AttMapRecord*>::iterator i = d_attModuleMap.begin();
                          i != d_attModuleMap.end(); i++ )
                    {
                        if ( 0 == (*i)->d_strName.CompareNoCase( strCatDEntryName ) )
                        {
                            // Yippee! We found a match!
                            (*i)->d_strFilename = pCatDEntry->getFile().c_str();
                            break;
                        }
                    }
                }
                else
                {
                    AttMapRecord* pAMR = new AttMapRecord( strCatDEntryName );
                    pAMR->d_strFilename = pCatDEntry->getFile().c_str();
                    d_attModuleMap.push_back( pAMR );
                }
            }
        }
        
		delete pCatDEntry;					
	}

    ddf.close();

    return true;
}

bool
SDTSDLGOverlay::loadAttributeHeaderModule( void )
{
    // Search through the FF01 module to find out which record in the AHDR
    // module pertains to this overlay
    d_ahdrRecordNum = getAHDRRecordNum();

    d_pAttHeaderThread = AfxBeginThread( loadAttHeaderThreadFunc, (LPVOID)this );

    return ( NULL != d_pAttHeaderThread );
}

bool
SDTSDLGOverlay::loadAttributeModules( void )
{
    d_pAttModuleThread = AfxBeginThread( loadAttModulesThreadFunc, (LPVOID)this );

    return ( NULL != d_pAttModuleThread );
}

bool
SDTSDLGOverlay::loadDataQualityModules( void )
{
    d_pDataQualityThread = AfxBeginThread( loadDataQualityThreadFunc, (LPVOID)this );

    return ( NULL != d_pDataQualityThread );
}

bool
SDTSDLGOverlay::loadDQAA( void )
{
    ifstream ddf( d_strPath + d_strDQAAFilename, ios::binary );

	  if ( !ddf )
    {
        return false;
    }

    sio_8211Reader	reader( ddf );				
	  sc_Record		record;
    sio_8211ForwardIterator iterator( reader );

    // Get the DQAA record
    iterator.get( record );

    // Create a DQAA object based on the record
    d_pDQAA = new sb_AttAccuracy( record );

    ddf.close();

    return true;
}
                
bool
SDTSDLGOverlay::loadDQCG( void )
{
    ifstream ddf( d_strPath + d_strDQCGFilename, ios::binary );

	  if ( !ddf )
    {
        return false;
    }

    sio_8211Reader	reader( ddf );				
	  sc_Record		record;
    sio_8211ForwardIterator iterator( reader );

    // Get the DQCG record
    iterator.get( record );

    // Create a DQCG object based on the record
    d_pDQCG = new sb_Completeness( record );

    ddf.close();

    return true;
}

bool
SDTSDLGOverlay::loadDQHL( void )
{
    ifstream ddf( d_strPath + d_strDQHLFilename, ios::binary );

	  if ( !ddf )
    {
        return false;
    }

    sio_8211Reader	reader( ddf );				
	  sc_Record		record;
    sio_8211ForwardIterator iterator( reader );

    // Get the DQHL record
    iterator.get( record );

    // Create a DQHL object based on the record
    d_pDQHL = new sb_Lineage( record );

    ddf.close();

    return true;
}

bool
SDTSDLGOverlay::loadDQLC( void )
{
    ifstream ddf( d_strPath + d_strDQLCFilename, ios::binary );

	  if ( !ddf )
    {
        return false;
    }

    sio_8211Reader	reader( ddf );				
	  sc_Record		record;
    sio_8211ForwardIterator iterator( reader );

    // Get the DQLC record
    iterator.get( record );

    // Create a DQLC object based on the record
    d_pDQLC = new sb_LogicalConsis( record );

    ddf.close();

    return true;
}

bool
SDTSDLGOverlay::loadDQPA( void )
{
    ifstream ddf( d_strPath + d_strDQPAFilename, ios::binary );

	  if ( !ddf )
    {
        return false;
    }

    sio_8211Reader	reader( ddf );				
	  sc_Record		record;
    sio_8211ForwardIterator iterator( reader );

    // Get the DQPA record
    iterator.get( record );

    // Create a DQPA object based on the record
    d_pDQPA = new sb_PosAccuracy( record );

    ddf.close();

    return true;
}

bool
SDTSDLGOverlay::loadExternalRef( void )
{
    ifstream ddf( d_strPath + d_strXRefFilename, ios::binary );

	  if ( !ddf )
    {
        return false;
    }

    sio_8211Reader	reader( ddf );				
	  sc_Record		record;
    sio_8211ForwardIterator iterator( reader );

    // Get the external ref record
    iterator.get( record );

    // Create an External Spatial Ref object based on the record
    d_pExternalRef = new sb_ExtSpatialRef( record );

    ddf.close();

    return true;
}

bool
SDTSDLGOverlay::loadInternalRef( void )
{
    ifstream ddf( d_strPath + d_strIntRefFilename, ios::binary );

	  if ( !ddf )
    {
        return false;
    }

    sio_8211Reader	reader( ddf );				
	  sc_Record		record;
    sio_8211ForwardIterator iterator( reader );

    // Get the external ref record
    iterator.get( record );

    // Create an External Spatial Ref object based on the record
    d_pInternalRef = new sb_IntSpatialRef( record );

    ddf.close();

    return true;
}

bool
SDTSDLGOverlay::loadIdent( void )
{
    ifstream ddf( d_strPath + d_strIdentFilename, ios::binary );

	  if ( !ddf )
    {
        return false;
    }

    sio_8211Reader	reader( ddf );				
	  sc_Record		record;
    sio_8211ForwardIterator iterator( reader );

    // Get the external ref record
    iterator.get( record );

    // Create an External Spatial Ref object based on the record
    d_pIdent = new sb_Ident( record );

    ddf.close();

    return true;
}

// Get the control points from the NP file (if this isn't a 1:2M DLG)
bool 
SDTSDLGOverlay::loadControlPoints( void )
{
    ASSERT( NULL != d_pIdent );

    // If this is a 1:2M DLG, get control points from the spatial
    // domain file, otherwise get them from the NP file
    if ( (100000 != d_pIdent->getScale()) && (24000 != d_pIdent->getScale()) 
          && (d_pIdent->getScale() != 25000) && (d_pIdent->getScale() != 20000)
          && (d_pIdent->getScale() != 30000) && (d_pIdent->getScale() != 63360) )
    {
        ifstream ddf( d_strPath + d_strSpatialDomFilename, ios::binary );

	      if ( !ddf )
        {
            return false;
        }

        // Create converters for the reader
        // sio_Converter_BI32 bi32_converter;
        sio_8211Converter_BI32 bi32_converter;
        //map <string, sio_Converter*> mapConverters;
        map <string, sio_8211Converter*> mapConverters;
        mapConverters["X"] = &bi32_converter;
        mapConverters["Y"] = &bi32_converter;

        sio_8211Reader	reader( ddf, &mapConverters );				
	      sc_Record		record;
        sio_8211ForwardIterator i( reader );

        // Get the spatial domain record
        i.get( record );

        // Create an spatial domain object based on the record
        d_pSpatialDom = new sb_SpatialDom( record );

        ddf.close();
    }
    else
    {
        ifstream ddf( d_strPath + d_strNPFilename, ios::binary );

	      if ( !ddf )
        {
            return false;
        }

        // Create converters for the reader
        sio_8211Converter_BI32 bi32_converter;
        map <string, sio_8211Converter*> mapConverters;
        mapConverters["X"] = &bi32_converter;
        mapConverters["Y"] = &bi32_converter;

        sio_8211Reader	reader( ddf, &mapConverters );				
	      sc_Record		record;
        int j = 0;
        for ( sio_8211ForwardIterator i( reader ); 
              !i.done() && j < 4; ++i, j++ )
        {
            // Get the point node record
            i.get( record );

            // Create an Point-Node object based on the record
            d_pControlPoints[j] = new sb_PointNode( record );
        }

        ddf.close();
    }

    return true;
}

bool
SDTSDLGOverlay::loadTransferStats( void )
{
    ifstream ddf( d_strPath + d_strTransferStatsFilename, ios::binary );

  	if ( !ddf )
    {
        return false;
    }

    try
    {
        sio_8211Reader	reader( ddf );				
	      sc_Record		record;
        sb_TransferStats* pStats = NULL;
        CString strModuleName;
        for ( sio_8211ForwardIterator i( reader ); !i.done(); ++i )
        {
            // Get the transfer stats record
            i.get( record );

            // Create a transfer stats object based on the record
            pStats = new sb_TransferStats( record );

            // Get the name of the module referred to
            strModuleName = pStats->getModuleNameReferred().c_str();

            // Check for appropriate line record
            if ( 0 == strModuleName.CompareNoCase( "LE" + d_strAGOB ) )
            {
                d_numLines = pStats->getModuleRecCount();
            }
            // Check for appropriate node record
            else if ( 0 == strModuleName.CompareNoCase( "NO" + d_strAGOB ) )
            {
                d_numNodes = pStats->getModuleRecCount();
            }
            // Check for appropiate degenerate line (entity point) record
            else if ( 0 == strModuleName.CompareNoCase( "NE" + d_strAGOB ) )
            {
                d_numDegLines = pStats->getModuleRecCount();
            }
            // Check for appropriate area record
            else if ( 0 == strModuleName.CompareNoCase( "NA" + d_strAGOB ) )
            {
                d_numAreas = pStats->getModuleRecCount();
            }
            // Check for appropriate polygon record
            else if ( 0 == strModuleName.CompareNoCase( "PC" + d_strAGOB ) )
            {
                d_numPolygons = pStats->getModuleRecCount();
            }
            // TODO -check for other stuff

            delete pStats;
        }
    }
    catch ( ... )
    {
    }

    ddf.close();

    return true;

}

bool
SDTSDLGOverlay::readAreas( CLoadingDialog& dlgLoading )
{
    // Create an input stream based on the area file name
    ifstream ddf( d_strPath + d_strAreasFilename, ios::binary );

  	// Abort load if failed to open stream
	  if ( !ddf )
	  {
		  return false;
	  }

    // Determine the convertor type
    sio_8211Converter* pConverter = NULL;
    if ( d_pInternalRef->getHorizontalCompFmt() == "BI32" )
    {
        pConverter = new sio_8211Converter_BI32;
    }
    else if ( d_pInternalRef->getHorizontalCompFmt() == "BFP64" )
    {
        pConverter = new sio_8211Converter_BFP64;
    }
    else
    {
        ddf.close();
        return false;
    }

    // Create converters for the reader
    map <string, sio_8211Converter*> mapConverters;
    mapConverters["X"] = pConverter;
    mapConverters["Y"] = pConverter;

    // Create a reader for reading in the area records
    sio_8211Reader reader( ddf, &mapConverters );

    // Read in the area records
    SDTSDLGPointGraphic* pArea = NULL;
    sc_Record areaRecord;
    for ( sio_8211ForwardIterator i( reader ); !i.done(); ++i )
    {
        // Get the area record
        i.get( areaRecord );

        // Create a SDTS point graphic based on the area and add it to the area vector
        pArea = new SDTSDLGPointGraphic( this, areaRecord, getAreaShape() );
        d_pAreas.push_back( pArea );
        
        // Update loading dialog
        dlgLoading.d_progressControl.OffsetPos( 1 );
    }

    // Cleanup the converters
    delete pConverter;

    // Close the ddf stream
    ddf.close();

    return true;
}

bool
SDTSDLGOverlay::readDegLines( CLoadingDialog& dlgLoading )
{
    // Create an input stream based on the degenerate line file name
    ifstream ddf( d_strPath + d_strDegLinesFilename, ios::binary );

  	// Abort load if failed to open stream
  	if ( !ddf )
  	{
  		return false;
  	}

    // Determine the convertor type
    sio_8211Converter* pConverter = NULL;
    if ( d_pInternalRef->getHorizontalCompFmt() == "BI32" )
    {
        pConverter = new sio_8211Converter_BI32;
    }
    else if ( d_pInternalRef->getHorizontalCompFmt() == "BFP64" )
    {
        pConverter = new sio_8211Converter_BFP64;
    }
    else
    {
        ddf.close();
        return false;
    }

    // Create converters for the reader
    map <string, sio_8211Converter*> mapConverters;
    mapConverters["X"] = pConverter;
    mapConverters["Y"] = pConverter;

    // Create a reader for reading in the degenerate line records
    sio_8211Reader reader( ddf, &mapConverters );

    // Read in the degenerate line records
    SDTSDLGDegLineGraphic* pDegLine = NULL;
    sc_Record nodeRecord;
    for ( sio_8211ForwardIterator i( reader ); !i.done(); ++i )
    {
        // Get the degenerate line record
        i.get( nodeRecord );

        // Create a SDTS deg line graphic based on the node and add it to the line vector
        pDegLine = new SDTSDLGDegLineGraphic( this, nodeRecord );
        d_pLines.push_back( pDegLine );
        
        // Update loading dialog
        dlgLoading.d_progressControl.OffsetPos( 1 );
    }

    // Cleanup the converters
    delete pConverter;

    // Close the ddf stream
    ddf.close();

    return true;
}

bool
SDTSDLGOverlay::readLines( CLoadingDialog& dlgLoading )
{
    // Create an input stream based on the line file name
    ifstream ddf( d_strPath + d_strLinesFilename, ios::binary );

  	// Abort load if failed to open stream
  	if ( !ddf )
  	{
  		return false;
  	}

    // Determine the convertor type
    sio_8211Converter* pConverter = NULL;
    if ( d_pInternalRef->getHorizontalCompFmt() == "BI32" )
    {
        pConverter = new sio_8211Converter_BI32;
    }
    else if ( d_pInternalRef->getHorizontalCompFmt() == "BFP64" )
    {
        pConverter = new sio_8211Converter_BFP64;
    }
    else
    {
        ddf.close();
        return false;
    }

    // Create converters for the reader
    map <string, sio_8211Converter*> mapConverters;
    mapConverters["X"] = pConverter;
    mapConverters["Y"] = pConverter;

    // Create a reader for reading in the line records
    sio_8211Reader reader( ddf, &mapConverters );

    // Read in the line records
    SDTSDLGPolylineGraphic* pPolyline = NULL;
    sc_Record lineRecord;
    for ( sio_8211ForwardIterator i( reader ); !i.done(); ++i )
    {
        // Get the line record
        i.get( lineRecord );

        // Create a SDTS polyline based on the line and add it to the line vector
        pPolyline = new SDTSDLGPolylineGraphic( this, lineRecord );
        d_pLines.push_back( pPolyline );

        // Update loading dialog
        dlgLoading.d_progressControl.OffsetPos( 1 );
    }

    // Cleanup the converter
    delete pConverter;

    // Close the ddf stream
    ddf.close();

    return true;
}

bool
SDTSDLGOverlay::readNodes( CLoadingDialog& dlgLoading )
{
    // Create an input stream based on the node file name
    ifstream ddf( d_strPath + d_strNodesFilename, ios::binary );

  	// Abort load if failed to open stream
  	if ( !ddf )
  	{
	  	return false;
	  }

    // Determine the convertor type
    sio_8211Converter* pConverter = NULL;
    if ( d_pInternalRef->getHorizontalCompFmt() == "BI32" )
    {
        pConverter = new sio_8211Converter_BI32;
    }
    else if ( d_pInternalRef->getHorizontalCompFmt() == "BFP64" )
    {
        pConverter = new sio_8211Converter_BFP64;
    }
    else
    {
        ddf.close();
        return false;
    }

    // Create converters for the reader
    map <string, sio_8211Converter*> mapConverters;
    mapConverters["X"] = pConverter;
    mapConverters["Y"] = pConverter;

    // Create a reader for reading in the node records
    sio_8211Reader reader( ddf, &mapConverters );

    // Read in the node records
    SDTSDLGPointGraphic* pNode = NULL;
    sc_Record nodeRecord;
    for ( sio_8211ForwardIterator i( reader ); !i.done(); ++i )
    {
        // Get the node record
        i.get( nodeRecord );

        // Create a SDTS point graphic based on the node and add it to the node vector
        pNode = new SDTSDLGPointGraphic( this, nodeRecord, getNodeShape() );
        d_pNodes.push_back( pNode );
        
        // Update loading dialog
        dlgLoading.d_progressControl.OffsetPos( 1 );
    }

    // Cleanup the converter
    delete pConverter;

    // Close the ddf stream
    ddf.close();

    return true;
}

bool
SDTSDLGOverlay::readPolygons( CLoadingDialog& dlgLoading )
{
    // Create an input stream based on the node file name
    ifstream ddf( d_strPath + d_strPolygonFilename, ios::binary );

  	// Abort load if failed to open stream
  	if ( !ddf )
  	{
  		return false;
  	}

    // Create a reader for reading in the polygon records
    sio_8211Reader reader( ddf );

    // Read in the polygon records
    sc_Record polygonRecord;
    for ( sio_8211ForwardIterator i( reader ); !i.done(); ++i )
    {
        // Get the polygon record
        i.get( polygonRecord );

        // Create a polygon and add it to the polygon vector
        d_pPolygons.push_back( new sb_Polygon( polygonRecord ) );
        
        // Update loading dialog
        dlgLoading.d_progressControl.OffsetPos( 1 );
    }

    // Close the ddf stream
    ddf.close();

    return true;
}

void 
SDTSDLGOverlay::showPropertiesDialog()
{
    // Create the dialog if necessary
    if ( NULL == d_pPropertySheet )
    {
        d_pPropertySheet = new SDTSDLG_PropSheet( 
                                (LPCTSTR)(getDescription() + " Metadata"), 
                                d_pIdent, getNativeProjection()->toString().c_str(),
                                d_numAreas, d_numNodes, d_numDegLines, d_numLines,
                                d_numPolygons, &d_pDQAA, &d_pDQCG, &d_pDQHL, &d_pDQLC, &d_pDQPA,
                                &d_pAHDRModule, d_ahdrRecordNum );
        d_pPropertySheet->Create( AfxGetMainWnd() );
    }

    // Show the dialog
    d_pPropertySheet->ShowWindow( SW_SHOWNORMAL );
}

void 
SDTSDLGOverlay::calculateBoundingRect()
{
    ASSERT( d_loaded );
    ASSERT( d_pIdent );

	  double min_x, min_y, max_x, max_y;
	  double x, y;

    // Calculate the bounding rectangle using the control points if this
    // isn't a 1:2M DLG, if it is a 1:2M DLG use the Spatial domain info
    if ( (100000 == d_pIdent->getScale()) || (24000 == d_pIdent->getScale()) 
         || (d_pIdent->getScale() == 25000) || (d_pIdent->getScale() == 20000)
         || (d_pIdent->getScale() == 30000) || (d_pIdent->getScale() == 63360) )
    {
        ASSERT( d_pControlPoints[0] && d_pControlPoints[1] && 
                d_pControlPoints[2] && d_pControlPoints[3] );

        for ( int n = 0; n < 4; n++ )
	    {
            // Get the coordinates in the point
            const vector<sb_SpatialAddr>& vecPoint = d_pControlPoints[n]->getSpatialAddrs();
            vector<sb_SpatialAddr>::const_iterator i = vecPoint.begin();
            i->getXY( x, y );
            convertPoint( x, y );    

		    // If at the first control point, initialize variables
		    if ( n == 0 )
		    {
			    min_x = max_x = x;
			    min_y = max_y = y;
		    }
		    else
		    {
			    if ( x < min_x )
			    {
				    min_x = x;
			    }
			    else if ( x > max_x )
			    {
				    max_x = x;
			    }

			    if ( y < min_y )
			    {
				    min_y = y;
			    }
			    else if ( y > max_y )
			    {
				    max_y = y;
			    }
		    }
	    }
    }
    else
    {
        ASSERT( d_pSpatialDom );

        // Get the coordinates in the point
        const vector<sb_SpatialAddr>& vecPoint = d_pSpatialDom->getDomSpatialAddrs();
        vector<sb_SpatialAddr>::const_iterator i = vecPoint.begin();

        for ( ; i != vecPoint.end(); i++ )
        {
            i->getXY( x, y );
            convertPoint( x, y );    

            // First point is minimum, second is max
            if ( vecPoint.begin() == i )
            {
                min_x = x;
                min_y = y;
            }
            else
            {
                max_x = x;
                max_y = y;
            }
        }
    }

	d_boundingRect.setPoints( min_x, min_y, max_x, max_y );

    // Expand the bounding rectangle by 1% to account for the pen width
    d_boundingRect.inflateRect( d_boundingRect.width() / 100 );

    // Call base class version to ensure that all components calculate their
    // bounding rectangles
    DLGOverlay::calculateBoundingRect();
}

PROJSYS
SDTSDLGOverlay::getGndRefSys( void )
{
    CString strRefSys = d_pExternalRef->getRefSysName().c_str();

    if ( 0 == strRefSys.CompareNoCase( "UTM" ) )
    {
        return UTM;
    }
    else if ( 0 == strRefSys.CompareNoCase( "GEO" ) )
    {
        return GEO;
    }
    else 
    {
        return UNKNOWN_PROJSYS;
    }
}

DATUM
SDTSDLGOverlay::getHorizDatum( void )
{
    CString strHorizDatum = d_pExternalRef->getHorizDatum().c_str();

    if ( 0 == strHorizDatum.CompareNoCase( "NAS" ) )
    {
        return NAD27;
    }
    else if ( 0 == strHorizDatum.CompareNoCase( "NAX" ) )
    {
        return NAD83;
    }
    else if ( 0 == strHorizDatum.CompareNoCase( "Puerto Rico" ) )
    {
        return PUERTO_RICO;
    }
    else if ( 0 == strHorizDatum.CompareNoCase( "Old Hawaiian" ) )
    {
        return OLD_HAWAIIAN_MEAN;
    }
    else
    {
        return UNKNOWN_DATUM;
    }
}

long
SDTSDLGOverlay::getZone( void )
{
    return atol( d_pExternalRef->getZoneNum().c_str() );
}

void
SDTSDLGOverlay::convertPoint( double& x, double& y )
{
    ASSERT( d_pInternalRef != NULL );
    x = d_pInternalRef->getScaleFactX() * x + d_pInternalRef->getXOrigin();
    y = d_pInternalRef->getScaleFactY() * y + d_pInternalRef->getYOrigin();
}

void 
SDTSDLGOverlay::getAttLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs,
                                       const CString& strModuleName, UINT index ) const
{
    // Find the module corresponding to the module name
    SDTS_AttModule* pModule = NULL;
    if ( !getModuleFromName( strModuleName, &pModule ) )
    {
        return;
    }

    if ( NULL == pModule )
    {
        // If the attribute primary module isn't loaded, return an empty string
        return;
    }

    // Get the record
    SDTS_AttRecord* pRecord = pModule->getRecord( index );

    // Make sure the record was successfully retrieved
    if ( NULL == pRecord )
    {
        return;
    }

    // Get the label-value pairs from the record
    pRecord->getLabelValuePairs( pairs );

    // Get the records foreign key reference fields
    getAttForeignKeys( pRecord, pairs );
}

const string&
SDTSDLGOverlay::getEntityDesc( const vector<SDTSAtt_LabelValuePair>& pairs ) const
{
    static string strNotEntMessage = "Not an Entity";

    // If no MDEF module is loaded just return a status string
    if ( NULL == d_pMDEFModule )
    {
        return d_strMDEFStatus;
    }

    // Search through the att-value pairs for the ENTITY_LABEL pair
    for ( vector<SDTSAtt_LabelValuePair>::const_iterator i = pairs.begin();
          i != pairs.end(); i++ )
    {
        if ( "ENTITY_LABEL" == i->getLabel() )
        {
            return d_pMDEFModule->getEntityDesc( i->getValue() );
        }
    }
         
    // No entity label field found
    return strNotEntMessage;
}

void    
SDTSDLGOverlay::getAttForeignKeys( SDTS_AttRecord* pRecord, 
                                   vector<SDTSAtt_LabelValuePair>& pairs ) const
{
    // Get the foreign key reference info
    vector<SDTS_AttReferenceInfo> attRefInfo;
    pRecord->getAttReferenceInfo( attRefInfo );

    // Get the label-value pairs for each foreign key reference
    for ( vector<SDTS_AttReferenceInfo>::iterator i = attRefInfo.begin(); i != attRefInfo.end(); i++ )
    {
        // Find the module corresponding to the module name
        SDTS_AttModule* pModule = NULL;
        if ( !getModuleFromName( i->getModuleName().c_str(), &pModule ) )
        {
            continue;
        }

        if ( NULL == pModule )
        {
       	    // Show a status bar message saying that we are waiting for the
            // attribute primary module to finish loading
    	    CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
    	    MCStatusBar* pStatusBar = pMainFrame->GetStatusBar();
            pStatusBar->SetPaneText( 0, "Waiting for Attribute Module to Load..." );
            pStatusBar->UpdateWindow();

            // Wait on the loading thread for 1 second
            ::WaitForSingleObject( d_pAttModuleThread->m_hThread, 1000 );

            // If the attribute primary module still isn't loaded, return an
            // empty string
            if ( NULL == pModule )
            {
                // Show timed out message on status bar
                pStatusBar->SetPaneText( 0, "Timeout waiting for attribute module to load" );
                pStatusBar->UpdateWindow();
                return;
            }
            else
            {
                // Clear status bar
                pStatusBar->SetPaneText( 0, "" );
            }
        }

        // Get the label value pairs from the module
        pModule->getLabelValuePairsByFK( pairs, i->getForeignKeys() );
    }
}

void 
SDTSDLGOverlay::getPolygonAttLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs,
                                              UINT rcid ) const
{
    for ( vector<sb_Polygon*>::const_iterator i = d_pPolygons.begin();
          i != d_pPolygons.end(); i++ )
    {
        // See if this is the polygon we're looking for
        if ( rcid == (*i)->getRecordID() )
        {
            // This is it, get the module name and record number of the attribute
            const sb_ForeignID& attID = (*i)->getAttributeID();
            getAttLabelValuePairs( pairs, attID.getModuleName().c_str(), attID.getRecordID() );
            return;
        }
    }
}

int
SDTSDLGOverlay::getAHDRRecordNum( void )
{
    // Open the FF01 module
    ifstream ddf( d_strPath + d_strFF01Filename, ios::binary );

	if ( !ddf )
    {
        return false;
    }

    // Set the search string to be "LE" plus the AGOB
    string strSearch = "LE";
    strSearch += d_strAGOB;

    // Read in the FF01 Composite records until we find a match
    sio_8211Reader reader( ddf );				
    sb_Composite*  pComposite = NULL;
	sc_Record	   record;
    for ( sio_8211ForwardIterator i( reader ); !i.done(); ++i )
    {
        // Get the line record
        i.get( record );

        // Create a composite record based on the record
        pComposite = new sb_Composite( record );        
        
        // Get the foreign ID's of the composite record
        const vector<sb_ForeignID>& fIDs = pComposite->getForeignID();

        // Look through the foreign ID's for a match
        for ( vector<sb_ForeignID>::const_iterator j = fIDs.begin(); j != fIDs.end(); j++ )
        {
            if ( j->getModuleName() == strSearch )
            {
                // We found a match, return the record number
                int retVal = pComposite->getAttributeID().getRecordID();
                delete pComposite;
                ddf.close();
                return retVal;
            }
        }

        // Delete the composite record
        delete pComposite;
    }

    // Close the ddf stream
    ddf.close();

    // If we got here we didn't find anything, return -1
    return -1;
}

UINT 
SDTSDLGOverlay::loadAttHeaderThreadFunc( LPVOID pParam )
{
    ASSERT( NULL != pParam );

    // pParam should be a pointer to the class instance
    SDTSDLGOverlay* pInstance = (SDTSDLGOverlay*)pParam;

    // Add a reference to the AHDR attribute module
    CString strFullPath = pInstance->d_strPath + pInstance->d_strAHDRFilename;
    pInstance->d_pAHDRModule = SDTS_AttModuleFactory::AddRef( (LPCSTR)( strFullPath ), "AHDR" );

    return 0;
}

UINT
SDTSDLGOverlay::loadAttModulesThreadFunc( LPVOID pParam )
{
    ASSERT( NULL != pParam );

    // pParam should be a pointer to the class instance
    SDTSDLGOverlay* pInstance = (SDTSDLGOverlay*)pParam;

    // Set the default status string
    pInstance->d_strMDEFStatus = "Some or all of the attribute modules are not finished loading.  "
                                 "Click the right mouse button to retry";
    
    // Load each attribute module
    for ( list<AttMapRecord*>::iterator i = pInstance->d_attModuleMap.begin();
          i != pInstance->d_attModuleMap.end() && !pInstance->d_bDestroying; i++ )
    {    
        // An attribute primary module should not already have been created
        ASSERT( NULL == (*i)->d_pModule );

        // If there is no filename for this attribute type, skip it
        if ( (*i)->d_strFilename.IsEmpty() )
        {
            continue;
        }
    
        // Create an attribute module
        SDTS_AttModule* pTemp = NULL;

        // Get the module from the module factory
        CString strFullPath = pInstance->d_strPath + (*i)->d_strFilename;
        strFullPath.MakeUpper();
        pTemp = SDTS_AttModuleFactory::AddRef( (LPCTSTR)strFullPath,
                                               (LPCTSTR)( (*i)->d_strName ) );
        if ( NULL != pTemp )
        {
            (*i)->d_pModule = pTemp;
        }
        else
        {
            delete pTemp;
            AfxMessageBox( "Error loading attribute module.  Some or all of the entity information "
                           "may not be available." );
        }
    }

    // Make sure the user didn't decide to stop loading before we get here
    if ( pInstance->d_bDestroying )
    {
        return 0;
    }

    // Get the Master Data Definition file for this scale
    pInstance->d_pMDEFModule = SDTS_MDEFFactory::AddRef( pInstance->d_pIdent->getScale(), 
                                                         pInstance->d_moduleVersion );
    if ( NULL == pInstance->d_pMDEFModule )
    {
        pInstance->d_strMDEFStatus = "Error loading MDEF module, entity descriptions will not be available.";
    }
    else
    {
        pInstance->d_strMDEFStatus = "MDEF Module Successfully Loaded";
    }

    return 0;
}

UINT
SDTSDLGOverlay::loadDataQualityThreadFunc( LPVOID pParam )
{
    ASSERT( NULL != pParam );
    
    // pParam should be a pointer to the class instance
    SDTSDLGOverlay* pInstance = (SDTSDLGOverlay*)pParam;

    // None of the Data quality builder objects should have been created yet
    ASSERT( !pInstance->d_pDQAA && !pInstance->d_pDQCG && !pInstance->d_pDQHL &&
            !pInstance->d_pDQLC && !pInstance->d_pDQPA );

    // Load each of the data quality modules
    pInstance->loadDQAA();
    pInstance->loadDQCG();
    pInstance->loadDQHL();
    pInstance->loadDQLC();
    pInstance->loadDQPA();

    return 0;
}

void    
SDTSDLGOverlay::getAttModuleNameFromTheme( void )
{
    // NOTE: I explicitly add the names of the attribute module rather than
    // just reading them from the CATD module because one transfer may include
    // multiple layers that reference difference attribute modules.  If the
    // user just wants to open the railroads layer of a transportation transfer
    // there's no reason to load the attribute modules for the roads and pipelines
    // layers too.

    CString strLeft = d_strTheme.Left(4);
    strLeft.TrimRight();

    // Determine the attribute primary module name based on the leftmost
    // four characters of the theme name
    if ( 0 == strLeft.CompareNoCase( "BOUN" ) )
    {
        d_attModuleMap.push_back( new AttMapRecord( "ABDF" ) );
        d_attModuleMap.push_back( new AttMapRecord( "ABDM" ) );
        d_attModuleMap.push_back( new AttMapRecord( "BFPC" ) );
        d_attModuleMap.push_back( new AttMapRecord( "BFPS" ) );
    }
    else if ( 0 == strLeft.CompareNoCase( "HYPS" ) )
    {
        d_attModuleMap.push_back( new AttMapRecord( "AHPF" ) );
        d_attModuleMap.push_back( new AttMapRecord( "AHPR" ) );
        d_attModuleMap.push_back( new AttMapRecord( "AHPT" ) );
    }
    else if ( 0 == strLeft.CompareNoCase( "HYDR" ) )
    {
        d_attModuleMap.push_back( new AttMapRecord( "AHYF" ) );
    }
    else if ( 0 == strLeft.CompareNoCase( "MANM" ) )
    {
        d_attModuleMap.push_back( new AttMapRecord( "AMSF" ) );
        d_attModuleMap.push_back( new AttMapRecord( "BMSP" ) );
        d_attModuleMap.push_back( new AttMapRecord( "BFPC" ) );
        d_attModuleMap.push_back( new AttMapRecord( "BFPS" ) );
    }
    else if ( 0 == strLeft.CompareNoCase( "PIPE" ) )
    {
        d_attModuleMap.push_back( new AttMapRecord( "AMTF" ) );
        d_attModuleMap.push_back( new AttMapRecord( "BMTA" ) );
        d_attModuleMap.push_back( new AttMapRecord( "BFPS" ) );
    }
    else if ( 0 == strLeft.CompareNoCase( "NON-" ) )
    {
        d_attModuleMap.push_back( new AttMapRecord( "ANVF" ) );
    }
    else if ( 0 == strLeft.CompareNoCase( "PUBL" ) )
    {
        d_attModuleMap.push_back( new AttMapRecord( "APLF" ) );
        d_attModuleMap.push_back( new AttMapRecord( "BGRL" ) );
    }
    else if ( 0 == strLeft.CompareNoCase( "ROAD" ) )
    {
        d_attModuleMap.push_back( new AttMapRecord( "ARDF" ) );
        d_attModuleMap.push_back( new AttMapRecord( "ARDM" ) );
        d_attModuleMap.push_back( new AttMapRecord( "BMTA" ) );
        d_attModuleMap.push_back( new AttMapRecord( "BFPS" ) );
    }
    else if ( 0 == strLeft.CompareNoCase( "RAIL" ) )
    {
        d_attModuleMap.push_back( new AttMapRecord( "ARRF" ) );
        d_attModuleMap.push_back( new AttMapRecord( "BMTA" ) );
        d_attModuleMap.push_back( new AttMapRecord( "BFPS" ) );
    }
    else if ( 0 == strLeft.CompareNoCase( "SURV" ) )
    {
        // XXX - This was documented as ABDF in the DLG3->SDTS document, but
        //       that must be a typo
        d_attModuleMap.push_back( new AttMapRecord( "ASMF" ) );
    }
    else if ( 0 == strLeft.CompareNoCase( "VEG" ) )
    {
        d_attModuleMap.push_back( new AttMapRecord( "ASCF" ) );
    }
    else
    {
        // The theme for this transfer is unknown
        d_bUnknownTheme = true;
    }

    // All types have a coincident module
    d_attModuleMap.push_back( new AttMapRecord( "ACOI" ) );
}

bool 
SDTSDLGOverlay::getModuleFromName( const CString& strName, SDTS_AttModule** ppModule ) const
{
    // Search through the list of attribute modules, looking for the module name. If it
    // is found, set the module pointer and return true.  If not, return FALSE
	list<AttMapRecord*> foo1 = d_attModuleMap;
    for ( list<AttMapRecord*>::iterator i = /*d_attModuleMap*/foo1.begin();
          i != /*d_attModuleMap*/foo1.end(); i++ )
    {
        if ( 0 == (*i)->d_strName.CompareNoCase( strName ) )
        {
            *ppModule = (*i)->d_pModule;
            return true;
        }
    }

    // Not found
    *ppModule = NULL;
    return false;
}

bool
SDTSDLGOverlay::setupProjection()
{
    ASSERT( NULL == d_pProjection );

    DATUM d = getHorizDatum();
    PROJSYS projSys = getGndRefSys();
    long zone = getZone();

    // Create the projection
    switch( projSys )
    {
        case GEO:
            d_pProjection = new GeographicProjection( d, ARC_DEGREES );
            break;
        case UTM:
            d_pProjection = new UTMProjection( zone, d, METERS );
            break;
    }

    // Check for errors
    if ( NULL == d_pProjection )
    {
        AfxMessageBox( "Unable to create projection\nLoad will abort" );
        return false;
    }

    // Setup the global projection if one hasn't been setup yet
    if ( NULL == CoordinateTransforms::getProjection() )
    {
        CoordinateTransforms::setProjection( d_pProjection );
    }

    return true;
}