#ifndef INCLUDED_SB_DATADICTDEFN_HXX
#define INCLUDED_SB_DATADICTDEFN_HXX

// $Id: sb_DataDictDefn.hxx,v 1.1 1998/09/14 15:04:19 bmaddox Exp bmaddox $
// Note:  This class has been compiled, but has NOT been tested due to
//        the lack of data using the Dimension Definition module.

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



class sb_DataDictDefn
{
   public:

      sb_DataDictDefn();
      sb_DataDictDefn(sb_DataDictDefn const& right); // Copy Constructor

      sb_DataDictDefn const& operator=(sb_DataDictDefn const& right);

      explicit sb_DataDictDefn(sc_Record& recprox);
         // recprox must be from a Data Dictionary/Definition module, or this
         // won't work. recprox can't be const because we use its -> operator.

      // Accessors:  function which returns the value of a data member
      // const member functions: may not modify data members.

      string const& getModuleName() const;
      long getRecordID() const;
      string const& getEntOrAtt() const;
      string const& getEntAttLbl() const;
      string const& getSource() const;
      string const& getDefinition() const;
      string const& getAttAuthority() const;
      string const& getAttAuthorityDes() const;

   private:

      string d_moduleName;
      long d_recordID;
      string d_entOrAtt;
      string d_entAttLbl;
      string d_source;
      string d_definition;
      string d_attAuthority;
      string d_attAuthorityDes;

};

// Inline methods

inline
string const&
sb_DataDictDefn::getModuleName() const
{
    return d_moduleName;
}

inline
long
sb_DataDictDefn::getRecordID() const
{
    return d_recordID;
}

inline
string const&
sb_DataDictDefn::getEntOrAtt() const
{
    return d_entOrAtt;
}

inline
string const&
sb_DataDictDefn::getEntAttLbl() const
{
    return d_entAttLbl;
}

inline
string const& 
sb_DataDictDefn::getSource() const
{
    return d_source;
}

inline
string const&
sb_DataDictDefn::getDefinition() const
{
    return d_definition;
}

inline 
string const&
sb_DataDictDefn::getAttAuthority() const
{
    return d_attAuthority;
}

inline
string const&
sb_DataDictDefn::getAttAuthorityDes() const
{
   return d_attAuthorityDes;
}

#endif // INCLUDED_SB_DATADICTDEFN_HXX 

