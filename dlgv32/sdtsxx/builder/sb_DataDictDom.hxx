#ifndef INCLUDED_SB_DATADICTDOM_HXX
#define INCLUDED_SB_DATADICTDOM_HXX

// $Id: sb_DataDictDom.hxx,v 1.1 1998/09/14 15:04:20 bmaddox Exp bmaddox $
// Note:  This class has been compiled, but has NOT been tested due to
//        the lack of data. Data Dictionary/Domain module is external to the 
//        transfer data set.  

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

class sb_DataDictDom
{
   public:
      
     sb_DataDictDom();
     sb_DataDictDom(sb_DataDictDom const& right); // Copy Constructor
     sb_DataDictDom const& operator=(sb_DataDictDom const& right);
     
     explicit sb_DataDictDom(sc_Record& recprox);
        // recprox must be from a Data Dictionary/Domain module, or this
        // won't work.  recprox can't be const because we use its -> operator.

     // Accessors
     string const& getModuleName() const;
     long getRecordID() const;
     string const& getAttLbl() const;
     string const& getAttAuth() const;
     string const& getAttDomType() const;
     string const& getAttDomValFmt() const;
     string const& getAttDomValMsmtUnit() const;
     string const& getRangeOrValue() const;

     // XXX Not sure about the data type for d_domainValue
//     string const& getDomainValue() const;
     sc_Subfield const& getDomainValue() const;
     string const& getDomainValueDefn() const;
 
   private:
     
     string d_moduleName;
     long d_recordID;
     string d_attLbl;
     string d_attAuth;
     string d_attDomType;
     string d_attDomValFmt; 
     string d_attDomValMsmtUnit;
     string d_rangeOrValue;

     // XXX should this be a string?
     string d_domainValue;
     sc_Subfield d_domainValueSubfield;
     string d_domainValueDefn;
};

// inline methods

inline
string const&
sb_DataDictDom::getModuleName() const
{
   return d_moduleName;
}

inline
long
sb_DataDictDom::getRecordID() const
{
   return d_recordID;
}

inline
string const&
sb_DataDictDom::getAttLbl() const
{
   return d_attLbl;
}

inline 
string const&
sb_DataDictDom::getAttAuth() const
{  
   return d_attAuth;
}

inline
string const&
sb_DataDictDom::getAttDomType() const
{
   return d_attDomType;
}

inline
string const&
sb_DataDictDom::getAttDomValFmt() const
{
   return d_attDomValFmt;
}


inline
string const&
sb_DataDictDom::getAttDomValMsmtUnit() const
{
   return d_attDomValMsmtUnit;
}

inline 
string const&
sb_DataDictDom::getRangeOrValue() const
{
   return d_rangeOrValue;
}

inline
//string const&
sc_Subfield const&
sb_DataDictDom::getDomainValue() const
{
   return d_domainValueSubfield;
}

inline
string const&
sb_DataDictDom::getDomainValueDefn() const
{
   return d_domainValueDefn;
}


#endif // INCLUDED_SB_DATADICTDOM
