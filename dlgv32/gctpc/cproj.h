#ifndef INCLUDED_CPROJ_H
#define INCLUDED_CPROJ_H

#include <math.h>

#define PI 	3.141592653589793238
#define HALF_PI (PI*0.5)
#define TWO_PI 	(PI*2.0)
#define EPSLN	1.0e-10
#define R2D     57.2957795131
/*
#define D2R     0.0174532925199
*/
#define D2R     1.745329251994328e-2
#define S2R	4.848136811095359e-6

#define OK	0
#define ERROR  -1
#define IN_BREAK -2

/* Misc macros
  -----------*/
#define SQUARE(x)       x * x   /* x**2 */
#define CUBE(x)     x * x * x   /* x**3 */
#define QUAD(x) x * x * x * x   /* x**4 */

#define GMAX(A, B)      ((A) > (B) ? (A) : (B)) /* assign maximum of a and b */
#define GMIN(A, B)      ((A) < (B) ? (A) : (B)) /* assign minimum of a and b */

#define IMOD(A, B)      (A) - (((A) / (B)) * (B)) /* Integer mod function */

/* Not part of the original gctpc distribution. */

#ifdef NEED_SINCOS
void
sincos(double val, double *sin_val, double *cos_val);
#endif

double asinz (double con);
double msfnz (double eccent, double sinphi, double cosphi);
double qsfnz (double eccent, double sinphi, double cosphi);
double phi1z (double eccent, double qs, long int *flag);
double phi2z(double eccent, double ts, long int *flag);
double phi3z(double ml, double e0, double e1, double e2, double e3, long int *flag);
double phi4z (double eccent, double e0, double e1, double e2, double e3,
              double a, double b, double *c, double *phi);
double pakcz(double pak);
double pakr2dm(double pak);
double tsfnz(double eccent, double phi, double sinphi);
int sign(double x);
double adjust_lon(double x);
double e0fn(double x);
double e1fn(double x);
double e2fn(double x);
double e3fn(double x);
double e4fn(double x);
double mlfn(double e0, double e1, double e2, double e3, double phi);
long calc_utm_zone(double lon);

#endif  // INCLUDED_CPROJ_H
