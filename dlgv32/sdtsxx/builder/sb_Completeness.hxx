#ifndef INCLUDED_SB_OMPLETENESS_HXX
#define INCLUDED_SB_COMPLETENESS_HXX

// $Id: sb_Completeness.hxx,v 1.1 1998/09/14 15:04:18 bmaddox Exp bmaddox $

#include <string>

#ifndef INCLUDED_SB_FOREIGNID_HXX
#include "builder/sb_ForeignID.hxx"
#endif

#ifndef INCLUDED_SC_RECORD_H
#include "container/sc_Record.h"
#endif


class sb_Completeness
{
   public:
     
     sb_Completeness();
     sb_Completeness(sb_Completeness const& right);
     explicit sb_Completeness(sc_Record& recprox);
     sb_Completeness const& operator=(sb_Completeness const& right);
     
     // Accessors
     string const& getModuleName() const;
     long getRecordID() const;
     string const& getComment() const;

     sb_ForeignID const& getAttributeID() const;
     sb_ForeignID const& getForeignID() const; 

   private:
     
     string d_moduleName;
     long d_recordID;
     string d_comment;
     sb_ForeignID d_attributeID;
     sb_ForeignID d_foreignID;
};


inline
string const&
sb_Completeness::getModuleName() const
{
   return d_moduleName;
}


inline
long
sb_Completeness::getRecordID() const
{
   return d_recordID;
}

inline
string const&
sb_Completeness::getComment() const
{
   return d_comment;
}

inline
sb_ForeignID const&
sb_Completeness::getAttributeID() const
{
   return d_attributeID;
}

inline
sb_ForeignID const&
sb_Completeness::getForeignID() const
{
   return d_foreignID;
}

#endif // INCLUDED_SB_COMPLETENESS_HXX
