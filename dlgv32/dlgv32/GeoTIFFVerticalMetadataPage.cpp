// GeoTIFFVerticalMetadataPage.cpp : implementation file
//

#include "stdafx.h"
#include "dlgv32.h"
#include "GeoTIFFOverlay.h"
#include "GeoTIFFVerticalMetadataPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GeoTIFFVerticalMetadataPage property page

IMPLEMENT_DYNCREATE(GeoTIFFVerticalMetadataPage, CPropertyPage)

GeoTIFFVerticalMetadataPage::GeoTIFFVerticalMetadataPage() 
: CPropertyPage(GeoTIFFVerticalMetadataPage::IDD)
{
	//{{AFX_DATA_INIT(GeoTIFFVerticalMetadataPage)
	d_strMaxElevation = _T("");
	d_strMinElevation = _T("");
	d_strVerticalCitation = _T("");
	d_strVerticalDatum = _T("");
	d_strVerticalUnits = _T("");
	//}}AFX_DATA_INIT
}

GeoTIFFVerticalMetadataPage::~GeoTIFFVerticalMetadataPage()
{
}

void
GeoTIFFVerticalMetadataPage::setOverlay( GeoTIFFOverlay* pOverlay )
{
  // Set the min and max elevation fields
  float min, max;
  pOverlay->getMinMaxSampleValue( min, max );
  d_strMinElevation.Format( "%g %s", min * pOverlay->d_verticalSpatialRes, 
                            pOverlay->getVerticalUnitString() );
  d_strMaxElevation.Format( "%g %s", max * pOverlay->d_verticalSpatialRes, 
                            pOverlay->getVerticalUnitString() );

  // Get the vertical datum field
  switch ( pOverlay->d_verticalCSTypeGeoKey )
  {
  case VertCS_North_American_Vertical_Datum_1929:
    d_strVerticalDatum = "NGVD29";
    break;
  case VertCS_North_American_Vertical_Datum_1988:
    d_strVerticalDatum = "NGVD88";
    break;
  default:
    d_strVerticalDatum.Format( "Unknown Datum Code: %d", 
                               pOverlay->d_verticalCSTypeGeoKey );
    break;
  }

  // Set the other vertical fields
  d_strVerticalCitation = pOverlay->d_verticalCitationGeoKey;
  d_strVerticalUnits = pOverlay->getVerticalUnitString();
}

void GeoTIFFVerticalMetadataPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GeoTIFFVerticalMetadataPage)
	DDX_Text(pDX, IDC_GEOTIFF_MAX_ELEVATION, d_strMaxElevation);
	DDX_Text(pDX, IDC_GEOTIFF_MIN_ELEVATION, d_strMinElevation);
	DDX_Text(pDX, IDC_GEOTIFF_VERTICAL_CITATION, d_strVerticalCitation);
	DDX_Text(pDX, IDC_GEOTIFF_VERTICAL_DATUM, d_strVerticalDatum);
	DDX_Text(pDX, IDC_GEOTIFF_VERTICAL_UNITS, d_strVerticalUnits);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GeoTIFFVerticalMetadataPage, CPropertyPage)
	//{{AFX_MSG_MAP(GeoTIFFVerticalMetadataPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GeoTIFFVerticalMetadataPage message handlers
