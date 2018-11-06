// RasterPluginOverlay.h - interface for RasterPluginOverlay class
//
// Developed by: Mike Childs
//      Started: 4/10/98

#ifndef _RASTERPLUGINOVERLAY_H_
#define _RASTERPLUGINOVERLAY_H_

#include "RasterOverlay.h"
#include "StdAfx.h"

// Forward declarations
class CDlgv32Doc;

class RasterPluginOverlay : public RasterOverlay
{
public:
    // Construction
    RasterPluginOverlay( CString& strFilename, const CString& strDLLName );

    // Destruction
    ~RasterPluginOverlay();

    // Overrides
    CString getDescription() const;
    long getImageHeight() const;
    long getImageWidth() const;
    bool isVertical() const;
    BOOL load();
    BOOL showOptionsDialog( CDlgv32Doc* pDoc = NULL );
    void showPropertiesDialog();

protected:
    // Overrides
    void calculateBoundingRect();
    float convertElevationToMeters( float elev ) const;
    COLORREF getBadElevationColor() const;
    bool getElevation( long row, long col, float& elev ) const;
    COLORREF getRowColColor( long row, long col );
    void getMinMaxSampleValue( float& min, float& max ) const;
    float getVerticalPixelScale() const;
    bool showBadElevations() const;

    // Helper
    bool setupProjection();

private:
    // Function typedefs
    typedef void (*DESTROY_OVERLAY_FUNC)( int );
    typedef void (*GET_BAD_ELEVATION_COLOR_FUNC)( int, unsigned char*, unsigned char*, unsigned char* );
    typedef void (*GET_BOUNDING_RECT_FUNC)( int, double*, double*, double*, double* );
    typedef const char* (*GET_DESCRIPTION_FUNC)( int );
    typedef bool (*GET_ELEVATION_FUNC)( int, long, long, float* );
    typedef long (*GET_IMAGE_HEIGHT_FUNC)( int );
    typedef long (*GET_IMAGE_WIDTH_FUNC)( int );
    typedef void (*GET_MIN_MAX_SAMPLE_VALUE_FUNC)( int, float*, float* );
    typedef void (*GET_PROJECTION_FUNC)( int, PROJSYS*, DATUM*, UNIT*, int*, double* );
    typedef bool (*GET_ROW_COL_COLOR_FUNC)( int, long, long, 
                                            unsigned char*, unsigned char*, unsigned char* );
    typedef float (*GET_VERTICAL_PIXEL_SCALE_FUNC)( int );
    typedef UNIT (*GET_VERTICAL_UNITS_FUNC)( int );
    typedef bool (*IS_VERTICAL_FUNC)( int );
    typedef bool (*LOAD_OVERLAY_FUNC)( int, const char* );
    typedef bool (*SHOW_BAD_ELEVATIONS_FUNC)( int );
    typedef bool (*SHOW_OPTIONS_DIALOG_FUNC)( int );
    typedef void (*SHOW_PROPERTIES_DIALOG_FUNC)( int );

    // Data members
    static int d_overlayIDCounter;
    int        d_overlayID;

    // Data members retrieved from the plugin
    bool  d_bIsVertical;
    long  d_imageHeight;
    long  d_imageWidth;

    // DLL data members
    CString   d_strDLLName;
    HINSTANCE d_pPlugin;

    // DLL functions
    DESTROY_OVERLAY_FUNC          d_destroyOverlayFunc;
    GET_BAD_ELEVATION_COLOR_FUNC  d_getBadElevationColorFunc;
    GET_BOUNDING_RECT_FUNC        d_getBoundingRectFunc;
    GET_DESCRIPTION_FUNC          d_getDescriptionFunc;
    GET_ELEVATION_FUNC            d_getElevationFunc;
    GET_IMAGE_HEIGHT_FUNC         d_getImageHeightFunc;
    GET_IMAGE_WIDTH_FUNC          d_getImageWidthFunc;
    GET_MIN_MAX_SAMPLE_VALUE_FUNC d_getMinMaxSampleValueFunc;
    GET_PROJECTION_FUNC           d_getProjectionFunc;
    GET_ROW_COL_COLOR_FUNC        d_getRowColColorFunc;
    GET_VERTICAL_PIXEL_SCALE_FUNC d_getVerticalPixelScaleFunc;
    GET_VERTICAL_UNITS_FUNC       d_getVerticalUnitsFunc;
    IS_VERTICAL_FUNC              d_isVerticalFunc;
    LOAD_OVERLAY_FUNC             d_loadOverlayFunc;
    SHOW_BAD_ELEVATIONS_FUNC      d_showBadElevationsFunc;
    SHOW_OPTIONS_DIALOG_FUNC      d_showOptionsDialogFunc;
    SHOW_PROPERTIES_DIALOG_FUNC   d_showPropertiesDialogFunc;
};

inline long
RasterPluginOverlay::getImageHeight() const
{
    return d_imageHeight;
}

inline long
RasterPluginOverlay::getImageWidth() const
{
    return d_imageWidth;
}

inline bool
RasterPluginOverlay::isVertical() const
{
    return d_bIsVertical;
}

inline float 
RasterPluginOverlay::convertElevationToMeters( float elev ) const
{
    return ( RasterOverlay::convertElevationToMeters(elev) * d_verticalSpatialRes );
}

#endif