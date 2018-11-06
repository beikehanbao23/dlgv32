// InterpolatedIntensity.cpp - implementation for InterpolatedIntensity class
//
// Developed by: Mike Childs
//      Started: 2/24/98

#include "InterpolatedIntensity.h"

// Construction
InterpolatedIntensity::InterpolatedIntensity( unsigned short width,
                                              unsigned short height )
: d_width(width), d_height(height)                                              
{
  d_pIntensityCache = new IntensityCacheEntry[d_width * d_height];
  invalidateIntensityCache();
}

// Destruction
InterpolatedIntensity::~InterpolatedIntensity()
{
  delete[] d_pIntensityCache;
}

bool InterpolatedIntensity::getCachedIntensity( long row, long col, 
                                                BYTE& inten, float& elev )
{
  ASSERT( NULL != d_pIntensityCache );

  // Calculate the offset of the entry
  unsigned int offset = ( row % d_width ) * d_height + ( col % d_width );

  // Check to see if the entry is already in the cache
  if ( d_pIntensityCache[offset].d_row == row &&
       d_pIntensityCache[offset].d_col == col )
  {
    // The entry matched
    inten = d_pIntensityCache[offset].d_intensity;
    elev = d_pIntensityCache[offset].d_elev;
    return true;
  }

  // Intensity not in cache, read it and put it in cache
  if ( getRowColIntensity( row, col, d_pIntensityCache[offset].d_intensity, 
                           d_pIntensityCache[offset].d_elev ) )
  {
    d_pIntensityCache[offset].d_row = row;
    d_pIntensityCache[offset].d_col = col;
    inten = d_pIntensityCache[offset].d_intensity;
    elev = d_pIntensityCache[offset].d_elev;        
    return true;
  }

  return false;
}

bool InterpolatedIntensity::getInterpolatedIntensity( float row, float col, 
                                                      BYTE& inten,
                                                      float& elev )
{
  // Get the truncated row column coordinates
  long left   = max( 0, static_cast<long>( col ) );
  long right  = left + 1;
  long top    = max( 0, static_cast<long>( row ) );
  long bottom = top + 1;    

  // Get the colors of the four surrounding pixels
  BYTE tlInten(0), trInten(0), brInten(0), blInten(0);
  float tlElev, trElev, brElev, blElev;
  if ( !getCachedIntensity( top, left, tlInten, tlElev ) )
  {
    return false;
  }

  if ( !getCachedIntensity( top, right, trInten, trElev ) )
  {
    trInten = tlInten;
    trElev = tlElev;
  }

  if ( !getCachedIntensity( bottom, right, brInten, brElev ) )
  {
    brInten = tlInten;
    brElev = tlElev;
  }

  if ( !getCachedIntensity( bottom, left, blInten, blElev ) )
  {
    blInten = tlInten;
    blElev = tlElev;
  }

  // Get the t and u values
  float t = ( col - left );
  float u = ( bottom - row );

  // Interpolate the elevations
  elev = bilinearlyInterpolate( t, u, tlElev, trElev, brElev, blElev );

  // Interpolate the intensities
  inten = bilinearlyInterpolate( t, u, tlInten, trInten, brInten, blInten );

  return true;
}

void InterpolatedIntensity::invalidateIntensityCache()
{
  for ( int i = 0; i < ( d_width * d_height ); i++ )
  {
    d_pIntensityCache[i].d_row = -1;
    d_pIntensityCache[i].d_col = -1;
  }
}