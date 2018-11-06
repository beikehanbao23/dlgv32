#include <stdio.h>
#include <math.h>
#include "Projection2D.h"
#include "MVCUtils.h"
//#include "Global.h"

void Projection2D::adjustWSW(double *x1, double *y1, double *x2, double *y2)
{
   double wd,hd;
   double ww,hw;
   double ar_ddw,ar_wsw;
   double new_ww,new_hw;
#if 0
   char debugbuf[1000];
#endif 

   // Adjust requested WSW to be proportional to DDW.

   wd = ddw_x2 - ddw_x1;
   hd = ddw_y1 - ddw_y2;
   ar_ddw = wd / hd;  // Aspect ratio of Display Device Window.

   ww = *x2 - *x1;
   hw = *y1 - *y2;
   ar_wsw = ww / hw; // Aspect ratio of World Space Window.


#if 0
   GlobalDebug.message("In Projection2D::adjustWSW()");
   sprintf(debugbuf,"wd,hd: %f,%f",wd,hd);
   GlobalDebug.message(debugbuf);
#endif

   if (ar_wsw < ar_ddw)
      {
         // Adjust width of WSW
         //ww = hw * ar_ddw;
         //*x2 = *x1 + ww;
         new_ww = hw * ar_ddw;
         *x2 = *x2 + ((new_ww - ww) / 2.0);
         *x1 = *x1 - ((new_ww - ww) / 2.0);
      }
   else
      {
         // Adjust height of WSW
         //hw = ww / ar_ddw;
         //*y2 = *y1 - hw;
         new_hw = ww / ar_ddw;
         *y2 = *y2 - ((new_hw - hw) / 2.0);
         *y1 = *y1 + ((new_hw - hw) / 2.0);
      }

}

Projection2D::Projection2D(void)
{
   fullview_set = false;
   _maintain_aspect_ratio = false;
}

void Projection2D::setWorldSpaceWin(double x1, double y1,
                                 double x2, double y2)
{
   // Sets WSW to be rectangle defined by (x1,y1) (x2,y2) as corners.

   canonicalRect(&x1,&y1,&x2,&y2);
   
   if (_maintain_aspect_ratio)
      {
         adjustWSW(&x1,&y1,&x2,&y2);
      }

   wsw_x1 = x1;
   wsw_y1 = y1;
   wsw_x2 = x2;
   wsw_y2 = y2;

}

void Projection2D::getWorldSpaceWin(double *x1, double *y1,
                                    double *x2, double *y2)
{
   *x1 = wsw_x1;
   *y1 = wsw_y1;
   *x2 = wsw_x2;
   *y2 = wsw_y2;
}

void Projection2D::setDisplayDevWin(int x1, int y1, int x2, int y2)
{
   // Sets DDW to be rectangle defined by (x1,y1) (x2,y2) as corners.
   // Normally this is set to (0,0) (width, height) where 
   // width and height are the full width and height of the Display
   // Device. 

   double new_wx1, new_wy1;
   double new_wx2, new_wy2;
#if 0
   char debugbuf[1000];
#endif

   canonicalRect(&x1,&y1,&x2,&y2);

#if 0
   GlobalDebug.message("In Projection2D::setDisplayDevWin()");
   sprintf(debugbuf,"x1,y1: (%d,%d)   x2,y2: (%d,%d)",x1,y1,x2,y2);
   GlobalDebug.message(debugbuf);
   sprintf(debugbuf,"wsw_x1,wsw_y1: (%f,%f)   wsw_x2,wsw_y2: (%f,%f)",
           wsw_x1,wsw_y1,wsw_x2,wsw_y2);
   GlobalDebug.message(debugbuf);
#endif

   if (_maintain_aspect_ratio)
      {
         new_wx1 = getWorldSpaceX(x1,y1);
         new_wy1 = getWorldSpaceY(x1,y1);
         new_wx2 = getWorldSpaceX(x2,y2);
         new_wy2 = getWorldSpaceY(x2,y2);
         wsw_x1 = new_wx1; wsw_y1 = new_wy1;
         wsw_x2 = new_wx2; wsw_y2 = new_wy2;
         canonicalRect(&wsw_x1,&wsw_y1,&wsw_x2,&wsw_y2);
      }

   ddw_x1 = x1 * 1.0; 
   ddw_y1 = y1 * 1.0;
   ddw_x2 = x2 * 1.0; 
   ddw_y2 = y2 * 1.0;

#if 0
   if (_maintain_aspect_ratio)
      {
         tx1 = wsw_x1; ty1 = wsw_y1;
         tx2 = wsw_x2; ty2 = wsw_y2;
         adjustWSW(&tx1,&ty1,&tx2,&ty2);
         wsw_x1 = tx1; wsw_y1 = ty1;
         wsw_x2 = tx2; wsw_y2 = ty2;
      }
#endif

}

void Projection2D::getDisplayDevWin(int *x1, int *y1, int *x2, int *y2)
{
   // Returns (x1,y1)(x2,y2) set to corners of Display Device window.
   *x1 = (int) ddw_x1;
   *y1 = (int) ddw_y1;
   *x2 = (int) ddw_x2;
   *y2 = (int) ddw_y2;
}


bool Projection2D::recalc(void)
{
   // This method recalculates the projection. It must be called
   // by the user of this class whenever any projection parameters
   // have been altered.

   return(true);
}

int Projection2D::getDisplayDeviceX(double x, double y)
{
   return(0);
}

int Projection2D::getDisplayDeviceY(double x, double y)
{
   return(0);
}


double Projection2D::getWorldSpaceX(int x, int y)
{
   return(0.0);
}

double Projection2D::getWorldSpaceY(int x, int y)
{
   return(0.0);
}

bool Projection2D::inverseExists(void)
{
   // Returns 'true' if an inverse projection is defined for the
   // current projection. 'false' otherwise.

   return false;  // Safe default.
}

void Projection2D::pan(double newcenter_x, double newcenter_y)
{
   // Moves the center of the World Space Window to
   // (newcenter_x, newcenter_y) without changing its size.

   double w,h;

   w = wsw_x2 - wsw_x1;
   h = wsw_y1 - wsw_y2;

   wsw_x1 = newcenter_x - (w / 2.0);
   wsw_y1 = newcenter_y + (h / 2.0);

   wsw_x2 = newcenter_x + (w / 2.0);
   wsw_y2 = newcenter_y - (h / 2.0);

   recalc();
}

void Projection2D::zoomBy(double magfactor)
{
   // Zooms current projection by magfactor. Center of projection
   // does not move. Positive magfactors make things "bigger" 
   // (World Coordinate window gets smaller). Negative magfactors
   // make things "smaller" (World Coordinate window get bigger).

   double w,h;
   double cx,cy;
   double tx1,ty1;
   double tx2,ty2;

   w = wsw_x2 - wsw_x1;
   h = wsw_y1 - wsw_y2;
   cx = wsw_x1 + (w / 2.0);
   cy = wsw_y2 + (h / 2.0);

   if (magfactor > 0.0)
      magfactor = 1.0 / magfactor;
   else
      magfactor = fabs(magfactor);

   w = w * magfactor;
   h = h * magfactor;

   wsw_x1 = cx - (w / 2.0);
   wsw_y1 = cy + (h / 2.0);

   wsw_x2 = cx + (w / 2.0);
   wsw_y2 = cy - (h / 2.0);

#if 0
   if (_maintain_aspect_ratio)
      {
         tx1 = wsw_x1; ty1 = wsw_y1;
         tx2 = wsw_x2; ty2 = wsw_y2;
         adjustWSW(&tx1,&ty1,&tx2,&ty2);
         wsw_x1 = tx1; wsw_y1 = ty1;
         wsw_x2 = tx2; wsw_y2 = ty2;
      }
#endif

   recalc();
}

void Projection2D::zoomTo(double x, double y, double magfactor)
{
   // A combination of 'pan' and 'zoomBy', this function magnifies the
   // current projection and centers it on (x,y);

   zoomBy(magfactor);
   pan(x,y);

}

void Projection2D::setFullView(double x1, double y1, double x2, double y2)
{
   // Projection will remember the WS rectangle (x1,y1) (x2,y2), and
   // reset to this region when 'zoomFullView' is called.

   fv_x1 = x1;
   fv_y1 = y1;
   fv_x2 = x2;
   fv_y2 = y2;
   canonicalRect(&fv_x1,&fv_y1,&fv_x2,&fv_y2);
   fullview_set = true;
}

void Projection2D::getFullView(double *x1, double *y1, double *x2, double *y2)
{
   *x1 = fv_x1;
   *y1 = fv_y1;
   *x2 = fv_x2;
   *y2 = fv_y2;
}

void Projection2D::zoomFullView(void)
{
   // Causes the World Space Window to become the region set by 
   // 'setFullView'. If no view has been set, the current projection
   // is unchanged.

   double tx1,ty1;
   double tx2,ty2;

   if (fullview_set)
      {
         wsw_x1 = fv_x1;
         wsw_y1 = fv_y1;
         wsw_x2 = fv_x2;
         wsw_y2 = fv_y2;
         if (_maintain_aspect_ratio)
            {
               tx1 = wsw_x1; ty1 = wsw_y1;
               tx2 = wsw_x2; ty2 = wsw_y2;
               adjustWSW(&tx1,&ty1,&tx2,&ty2);
               wsw_x1 = tx1; wsw_y1 = ty1;
               wsw_x2 = tx2; wsw_y2 = ty2;
            }      
      }

   recalc();
}

void Projection2D::setMaintainAspectRatio(bool val)
{
   _maintain_aspect_ratio = val;
}

bool Projection2D::clipLine(double *x1, double *y1, double *x2, double *y2)
{
   // Clips line (x1,y1)(x2,y2) to World Space Window. Returns 'true' if
   // part or all of line is visible. Returns false if line is 
   // completely out of World Space Window.

   return(clip_line(x1,y1,x2,y2,wsw_x1,wsw_y2,wsw_x2,wsw_y1));
}

bool Projection2D::inDisplayDeviceWindow(int x, int y)
{
   // returns true if (x,y) is inside or on the edge of the 
   // Display Device Window.

   bool result;

   result = true;

   if ((ddw_x1 > x) || (ddw_x2 < x) ||
       (ddw_y1 < y) || (ddw_y2 > y))
      result = false;

   return result;
}