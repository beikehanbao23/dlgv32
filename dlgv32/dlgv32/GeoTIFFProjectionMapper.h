// GeoTIFFProjectionMapper.h - interface for GeoTIFFProjectionMapper class
//
// Developed by: Mike Childs
//      Started: 3/18/98

#ifndef _GEOTIFFPROJECTIONMAPPER_H_
#define _GEOTIFFPROJECTIONMAPPER_H_

#include "ProjectionLib/ProjectionTypes.h"
#include "libgeotiff/geotiffio.h"

// Forward declarations
class Projection;

class GeoTIFFProjectionMapper
{
public:
  static Projection* getProjection( GTIF* pGTIFF );
  static DATUM   getGeodeticDatum( GTIF* pGTIFF );
  static UNIT    getAngularUnitFromAngularUnitCode( unsigned short unitCode);
  static UNIT    getLinearUnitFromLinearUnitCode( unsigned short unitCode );
  static bool    writeProjection( GTIF* pGTIFF, const Projection* pProj );

private:
  // Helper functions
  static void           convertDMSToPackedDMS( double& dms );
  static void           convertPackedDMSToDMS( double& dms );
  static unsigned short getAngularUnitCodeFromAngularUnit( UNIT u );
  static unsigned short getCoordTransCodeFromProjectionSystem(PROJSYS projSys);
  static DATUM        getDatumFromGeographicCSTypeCode(unsigned short gcsCode);
  static DATUM        getDatumFromGeodeticDatumCode(unsigned short datumCode);
  static unsigned short getGeographicCSTypeCodeFromDatum(DATUM datum);
  static Projection*    getGeographicProjection( GTIF* pGTIFF );
  static unsigned short getLinearUnitCodeFromLinearUnit( UNIT u );
  static Projection*  getNonStandardDatumProjection(unsigned short projection,
                                                    DATUM datum, UNIT units );
  static unsigned short getNonStandardDatumProjectionCode( const Projection* pProj );
  static bool    getPCSCodeFromNAD27StatePlaneZone(short zone, 
                                                   unsigned short& pcsCode);
  static bool    getPCSCodeFromNAD83StatePlaneZone( short zone,
                                                    unsigned short& pcsCode );
  static Projection*    getPCSProjection( GTIF* pGTIFF );
  static unsigned short getProjectedCSType( const Projection* pProj );
  static Projection*    getProjectionFromPCSCode( unsigned short pcsCode );
  static PROJSYS        getProjectionSystemFromCoordTransCode( unsigned short coordTransCode );
  static bool           getNAD27StatePlaneZone( unsigned short pcsCode,
                                                short& zone );
  static bool           getNAD83StatePlaneZone( unsigned short pcsCode, 
                                                short& zone );
  static bool           writeGeographicProjection( GTIF* pGTIFF,
                                                   const Projection* pProj );
  static bool           writePCSProjection( GTIF* pGTIFF,
                                            const Projection* pProj );

  // State plane mapper arrays
  struct StatePlaneMap
  {
    unsigned short d_pcsCode;
    short          d_statePlaneZone;
  };

  static StatePlaneMap d_nad27StatePlaneMap[];
  static StatePlaneMap d_nad83StatePlaneMap[];

  // Geographic CS To Datum code array
  struct GeogCSDatumMap
  {
    unsigned short d_gcsCode;
    DATUM          d_datum;
  };

  static GeogCSDatumMap d_geogCSDatumMap[];

  // Coordinate Transform Key to Projection System array
  struct CoordTransProjSysMap
  {
    unsigned short d_ctCode;
    PROJSYS        d_projSys;
  };

    static CoordTransProjSysMap d_ctProjSysMap[];
};

#endif