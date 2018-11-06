/*******************************************************************************
NAME                            WAGNER IV

PURPOSE:	Transforms input Easting and Northing to longitude and
		latitude for the Wagner IV projection.  The
		Easting and Northing must be in meters.  The longitude
		and latitude values will be returned in radians.

PROGRAMMER              DATE
----------              ----
D. Steinwand, EROS      May, 1991

This function was implemented with formulas supplied by John P. Snyder.

ALGORITHM REFERENCES

1.  Snyder, John P. and Voxland, Philip M., "An Album of Map Projections",
    U.S. Geological Survey Professional Paper 1453 , United State Government
    Printing Office, Washington D.C., 1989.

2.  Snyder, John P., Personal correspondence, January 1991.
*******************************************************************************/
#include "gctpc/cproj.h"
#include "gctpc/report.h"

/* Variables common to all subroutines in this code file
  -----------------------------------------------------*/
static double lon_center;	/* Center longitude (projection center) */
static double R;		/* Radius of the earth (sphere) */
static double false_easting;	/* x offset				*/
static double false_northing;	/* y offset				*/

/* Initialize the Wagner IV projection
  ------------------------------------*/
long
wivinvint(double r, double center_long, double false_east, double false_north) 
          			/* (I) Radius of the earth (sphere) */
                   		/* (I) Center longitude */
                  		/* x offset				*/
                   		/* y offset				*/
{
/* Place parameters in static storage for common use
  -------------------------------------------------*/
R = r;
lon_center = center_long;
false_easting = false_east;
false_northing = false_north;

/* Report parameters to the user
  -----------------------------*/
ptitle("WAGNER IV"); 
radius(r);
cenlon(center_long);
offsetp(false_east,false_north);
return(OK);
}

/* Wagner IV inverse equations--mapping x,y to lat,long 
  ----------------------------------------------------*/
long
wivinv(double x, double y, double *lon, double *lat)
         		/* (I) X projection coordinate */
         		/* (I) Y projection coordinate */
            		/* (O) Longitude */
            		/* (O) Latitude */
{
double adjust_lon(double x);    /* Function to adjust longitude to -180 - 180 */
double theta;

/* Inverse equations
  -----------------*/
x -= false_easting;
y -= false_northing;
theta = asin(y /  (1.56548 * R));
*lon = adjust_lon(lon_center + (x / (0.86310 * R * cos(theta))));
*lat = asin((2.0 * theta + sin(2.0 * theta)) / 2.9604205062);
return(OK);
}

