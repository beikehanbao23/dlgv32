/*******************************************************************************
NAME                             STEREOGRAPHIC 

PURPOSE:	Transforms input Easting and Northing to longitude and
		latitude for the Stereographic projection.  The
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
static double sin_p10;		/* sin of center latitude		*/
static double cos_p10;		/* cos of center latitude		*/

/* Initialize the Stereographic projection
  --------------------------------------*/
long
sterinvint(double r_maj, double center_lon, double center_lat, double false_east, double false_north) 

             			/* major axis			*/
                  		/* center longitude		*/
                  		/* center latitude		*/
                  		/* x offset in meters		*/
                   		/* y offset in meters		*/
{
double temp;			/* temporary variable		*/
double e0fn(double x),e1fn(double x),e2fn(double x),e3fn(double x); 		/* functions	*/

/* Place parameters in static storage for common use
  -------------------------------------------------*/
r_major = r_maj;
lon_center = center_lon;
lat_origin = center_lat;
false_northing = false_north;
false_easting = false_east;

sincos(center_lat,&sin_p10,&cos_p10);

/* Report parameters to the user
  -----------------------------*/
ptitle("STEREOGRAPHIC"); 
radius(r_major);
cenlonmer(lon_center);
origin(lat_origin);
offsetp(false_easting,false_northing);
return(OK);
}


/* Stereographic inverse equations--mapping x,y to lat/long
  -------------------------------------------------------*/
long
sterinv(double x, double y, double *lon, double *lat)
         			/* (O) X projection coordinate 	*/
         			/* (O) Y projection coordinate 	*/
            			/* (I) Longitude 		*/
            			/* (I) Latitude 		*/
{
double adjust_lon(double x);	/* Function to adjust longitude to -180 - 180 	*/
double msfnz(double eccent, double sinphi, double cosphi);		/* function to compute m			*/
double rh;		/* height above ellipsoid			*/
double z;		/* angle					*/
double sinz,cosz;	/* sin of z and cos of z			*/
double con;

/* Inverse equations
  -----------------*/
x -= false_easting;
y -= false_northing;
rh = sqrt(x * x + y * y);
z = 2.0 * atan(rh / (2.0 * r_major));
sincos(z,&sinz,&cosz);
*lon = lon_center;
if (fabs(rh) <= EPSLN)
   {
   *lat = lat_origin;
   return(OK);
   }
else
   {
   *lat = asin(cosz * sin_p10 + (y * sinz * cos_p10) / rh);
   con = fabs(lat_origin) - HALF_PI;
   if (fabs(con) <= EPSLN)
     {
     if (lat_origin >= 0.0)
       {
       *lon = adjust_lon(lon_center + atan2(x, -y));
       return(OK);
       }
     else
       {
       *lon = adjust_lon(lon_center - atan2(-x, y));
       return(OK);
       }
     }
   else
     {
     con = cosz - sin_p10 * sin(*lat);
     if ((fabs(con) < EPSLN) && (fabs(x) < EPSLN))
        return(OK);
     else
       *lon = adjust_lon(lon_center + atan2((x * sinz * cos_p10), (con * rh)));
     }
   }

return(OK);
}
