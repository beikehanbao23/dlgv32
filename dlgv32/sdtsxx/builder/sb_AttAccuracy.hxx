#ifndef INCLUDED_SB_ATTACCURACY_HXX
#define INCLUDED_SB_ATTACCURACY_HXX

// $Id: sb_AttAccuracy.hxx,v 1.1 1998/09/14 15:04:13 bmaddox Exp bmaddox $

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

class sb_AttAccuracy
{
   public:
     
     sb_AttAccuracy();
     sb_AttAccuracy(sb_AttAccuracy const& right);
     sb_AttAccuracy const& operator=(sb_AttAccuracy const& right);
     explicit sb_AttAccuracy(sc_Record& recprox);
        // recprox can't be const because we use its -> operator
     
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
sb_AttAccuracy::getModuleName() const
{
   return d_moduleName;
}

inline
long
sb_AttAccuracy::getRecordID() const
{
   return d_recordID;
}

inline
string const&
sb_AttAccuracy::getComment() const
{
   return d_comment;
}

inline
sb_ForeignID const&
sb_AttAccuracy::getAttributeID() const
{
   return d_attributeID;
}

inline
sb_ForeignID const&
sb_AttAccuracy::getForeignID() const
{
   return d_foreignID;
}


#endif INCLUDED_SB_ATTACCURACY_HXX

