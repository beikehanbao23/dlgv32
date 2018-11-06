// RasterPluginLayer.cpp - implementation of RasterPluginLayer class
//
// Developed by: Mike Childs
//      Started: 4/12/98

#include "RasterPluginLayer.h"

// Construction
RasterPluginLayer::RasterPluginLayer( int layerID, const char* strFilename, HINSTANCE hInstance )
: d_layerID(layerID), d_strFilename(strFilename), d_hInstance(hInstance)
{
}

// Destruction
RasterPluginLayer::~RasterPluginLayer()
{
}