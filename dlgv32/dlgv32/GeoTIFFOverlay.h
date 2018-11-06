// GeoTIFFOverlay.h - header file for GeoTIFFOverlay class
//
// Developed by: Mike Childs
//      Started: 2/9/97
//

#ifndef _GEOTIFFOVERLAY_H_
#define _GEOTIFFOVERLAY_H_

#include "StdAfx.h"
#include "TIFFOverlay.h"
#include "libgeotiff/geotiffio.h"
#include "CoordinateTransforms.h"

class GeoTIFFOverlay : public TIFFOverlay
{
  friend class GeoTIFFPropertyPage;
  friend class GeoTIFFVerticalMetadataPage;

public:
	// Constructors/Destructors
	GeoTIFFOverlay( CString& filename );
	virtual ~GeoTIFFOverlay();

	// Overrides
  bool isVertical() const;
	BOOL load();
	void showPropertiesDialog();
	void calculateBoundingRect();

  // Informational
  BOOL notGeoTIFF();

protected:
	// Data members
	int     d_version[3];
	double* d_modelTiePoint;
	uint16  d_modelTiePointCount;
	double* d_pixelScale;
	uint16  d_pixelScaleCount;
	uint16  d_modelTypeGeoKey;
	uint16  d_rasterTypeGeoKey;
  uint16  d_verticalCSTypeGeoKey;
  uint16  d_verticalUnitsGeoKey;
	char*   d_citationGeoKey;
	char*   d_PCScitationGeoKey;
  char*   d_verticalCitationGeoKey;
  BOOL    d_notGeoTIFF;

  // Helper functions
  CString modelTypeToString() const;

  // Overrides of vertical stuff
  virtual CString getVerticalUnitString() const;

private:
  bool readModelTiePoints( TIFF* pTIFF );
  bool readPixelScale( TIFF* pTIFF );
};

inline BOOL
GeoTIFFOverlay::notGeoTIFF()
{
  return d_notGeoTIFF;
}

#endif