// OverlayFactory.h - interface for OverlayFactory class
//
// Developed by: Mike Childs
//      Started: 3/31/98

#ifndef _OVERLAYFACTORY_H_
#define _OVERLAYFACTORY_H_

#include "StdAfx.h"
#include <list>
#include <string>
#include <vector>
using namespace std;

// Forward declarations
class GeographicOverlay;

// List of overlay types supported
enum OVERLAYTYPE { DLGO_OVERLAY, GEOTIFF_OVERLAY, TIFF_OVERLAY, 
                   SDTSTRANSFER_OVERLAY,RASTER_PLUGIN_OVERLAY,
                   VECTOR_PLUGIN_OVERLAY, UNKNOWN_OVERLAY };

// Type info class
class OverlayTypeInfo
{
public:
  OVERLAYTYPE  d_overlayType;
  string       d_strName;
  string       d_strDLLName;
  list<string> d_strMasks;
  bool         d_bRaster;
};

class OverlayFactory
{
public:
  // Construction/Destruction
  OverlayFactory();
  ~OverlayFactory();

  int loadOverlay( const string& strFilename );
  /* Loads the overlay(s) associated with the file <strFilename>.  Returns
     the number of overlays loaded, or 0 if an error occurred */

  bool removeOverlay( GeographicOverlay* pOverlay );
  /* Removes the overlay pointed to by <pOverlay> from the currently loaded
     overlays list.  If the overlay was successfully removed, true is returned,
     otherwise false is returned. */

  void removeAllOverlays();
  /* Removes and destroys all currently loaded overlays */

  int getNumOverlaysLoaded() const;
  /* Returns the number of overlays currently loaded */

  int getNumRasterOverlaysLoaded() const;
  /* Returns the number of raster overlays currently loaded */

  list<GeographicOverlay*>& getOverlays();
  const list<GeographicOverlay*>& getOverlays() const;
  /* Returns a reference to the list of overlays currently loaded */

  GeographicOverlay* getOverlay( int pos );
  /* Returns the overlay at <pos> in the list */

  CString getFilterString() const;
  /* Returns a filter string for use with Open File Dialogs */

private:
  // Helper functions
  void addRasterOverlay( GeographicOverlay* pOverlay );
  static bool checkForMaskMatch( const string& strFilename,
                                 const string& strMask );
  static CString getCATSFilename( ifstream& istrCATD, 
                                  const CString& strDirectoryName );
  static CString getDirectory( const string& strFilename );
  OverlayTypeInfo* getPluginTypeInfo( const char* strEntryName );
  void initializePluginTypes();
  void initializeTypeInfoList();
  const OverlayTypeInfo* getOverlayTypeInfo( const string& strFilename ) const;
  static void loadGeoTIFFOverlay( GeographicOverlay*& pOverlay );
  static void loadOverlay( GeographicOverlay*& pOverlay );
  void loadSDTSTransfer( const string& strFilename );

  // Member data
  list<GeographicOverlay*> d_pOverlays;
  vector<OverlayTypeInfo*> d_typeInfoList;
  int                      d_numRasterOverlays;
};

inline int
OverlayFactory::getNumOverlaysLoaded() const
{
  return d_pOverlays.size();
}

inline int
OverlayFactory::getNumRasterOverlaysLoaded() const
{
  return d_numRasterOverlays;
}

inline list<GeographicOverlay*>&
OverlayFactory::getOverlays()
{
  return d_pOverlays;
}

inline const list<GeographicOverlay*>&
OverlayFactory::getOverlays() const
{
  return d_pOverlays;
}

#endif