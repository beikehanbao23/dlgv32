// GeoTIFFPropertyPage.cpp : implementation file
//

#include "stdafx.h"
#include "dlgv32.h"
#include "GeoTIFFPropertyPage.h"
#include "GeoTIFFOverlay.h"
#include "libgeotiff/geovalues.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GeoTIFFPropertyPage property page

IMPLEMENT_DYNCREATE(GeoTIFFPropertyPage, CPropertyPage)

GeoTIFFPropertyPage::GeoTIFFPropertyPage() 
: CPropertyPage(GeoTIFFPropertyPage::IDD)
{
	//{{AFX_DATA_INIT(GeoTIFFPropertyPage)
	d_strGeoPixelScale = _T("");
	d_strGeoTiepoint = _T("");
	d_strModelType = _T("");
	d_strPCSCitation = _T("");
	d_strRasterType = _T("");
	d_strProjection = _T("");
	//}}AFX_DATA_INIT
}

GeoTIFFPropertyPage::GeoTIFFPropertyPage( GeoTIFFOverlay* pGeoTIFF )
: CPropertyPage(GeoTIFFPropertyPage::IDD)
{
  // Do nothing if the overlay pointer is NULL
  if ( NULL == pGeoTIFF )
  {
    return;
  }

  // Account for NULL values in PCS Citation
  if ( NULL != pGeoTIFF->d_PCScitationGeoKey )
  {
    d_strPCSCitation = pGeoTIFF->d_PCScitationGeoKey;

    // Convert all line feeds in the citation string to control-line feeds
    CString strTemp;
    int pos;
    while ( -1 != ( pos = d_strPCSCitation.Find( '\n' ) ) )
    {
      strTemp += d_strPCSCitation.Left( pos );
      strTemp += "\r\n";
      d_strPCSCitation = 
        d_strPCSCitation.Right( d_strPCSCitation.GetLength() - pos - 1 );
    }
    d_strPCSCitation = strTemp + d_strPCSCitation;
  }
  else
  {
    d_strPCSCitation = _T("None Given");
  }

  // Get the pixel scale
  if ( pGeoTIFF->d_pixelScaleCount >= 1 )
  {
    d_strGeoPixelScale.Format( "( %g, %g, %g )", pGeoTIFF->d_pixelScale[0],
                               pGeoTIFF->d_pixelScale[1],
                               pGeoTIFF->d_pixelScale[2] );
  }
  else
  {
    d_strGeoPixelScale = _T("None Given");
  }

  // Get the model tiepoint
  if ( pGeoTIFF->d_modelTiePointCount >= 1 )
  {
    d_strGeoTiepoint.Format( "( %.0f, %.0f, %.0f ) --> ( %.0f, %.0f, %.0f )", 
                             pGeoTIFF->d_modelTiePoint[0],
                             pGeoTIFF->d_modelTiePoint[1],
                             pGeoTIFF->d_modelTiePoint[2],
                             pGeoTIFF->d_modelTiePoint[3],
                             pGeoTIFF->d_modelTiePoint[4],
                             pGeoTIFF->d_modelTiePoint[5] );
  }
  else
  {
    d_strGeoTiepoint = _T("None Given");
  }

  d_strModelType = pGeoTIFF->modelTypeToString();

  // Get the raster type
  if ( RasterPixelIsArea == pGeoTIFF->d_rasterTypeGeoKey )
  {
    d_strRasterType = _T("Pixel is Area");
  }
  else if ( RasterPixelIsPoint == pGeoTIFF->d_rasterTypeGeoKey )
  {
    d_strRasterType = _T("Pixel is Point");
  }
  else
  {
    d_strRasterType.Format( "Invalid GeoKey: %d", 
                            pGeoTIFF->d_rasterTypeGeoKey );
  }

  // Get the projection
  d_strProjection = pGeoTIFF->getNativeProjection()->toString().c_str();
}

GeoTIFFPropertyPage::~GeoTIFFPropertyPage()
{
}

void GeoTIFFPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GeoTIFFPropertyPage)
	DDX_Text(pDX, IDC_GEOTIFF_GEOPIXELSCALE, d_strGeoPixelScale);
	DDX_Text(pDX, IDC_GEOTIFF_GEOTIEPOINT, d_strGeoTiepoint);
	DDX_Text(pDX, IDC_GEOTIFF_MODELTYPE, d_strModelType);
	DDX_Text(pDX, IDC_GEOTIFF_PCSCITATION, d_strPCSCitation);
	DDX_Text(pDX, IDC_GEOTIFF_RASTERTYPE, d_strRasterType);
	DDX_Text(pDX, IDC_GEOTIFF_PROJECTION, d_strProjection);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GeoTIFFPropertyPage, CPropertyPage)
	//{{AFX_MSG_MAP(GeoTIFFPropertyPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GeoTIFFPropertyPage message handlers
