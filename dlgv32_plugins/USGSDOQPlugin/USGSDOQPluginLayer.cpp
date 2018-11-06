// Brian Maddox - USGS MCMC SES - bmaddox@usgs.gov
// USGSDOQPluginLayer.cpp: implementation of the USGSDOQPluginLayer class.

#include "USGSDOQPluginLayer.h"
#include "ImageLib/ImageCommon.h"
#include "ImageLib/RGBPixel.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

USGSDOQPluginLayer::USGSDOQPluginLayer(int layerID, const char* strFilename,
                                       HINSTANCE hInstance)
 : RasterPluginLayer(layerID, strFilename, hInstance),
   _projection(UNKNOWN_PROJSYS), _datum(UNKNOWN_DATUM), _unit(UNKNOWN_UNIT),
   _zone(0), _samplesperpixel(0)
{
//  _lastrow = new long int;
  _lowerbound = new long int;
  _upperbound = new long int;
}

USGSDOQPluginLayer::~USGSDOQPluginLayer()
{
  try
  {
    delete indoq;
//    delete _lastrow;
    delete _lowerbound;
    delete _upperbound;
//    delete [] array;
    for (int loopc = 0; loopc < 10; loopc++)
      delete [] _cache[loopc];
  }
  catch (...)
  {
  }
}

void USGSDOQPluginLayer::getProjection(PROJSYS& projSys, DATUM& datum,
                                       UNIT& unit, int& zone,
                                       double* pParams) const
{
  projSys = _projection;
  datum = _datum;
  unit = _unit;
  zone = _zone;
}


void USGSDOQPluginLayer::getBoundingRect(double& left, double& bottom,
                                         double& right, double& top) const
{
  left = ulx;
  right = ulx + (_width * _resolution);
  top = uly;
  bottom = uly - (_height * _resolution);
}

long USGSDOQPluginLayer::getImageHeight() const
{
  return _height;
}

long USGSDOQPluginLayer::getImageWidth() const
{
  return _width;
}

bool USGSDOQPluginLayer::load()
{
  std::string _coordsystem;
  std::string _tdatum;
  std::string _units;
  std::string filename = getFilename();
  std::string _tbandorg;
  std::string quadname, quadrant, quadstate;//strings for description
  try
  {
    if (!(indoq = new(std::nothrow)
          USGSImageLib::DOQImageIFile(filename)))
      throw std::bad_alloc();
    if (!indoq->good())
      throw USGSImageLib::ImageException(IMAGE_FILE_OPEN_ERR);

    // Now go ahead and parse some stuff from the header and store it
    indoq->getSamples(_width);
    indoq->getLines(_height);
    indoq->getXOrigin(ulx);
    indoq->getYOrigin(uly);
    indoq->getHorizontalResolution(_resolution);
    indoq->getHorizontalCoordinateSystem(_coordsystem);
    if (!USGSImageLib::cmp_nocase(_coordsystem, std::string("UTM")))
      _projection = UTM;
    else if (!USGSImageLib::cmp_nocase(_coordsystem, std::string("SPCS")))
      _projection = SPCS;
    indoq->getHorizontalDatum(_tdatum);
    if (!USGSImageLib::cmp_nocase(_tdatum, std::string("NAD83")))
      _datum = NAD83;
    else if (!USGSImageLib::cmp_nocase(_tdatum, std::string("NAD27")))
      _datum = NAD27;

    // Now determine the units of the DOQ
    indoq->getHorizontalUnits(_units);
    if (!USGSImageLib::cmp_nocase(_units, std::string("METERS")))
      _unit = METERS;
    else if (!USGSImageLib::cmp_nocase(_units, std::string("FEET")))
      _unit = US_FEET;
    else if (!USGSImageLib::cmp_nocase(_units, std::string("SURVEY FEET")))
      _unit = US_FEET;
    else if (!USGSImageLib::cmp_nocase(_units, std::string("RADIANS")))
      _unit = RADIANS;
    else if (!USGSImageLib::cmp_nocase(_units, std::string("ARC SECONDS")))
      _unit = ARC_SECONDS;
    else if (!USGSImageLib::cmp_nocase(_units, 
                                       std::string("INTERNATIONAL FEET")))
      _unit = INTERNATIONAL_FEET;

    indoq->getCoordinateZone(_zone);
    indoq->getSamplesPerPixel(_samplesperpixel);

    // Initialize the scanline cache
//    if (!(array = new(std::nothrow) unsigned char[_width * _samplesperpixel]))
//      throw std::bad_alloc();
    for (int loopc = 0; loopc < 10; loopc++)
      _cache[loopc] = new unsigned char[_width * _samplesperpixel];

    // perform the initial scanline caching
    cacheScanlines(0);

//    *_lastrow = 0;
//    indoq->getRawScanline(0, array);

	//get the description
	indoq->getQuadName(quadname);
    indoq->getQuadrant(quadrant);
    indoq->getState(quadstate, 1);
    description = quadname + std::string(" ") + quadrant + std::string(", ")
             + quadstate;
    return true;
  }
  catch (...)
  {
    return false;
  }
}

bool USGSDOQPluginLayer::getRowColColor(long row, long col, 
                                        unsigned char& r, unsigned char& g,
                                        unsigned char& b) const
{
  int cachepos; // which cacheposition we use

  if ( (row < 0) || (row >= _height) || (col < 0) || (col >= _width) )
    return false;

  try
  {
    // If the scanline is already cached, don't do anything
    if ( !( (row >= *_lowerbound) && (row <= *_upperbound) ) )
      cacheScanlines(row);

    cachepos = row - *_lowerbound;

    if (_samplesperpixel == 1) // handle greyscale case
    {
//      r = g = b = array[col];
      r = g = b = _cache[cachepos][col];
    }
    else
    {
//      r = array[col * _samplesperpixel];
//      g = array[col * _samplesperpixel + 1];
//      b = array[col * _samplesperpixel + 2];
      r = _cache[cachepos][col * _samplesperpixel];
      g = _cache[cachepos][col * _samplesperpixel + 1];
      b = _cache[cachepos][col * _samplesperpixel + 2];
    }

    return true;
  }
  catch (...)
  {
    return false;
  }
}

const char* USGSDOQPluginLayer::getDescription() const
{

  try
  {
    return description.c_str();
  }
  catch (...)
  {
    return "";
  }
}

// This function starts at rowstart and caches the next 10 scanlines.  Return
// false instead of throwing an exception.
bool USGSDOQPluginLayer::cacheScanlines(long rowstart) const
{
  int rowcount;
  long _currrow;

  // This is to make sure we don't try to blow past the image bounds.
  if (rowstart <= 9) // just cache from 0 to 9
    rowstart = 0;
  else if (rowstart >= _height - 10)
    rowstart = _height - 10;
  // Here, the scanlines run 0 to height - 1, subtracting 9 since we also 
  // cache the first scanline gives us height - 10

  try
  {
    _currrow = rowstart;

    for (rowcount = 0; rowcount < 10; rowcount++)
    {
      indoq->getRawScanline(_currrow++, _cache[rowcount]);
    }

    // if we got here, modify the lower and upperbounds accordingly
    *_lowerbound = rowstart;
    *_upperbound = _currrow - 1;

    return true;
  }
  catch(...)
  {
    return false;
  }
}

void USGSDOQPluginLayer::showPropertiesDialog() const
{
	//Added for Doq Meta Data dialog - CBB
	//Initialize common controls, create dialog and pass it the filename as a LPARAM
	INITCOMMONCONTROLSEX ccom; //common control initializer
	
	ccom.dwSize = sizeof (LPINITCOMMONCONTROLSEX);
	ccom.dwSize = ICC_WIN95_CLASSES;
	
	::InitCommonControlsEx(&ccom);
	::CreateDialogParam( getInstance(), MAKEINTRESOURCE( IDD_PROPERTIES_DIALOG  ),
                        ::GetActiveWindow(), (DLGPROC)PropertiesDialogProc, 
						(LPARAM)(getFilename().c_str()));
}

BOOL CALLBACK PropertiesDialogProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    //Handles meta data dialog messages - CBB
	HWND hwnd2;            //handle to the edit control
	std::ifstream * file;    //file stream for reading in the header
	std::string *doqfile;   //file name
	char * data;           //buffer for text
	USGSImageLib::DOQImageIFile* indoq;   //temp doq for header size
	long bytecount;		   //size of header
	int counter;           //counter for loops
	static bool firstpaint; //just overload edit selection once
	RECT clientrect;   //the width and the height for resizing controls
	switch (uMsg)
	{
	case WM_INITDIALOG:
		//get the handle of the edit control
		hwnd2 = ::GetDlgItem(hwnd, IDC_EDIT1);
		//get the filename
		doqfile = new std::string((char *) lParam);
		//get the header size (not the best way, but easy)
		indoq = new USGSImageLib::DOQImageIFile ((*doqfile));
		indoq->getByteCount(bytecount);
		delete indoq;
		//create and init the buffer
		data = new char [bytecount +1];
		for (counter = 0; counter < bytecount+1; counter++)
			data[counter] = '\0';
		//open the doq and read in the header
		file = new ifstream(doqfile->c_str(), std::ios::in | std::ios::binary);
		file->read(data, bytecount);
		file->close();
		delete file;
		delete doqfile;
		//find and replace *\r with \r\n to put in end of lines
		for (counter = 0; counter < bytecount+1; counter++)
		{
			if (data[counter] == '*')
			{
				data[counter] = '\r';
				data[counter+1] = '\n';
			}
		}
		
		//send the buffer to the edit box
		::SendMessage( hwnd2, WM_SETTEXT, (WPARAM)0, (LPARAM)data);
		firstpaint = true; //set first paint
		delete [] data; //clean data
		return false;  //process default initdialog
	case WM_SIZE:
		clientrect.right = LOWORD(lParam);
		clientrect.bottom = HIWORD(lParam) - 30;
		clientrect.top = 0;
		clientrect.left = 0;
		//resize the text box
		hwnd2 = ::GetDlgItem(hwnd, IDC_EDIT1);
		//::SendMessage(hwnd2, WM_SIZE, (WPARAM)0, (LPARAM)&temp );
		::SetWindowPos(hwnd2, hwnd, 0, 0, clientrect.right, clientrect.bottom, SWP_NOZORDER);
		//resize the button
		hwnd2 = ::GetDlgItem(hwnd, IDC_OK);
		::SetWindowPos(hwnd2, hwnd, clientrect.right/2 - 30, clientrect.bottom, 60, 30, SWP_NOZORDER);

		return false;

	case WM_PAINT:
		if (firstpaint)
		{
			//get the hwnd of the edit box
			hwnd2 = ::GetDlgItem(hwnd, IDC_EDIT1);
			//tell the edit to stop selecting what it is selecting
			::SendMessage( hwnd2, EM_SETSEL, (WPARAM)-1, (LPARAM)-1 );
			firstpaint = false; //make sure that we don't do this again
		}
		return false; //process default paint after overload
	case WM_COMMAND://proccess ok button
		if (LOWORD(wParam) == IDC_OK)
			::PostMessage(hwnd, WM_CLOSE, 0, 0);
		return false;
	case WM_CLOSE:
	case WM_DESTROY:
		::DestroyWindow(hwnd); //destory dialog
	}
	return false; //process default messages
}
 