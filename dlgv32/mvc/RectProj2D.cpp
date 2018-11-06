
#include <stdio.h>
#include "RectProj2D.h"
#include "MVCUtils.h"

RectProj2D::RectProj2D(RectProj2D::OriginLocation ol)
          : _origLoc(ol)
{
   // Give WSW and DDW initial values so that we can precompute
   // constants in the projection equations.


   wsw_x1 = 0.0; wsw_y1 = 1.0;
   wsw_x2 = 1.0; wsw_y2 = 0.0;
   canonicalRect(&wsw_x1,&wsw_y1,&wsw_x2,&wsw_y2);

   ddw_x1 = 0.0; ddw_y1 = 0.0;
   ddw_x2 = 100.0; ddw_y2 = 100.0;
   canonicalRect(&ddw_x1,&ddw_y1,&ddw_x2,&ddw_y2);

   recalc();
}

void RectProj2D::setWorldSpaceWin(double x1, double y1, double x2, double y2)
{
   Projection2D::setWorldSpaceWin(x1,y1,x2,y2);

   recalc();
}

void RectProj2D::setDisplayDevWin(int x1, int y1, int x2, int y2)
{
   Projection2D::setDisplayDevWin(x1,y1,x2,y2);

   recalc();
}

bool RectProj2D::recalc(void)
{
   double ddw_deltax, ddw_deltay;
   double wsw_deltax, wsw_deltay;

   ddw_deltax = ddw_x2 - ddw_x1;
   ddw_deltay = ddw_y1 - ddw_y2;

   wsw_deltax = wsw_x2 - wsw_x1;
   wsw_deltay = wsw_y1 - wsw_y2;

   a = ddw_deltax / wsw_deltax;
   b = ddw_deltay / wsw_deltay;
   c = wsw_deltax / ddw_deltax;
   d = wsw_deltay / ddw_deltay;

   return true;
}

int RectProj2D::getDisplayDeviceX(double px, double py)
{
   int qx;

   //qx = (int) (((px - wsw_x1) / (wsw_x2 - wsw_x1)) * (ddw_x2 - ddw_x1));
   qx = (int) ((px - wsw_x1) * a);
   qx = (int) (qx + ddw_x1);

   return qx;
}

int RectProj2D::getDisplayDeviceY(double px, double py)
{
   int qy;

   //qy = (int) (((wsw_y1 - py) / (wsw_y1 - wsw_y2)) * (ddw_y1 - ddw_y2));
   if (_origLoc == UpperLeft)
      qy = (int) ((wsw_y1 - py) * b);
   else
      qy = (int) ((py - wsw_y2) * b);
   qy = (int) (qy + ddw_y2);

   return qy;
}


double RectProj2D::getWorldSpaceX(int qx, int qy)
{
   double px;

   //px = (((qx - ddw_x1) / (ddw_x2 - ddw_x1)) * (wsw_x2 - wsw_x1));
   px = (qx - ddw_x1) * c;
   px = px + wsw_x1;

   return px;
}

double RectProj2D::getWorldSpaceY(int qx, int qy)
{
   double py;

   //py = (((ddw_y1 - qy) / (ddw_y1 - ddw_y2)) * (wsw_y1 - wsw_y2));
   if (_origLoc == UpperLeft)
      py = (ddw_y1 - qy) * d;
   else
      py = (qy - ddw_y2) * d;
   py = py + wsw_y2;

   return py;
}

bool RectProj2D::inverseExists(void)
{
   // This projection has an inverse.

   return true;
}


