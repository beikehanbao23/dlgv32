#ifndef INCLUDED_SB_INTSPATIALREF_HXX
#define INCLUDED_SB_INTSPATIALREF_HXX

// $Id: sb_IntSpatialRef.hxx,v 1.1 1998/09/14 15:04:25 bmaddox Exp bmaddox $

#ifdef _WIN32
   #include <vector>
#else
   #include <vector.h>
#endif

#include <string>

#ifndef INCLUDED_SB_FOREIGNID_HXX
#include "builder/sb_ForeignID.hxx"
#endif

#ifndef INCLUDED_SC_RECORD_H
#include "container/sc_Record.h"
#endif

class sb_IntSpatialRef
{
   public:

      sb_IntSpatialRef();
      sb_IntSpatialRef(sb_IntSpatialRef const& right); // Copy Constructor

      sb_IntSpatialRef const& operator=(sb_IntSpatialRef const& right);

      explicit sb_IntSpatialRef(sc_Record& recprox);
         // recprox must be from a Internal Spatial Reference module, or this 
         // won't work. recprox can't be const because we use its -> operator.

      // Accessors:  function which returns the value of a data member
      // const member functions: may not modify data members.

      string const& getModuleName() const;
      long getRecordID() const;
      string const& getComment() const;

      string const& getSpatialAddType() const;
      string const& getSpatialAddXCompLbl() const;
      string const& getSpatialAddYCompLbl() const;
      string const& getHorizontalCompFmt() const;
      string const& getVerticalCompFmt() const;
       
      double getScaleFactX() const;
      double getScaleFactY() const;
      double getScaleFactZ() const;
      double getXOrigin() const;
      double getYOrigin() const;
      double getZOrigin() const;
      
      double getXCompHorizRes() const;
      double getYCompHorizRes() const;
      double getVerticalResComp() const;

      vector<sb_ForeignID> const& getDimensionID() const;

   private:
     
      string d_moduleName; 
      long d_recordID;
      string d_comment;
      
      string d_spatialAddType;
      string d_spatialAddXCompLbl;
      string d_spatialAddYCompLbl;
      string d_horizontalCompFmt;
      string d_verticalCompFmt;
     
      double d_scaleFactX;
      double d_scaleFactY;
      double d_scaleFactZ;
      double d_xOrigin;
      double d_yOrigin; 
      double d_zOrigin;
      
      double d_xCompHorizRes;
      double d_yCompHorizRes;
      double d_verticalResComp;

      vector<sb_ForeignID> d_dimensionID;
};


// Inline methods

inline
string const&
sb_IntSpatialRef::getModuleName() const
{
    return d_moduleName;
}

inline
long
sb_IntSpatialRef::getRecordID() const
{
    return d_recordID;
}

inline
string const&
sb_IntSpatialRef::getComment() const
{
    return d_comment;
}

inline
string const&
sb_IntSpatialRef::getSpatialAddType() const
{
    return d_spatialAddType;
}

inline
string const&
sb_IntSpatialRef::getSpatialAddXCompLbl() const
{
    return d_spatialAddXCompLbl;
}

inline
string const&
sb_IntSpatialRef::getSpatialAddYCompLbl() const
{
    return d_spatialAddYCompLbl;
}

inline
string const&
sb_IntSpatialRef::getHorizontalCompFmt() const
{
    return d_horizontalCompFmt;
}

inline 
string const&
sb_IntSpatialRef::getVerticalCompFmt() const
{
    return d_verticalCompFmt;
}

inline
double
sb_IntSpatialRef::getScaleFactX() const
{
    return d_scaleFactX;
}

inline
double
sb_IntSpatialRef::getScaleFactY() const
{
    return d_scaleFactY;
}

inline
double
sb_IntSpatialRef::getScaleFactZ() const
{
    return d_scaleFactZ;
}

inline
double
sb_IntSpatialRef::getXOrigin() const
{
    return d_xOrigin;
}

inline
double
sb_IntSpatialRef::getYOrigin() const
{
    return d_yOrigin;
}

inline 
double
sb_IntSpatialRef::getZOrigin() const
{
    return d_zOrigin;
}

inline
double
sb_IntSpatialRef::getXCompHorizRes() const
{
    return d_xCompHorizRes;
}

inline
double
sb_IntSpatialRef::getYCompHorizRes() const
{
    return d_yCompHorizRes;
}

inline
double
sb_IntSpatialRef::getVerticalResComp() const
{
    return d_verticalResComp;
}

inline
vector<sb_ForeignID> const&                 //sb_ForeignID const&
sb_IntSpatialRef::getDimensionID() const
{
    return d_dimensionID;
}

#endif // INCLUDED_SB_INTSPATIALREF_HXX
