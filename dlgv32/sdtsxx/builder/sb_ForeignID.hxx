#ifndef INCLUDED_SB_FOREIGNID_HXX
#define INCLUDED_SB_FOREIGNID_HXX

// $Id: sb_ForeignID.hxx,v 1.1 1998/09/14 15:04:24 bmaddox Exp bmaddox $

#ifdef _WIN32
   #include <string>
   using namespace std;
#else
   #include <string>
#endif

#ifndef INCLUDED_SC_FIELD_H
#include "container/sc_Field.h"
#endif

class sb_ForeignID
{
   public:
      sb_ForeignID();
      explicit sb_ForeignID(sb_ForeignID const& right);
      explicit sb_ForeignID(sc_Field const& fidField);
         // fidField is assumed to be a foriegn ID field.
      sb_ForeignID const& operator=(sb_ForeignID const& right);
      bool operator==(sb_ForeignID const& right) const;
      bool operator<(sb_ForeignID const& right) const;

      // Accessors
      string const& getModuleName() const;
      long getRecordID() const;
      string const& getUsageModifier() const;

      // Mutators
      void setModuleName(string const& modname);
      void setRecordID(long recid);
      void setUsageModifier(string const& usemod);

   private:

      string d_moduleName;
      long d_recordID;
      string d_usageModifier;
};

// Inline methods.

inline
string const&
sb_ForeignID::getModuleName() const
{
   return d_moduleName;
}

inline
long
sb_ForeignID::getRecordID() const
{
   return d_recordID;
}

inline
string const&
sb_ForeignID::getUsageModifier() const
{
   return d_usageModifier;
}

inline
void
sb_ForeignID::setModuleName(string const& modname)
{
   d_moduleName = modname;
}

inline
void
sb_ForeignID::setRecordID(long recid)
{
   d_recordID = recid;
}

inline
void
sb_ForeignID::setUsageModifier(string const& usemod)
{
   d_usageModifier = usemod;
}

inline
bool
sb_ForeignID::operator<(sb_ForeignID const& right) const
{
   return false;
}

#endif  // INCLUDED_SB_FOREIGNID_HXX
