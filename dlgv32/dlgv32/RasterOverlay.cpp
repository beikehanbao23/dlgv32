// RasterOverlay.cpp - implementation of RasterOverlay class
//
// Developed by: Mike Childs
//      Started: 2/9/98

#include "RasterOverlay.h"
#include "CoordinateTransforms.h"
#include "GraphicsLib/CoordinateMapping.h"
#include "MainFrm.h"
#include "RasterMetadataDialog.h"
#include "RasterOptionsSheet.h"
#include <limits.h>
#include <float.h>
#include <math.h>
#include "gctpc/untfz.h"

// Static member initialization
float RasterOverlay::d_verticalExaggeration = 3.0;
list<RasterOverlay*> RasterOverlay::d_pRasterOverlays;
ps_PixelShaderInfo RasterOverlay::d_shaderInfo;
ps_ColorRampShader RasterOverlay::d_colorRampShader;
ps_DaylightShader RasterOverlay::d_daylightShader;
ps_GradientShader RasterOverlay::d_gradientShader;
ps_HSVShader      RasterOverlay::d_HSVShader;
ps_PixelShader*   RasterOverlay::d_pShader = &RasterOverlay::d_colorRampShader;

// Construction
RasterOverlay::RasterOverlay( CString& strFilename )
: GeographicOverlay(strFilename), 
  InterpolatedIntensity(64,64),
  InterpolatedRaster(32,32),
  d_bInterpolate(false),
  d_bTextureMap(false),
  d_bTransparent(false),
  d_colorIntensity(10),
  d_oldWorldHeight(0.0),
  d_oldWorldWidth(0.0),
  d_pDIBSection(NULL),
  d_pGenericMetadataDialog(NULL),
  d_rasterAreaStored(0.0,0.0,0.0,0.0),
  d_transparentColor(RGB(255,255,255)),
  d_verticalPixelScale(0.0),
  d_verticalSpatialRes(1.0),
  d_verticalUnitConversionFactor(1.0),
  d_verticalUnits(METERS)
{
	// Initialize DIB section header
	d_bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	d_bmi.bmiHeader.biPlanes = 1;
	d_bmi.bmiHeader.biCompression = BI_RGB;
	d_bmi.bmiHeader.biSizeImage = 0;
	d_bmi.bmiHeader.biXPelsPerMeter = 0;
	d_bmi.bmiHeader.biYPelsPerMeter = 0;
	d_bmi.bmiHeader.biClrUsed = 0;
	d_bmi.bmiHeader.biClrImportant = 0;

  // Update all the overlays texture mapped layers list if necessary
  if ( isVertical() )
  {
    updateAllTextureMappedLayers();
  }

  // Reset the shaders if this is the only overlay loaded
  if ( d_pRasterOverlays.empty() )
  {
    resetShaders();
  }

  // Add the overlay to the static list of raster overlays
  d_pRasterOverlays.push_back( this );
}

// Destruction
RasterOverlay::~RasterOverlay()
{
  // Free the DIB Section
  delete d_pDIBSection;

  // Find and remove the overlay from the static list of raster overlays
  list<RasterOverlay*>::iterator i;
  for ( i = d_pRasterOverlays.begin(); i != d_pRasterOverlays.end(); i++ )
  {
    if ( this == *i )
    {
      d_pRasterOverlays.erase( i );
      break;
    }
  }

  // Update all the overlay's texture mapped layers lists
  updateAllTextureMappedLayers();

  // Recalculate the min and max sample values
  recalculateMinMaxSampleValue();

  // Free the metadata dialog
  delete d_pGenericMetadataDialog;
}

COLORREF 
RasterOverlay::modifyRGBIntensity( COLORREF rgb ) const
{
  // If the color intensity hasn't been modified just return the original value
  if ( 10 == d_colorIntensity )
	{
    return rgb;
	}

  // Adjust the color intensity
  if ( d_colorIntensity > 10 )
	{
  	double factor_gt = (double)( 20.0 - d_colorIntensity ) / 10.0;
    rgb = RGB( GetRValue( rgb ) * factor_gt,
               GetGValue( rgb ) * factor_gt,
               GetBValue( rgb ) * factor_gt );
  }
  else
	{
  	double factor_lt = (double)( 10.0 - d_colorIntensity ) / 10.0;
    rgb = RGB( GetRValue( rgb ) + ( 255 - GetRValue( rgb ) ) * factor_lt,
               GetGValue( rgb ) + ( 255 - GetGValue( rgb ) ) * factor_lt,
               GetBValue( rgb ) + ( 255 - GetBValue( rgb ) ) * factor_lt );
	}

  return rgb;
}

BOOL
RasterOverlay::showOptionsDialog( CDlgv32Doc* pDoc )
{
  RasterOptionsSheet dlg( "Raster Options", this, &d_daylightShader, &d_gradientShader,
                          &d_HSVShader, &d_colorRampShader, pDoc );
  dlg.DoModal();
  return FALSE;
}

void
RasterOverlay::draw( CDC* pDC, CRect* pClipRect )
{
	// Do not attempt to draw if the overlay is not loaded or 
	// it is not supposed to be shown or there is no current
	// projection defined
	if ( !d_loaded || !d_show || CoordinateTransforms::getCurrentMapping() == 0 )
	{
		return;
	}

	// Don't draw if the device isn't capable of raster operations
	if ( ! ( pDC->GetDeviceCaps( RASTERCAPS ) & RC_BITBLT ) )
	{
		return;
	}

	// Calculate the total invalid rectangle
	Rectangle2D invalidRect = calculateInvalidRect( pDC, pClipRect );

	// Abort the draw if the intersection rectangle is empty
	if ( invalidRect.isEmpty() )
	{
		pDC->SelectClipRgn( NULL );
		return;
	}

  // Get the size of the invalid rectangle in pixel coordinates
  CRect pixelRect = CoordinateTransforms::GndRefSystoLP( invalidRect );
  int clipWidth  = pixelRect.Width();	 // pixel width of clip region
	int clipHeight = pixelRect.Height(); // pixel length of clip region

	// Get the current height and width of the world space window
	Rectangle2D worldSpaceRect = CoordinateTransforms::getCurrentMapping()->getWindowExtents();
	double worldHeight = worldSpaceRect.height();
	double worldWidth  = worldSpaceRect.width();

	// If the current loaded area contains the area to be loaded and
	// the worldspace height and width hasn't changed  just blit the old bitmap
	Rectangle2D tempIntersectArea;
  tempIntersectArea.intersectRect( invalidRect, d_rasterAreaStored );
	if ( tempIntersectArea == invalidRect && 
       d_oldWorldHeight  == worldHeight &&
  		 d_oldWorldWidth   == worldWidth )
	{
		// Find the logical coordinates of the top left of the area stored
		double top, left;
		top  = d_rasterAreaStored.top();
		left = d_rasterAreaStored.left();
    CoordinateTransforms::GndRefSystoLP( left, top );

		// Draw the bitmap
    if ( isTransparent() && !d_bReproject )
    {
      d_pDIBSection->DrawTransparent( pDC, left, top, getTransparentColor() );
    }
    else
    {
	    d_pDIBSection->DrawMasked( pDC, left, top );
    }

		pDC->SelectClipRgn( NULL );
		return;
	}
	else
	{
		delete d_pDIBSection;
    d_pDIBSection = NULL;
		d_rasterAreaStored = invalidRect;

		// Set the old world space height and width variables
		d_oldWorldHeight = worldHeight;
		d_oldWorldWidth  = worldWidth;
	}

  // Get and setup the status bar progress control
	CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>( AfxGetMainWnd() );
  MCStatusBar* pStatusBar = NULL;
  if ( NULL != pMainFrame )
  {
	  pStatusBar = pMainFrame->GetStatusBar();
	  pStatusBar->StartProgress( 0, clipHeight, "Rendering Image..." );
  }

	// Initialize the BITMAPINFOHEADER
  d_bmi.bmiHeader.biBitCount = 24;
	d_bmi.bmiHeader.biWidth    = clipWidth;
	d_bmi.bmiHeader.biHeight   = -clipHeight;

  // Get the number of bytes in a scanline
  int bytesPerScanline = getBytesPerScanline( clipWidth, 24 );

	// Create the DIBSection
	BYTE*   pBits;
	HBITMAP hDIBSection;
	hDIBSection = CreateDIBSection( pDC->GetSafeHdc(), (BITMAPINFO*)&d_bmi, 
  		                            DIB_RGB_COLORS, (VOID**)&pBits, 0, 0 );
	if ( !hDIBSection )
	{
		AfxMessageBox( "Unable to create DIBSection" );
		return;
	}

  // Figure out the spacing of the pixels in world coordinates
  double rowSpacing = invalidRect.height() / clipHeight;
  double colSpacing = invalidRect.width()  / clipWidth;
  double curRow = invalidRect.top();
  double curCol = invalidRect.left();

  // Determine whether or not interpolation should be used
  const Rectangle2D& grsBoundingRect = getGlobalBoundingRect();
  double hPixelSpacing = colSpacing * getImageWidth()  / grsBoundingRect.width();
  double vPixelSpacing = rowSpacing * getImageHeight() / grsBoundingRect.height();
  bool bInterpolate = ( vPixelSpacing < 1.0 ) || ( hPixelSpacing < 1.0 );
  bInterpolate = bInterpolate && d_bInterpolate;

  // Determine whether or not to texture map stuff
  bool bTextureMap = false;
  if ( isTextureMapped() && !d_textureMappedLayers.empty() )
  {
    bTextureMap = true;
    d_shaderInfo.bUseColor = true;
  }

  // Create the bitmap and its mask
	d_pDIBSection = new CMaskedBitmap();
  int maskWidthBytes = getBytesPerScanline( clipWidth, 1, 16 );
  d_pDIBSection->CreateMask( clipWidth, clipHeight, maskWidthBytes );

  for ( register int row_ctr = 0; row_ctr < clipHeight; row_ctr++ )
	{
		// Set the progress bar position
		pStatusBar->SetProgressPos( row_ctr );

    COLORREF pixelCol;
    BYTE* pCurPixel = pBits;
    for ( register int col_ctr = 0; col_ctr < clipWidth; col_ctr++ )
    {
      // Get the pixel color at the current position
      if ( !getPixelColor( curCol, curRow, pixelCol, bInterpolate ) )
      {
         d_pDIBSection->TurnPixelOff( col_ctr, row_ctr );
      }
      else
      {
        // Texture map if necessary
        if ( bTextureMap )
        {
           getTextureMappedColor( curCol, curRow, pixelCol );
        }
      }

      // Fill the pixel with the color
      set24BitPixel( pCurPixel, pixelCol );

      // Increment to the next column
      curCol += colSpacing;
    }

    // Move the pixel buffer pointer to the next row
    pBits += bytesPerScanline;

    // Increment to the next row and reset the column
    curCol = invalidRect.left();
    curRow -= rowSpacing;
	}
        
  // Reset the shader info
  d_shaderInfo.bUseColor = false;

	// Stop showing progress bar on status bar
	pStatusBar->StopProgress();

  // Make sure the GDI is finished
  ::GdiFlush();

	// Attach the DIB Section to the bitmap
	d_pDIBSection->Attach( hDIBSection );

	// Find the logical coordinates of the top left of the area stored
	int top  = pixelRect.TopLeft().y;
	int left = pixelRect.TopLeft().x;

	// Draw the DIB
  if ( isTransparent() && !d_bReproject )
  {
     d_pDIBSection->DrawTransparent( pDC, left, top, getTransparentColor() );
  }
  else
  {
	   d_pDIBSection->DrawMasked( pDC, left, top );
  }

	// Restore DC to its previous state
	pDC->SelectClipRgn( NULL );
}    

// Returns the number of bytes it takes to store <width> pixels
// aligned on a boundary of <paddedTo> bits
int 
RasterOverlay::getBytesPerScanline( int width, int bpp, int paddedTo )
{
	int temp = width * bpp;
	if ( temp % paddedTo != 0 )
	{
		temp += paddedTo - temp % paddedTo;
	}
	return ( temp >> 3 );
}

void
RasterOverlay::invalidateAllCaches()
{
  // Clear the stored area buffer for each overlay
  for ( list<RasterOverlay*>::iterator i = d_pRasterOverlays.begin();
        i != d_pRasterOverlays.end(); i++ )
  {
    (*i)->invalidateCache();
  }
}

void
RasterOverlay::invalidateAllIntensityCaches()
{
  // Clear the stored area buffer for each overlay
  for ( list<RasterOverlay*>::iterator i = d_pRasterOverlays.begin();
        i != d_pRasterOverlays.end(); i++ )
  {
    if ( (*i)->isVertical() )
    {
      (*i)->invalidateIntensityCache();
    }
  }
}

void
RasterOverlay::recalculateMinMaxSampleValue()
{
  float oldMin, oldMax;
  bool bFirstVertical = true;
  getGlobalMinMaxSampleValue( oldMin, oldMax );

  // Calculate the min and max sample values
  float newMin = oldMin;
  float newMax = oldMax;
  for ( list<RasterOverlay*>::iterator i = d_pRasterOverlays.begin();
        i != d_pRasterOverlays.end(); i++ )
  {       
    if ( (*i)->isVertical() )
    {
      if ( bFirstVertical )
      {
        bFirstVertical = false;

        // Initialize min and max
        (*i)->getMinMaxSampleValue( newMin, newMax );
        newMin = (*i)->convertElevationToMeters( newMin );
        newMax = (*i)->convertElevationToMeters( newMax );
      }
      else
      {
        float minVal, maxVal;
        (*i)->getMinMaxSampleValue( minVal, maxVal );
        minVal = (*i)->convertElevationToMeters( minVal );
        maxVal = (*i)->convertElevationToMeters( maxVal );
        newMin = min( minVal, newMin );
        newMax = max( maxVal, newMax );
      }    
    }
  }

  // If the min and max values have changed, invalidate all caches
  if ( oldMin != newMin || oldMax != newMax )
  {
    d_shaderInfo.minZ = newMin;
    d_shaderInfo.maxZ = newMax;
    invalidateAllCaches();
  }
}

float
RasterOverlay::getVerticalPixelScale() const
{
  // Calculate the vertical pixel scale if necessary
  if ( 0.0 == d_verticalPixelScale )
  {
    // Get the lat, lon of the top two points
    double left = d_boundingRect.left();
    double top  = d_boundingRect.top();
    double right = d_boundingRect.right();
    double bottom = d_boundingRect.bottom();

    // Convert the points to lat, lon
    double lat1, lon1, lat2, lon2;
    getNativeProjection()->projectToGeo( left, top, lat1, lon1 );
    getNativeProjection()->projectToGeo( right, bottom, lat2, lon2 );

    // Calculate the distance in meters between the two points
    double distance = CoordinateTransforms::calculateGreatCircleDistance( lat1, lon1, lat2, lon2 );
    double pixDist = sqrt( getImageHeight() * getImageHeight() + getImageWidth() * getImageWidth() );
    double vps = distance / ( convertElevationToMeters( 1.0 ) * pixDist );
    const_cast<RasterOverlay*>(this)->d_verticalPixelScale = vps;
  }

  return d_verticalPixelScale;
}

void
RasterOverlay::enableTextureMapping( bool bTextureMap )
{
  if ( d_bTextureMap != bTextureMap )
  {
    d_bTextureMap = bTextureMap;

    // Invalidate the cache if we're turning off texture mapping and
    // there were texture mapped layers
    if ( !d_bTextureMap && !d_textureMappedLayers.empty() )
    {
      invalidateCache();
      d_textureMappedLayers.clear();
    }
    else if ( d_bTextureMap )
    {
      updateTextureMappedLayers();
    }
  }
}

void 
RasterOverlay::updateTextureMappedLayers()
{
  // Get the current size of the list
  int previousSize = d_textureMappedLayers.size();

  // Clear out the list
  d_textureMappedLayers.clear();

  if ( !isTextureMapped() )
  {
    return;
  }

  // Add all vertical layers which intersect this layer to the list
  Rectangle2D rectTemp;
  for ( list<RasterOverlay*>::iterator i = d_pRasterOverlays.begin();
        i != d_pRasterOverlays.end(); i++ )
  {
    if ( (*i)->isVertical() )
    {
      if ( rectTemp.intersectRect( getGlobalBoundingRect(),
                                   (*i)->getGlobalBoundingRect() ) )
      {
        d_textureMappedLayers.push_back( *i );
      }
    }
  }

  // Invalidate the overlay's cache if the number of overlays in the texture
  // mapped layers list has changed
  if ( d_textureMappedLayers.size() != previousSize )
  {
    invalidateCache();
  }
}

bool
RasterOverlay::getRowColIntensity( long row, long col, BYTE& inten, float& elev )
{
  // Get the surface normal at the point
  ps_Vector normal;
  if ( !getRowColSurfaceNormal( row, col, normal, elev ) )
  {
    return false;
  }

  inten = static_cast<BYTE>( d_pShader->getIntensity( normal ) * 255.0 );
  return true;
}

bool 
RasterOverlay::getPixelColor( double x, double y, COLORREF& color, bool bInterpolate )
{
  // Get the native coordinates of the current position
  if ( !projectGlobalToNative( x, y ) )
  {
    return false;
  }

  // Return false if the point isn't in the bounding rectangle
  if ( !getBoundingRect().pointInRect( x, y ) )
  {
    return false;
  }

  // Get the row and column coordinates of the pixel
  nativeProjectionToRowCol( x, y );

  if ( !isVertical() )
  {
    if ( bInterpolate )
    {
      color = getInterpolatedColor( y, x );
    }
    else
    {
      color = getCachedColor( y, x );
    }
  }
  else
  {
    bool bBadElevation;
    if ( bInterpolate )
    {
      bBadElevation = !getInterpolatedIntensity( y, x,
                                                 d_shaderInfo.intensity, 
                                                 d_shaderInfo.pixelZ );
    }
    else
    {
      bBadElevation = !getCachedIntensity( y, x,
                                           d_shaderInfo.intensity, 
                                           d_shaderInfo.pixelZ );
    }

    // Handle bad elevations
    if ( bBadElevation )
    {
      color = getBadElevationColor();
      return ( showBadElevations() && 
               !( isTransparent() && color == getTransparentColor() ) );
    }

    // Shade the pixel if a shader is installed
    if ( NULL != d_pShader )
    {
      d_pShader->shade( d_shaderInfo );
      color = RGB( d_shaderInfo.pixel.red, d_shaderInfo.pixel.green, d_shaderInfo.pixel.blue );
    }
    else
    {
      // Just scale the value between the min and max elevation
      BYTE scaledHeight = ( d_shaderInfo.pixelZ - d_shaderInfo.minZ ) * 255 / 
                            ( d_shaderInfo.maxZ - d_shaderInfo.minZ );
      color = RGB( scaledHeight, scaledHeight, scaledHeight );
    }
  }

  // If the pixel color should be transparent, return false
  return !( isTransparent() && color == getTransparentColor() );
}

void
RasterOverlay::showPropertiesDialog()
{
  // Create the dialog if necessary
  if ( NULL == d_pGenericMetadataDialog )
  {
    d_pGenericMetadataDialog = new RasterMetadataDialog( AfxGetMainWnd() );
    d_pGenericMetadataDialog->setOverlay( this );
  }

  // Show the dialog
  d_pGenericMetadataDialog->ShowWindow( SW_SHOWNORMAL );
}

bool
RasterOverlay::getRowColSurfaceNormal( long row, long col, ps_Vector& normal, float& elev ) const
{
  if ( !getElevation( row, col, elev ) )
  {
    return false;
  }

  // Get the elevations of the four surrounding points
  float eL, eR, eT, eB;
  if ( !getElevation( row, col - 1, eL ) ) eL = elev;
  if ( !getElevation( row, col + 1, eR ) ) eR = elev;
  if ( !getElevation( row + 1, col, eB ) ) eB = elev;
  if ( !getElevation( row - 1, col, eT ) ) eT = elev;

  // Calculate the surface normal
  normal = ps_Vector( eL - eR, eT - eB, getVerticalPixelScale() / d_verticalExaggeration );
  normal.normalize();

  elev = convertElevationToMeters( elev );

  return true;
}

bool 
RasterOverlay::getBrowseText( const CRect& pickRect, const CRect& clientRect,
                              CString& strBrowse ) const
{
  // Abort if the overlay is hidden or not vertical
  if ( !getShow() )
  {
    return false;
  }

  // Abort if there is no global projection set
  if ( NULL == CoordinateTransforms::getProjection() )
  {
    return false;
  }

  // Get the center of the pick rectangle
  CPoint ptCenter = pickRect.CenterPoint();
  double x = ptCenter.x;
  double y = ptCenter.y;

  // Convert the center point to native coordinates
  double globalX, globalY;
  CoordinateTransforms::LPtoGndRefSys( x, y );
  globalX = x;
  globalY = y;
  projectGlobalToNative( x, y );

  // Get the row and column coordinates of the pixel
  nativeProjectionToRowCol( x, y );
  float row = y;
  float col = x;

  // Get a global projection version of the client rectangle
  Rectangle2D globalClientRect = CoordinateTransforms::LPtoGndRefSys( clientRect );

  // Determine whether or not this overlay is interpolated
  bool bInterpolated = false;
  if ( isInterpolated() )
  {
    float horizSpacing = getGlobalBoundingRect().width() / getImageWidth();
    horizSpacing *= clientRect.Width() / globalClientRect.width();
    float vertSpacing = getGlobalBoundingRect().height() / getImageHeight();
    vertSpacing *= clientRect.Height() / globalClientRect.height();
    if ( horizSpacing > 1.0 || vertSpacing > 1.0 )
    {
      bInterpolated = true;
    }
  }

  if ( col >= 0.0 && col <= ( getImageWidth()  - 1 ) && 
       row >= 0.0 && row <= ( getImageHeight() - 1 ) )
  {
    // If this isn't a vertical raster show the pixel color at this point
    if ( !isVertical() )
    {
    	list<RasterOverlay*> foo1 = d_textureMappedLayers;
      // Display the elevation if this position is texture mapped
      for ( list<RasterOverlay*>::iterator i = /*d_textureMappedLayers*/foo1.begin();
            i != /*d_textureMappedLayers*/foo1.end(); i++ )
      {
        if ( (*i)->getBrowseText( pickRect, clientRect, strBrowse ) )
        {
          return true;
        }
      }

      COLORREF color;
      if ( const_cast<RasterOverlay*>(this)->getPixelColor( globalX, globalY, 
                                                            color, bInterpolated ) )
      {
        strBrowse.Format( "RGB(%3.3d,%3.3d,%3.3d)", GetRValue(color), GetGValue(color), GetBValue(color) );
      }
    }
    else
    {
      float elev;
      if ( const_cast<RasterOverlay*>(this)->getElevation( row, col, elev, bInterpolated ) )
      {
        // Get the min and max elevations for this overlay
        float min, max;
        getMinMaxSampleValue( min, max );

        // Convert the elevation from meters back to vertically adjusted native units
        elev = convertElevationFromMeters( elev ) * d_verticalSpatialRes;

        // Adjust the min and max elevations by the vertical spatial res value
        min *= d_verticalSpatialRes;
        max *= d_verticalSpatialRes;

        // Make sure th elevation is in a valid range
        if ( elev >= min && elev <= max )
        {
          strBrowse.Format( "Height = %g %s", elev, getVerticalUnitString() );
        }
        else
        {
          strBrowse.Format( "Invalid height: %g %s", elev, getVerticalUnitString() );
        }
      }
      else
      {
        // This is a void pixel
        if ( showBadElevations() )
        {
          // If the bad elevation color is also the transparent color then
          // don't show it
          if ( !isTransparent() || getBadElevationColor() != getTransparentColor() )
          {
            strBrowse.Format( "Void pixel" );
          }
        }
      }
    }

    if ( !strBrowse.IsEmpty() )
    {
      strBrowse += " (" + getFilenameWithoutPath() + ")";
      return true;
    };
  }

  return false;
}

void 
RasterOverlay::updateAllTextureMappedLayers()
{
  list<RasterOverlay*>::iterator i;
  for ( i = d_pRasterOverlays.begin(); i != d_pRasterOverlays.end(); i++ )
  {
    (*i)->updateTextureMappedLayers();
  }
}

void 
RasterOverlay::handleOverlayChanging( const RasterOverlay* pOverlay )
{
  list<RasterOverlay*>::iterator i;
  list<RasterOverlay*>::iterator j;
  for ( i = d_pRasterOverlays.begin(); i != d_pRasterOverlays.end(); i++ )
  {
    // Search through the overlay's list of texture mapped layers, and
    // invalidate the cache if the changing layer is in the list
    if ( (*i)->isTextureMapped() )
    {
      for ( j = (*i)->d_textureMappedLayers.begin(); 
            j != (*i)->d_textureMappedLayers.end(); j++ )
      {
        if ( pOverlay == *j )
        {
          (*i)->invalidateCache();
          break;
        }
      }
    }
  }
}

void
RasterOverlay::setVerticalUnits( UNIT u, float verticalResolution )
{
  double factor = 0.0;
  untfz( u, METERS, &factor );
  d_verticalUnits = u;
  d_verticalSpatialRes = verticalResolution;
  d_verticalUnitConversionFactor = factor * verticalResolution;
}

bool 
RasterOverlay::getElevation( float row, float col, float& elev, bool bInterpolate )
{
  BYTE inten;
  bool bSuccess = false;
  if ( bInterpolate )
  {
    bSuccess = getInterpolatedIntensity( row, col, inten, elev );
  }
  else
  {
    bSuccess = getCachedIntensity( row, col, inten, elev );
  }

  return bSuccess;
}

void 
RasterOverlay::getTextureMappedColor( double x, double y, COLORREF& color )
{
  // Set the color field of the shader info
  d_shaderInfo.pixel.red   = GetRValue( color );
  d_shaderInfo.pixel.green = GetGValue( color );
  d_shaderInfo.pixel.blue  = GetBValue( color );
    
  // Set the color use field of the shader info
  d_shaderInfo.bUseColor = true;

  COLORREF textureMappedColor = color;
  for ( list<RasterOverlay*>::iterator i = d_textureMappedLayers.begin();
        i != d_textureMappedLayers.end(); i++ )
  {
    if ( (*i)->getPixelColor( x, y, textureMappedColor, (*i)->isInterpolated() ) )
    {
      // Don't use it if it's the transparent color
      if ( (*i)->isTransparent() &&
           (*i)->getTransparentColor() == textureMappedColor )
      {
          continue;
      }
                  
      color = textureMappedColor;
      break;
    }
  }
}

void
RasterOverlay::resetShaders()
{
  ps_PixelShader* pShaders[4] = { &d_daylightShader,
                                  &d_gradientShader,
                                  &d_HSVShader,
                                  &d_colorRampShader };

  for ( int i = 0; i < 4; i++ )
  {
    // Set the water level of each shader to zero
    pShaders[i]->setWaterLevel( 0.0 );
  }
}