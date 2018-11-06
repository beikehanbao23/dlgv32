/*******************************************************************************
NAME                            MERCATOR

PURPOSE:	Transforms input longitude and latitude to Easting and
		Northing for the Mercator projection.  The
		longitude and latitude must be in radians.  The Easting
		and Northing values will be returned in meters.

PROGRAMMER              DATE
----------              ----
D. Steinwand, EROS      Nov, 1991
T. Mittan		Mar, 1993

ALGORITHM REFERENCES

1.  Snyder, John P., "Map Projections--A Working Manual", U.S. Geological
    Survey Professional Paper 1395 (Supersedes USGS Bulletin 1532), United
    State Government Printing Office, Washington D.C., 1987.

2.  Snyder, John P. and Voxland, Philip M., "An Album of Map Projections",
    U.S. Geological Survey Professional Paper 1453 , United State Government
    Printing Office, Washington D.C., 1989.
*******************************************************************************/
#include "gctpc/cproj.h"
#include "gctpc/report.h"

/* Variables common to all subroutines in this code file
  -----------------------------------------------------*/
static double r_major;		/* major axis 				*/
static double r_minor;		/* minor axis 				*/
static double lon_center;	/* Center longitude (projection center) */
static double lat_origin;	/* center latitude			*/
static double e,es;		/* eccentricity constants		*/
static double m1;		/* small value m			*/
static double false_northing;	/* y offset in meters			*/
static double false_easting;	/* x offset in meters			*/


/* Initialize the Mercator projection
  -------------------------------------------------*/
long
merforint(double r_maj, double r_min, double center_lon, double center_lat, double false_east, double false_north) 

             			/* major axis			*/
             			/* minor axis			*/
                  		/* center longitude		*/
                  		/* center latitude		*/
                  		/* x offset in meters		*/
                   		/* y offset in meters		*/
{
double temp;			/* temporary variable		*/
double e0fn(double x),e1fn(double x),e2fn(double x),e3fn(double x); 	/* 	functions	*/

/* Place parameters in static storage for common use
  -------------------------------------------------*/
r_major = r_maj;
r_minor = r_min;
lon_center = center_lon;
lat_origin = center_lat;
false_northing = false_north;
false_easting = false_east;

temp = r_minor / r_major;
es = 1.0 - SQUARE(temp);
e = sqrt(es);
m1 = cos(center_lat)/(sqrt(1.0 - es * sin(center_lat) * sin(center_lat)));

/* Report parameters to the user
  -----------------------------*/
ptitle("MERCATOR"); 
radius2(r_major, r_minor);
cenlonmer(lon_center);
origin(lat_origin);
offsetp(false_easting,false_northing);
return(OK);
}


/* Mercator forward equations--mapping lat,long to x,y
  --------------------------------------------------*/
long
merfor(double lon, double lat, double *x, double *y)
           			/* (I) Longitude 		*/
           			/* (I) Latitude 		*/
          			/* (O) X projection coordinate 	*/
          			/* (O) Y projection coordinate 	*/
{
double adjust_lon(double x);	/* Function to adjust longitude to -180 - 180 	*/
double tsfnz(double eccent, double phi, double sinphi);		/* function to compute t			*/
double ts;		/* small t value				*/
double sinphi;		/* sin value					*/

/* Forward equations
  -----------------*/
if (fabs(fabs(lat) - HALF_PI)  <= EPSLN)
   {
   p_error("Transformation cannot be computed at the poles","mer-forward");
   return(53);
   }
else
   {
   sinphi = sin(lat);
   ts = tsfnz(e,lat,sinphi);
   *x = false_easting + r_major * m1 * adjust_lon(lon - lon_center);
   *y = false_northing - r_major * m1 * log(ts);
   }
return(OK);
}
