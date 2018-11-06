/*******************************************************************************
NAME                            POLAR STEREOGRAPHIC 

PURPOSE:	Transforms input longitude and latitude to Easting and
		Northing for the Polar Stereographic projection.  The
		longitude and latitude must be in radians.  The Easting
		and Northing values will be returned in meters.

PROGRAMMER              DATE
----------              ----
T. Mittan		2-26-93

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
  static double r_major;		/* major axis			*/
  static double r_minor;		/* minor axis			*/
  static double es;			/* eccentricity squared		*/
  static double e;			/* eccentricity			*/
  static double e4;			/* e4 calculated from eccentricity*/
  static double center_lon;		/* center longitude		*/
  static double center_lat;		/* center latitude		*/
  static double fac;			/* sign variable		*/
  static double ind;			/* flag variable		*/
  static double mcs;			/* small m			*/
  static double tcs;			/* small t			*/
  static double false_northing;		/* y offset in meters		*/
  static double false_easting;		/* x offset in meters		*/

/* Initialize the Polar Stereographic projection
  --------------------------------------------*/
long
psforint(double r_maj, double r_min, double c_lon, double c_lat, double false_east, double false_north) 

             				/* center longitude		*/
             				/* center latitude		*/
             				/* major axis			*/
             				/* minor axis			*/
                  			/* x offset in meters		*/
                   			/* y offset in meters		*/

{
double temp;				/* temporary variable		*/
double con1;				/* temporary angle		*/
double sinphi;				/* sin value			*/
double cosphi;				/* cos value			*/
double e4fn(double x);				/* function to compute e4	*/
double msfnz(double eccent, double sinphi, double cosphi);				/* function to compute m	*/
double tsfnz(double eccent, double phi, double sinphi);				/* function to compute t	*/

r_major = r_maj;
r_minor = r_min;
false_northing = false_north;
false_easting = false_east;
temp = r_minor / r_major;
es = 1.0 - SQUARE(temp);
e = sqrt(es);
e4 = e4fn(e);
center_lon = c_lon;
center_lat = c_lat;

if (c_lat < 0)
   fac = -1.0;
else
   fac = 1.0;
ind = 0;
if (fabs(fabs(c_lat) - HALF_PI) > EPSLN)
   {
   ind = 1;
   con1 = fac * center_lat; 
   sincos(con1,&sinphi,&cosphi);
   mcs = msfnz(e,sinphi,cosphi);
   tcs = tsfnz(e,con1,sinphi);
   }
/* Report parameters to the user
  -----------------------------*/
ptitle("POLAR STEREOGRAPHIC");
radius2(r_major, r_minor);
cenlon(center_lon);
offsetp(false_east,false_north);

return(OK);
}

/* Polar Stereographic forward equations--mapping lat,long to x,y
  --------------------------------------------------------------*/
long
psfor(double lon, double lat, double *x, double *y)
           			/* (I) Longitude 		*/
           			/* (I) Latitude 		*/
          			/* (O) X projection coordinate 	*/
          			/* (O) Y projection coordinate 	*/

{
double con1;			/* adjusted longitude		*/
double con2;			/* adjusted latitude		*/
double adjust_lon(double x);		/* function to adjust longitude	*/
double tsfnz(double eccent, double phi, double sinphi);			/* function to compute t	*/
double rh;			/* height above ellipsoid	*/
double sinphi;			/* sin value			*/
double ts;			/* value of small t		*/

con1 = fac * adjust_lon(lon - center_lon);
con2 = fac * lat;
sinphi = sin(con2);
ts = tsfnz(e,con2,sinphi);
if (ind != 0)
   rh = r_major * mcs * ts / tcs;
else
   rh = 2.0 * r_major * ts / e4;
*x = fac * rh * sin(con1) + false_easting;
*y = -fac * rh * cos(con1) + false_northing;;

return(OK);
}
