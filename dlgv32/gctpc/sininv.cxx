/*******************************************************************************
NAME                  		SINUSOIDAL

PURPOSE:	Transforms input Easting and Northing to longitude and
		latitude for the Sinusoidal projection.  The
		Easting and Northing must be in meters.  The longitude
		and latitude values will be returned in radians.

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
sininvint(double r, double center_long, double false_east, double false_north) 
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

/* Sinusoidal inverse equations--mapping x,y to lat,long 
  -----------------------------------------------------*/
long
sininv(double x, double y, double *lon, double *lat)
         		/* (I) X projection coordinate */
         		/* (I) Y projection coordinate */
            		/* (O) Longitude */
            		/* (O) Latitude */
{
double adjust_lon(double x);    /* Function to adjust longitude to -180 - 180 */
double temp;		/* Re-used temporary variable */

/* Inverse equations
  -----------------*/
x -= false_easting;
y -= false_northing;
*lat = y / R;
if (fabs(*lat) > HALF_PI) 
   {
   p_error("Input data error","sinusoidal-inverse");
   return(164);
   }
temp = fabs(*lat) - HALF_PI;
if (fabs(temp) > EPSLN)
   {
   temp = lon_center + x / (R * cos(*lat));
   *lon = adjust_lon(temp);
   }
else *lon = lon_center;
return(OK);
}

