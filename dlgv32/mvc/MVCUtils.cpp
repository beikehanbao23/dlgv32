
#include "MVCUtils.h"

void canonicalRect(int *x1, int *y1, int *x2, int *y2)
{
   // The "canonical" form of a rectangle is such that (x1,y1) is
   // the "upper left" corner and (x2,y2) is the "lower right" corner.
   // Mathmatically, we want x1 <= x2 and y1 >= y2

   int tmp;

   if (*x1 > *x2)
      {
         tmp = *x1;
         *x1 = *x2;
         *x2 = tmp;
      }

   if (*y1 < *y2)
      {
         tmp = *y1;
         *y1 = *y2;
         *y2 = tmp;
      }
}

void canonicalRect(double *x1, double *y1, double *x2, double *y2)
{
   // The "canonical" form of a rectangle is such that (x1,y1) is
   // the "upper left" corner and (x2,y2) is the "lower right" corner.
   // Mathmatically, we want x1 <= x2 and y1 >= y2

   double tmp;

   if (*x1 > *x2)
      {
         tmp = *x1;
         *x1 = *x2;
         *x2 = tmp;
      }

   if (*y1 < *y2)
      {
         tmp = *y1;
         *y1 = *y2;
         *y2 = tmp;
      }
}

/* Author: Jamie Moyers */
/* Started: October 7 1991 */
/* Modification History: */
/*    November 29 1994 -- Modified for use with MVC graphics package.

/* Implementation of the Cohen-Sutherland Outcode algorithm for */
/* clipping an arbitrary line against a rectangle. The main procedure */
/* is called clip_line. */

/* Bit masks for outcode: xxxx => top bottom right left */
#define TOP 0x08
#define BOTTOM 0x04
#define RIGHT 0x02
#define LEFT 0x01
#define INSIDE 0x00

int compute_outcode(double x1,double y1,double rx1,double ry1,
                    double rx2,double ry2)
{
   /* Determines outcodes for (x1,y1) relative to rectangle defined */
   /* by (rx1,ry1),(rx2,ry2). It is assumed (rx1,ry1) = lower left */
   /* corner, (rx2,ry2) = upper right corner. */

   int oc;

   oc = 0;

   if (y1 > ry2)
      oc = oc | TOP;
   else
      if (y1 < ry1)
         oc = oc | BOTTOM;

   if (x1 > rx2)
      oc = oc | RIGHT;
   else 
      if (x1 < rx1)
         oc = oc | LEFT;

   return(oc);
}

bool clip_line(double *x1, double *y1, double *x2, double *y2,
               double rec_x1, double rec_y1, double rec_x2, double rec_y2)
{
#if 0
      Input: 
         (x1,y1),(x2,y2)    Endpoints of line to clip to rectangle.

         (rec_x1,rec_y1),
         (rec_x2,rec_y2)    Lower left and upper right corners of 
                            rectangle to clip to.
      Output:
         return value       Set to one of the following:
                            false - None of the line segment is visible.
                            true - Part or all of line is visible.

         (x1,y1),(x2,y2)    Replaced with endpoints of new line resulting
                            from clipping old line to clip rectangle.
                            (Different from input values only if 
                             return_code = 1)
#endif

   bool accept,done,visible;
   int outcode0,outcode1,outcodeOut;
   double x,y;

   accept = false;
   done = false;

   outcode0 = compute_outcode(*x1,*y1,rec_x1,rec_y1,
                              rec_x2,rec_y2);
   outcode1 = compute_outcode(*x2,*y2,rec_x1,rec_y1,
                              rec_x2,rec_y2);

   visible = false;  /* None of line is visible. */
   do
      {
         if ((outcode0 == INSIDE) && (outcode1 == INSIDE))
            {
               /* Trivial accept and exit */
               accept = true;
               done = true;
               visible = true;  /* Part or all is visible. */
            }
         else
            if ((outcode0 & outcode1) != 0)
               /* Logical intersection is true, so trival reject and exit */
               done = true;
            else
               /* Failed both tests, so calculate the line segment to clip. */
               /* from and outside point to an intersection with clip edge. */
               {
                  /* At least one endpoint is outside the clip rectangle. */
                  /* Pick it. */
                  if (outcode0 != 0)
                     outcodeOut = outcode0;
                  else
                     outcodeOut = outcode1;
                  /* Now find intersection point */
                  if (outcodeOut & TOP) 
                     {
                        x = *x1 + (*x2 - *x1) * (rec_y2 - *y1) / (*y2 - *y1);
                        y = rec_y2;
                     }
                  else if (outcodeOut & BOTTOM) 
                     {
                        x = *x1 + (*x2 - *x1) * (rec_y1 - *y1) / (*y2 - *y1);
                        y = rec_y1;
                     }
                  else if (outcodeOut & RIGHT)
                     {
                        y = *y1 + (*y2 - *y1) * (rec_x2 - *x1) / (*x2 - *x1);
                        x = rec_x2;
                     }
                  else if (outcodeOut & LEFT)
                     {
                        y = *y1 + (*y2 - *y1) * (rec_x1 - *x1) / (*x2 - *x1);
                        x = rec_x1;
                     }
                  /* Now move outside point to intersection point to clip, */
                  /* and get ready for next pass. */
                  if (outcodeOut == outcode0)
                     {
                        *x1 = x;
                        *y1 = y;
                        outcode0 = compute_outcode(*x1,*y1,rec_x1,rec_y1,
                                                   rec_x2,rec_y2);
                     }
                  else
                     {
                        *x2 = x;
                        *y2 = y;
                        outcode1 = compute_outcode(*x2,*y2,rec_x1,rec_y1,
                                                   rec_x2,rec_y2);
                     }
               }
      }
   while (!done);

   return(visible);

}