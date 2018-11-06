// Brian Maddox - USGS MCMC SES - bmaddox@usgs.gov
// USGSDOQPluginLayer.h: interface for the USGSDOQPluginLayer class.


#ifndef _USGSDOQPLUGINLAYER_H_
#define _USGSDOQPLUGINLAYER_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windowsx.h>
#include "RasterPluginLayer.h"
#include "ImageLib/DOQImageIFile.h"
#include "ImageLib/ImageIFile.h"
#include "ImageLib/ImageException.h"
#include "resource.h"
#include <commctrl.h>
#include <string>
#include <fstream>

// Procedure for handling messages for the metadata dialog
BOOL CALLBACK PropertiesDialogProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

class USGSDOQPluginLayer : public RasterPluginLayer  
{
public:
	USGSDOQPluginLayer(int layerID, const char* strFilename, 
                     HINSTANCE hInstance);
	virtual ~USGSDOQPluginLayer();

  void getProjection(PROJSYS& projSys, DATUM& datum, UNIT& unit, int& zone,
                     double* pParams) const;
  void getBoundingRect(double& left, double& bottom, double& right,
                       double& top) const;
  long getImageHeight() const;
  long getImageWidth()  const;
  bool load();

  bool getRowColColor(long row, long col, unsigned char& r, unsigned char& g,
                      unsigned char& b) const;

  const char* getDescription() const;

  //overloaded showPropertiesDialog()
  //handles creation of doq metadata dialog box
  virtual void showPropertiesDialog() const;

private:
	bool cacheScanlines(long int rowstart) const;

  USGSImageLib::DOQImageIFile* indoq;

  long int       _height;
  long int       _width;
  double         ulx, uly;
  float          _resolution;
  PROJSYS        _projection;
  DATUM          _datum;
  UNIT           _unit;
  int            _zone;
  int            _samplesperpixel;
  long int*      _lowerbound;
  long int*      _upperbound;
  unsigned char* _cache[10];
  std::string    description;
  // For the scanline cache
//  long int*      _lastrow;
//  unsigned char* array;
};

#endif
