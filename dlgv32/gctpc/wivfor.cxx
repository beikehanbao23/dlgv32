/*******************************************************************************
NAME                            WAGNER IV

PURPOSE:	Transforms input longitude and latitude to Easting and
		Northing for the Wagner IV projection.  The
		longitude and latitude must be in radians.  The Easting
		and Northing values will be returned in meters.

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
wivforint(double r, double center_long, double false_east, double false_north) 
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

/* Wagner IV forward equations--mapping lat,long to x,y
  ----------------------------------------------------*/
long
wivfor(double lon, double lat, double *x, double *y)
           			/* (I) Longitude */
           			/* (I) Latitude */
          			/* (O) X projection coordinate */
          			/* (O) Y projection coordinate */
{
double adjust_lon(double x);	/* Function to adjust longitude to -180 - 180 */
double delta_lon;	/* Delta longitude (Given longitude - center */
double theta;
double delta_theta;
double con;
long i;

/* Forward equations
  -----------------*/
delta_lon = adjust_lon(lon - lon_center);
theta = lat;
con = 2.9604205062 * sin(lat);

/* Iterate using the Newton-Raphson method to find theta
  -----------------------------------------------------*/
for (i=0;;i++)
   {
   delta_theta = -(theta + sin(theta) - con) / (1.0 + cos(theta));
   theta += delta_theta;
   if (fabs(delta_theta) < EPSLN) break;
   /* if (i >= 30) perror("Iteration failed to converge","wagneriv-forward"); */
   if (i >= 30) p_error("Iteration failed to converge","Wagneriv-Forward");
   }
theta /= 2.0;
*x = 0.86310 * R * delta_lon * cos(theta) + false_easting;
*y = 1.56548 * R * sin(theta) + false_northing;
return(OK);
}
