// RasterPlugin.cpp - implementation of exported Plugin functions
//
// Developed by: Mike Childs

#include "RasterPlugin.h"
#include "LayerFactory.h"
#include "USGSDOQPluginLayer.h"
#include <windows.h>

// Name and Mask for Plugin Identification
static const char* g_strPluginName = "USGS DOQ";
static const char* g_strMasks      = "*.doq;*.bil;*.nes;*.ses;*.nws;*.sws";

// Layer list
LayerFactory g_layers;

// Instance handle
HANDLE g_hInstance = NULL;

// DLL Entry function
BOOL WINAPI DllMain( HINSTANCE hInstance, DWORD fdwReason, LPVOID fImpLoad )
{
  // Save the instance handle
  g_hInstance = hInstance;

  return TRUE;
}

// Plugin ID functions
const char* getName()
{
  return g_strPluginName;
}

const char* getMasks()
{
  return g_strMasks;
}

void destroyOverlay( int layerID )
{
  g_layers.removeLayer( layerID );
}


void getBoundingRect( int layerID, double* pLeft, double* pBottom,
                      double* pRight, double* pTop )
{
  RasterPluginLayer* pLayer = g_layers.getLayer( layerID );
  if ( NULL != pLayer )
  {
    pLayer->getBoundingRect( *pLeft, *pBottom, *pRight, *pTop );
  }
}

const char* getDescription( int layerID )
{
  RasterPluginLayer* pLayer = g_layers.getLayer( layerID );
  if ( NULL != pLayer )
  {
    return pLayer->getDescription();
  }

  return NULL;
}

long getImageHeight( int layerID )
{
  RasterPluginLayer* pLayer = g_layers.getLayer( layerID );
  if ( NULL != pLayer )
  {
    return pLayer->getImageHeight();
  }

  return 0;
}

long getImageWidth( int layerID )
{
  RasterPluginLayer* pLayer = g_layers.getLayer( layerID );
  if ( NULL != pLayer )
  {
    return pLayer->getImageWidth();
  }

  return 0;
}

void getProjection( int layerID, PROJSYS* pProjSys, DATUM* pDatum, UNIT* pUnit, 
                    int* pZone, double* pParams )
{
  RasterPluginLayer* pLayer = g_layers.getLayer( layerID );
  if ( NULL != pLayer )
  {
    pLayer->getProjection( *pProjSys, *pDatum, *pUnit, *pZone, pParams );
  }
}

bool getRowColColor( int layerID, long row, long col,
                     unsigned char* pR, unsigned char* pG, unsigned char* pB )
{
  RasterPluginLayer* pLayer = g_layers.getLayer( layerID );
  if ( NULL != pLayer )
  {
    return pLayer->getRowColColor( row, col, *pR, *pG, *pB );
  }

  return false;
}

bool loadOverlay( int layerID, const char* strFilename )
{
  // Create a new instance of the plugin layer type
  RasterPluginLayer* pLayer = new USGSDOQPluginLayer( layerID, strFilename,
                                                      (struct HINSTANCE__ *)g_hInstance );

  // Add the layer to the list
  g_layers.addLayer( pLayer );

  // Load the layer
  return pLayer->load();
}

bool getElevation( int layerID, long row, long col, float* pElev )
{
  RasterPluginLayer* pLayer = g_layers.getLayer( layerID );
  if ( NULL != pLayer )
  {
    return pLayer->getElevation( row, col, *pElev );
  }

  return false;
}

void getMinMaxSampleValue( int layerID, float* pMin, float* pMax )
{
  RasterPluginLayer* pLayer = g_layers.getLayer( layerID );
  if ( NULL != pLayer )
  {
    pLayer->getMinMaxSampleValue( *pMin, *pMax );
  }
}

float getVerticalPixelScale( int layerID )
{
  RasterPluginLayer* pLayer = g_layers.getLayer( layerID );
  if ( NULL != pLayer )
  {
    return pLayer->getVerticalPixelScale();
  }

  return 30;
}

UNIT getVerticalUnits( int layerID )
{
  RasterPluginLayer* pLayer = g_layers.getLayer( layerID );
  if ( NULL != pLayer )
  {
    return pLayer->getVerticalUnits();
  }

  return METERS;
}

bool isVertical( int layerID )
{
  RasterPluginLayer* pLayer = g_layers.getLayer( layerID );
  if ( NULL != pLayer )
  {
    return pLayer->isVertical();
  }

  return false;
}


bool showOptionsDialog( int layerID )
{
  RasterPluginLayer* pLayer = g_layers.getLayer( layerID );
  if ( NULL != pLayer )
  {
    return pLayer->showOptionsDialog();
  }

  return false;
}

void showPropertiesDialog( int layerID )
{
  RasterPluginLayer* pLayer = g_layers.getLayer( layerID );
  if ( NULL != pLayer )
  {
    pLayer->showPropertiesDialog();
  }
}
