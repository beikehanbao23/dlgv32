#ifndef RECTPROJ2D_H
#define RECTPROJ2D_H

#include "Projection2D.h"

class RectProj2D : public Projection2D
{
   // Rectangular Projection class.
 
   // Treats world space as a rectangular coordinate system, and simply
   // scales it to fit on the device. 



   public:

      enum OriginLocation {UpperLeft, LowerLeft};
   
      RectProj2D(OriginLocation ol = UpperLeft);

      void setWorldSpaceWin(double x1, double y1, double x2, double y2);

      void setDisplayDevWin(int x1, int y1, int x2, int y2);

      bool recalc(void);

      int getDisplayDeviceX(double x, double y);
      int getDisplayDeviceY(double x, double y);
         // These two functions return either the Display Device X
         // or Display Device Y coordinate given a point in World Space.

      double getWorldSpaceX(int x, int y);
      double getWorldSpaceY(int x, int y);
         // These two functions return either the World Space X or
         // World Space Y coordinate given a point in Device Space.
         // This "inverse projection" may not be possible, in which case
         // '0' (zero) is returned for both. Callers should ensure that
         // an inverse mapping exists by calling 'inverseExists()'.

      bool inverseExists(void);
         // An inverse (DDW->WSW) projection exists. Returns 'true'.

   protected:

      double a,b,c,d;  // Projection constants.
      OriginLocation _origLoc;
};

#endif // RECTPROJ2D_H
