// RasterPluginLayer.h - interface for abstract RasterPluginLayer class
//
// Developed by: Mike Childs
//      Started: 4/11/98

#ifndef _RASTERPLUGINLAYER_H_
#define _RASTERPLUGINLAYER_H_

#include "ProjectionTypes.h"
#include <string>
#include <windows.h>
using namespace std;

class RasterPluginLayer
{
public:
    // Construction
    RasterPluginLayer( int layerID, const char* strFilename, HINSTANCE hInstance );

    // Destruction
    virtual ~RasterPluginLayer();

    // Accessors
    int getID() const;
        /* Returns the unique ID of this plugin layer */

    // Overrideable accessors
    virtual const char* getDescription() const;
        /* Returns a textual description of the layer.  Default is the filename */

    virtual float getVerticalPixelScale() const;
        /* Returns the number of vertical units per ground pixel */

    virtual UNIT getVerticalUnits() const;
        /* Returns the vertical units */

    virtual bool showOptionsDialog();
        /* Show specialized options for this layer.  Returns true if the layer
           was modified by the dialog */

    virtual void showPropertiesDialog() const;
        /* Displays properties for this layer */

    // Functions which should be overridden
    virtual bool getElevation( long row, long col, float& elev ) const;
        /* Retrieves the elevation at pixel coordinates (<row>,<col>).  Returns
           false if the coordinates are invalid. Override this method in vertical layers */

    virtual void getMinMaxSampleValue( float& minElev, float& maxElev ) const;
        /* Retrieves the minimum and maximum elevation for this layer.  This only
           applies to vertical layers.  The default returns 0.0 for both parameters */

    virtual bool getRowColColor( long row, long col, unsigned char& r,
                                 unsigned char& g, unsigned char& b ) const;
        /* Retrieves the RGB color at pixel coordinates (<row>,<col>).  Override this
           method in non-vertical layers.  Returns false if the coordinates are invalid */

    virtual bool isVertical() const;
        /* Returns true if this is an elevation-based layer */
    
    // Functions which must be overridden
    virtual void getBoundingRect( double& left, double& bottom, double& right, double& top ) const = 0;
        /* Retrieves the bounding rectangle for this layer in native coordinates */

    virtual long getImageHeight() const = 0;
    virtual long getImageWidth() const = 0;
        /* Retrieves the pixel dimensions of this layer */

    virtual void getProjection( PROJSYS& projSys, DATUM& datum, UNIT& unit, int& zone, double* pParams ) const = 0;
        /* Retrieves the projection parameters for this layer */

    virtual bool load() = 0;
        /* Loads the layer.  Returns true if the load was successful */

protected:
    HINSTANCE getInstance() const;
    const string& getFilename() const;

private:
    // Data members
    HINSTANCE d_hInstance;
    int       d_layerID;
    string    d_strFilename;
};

inline int
RasterPluginLayer::getID() const
{
    return d_layerID;
}

inline const char*
RasterPluginLayer::getDescription() const
{
    return getFilename().c_str();
}

inline bool
RasterPluginLayer::getElevation( long row, long col, float& elev ) const
{
    return false;
}

inline void
RasterPluginLayer::getMinMaxSampleValue( float& minElev, float& maxElev ) const
{
    minElev = 0.0;
    maxElev = 0.0;
}

inline bool
RasterPluginLayer::getRowColColor( long row, long col, unsigned char& r, unsigned char& g,
                                   unsigned char& b ) const
{
    return false;
}

inline float
RasterPluginLayer::getVerticalPixelScale() const
{
    return 30.0;
}

inline UNIT
RasterPluginLayer::getVerticalUnits() const
{
    return METERS;
}

inline bool
RasterPluginLayer::isVertical() const
{
    return false;
}

inline bool
RasterPluginLayer::showOptionsDialog()
{
    return false;
}

inline void
RasterPluginLayer::showPropertiesDialog() const
{
    return;
}

inline HINSTANCE
RasterPluginLayer::getInstance() const
{
    return d_hInstance;
}

inline const string&
RasterPluginLayer::getFilename() const
{
    return d_strFilename;
}

#endif