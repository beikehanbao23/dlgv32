// OverlayFactory.cpp - implementation of OverlayFactory class
//
// Developed by: Mike Childs
//      Started: 3/31/98

#include "OverlayFactory.h"
#include "OverlayTypeSelector.h"
#include <fstream>
using namespace std;

// Overlay type classes
#include "DLG3Overlay.h"
#include "GeoTIFFOverlay.h"
#include "RasterPluginOverlay.h"
#include "SDTSDEMOverlay.h"
#include "SDTSDLGOverlay.h"
#include "TIFFOverlay.h"

// SDTS includes
#include "sdtsxx/io/sio_Reader.h"
#include "sdtsxx/io/sio_8211DirEntry.h"
#include "sdtsxx/io/sio_Converter.h"
#include "sdtsxx/container/sc_Record.h"
#include "sdtsxx/builder/sb_CatalogDir.hxx"
#include "sdtsxx/builder/sb_CatalogSpatialDom.hxx"
#include "SDTSLayerDialog.h"

// Constructor
OverlayFactory::OverlayFactory()
: d_numRasterOverlays(0)
{
  // Initialize the type info list
  initializeTypeInfoList();
}

// Destructor
OverlayFactory::~OverlayFactory()
{
  // Close every overlay loaded
  removeAllOverlays();

  // Clear out the type info list
  for ( vector<OverlayTypeInfo*>::iterator j = d_typeInfoList.begin();
        j != d_typeInfoList.end(); j++ )
  {
    delete (*j);
  }
}

// Initialization
void OverlayFactory::initializeTypeInfoList()
{
  // Setup DLG-O type info
  OverlayTypeInfo* pInfoDLGO = new OverlayTypeInfo();
  pInfoDLGO->d_overlayType = DLGO_OVERLAY;
  pInfoDLGO->d_strName = "DLG-O";
  pInfoDLGO->d_strMasks.push_back( "*.do" );
  pInfoDLGO->d_strMasks.push_back( "*.opt" );
  pInfoDLGO->d_strMasks.push_back( "*.dlg" );
  pInfoDLGO->d_bRaster = false;
  d_typeInfoList.push_back( pInfoDLGO );

  // Setup GeoTIFF type info
  OverlayTypeInfo* pInfoGeoTIFF = new OverlayTypeInfo();
  pInfoGeoTIFF->d_overlayType = GEOTIFF_OVERLAY;
  pInfoGeoTIFF->d_strName = "GeoTIFF (DRG, DOQ, DEM)";
  pInfoGeoTIFF->d_strMasks.push_back( "*.tif" );
  pInfoGeoTIFF->d_strMasks.push_back( "*.tiff" );
  pInfoGeoTIFF->d_strMasks.push_back( "*.drg" );
  pInfoGeoTIFF->d_bRaster = true;
  d_typeInfoList.push_back( pInfoGeoTIFF );

  // Setup SDTS Transfer type info
  OverlayTypeInfo* pInfoSDTS = new OverlayTypeInfo();
  pInfoSDTS->d_overlayType = SDTSTRANSFER_OVERLAY;
  pInfoSDTS->d_strName = "SDTS Catalog Directory";
  pInfoSDTS->d_strMasks.push_back( "*catd.ddf" );
  pInfoSDTS->d_bRaster = false;
  d_typeInfoList.push_back( pInfoSDTS );
    
  // Get the plugin types
  initializePluginTypes();
}

bool OverlayFactory::removeOverlay( GeographicOverlay* pOverlay )
{
  // Find the overlay in the list
  int pos = 0;
  for ( list<GeographicOverlay*>::iterator i = d_pOverlays.begin();
        i != d_pOverlays.end(); i++, pos++ )
  {
    if ( (*i) == pOverlay )
    {
      delete (*i);
      d_pOverlays.erase( i );

      // Update the raster overlay count if necessary
      if ( pos < d_numRasterOverlays )
      {
        d_numRasterOverlays--;
      }

      return true;
    }
  }

  return false;
}

void OverlayFactory::removeAllOverlays()
{
  // Close every overlay loaded
  for ( list<GeographicOverlay*>::iterator i = d_pOverlays.begin();
        i != d_pOverlays.end(); i++ )
  {
    delete (*i);
  }

  // Clear the list
  d_pOverlays.clear();

  // Reset the number of raster overlays
  d_numRasterOverlays = 0;
}

const OverlayTypeInfo* 
OverlayFactory::getOverlayTypeInfo( const string& strFilename ) const
{
  CString strName = strFilename.c_str();
  vector<OverlayTypeInfo*> matches;

  // Search through the list of overlay types looking for matches to the 
  // filename
  for ( vector<OverlayTypeInfo*>::const_iterator i = d_typeInfoList.begin();
        i != d_typeInfoList.end(); i++ )
  {
    for ( list<string>::iterator j = (*i)->d_strMasks.begin();
          j != (*i)->d_strMasks.end(); j++ )
    {
      if ( checkForMaskMatch( strFilename, *j ) )
      {
        // The mask matched, add the overlay type to the list
        matches.push_back( *i );
        break;
      }
    }
  }

  // If there was just one match, return that overlay type's info
  if ( 1 == matches.size() )
  {
    return matches.front();
  }
  // If there were no matches, show an unknown overlay dialog with all
  // the types
  else if ( 0 == matches.size() )
  {
    OverlayTypeSelector dlg;
    dlg.setOverlayTypes( d_typeInfoList );
    if ( IDOK == dlg.DoModal() )
    {
      return dlg.getSelectedOverlayType();
    }
  }
  // If there were multiple matches, show an unknown overlay dialog with
  // the possible type matches
  else
  {
    OverlayTypeSelector dlg;
    dlg.setOverlayTypes( matches );
    if ( IDOK == dlg.DoModal() )
    {
      return dlg.getSelectedOverlayType();
    }
  }

  return NULL;
}

bool OverlayFactory::checkForMaskMatch( const string& strFilename,
                                       const string& strMask )
{
  CString strName( strFilename.c_str() );
  CString strM( strMask.c_str() );

  // Trim the wildcards off the mask string
  int wildcardPos;
  if ( -1 != ( wildcardPos = strM.ReverseFind( '*' ) ) )
  {
    strM = strM.Right( strM.GetLength() - wildcardPos - 1 );
  }

  // Make the filename have the same length as the mask string
  strName = strName.Right( strM.GetLength() );

  if ( 0 == strName.CompareNoCase( strM ) )
  {
    return true;
  }
  else
  {
    return false;
  }
}

int OverlayFactory::loadOverlay( const string& strFilename )
{
  // Get the type of overlay
  const OverlayTypeInfo* pTypeInfo = getOverlayTypeInfo( strFilename );
  if ( NULL == pTypeInfo )
  {
    return 0;
  }

  // Get the number of overlays currently loaded
  int oldNumOverlaysLoaded = getNumOverlaysLoaded();

  // Create and load the overlay
  GeographicOverlay* pOverlay = NULL;
  switch ( pTypeInfo->d_overlayType )
  {
  case DLGO_OVERLAY:
    pOverlay = new DLG3Overlay( CString( strFilename.c_str() ) );
    loadOverlay( pOverlay );
    break;
  case GEOTIFF_OVERLAY:
    pOverlay = new GeoTIFFOverlay( CString( strFilename.c_str() ) );
    loadGeoTIFFOverlay( pOverlay );
    break;
  case SDTSTRANSFER_OVERLAY:
    // Load the SDTS transfer
    loadSDTSTransfer( strFilename );
    break;
  case RASTER_PLUGIN_OVERLAY:
    pOverlay = new RasterPluginOverlay( CString( strFilename.c_str() ),
                                        CString( pTypeInfo->
                                        d_strDLLName.c_str() ) );
    loadOverlay( pOverlay );
    break;
  case VECTOR_PLUGIN_OVERLAY:
    break;
  }

  // Add the overlay to the overlay list in the appropriate place
  if ( NULL != pOverlay )
  {
    if ( pTypeInfo->d_bRaster )
    {
      // Add the overlay after the last raster loaded
      addRasterOverlay( pOverlay );
    }
    else
    {
      // Add the overlay to the end of the list
      d_pOverlays.push_back( pOverlay );
    }
  }

  return ( getNumOverlaysLoaded() - oldNumOverlaysLoaded );
}

void OverlayFactory::addRasterOverlay( GeographicOverlay* pOverlay )
{
  list<GeographicOverlay*>::iterator i;
  int ctr;
  for ( i = d_pOverlays.begin(), ctr = 0; i != d_pOverlays.end(); i++, ctr++ )
  {
    if ( ctr == d_numRasterOverlays )
    {
      break;
    }
  }

  // Insert the overlay before the position pointed to by the iterator
  d_pOverlays.insert( i, pOverlay );

  // Update the raster overlay count
  d_numRasterOverlays++;
}

void OverlayFactory::loadOverlay( GeographicOverlay*& pOverlay )
{
  if ( !pOverlay->load() )
  {
    delete pOverlay;
    pOverlay = NULL;
  }
}

void OverlayFactory::loadGeoTIFFOverlay( GeographicOverlay*& pOverlay )
{
	// Load the GeoTIFF overlay, if unsuccessful ask the user if
	// he wishes to attempt to load the overlay as a plain TIFF
	if ( !pOverlay->load() )
	{
    GeoTIFFOverlay* pGeoTIFFOverlay = 
      dynamic_cast<GeoTIFFOverlay*>( pOverlay );
    if ( NULL != pGeoTIFFOverlay )
    {
      // If the load failed because the file didn't have GeoTIFF tags,
      // see if the user wants to load it as a TIFF
      if ( pGeoTIFFOverlay->notGeoTIFF() )
      {
        CString strFilename = pOverlay->getFilename();
        delete pOverlay;	// deallocate memory used by overlay
        pOverlay = NULL;

		    CString strText;
        UINT    flags = MB_YESNO | MB_ICONEXCLAMATION;
        strText = "The file " + strFilename + " does not "
                  "contain any GeoTIFF information.  The file could "
                  "be loaded as a plain TIFF, however there will be "
                  "no georeferencing information available and the "
                  "image will not be correctly placed.\n\n"
                  "Would you like to attempt to open this file as a TIFF?";

        // Attempt to open as a tiff
        if ( IDYES == AfxMessageBox( strText, flags ) )
        {
	        pOverlay = new TIFFOverlay( strFilename );
          loadOverlay( pOverlay );
          return;
        }
      } /* End check to see if an error occurred processing GeoTIFF tags */
    } /* End check to make sure a GeoTIFFOverlay was passed in */

    delete pOverlay;
    pOverlay = NULL;
	}
}

void OverlayFactory::loadSDTSTransfer( const string& strFilename )
{
  ifstream istrCATD( strFilename.c_str(), ios::binary );

  if ( !istrCATD )
  {
    CString strError;
    strError.Format( "Error opening: %s, aborting load...",
                     strFilename.c_str() );
    AfxMessageBox( strError );
    return;
  }

  // Get the directory name
  CString strDir = getDirectory( strFilename );

  // Get the name of the CATS file from the CATD file
  CString strCATSFilename = getCATSFilename( istrCATD, strDir );
    
  // Close the CATD file stream
  istrCATD.close();
    
  SDTSLayerDialog dlgLayers( strCATSFilename );

  if ( IDOK == dlgLayers.DoModal() )
  {				
    const vector<SDTSModuleInfo*>& selectedLayers = dlgLayers.GetSelected();
    GeographicOverlay* pOverlay = NULL;
        
    // Check to see if this is a raster transfer
    if ( dlgLayers.isRasterTransfer() )
    {
      // Just load the SDTS/DEM
      pOverlay = new SDTSDEMOverlay( CString( strFilename.c_str() ), 
                                     selectedLayers[0]->getMap(), 
                                     getDirectory( strFilename ) );
      loadOverlay( pOverlay );
      addRasterOverlay( pOverlay );
    }
    else
    {    
      for ( vector<SDTSModuleInfo*>::const_iterator iter =
        selectedLayers.begin(); iter != selectedLayers.end(); iter++)
      {
        // Set overlay to point to a news SDTSOverlay created from
        // filename pointed to by LayersIterator.
        pOverlay = new SDTSDLGOverlay( CString( strFilename.c_str() ),
                                       (*iter)->getAGOB(),
                                       (*iter)->getMap(),
                                       (*iter)->getTheme(), strDir );
            
        // Load the overlay
        loadOverlay( pOverlay );

        // If the load was successful, add the overlay to the list and
        // update its bounding rectangle
        if ( NULL != pOverlay )
        {
          pOverlay->calculateBoundingRect();
          d_pOverlays.push_back( pOverlay );
        }
      } // End loop - loading each selected transfer 
    }
  } // End - OK pressed in layer select dialog
}

CString OverlayFactory::getCATSFilename( ifstream& istrCATD,
                                         const CString& strDirectoryName )
{
  sio_8211Reader reader( istrCATD );
				
	sc_Record      record;
	sb_CatalogDir* pCatDEntry = NULL;
	CString	       strCatDEntryName;
  CString        strCATSFilename = strDirectoryName;
				
	for ( sio_8211ForwardIterator iterator( reader ); 
  	 	  !iterator.done(); ++iterator )									
  {				
    // Get the next category domain record
    iterator.get( record );

		pCatDEntry = new sb_CatalogDir( record );

		// Get the name of the entry
    strCatDEntryName = pCatDEntry->getName().c_str();
		strCatDEntryName.TrimRight();

		if ( 0 == strCatDEntryName.CompareNoCase( "CATS" ) ) 
		{
			strCATSFilename += pCatDEntry->getFile().c_str();
      delete pCatDEntry;
      break;
		}
	
		delete pCatDEntry;					
	}

  return strCATSFilename;
}

CString OverlayFactory::getDirectory( const string& strFilename )
{
  char strDrive[_MAX_DRIVE];
  char strDir[_MAX_DIR];
  _splitpath( strFilename.c_str(), strDrive, strDir, NULL, NULL );
  CString strPath;
  strPath.Format( "%s%s", strDrive, strDir );
  return strPath;
}

GeographicOverlay* OverlayFactory::getOverlay( int pos )
{
  int curPos = 0;
  for ( list<GeographicOverlay*>::iterator i = d_pOverlays.begin();
        i != d_pOverlays.end(); i++ )
  {
    if ( pos == curPos++ )
    {
      return (*i);
    }
  }

  return NULL;
}

CString OverlayFactory::getFilterString() const
{
  CString strFilter;
  for ( vector<OverlayTypeInfo*>::const_iterator i = d_typeInfoList.begin();
        i != d_typeInfoList.end(); i++ )
  {
    strFilter += (*i)->d_strName.c_str();
    strFilter += " Files (";
    for ( list<string>::const_iterator j = (*i)->d_strMasks.begin();
          j != (*i)->d_strMasks.end(); )
    {
      strFilter += (*j).c_str();
      if ( ( ++j ) != (*i)->d_strMasks.end() )
      {
        strFilter += ", ";
      }
    }
    strFilter += ")|";
    for ( list<string>::const_iterator k = (*i)->d_strMasks.begin();
          k != (*i)->d_strMasks.end(); )
    {
      strFilter += (*k).c_str();
      if ( ( ++k ) != (*i)->d_strMasks.end() )
      {
        strFilter += "; ";
      }
    }
    strFilter += "|";
  }
  strFilter += "All Files (*.*)|*.*||";

  return strFilter;
}

void OverlayFactory::initializePluginTypes()
{
  // Get the path to search in
  CString strPath = AfxGetApp()->GetProfileString( "", "InstallDir", "" );
  strPath += "\\Plugins\\";

  // Find all the DLLs in the plugin directory
  WIN32_FIND_DATA findData;
  CString strSearchMask = strPath + "*.dll";
  HANDLE hFind = ::FindFirstFile( strSearchMask, &findData );

  if ( INVALID_HANDLE_VALUE == hFind )
  {
    return;
  }

  // Get the type info for each plugin
  OverlayTypeInfo* pInfo = NULL;
  do
  {
    CString strDLLName = strPath;
    strDLLName += findData.cFileName;
    pInfo = getPluginTypeInfo( strDLLName );
    if ( NULL != pInfo )
    {
      d_typeInfoList.push_back( pInfo );
    }
  } while ( ::FindNextFile( hFind, &findData ) );

  ::FindClose( hFind );        
}

OverlayTypeInfo* OverlayFactory::getPluginTypeInfo( const char* strDLLName )
{    
  // Get a handle to the DLL
  HINSTANCE hPlugin = ::LoadLibrary( strDLLName );
  if ( NULL == hPlugin )
  {
    return NULL;
  }

  // Get handles to the getName and getMask functions
  typedef const char* (*GET_NAME_FUNC)();
  typedef const char* (*GET_MASKS_FUNC)();
  GET_NAME_FUNC getNameFunc = (GET_NAME_FUNC)::GetProcAddress( hPlugin,
                                                               "getName" );
  GET_MASKS_FUNC getMasksFunc = (GET_MASKS_FUNC)::GetProcAddress( hPlugin,
                                                                  "getMasks" );

  // Skip if both functions weren't there
  if ( NULL == getNameFunc || NULL == getMasksFunc )
  {
    ::FreeLibrary( hPlugin );
    return NULL;
  }

  // Create the type info structure
  OverlayTypeInfo* pInfo = new OverlayTypeInfo();

  // Get the plugin type
  // XXX - only Raster plugins supported for now
  pInfo->d_bRaster = true;
  if ( pInfo->d_bRaster )
  {
    pInfo->d_overlayType = RASTER_PLUGIN_OVERLAY;
  }
  else
  {
    pInfo->d_overlayType = VECTOR_PLUGIN_OVERLAY;
  }

  pInfo->d_strName = (*getNameFunc)();
  pInfo->d_strDLLName = strDLLName;

  // Get the masks
  CString strMasks = (*getMasksFunc)();
  strMasks.TrimLeft();
  strMasks.TrimRight();
  int pos;
  while ( -1 != ( pos = strMasks.Find( ';' ) ) )
  {
    pInfo->d_strMasks.push_back( (LPCTSTR)strMasks.Left( pos ) );
    strMasks = strMasks.Right( strMasks.GetLength() - pos - 1 );
    strMasks.TrimLeft();
    strMasks.TrimRight();
  }
  pInfo->d_strMasks.push_back( (LPCTSTR)strMasks );

  // Free the plugin
  ::FreeLibrary( hPlugin );

  return pInfo;
}