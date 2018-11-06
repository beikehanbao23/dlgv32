// TIFFOverlay.h - header file for TIFFOverlay class
//
// Developed by: Mike Childs
//      Started: 2/9/97
//

#ifndef _TIFFOVERLAY_H_
#define _TIFFOVERLAY_H_

#include "StdAfx.h"
#include "RasterOverlay.h"
#include "libgeotiff/libxtiff/xtiffio.h"

// Forward declaration
class TIFFPropertySheet;

class TIFFOverlay : public RasterOverlay
{
  friend class TIFFPropertyPage;

public:
	// Constructors/Destructors
	TIFFOverlay( CString& filename );
	virtual ~TIFFOverlay();

	// Overrides
	void draw( CDC* pDC, CRect* pClipRect = NULL );
  CString getDescription() const;
  long getImageHeight() const;
  long getImageWidth() const;
  bool isVertical() const;
	BOOL load();
	void showPropertiesDialog();
	void calculateBoundingRect();
  UINT getBitsPerPixel() const;

protected:
	// Overrides
	virtual void adjustPalette();
  virtual COLORREF getRowColColor( long row, long col );
  virtual void getMinMaxSampleValue( float& min, float& max ) const;
  virtual bool getElevation( long row, long col, float& elev ) const;
  virtual bool getRowColSurfaceNormal( long row, long col, ps_Vector& normal,
                                       float& elev ) const;

	// Helper functions
	void rowColToLP( double& row, double& col ) const;
	UINT getNumImportantColors() const;
  void readMinMaxSampleValues( TIFF* pTIFF );
  CString photoInterpToString() const;
  void getTIFFAreaToLoad( const Rectangle2D& rectInvalid, double& startRow,
                          double& endRow, double& startColumn,
                          double& endColumn ) const;

  // Vertical TIFF and shader data
  int16  d_minSampleValue;
  int16  d_maxSampleValue;

	// Data members
	TIFF*  tif;
  TIFFPropertySheet* d_pPropertySheet;

	// Data members to hold TIFF tags
	uint16 d_bitsPerSample;
	uint16 d_samplesPerPixel;
	char*  d_copyright;
	char*  d_datetime;
	char*  d_description;
	uint32 d_imageLength;
	uint32 d_imageWidth;
	uint16 d_photometricInterpretation;
	uint32 d_rowsPerStrip;

	// Data members to hold non-tags
	BYTE d_colorMapRed[256];
	BYTE d_colorMapGreen[256];
	BYTE d_colorMapBlue[256];

  // Buffering class
  class TIFFCache
  {
   public:
    // Construction/Destruction
    TIFFCache( TIFF* pTIFF, int rowsPerStrip, UINT cacheSize = 32 );
    ~TIFFCache();

    // Data Access members
    BYTE* getScanlineData( long row );

   private:
    // Internal buffer class
    class TIFFStripBuffer
    {
     public:
       TIFFStripBuffer();
       ~TIFFStripBuffer();

       bool isRowInStrip( int row ) const;
       tdata_t getStripData();
       void setStripData( tdata_t pStrip );
       void setStripLocation( int startRow, int endRow );

     protected:
       tdata_t d_pStrip;
       int     d_startRow;
       int     d_endRow;
    };

    // Data members
    TIFFStripBuffer* d_pStrips;
    TIFF*            d_pTIFF;
    int              d_rowsPerStrip;
    UINT             d_cacheSize;
    int              d_stripSize;
    int              d_scanlineSize;
    };
    TIFFCache* d_pCache;
};

inline void
TIFFOverlay::getMinMaxSampleValue( float& min, float& max ) const
{
  min = static_cast<float>( d_minSampleValue );
  max = static_cast<float>( d_maxSampleValue );
}

inline long
TIFFOverlay::getImageHeight() const
{
  return d_imageLength;
}

inline long
TIFFOverlay::getImageWidth() const
{
  return d_imageWidth;
}

inline bool
TIFFOverlay::TIFFCache::TIFFStripBuffer::isRowInStrip( int row ) const
{
  return ( row >= d_startRow && row <= d_endRow );
}

inline tdata_t
TIFFOverlay::TIFFCache::TIFFStripBuffer::getStripData()
{
  return d_pStrip;
}

inline void
TIFFOverlay::TIFFCache::TIFFStripBuffer::setStripData( tdata_t pStrip )
{
  d_pStrip = pStrip;
}

inline void
TIFFOverlay::TIFFCache::TIFFStripBuffer::setStripLocation( int startRow, 
                                                           int endRow )
{
  d_startRow = startRow;
  d_endRow = endRow;
}

inline UINT
TIFFOverlay::getBitsPerPixel() const
{
  return ( d_bitsPerSample * d_samplesPerPixel );
}

inline bool
TIFFOverlay::isVertical() const
{
  return ( d_minSampleValue != d_maxSampleValue );
}

#endif	