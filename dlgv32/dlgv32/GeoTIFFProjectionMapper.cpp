// GeoTIFFProjectionMapper.cpp - implementation of GeoTIFFProjectionMapper class
//
// Developed by: Mike Childs
//      Started: 3/18/98

#include "GeoTIFFProjectionMapper.h"
#include "libgeotiff/geovalues.h"
#include "libgeotiff/libxtiff/xtiffio.h"

// Projection includes
#include "ProjectionLib/AlaskaConformalProjection.h"
#include "ProjectionLib/AlbersConicProjection.h"
#include "ProjectionLib/AzimuthalEquidistantProjection.h"
#include "ProjectionLib/EquidistantConicProjection.h"
#include "ProjectionLib/EquirectangularProjection.h"
#include "ProjectionLib/GeographicProjection.h"
#include "ProjectionLib/GnomonicProjection.h"
#include "ProjectionLib/HotineObliqueMercatorProjection.h"
#include "ProjectionLib/LambertAzimuthalProjection.h"
#include "ProjectionLib/LambertConformalConicProjection.h"
#include "ProjectionLib/MercatorProjection.h"
#include "ProjectionLib/MillerCylindricalProjection.h"
#include "ProjectionLib/OrthographicProjection.h"
#include "ProjectionLib/PolarStereographicProjection.h"
#include "ProjectionLib/PolyconicProjection.h"
#include "ProjectionLib/RobinsonProjection.h"
#include "ProjectionLib/SinusoidalProjection.h"
#include "ProjectionLib/StatePlaneProjection.h"
#include "ProjectionLib/StereographicProjection.h"
#include "ProjectionLib/TransverseMercatorProjection.h"
#include "ProjectionLib/UTMProjection.h"
#include "ProjectionLib/VanDerGrintenProjection.h"

// Initialize NAD27 to State Plane zone map
GeoTIFFProjectionMapper::StatePlaneMap GeoTIFFProjectionMapper::d_nad27StatePlaneMap[] =
{
    { 26729,  101 },
    { 26730,  102 },
    { 26731, 5001 },
    { 26732, 5002 },
    { 26733, 5003 },
    { 26734, 5004 },
    { 26735, 5005 },
    { 26736, 5006 },
    { 26737, 5007 },
    { 26738, 5008 },
    { 26739, 5009 },
    { 26740, 5010 },
    { 26741,  401 },
    { 26742,  402 },
    { 26743,  403 },
    { 26744,  404 },
    { 26745,  405 },
    { 26746,  406 },
    { 26747,  407 },
    { 26748,  201 },
    { 26749,  202 },
    { 26750,  203 },
    { 26751,  301 },
    { 26752,  302 },
    { 26753,  501 },
    { 26754,  502 },
    { 26755,  503 },
    { 26756,  600 },
    { 26757,  700 },
    { 26758,  901 },
    { 26759,  902 },
    { 26760,  903 },
    { 26761, 5101 },
    { 26762, 5102 },
    { 26763, 5103 },
    { 26764, 5104 },
    { 26765, 5105 },
    { 26766, 1001 },
    { 26767, 1002 },
    { 26768, 1101 },
    { 26769, 1102 },
    { 26770, 1103 },
    { 26771, 1201 },
    { 26772, 1202 },
    { 26773, 1301 },
    { 26774, 1302 },
    { 26775, 1401 },
    { 26776, 1402 },
    { 26777, 1501 },
    { 26778, 1502 },
    { 26779, 1601 },
    { 26780, 1602 },
    { 26781, 1701 },
    { 26782, 1702 },
    { 26783, 1801 },
    { 26784, 1802 },
    { 26785, 1900 },
    { 26786, 2001 },
    { 26787, 2002 },
    { 26788, 2111 },
    { 26789, 2112 },
    { 26790, 2113 },
    { 26791, 2201 },
    { 26792, 2202 },
    { 26793, 2203 },
    { 26794, 2301 },
    { 26795, 2303 },
    { 26796, 2401 },
    { 26797, 2402 },
    { 26798, 2403 },
    { 32001, 2501 },
    { 32002, 2502 },
    { 32003, 2503 },
    { 32005, 2601 },
    { 32006, 2602 },
    { 32007, 2701 },
    { 32008, 2702 },
    { 32009, 2703 },
    { 32010, 2800 },
    { 32011, 2900 },
    { 32012, 3001 },
    { 32013, 3002 },
    { 32014, 3003 },
    { 32015, 3101 },
    { 32016, 3102 },
    { 32017, 3103 },
    { 32018, 3104 },
    { 32019, 3200 },
    { 32020, 3301 },
    { 32021, 3302 },
    { 32022, 3401 },
    { 32023, 3402 },
    { 32024, 3501 },
    { 32025, 3502 },
    { 32026, 3601 },
    { 32027, 3602 },
    { 32028, 3701 },
    { 32029, 3702 },
    { 32030, 3800 },
    { 32031, 3901 },
    { 32033, 3902 },
    { 32034, 4001 },
    { 32035, 4002 },
    { 32036, 4100 },
    { 32037, 4201 },
    { 32038, 4202 },
    { 32039, 4203 },
    { 32040, 4204 },
    { 32041, 4205 },
    { 32042, 4301 },
    { 32043, 4302 },
    { 32044, 4303 },
    { 32045, 4400 },
    { 32046, 4501 },
    { 32047, 4502 },
    { 32048, 4601 },
    { 32049, 4602 },
    { 32050, 4701 },
    { 32051, 4702 },
    { 32052, 4801 },
    { 32053, 4802 },
    { 32054, 4803 },
    { 32055, 4901 },
    { 32056, 4902 },
    { 32057, 4903 },
    { 32058, 4904 },
    { 32059, 5201 },
    { 32060, 5202 }
};

// Initialize NAD83 to State Plane zone map
GeoTIFFProjectionMapper::StatePlaneMap GeoTIFFProjectionMapper::d_nad83StatePlaneMap[] =
{
    { 32100, 2500 },
    { 32104, 2600 },
    { 32133, 3900 },
    { 32161, 5200 }
};

// Initialize Geographic CS to Datum Map
GeoTIFFProjectionMapper::GeogCSDatumMap GeoTIFFProjectionMapper::d_geogCSDatumMap[] =
{
    { GCS_Adindan, ADINDAN },
    { GCS_Arc_1950, ARC1950 },
    { GCS_Arc_1960, ARC1960 },
    { GCS_Cape, CAPE },
    { GCS_ED50, EUROPEAN_DATUM_1950 },
    { GCS_GD49, GEODETIC_DATUM_1949 },
    { GCS_Hu_Tzu_Shan, HU_TZU_SHAN },
    { GCS_Indian_1954, INDIAN },
    { GCS_Indian_1975, INDIAN },
    { GCS_NAD27, NAD27 },
    { GCS_NAD83, NAD83 },
    { GCS_OSGB_1936, ORDNANCE_SURVEY_1936 },
    { GCS_Pulkovo_1942, PULKOVO_1942 },
    { GCS_PSAD56, PROVISIONAL_S_AMERICAN_1956 },
    { GCS_Tokyo, TOKYO },
    { GCS_WGS_72, WGS_72 },
    { GCS_WGS_72BE, WGS_72 },
    { GCS_WGS_84, WGS_84 }
};

// Initialize Coordinate Trans type to Projection System map
GeoTIFFProjectionMapper::CoordTransProjSysMap GeoTIFFProjectionMapper::d_ctProjSysMap[] =
{
    { CT_TransverseMercator, TM },
    { CT_TransvMercator_Modified_Alaska, ALASKA },
    { CT_ObliqueMercator, HOM },
    { CT_Mercator, MERCAT },
    { CT_LambertConfConic, LAMCC },
    { CT_LambertAzimEqualArea, LAMAZ },
    { CT_AlbersEqualArea, ALBERS },
    { CT_AzimuthalEquidistant, AZMEQD },
    { CT_EquidistantConic, EQUIDC },
    { CT_Stereographic, STEREO },
    { CT_PolarStereographic, PS },
    { CT_Equirectangular, EQRECT },
    { CT_Gnomonic, GNOMON },
    { CT_MillerCylindrical, MILLER },
    { CT_Orthographic, ORTHO },
    { CT_Polyconic, POLYC },
    { CT_Robinson, ROBIN },
    { CT_Sinusoidal, SNSOID },
    { CT_VanDerGrinten, VGRINT }
};

Projection* GeoTIFFProjectionMapper::getProjection( GTIF* pGTIFF )
{
  if ( NULL == pGTIFF )
  {
    return NULL;
  }

  // Get the model type
  uint16 modelType;
  if ( !GTIFKeyGet( pGTIFF, GTModelTypeGeoKey, &modelType, 0, 1 ) )
  {
    return NULL;
  }

  // See if this is a projected or a geographic model
  switch ( modelType )
  {
  case ModelTypeProjected:
    return getPCSProjection( pGTIFF );
  case ModelTypeGeographic:
    return getGeographicProjection( pGTIFF );
  default:
    return NULL;
  }
}

Projection* GeoTIFFProjectionMapper::getGeographicProjection( GTIF* pGTIFF )
{
  // Get the datum, abort if it couldn't be determined
  DATUM datum;
  if ( UNKNOWN_DATUM == ( datum = getGeodeticDatum( pGTIFF ) ) )
  {
    return NULL;
  }

  // Read in the GeogAngularUnitsGeoKey
  uint16 geogAngularUnits;
	if ( GTIFKeyGet( pGTIFF, GeogAngularUnitsGeoKey, &geogAngularUnits, 0, 1 ) )
  {
    return ( new GeographicProjection( datum, 
                                       getAngularUnitFromAngularUnitCode( geogAngularUnits ) ) );
  }

  return NULL;
}

Projection* GeoTIFFProjectionMapper::getPCSProjection( GTIF* pGTIFF )
{
  // See if this is a pre-defined projected CS
  uint16 projectedCSType;
	if ( GTIFKeyGet( pGTIFF, ProjectedCSTypeGeoKey, &projectedCSType, 0, 1 ) )
  {
    if ( KvUserDefined != projectedCSType )
    {
      return getProjectionFromPCSCode( projectedCSType );
    }
  }

  // Get the datum, abort if it couldn't be determined
  DATUM datum;
  if ( UNKNOWN_DATUM == ( datum = getGeodeticDatum( pGTIFF ) ) )
  {
    return NULL;
  }

  // Get the linear units
  uint16 projLinearUnits = Linear_Meter;
  GTIFKeyGet( pGTIFF, ProjLinearUnitsGeoKey, &projLinearUnits, 0, 1 );
  UNIT units = getLinearUnitFromLinearUnitCode( projLinearUnits );

  // See if this is a standard projection with a non-standard datum
  uint16 projection;
	if ( GTIFKeyGet( pGTIFF, GeographicTypeGeoKey, &projection, 0, 1 ) )
  {
    if ( KvUserDefined != projection )
    {
      Projection* pTemp = getNonStandardDatumProjection( projection, datum, 
                                                         units );
      if ( NULL != pTemp )
      {
        return pTemp;
      }
    }
  }

  // Get the projection system type
  PROJSYS projSys;
  uint16 projCoordTrans;
  if ( !GTIFKeyGet( pGTIFF, ProjCoordTransGeoKey, &projCoordTrans, 0, 1 ) )
  {
    return NULL;
  }
  else
  {
    projSys = getProjectionSystemFromCoordTransCode( projCoordTrans );

    // Abort if the projection system is unknown
    if ( UNKNOWN_PROJSYS == projSys )
    {
      return NULL;
    }
  }

  // Create all the possible parameters and give them reasonable defaults
  double projStdParallel1 = 0.0;
  double projStdParallel2 = 0.0;
  double projNatOriginLong = 0.0;
  double projNatOriginLat = 0.0;
  double projFalseEasting = 0.0;
  double projFalseNorthing = 0.0;
  double projFalseOriginLong = 0.0;
  double projFalseOriginLat = 0.0;
  double projFalseOriginEasting = 0.0;
  double projFalseOriginNorthing = 0.0;
  double projCenterLong = 0.0;
  double projCenterLat = 0.0;
  double projCenterEasting = 0.0;
  double projCenterNorthing = 0.0;
  double projScaleAtNatOrigin = 1.0;
  double projAzimuthAngle = 0.0;
  double projStraightVertPoleLong = 0.0;

  // Read in the projection parameters
	GTIFKeyGet( pGTIFF, ProjStdParallel1GeoKey, &projStdParallel1, 0, 1 );
	GTIFKeyGet( pGTIFF, ProjStdParallel2GeoKey, &projStdParallel2, 0, 1 );
  GTIFKeyGet( pGTIFF, ProjNatOriginLongGeoKey,&projNatOriginLong,0, 1 );
	GTIFKeyGet( pGTIFF, ProjNatOriginLatGeoKey, &projNatOriginLat, 0, 1 );
	GTIFKeyGet( pGTIFF, ProjFalseEastingGeoKey, &projFalseEasting, 0, 1 );
	GTIFKeyGet( pGTIFF, ProjFalseNorthingGeoKey,&projFalseNorthing,0, 1 );
  GTIFKeyGet( pGTIFF, ProjFalseOriginLongGeoKey, &projFalseOriginLong, 0, 1 );
  GTIFKeyGet( pGTIFF, ProjFalseOriginLatGeoKey,  &projFalseOriginLat,  0, 1 );
  GTIFKeyGet( pGTIFF, ProjFalseOriginEastingGeoKey, &projFalseOriginEasting,
              0, 1 );
  GTIFKeyGet( pGTIFF, ProjFalseOriginNorthingGeoKey, &projFalseOriginNorthing,
              0, 1 );
	GTIFKeyGet( pGTIFF, ProjCenterLongGeoKey, &projCenterLong, 0, 1 );
	GTIFKeyGet( pGTIFF, ProjCenterLatGeoKey,  &projCenterLat,  0, 1 );
	GTIFKeyGet( pGTIFF, ProjCenterEastingGeoKey,  &projCenterEasting, 0, 1 );
	GTIFKeyGet( pGTIFF, ProjCenterNorthingGeoKey, &projCenterNorthing,0, 1 );
  GTIFKeyGet( pGTIFF, ProjScaleAtNatOriginGeoKey, &projScaleAtNatOrigin, 0, 1);
  GTIFKeyGet( pGTIFF, ProjAzimuthAngleGeoKey,     &projAzimuthAngle,     0, 1);
  GTIFKeyGet( pGTIFF, ProjStraightVertPoleLongGeoKey,
              &projStraightVertPoleLong, 0, 1 );

  // Convert all the lat/long values to packed DMS
  convertDMSToPackedDMS( projStdParallel1 );
  convertDMSToPackedDMS( projStdParallel2 );
  convertDMSToPackedDMS( projNatOriginLong );
  convertDMSToPackedDMS( projNatOriginLat );
  convertDMSToPackedDMS( projFalseOriginLong );
  convertDMSToPackedDMS( projFalseOriginLat );
  convertDMSToPackedDMS( projCenterLong );
  convertDMSToPackedDMS( projCenterLat );
  convertDMSToPackedDMS( projStraightVertPoleLong );

  // Setup the appropriate projection
  switch ( projSys )
  {
  case ALASKA:
    return ( new AlaskaConformalProjection( 0.0, 0.0,
                                            projFalseEasting,
                                            projFalseNorthing,
                                            datum, units ) );
  case ALBERS:
    return ( new AlbersConicProjection( projStdParallel1, projStdParallel2,
                                        0.0, 0.0, projCenterLong,
                                        projNatOriginLat, projFalseEasting,
                                        projFalseNorthing, datum, units ) );
  case AZMEQD:
    return ( new AzimuthalEquidistantProjection( projCenterLong,
                                                 projCenterLat,
                                                 projFalseEasting,
                                                 projFalseNorthing,
                                                 0.0, datum, units ) );
  case EQUIDC:
    // Setup a type A or B projection
    if ( projStdParallel1 == projStdParallel2 )
    {
      return ( new EquidistantConicProjection( projCenterLat,
                                               0.0, 0.0,
                                               projCenterLong,
                                               projNatOriginLat,
                                               projFalseEasting,
                                               projFalseNorthing,
                                               datum, units ) );
    }
    else
    {
      return ( new EquidistantConicProjection( projStdParallel1,
                                               projStdParallel2,
                                               0.0, 0.0,
                                               projCenterLong,
                                               projNatOriginLat,
                                               projFalseEasting,
                                               projFalseNorthing,
                                               datum, units ) );
    }
    case EQRECT:
      return ( new EquirectangularProjection( projCenterLat,
                                              0.0, projCenterLong,
                                              projFalseEasting,
                                              projFalseNorthing,
                                              datum, units ) );
    case GNOMON:
      return ( new GnomonicProjection( projCenterLong,
                                       projCenterLat,
                                       projFalseEasting,
                                       projFalseNorthing,
                                       0.0, datum, units ) );
    case HOM: // Hotine B
      return ( new HotineObliqueMercatorProjection( projScaleAtNatOrigin,
                                                    projAzimuthAngle,
                                                    0.0, 0.0,
                                                    projCenterLong,
                                                    projCenterLat,
                                                    projFalseEasting,
                                                    projFalseNorthing,
                                                    datum, units ) );
    case LAMAZ:
      return ( new LambertAzimuthalProjection( projCenterLong,
                                               projCenterLat,
                                               projFalseEasting,
                                               projFalseNorthing,
                                               0.0, datum, units ) );
    case LAMCC:
      return ( new LambertConformalConicProjection( projStdParallel1,
                                                    projStdParallel2,
                                                    0.0, 0.0,
                                                    projNatOriginLong,
                                                    projFalseOriginLat,
                                                    projFalseEasting,
                                                    projFalseNorthing,
                                                    datum, units ) );
    case MERCAT:
      return ( new MercatorProjection( 0.0, 0.0,
                                       projNatOriginLong,
                                       projNatOriginLat,
                                       projCenterEasting,
                                       projCenterNorthing,
                                       datum, units ) );
    case MILLER:
      return ( new MillerCylindricalProjection( 0.0, projCenterLong,
                                                projFalseEasting,
                                                projFalseNorthing,
                                                datum, units ) );
    case ORTHO:
      return ( new OrthographicProjection( projCenterLong,
                                           projCenterLat,
                                           projFalseEasting,
                                           projFalseNorthing,
                                           0.0, datum, units ) );
    case POLYC:
      return ( new PolyconicProjection( 0.0, 0.0,
                                        projCenterLong,
                                        projCenterLat,
                                        projFalseEasting,
                                        projFalseNorthing,
                                        datum, units ) );
    case PS:
      return ( new PolarStereographicProjection( projStraightVertPoleLong,
                                                 projNatOriginLat, 0.0, 0.0,
                                                 projFalseEasting,
                                                 projFalseNorthing,
                                                 datum, units ) );
    case ROBIN:
      return ( new RobinsonProjection( 0.0, projCenterLong,
                                       projFalseEasting,
                                       projFalseNorthing,
                                       datum, units ) );
    case SNSOID:
      return ( new SinusoidalProjection( 0.0, projCenterLong,
                                         projFalseEasting,
                                         projFalseNorthing,
                                         datum, units ) );
    case STEREO:
      return ( new StereographicProjection( projCenterLong,
                                            projCenterLat,
                                            projFalseEasting,
                                            projFalseNorthing,
                                            0.0, datum, units ) );
    case TM:
      return ( new TransverseMercatorProjection( projScaleAtNatOrigin,
                                                 0.0, 0.0,
                                                 projCenterLong,
                                                 projNatOriginLat,
                                                 projFalseEasting,
                                                 projFalseNorthing,
                                                 datum, units ) );
    case VGRINT:
      return ( new VanDerGrintenProjection( projCenterLat,
                                            0.0, projCenterLong,
                                            projFalseEasting,
                                            projFalseNorthing,
                                            datum, units ) );
  }


  return NULL;
}

Projection*
GeoTIFFProjectionMapper::getProjectionFromPCSCode( unsigned short pcsCode )
{
  if ( pcsCode < 20137 )
  {
    return NULL;
  }

  PROJSYS projSys = UNKNOWN_PROJSYS;
  DATUM   datum = UNKNOWN_DATUM;
  UNIT    u = METERS;
  short   zone = 0;

  // Adindan UTM
  if ( pcsCode >= 20137 && pcsCode <= 20138 )
  {
    projSys = UTM;
    datum = ADINDAN;
    zone = pcsCode % 100;
  }
  // European Datum 1950 UTM
  else if ( pcsCode >= 23028 && pcsCode <=23038 )
  {
    projSys = UTM;
    datum = EUROPEAN_DATUM_1950;
    zone = pcsCode % 100;
  }
  // Indian 1954/1978 UTM
  else if ( pcsCode >= 23947 && pcsCode <= 24048 )
  {
    projSys = UTM;
    datum = INDIAN;
    zone = pcsCode % 100;
  }
  // Provisional South American 1956 UTM North
  else if ( pcsCode >= 24818 && pcsCode <= 24821 )
  {
    projSys = UTM;
    datum = PROVISIONAL_S_AMERICAN_1956;
    zone = pcsCode % 100;
  }
  // Provisional South American 1956 UTM South
  else if ( pcsCode >= 24818 && pcsCode <= 24821 )
  {
    projSys = UTM;
    datum = PROVISIONAL_S_AMERICAN_1956;
    zone = 60 - ( pcsCode % 100 );
  }
  // NAD27 UTM North
  else if ( pcsCode >= 26703 && pcsCode <= 26722 )
  {
    projSys = UTM;
    datum = NAD27;
    zone = pcsCode % 100;
  }
  // NAD27 State Plane
  else if ( pcsCode >= 26729 && pcsCode <= 26798 )
  {
    if ( getNAD27StatePlaneZone( pcsCode, zone ) )
    {
      projSys = SPCS;
      datum = NAD27;
      u = US_FEET;
    }
  }
  // NAD83 UTM North
  else if ( pcsCode >= 26903 && pcsCode <= 26923 )
  {
    projSys = UTM;
    datum = NAD83;
    zone = pcsCode % 100;
  }
  // NAD83 State Plane
  else if ( pcsCode >= 26929 && pcsCode <= 26998 )
  {
    if ( getNAD83StatePlaneZone( pcsCode, zone ) )
    {
      projSys = SPCS;
      datum = NAD83;
      u = US_FEET;
    }
  }
  // NAD27 State Plane
  else if ( pcsCode >= 32001 && pcsCode <= 32060 )
  {
    if ( getNAD27StatePlaneZone( pcsCode, zone ) )
    {
      projSys = SPCS;
      datum = NAD27;
      u = US_FEET;
    }
  }
  // NAD83 State Plane
  else if ( pcsCode >= 32100 && pcsCode <= 32161 )
  {
    if ( getNAD83StatePlaneZone( pcsCode, zone ) )
    {
      projSys = SPCS;
      datum = NAD83;
      u = US_FEET;
    }
  }
  // WGS72 UTM North
  else if ( pcsCode >= 32201 && pcsCode <= 32260 )
  {
    projSys = UTM;
    datum = WGS_72;
    zone = pcsCode % 100;
  }
  // WGS72 UTM South
  else if ( pcsCode >= 32301 && pcsCode <= 32360 )
  {
    projSys = UTM;
    datum = WGS_72;
    zone = -( pcsCode % 100 );
  }
  // WGS72BE UTM North
  else if ( pcsCode >= 32401 && pcsCode <= 32460 )
  {
    projSys = UTM;
    datum = WGS_72;
    zone = pcsCode % 100;
  }
  // WGS72BE UTM South
  else if ( pcsCode >= 32501 && pcsCode <= 32560 )
  {
    projSys = UTM;
    datum = WGS_72;
    zone = -( pcsCode % 100 );
  }
  // WGS84 UTM North
  else if ( pcsCode >= 32601 && pcsCode <= 32660 )
  {
    projSys = UTM;
    datum = WGS_84;
    zone = pcsCode % 100;
  }
  // WGS84 UTM South
  else if ( pcsCode >= 32701 && pcsCode <= 32760 )
  {
    projSys = UTM;
    datum = WGS_84;
    zone = -( pcsCode % 100 );
  }

  // Create the projection if a valid projection system was found
  if ( UNKNOWN_PROJSYS != projSys )
  {
    switch ( projSys )
    {
    case UTM:
      return ( new UTMProjection( zone, datum, u ) );
    case SPCS:
      return ( new StatePlaneProjection( zone, datum, u ) );
    default:
      return NULL;
    }
  }

  return NULL;
}

unsigned short
GeoTIFFProjectionMapper::getNonStandardDatumProjectionCode( const Projection* pProj )
{
  // Get the zone, datum, and units
  DATUM d = pProj->getDatum();
  int zone = 0;
  switch ( pProj->getProjectionSystem() )
  {
  case UTM:
  {
    // Make sure it's a UTM projection
    const UTMProjection* pUTM = dynamic_cast<const UTMProjection*>( pProj );
    if ( NULL == pUTM )
    {
      return 0;
    }

    // Get the zone
    zone = pUTM->getZone();
            
    if ( zone > 0 )
    {
      return ( 16000 + zone );
    }
    else if ( zone < 0 )
    {
      return ( 16100 - zone );
    }
    break;
  }
  case SPCS:
  {
    // Make sure it's a State Plane projection
    const StatePlaneProjection* pSP = 
      dynamic_cast<const StatePlaneProjection*>( pProj );
    if ( NULL == pSP )
    {
      return 0;
    }

    // Get the zone
    zone = pSP->getZone();

    if ( NAD27 == d )
    {
      return ( 10000 + zone );
    }
    else if ( NAD83 == d )
    {
      return ( 10000 + zone + 30 );
    }

    break;
  }
  }
    
  return 0;
}

Projection*
GeoTIFFProjectionMapper::getNonStandardDatumProjection( unsigned short projection, 
                                                        DATUM datum,
                                                        UNIT  units )
{
  // Check for state plane
  if ( projection >= 10000 && projection < 16000 )
  {
    unsigned short stateCode = ( projection - 10000 ) / 100;
    unsigned short zoneCode = projection % 100;
    if ( zoneCode >= 30 )
    {
      zoneCode -= 30;
    }
    short statePlaneZoneCode = stateCode * 100 + zoneCode;

    return ( new StatePlaneProjection( statePlaneZoneCode, datum, units ) );
  }
  // Check for UTM North
  else if ( projection >= 16000 && projection < 16100 )
  {
    return ( new UTMProjection( projection % 100, datum, units ) );
  }
  // Check for UTM South
  else if ( projection >= 16100 && projection < 16200 )
  {
    return ( new UTMProjection( -( projection % 100 ), datum, units ) );
  }

  return NULL;
}

bool
GeoTIFFProjectionMapper::writeProjection( GTIF* pGTIFF, const Projection* pProj )
{
  // Write the projection
  if ( GEO == pProj->getProjectionSystem() )
  {
    return writeGeographicProjection( pGTIFF, pProj );
  }
  else
  {
    return writePCSProjection( pGTIFF, pProj );
  }

  return true;
}

bool
GeoTIFFProjectionMapper::writeGeographicProjection( GTIF* pGTIFF, const Projection* pProj )
{
  // Write the model type
  GTIFKeySet( pGTIFF, GTModelTypeGeoKey, TYPE_SHORT, 1, ModelTypeGeographic );

  // Get the Geographic CS type code
  unsigned short gcsCode = getGeographicCSTypeCodeFromDatum( pProj->getDatum() );
  if ( 0 == gcsCode )
  {
    return false;
  }

  // Write the Geographic CS type code
  GTIFKeySet( pGTIFF, GeographicTypeGeoKey, TYPE_SHORT, 1, gcsCode );
  
  // Get the angular units code
  unsigned short angUnitsCode =
    getAngularUnitCodeFromAngularUnit( pProj->getUnit() );
  if ( 0 == angUnitsCode )
  {
    return false;
  }

  // Write the Anuglar Units Code
  GTIFKeySet( pGTIFF, GeogAngularUnitsGeoKey, TYPE_SHORT, 1, angUnitsCode );

  return true;
}

bool GeoTIFFProjectionMapper::writePCSProjection(GTIF* pGTIFF,
                                                 const Projection* pProj )
{
  // Write the model type
  GTIFKeySet( pGTIFF, GTModelTypeGeoKey, TYPE_SHORT, 1, ModelTypeProjected );

  // Write out the linear units
  GTIFKeySet( pGTIFF, ProjLinearUnitsGeoKey, TYPE_SHORT, 1, 
              getLinearUnitCodeFromLinearUnit( pProj->getUnit() ) );
    
  // See if this is a pre-defined projected CS
  uint16 projectedCSType;
  if ( 0 != ( projectedCSType = getProjectedCSType( pProj ) ) )
  {
    GTIFKeySet( pGTIFF, ProjectedCSTypeGeoKey, TYPE_SHORT, 1, projectedCSType );
    return true;
  }
  else
  {
    // This must be a user-defined projection
    GTIFKeySet( pGTIFF, ProjectedCSTypeGeoKey, TYPE_SHORT, 1, KvUserDefined );
  }

  // Get the datum code
  unsigned short gcsCode = getGeographicCSTypeCodeFromDatum( pProj->getDatum() );
  if ( 0 == gcsCode )
  {
    return false;
  }

  // Write the datum code
  GTIFKeySet( pGTIFF, GeographicTypeGeoKey, TYPE_SHORT, 1, gcsCode );

  // See if this is a standard projection with a non-standard datum
  uint16 projection;
  if ( 0 != ( projection = getNonStandardDatumProjectionCode( pProj ) ) )
  {
    GTIFKeySet( pGTIFF, GeographicTypeGeoKey, TYPE_SHORT, 1, projection );
    return true;
  }
        
  // Get the projection system type
  unsigned short coordTransType = getCoordTransCodeFromProjectionSystem( pProj->getProjectionSystem() );
  if ( 0 == coordTransType )
  {
    return false;
  }

  // Write the projection system type
  GTIFKeySet( pGTIFF, ProjCoordTransGeoKey, TYPE_SHORT, 1, coordTransType );

  // Create all the possible parameters and give them reasonable defaults
  double projStdParallel1 = 0.0;
  double projStdParallel2 = 0.0;
  double projNatOriginLong = 0.0;
  double projNatOriginLat = 0.0;
  double projFalseEasting = 0.0;
  double projFalseNorthing = 0.0;
  double projFalseOriginLong = 0.0;
  double projFalseOriginLat = 0.0;
  double projFalseOriginEasting = 0.0;
  double projFalseOriginNorthing = 0.0;
  double projCenterLong = 0.0;
  double projCenterLat = 0.0;
  double projCenterEasting = 0.0;
  double projCenterNorthing = 0.0;
  double projScaleAtNatOrigin = 1.0;
  double projAzimuthAngle = 0.0;
  double projStraightVertPoleLong = 0.0;

  switch ( pProj->getProjectionSystem() )
  {
  case ALBERS:
    {
      // Make sure this is an Albers projection
      const AlbersConicProjection* pAlb = 
        dynamic_cast<const AlbersConicProjection*>( pProj );
      if ( NULL == pAlb )
      {
        return false;
      }

      // Get the parameters
      projStdParallel1 = pAlb->getFirstStandardParallel();
      projStdParallel2 = pAlb->getSecondStandardParallel();
      projCenterLong = pAlb->getCentralMeridian();
      projFalseEasting = pAlb->getFalseEasting();
      projFalseNorthing = pAlb->getFalseNorthing();
      break;
    }
  case AZMEQD:
  case GNOMON:
  case LAMAZ:
  case ORTHO:
  case STEREO:
    {
      // Make sure this is an Azimuthal projection
      const AzimuthalProjection* pAz =
        dynamic_cast<const AzimuthalProjection*>( pProj );
      if ( NULL == pAz )
      {
        return false;
      }

      // Get the parameters
      projCenterLong = pAz->getCentralLongitude();
      projCenterLat = pAz->getCentralLatitude();
      projFalseEasting = pAz->getFalseEasting();
      projFalseNorthing = pAz->getFalseNorthing();
      break;
    }
  case MILLER:
  case ROBIN:
  case SNSOID:
    {
      // Make sure this is an Pseudocylindrical projection
      const PseudocylindricalProjection* pPC = 
        dynamic_cast<const PseudocylindricalProjection*>( pProj );
      if ( NULL == pPC )
      {
        return false;
      }

      // Get the parameters
      projCenterLong = pPC->getCentralMeridian();
      projFalseEasting = pPC->getFalseEasting();
      projFalseNorthing = pPC->getFalseNorthing();
      break;
    }
  case EQUIDC:
    {
      // Make sure this is an EquidistantConic projection
      const EquidistantConicProjection* pEC =
        dynamic_cast<const EquidistantConicProjection*>( pProj );
      if ( NULL == pEC )
      {
        return false;
      }

      // Get the parameters
      projCenterLat = pEC->getStandardParallel();
      projCenterLong = pEC->getCentralMeridian();
      projNatOriginLat = pEC->getOriginLatitude();
      projFalseEasting = pEC->getFalseEasting();
      projFalseNorthing = pEC->getFalseNorthing();
      projStdParallel1 = pEC->getFirstStandardParallel();
      projStdParallel2 = pEC->getSecondStandardParallel();
      break;
    }
  case EQRECT:
    {
      // Make sure this is an Equirectangular projection
      const EquirectangularProjection* pER =
        dynamic_cast<const EquirectangularProjection*>( pProj );
      if ( NULL == pER )
      {
        return false;
      }

      // Get the parameters
      projCenterLat = pER->getTrueScaleLatitude();
      projCenterLong = pER->getCentralMeridian();
      projFalseEasting = pER->getFalseEasting();
      projFalseNorthing = pER->getFalseNorthing();
      break;
    }
  case HOM:
    {
      // Make sure this is an HotineObliqueMercator projection
      const HotineObliqueMercatorProjection* pHOM =
        dynamic_cast<const HotineObliqueMercatorProjection*>( pProj );
      if ( NULL == pHOM )
      {
        return false;
      }

      // Make sure this is a type B HOM projection
      if ( 0.0 != pHOM->getLatitude1()  || 0.0 != pHOM->getLatitude2() ||
           0.0 != pHOM->getLongitude1() || 0.0 != pHOM->getLongitude2() ||
           0.0 != pHOM->getAzimuthPoint() )
      {
        return false;
      }

      // Get the parameters
      projScaleAtNatOrigin = pHOM->getProjectionCenterScaleFactor();
      projAzimuthAngle = pHOM->getAzimuthAngle();
      projCenterLong = pHOM->getCentralMeridian();
      projCenterLat = pHOM->getOriginLatitude();
      projFalseEasting = pHOM->getFalseEasting();
      projFalseNorthing = pHOM->getFalseNorthing();
      break;
    }
  case LAMCC:
    {
      // Make sure this is a LambertConformalConic projection
      const LambertConformalConicProjection* pLCC =
        dynamic_cast<const LambertConformalConicProjection*>( pProj );
      if ( NULL == pLCC )
      {
        return false;
      }

      // Get the parameters
      projStdParallel1 = pLCC->getFirstStandardParallel();
      projStdParallel2 = pLCC->getSecondStandardParallel();
      projNatOriginLong = pLCC->getCentralMeridian();
      projFalseOriginLat = pLCC->getOriginLatitude();
      projFalseEasting = pLCC->getFalseEasting();
      projFalseNorthing = pLCC->getFalseNorthing();

      break;
    }
  case MERCAT:
    {
      // Make sure this is a Mercator projection
      const MercatorProjection* pMC =
        dynamic_cast<const MercatorProjection*>( pProj );
      if ( NULL == pMC )
      {
        return false;
      }

      // Get the parameters
      projNatOriginLong = pMC->getCentralMeridian();
      projNatOriginLat = pMC->getOriginLatitude();
      projCenterEasting = pMC->getFalseEasting();
      projCenterNorthing = pMC->getFalseNorthing();

      break;
    }
  case POLYC:
    {
      // Make sure this is a Polyconic projection
      const PolyconicProjection* pPC =
        dynamic_cast<const PolyconicProjection*>( pProj );
      if ( NULL == pPC )
      {
        return false;
      }

      // Get the parameters
      projCenterLong = pPC->getCentralMeridian();
      projCenterLat = pPC->getOriginLatitude();
      projFalseEasting = pPC->getFalseEasting();
      projFalseNorthing = pPC->getFalseNorthing();

      break;
    }
  case PS:
    {
      // Make sure this is a PolarStereographic projection
      const PolarStereographicProjection* pPS = 
        dynamic_cast<const PolarStereographicProjection*>( pProj );
      if ( NULL == pPS )
      {
        return false;
      }

      // Get the parameters
      projStraightVertPoleLong = pPS->getLongitudePole();
      projNatOriginLat = pPS->getTrueScaleLatitude();
      projFalseEasting = pPS->getFalseEasting();
      projFalseNorthing = pPS->getFalseNorthing();

      break;
    }
  case ALASKA:
  case TM:
    {
      // Make sure this is a TransverseMercator projection
      const TransverseMercatorProjection* pTM = 
        dynamic_cast<const TransverseMercatorProjection*>( pProj );
      if ( NULL == pTM )
      {
        return false;
      }

      // Get the parameters
      projScaleAtNatOrigin = pTM->getCentralMeridianScaleFactor();
      projCenterLong = pTM->getCentralMeridian();
      projNatOriginLat = pTM->getOriginLatitude();
      projFalseEasting = pTM->getFalseEasting();
      projFalseNorthing = pTM->getFalseNorthing();

      break;
    }
  case VGRINT:
    {
      // Make sure this is a VanDerGrinten projection
      const VanDerGrintenProjection* pVDG =
        dynamic_cast<const VanDerGrintenProjection*>( pProj );
      if ( NULL == pVDG )
      {
        return false;
      }

      // Get the parameters
      projCenterLat = pVDG->getOriginLatitude();
      projCenterLong = pVDG->getCentralMeridian();
      projFalseEasting = pVDG->getFalseEasting();
      projFalseNorthing = pVDG->getFalseNorthing();

      break;
    }
  default:
    {
      return false;
    }
  }

  // Convert all the angular parameters to DMS
  convertPackedDMSToDMS( projStdParallel1 );
  convertPackedDMSToDMS( projStdParallel2 );
  convertPackedDMSToDMS( projNatOriginLong );
  convertPackedDMSToDMS( projNatOriginLat );
  convertPackedDMSToDMS( projFalseOriginLong );
  convertPackedDMSToDMS( projFalseOriginLat );
  convertPackedDMSToDMS( projCenterLong );
  convertPackedDMSToDMS( projCenterLat );
  convertPackedDMSToDMS( projStraightVertPoleLong );

  // Write out all the keys
	GTIFKeySet(pGTIFF, ProjStdParallel1GeoKey, TYPE_DOUBLE, 1, projStdParallel1);
	GTIFKeySet(pGTIFF, ProjStdParallel2GeoKey, TYPE_DOUBLE, 1, projStdParallel2);
  GTIFKeySet(pGTIFF, ProjNatOriginLongGeoKey,TYPE_DOUBLE, 1, projNatOriginLong);
	GTIFKeySet(pGTIFF, ProjNatOriginLatGeoKey, TYPE_DOUBLE, 1, projNatOriginLat);
	GTIFKeySet(pGTIFF, ProjFalseEastingGeoKey, TYPE_DOUBLE, 1, projFalseEasting);
	GTIFKeySet(pGTIFF, ProjFalseNorthingGeoKey,TYPE_DOUBLE, 1, projFalseNorthing);
  GTIFKeySet(pGTIFF, ProjFalseOriginLongGeoKey, TYPE_DOUBLE, 1, 
             projFalseOriginLong );
  GTIFKeySet(pGTIFF, ProjFalseOriginLatGeoKey, TYPE_DOUBLE, 1, 
             projFalseOriginLat );
  GTIFKeySet(pGTIFF, ProjFalseOriginEastingGeoKey, TYPE_DOUBLE, 1,
             projFalseOriginEasting );
  GTIFKeySet(pGTIFF, ProjFalseOriginNorthingGeoKey, TYPE_DOUBLE, 1,
             projFalseOriginNorthing );
	GTIFKeySet(pGTIFF, ProjCenterLongGeoKey,  TYPE_DOUBLE, 1, projCenterLong );
	GTIFKeySet(pGTIFF, ProjCenterLatGeoKey,   TYPE_DOUBLE, 1, projCenterLat );
	GTIFKeySet(pGTIFF, ProjCenterEastingGeoKey, TYPE_DOUBLE, 1,
             projCenterEasting );
	GTIFKeySet(pGTIFF, ProjCenterNorthingGeoKey, TYPE_DOUBLE, 1, 
             projCenterNorthing );
  GTIFKeySet(pGTIFF, ProjScaleAtNatOriginGeoKey, TYPE_DOUBLE, 1,
             projScaleAtNatOrigin );
  GTIFKeySet(pGTIFF, ProjAzimuthAngleGeoKey, TYPE_DOUBLE, 1, projAzimuthAngle);
  GTIFKeySet(pGTIFF, ProjStraightVertPoleLongGeoKey, TYPE_DOUBLE, 1, 
             projStraightVertPoleLong );

  return true;
}

unsigned short
GeoTIFFProjectionMapper::getProjectedCSType( const Projection* pProj )
{
  // Get the zone, datum, and units
  DATUM d = pProj->getDatum();
  UNIT u = pProj->getUnit();
  int zone = 0;
  switch ( pProj->getProjectionSystem() )
  {
  case UTM:
    {
      // Make sure it's a UTM projection
      const UTMProjection* pUTM =
        dynamic_cast<const UTMProjection*>( pProj );
      if ( NULL == pUTM )
      {
        return 0;
      }

      // Get the zone
      zone = pUTM->getZone();

      // Make sure the units are meters
      if ( METERS != u )
      {
        return 0;
      }

      switch ( d )
      {
      case ADINDAN:
        if ( 37 == zone )
        {
          return PCS_Adindan_UTM_zone_37N;
        }
        else if ( 38 == zone )
        {
          return PCS_Adindan_UTM_zone_38N;
        }

        return 0;
      case  EUROPEAN_DATUM_1950:
        if ( 28 <= zone && zone <= 38 )
        {
          return ( PCS_ED50_UTM_zone_28N + zone - 28 );
        }

        return 0;
      case INDIAN:
        if ( 47 <= zone && zone <= 48 )
        {
          return ( PCS_Indian_1975_UTM_47N + zone - 47 );
        }

        return 0;
      case PROVISIONAL_S_AMERICAN_1956:
        if ( 18 <= zone && zone <= 21 )
        {
          return ( PCS_PSAD56_UTM_zone_18N + zone - 18 );
        }
        else if ( -20 <= zone && zone <= -17 )
        {
          return ( PCS_PSAD56_UTM_zone_17S - zone - 17 );
        }

        return 0;
      case NAD27:
        if ( zone >= 3 && zone <= 22 )
        {
          return ( PCS_NAD27_UTM_zone_3N + zone - 3 );
        }

        return 0;
      case NAD83:
        if ( zone >= 3 && zone <= 23 )
        {
          return ( PCS_NAD83_UTM_zone_3N + zone - 3 );
        }

        return 0;
      case WGS_72:
        if ( zone >= 1 && zone <= 60 )
        {
          return ( PCS_WGS72_UTM_zone_1N + zone - 1 );
        }
        else if ( zone >= -60 && zone <= -1 )
        {
          return ( PCS_WGS72_UTM_zone_1S - zone - 1 );
        }

        return 0;
      case WGS_84:
        if ( zone >= 1 && zone <= 60 )
        {
          return ( PCS_WGS84_UTM_zone_1N + zone - 1 );
        }
        else if ( zone >= -60 && zone <= -1 )
        {
          return ( PCS_WGS84_UTM_zone_1S - zone - 1 );
        }

        return 0;
      }

      break;
    }
  case SPCS:
    {
      // Make sure it's a State Plane projection
      const StatePlaneProjection* pSP =
        dynamic_cast<const StatePlaneProjection*>( pProj );
      if ( NULL == pSP )
      {
        return 0;
      }

      // Get the zone
      zone = pSP->getZone();

      // Make sure the units are US feet
      if ( US_FEET != u )
      {
        return 0;
      }

      uint16 pcsCode = 0;
      if ( NAD27 == d )
      {                
        getPCSCodeFromNAD27StatePlaneZone( zone, pcsCode );
      }
      else if ( NAD83 == d )
      {
        getPCSCodeFromNAD83StatePlaneZone( zone, pcsCode );
      }

      return pcsCode;
    }
  default:
    {
      return 0;
    }
  }

  return 0;
}

DATUM 
GeoTIFFProjectionMapper::getDatumFromGeographicCSTypeCode( unsigned short gcsCode )
{
  int numEntries = sizeof( d_geogCSDatumMap ) / 
                   sizeof( GeoTIFFProjectionMapper::GeogCSDatumMap );
  for ( int i = 0; i < numEntries; i++ )
  {
    if ( gcsCode == d_geogCSDatumMap[i].d_gcsCode )
    {
      return d_geogCSDatumMap[i].d_datum;
    }
  }

  return UNKNOWN_DATUM;
}

unsigned short
GeoTIFFProjectionMapper::getGeographicCSTypeCodeFromDatum( DATUM datum )
{
  int numEntries = sizeof( d_geogCSDatumMap ) / 
                   sizeof( GeoTIFFProjectionMapper::GeogCSDatumMap );
  for ( int i = 0; i < numEntries; i++ )
  {
    if ( datum == d_geogCSDatumMap[i].d_datum )
    {
      return d_geogCSDatumMap[i].d_gcsCode;
    }
 }

  return 0;
}

DATUM       
GeoTIFFProjectionMapper::getDatumFromGeodeticDatumCode( unsigned short datumCode )
{
  switch ( datumCode )
  {
  case Datum_Adindan:
    return ADINDAN;
  case Datum_Arc_1950:
    return ARC1950;
  case Datum_Arc_1960:
    return ARC1960;
  case Datum_Australian_Geodetic_Datum_1966:
    return AUSTRALIAN_GEODETIC_1966;
  case Datum_Australian_Geodetic_Datum_1984:
    return AUSTRALIAN_GEODETIC_1984;
  case Datum_Cape:
    return CAPE;
  case Datum_European_Datum_1950:
    return EUROPEAN_DATUM_1950;
  case Datum_Hu_Tzu_Shan:
    return HU_TZU_SHAN;
  case Datum_Indian_1954:
  case Datum_Indian_1975:
    return INDIAN;
  case Datum_North_American_Datum_1927:
    return NAD27;
  case Datum_North_American_Datum_1983:
    return NAD83;
  case Datum_OSGB_1936:
    return ORDNANCE_SURVEY_1936;
  case Datum_Pulkovo_1942:
    return PULKOVO_1942;
  case Datum_Provisional_S_American_Datum_1956:
    return PROVISIONAL_S_AMERICAN_1956;
  case Datum_Tokyo:
    return TOKYO;
  case Datum_WGS72:
    return WGS_72;
  case Datum_WGS84:
    return WGS_84;
  default:
    return UNKNOWN_DATUM;
  }
}

UNIT
GeoTIFFProjectionMapper::getLinearUnitFromLinearUnitCode( unsigned short unitCode )
{
  switch ( unitCode )
  {
  case Linear_Meter:
    return METERS;
  case Linear_Foot:
  case Linear_Foot_Modified_American:
  case Linear_Foot_Clarke:
  case Linear_Foot_Indian:
    return US_FEET;
  default:
    return UNKNOWN_UNIT;
  }
}

unsigned short
GeoTIFFProjectionMapper::getLinearUnitCodeFromLinearUnit( UNIT u )
{
  switch ( u )
  {
  case METERS:
    return Linear_Meter;
  case US_FEET:
    return Linear_Foot;
  default:
    return Linear_Meter;
  }
}

UNIT        
GeoTIFFProjectionMapper::getAngularUnitFromAngularUnitCode( unsigned short unitCode )
{
    switch ( unitCode )
    {
        case Angular_Radian:
            return RADIANS;
        case Angular_Degree:
            return ARC_DEGREES;
        case Angular_Arc_Second:
            return ARC_SECONDS;
        default:
            return ARC_DEGREES;
    }
}

unsigned short
GeoTIFFProjectionMapper::getAngularUnitCodeFromAngularUnit( UNIT u )
{
  switch ( u )
  {
  case RADIANS:
    return Angular_Radian;
  case ARC_DEGREES:
    return Angular_Degree;
  case ARC_SECONDS:
    return Angular_Arc_Second;
  default:
    return Angular_Degree;
  }
}

bool
GeoTIFFProjectionMapper::getNAD27StatePlaneZone( unsigned short pcsCode, short& zone )
{
  int numEntries = sizeof( d_nad27StatePlaneMap ) / 
                   sizeof( GeoTIFFProjectionMapper::StatePlaneMap );
  for ( int i = 0; i < numEntries; i++ )
  {
    if ( pcsCode == d_nad27StatePlaneMap[i].d_pcsCode )
    {
      zone = d_nad27StatePlaneMap[i].d_statePlaneZone;
      return true;
    }
  }

  return false;
}

bool
GeoTIFFProjectionMapper::getNAD83StatePlaneZone( unsigned short pcsCode, short& zone )
{
  int numEntries = sizeof( d_nad83StatePlaneMap ) / sizeof( StatePlaneMap );
  for ( int i = 0; i < numEntries; i++ )
  {
    if ( pcsCode == d_nad83StatePlaneMap[i].d_pcsCode )
    {
      zone = d_nad83StatePlaneMap[i].d_statePlaneZone;
      return true;
    }
  }

  // A matching pcdCode wasn't found in the list of codes for which NAD27 and NAD83
  // differ, so search the NAD27 list with the appropriate PCS code
  if ( pcsCode >= 26929 && pcsCode <= 26998 )
  {
    return getNAD27StatePlaneZone( pcsCode - 200, zone );
  }
  else if ( pcsCode >= 32100 && pcsCode <= 32161 )
  {
    return getNAD27StatePlaneZone( pcsCode - 100, zone );
  }

  return false;
}


bool
GeoTIFFProjectionMapper::getPCSCodeFromNAD27StatePlaneZone( short zone, unsigned short& pcsCode )
{
  int numEntries = sizeof( d_nad27StatePlaneMap ) / 
                   sizeof( GeoTIFFProjectionMapper::StatePlaneMap );
  for ( int i = 0; i < numEntries; i++ )
  {
    if ( zone == d_nad27StatePlaneMap[i].d_statePlaneZone )
    {
      pcsCode = d_nad27StatePlaneMap[i].d_pcsCode;
      return true;
    }
  }

  return false;
}

bool
GeoTIFFProjectionMapper::getPCSCodeFromNAD83StatePlaneZone( short zone, unsigned short& pcsCode )
{
  int numEntries = sizeof( d_nad83StatePlaneMap ) / sizeof( StatePlaneMap );
  for ( int i = 0; i < numEntries; i++ )
  {
    if ( zone == d_nad83StatePlaneMap[i].d_statePlaneZone )
    {
      pcsCode = d_nad83StatePlaneMap[i].d_pcsCode;
      return true;
    }
  }

  // A matching pcdCode wasn't found in the list of codes for which NAD27 and NAD83
  // differ, so search the NAD27 list with the appropriate PCS code
  if ( getPCSCodeFromNAD27StatePlaneZone( zone, pcsCode ) )
  {
    if ( pcsCode >= 26729 && pcsCode <= 26798 )
    {
      pcsCode += 200;
      return true;
    }
    else if ( pcsCode >= 32000 && pcsCode <= 32061 )
    {
      pcsCode += 100;
      return true;
    }
  }

  return false;
}

DATUM
GeoTIFFProjectionMapper::getGeodeticDatum( GTIF* pGTIFF )
{
  // Get the datum
  uint16 geographicType;
  uint16 geodeticDatum;
  if ( GTIFKeyGet( pGTIFF, GeographicTypeGeoKey, &geographicType, 0, 1 ) )
  {
    return getDatumFromGeographicCSTypeCode( geographicType );
  }
  else if ( GTIFKeyGet( pGTIFF, GeogGeodeticDatumGeoKey, &geodeticDatum, 0, 1 ) )
  {
    return getDatumFromGeodeticDatumCode( geodeticDatum );
  }

  return UNKNOWN_DATUM;
}

PROJSYS     
GeoTIFFProjectionMapper::getProjectionSystemFromCoordTransCode( unsigned short coordTransCode )
{
  int numEntries = sizeof( d_ctProjSysMap ) / 
                   sizeof( GeoTIFFProjectionMapper::CoordTransProjSysMap );
  for ( int i = 0; i < numEntries; i++ )
  {
    if ( coordTransCode == d_ctProjSysMap[i].d_ctCode )
    {
      return d_ctProjSysMap[i].d_projSys;
    }
  }

  return UNKNOWN_PROJSYS;
}

unsigned short
GeoTIFFProjectionMapper::getCoordTransCodeFromProjectionSystem( PROJSYS projSys )
{
  int numEntries = sizeof( d_ctProjSysMap ) / 
                   sizeof( GeoTIFFProjectionMapper::CoordTransProjSysMap );
  for ( int i = 0; i < numEntries; i++ )
  {
    if ( projSys == d_ctProjSysMap[i].d_projSys )
    {
      return d_ctProjSysMap[i].d_ctCode;
    }
  }

  return 0;
}

void GeoTIFFProjectionMapper::convertDMSToPackedDMS( double& dms )
{
  double sign = 1.0;
  if ( dms < 0.0 )
  {
    dms = -dms;
    sign = -1.0;
  }

  // Extract the degrees, minutes, and seconds
  short deg = static_cast<short>( dms );
  dms -= deg;
  dms *= 60.0;
  short min = static_cast<short>( dms );
  dms -= min;
  dms *= 60.0;

  // Rebuild the coordinate in packed DMS
  dms = deg * 1000000 + min * 1000 + dms;
  dms *= sign;
}

void GeoTIFFProjectionMapper::convertPackedDMSToDMS( double& dms )
{
  double sign = 1.0;
  if ( dms < 0.0 )
  {
    dms = -dms;
    sign = -1.0;
  }

  // Extract the degrees, minutes, and seconds
  short deg = dms / 1000000;
  dms -= deg * 1000000;
  short min = dms / 1000;
  dms -= min / 1000;
  dms /= 3600;
  dms += min / 60.0;
  dms += deg;
  dms *= sign;
}