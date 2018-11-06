#ifndef INCLUDED_SB_COMPOSITE_HXX
#define INCLUDED_SB_COMPOSITE_HXX

// $Id: sb_Composite.hxx,v 1.1 1998/09/14 15:04:19 bmaddox Exp bmaddox $

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


class sb_Composite
{
   public:
     
     sb_Composite();
     sb_Composite(sb_Composite const& right);  
     explicit sb_Composite(sc_Record& recprox);
     sb_Composite const& operator=(sb_Composite const& right);

     // Accessors

     string const& getModuleName() const;
     long getRecordID() const;
     string const& getObjectRep() const;
     sb_ForeignID const& getAttributeID() const;
     vector<sb_ForeignID> const& getForeignID() const;
     sb_ForeignID const& getCompositeID() const;
   
   private:

     string d_moduleName;
     long d_recordID;
     string d_objectRep;
     // XXX All of the following are repeating fields!!!
     sb_ForeignID d_attributeID;
     vector<sb_ForeignID> d_foreignID;
     sb_ForeignID d_compositeID;

};

inline
string const&
sb_Composite::getModuleName() const
{
   return d_moduleName;
}

inline
long
sb_Composite::getRecordID() const
{
   return d_recordID;
}

inline
string const&
sb_Composite::getObjectRep() const
{
   return d_objectRep;
}

inline
sb_ForeignID const&
sb_Composite::getAttributeID() const
{
   return d_attributeID;
}


inline
vector<sb_ForeignID> const&
sb_Composite::getForeignID() const
{
   return d_foreignID;
}

inline
sb_ForeignID const&
sb_Composite::getCompositeID() const
{
   return d_compositeID;
}

#endif // INCLUDED_SB_COMPOSITE_HXX
