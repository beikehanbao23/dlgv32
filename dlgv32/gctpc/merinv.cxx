/*******************************************************************************
NAME                            MERCATOR

PURPOSE:	Transforms input Easting and Northing to longitude and
		latitude for the Mercator projection.  The
		Easting and Northing must be in meters.  The longitude
		and latitude values will be returned in radians.

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
  -----------------------------------*/
long
merinvint(double r_maj, double r_min, double center_lon, double center_lat, double false_east, double false_north) 

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


/* Mercator inverse equations--mapping x,y to lat/long
  --------------------------------------------------*/
long
merinv(double x, double y, double *lon, double *lat)
         			/* (O) X projection coordinate 	*/
         			/* (O) Y projection coordinate 	*/
            			/* (I) Longitude 		*/
            			/* (I) Latitude 		*/
{
double adjust_lon(double x);	/* Function to adjust longitude to -180 - 180 	*/
double tsfnz(double eccent, double phi, double sinphi);		/* function to compute t			*/
double phi2z(double eccent, double ts, long int *flag);		/* function to compute phi			*/
double ts;		/* small t value				*/
double sin_phii;	/* sin value					*/
long flag;		/* error flag 					*/


/* Inverse equations
  -----------------*/
flag = 0;
x -= false_easting;
y -= false_northing;
ts = exp(-y/(r_major * m1));
*lat = phi2z(e,ts,&flag);
if (flag != 0)
   return(flag);
*lon = adjust_lon(lon_center + x/(r_major * m1));

return(OK);
}
