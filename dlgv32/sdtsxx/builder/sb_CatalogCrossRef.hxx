#ifndef INCLUDED_SB_CATALOGCROSSREF_HXX
#define INCLUDED_SB_CATALOGCROSSREF_HXX

// $Id: sb_CatalogCrossRef.hxx,v 1.1 1998/09/14 15:04:14 bmaddox Exp bmaddox $

#include <string>

#ifndef INCLUDED_SC_RECORD_H
#include "container/sc_Record.h"
#endif

class sb_CatalogCrossRef
{
   public:
       
      sb_CatalogCrossRef();
      sb_CatalogCrossRef(sb_CatalogCrossRef const& right);
      sb_CatalogCrossRef const& operator=(sb_CatalogCrossRef const& right);
      explicit sb_CatalogCrossRef(sc_Record& recprox);
         // recprox must be from a Catalog/Cross-Reference  module, or this 
         // won't work. recprox can't be const because we use its -> operator.


      string const& getModuleName() const;
      long getRecordID() const;
      string const& getName1() const;
      string const& getType1() const;
      string const& getName2() const;
      string const& getType2() const;
      string const& getComment() const;

   private:
      
      string d_moduleName;
      long d_recordID;
      string d_name1;
      string d_type1;
      string d_name2;
      string d_type2;
      string d_comment;
};


// Inline methods


inline
string const&
sb_CatalogCrossRef::getModuleName() const
{
   return d_moduleName;
}

inline
long
sb_CatalogCrossRef::getRecordID() const
{
   return d_recordID;
}

inline 
string const&
sb_CatalogCrossRef::getName1() const
{
   return d_name1;
}

inline 
string const&
sb_CatalogCrossRef::getType1() const
{
   return d_type1;
}

inline
string const&
sb_CatalogCrossRef::getName2() const
{
   return d_name2;
}

inline
string const&
sb_CatalogCrossRef::getType2() const
{
   return d_type2;
}

inline
string const&
sb_CatalogCrossRef::getComment() const
{
   return d_comment;
}

#endif // INCLUDED_SB_CATALOGCROSSREF_HXX

