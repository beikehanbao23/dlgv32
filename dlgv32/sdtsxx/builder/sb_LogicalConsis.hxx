#ifndef INCLUDED_SB_LOGICALCONSIS_HXX
#define INCLUDED_SB_LOGICALCONSIS_HXX

// $Id: sb_LogicalConsis.hxx,v 1.1 1998/09/14 15:04:27 bmaddox Exp bmaddox $
// XXX This is core dumping on generic view as well as specific view.

#include <string>

#ifndef INCLUDED_SB_FOREIGNID_HXX
#include "builder/sb_ForeignID.hxx"
#endif

#ifndef INCLUDED_SC_RECORD_H
#include "container/sc_Record.h"
#endif

class sb_LogicalConsis
{
   public:
 
     sb_LogicalConsis();
     sb_LogicalConsis(sb_LogicalConsis const& right);
     sb_LogicalConsis const& operator=(sb_LogicalConsis const& right);
     explicit sb_LogicalConsis(sc_Record& recprox);
        // recprox can't be const because we use its -> operator. 

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
sb_LogicalConsis::getModuleName() const
{
   return d_moduleName;
}

inline
long
sb_LogicalConsis::getRecordID() const
{
   return d_recordID;
}

inline
string const&
sb_LogicalConsis::getComment() const
{
   return d_comment;
}

inline
sb_ForeignID const&
sb_LogicalConsis::getAttributeID() const
{
   return d_attributeID;
}

inline
sb_ForeignID const&
sb_LogicalConsis::getForeignID() const
{
   return d_foreignID;
}
  
#endif // INCLUDED_SB_LOGICALCONSIS_HXX
