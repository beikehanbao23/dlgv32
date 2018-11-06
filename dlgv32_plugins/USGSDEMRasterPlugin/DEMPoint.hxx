#ifndef INCLUDED_DEMPOINT_HXX
#define INCLUDED_DEMPOINT_HXX


#ifndef INCLUDED_DEMTYPES_HXX
#include "DEMTypes.hxx"
#endif

class DEMPoint
{
   public:
      DEMPoint(double x = 0.0, double y = 0.0);
     
      // Accessors
      double getX() const;
      double getY() const;
      void getXY(double& x, double& y) const;

      // Modifiers
      void setX(double x);
      void setY(double y);
      void setXY(double x, double y);
      bool operator<(DEMPoint const& rhs) const {return false;}
      bool operator==(DEMPoint const& rhs) const {return false;}

   private:
      double _x;
      double _y;
};

// Inline Methods for class DEMPoint

inline
DEMPoint::DEMPoint(double x, double y)
{
   _x = x;
   _y = y;
}

inline
double
DEMPoint::getX() const
{
   return _x;
}

inline
double
DEMPoint::getY() const
{
   return _y;
}

inline
void
DEMPoint::getXY(double& x, double& y) const
{
   x = _x;
   y = _y;
}

inline
void
DEMPoint::setX(double x)
{
   _x = x;
}

inline
void
DEMPoint::setY(double y)
{
   _y = y;
}

inline
void
DEMPoint::setXY(double x, double y)
{
   _x = x;
   _y = y;
}



// The Microsoft Visual C++ 4.2 STL implementation doesn't handle default
// template parameters correctly. Thus this hack.
#ifdef WIN32
//   typedef std::vector<DEMPoint> DEMPointVector;
   typedef vector<DEMPoint> DEMPointVector;
#else
   typedef vector<DEMPoint> DEMPointVector;
#endif

#endif  // INCLUDED_DEMPOINT_HXX
