/*******************************************************************************
NAME                            POLYCONIC 

PURPOSE:	Transforms input Easting and Northing to longitude and
		latitude for the Polyconic projection.  The
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
static double r_minor;		/* minor axis 				*/
static double lon_center;	/* Center longitude (projection center) */
static double lat_origin;	/* center latitude			*/
static double e0,e1,e2,e3;	/* eccentricity constants		*/
static double e,es,esp;		/* eccentricity constants		*/
static double ml0;		/* small value m			*/
static double false_northing;	/* y offset in meters			*/
static double false_easting;	/* x offset in meters			*/

/* Initialize the POLYCONIC projection
  ----------------------------------*/
long
polyinvint(double r_maj, double r_min, double center_lon, double center_lat, double false_east, double false_north) 

             			/* major axis			*/
             			/* minor axis			*/
                  		/* center longitude		*/
                  		/* center latitude		*/
                  		/* x offset in meters		*/
                   		/* y offset in meters		*/
{
double temp;			/* temporary variable		*/
double e0fn(double x),e1fn(double x),e2fn(double x),e3fn(double x),mlfn(double e0, double e1, double e2, double e3, double phi); 	/* functions	*/

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
e0 = e0fn(es);
e1 = e1fn(es);
e2 = e2fn(es);
e3 = e3fn(es);
ml0 = mlfn(e0, e1, e2, e3, lat_origin);

/* Report parameters to the user
  -----------------------------*/
ptitle("POLYCONIC"); 
radius2(r_major, r_minor);
cenlonmer(lon_center);
origin(lat_origin);
offsetp(false_easting,false_northing);
return(OK);
}


/* Polyconic inverse equations--mapping x,y to lat/long
  ---------------------------------------------------*/
long
polyinv(double x, double y, double *lon, double *lat)
         			/* (O) X projection coordinate 	*/
         			/* (O) Y projection coordinate 	*/
            			/* (I) Longitude 		*/
            			/* (I) Latitude 		*/
{
double adjust_lon(double x);	/* Function to adjust longitude to -180 - 180 	*/
double asinz(double con);
double mlfn(double e0, double e1, double e2, double e3, double phi);		/* function to compute small m			*/
double phi4z(double eccent, double e0, double e1, double e2, double e3, double a, double b, double *c, double *phi);		/* function to compute latitude			*/
double sin_phi, cos_phi;/* sin and cos value				*/
double al;		/* temporary values				*/
double b;		/* temporary values				*/
double c;		/* temporary values				*/
double con, ml;		/* cone constant, small m			*/
long iflg;		/* error flag					*/

/* Inverse equations
  -----------------*/
x -= false_easting;
y -= false_northing;
al = ml0 + y/r_major;
iflg = 0;
if (fabs(al) <= .0000001)
   {
   *lon = x/r_major + lon_center;
   *lat = 0.0;
   }
else
   {
   b = al * al + (x/r_major) * (x/r_major);
   iflg = phi4z(es,e0,e1,e2,e3,al,b,&c,lat);
   if (iflg != 0)
      return(74);
   *lon = adjust_lon((asinz(x * c / r_major) / sin(*lat)) + lon_center);
   }

return(OK);
}
