// LayerFactory.cpp - implementation of LayerFactory class
//
// Developed by: Mike Childs
//      Started: 4/12/98

#include "LayerFactory.h"

// Construction
LayerFactory::LayerFactory()
: d_pLastLayerRetrieved(NULL)
{
}

// Destruction
LayerFactory::~LayerFactory()
{
    // Destroy each layer
    for ( list<RasterPluginLayer*>::iterator i = d_layers.begin(); i != d_layers.end(); i++ )
    {
        delete (*i);
    }

    d_layers.clear();
}

void
LayerFactory::addLayer( RasterPluginLayer* pLayer )
{
    d_layers.push_back( pLayer );
}

RasterPluginLayer*
LayerFactory::getLayer( int layerID )
{
    // See if this is the last overlay retrieved
    if ( NULL != d_pLastLayerRetrieved )
    {
        if ( layerID == d_pLastLayerRetrieved->getID() )
        {
            return d_pLastLayerRetrieved;
        }
    }

    // Search the layers list for a match
    for ( list<RasterPluginLayer*>::iterator i = d_layers.begin(); i != d_layers.end(); i++ )
    {
        if ( layerID == (*i)->getID() )
        {
            d_pLastLayerRetrieved = (*i);
            return (*i);
        }
    }

    return NULL;
}

void
LayerFactory::removeLayer( int layerID )
{
    // Search the layers list for a match
    for ( list<RasterPluginLayer*>::iterator i = d_layers.begin(); i != d_layers.end(); i++ )
    {
        if ( layerID == (*i)->getID() )
        {
            delete (*i);
            d_layers.erase( i );
            return;
        }
    }
}