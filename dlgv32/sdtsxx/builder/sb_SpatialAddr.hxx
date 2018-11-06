
#ifndef INCLUDED_SB_SPATIALADDR_HXX
#define INCLUDED_SB_SPATIALADDR_HXX

#ifndef INCLUDED_SC_FIELD_H
#include "container/sc_Field.h"
#endif

class sb_SpatialAddr
{
   // The generalize form of an SDTS Spatial Address field. The subfield values
   // are converted to doubles regardless of the type they have in the SDTS transfer.

   // XXX nongeospatial Deminsions - not implimented

   public:
      sb_SpatialAddr();
      sb_SpatialAddr(sb_SpatialAddr const& right);
      sb_SpatialAddr(double x, double y, double z = 0.0);
      explicit sb_SpatialAddr(sc_Field const& sadrField);
         // sadrField is assumed to be a Spatial Address Field.
      sb_SpatialAddr const& operator=(sb_SpatialAddr const& right);;
      bool operator<(sb_SpatialAddr const& right) const;
	  bool operator==(sb_SpatialAddr const& right) const;

      // Accessors
      double getX() const;
      double getY() const;
      double getZ() const;
      void getXY(double& x, double& y) const;
      void getXYZ(double& x, double& y, double& z) const;

      // Mutators
      void setX(double x);
      void setY(double y);
      void setZ(double z);
      void setXY(double x, double y);
      void setXYZ(double x, double y, double z);

   private:

      double d_x;
      double d_y;
      double d_z;

};

inline
sb_SpatialAddr const&
sb_SpatialAddr::operator=(sb_SpatialAddr const& right)
{
   if (this == &right) return *this;

   d_x = right.d_x;
   d_y = right.d_y;
   d_z = right.d_z;

   return *this;
}

inline
bool
sb_SpatialAddr::operator<(sb_SpatialAddr const& right) const
{
   return false;
}

inline
bool
sb_SpatialAddr::operator==(sb_SpatialAddr const& right) const
{
   return false;
}

inline
sb_SpatialAddr::sb_SpatialAddr(sb_SpatialAddr const& right)
{
   operator=(right);
}

inline
sb_SpatialAddr::sb_SpatialAddr(double x, double y, double z)
             : d_x(x), d_y(y), d_z(z)
{
}

inline
double
sb_SpatialAddr::getX() const
{
   return d_x;
}

inline
double
sb_SpatialAddr::getY() const
{
   return d_y;
}

inline
double
sb_SpatialAddr::getZ() const
{
   return d_z;
}

inline
void
sb_SpatialAddr::getXY(double& x, double& y) const
{
   x = d_x;
   y = d_y;
}

inline
void
sb_SpatialAddr::getXYZ(double& x, double& y, double& z) const
{
   x = d_x;
   y = d_y;
   z = d_z;
}

inline
void
sb_SpatialAddr::setX(double x)
{
   d_x = x;
}

inline
void
sb_SpatialAddr::setY(double y)
{
   d_y = y;
}

inline
void
sb_SpatialAddr::setZ(double z)
{
   d_z = z;
}

inline
void
sb_SpatialAddr::setXY(double x, double y)
{
   d_x = x;
   d_y = y;
}

inline
void
sb_SpatialAddr::setXYZ(double x, double y, double z)
{
   d_x = x;
   d_y = y;
   d_z = z;
}


#endif  // INCLUDED_SB_SPATIALADDR_HXX
