#ifndef INCLUDED_SB_POINTNODE_HXX
#define INCLUDED_SB_POINTNODE_HXX

// $Id: sb_PointNode.hxx,v 1.1 1998/09/14 15:04:28 bmaddox Exp bmaddox $

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


class sb_PointNode
{
   public:
     
     sb_PointNode();
     sb_PointNode(sb_PointNode const& right); // Copy Constructor
    
     sb_PointNode const& operator=(sb_PointNode const& right);
     explicit sb_PointNode(sc_Record& recprox);
        // recprox must be from a Security module, or this won't work.
        // recprox can't be const because we use its -> operator.

     // Accessors:  function which returns the value of a data member

     string const& getModuleName() const;
     long getRecordID() const;
     string const& getObjectRep() const;

     // Note: this is not a repeating field.
     vector<sb_SpatialAddr> const& getSpatialAddrs() const;

     sb_ForeignID const& getAttributeID() const;
     sb_ForeignID const& getLineID() const;
     sb_ForeignID const& getAreaID() const;
     sb_ForeignID const& getCompositeID() const;
     sb_ForeignID const& getRepModuleID() const;

     vector<sb_SpatialAddr> const& getOrientSpatialAddrs() const;

     sb_ForeignID const& getAttPrimaryID() const;

     string const& getAttLbl() const;

     vector<sb_SpatialAddr> const& getSymbolOrientSpatialAddrs() const;

   private:

     string d_moduleName;
     long d_recordID;
     string d_objectRep;

     vector<sb_SpatialAddr> d_spatialAddrs;
     
     sb_ForeignID d_attributeID;
     sb_ForeignID d_lineID;
     sb_ForeignID d_areaID;
     sb_ForeignID d_compositeID;
     sb_ForeignID d_repModuleID;
     
     vector<sb_SpatialAddr> d_orientSpatialAddrs;
    
     sb_ForeignID d_attPrimaryID;
     string d_attLbl; 

     vector<sb_SpatialAddr> d_symbolOrientSpatialAddrs;

};

// Inline methods

inline 
string const&
sb_PointNode::getModuleName() const
{
    return d_moduleName;
}

inline 
long
sb_PointNode::getRecordID() const
{
    return d_recordID;
}

inline
string const&
sb_PointNode::getObjectRep() const
{
    return d_objectRep;
}

inline
vector<sb_SpatialAddr> const&
sb_PointNode::getSpatialAddrs() const
{
    return d_spatialAddrs;
}

inline
sb_ForeignID const&
sb_PointNode::getAttributeID() const
{
    return d_attributeID;
}

inline
sb_ForeignID const&
sb_PointNode::getLineID() const
{
    return d_lineID;
}

inline
sb_ForeignID const&
sb_PointNode::getAreaID() const
{
    return d_areaID;
}

inline
sb_ForeignID const&
sb_PointNode::getCompositeID() const
{
    return d_compositeID;
}

inline
sb_ForeignID const&
sb_PointNode::getRepModuleID() const
{   return d_repModuleID;
}

inline
vector<sb_SpatialAddr> const&
sb_PointNode::getOrientSpatialAddrs() const
{
    return d_orientSpatialAddrs;
}

inline
sb_ForeignID const&
sb_PointNode::getAttPrimaryID() const
{
    return d_attPrimaryID;
}

inline
string const&
sb_PointNode::getAttLbl() const
{
    return d_attLbl;
}

inline
vector<sb_SpatialAddr> const&
sb_PointNode::getSymbolOrientSpatialAddrs() const
{
    return d_symbolOrientSpatialAddrs;
}

#endif // INCLUDED_SB_POINTNODE_HXX
