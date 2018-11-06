/*******************************************************************************
NAME                             ORTHOGRAPHIC 

PURPOSE:	Transforms input longitude and latitude to Easting and
		Northing for the Orthographic projection.  The
		longitude and latitude must be in radians.  The Easting
		and Northing values will be returned in meters.

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
static double sin_p14;		/* sin of center latitude		*/
static double cos_p14;		/* cos of center latitude		*/

/* Initialize the Orthographic projection
  -------------------------------------*/
long
orthforint(double r_maj, double center_lon, double center_lat, double false_east, double false_north) 

             			/* major axis			*/
                  		/* center longitude		*/
                  		/* center latitude		*/
                  		/* x offset in meters		*/
                   		/* y offset in meters		*/
{
double temp;			/* temporary variable		*/

/* Place parameters in static storage for common use
  -------------------------------------------------*/
r_major = r_maj;
lon_center = center_lon;
lat_origin = center_lat;
false_northing = false_north;
false_easting = false_east;

sincos(center_lat,&sin_p14,&cos_p14);

/* Report parameters to the user
  -----------------------------*/
ptitle("ORTHOGRAPHIC"); 
radius(r_major);
cenlonmer(lon_center);
origin(lat_origin);
offsetp(false_easting,false_northing);
return(OK);
}


/* Orthographic forward equations--mapping lat,long to x,y
  ---------------------------------------------------*/
long
orthfor(double lon, double lat, double *x, double *y)
           			/* (I) Longitude 		*/
           			/* (I) Latitude 		*/
          			/* (O) X projection coordinate 	*/
          			/* (O) Y projection coordinate 	*/
{
double adjust_lon(double x);	/* Function to adjust longitude to -180 - 180 	*/
double sinphi, cosphi;	/* sin and cos value				*/
double dlon;		/* delta longitude value			*/
double coslon;		/* cos of longitude				*/
double ksp;		/* scale factor					*/
double g;		

/* Forward equations
  -----------------*/
dlon = adjust_lon(lon - lon_center);
sincos(lat,&sinphi,&cosphi);
coslon = cos(dlon);
g = sin_p14 * sinphi + cos_p14 * cosphi * coslon;
ksp = 1.0;
if ((g > 0) || (fabs(g) <= EPSLN))
  {
  *x = false_easting + r_major * ksp * cosphi * sin(dlon);
  *y = false_northing + r_major * ksp * (cos_p14 * sinphi -
					 sin_p14 * cosphi * coslon);
  }
else
  {
  p_error("Point can not be projected","orth-for");
  return(143);
  }
return(OK);
}
