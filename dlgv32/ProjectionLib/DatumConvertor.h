// DatumConvertor.h - interface for DatumConvertor class
//
// Developed by: Mike Childs
//      Started: 3/17/98

#ifndef _DATUMCONVERTOR_H_
#define _DATUMCONVERTOR_H_

#include "ProjectionTypes.h"

class DatumConvertor
{
public:
  static bool convertDatum( double& lat, double& lon, DATUM from, DATUM to );
  static ELLIPSOID getDatumEllipsoid( DATUM d );

private:
  // Datum info type
  struct DatumParameters
  {
    DATUM  d_datum;
    ELLIPSOID d_ellipsoid;
    double d_deltaX;
    double d_deltaY;
    double d_deltaZ;
  };

  // Ellipsoid info type
  struct EllipsoidParameters
  {
    ELLIPSOID d_ellipsoid;
    double d_deltaA; // equatorial radius shift from WGS84
    double d_deltaF; // flattening shift from WGS84
  };

  static bool convertToWGS84( double& lat, double& lon, double& height,
                              DATUM from );
  static bool convertFromWGS84( double& lat, double& lon, double& height,
                                DATUM to );
  static DatumParameters* getDatumParameters( DATUM d );
  static EllipsoidParameters* getEllipsoidParameters( ELLIPSOID e );
  /*static bool convertToECEF( double& lat, double& lon, double& height,
                               DATUM from );
  static bool convertFromECEF( double& lat, double& lon, double& height,
                               DATUM to );*/

  // Conversion parameters array
  static DatumParameters     d_datumParams[];
  static EllipsoidParameters d_ellipsoidParams[];
};

#endif