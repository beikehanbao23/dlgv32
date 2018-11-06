// InterpolatedRaster.cpp - implementation for InterpolatedRaster class
//
// Developed by: Mike Childs
//      Started: 2/15/98

#include "InterpolatedRaster.h"
#include <math.h>

InterpolatedRaster::InterpolatedRaster(unsigned short width, 
                                       unsigned short height )
: d_cacheWidth(width), d_cacheHeight(height)
{
  d_pColorCache = new ColorCacheEntry[width * height];
  invalidateColorCache();
}

InterpolatedRaster::~InterpolatedRaster()
{
  delete[] d_pColorCache;
}

COLORREF InterpolatedRaster::getCachedColor( long row, long col )
{
  ASSERT( NULL != d_pColorCache );

  // Calculate the offset of the entry
  unsigned int offset = ( row % d_cacheWidth ) * d_cacheHeight +
                        ( col % d_cacheWidth );

  // Check to see if the entry is already in the cache
  if ( d_pColorCache[offset].d_row == row &&
       d_pColorCache[offset].d_col == col )
  {
    return d_pColorCache[offset].d_color;
  }

  // Intensity not in cache, read it and put it in cache
  d_pColorCache[offset].d_color = getRowColColor( row, col );
  d_pColorCache[offset].d_row = row;
  d_pColorCache[offset].d_col = col;
  return d_pColorCache[offset].d_color;
}

COLORREF InterpolatedRaster::getInterpolatedColor( float row, float col )
{
  // Get the truncated row column coordinates
  long left   = max( 0, static_cast<long>( col ) );
  long right  = left + 1;
  long top    = max( 0, static_cast<long>( row ) );
  long bottom = top + 1;    

  // Get the colors of the four surrounding pixels
  COLORREF tlColor = getCachedColor( top, left );
  COLORREF trColor = getCachedColor( top, right );
  COLORREF brColor = getCachedColor( bottom, right );
  COLORREF blColor = getCachedColor( bottom, left );

  // Get the t and u values
  float t = ( col - left );
  float u = ( bottom - row );

  BYTE r = bilinearlyInterpolate( t, u, 
                                  GetRValue( tlColor ),
                                  GetRValue( trColor ),
                                  GetRValue( brColor ),
                                  GetRValue( blColor ) );
  BYTE g = bilinearlyInterpolate( t, u, 
                                  GetGValue( tlColor ),
                                  GetGValue( trColor ),
                                  GetGValue( brColor ),
                                  GetGValue( blColor ) );
  BYTE b = bilinearlyInterpolate( t, u, 
                                  GetBValue( tlColor ),
                                  GetBValue( trColor ),
                                  GetBValue( brColor ),
                                  GetBValue( blColor ) );

  return RGB( r, g, b );
}

void
InterpolatedRaster::invalidateColorCache()
{
  for ( int i = 0; i < ( d_cacheWidth * d_cacheHeight ); i++ )
  {
    d_pColorCache[i].d_row = -1;
    d_pColorCache[i].d_col = -1;
  }
}