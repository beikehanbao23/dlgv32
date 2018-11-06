#ifndef INCLUDED_SB_ARC_HXX
#define INCLUDED_SB_ARC_HXX

// $Id: sb_Arc.hxx,v 1.1 1998/09/14 15:04:12 bmaddox Exp bmaddox $ 
// Note:  This class has been compiled, but has NOT been tested due to
//        the lack of data using the Security module.
// XXX This class will not compile correctly as written. There seems to
// be a problem returning a single sb_SpatialAddress rather than a vector
// of sb_SpatialAddress's. 

#include <string>

#ifdef _WIN32
   #include <vector>
#else
   #include <vector.h>
#endif

#ifndef INCLUDED_SB_SPATIALADDR_HXX
#include "builder/sb_SpatialAddr.hxx"
#endif

#ifndef INCLUDED_SB_FOREIGNID_HXX
#include "builder/sb_ForeignID.hxx"
#endif

#ifndef INCLUDED_SC_RECORD_H
#include "container/sc_Record.h"
#endif


class sb_Arc
{
   public:
   
     sb_Arc();
     sb_Arc(sb_Arc const& right);
     sb_Arc const& operator=(sb_Arc const& right);
     explicit sb_Arc(sc_Record& recprox);

     // Accessors

     string const& getModuleName() const;
     long getRecordID() const;
     string const& getObjectRep() const;
     string const& getSurface() const;
     long getOrder() const;
     
     // Arc Address is a NON-repeating field
     sb_SpatialAddr const& getCenterAddr() const;
     sb_SpatialAddr const& getStartAddr() const;
     sb_SpatialAddr const& getEndAddr() const;

     // Ellipse Address is a NON-repeating field
     sb_SpatialAddr const& getMJRA() const;
     sb_SpatialAddr const& getMNRA() const;
     
     // Curve Address is a repeating field
     vector<sb_SpatialAddr> const& getCurveAddrs() const;

     vector<sb_ForeignID> const& getAttributeID() const;
     vector<sb_ForeignID> const& getCompositeID() const;
     vector<sb_ForeignID> const& getRepModuleID() const;


   private:
     
     string d_moduleName;
     long d_recordID;
     string d_objectRep;
     string d_surface;
     long d_order;

     sb_SpatialAddr d_centerAddr;
     sb_SpatialAddr d_startAddr;
     sb_SpatialAddr d_endAddr;

     sb_SpatialAddr d_mJRA;
     sb_SpatialAddr d_mNRA;
      
     vector<sb_SpatialAddr> d_curveAddrs;
     vector<sb_ForeignID> d_attributeID;
     vector<sb_ForeignID> d_compositeID;
     vector<sb_ForeignID> d_repModuleID;
};


inline
string const&
sb_Arc::getModuleName() const
{
   return d_moduleName;
}


inline
long
sb_Arc::getRecordID() const
{
   return d_recordID;
}

inline
string const&
sb_Arc::getObjectRep() const
{
   return d_objectRep;
}

inline
string const&
sb_Arc::getSurface() const
{
   return d_surface;
}

inline
long
sb_Arc::getOrder() const
{
   return d_order;
}

inline
sb_SpatialAddr const&
sb_Arc::getCenterAddr() const
{
   return d_centerAddr;
}
   
inline
sb_SpatialAddr const&
sb_Arc::getStartAddr() const
{
   return d_startAddr;
}

inline
sb_SpatialAddr const&
sb_Arc::getEndAddr() const
{
   return d_endAddr;
}

inline
sb_SpatialAddr const&
sb_Arc::getMJRA() const
{
   return d_mJRA;
}


inline
sb_SpatialAddr const&
sb_Arc::getMNRA() const
{
   return d_mNRA;
}

inline
vector<sb_SpatialAddr> const&
sb_Arc::getCurveAddrs() const
{   
   return d_curveAddrs;
}

inline
vector<sb_ForeignID> const&
sb_Arc::getAttributeID() const
{
  return d_attributeID;
}

inline
vector<sb_ForeignID> const&
sb_Arc::getCompositeID() const
{
  return d_compositeID;
}


inline
vector<sb_ForeignID> const&
sb_Arc::getRepModuleID() const
{
  return d_repModuleID;
}

#endif // INCLUDED_SB_ARC_HXX
