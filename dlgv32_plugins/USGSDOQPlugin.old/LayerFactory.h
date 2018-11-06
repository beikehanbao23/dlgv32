// LayerFactory.h - interface for LayerFactory class
//
// Developed by: Mike Childs
//      Started: 4/12/98

#ifndef _LAYERFACTORY_H_
#define _LAYERFACTORY_H_

#include "RasterPluginLayer.h"
#include <list>
using namespace std;

class LayerFactory
{
public:
  // Construction/Destruction
  LayerFactory();
  ~LayerFactory();

  // Layer methods
  void addLayer( RasterPluginLayer* pLayer );
  RasterPluginLayer* getLayer( int layerID );
  void removeLayer( int layerID );

private:
  list<RasterPluginLayer*> d_layers;
  RasterPluginLayer*       d_pLastLayerRetrieved;
};

#endif