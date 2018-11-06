#ifndef INCLUDED_SB_DIMENDEFN_HXX
#define INCLUDED_SB_DIMENDEFN_HXX

// $Id: sb_DimenDefn.hxx,v 1.1 1998/09/14 15:04:22 bmaddox Exp bmaddox $
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


class sb_DimenDefn
{
   public:

      sb_DimenDefn();
      sb_DimenDefn(sb_DimenDefn const& right); // Copy Constructor

      sb_DimenDefn const& operator=(sb_DimenDefn const& right);

      explicit sb_DimenDefn(sc_Record& recprox);
         // recprox must be from a Dimension Definition module, or this won't 
         // work. recprox can't be const because we use its -> operator.

      // Accessors:  function which returns the value of a data member
      // const member functions: may not modify data members.

      string const& getModuleName() const;
      long getRecordID() const;
      string const& getDimenLbl() const;
      string const& getDimenCompFormat() const;
      double getDimenCompRes() const;
      string const& getDimenValMeasureUnit() const;
      string const& getDimenDescription() const;
      sb_ForeignID const& getDimenAttributeID() const;

   private:
     
      string d_moduleName;
      long d_recordID;
      string d_dimenLbl;
      string d_dimenCompFormat;
      double d_dimenCompRes;
      string d_dimenValMeasureUnit;
      string d_dimenDescription; 
      
      sb_ForeignID d_dimenAttributeID;

};

// Inline methods

inline
string const&
sb_DimenDefn::getModuleName() const
{
    return d_moduleName;
}

inline
long
sb_DimenDefn::getRecordID() const
{
    return d_recordID;
}

inline
string const&
sb_DimenDefn::getDimenLbl() const
{
    return d_dimenLbl;
}

inline
string const&
sb_DimenDefn::getDimenCompFormat() const
{
    return d_dimenCompFormat;
}

inline
double
sb_DimenDefn::getDimenCompRes() const
{
    return d_dimenCompRes;
}

inline
string const&
sb_DimenDefn::getDimenValMeasureUnit() const
{ 
    return d_dimenValMeasureUnit;
}

inline
string const&
sb_DimenDefn::getDimenDescription() const
{
    return d_dimenDescription;
}


inline
sb_ForeignID const&
sb_DimenDefn::getDimenAttributeID() const
{
    return d_dimenAttributeID;
}

#endif // INCLUDED_SB_DIMENDEFN_HXX

