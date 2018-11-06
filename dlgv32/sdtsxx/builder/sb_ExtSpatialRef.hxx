#ifndef INCLUDED_SB_EXTSPATIALREF_HXX
#define INCLUDED_SB_EXTSPATIALREF_HXX

// $Id: sb_ExtSpatialRef.hxx,v 1.1 1998/09/14 15:04:22 bmaddox Exp bmaddox $ 

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

class sb_ExtSpatialRef
{
   public:

      sb_ExtSpatialRef();
      sb_ExtSpatialRef(sb_ExtSpatialRef const& right); // Copy Constructor

      sb_ExtSpatialRef const& operator=(sb_ExtSpatialRef const& right);

      explicit sb_ExtSpatialRef(sc_Record& recprox);
         // recprox must be from a External Spatial Reference module, or this 
         // won't work. recprox can't be const because we use its -> operator.

      // Accessors:  function which returns the value of a data member
      // const member functions: may not modify data members.

      string const& getModuleName() const;
      long getRecordID() const;
      string const& getComment() const;
      string const& getRefDoc() const;
      string const& getRefSysName() const;
      string const& getVertDatum() const;
      string const& getSoundDatum() const;
      string const& getHorizDatum() const;
      string const& getZoneNum() const;
      string const& getProjection() const;
      
      sb_ForeignID const& getAttID() const;
      // XXX Secondary Field - Vertical Attributes.
      // XXX non implimented

      // XXX Secondary field -  Sounding Attributes.
      // XXX non implimented

      
    private:
      
      string d_moduleName;
      long d_recordID;
      string d_comment;
      string d_refDoc;
      string d_refSysName;
      string d_vertDatum;
      string d_soundDatum;
      string d_horizDatum;
      string d_zoneNum;
      string d_projection;
      sb_ForeignID d_attID;
};

// Inline methods

inline
string const&
sb_ExtSpatialRef::getModuleName() const
{
    return d_moduleName;
}

inline
long
sb_ExtSpatialRef::getRecordID() const
{
   return d_recordID;
}

inline
string const&
sb_ExtSpatialRef::getComment() const
{
   return d_comment;
}

inline
string const&
sb_ExtSpatialRef::getRefDoc() const
{
   return d_refDoc;
}

inline
string const&
sb_ExtSpatialRef::getRefSysName() const
{
   return d_refSysName;
}

inline
string const&
sb_ExtSpatialRef::getVertDatum() const
{
   return d_vertDatum;
}

inline
string const&
sb_ExtSpatialRef::getSoundDatum() const
{
   return d_soundDatum;
}

inline
string const&
sb_ExtSpatialRef::getHorizDatum() const
{
   return d_horizDatum;
}

inline
string const&
sb_ExtSpatialRef::getZoneNum() const
{
   return d_zoneNum;
}

inline
string const&
sb_ExtSpatialRef::getProjection() const
{
   return d_projection;
}

inline
sb_ForeignID const&
sb_ExtSpatialRef::getAttID() const
{
   return d_attID;
}

#endif // INCLUDED_SB_EXTSPATIALREF_HXX

