#ifndef PROJECTION2D_H
#define PROJECTION2D_H

// this definitions are needed for use with MFC
/* #ifndef BOOL
	#define BOOL int
#endif */

/* #define bool BOOL
#define true 1
#define false 0 */

class Projection2D
{
   // Abstract Two Dimensional Projection class

   // Projection2D maps World Space Coordinates to Display Device Coordinates.
   // The "World Space Window" (WSW) is a region in World Space.
   // This region is projected onto the Display Device Window (DDW)
   // a region in Display Device space.
   //
   // World Space and Display Device space are assumed to be 
   // two dimensional.

private:

protected:

   double wsw_x1,wsw_y1;  // Corners of World Space Window (WSW)
   double wsw_x2,wsw_y2;

   double ddw_x1,ddw_y1;  // Corners of Display Device Window (DDW)
   double ddw_x2,ddw_y2;

   double fv_x1,fv_y1;    // "Full view" coordinates. 
   double fv_x2,fv_y2;
   bool fullview_set;     // 'true' if a Full View has been set up.

   bool _maintain_aspect_ratio;

   void adjustWSW(double *x1, double *y1, double *x2, double *y2);

public:
  
   Projection2D(void);

   virtual void setWorldSpaceWin(double x1, double y1,
                                 double x2, double y2);
      // Sets WSW to be rectangle defined by (x1,y1) (x2,y2) as corners.

   virtual void getWorldSpaceWin(double *x1, double *y1, 
                                 double *x2, double *y2);
      // Returns (x1,y1) (x2,y2) set to corners of World Space window.

   virtual void setDisplayDevWin(int x1, int y1, int x2, int y2);
      // Sets DDW to be rectangle defined by (x1,y1) (x2,y2) as corners.
      // Normally this is set to (0,0) (width, height) where 
      // width and height are the full width and height of the Display
      // Device. 

   virtual void getDisplayDevWin(int *x1, int *y1, int *x2, int *y2);
      // Returns (x1,y1)(x2,y2) set to corners of Display Device window.

   virtual bool recalc(void);
      // This method recalculates the projection. It must be called
      // by the user of this class whenever any projection parameters
      // have been altered. 

   virtual int getDisplayDeviceX(double x, double y);
   virtual int getDisplayDeviceY(double x, double y);
      // These two functions return either the Display Device X
      // or Display Device Y coordinate given a point in World Space.

   virtual double getWorldSpaceX(int x, int y);
   virtual double getWorldSpaceY(int x, int y);
      // These two functions return either the World Space X or
      // World Space Y coordinate given a point in Device Space.
      // This "inverse projection" may not be possible, in which case
      // '0' (zero) is returned for both. Callers should ensure that
      // an inverse mapping exists by calling 'inverseExists()'.

   virtual bool inverseExists(void);
      // Returns 'true' if an inverse projection is defined for the
      // current projection. 'false' otherwise.

   virtual void pan(double newcenter_x, double newcenter_y);
      // Moves the center of the World Space Window to
      // (newcenter_x, newcenter_y) without changing its size.

   virtual void zoomBy(double magfactor);
      // Zooms current projection by magfactor. Center of WSW
      // does not move. Positive magfactors make things "bigger" 
      // (World Space Window gets smaller). Negative magfactors
      // make things "smaller" (World Space Window get bigger).

   virtual void zoomTo(double x, double y, double magfactor);
      // A combination of 'pan' and 'zoomBy', this function magnifies the
      // current projection and centers it on (x,y);

   virtual void setFullView(double x1, double y1, double x2, double y2);
      // Projection will remember the WS rectangle (x1,y1) (x2,y2), and
      // reset to this region when 'zoomFullView' is called.

   virtual void getFullView(double *x1, double *y1, double *x2, double *y2);
      // Returns "full view" rectangle.

   virtual void zoomFullView(void);
      // Causes the World Space Window to become the region set by 
      // 'setFullView'. If no view has been set, the current projection
      // is unchanged.

   virtual void setMaintainAspectRatio(bool val);
      // If true, forces width and height of World Space Window and
      // the width and height of the Display Device Window to be 
      // proportional to each other. 
      // Let:
      //    ww = width of WSW
      //    hw = height of WSW
      //    wd = width of DDW
      //    hd = height of DDW
      // Then this method forces the following relationship
      //    (ww / hw) = (wd / hd)
      // by altering the world space window parameters. The WSW will never
      // be smaller than requested, but may grow in width or height to
      // make the equality true.
      // Default: false

   virtual bool clipLine(double *x1, double *y1, double *x2, double *y2);
      // Clips line (x1,y1)(x2,y2) to World Space Window. Returns 'true' if
      // part or all of line is visible. Returns false if line is 
      // completely out of World Space Window.

   virtual bool inDisplayDeviceWindow(int x, int y);
      // returns true if (x,y) is inside or on the edge of the 
      // Display Device Window.
};

#endif // PROJECTION2D_H
