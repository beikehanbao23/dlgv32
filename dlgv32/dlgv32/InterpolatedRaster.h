// InterpolatedRaster.h - interface for InterpolatedRaster class
//
// Developed by: Mike Childs
//      Started: 2/15/98

#ifndef _INTERPOLATEDRASTER_H_
#define _INTERPOLATEDRASTER_H_

#include "StdAfx.h"

class InterpolatedRaster
{
public:
  InterpolatedRaster( unsigned short width, unsigned short height );
  ~InterpolatedRaster();

protected:
  COLORREF getInterpolatedColor( float row, float col );
  /* Returns the color found by bilinearly interpolating the colors
     at each of the four points surrounding the <row>, <col> given */

  virtual COLORREF getRowColColor( long row, long col ) = 0;
  /* This is the only function that must be overridden to provide
     support for the bilinear interpolation of raster images.  This
     function returns the color at the coordinates ( <row>, <col> ) */

  void invalidateColorCache();
  /* Invalidates the cache of colors */

  // Color caching function
  COLORREF getCachedColor( long row, long col );

private:
  // Interpolation function
  BYTE bilinearlyInterpolate( float t, float u, BYTE c1, BYTE c2, BYTE c3,
                              BYTE c4 );
    
  // Color cache
  struct ColorCacheEntry
  {
    long d_row;
    long d_col;
    COLORREF d_color;
  };
  ColorCacheEntry* d_pColorCache;
  unsigned short d_cacheWidth, d_cacheHeight;
};

inline BYTE
InterpolatedRaster::bilinearlyInterpolate( float t, float u,
                                           BYTE c1, BYTE c2,
                                           BYTE c3, BYTE c4 )
{
  ASSERT( 0 <= t && 1 >= t && 0 <= u && 1 >= u );
  float temp1 = c4 + ( c3 - c4 ) * t;
  return static_cast<BYTE>( temp1 + ( c1 + ( c2 - c1 ) * t - temp1 ) * u );
}

#endif