// InterpolatedIntensity.h - interface for InterpolatedIntensity class
//
// Developed by: Mike Childs
//      Started: 2/15/98

#ifndef _INTERPOLATEDINTENSITY_H_
#define _INTERPOLATEDINTENSITY_H_

#include "StdAfx.h"

class InterpolatedIntensity
{
public:
  // Construction
  InterpolatedIntensity( unsigned short width, unsigned short height );

  // Destruction
  virtual ~InterpolatedIntensity();

protected:
  bool getInterpolatedIntensity( float row, float col, 
                                 BYTE& inten, float& elev );
  /* Returns the intensity found by bilinearly interpolating the intensity
     at each of the four points surrounding the <row>, <col> given.  Note
     that the intensity is scaled between 0 and 255 to facilitate 
     calculation */

  virtual bool getRowColIntensity( long row, long col, 
                                   BYTE& inten, float& elev ) = 0;
  /* This is the only function that must be overridden to provide
     support for the bilinear interpolation of raster images.  This
     function finds the intensity at the coordinates ( <row>, <col> ) 
     and returns true or returns false if the intensity was undefined
     at that point */

  void invalidateIntensityCache();
  /* Invalidates the cache of intensities */

  // Color caching function
  bool getCachedIntensity( long row, long col, BYTE& inten, float& elev );

private:
  // Interpolation function
  BYTE bilinearlyInterpolate( float t, float u, BYTE c1, BYTE c2,
                              BYTE c3, BYTE c4 );
  float bilinearlyInterpolate( float t, float u, float e1, float e2,
                               float e3, float e4 );
    
  // Data members
  unsigned short d_width;
  unsigned short d_height;

  // Intensity cache entry
  struct IntensityCacheEntry
  {
    long  d_row;
    long  d_col;
    BYTE  d_intensity;
    float d_elev;
  };
  IntensityCacheEntry* d_pIntensityCache;
};

inline BYTE
InterpolatedIntensity::bilinearlyInterpolate( float t, float u,
                                              BYTE c1, BYTE c2,
                                              BYTE c3, BYTE c4 )
{
  ASSERT( 0 <= t && 1 >= t && 0 <= u && 1 >= u );
  float temp1 = c4 + ( c3 - c4 ) * t;
  return static_cast<BYTE>( temp1 + ( c1 + ( c2 - c1 ) * t - temp1 ) * u );
}

inline float
InterpolatedIntensity::bilinearlyInterpolate( float t, float u,
                                              float e1, float e2,
                                              float e3, float e4 )
{
  ASSERT( 0 <= t && 1 >= t && 0 <= u && 1 >= u );
  float temp1 = e4 + ( e3 - e4 ) * t;
  return ( temp1 + ( e1 + ( e2 - e1 ) * t - temp1 ) * u );
}

#endif