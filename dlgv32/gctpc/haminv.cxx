/*******************************************************************************
NAME                            HAMMER 

PURPOSE:	Transforms input Easting and Northing to longitude and
		latitude for the Hammer projection.  The
		Easting and Northing must be in meters.  The longitude
		and latitude values will be returned in radians.

PROGRAMMER              DATE            
----------              ----           
T. Mittan		March, 1993

This function was adapted from the Hammer projection code (FORTRAN) in
the General Cartographic Transformation Package software which is
available from the U.S. Geological Survey National Mapping Division.
 
ALGORITHM REFERENCES

1.  "New Equal-Area Map Projections for Noncircular Regions", John P. Snyder,
    The American Cartographer, Vol 15, No. 4, October 1988, pp. 341-355.

2.  Snyder, John P., "Map Projections--A Working Manual", U.S. Geological
    Survey Professional Paper 1395 (Supersedes USGS Bulletin 1532), United
    State Government Printing Office, Washington D.C., 1987.

3.  "Software Documentation for GCTP General Cartographic Transformation
    Package", U.S. Geological Survey National Mapping Division, May 1982.
*******************************************************************************/
#include "gctpc/cproj.h"
#include "gctpc/report.h"

/* Variables common to all subroutines in this code file
  -----------------------------------------------------*/
static double lon_center;	/* Center longitude (projection center) */
static double R;		/* Radius of the earth (sphere)	 	*/
static double false_easting;	/* x offset in meters			*/
static double false_northing;	/* y offset in meters			*/

/* Initialize the HAMMER projection
  -------------------------------*/
long
haminvint(double r, double center_long, double false_east, double false_north) 

          			/* (I) Radius of the earth (sphere) 	*/
                   		/* (I) Center longitude 		*/
                  		/* x offset in meters			*/
                   		/* y offset in meters			*/
{
long i;

/* Place parameters in static storage for common use
  -------------------------------------------------*/
R = r;
lon_center = center_long;
false_easting = false_east;
false_northing = false_north;

/* Report parameters to the user
  -----------------------------*/
ptitle("HAMMER"); 
radius(r);
cenlon(center_long);
offsetp(false_easting,false_northing);
return(OK);
}

/* HAMMER inverse equations--mapping x,y to lat/long
  ------------------------------------------------*/
long
haminv(double x, double y, double *lon, double *lat)
         			/* (O) X projection coordinate */
         			/* (O) Y projection coordinate */
            			/* (I) Longitude */
            			/* (I) Latitude */

{
double dlon;
double adjust_lon(double x);
double asinz(double con);
double fac;

/* Inverse equations
  -----------------*/
x -= false_easting;
y -= false_northing;
fac = sqrt(4.0 * R * R - (x * x)/ 4.0 - y * y) / 2.0;
*lon = adjust_lon(lon_center + 2.0 * 
                  atan2((x * fac), (2.0 * R * R - x * x/4 - y * y)));
*lat = asinz(y * fac / R / R);
return(OK);
}
