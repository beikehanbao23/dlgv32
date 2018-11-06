/*******************************************************************************
NAME                             EQUIRECTANGULAR 

PURPOSE:	Transforms input Easting and Northing to longitude and
		latitude for the Equirectangular projection.  The
		Easting and Northing must be in meters.  The longitude
		and latitude values will be returned in radians.

PROGRAMMER              DATE
----------              ----
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
static double lon_center;	/* Center longitude (projection center) */
static double lat_origin;	/* center latitude			*/
static double false_northing;	/* y offset in meters			*/
static double false_easting;	/* x offset in meters			*/

/* Initialize the Equirectangular projection
  ----------------------------------------*/
long
equiinvint(double r_maj, double center_lon, double lat1, double false_east, double false_north) 

             			/* major axis			*/
                  		/* center longitude		*/
            			/* latitude of true scale	*/
                  		/* x offset in meters		*/
                   		/* y offset in meters		*/
{
double temp;			/* temporary variable		*/

/* Place parameters in static storage for common use
  -------------------------------------------------*/
r_major = r_maj;
lon_center = center_lon;
lat_origin = lat1;
false_northing = false_north;
false_easting = false_east;

/* Report parameters to the user
  -----------------------------*/
ptitle("EQUIRECTANGULAR"); 
radius(r_major);
cenlonmer(lon_center);
origin(lat_origin);
offsetp(false_easting,false_northing);
return(OK);
}


/* Equirectangular inverse equations--mapping x,y to lat/long
  ---------------------------------------------------------*/
long
equiinv(double x, double y, double *lon, double *lat)
         			/* (O) X projection coordinate 	*/
         			/* (O) Y projection coordinate 	*/
            			/* (I) Longitude 		*/
            			/* (I) Latitude 		*/
{
double adjust_lon(double x);	/* Function to adjust longitude to -180 - 180 	*/
double sinphi, cosphi;	/* sin and cos value				*/
double dlon;		/* delta longitude value			*/
double coslon;		/* cos of longitude				*/
double ksp;		/* scale factor					*/
double g;		

/* Inverse equations
  -----------------*/
x -= false_easting;
y -= false_northing;
*lat = y / r_major;
if (fabs(*lat) > HALF_PI)
   {
   p_error("Input data error","equi-inv");
   return(174);
   }
*lon = adjust_lon(lon_center + x / (r_major * cos(lat_origin)));
return(OK);
}
