#ifndef INCLUDED_SB_POSACCURACY_HXX
#define INCLUDED_SB_POSACCURACY_HXX

// $Id: sb_PosAccuracy.hxx,v 1.1 1998/09/14 15:04:30 bmaddox Exp bmaddox $

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

class sb_PosAccuracy
{
   public:

     sb_PosAccuracy();
     sb_PosAccuracy(sb_PosAccuracy const& right);
     sb_PosAccuracy const& operator=(sb_PosAccuracy const& right);
     explicit sb_PosAccuracy(sc_Record& recprox);
         // recprox must be from a Positional Accuracy module, or this won't
         // work. recprox can't be const because we use its -> operator.

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
sb_PosAccuracy::getModuleName() const
{
   return d_moduleName;
}

inline
long
sb_PosAccuracy::getRecordID() const
{
   return d_recordID;
}


inline
string const&
sb_PosAccuracy::getComment() const
{
   return d_comment;
}

inline
sb_ForeignID const&
sb_PosAccuracy::getAttributeID() const
{
   return d_attributeID;
}

inline
sb_ForeignID const&
sb_PosAccuracy::getForeignID() const
{
   return d_foreignID;
}

 

#endif // INCLUDED_SB_POSACCURACY
