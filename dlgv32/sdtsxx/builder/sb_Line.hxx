#ifndef INCLUDED_SB_LINE_HXX
#define INCLUDED_SB_LINE_HXX

// $Id: sb_Line.hxx,v 1.1 1998/09/14 15:04:26 bmaddox Exp bmaddox $

#ifdef _WIN32
   #include <vector>
#else
   #include <vector.h>
#endif

#include <string>

#ifndef INCLUDED_SB_FOREIGNID_HXX
#include "builder/sb_ForeignID.hxx"
#endif

#ifndef INCLUDED_SB_SPATIALADDR_HXX
#include "builder/sb_SpatialAddr.hxx"
#endif

#ifndef INCLUDED_SC_RECORD_H
#include "container/sc_Record.h"
#endif
      

class sb_Line
{
   public:

      sb_Line();
      sb_Line(sb_Line const& right);
      sb_Line const& operator=(sb_Line const& right);
      explicit sb_Line(sc_Record& recprox);
         // recprox must be from a Line module, or this won't work.
         // recprox can't be const because we use its -> operator.

      // Accessors

      string const& getModuleName() const;
      long getRecordID() const;
      string const& getObjectRep() const;

      sb_ForeignID const& getPolygonIDLeft() const;
      sb_ForeignID const& getPolygonIDRight() const;
      sb_ForeignID const& getStartNodeID() const;
      sb_ForeignID const& getEndNodeID() const;
      
      vector<sb_ForeignID>   const& getAttributeIDs() const;
      vector<sb_SpatialAddr> const& getSpatialAddrs() const;

   private:

      string d_moduleName;
      long d_recordID;
      string d_objectRep;

      sb_ForeignID d_polyIDLeft;
      sb_ForeignID d_polyIDRight;
      sb_ForeignID d_startNodeID;
      sb_ForeignID d_endNodeID;

      vector<sb_ForeignID>   d_attrIDs;
      vector<sb_SpatialAddr> d_spatialAddrs;
};

// Inline methods

inline
string const&
sb_Line::getModuleName() const
{
   return d_moduleName;
}

inline
long
sb_Line::getRecordID() const
{
   return d_recordID;
}

inline
string const&
sb_Line::getObjectRep() const
{
   return d_objectRep;
}

inline
sb_ForeignID const&
sb_Line::getPolygonIDLeft() const
{
   return d_polyIDLeft;
}

inline
sb_ForeignID const&
sb_Line::getPolygonIDRight() const
{
   return d_polyIDRight;
}

inline
sb_ForeignID const&
sb_Line::getStartNodeID() const
{
   return d_startNodeID;
}

inline
sb_ForeignID const&
sb_Line::getEndNodeID() const
{
   return d_endNodeID;
}

inline
vector<sb_ForeignID> const&
sb_Line::getAttributeIDs() const
{
   return d_attrIDs;
}

inline
vector<sb_SpatialAddr> const&
sb_Line::getSpatialAddrs() const
{
   return d_spatialAddrs;
}

#endif  // INCLUDED_SB_LINE_HXX
