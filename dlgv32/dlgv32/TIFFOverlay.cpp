// TIFFOverlay.cpp - implementation of TIFFOverlay class
//
// Developed by: Mike Childs
//      Started: 2/9/97
//

#include <iostream>
#include <limits.h>

#include "TIFFOverlay.h"
#include "CoordinateTransforms.h"
#include "MainFrm.h"
#include "MC_SBAR.h"
#include "GraphicsLib\CoordinateMapping.h"
#include "TIFFPropertySheet.h"
#include "ProjectionLib/UnknownProjection.h"

// Pixel shader stuff
#include "ps_Vector.h"

using namespace std;

TIFFOverlay::TIFFOverlay( CString& strFilename )
: RasterOverlay(strFilename),
  d_pCache(NULL),
  d_samplesPerPixel(1), 
  d_pPropertySheet(NULL) 
{
	tif = (TIFF*)0;
}

TIFFOverlay::~TIFFOverlay()
{
	// Close the tif if it's valid
	if ( tif )
	{
    try
    {
      XTIFFClose(tif);
    }
    catch ( ... )
    {
    }
	}

  // Free the property sheet
  delete d_pPropertySheet;

  // Free the data cache
  delete d_pCache;
}

TIFFOverlay::TIFFCache::TIFFCache( TIFF* pTIFF, int rowsPerStrip, 
                                  UINT cacheSize )
: d_pTIFF(pTIFF), d_rowsPerStrip(rowsPerStrip), d_cacheSize(cacheSize)
{
  ASSERT( NULL != pTIFF );
  d_scanlineSize = TIFFScanlineSize( pTIFF );
  d_stripSize = TIFFStripSize( pTIFF );
  d_pStrips = new TIFFStripBuffer[cacheSize];

  // Create the strip buffers with pre-allocated buffers
  for ( int i = 0; i < d_cacheSize; i++ )
  {
    tdata_t buf = _TIFFmalloc( d_stripSize );
    d_pStrips[i].setStripData( buf );
  }
}

TIFFOverlay::TIFFCache::~TIFFCache()
{
  // Delete the strip buffer
  delete[] d_pStrips;
}

TIFFOverlay::TIFFCache::TIFFStripBuffer::TIFFStripBuffer()
: d_pStrip(NULL), d_startRow(-1), d_endRow(-2)
{
}

TIFFOverlay::TIFFCache::TIFFStripBuffer::~TIFFStripBuffer()
{
  if ( NULL != d_pStrip )
  {
    _TIFFfree( d_pStrip );
  }
}

BYTE* TIFFOverlay::TIFFCache::getScanlineData( long row )
{
  tstrip_t strip = row / d_rowsPerStrip;
  TIFFStripBuffer& pBuffer = d_pStrips[strip % d_cacheSize];
  BYTE* pStripData = reinterpret_cast<BYTE*>( pBuffer.getStripData() );
  ASSERT( NULL != pStripData );

  // See if the appropriate strip has already been loaded
  if ( !pBuffer.isRowInStrip( row ) )
  {
    // Read the TIFF strip with the appropriate data in it
    TIFFReadEncodedStrip( d_pTIFF, strip, pStripData, (tsize_t)-1 );

    // Set the new start and end row of the strip
    int startRow = strip * d_rowsPerStrip;
    pBuffer.setStripLocation( startRow, startRow + d_rowsPerStrip - 1 );
  }

  // Return a pointer to the requested scanline
  return ( pStripData + d_scanlineSize * ( row % d_rowsPerStrip ) );
}

BOOL operator==( const RGBQUAD& rgb1, const RGBQUAD& rgb2 )
{
	if ( rgb1.rgbGreen == rgb2.rgbGreen && rgb1.rgbBlue == rgb2.rgbBlue &&
  		 rgb1.rgbRed == rgb2.rgbRed && rgb1.rgbReserved == rgb2.rgbReserved )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void TIFFOverlay::draw( CDC* pDC, CRect* pClipRect )
{
  // Use the base class draw if projection switching has occurred
  // or we need bilinear interpolation or this isn't an 8-bit TIFF
  if ( isInterpolated() || isTextureMapped() || getBitsPerPixel() != 8 || 
       d_bReproject || isVertical() )
  {
    RasterOverlay::draw( pDC, pClipRect );
    return;
  }

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

	// Determine what part of the image should be read
	double start_row, end_row, start_column, end_column;
  getTIFFAreaToLoad( invalidRect, start_row, end_row,
                     start_column, end_column );
 
  // Determine the column and row spacing
  CRect tempRect = CoordinateTransforms::GndRefSystoLP( invalidRect );
  int clipWidth  = tempRect.Width();	// pixel width of clip region
	int clipHeight = tempRect.Height();	// pixel length of clip region
	double col_spacing = ( end_column - start_column ) / (double)clipWidth;
	double row_spacing = ( end_row    - start_row )   / (double)clipHeight;

	// Get the current height and width of the world space window rounded 
	Rectangle2D worldSpaceRect = CoordinateTransforms::getCurrentMapping()->
  		                         getWindowExtents();
	double worldHeight = worldSpaceRect.height();
	double worldWidth  = worldSpaceRect.width();

	// If the current loaded tiff area contains the area to be loaded and
	// the worldspace height and width hasn't changed 
	// just blit the old bitmap
	Rectangle2D tempIntersectTIFFArea;
  tempIntersectTIFFArea.intersectRect( invalidRect, d_rasterAreaStored );
	if ( tempIntersectTIFFArea == invalidRect && 
       d_oldWorldHeight == worldHeight && d_oldWorldWidth == worldWidth )
	{
		// Find the logical coordinates of the top left of the area stored
		double top, left;
		top  = d_rasterAreaStored.top();
		left = d_rasterAreaStored.left();
    CoordinateTransforms::GndRefSystoLP( left, top );

		// Draw the bitmap
		if ( isTransparent() )
		{
			d_pDIBSection->DrawTransparent( pDC, left, top, getTransparentColor() );
		}
		else
		{
			d_pDIBSection->Draw( pDC, left, top );
		}

		pDC->SelectClipRgn( NULL );
		return;
	}
	else
	{
		delete d_pDIBSection;
		d_rasterAreaStored = invalidRect;

		// Set the old world space height and width variables
		d_oldWorldHeight = worldHeight;
		d_oldWorldWidth  = worldWidth;
	}

	// Get and setup the status bar progress control
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	MCStatusBar* pStatusBar = pMainFrame->GetStatusBar();
	pStatusBar->StartProgress( 0, clipHeight, "Rendering Image..." );

	// Initialize the BITMAPINFOHEADER
  UINT bpp = getBitsPerPixel();
  d_bmi.bmiHeader.biBitCount = ( 16 == bpp ) ? 24 : bpp;
	d_bmi.bmiHeader.biWidth  = clipWidth;
	d_bmi.bmiHeader.biHeight = -clipHeight;

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

	// Calculate the number of bytes in a DIB scanline
	int scanlineBytes = getBytesPerScanline( clipWidth, getBitsPerPixel() );

  // Create an array with the columns already cast to integers
  int* pColumns = new int[clipWidth];
  double cur_col = start_column;
  for ( register int col = 0; col < clipWidth; col++ )
  {
    pColumns[col] = static_cast<int>( cur_col );
    cur_col += col_spacing;
  }

	// Read the data into the DIB section
	double cur_row = start_row;
  int row = static_cast<int>(cur_row);
  int last_row = -1;
  BYTE* pScanline = NULL;
  BYTE* pDIB = NULL;
	for ( register int row_ctr = 0; row_ctr < clipHeight; row_ctr++ )
	{
		// Set the progress bar position
		pStatusBar->SetProgressPos( row_ctr );
		
    // If the row hasn't changed, just copy the bits from the last row
    if ( row == last_row )
    {
      memcpy( pBits, pBits - scanlineBytes, scanlineBytes );
    }
    else
    {
      // Get the current scanline
      pScanline = d_pCache->getScanlineData( row );

      ASSERT( 8 == getBitsPerPixel() );

      // Fill the DIB buffer with the TIFF scanline data
      pDIB = pBits;
      for ( register int pix = 0; pix < clipWidth; pix++ )
      {
        *pDIB++ = pScanline[ pColumns[pix] ];
      }
    }
 
		pBits += scanlineBytes;

    // Increment the current row
		cur_row += row_spacing;
    last_row = row;
    row = static_cast<int>(cur_row);	
  }

  // Reclaim the column array
  delete[] pColumns;

	// Stop showing progress bar on status bar
	pStatusBar->StopProgress();

  // Make sure the GDI is finished
  ::GdiFlush();

	// Attach the DIB Section to the bitmap
	d_pDIBSection = new CMaskedBitmap();
	d_pDIBSection->Attach( hDIBSection );
	
	// Find the logical coordinates of the top left of the area stored
	int top  = tempRect.TopLeft().y;
	int left = tempRect.TopLeft().x;

	// Draw the DIB
	if ( isTransparent() )
	{
		d_pDIBSection->DrawTransparent( pDC, left, top, getTransparentColor() );
	}
	else
	{
		d_pDIBSection->Draw( pDC, left, top );
	}

	// Restore DC to its previous state
	pDC->SelectClipRgn( NULL );
}

void 
TIFFOverlay::getTIFFAreaToLoad( const Rectangle2D& rectInvalid,
                                double& startRow, double& endRow,
                                double& startColumn, double& endColumn ) const
{
	// Determine what part of the image should be read
	double bound_width, bound_height, ul_x, ul_y, ir_x1, ir_y1, ir_x2, ir_y2;
	bound_width = d_boundingRect.width();
	bound_height = d_boundingRect.height();
  ul_x = d_boundingRect.left();
  ul_y = d_boundingRect.top();
  rectInvalid.getPoints( ir_x1, ir_y1, ir_x2, ir_y2 );
	startRow = ( ( ul_y - ir_y2 ) / bound_height ) * ( d_imageLength );
	endRow   = ( ( ul_y - ir_y1 ) / bound_height ) * ( d_imageLength );
	startColumn = ( ( ir_x1 - ul_x ) / bound_width ) * ( d_imageWidth );
	endColumn   = ( ( ir_x2 - ul_x ) /	bound_width ) * ( d_imageWidth );

	// Make sure <start_column>, <end_column>, <start_row>, and <end_row>
  // are valid
	startColumn = ( startColumn >= 0 ) ? startColumn : 0;
	startRow    = ( startRow    >= 0 ) ? startRow    : 0;
	endColumn   = ( endColumn <= d_imageWidth  ) ? endColumn : d_imageWidth;
	endRow      = ( endRow    <= d_imageLength ) ? endRow    : d_imageLength;
}

BOOL TIFFOverlay::load()
{
	// Open the TIFF file
	tif = XTIFFOpen( getFilename(), "r" );

	// Abort the load if the TIFF wasn't successfully opened
	if ( !tif )
	{
		AfxMessageBox( "Unable to open TIFF file: " + getFilename() );
		return FALSE;
	}

	// Get photometric interpretation
	if ( !TIFFGetField(tif, TIFFTAG_PHOTOMETRIC, &d_photometricInterpretation ))
	{
		AfxMessageBox( "Invalid TIFF: " + getFilename() );
		return FALSE;
	}

	// Get image width
	if ( !TIFFGetField( tif, TIFFTAG_IMAGEWIDTH, &d_imageWidth ) )
	{
		AfxMessageBox( "Invalid TIFF: " + getFilename() );
		return FALSE;
	}

	// Get image length
	if ( !TIFFGetField( tif, TIFFTAG_IMAGELENGTH, &d_imageLength ) )
	{
		AfxMessageBox( "Invalid TIFF: " + getFilename() );
		return FALSE;
	}

	// Get the number of rows per strip
	if ( !TIFFGetField( tif, TIFFTAG_ROWSPERSTRIP, &d_rowsPerStrip ) )
	{
		AfxMessageBox( "Invalid TIFF: " + getFilename() );
		return FALSE;
	}

	// Get the copyright info
	if ( !TIFFGetField( tif, TIFFTAG_COPYRIGHT, &d_copyright ) )
	{
		d_copyright = NULL;
	}

	// Get the date and time of creation
	if ( !TIFFGetField( tif, TIFFTAG_DATETIME, &d_datetime ) )
	{
		d_datetime = NULL;
	}

	// Get the image description
	if ( !TIFFGetField( tif, TIFFTAG_IMAGEDESCRIPTION, &d_description ) )
	{
		d_description = NULL;
	}

    // Get the number of bits per sample
    if ( !TIFFGetField( tif, TIFFTAG_BITSPERSAMPLE, &d_bitsPerSample ) )
	{
		AfxMessageBox( "Error loading TIFF: " + getFilename() );
		return FALSE;
	}

	// Get other TIFF fields depending upon what the photometric interpretation was
	switch ( d_photometricInterpretation )
	{
		case PHOTOMETRIC_MINISWHITE:	
		case PHOTOMETRIC_MINISBLACK:
    {
      // Determine the number of colors.  Is this is a special 16-bit TIFF
      // use 256 because we'll scale the values later
      int num_colors = 1 << d_bitsPerSample;
      if ( d_bitsPerSample > 8 )
      {
        num_colors = 256;

        // Test for 16-bit elevation model
        readMinMaxSampleValues( tif );

        // Recalculate the global min/max values if necessary
        if ( d_minSampleValue != d_maxSampleValue )
        {
          recalculateMinMaxSampleValue();
        }
      }

  		// Initialize variables that depend on photometric interp
  		int step = 255 / ( num_colors - 1 );
			int color = 0;
			if ( d_photometricInterpretation == PHOTOMETRIC_MINISWHITE )
			{
				step = -step;
				color = 255;
			}

			// Fill color table
			for ( int i = 0; i < num_colors; i++ )
			{
				d_colorMapRed[i] = color;
				d_colorMapBlue[i] = color;
				d_colorMapGreen[i] = color;
				d_bmi.bmiColors[i].rgbBlue = color;
				d_bmi.bmiColors[i].rgbGreen = color;
				d_bmi.bmiColors[i].rgbRed = color;
				d_bmi.bmiColors[i].rgbReserved = 0;
				color += step;
			}

			break;
		}
		case PHOTOMETRIC_RGB:
		{
			// Get the number of samples per pixel
			if ( !TIFFGetField( tif, TIFFTAG_SAMPLESPERPIXEL, &d_samplesPerPixel ) )
			{
				AfxMessageBox( "Error loading TIFF: " + getFilename() );
				return FALSE;
			}

			// Make sure samples per pixel is at least 3
			if ( d_samplesPerPixel < 3 )
			{
				AfxMessageBox( "Error loading TIFF: " + getFilename() );
				return FALSE;
			}

			d_bmi.bmiHeader.biBitCount = 24;				

			break;
		}
		case PHOTOMETRIC_PALETTE:
		{
			d_bmi.bmiHeader.biBitCount = d_bitsPerSample;

      // Read colormap
			uint16* colorMapRed;
			uint16* colorMapGreen;
			uint16* colorMapBlue;
			if ( !TIFFGetField( tif, TIFFTAG_COLORMAP, &colorMapRed, &colorMapGreen,
 					                &colorMapBlue ) )
			{
				AfxMessageBox( "Error loading TIFF: " + getFilename() );
				return FALSE;
			}

			// Make color map into RGB
			int num_colors = 1 << d_bitsPerSample;
			for ( int i = 0; i < num_colors; i++ )
			{
				d_colorMapRed[i]   = colorMapRed[i]   >> 8;
				d_colorMapGreen[i] = colorMapGreen[i] >> 8;
				d_colorMapBlue[i]  = colorMapBlue[i]  >> 8;
				d_bmi.bmiColors[i].rgbBlue = d_colorMapBlue[i];
				d_bmi.bmiColors[i].rgbGreen = d_colorMapGreen[i];
				d_bmi.bmiColors[i].rgbRed = d_colorMapRed[i];
				d_bmi.bmiColors[i].rgbReserved = 0;
			}

      break;
		}
		case PHOTOMETRIC_MASK:
		{
			AfxMessageBox( "Masked TIFFs not supported" );
			return FALSE;
			break;
		}
		case PHOTOMETRIC_SEPARATED:
		{
			AfxMessageBox( "Separated TIFFs not supported" );
			return FALSE;
			break;
		}
		case PHOTOMETRIC_YCBCR:
		{
			AfxMessageBox( "YCBCR TIFFs not supported" );
			return FALSE;
			break;
		}
		case PHOTOMETRIC_CIELAB:
		{
			AfxMessageBox( "CIELAB TIFFs not supported" );
			return FALSE;
			break;
		}
  	default:
		{
			AfxMessageBox( "Invalid Photometric Interpretation" );
			return FALSE;
		}
  }

  // Create the TIFF data cache
  d_pCache = new TIFFCache( tif, d_rowsPerStrip );

	// Set loaded flag
	d_loaded = TRUE;

	// Calculate bounding rectangle
	calculateBoundingRect();

  // Setup a default unknown projection
  d_pProjection = new UnknownProjection( 0, 0, getImageWidth(), getImageHeight() );
  handleProjectionChanged();	
    
  return TRUE;
}

void TIFFOverlay::showPropertiesDialog()
{
  // Create the dialog if necessary
  if ( NULL == d_pPropertySheet )
  {
    d_pPropertySheet = new TIFFPropertySheet( "TIFF Metadata", this );
    d_pPropertySheet->Create( AfxGetMainWnd() );
  }

  // Show the dialog
  d_pPropertySheet->ShowWindow( SW_SHOWNORMAL );
}

void TIFFOverlay::calculateBoundingRect()
{
	d_boundingRect.setPoints( 0.0, 0.0, d_imageWidth, d_imageLength );
}

void TIFFOverlay::adjustPalette()
{
	// Abort if not a palette TIFF
	if ( ( d_bitsPerSample * d_samplesPerPixel ) > 8  )
	{
		return;
	}

  int num_colors = 1 << d_bitsPerSample;
	int newred, newgreen, newblue;
	double factor_gt = (double)( 20.0 - getColorIntensity() ) / 10.0;
	double factor_lt = (double)( 10.0 - getColorIntensity() ) / 10.0;

	for ( int i = 0; i < num_colors; i++ )
	{
		newred   = d_colorMapRed[i];
		newgreen = d_colorMapGreen[i];
		newblue  = d_colorMapBlue[i];

		if ( getColorIntensity() > 10 )
		{
			newred   *= factor_gt;
			newgreen *= factor_gt;
			newblue  *= factor_gt;
		}
		else
		{
			newred   += ( 255 - newred   ) * factor_lt;
			newgreen += ( 255 - newgreen ) * factor_lt;
			newblue  += ( 255 - newblue  ) * factor_lt;
		}

		d_bmi.bmiColors[i].rgbRed = newred;
		d_bmi.bmiColors[i].rgbGreen = newgreen;
		d_bmi.bmiColors[i].rgbBlue = newblue;
	}
}

void TIFFOverlay::rowColToLP( double& row, double& col ) const
{
	double x, y;
  x = getBoundingRect().left();
  y = getBoundingRect().top();
	x += ( col * getBoundingRect().width() ) / (double)( d_imageWidth - 1 );
	y -= ( row * getBoundingRect().height() ) / (double)( d_imageLength - 1 );

	// Convert (x,y) to LP
	CoordinateTransforms::GndRefSystoLP( x, y );

	row = y;
	col = x;
}

UINT  TIFFOverlay::getNumImportantColors() const
{
	// Return 0 if not palette-based image
	if ( d_bitsPerSample > 8 )
	{
		return 0;
	}

	UINT numColors = 1 << d_bitsPerSample;
	int impColors;
	for ( impColors = 1; impColors < numColors; impColors++ )
	{
		if ( d_bmi.bmiColors[impColors - 1] == d_bmi.bmiColors[impColors] )
		{
			break;
		}
	}

	return impColors;
}

CString TIFFOverlay::photoInterpToString() const
{
	// Determine the photometric interpretation name
	switch ( d_photometricInterpretation )
	{
  case PHOTOMETRIC_MINISWHITE:
    return "Greyscale (Min is White)";
  case PHOTOMETRIC_MINISBLACK:
    return "Greyscale (Min is Black)";
  case PHOTOMETRIC_RGB:
    return "RGB Full-Color";
  case PHOTOMETRIC_PALETTE:
    return "Palette-Color";
  case PHOTOMETRIC_MASK:
    return "Mask";
  case PHOTOMETRIC_SEPARATED:
    return "Color Separations";
  case PHOTOMETRIC_YCBCR:
    return "YCBCR Color";
  case PHOTOMETRIC_CIELAB:
    return "CIELab";
  default:
    return "Unknown type";
  }
}

void TIFFOverlay::readMinMaxSampleValues( TIFF* pTIFF )
{
	// Get the maximum sample value
	TIFFGetField( pTIFF, TIFFTAG_MAXSAMPLEVALUE, &d_maxSampleValue );

	// Get the minimum sample value
	TIFFGetField( pTIFF, TIFFTAG_MINSAMPLEVALUE, &d_minSampleValue );
}

COLORREF TIFFOverlay::getRowColColor( long row, long col )
{
  ASSERT( NULL != d_pCache );
  BYTE* pScanline = d_pCache->getScanlineData( row );

  // Extract the appropriate value
  switch ( getBitsPerPixel() )
  {
  case 1:
  {
    BYTE currentByte  = pScanline[ col >> 3];
    BYTE bitToExtract = 7 - ( col % 8 );
    if ( currentByte & ( 1 << bitToExtract ) )
    {
      return RGB( d_colorMapRed[1], d_colorMapGreen[1], d_colorMapBlue[1] );
    }
    else
    {
      return RGB( d_colorMapRed[0], d_colorMapGreen[0], d_colorMapBlue[0] );
    }

    break;
  }
  case 4:
  {
    BYTE index = pScanline[ col / 2 ];
    if ( 0 == ( col % 2 ) )
    {
      index = ( index & 0xF0 ) >> 4;
    }
    else
    {
      index &= 0x0F;
    }
    return RGB( d_colorMapRed[index], d_colorMapGreen[index],
                d_colorMapBlue[index] );
    break;
  }
  case 8:
  {
    BYTE index = pScanline[ col ];
    return RGB( d_colorMapRed[index], d_colorMapGreen[index],
                d_colorMapBlue[index] );
    break;
  }
  case 16:
  {
    ASSERT( !isVertical() );

    int16* pData = reinterpret_cast<int16*>(pScanline);
    int16  elev  = pData[col];
    float min, max;
    getGlobalMinMaxSampleValue( min, max );
    BYTE greyVal = ( elev - min ) / ( max - min );
    return RGB( greyVal, greyVal, greyVal );
    break;
  }
  case 24:
    col *= 3;
    return RGB( pScanline[col], pScanline[col + 1], pScanline[col + 2] );
  }

  return 0;
}

bool TIFFOverlay::getElevation( long row, long col, float& elev ) const
{
  if ( row < 0 || row >= getImageHeight() )
  {
    return false;
  }

  if ( col < 0 || col >= getImageWidth() )
  {
    return false;
  }

  switch ( getBitsPerPixel() )
  {
  case 16:
  {
    int16* pMidScanline =
      reinterpret_cast<int16*>(d_pCache->getScanlineData( row ) );
    elev = pMidScanline[col];
    return ( ( SHRT_MIN + 1 ) < elev );
  }
  case 8:
  {
    BYTE* pMidScanline = d_pCache->getScanlineData( row );
    elev = 
      ( pMidScanline[col] / 255.0 ) * ( d_maxSampleValue - d_minSampleValue );
    elev += d_minSampleValue;
    return true;
  }
  }

  return false;
}

bool TIFFOverlay::getRowColSurfaceNormal( long row, long col, 
                                          ps_Vector& normal, 
                                          float& elev ) const
{   
  if ( 16 != getBitsPerPixel() )
  {
    return RasterOverlay::getRowColSurfaceNormal( row, col, normal, elev );
  }

  int16* pTopScanline = 
    reinterpret_cast<int16*>(d_pCache->getScanlineData( max(row - 1,0) ) );
  int16* pMidScanline =
    reinterpret_cast<int16*>(d_pCache->getScanlineData( row ) );
  int16* pBotScanline =
    reinterpret_cast<int16*>(d_pCache->getScanlineData( min(row + 1,
                                                        getImageHeight() ) ) );

  long leftCol = max( col - 1, 0 );
  long rightCol = min( ( getImageWidth() - 1 ), ( col + 1 ) );
  short e  = pMidScanline[col];
  short eL = pMidScanline[leftCol];
  short eR = pMidScanline[rightCol];
  short eT = pTopScanline[col];
  short eB = pBotScanline[col];

  if ( (SHRT_MIN + 1) >= e ) return false;
  if ( (SHRT_MIN + 1) >= eL ) eL = e;
  if ( (SHRT_MIN + 1) >= eR ) eR = e;
  if ( (SHRT_MIN + 1) >= eB ) eB = e;
  if ( (SHRT_MIN + 1) >= eT ) eT = e;

  elev = convertElevationToMeters( e );

  // Calculate the surface normal
  normal = ps_Vector( eL - eR, eT - eB,
                      getVerticalPixelScale() / d_verticalExaggeration );
  normal.normalize();

  return true;
}

CString TIFFOverlay::getDescription() const
{
  if ( NULL != d_description )
  {
    CString strDesc;
    strDesc += "<" + getFilenameWithoutPath() + "> ";
    strDesc += d_description;
    strDesc.TrimRight();
    return strDesc;
  }
  else
  {
    return RasterOverlay::getDescription();
  }
}