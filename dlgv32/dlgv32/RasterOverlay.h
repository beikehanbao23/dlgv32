// RasterOverlay.h - interface for RasterOverlay class
//
// Developed by: Mike Childs
//      Started: 2/9/98

#ifndef _RASTEROVERLAY_H_
#define _RASTEROVERLAY_H_

#include "GeographicOverlay.h"
#include "InterpolatedIntensity.h"
#include "InterpolatedRaster.h"
#include "MaskedBitmap.h"
#include "ps_PixelShader.h"
#include "CoordinateTransforms.h"
#include <list>
using namespace std;

// Forward declarations
class RasterMetadataDialog;

class RasterOverlay : public GeographicOverlay, 
                      public InterpolatedIntensity,
                      public InterpolatedRaster
{
  friend class RasterMetadataDialog;
  friend class RasterOptionsPage;
  friend class RasterOptionsSheet;
  friend class VerticalOptionsPage;

public:
	// Constructors/Destructors
	RasterOverlay( CString& filename );
	virtual ~RasterOverlay();

  /*** Functions which must be overriden in subclasses ***/
  virtual long getImageHeight() const = 0;
  virtual long getImageWidth() const = 0;
  /* Return the height and width of the image in pixels respectively */

  // Accessors
  virtual UINT getBitsPerPixel() const;
  UINT getColorIntensity() const;
  COLORREF getTransparentColor() const;
  static float getVerticalExaggeration();
  bool isTextureMapped() const;
  bool isTransparent() const;
  bool isInterpolated() const;

  // Modifiers
  void enableInterpolation( bool bInterpolate = true );
  void enableTextureMapping( bool bTextureMap = true );
  void setColorIntensity( UINT colorIntensity );
  void setTransparent( bool bTransparent = true );
  void setTransparentColor( COLORREF col );
  static void setVerticalExaggeration( float vertExag );

  // Cache control functions
  virtual void invalidateCache();
  static void invalidateAllCaches();
  static void invalidateAllIntensityCaches();

  static void resetShaders();
  /* Resets all the shader to their initial state */

  virtual bool getPixelColor( double x, double y, 
                              COLORREF& color, 
                              bool bInterpolate = false );
  /* This function gets the color of the pixel at the specified
     location.  The coordinates are given in the current ground
     reference system.  If the point is not in the overlay,
     this function should return false.  If <bInterpolate> is set then
     the overlay should bilinearly interpolate to get the pixel's color.
     If the color retrieved is transparent, then false should be returned. */

  virtual bool isVertical() const;
  /* Returns true if this overlay contains elevation data, false if it
     is just a 2D raster image */

  // Overrides
	virtual void draw( CDC* pDC, CRect* pClipRect = NULL );
  virtual bool getBrowseText( const CRect& pickRect, const CRect& clientRect,
                                CString& strBrowse ) const;
	virtual BOOL showOptionsDialog( CDlgv32Doc* pDoc = NULL );
  virtual void showPropertiesDialog();

protected:
  /*** Functions which should be overridden in 2D subclasses ***/
  virtual COLORREF getRowColColor( long row, long col );
  /* Returns the color of the pixel at the specified location */

  /*** Functions which can be but aren't normally overridden in 2D subclasses ***/
  virtual void adjustPalette();
  virtual UINT getNumImportantColors() const;

  /*** Functions which should be overridden in 3D subclasses ***/
  virtual bool getElevation( long row, long col, float& elev ) const;
  /* This function should be overridden in 3D subclasses of
     RasterOverlay.  It places the elevation at (<row>,<col>) in <elev>.
     This function should return false if the elevation at that point
     is the elevation used to deliniate void values */

  virtual void getMinMaxSampleValue( float& min, float& max ) const = 0;
  /* This method retrieves the minimum and maximum elevation values
     for an overlay. */

  virtual float getVerticalPixelScale() const;
  /* Returns the number of vertical units it takes to equal one unit
     along the plane (x and y assumed to be equally proportioned) */

  virtual CString getVerticalUnitString() const;
  /* Returns a string containing the units for this overlay (i.e. meters) */

  /*** Functions which can be but aren't normally overridden in 3D subclasses ***/
  virtual COLORREF getBadElevationColor() const;
  /* Returns the color to use when getElevation returns false.  This
     defaults to the background color. */

  virtual bool showBadElevations() const;
  /* Returns true if bad elevation values should be shown using the color
     returned from the getBadElevationColor() method.  Default returns false */

  virtual bool getRowColSurfaceNormal( long row, long col, 
                                       ps_Vector& normal, float& elev ) const;
  /* This method determines the surface normal at the pixel location given
     by (<row>,<col>).  It also retrieves the elevation at that position
     and stores it in <elev>. The only reason this should be overriden
     is to use a different surface normal calculation method (i.e. Gouroud) 
     or to optimize the calculation of the normal somehow. */

  /*** Overrides from GeographicOverlay which shouldn't normally be overriden ***/
  virtual void getProjectionMeshSize( short& width, short& height ) const;
  /* Gets the size of the projection grid to use for fast reprojection.  The
     default implementation is 1/100th of the width and height of the image */

  float convertElevationToMeters( float elev ) const;
  /* Converts <elev> from the native vertical units of the overlay to
     meters and returns the value. The setVerticalUnits method must be
     called prior to the use of this function */

  float convertElevationFromMeters( float elev ) const;
  /* Converts <elev> from meters to the native vertical units of the overlay
     and returns the value. The setVerticalUnits method must be
     called prior to the use of this function */

  bool getElevation( float row, float col, float& elev, bool bInterpolate );
  /* Gets the elevation at ( <col>, <row> ) and places it in elev, interpolating
     if necessary.  Returns false if the elevation is invalid or void */

  void getTextureMappedColor( double x, double y, COLORREF& color );
  /* Modifies <color> to account for texture mapping */

  static int getBytesPerScanline( int width, int bpp, int paddedTo = 32 );
  COLORREF modifyRGBIntensity( COLORREF rgb ) const;
  void set24BitPixel( BYTE*& pDIB, COLORREF rgb ) const;
  void nativeProjectionToRowCol( double& x, double& y ) const;
  static void handleOverlayChanging( const RasterOverlay* pOverlay );
  static void updateAllTextureMappedLayers();

  // Vertical functions
  void setVerticalUnits( UNIT u, float verticalResolution = 1.0 );

  static void getGlobalMinMaxSampleValue( float& min, float& max );
  static void recalculateMinMaxSampleValue();

  // Overrides for InterpolatedIntensity support
  bool getRowColIntensity( long row, long col, BYTE& inten, float& elev );

  // Vertical data
  static float d_verticalExaggeration;
  float d_verticalPixelScale;
  float d_verticalUnitConversionFactor;
  float d_verticalSpatialRes;
  UNIT  d_verticalUnits;

	struct BITMAPINFO_8BIT
  {
		BITMAPINFOHEADER bmiHeader;
		RGBQUAD          bmiColors[256];
	} d_bmi;

	// Data members only for blitting purposes
	CMaskedBitmap* d_pDIBSection;
	Rectangle2D    d_rasterAreaStored;
	double		   d_oldWorldHeight;
	double		   d_oldWorldWidth;

  // Shader data
  static ps_ColorRampShader d_colorRampShader;
  static ps_DaylightShader  d_daylightShader;
  static ps_GradientShader  d_gradientShader;
  static ps_HSVShader       d_HSVShader;
  static ps_PixelShader*    d_pShader;
  static ps_PixelShaderInfo d_shaderInfo;

private:
  // Generic metadata dialog
  RasterMetadataDialog* d_pGenericMetadataDialog;

	// Data members to hold non-tags
  bool     d_bInterpolate;
  bool     d_bTextureMap;
	bool     d_bTransparent;
	COLORREF d_transparentColor;
	UINT     d_colorIntensity;

  // Raster overlay list
  static list<RasterOverlay*> d_pRasterOverlays;

  // List of layers to texture map on top of layer
  list<RasterOverlay*> d_textureMappedLayers;
  void updateTextureMappedLayers();
};

inline bool
RasterOverlay::isInterpolated() const
{
  return d_bInterpolate;
}

inline void
RasterOverlay::enableInterpolation( bool bInterpolate )
{
  d_bInterpolate = bInterpolate;
}

inline bool
RasterOverlay::isTextureMapped() const
{
  return d_bTextureMap;
}

inline UINT
RasterOverlay::getNumImportantColors() const
{
  return 0;
}

inline void
RasterOverlay::invalidateCache()
{
  d_rasterAreaStored.setPoints( 0.0, 0.0, 0.0, 0.0 );
}

inline UINT
RasterOverlay::getColorIntensity() const
{
  return d_colorIntensity;
}

inline void
RasterOverlay::setColorIntensity( UINT colorIntensity )
{
  d_colorIntensity = colorIntensity;
}

inline bool
RasterOverlay::isTransparent() const
{
  return d_bTransparent;
}

inline COLORREF
RasterOverlay::getTransparentColor() const
{
  return d_transparentColor;
}

inline void
RasterOverlay::setTransparent( bool bTransparent )
{
  d_bTransparent = bTransparent;
}

inline void
RasterOverlay::setTransparentColor( COLORREF transparentColor )
{
  d_transparentColor = transparentColor;
}

inline bool
RasterOverlay::isVertical() const
{
  return false;
}

inline CString
RasterOverlay::getVerticalUnitString() const
{
  return ( Projection::unitToString( d_verticalUnits ).c_str() );
}

inline void 
RasterOverlay::set24BitPixel( BYTE*& pDIB, COLORREF rgb ) const
{
  // Modify the intensity of the RGB triplet
  rgb = modifyRGBIntensity( rgb );

  // Put the RGB triplet into the DIB, note that RGB is stored as
  // BGR in the DIB array
	*pDIB++ = GetBValue( rgb );
	*pDIB++ = GetGValue( rgb );
	*pDIB++ = GetRValue( rgb );
}

inline void
RasterOverlay::adjustPalette()
{
  return;
}

inline void
RasterOverlay::getGlobalMinMaxSampleValue( float& min, float& max )
{
  min = d_shaderInfo.minZ;
  max = d_shaderInfo.maxZ;
}

inline float
RasterOverlay::convertElevationToMeters( float elev ) const
{
  return ( elev * d_verticalUnitConversionFactor );
}

inline float
RasterOverlay::convertElevationFromMeters( float elev ) const
{
  return ( elev / d_verticalUnitConversionFactor );
}

inline bool
RasterOverlay::showBadElevations() const
{
  return false;
}

inline COLORREF
RasterOverlay::getBadElevationColor() const
{
  return getBgColor();
}

inline void 
RasterOverlay::nativeProjectionToRowCol( double& x, double& y ) const
{
  y = ( getBoundingRect().top()  - y ) * ( getImageHeight() - 1 ) / d_boundingRect.height();
  x = ( x - getBoundingRect().left() ) * ( getImageWidth() - 1 )  / d_boundingRect.width();
}

inline bool
RasterOverlay::getElevation( long row, long col, float& elev ) const
{
  return false;
}

inline COLORREF
RasterOverlay::getRowColColor( long row, long col )
{
  return getBgColor();
}

inline void
RasterOverlay::getProjectionMeshSize( short& width, short& height ) const
{
  width = getImageWidth() / 75;
  height = getImageHeight() / 75;
}

inline float
RasterOverlay::getVerticalExaggeration()
{
  return d_verticalExaggeration;
}

inline void
RasterOverlay::setVerticalExaggeration( float vertExag )
{
  d_verticalExaggeration = vertExag;
}

inline UINT
RasterOverlay::getBitsPerPixel() const
{
  return 24;
}

#endif