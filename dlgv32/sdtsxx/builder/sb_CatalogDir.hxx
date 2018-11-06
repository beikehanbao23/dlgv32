#ifndef INCLUDED_SB_CATALOGDIR_HXX
#define INCLUDED_SB_CATALOGDIR_HXX

// $Id: sb_CatalogDir.hxx,v 1.1 1998/09/14 15:04:15 bmaddox Exp bmaddox $

#include <string>

#ifndef INCLUDED_SC_RECORD_H
#include "container/sc_Record.h"
#endif


class sb_CatalogDir
{
   public:

      sb_CatalogDir();
      sb_CatalogDir(sb_CatalogDir const& right); // Copy Constructor
      
      sb_CatalogDir const& operator=(sb_CatalogDir const& right);


      explicit sb_CatalogDir(sc_Record& recprox);  
         // recprox must be from a sb_CatalogDir module, or this won't work.
         // recprox can't be const because we use its -> operator.


      // Accessors:  function which returns the value of a data member
      // const member functions: may not modify data members.

      string const& getModuleName() const;
      long getRecordID() const;
      string const& getName() const;
      string const& getType() const;
      string const& getVolume() const;
      string const& getFile() const;
      string const& getRecord() const; 
      string const& getExternal() const;
      string const& getModuleVer() const;
      string const& getComment() const;

   private: 

      string d_moduleName;
      long d_recordID;
      string d_name;
      string d_type;
      string d_volume;
      string d_file;
      string d_record;
      string d_external;
      string d_moduleVer;
      string d_comment;
};

// Inline methods

inline
string const& 
sb_CatalogDir::getModuleName() const
{
    return d_moduleName;
}

inline
long
sb_CatalogDir::getRecordID() const
{
    return d_recordID;
}


inline
string const&
sb_CatalogDir::getName() const
{
    return d_name;
}

inline
string const&
sb_CatalogDir::getType() const
{
    return d_type;
}

inline
string const&
sb_CatalogDir::getVolume() const
{
    return d_volume;
}


inline
string const&
sb_CatalogDir::getFile() const
{
    return d_file;
}


inline
string const&
sb_CatalogDir::getRecord() const
{
    return d_record;
}

inline
string const&
sb_CatalogDir::getExternal() const
{
    return d_external;
}


inline
string const&
sb_CatalogDir::getModuleVer() const
{
    return d_moduleVer;
}

inline
string const&
sb_CatalogDir::getComment() const
{
    return d_comment;
}

#endif // INCLUDED_SB_CATALOGDIR_HXX
