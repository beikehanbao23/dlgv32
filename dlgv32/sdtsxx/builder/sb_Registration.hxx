#ifndef INCLUDED_SB_REGISTRATION_HXX
#define INCLUDED_SB_REGISTRATION_HXX

// $Id: sb_Registration.hxx,v 1.1 1998/09/14 15:04:31 bmaddox Exp bmaddox $

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

class sb_Registration
{
   public:

      sb_Registration();
      sb_Registration(sb_Registration const& right); // Copy Constructor

      sb_Registration const& operator=(sb_Registration const& right);

      explicit sb_Registration(sc_Record& recprox);
         // recprox must be from a Registration module, or this won't work.
         // recprox can't be const because we use its -> operator.

      // Accessors:  function which returns the value of a data member
      // const member functions: may not modify data members.

      string const& getModuleName() const;
      long getRecordID() const;
      string const& getComment() const;
      vector<sb_SpatialAddr> const& getExtRefSpatialAddrs() const;
      vector<sb_SpatialAddr> const& getIntRefSpatialAddrs() const;

   private:

      string d_moduleName;
      long d_recordID;
      string d_comment;
      vector<sb_SpatialAddr> d_extRefSpatialAddrs; 
      vector<sb_SpatialAddr> d_intRefSpatialAddrs;
};

// Inline methods

inline
string const&
sb_Registration::getModuleName() const
{
   return d_moduleName;
}

inline
long
sb_Registration::getRecordID() const
{
   return d_recordID;
}

inline
string const&
sb_Registration::getComment() const
{
   return d_comment;
}

inline
vector<sb_SpatialAddr> const&
sb_Registration::getExtRefSpatialAddrs() const
{
   return d_extRefSpatialAddrs;
}

inline
vector<sb_SpatialAddr> const&
sb_Registration::getIntRefSpatialAddrs() const
{
   return d_intRefSpatialAddrs;
}

#endif // INCLUDED_SB_REGISTRATION_HXX
