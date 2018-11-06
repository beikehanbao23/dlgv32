#ifndef MVCUTILS_H
#define MVCUTILS_H

/*
#ifdef BOOL
	#define bool BOOL
#else
	#define bool int
#endif

#define true 1
#define false 0
*/

//
// Several Utility functions used by the MVC stuff.
//
// Author: Jamie Moyers
// Started: November 25 1994
//

void canonicalRect(int *x1, int *y1, int *x2, int *y2);
void canonicalRect(double *x1, double *y1, double *x2, double *y2);

   // The "canonical" form of a rectangle is such that (x1,y1) is
   // the "upper left" corner and (x2,y2) is the "lower right" corner.
   // Mathmatically, we want x1 <= x2 and y1 >= y2

bool clip_line(double *x1, double *y1, double *x2, double *y2,
               double rec_x1, double rec_y1, double rec_x2, double rec_y2);

   // (x1,y1)(x2,y2) line to be clipped.
   // (rec_x1,rec_y1) (rec_x2,rec_y2) clipping rectangle.
   // returns True if line is partially or wholly visible.

#endif // MVCUTILS_H


