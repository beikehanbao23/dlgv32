
/*******************************************************************************
NAME                            LAMBERT CONFORMAL CONIC

PURPOSE:	Transforms input longitude and latitude to Easting and
		Northing for the Lambert Conformal Conic projection.  The
		longitude and latitude must be in radians.  The Easting
		and Northing values will be returned in meters.

PROGRAMMER              DATE
----------              ----
T. Mittan               2-26-93


ALGORITHM REFERENCES

1.  Snyder, John P., "Map Projections--A Working Manual", U.S. Geological
    Survey Professional Paper 1395 (Supersedes USGS Bulletin 1532), United
    State Government Printing Office, Washington D.C., 1987.

2.  Snyder, John P. and Voxland, Philip M., "An Album of Map Projections",
    U.S. Geological Survey Professional Paper 1453 , United State Government
*******************************************************************************/
#include "gctpc/cproj.h"
#include "gctpc/report.h"

/* Variables common to all subroutines in this code file
  -----------------------------------------------------*/
  static double r_major;                /* major axis                   */
  static double r_minor;                /* minor axis                   */
  static double es;                     /* eccentricity squared         */
  static double e;                      /* eccentricity                 */
  static double center_lon;             /* center longituted            */
  static double center_lat;             /* cetner latitude              */
  static double ns;                     /* ratio of angle between meridian*/
  static double f0;                     /* flattening of ellipsoid      */
  static double rh;                     /* height above ellipsoid       */
  static double false_easting;          /* x offset in meters           */
  static double false_northing;         /* y offset in meters           */

/* Initialize the Lambert Conformal conic projection
  ------------------------------------------------*/
long
lamccforint(double r_maj, double r_min, double lat1, double lat2, double c_lon, double c_lat, double false_east, double false_north)

                                /* center latitude                      */
                                /* center longitude                     */
                                /* first standard parallel              */
                                /* second standard parallel             */
                                /* major axis                           */
                                /* minor axis                           */
                                /* x offset in meters                   */
                                /* y offset in meters                   */
{
double sin_po;                  /* sin value                            */
double cos_po;                  /* cos value                            */
double con;                     /* temporary variable                   */
double ms1;                     /* small m 1                            */
double ms2;                     /* small m 2                            */
double temp;                    /* temporary variable                   */
double ts0;                     /* small t 0                            */
double ts1;                     /* small t 1                            */
double ts2;                     /* small t 2                            */
double msfnz(double eccent, double sinphi, double cosphi);                 /* function to compute small m          */
double tsfnz(double eccent, double phi, double sinphi);                 /* function to compute small t          */
r_major = r_maj;
r_minor = r_min;
false_northing = false_north;
false_easting = false_east;

/* Standard Parallels cannot be equal and on opposite sides of the equator
------------------------------------------------------------------------*/
if (fabs(lat1+lat2) < EPSLN)
   {
   p_error("Equal Latitiudes for St. Parallels on opposite sides of equator",
	   "lamcc-for");
   return(41);
   }
   
temp = r_minor / r_major;
es = 1.0 - SQUARE(temp);
e = sqrt(es);

center_lon = c_lon;
center_lat = c_lat;
sincos(lat1,&sin_po,&cos_po);
con = sin_po;
ms1 = msfnz(e,sin_po,cos_po);
ts1 = tsfnz(e,lat1,sin_po);
sincos(lat2,&sin_po,&cos_po);
ms2 = msfnz(e,sin_po,cos_po);
ts2 = tsfnz(e,lat2,sin_po);
sin_po = sin(center_lat);
ts0 = tsfnz(e,center_lat,sin_po);

if (fabs(lat1 - lat2) > EPSLN)
    ns = log (ms1/ms2)/ log (ts1/ts2);
else
    ns = con;
f0 = ms1 / (ns * pow(ts1,ns));
rh = r_major * f0 * pow(ts0,ns);


/* Report parameters to the user
  -----------------------------*/
ptitle("LAMBERT CONFORMAL CONIC");
radius2(r_major, r_minor);
stanparl(lat1,lat2);
cenlonmer(center_lon);
origin(c_lat);
offsetp(false_easting,false_northing);

return(OK);
}

/* Lambert Conformal conic forward equations--mapping lat,long to x,y
  -----------------------------------------------------------------*/
long
lamccfor(double lon, double lat, double *x, double *y)
                                /* (I) Longitude                */
                                /* (I) Latitude                 */
                                /* (O) X projection coordinate  */
                                /* (O) Y projection coordinate  */

{
double con;                     /* temporary angle variable             */
double rh1;                     /* height above ellipsoid               */
double sinphi;                  /* sin value                            */
double theta;                   /* angle                                */
double ts;                      /* small value t                        */
double tsfnz(double eccent, double phi, double sinphi);                 /* function to compute small t          */
double adjust_lon(double x);            /* function to adust the longitude      */

con  = fabs( fabs(lat) - HALF_PI);
if (con > EPSLN)
  {
  sinphi = sin(lat);
  ts = tsfnz(e,lat,sinphi);
  rh1 = r_major * f0 * pow(ts,ns);
  }
else
  {
  con = lat * ns;
  if (con <= 0)
    {
    p_error("Point can not be projected","lamcc-for");
    return(44);
    }
  rh1 = 0;
  }
theta = ns * adjust_lon(lon - center_lon);
*x = rh1 * sin(theta) + false_easting;
*y = rh - rh1 * cos(theta) + false_northing;

return(OK);
}

