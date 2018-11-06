#ifndef INCLUDED_SB_POLYGON_HXX
#define INCLUDED_SB_POLYGON_HXX

// $Id: sb_Polygon.hxx,v 1.1 1998/09/14 15:04:29 bmaddox Exp bmaddox $

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

class sb_Polygon
{
   public:

      sb_Polygon();
      sb_Polygon(sb_Polygon const& right); // Copy Constructor

      sb_Polygon const& operator=(sb_Polygon const& right);

      explicit sb_Polygon(sc_Record& recprox);
         // recprox must be from a Polygon module, or this won't work.
         // recprox can't be const because we use its -> operator.

      // Accessors:  function which returns the value of a data member
      // const member functions: may not modify data members.

      string const& getModuleName() const;
      long getRecordID() const;
      string const& getObjectRep() const;
      
      sb_ForeignID const& getAttributeID() const;
      sb_ForeignID const& getRingID() const;
      sb_ForeignID const& getChainID() const;
      sb_ForeignID const& getCompositeID() const;
      sb_ForeignID const& getRepModuleID() const;

   private:

      string d_moduleName;
      long d_recordID;
      string d_objectRep;

      sb_ForeignID d_attributeID;
      sb_ForeignID d_ringID;
      sb_ForeignID d_chainID;
      sb_ForeignID d_compositeID;
      sb_ForeignID d_repModuleID;
};

// Inline methods

inline
string const&
sb_Polygon::getModuleName() const 
{
    return d_moduleName;
}

inline
long
sb_Polygon::getRecordID() const
{
    return d_recordID;
}

inline
string const&
sb_Polygon::getObjectRep() const
{
    return d_objectRep;
}

inline
sb_ForeignID const&
sb_Polygon::getAttributeID() const
{
    return d_attributeID;
}

inline
sb_ForeignID const&
sb_Polygon::getRingID() const
{
    return d_ringID;
}

inline
sb_ForeignID const&
sb_Polygon::getChainID() const
{
    return d_chainID;
}

inline
sb_ForeignID const&
sb_Polygon::getCompositeID() const
{
    return d_compositeID;
}

inline
sb_ForeignID const&
sb_Polygon::getRepModuleID() const
{
    return d_repModuleID;
}

#endif // INCLUDED_SB_POLYGON_HXX
