/*******************************************************************************
NAME                  		SINUSOIDAL

PURPOSE:	Transforms input longitude and latitude to Easting and
		Northing for the Sinusoidal projection.  The
		longitude and latitude must be in radians.  The Easting
		and Northing values will be returned in meters.

PROGRAMMER              DATE            
----------              ----           
D. Steinwand, EROS      May, 1991     

This function was adapted from the Sinusoidal projection code (FORTRAN) in the 
General Cartographic Transformation Package software which is available from 
the U.S. Geological Survey National Mapping Division.
 
ALGORITHM REFERENCES

1.  Snyder, John P., "Map Projections--A Working Manual", U.S. Geological
    Survey Professional Paper 1395 (Supersedes USGS Bulletin 1532), United
    State Government Printing Office, Washington D.C., 1987.

2.  "Software Documentation for GCTP General Cartographic Transformation
    Package", U.S. Geological Survey National Mapping Division, May 1982.
*******************************************************************************/
#include "gctpc/cproj.h"
#include "gctpc/report.h"

/* Variables common to all subroutines in this code file
  -----------------------------------------------------*/
static double lon_center;	/* Center longitude (projection center) */
static double R;		/* Radius of the earth (sphere) 	*/
static double false_easting;	/* x offset in meters			*/
static double false_northing;	/* y offset in meters			*/

/* Initialize the Sinusoidal projection
  ------------------------------------*/
long
sinforint(double r, double center_long, double false_east, double false_north) 
          			/* (I) Radius of the earth (sphere) 	*/
                   		/* (I) Center longitude 		*/
                  		/* x offset in meters			*/
                   		/* y offset in meters			*/
{
/* Place parameters in static storage for common use
  -------------------------------------------------*/
R = r;
lon_center = center_long;
false_easting = false_east;
false_northing = false_north;

/* Report parameters to the user
  -----------------------------*/
ptitle("SINUSOIDAL"); 
radius(r);
cenlon(center_long);
offsetp(false_easting,false_northing);
return(OK);
}

/* Sinusoidal forward equations--mapping lat,long to x,y
  -----------------------------------------------------*/
long
sinfor(double lon, double lat, double *x, double *y)
           			/* (I) Longitude */
           			/* (I) Latitude */
          			/* (O) X projection coordinate */
          			/* (O) Y projection coordinate */
{
double adjust_lon(double x);	/* Function to adjust longitude to -180 - 180 */
double delta_lon;	/* Delta longitude (Given longitude - center */

/* Forward equations
  -----------------*/
delta_lon = adjust_lon(lon - lon_center);
*x = R * delta_lon * cos(lat) + false_easting;
*y = R * lat + false_northing;
return(OK);
}
