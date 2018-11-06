#ifndef INCLUDED_SDTS_SPATIALADDR_H_
#define INCLUDED_SDTS_SPATIALADDR_H_

#include "sdtsxx/container/sc_Field.h"

class SDTS_SpatialAddr
{
   // The generalize form of an SDTS Spatial Address field. The subfield values
   // are converted to doubles regardless of the type they have in the SDTS transfer.

   // XXX nongeospatial Deminsions - not implimented

   public:
      SDTS_SpatialAddr();
      SDTS_SpatialAddr( const SDTS_SpatialAddr& right);
      SDTS_SpatialAddr( double x, double y );
      explicit SDTS_SpatialAddr( const sc_Field& sadrField);
         // sadrField is assumed to be a Spatial Address Field.
      const SDTS_SpatialAddr& operator=( const SDTS_SpatialAddr& right);
      bool operator<( const SDTS_SpatialAddr& right) const;
	  bool operator==( const SDTS_SpatialAddr& right) const;

      // Accessors
      double getX() const;
      double getY() const;
      void getXY(double& x, double& y) const;

      // Mutators
      void setX(double x);
      void setY(double y);
      void setXY(double x, double y);

   private:

      double d_x;
      double d_y;
};

inline
SDTS_SpatialAddr const&
SDTS_SpatialAddr::operator=(SDTS_SpatialAddr const& right)
{
   if (this == &right) return *this;

   d_x = right.d_x;
   d_y = right.d_y;

   return *this;
}

inline
bool
SDTS_SpatialAddr::operator<(SDTS_SpatialAddr const& right) const
{
   return false;
}

inline
bool
SDTS_SpatialAddr::operator==(SDTS_SpatialAddr const& right) const
{
   return false;
}

inline
SDTS_SpatialAddr::SDTS_SpatialAddr(SDTS_SpatialAddr const& right)
{
   operator=(right);
}

inline
SDTS_SpatialAddr::SDTS_SpatialAddr(double x, double y )
: d_x(x), d_y(y)
{
}

inline
double
SDTS_SpatialAddr::getX() const
{
   return d_x;
}

inline
double
SDTS_SpatialAddr::getY() const
{
   return d_y;
}

inline
void
SDTS_SpatialAddr::getXY(double& x, double& y) const
{
   x = d_x;
   y = d_y;
}

inline
void
SDTS_SpatialAddr::setX(double x)
{
   d_x = x;
}

inline
void
SDTS_SpatialAddr::setY(double y)
{
   d_y = y;
}

inline
void
SDTS_SpatialAddr::setXY(double x, double y)
{
   d_x = x;
   d_y = y;
}

#endif
