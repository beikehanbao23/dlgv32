// SDTSDEMOverlay.cpp - implementation of SDTSDEMOverlay class
//
// Developed by: Mike Childs
//      Started: 4/22/98

#include "SDTSDEMOverlay.h"
#include "CoordinateTransforms.h"
#include "LoadingDialog.h"
#include <stdlib.h>
#include <fstream>
using namespace std;

// SDTS includes
#include "sdtsxx/io/sio_Reader.h"
#include "sdtsxx/io/sio_8211Converter.h"
#include "sdtsxx/builder/sb_CatalogDir.hxx"
#include "sdtsxx/builder/sb_DataDictDom.hxx"
#include "sdtsxx/builder/sb_DataDictSchema.hxx"
#include "sdtsxx/builder/sb_ExtSpatialRef.hxx"
#include "sdtsxx/builder/sb_IntSpatialRef.hxx"
#include "sdtsxx/builder/sb_RasterDefn.hxx"
#include "sdtsxx/builder/sb_SpatialDom.hxx"
#include "sdtsxx/container/sc_Record.h"

// Projection includes
#include "ProjectionLib/GeographicProjection.h"
#include "ProjectionLib/StatePlaneProjection.h"
#include "ProjectionLib/UTMProjection.h"

// Construction
SDTSDEMOverlay::SDTSDEMOverlay( CString& strCATDFilename, const CString& strMap,
                                const CString& strPath )
: RasterOverlay(strCATDFilename),
  d_pDDSH(NULL), d_pIREF(NULL), d_pRSDF(NULL), d_pSPDM(NULL), d_pXREF(NULL),
  d_strMap(strMap), d_strPath(strPath), d_pDataGrid(NULL)
{
    // Build the description
    d_strDescription.Format( "<%s> %s", getFilenameWithoutPath(), strMap );
}

// Destruction
SDTSDEMOverlay::~SDTSDEMOverlay()
{
    // Reclaim space used by builder objects
    delete d_pDDSH;
    delete d_pIREF;
    delete d_pRSDF;
    delete d_pSPDM;
    delete d_pXREF;

    // Reclaim space used by data
    delete[] d_pDataGrid;
}

// Loading
BOOL
SDTSDEMOverlay::load()
{
    // Get the necessary file names from the CATD module
    if ( !processCATD() )
    {
        // Abort load
        AfxMessageBox( "Unable to read CATD module\nAborting load..." );
        return FALSE;
    }

    // Load the raster definition module
    if ( !loadRasterDef() )
    {
        // Abort load
        AfxMessageBox( "Unable to read RSDF module\nAborting load..." );
        return FALSE;
    }

    // Load the internal spatial reference module
    if ( !loadInternalRef() )
    {
        // Abort load
        AfxMessageBox( "Unable to read IREF module\nAborting load..." );
        return FALSE;
    }

    // Load the external spatial reference module
    if ( !loadExternalRef() )
    {
        // Abort load
        AfxMessageBox( "Unable to read XREF module\nAborting load..." );
        return FALSE;
    }

    // Load the DDOM module
    if ( !loadDDOM() )
    {
        // Abort load
        AfxMessageBox( "Unable to read DDOM module\nAborting load..." );
        return FALSE;
    }

    // Load the DDSH module
    if ( !loadDDSH() )
    {
        // Abort load
        AfxMessageBox( "Unable to read DDSH module\nAborting load..." );
        return FALSE;
    }

    // Load the spatial domain module
    if ( !loadSpatialDomain() )
    {
        // Abort load
        AfxMessageBox( "Unable to read SPDM module\nAborting load..." );
        return FALSE;
    }

    // Read in the data
    if ( !readData() )
    {
        // Abort load
        AfxMessageBox( "Error reading data\nAborting Load..." );
        return FALSE;
    }
        
    // Setup the projection
    if ( !setupProjection() )
    {
        // Abort load
        return FALSE;
    }

    // Set the vertical units
    UNIT u = METERS;
    CString strVertUnits = d_pDDSH->getUnit().c_str();
    if ( 0 == strVertUnits.CompareNoCase( "FEET" ) )
    {
        u = US_FEET;
    }
    else if ( 0 == strVertUnits.CompareNoCase( "METERS" ) )
    {
        u = METERS;
    }
    setVerticalUnits( u );

    // Calculate the bounding rectangle
    calculateBoundingRect();

    // Setup the global projection changed stuff
    handleProjectionChanged();

    // Recalculate the global min/max values
    recalculateMinMaxSampleValue();

    d_loaded = TRUE;
    return TRUE;
}

// Extracts necessary filenames from CATD file
bool
SDTSDEMOverlay::processCATD( void )
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
      d_strXREFFilename = pCatDEntry->getFile().c_str();
    }
    // Check for an Internal Spatial Reference module
    else if ( 0 == strCatDEntryName.CompareNoCase( "IREF" ) )
    {
      d_strIREFFilename = pCatDEntry->getFile().c_str();
    }
    // Check for spatial domain filename
    else if ( 0 == strCatDEntryName.CompareNoCase( "SPDM" ) )
    {
      d_strSPDMFilename = pCatDEntry->getFile().c_str();
    }
    // Check for the DDOM module filename
    else if ( 0 == strCatDEntryName.CompareNoCase( "DDOM" ) )
    {
      d_strDDOMFilename = pCatDEntry->getFile().c_str();
    }
    // Check for the DDSH module filename
    else if ( 0 == strCatDEntryName.CompareNoCase( "DDSH" ) )
    {
      d_strDDSHFilename = pCatDEntry->getFile().c_str();
    }
    // Check for the RSDF module filename
    else if ( 0 == strCatDEntryName.CompareNoCase( "RSDF" ) )
    {
      d_strRSDFFilename = pCatDEntry->getFile().c_str();
    }        
    // Check for cell filename
    else if ( 0 == strCatDEntryName.CompareNoCase( "CEL0" ) )
    {
      d_strCELLFilename = pCatDEntry->getFile().c_str();
    }
        
		delete pCatDEntry;					
	}

  ddf.close();

  return true;
}

bool
SDTSDEMOverlay::loadExternalRef( void )
{
  ifstream ddf( d_strPath + d_strXREFFilename, ios::binary );

	if ( !ddf )
  {
    return false;
  }

  sio_8211Reader reader( ddf );				
	sc_Record record;
  sio_8211ForwardIterator iterator( reader );

  // Get the external ref record
  iterator.get( record );

  // Create an External Spatial Ref object based on the record
  d_pXREF = new sb_ExtSpatialRef( record );

  ddf.close();

  return true;
}

bool
SDTSDEMOverlay::loadInternalRef( void )
{
  ifstream ddf( d_strPath + d_strIREFFilename, ios::binary );

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
  d_pIREF = new sb_IntSpatialRef( record );

  ddf.close();

  return true;
}

bool
SDTSDEMOverlay::loadDDOM( void )
{
  ifstream ddf( d_strPath + d_strDDOMFilename, ios::binary );

	if ( !ddf )
  {
    return false;
  }

  sio_8211Reader	reader( ddf );				
  sc_Record		record;
  sb_DataDictDom* pDDOM = NULL;

  for ( sio_8211ForwardIterator i(reader); !i.done(); ++i )
  {
    // Get the external ref record
    i.get( record );

    // Create an Data Dictionary Domain object based on the record
    pDDOM = new sb_DataDictDom( record );

    // Check for different elevation types
    if ( pDDOM->getRangeOrValue() == "MIN" )
    {
      pDDOM->getDomainValue().getI( d_minElev );
    }
    else if ( pDDOM->getRangeOrValue() == "MAX" )
    {
      pDDOM->getDomainValue().getI( d_maxElev );
    }
    else
    {
      // This must be an invalid elevation value
      long tmp;
      pDDOM->getDomainValue().getI( tmp );
      d_invalidElevations.push_back( static_cast<int>( tmp ) );
    }

    delete pDDOM;
  }

  ddf.close();

  return true;
}

bool
SDTSDEMOverlay::loadDDSH( void )
{
  ifstream ddf( d_strPath + d_strDDSHFilename, ios::binary );

	if ( !ddf )
  {
    return false;
  }

  sio_8211Reader reader( ddf );				
	sc_Record record;
  sio_8211ForwardIterator iterator( reader );

  // Get the external ref record
  iterator.get( record );

  // Create a Data Dictionary Schema object based on the record
  d_pDDSH = new sb_DataDictSchema( record );

  ddf.close();

  return true;
}

bool
SDTSDEMOverlay::loadRasterDef( void )
{
  ifstream ddf( d_strPath + d_strRSDFFilename, ios::binary );

	if ( !ddf )
  {
    return false;
  }

  sio_8211Reader reader( ddf );				
	sc_Record record;
  sio_8211ForwardIterator iterator( reader );

  // Get the external ref record
  iterator.get( record );

  // Create a raster definition object based on the record
  d_pRSDF = new sb_RasterDefn( record );

  ddf.close();

  return true;
}

bool
SDTSDEMOverlay::loadSpatialDomain( void )
{
  ifstream ddf( d_strPath + d_strSPDMFilename, ios::binary );

	if ( !ddf )
  {
    return false;
  }

  sio_8211Reader reader( ddf );				
	sc_Record record;
  sio_8211ForwardIterator iterator( reader );

  // Get the external ref record
  iterator.get( record );

  // Create an Spatial Domain object based on the record
  d_pSPDM = new sb_SpatialDom( record );

  ddf.close();

  return true;
}

bool
SDTSDEMOverlay::setupProjection()
{
    ASSERT( NULL == d_pProjection );

    // Get the horizontal datum
    DATUM d = UNKNOWN_DATUM;
    CString strDatum = d_pXREF->getHorizDatum().c_str();
    if ( 0 == strDatum.CompareNoCase( "NAS" ) )
    {
        d = NAD27;
    }
    else if ( 0 == strDatum.CompareNoCase( "WGC" ) )
    {
        d = WGS_72;
    }
    else if ( 0 == strDatum.CompareNoCase( "WGE" ) )
    {
        d = WGS_84;
    }
    else if ( 0 == strDatum.CompareNoCase( "NAX" ) )
    {
        d = NAD83;
    }
    else if ( 0 == strDatum.CompareNoCase( "OHD" ) )
    {
        d = OLD_HAWAIIAN_MEAN;
    }
    else if ( 0 == strDatum.CompareNoCase( "PRD" ) )
    {
        d = PUERTO_RICO;
    }
    else
    {
        // Invalid datum
        CString strMsg;
        strMsg.Format( "Invalid Datum: <%s>", strDatum );
        AfxMessageBox( strMsg );
        return false;
    }

    // Get the Projection System
    PROJSYS p;
    CString strProjSys = d_pXREF->getRefSysName().c_str();
    if ( 0 == strProjSys.CompareNoCase( "GEO" ) )
    {
        p = GEO;
    }
    else if ( 0 == strProjSys.CompareNoCase( "UTM" ) )
    {
        p = UTM;
    }
    else if ( 0 == strProjSys.CompareNoCase( "SPCS" ) )
    {
        p = SPCS;
    }
    else
    {
        // Invalid projection
        CString strMsg;
        strMsg.Format( "Invalid projection system: <%s>", strProjSys );
        AfxMessageBox( strMsg );
        return false;
    }

    // Get the zone
    int zone = 0;
    zone = atoi( d_pXREF->getZoneNum().c_str() );

    // Create the projection
    switch ( p )
    {
        case GEO:
            d_pProjection = new GeographicProjection( d, ARC_SECONDS );
            break;
        case UTM:
            d_pProjection = new UTMProjection( zone, d, METERS );
            break;
        case SPCS:
            // XXX - should this be meters? Standard didn't say
            d_pProjection = new StatePlaneProjection( zone, d, US_FEET );
            break;
    }

    // Check for errors
    if ( NULL == d_pProjection )
    {
        AfxMessageBox( "Unable to create projection\nLoad will abort" );
        return false;
    }

    // Setup the global projection is one hasn't been setup yet
    if ( NULL == CoordinateTransforms::getProjection() )
    {
        CoordinateTransforms::setProjection( d_pProjection );
    }

    return true;
}

bool
SDTSDEMOverlay::getElevation( long row, long col, float& elev ) const
{
    if ( row < 0 || row >= getImageHeight() )
    {
        return false;
    }

    if ( col < 0 || col >= getImageWidth() )
    {
        return false;
    }

    short tmpElev = d_pDataGrid[ ( row * getImageWidth() ) + col ];    
    if ( !isElevationValid( tmpElev ) )
    {
        return false;
    }

    elev = static_cast<float>( tmpElev );
    return true;
}

void
SDTSDEMOverlay::getMinMaxSampleValue( float& min, float& max ) const
{
    min = d_minElev;
    max = d_maxElev;
}

long
SDTSDEMOverlay::getImageWidth() const
{
    return d_pRSDF->getColExtent();
}

long 
SDTSDEMOverlay::getImageHeight() const
{
    return d_pRSDF->getRowExtent();
}

void
SDTSDEMOverlay::calculateBoundingRect()
{
    // Get the spatial addresses
    const vector<sb_SpatialAddr>& points = d_pSPDM->getDomSpatialAddrs();

    // Find the bounding box
    double left, right, bottom, top;
    for ( int i = 0; i < points.size(); i++ )
    {
        if ( 0 == i )
        {
            left = right = points[i].getX();
            top = bottom = points[i].getY();
        }
        else
        {
            left = min( left, points[i].getX() );
            right = max( right, points[i].getX() );
            top = max( top, points[i].getY() );
            bottom = min( bottom, points[i].getY() );
        }
    }

    d_boundingRect.setPoints( left, bottom, right, top );
}

bool
SDTSDEMOverlay::readData()
{
  ASSERT( NULL == d_pDataGrid );

  ifstream ddf( d_strPath + d_strCELLFilename, ios::binary );

	if ( !ddf )
  {
    return false;
  }

  // Create the converter
  sio_8211Converter_BI16 bi16_converter;
  map<string, sio_8211Converter*> mapConverters;
  mapConverters["ELEVATION"] = &bi16_converter;

	// Create and initialize a dialog to display load progress
	CLoadingDialog loadingDialog;
	CString strTitle = "Loading " + getFilenameWithoutPath();
	loadingDialog.SetWindowText( strTitle );
	loadingDialog.d_progressControl.SetRange( 0, getImageHeight() );
	loadingDialog.d_progressControl.SetPos( 0 );

  // Create the elevation grid
  int gridOffset = 0;
  d_pDataGrid = new short[ getImageHeight() * getImageWidth() ];

  sio_8211Reader reader( ddf, &mapConverters );				
	sc_Record	   record;

  long temp;
  for ( sio_8211ForwardIterator i(reader); !i.done(); ++i )
  {
    // Get the cell record
    i.get( record );

    // Find the Cell Values field
    for ( sc_FieldCntr::const_iterator fIter = record.begin(); fIter != record.end(); fIter++ )
    {
      // Get the elevation if this is a cvls 
      if ( fIter->getMnemonic() == "CVLS" )
      {
        for ( sc_SubfieldCntr::const_iterator sfIter = fIter->begin();
              sfIter != fIter->end(); sfIter++ )
        {
          sfIter->getBI16( temp );
          d_pDataGrid[gridOffset++] = temp * d_pDDSH->getPrecision();
        }
      }
     }

     // Increment the loading dialog
     loadingDialog.d_progressControl.OffsetPos( 1 );
  }

  ddf.close();

  return true;
}

bool
SDTSDEMOverlay::isElevationValid( short elev ) const
{
    for ( int i = 0; i < d_invalidElevations.size(); i++ )
    {
        if ( elev == d_invalidElevations[i] )
        {
            return false;
        }
    }

    return true;
}