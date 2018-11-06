#ifndef INCLUDED_SB_DATADICTSCHEMA_HXX
#define INCLUDED_SB_DATADICTSCHEMA_HXX

// $Id: sb_DataDictSchema.hxx,v 1.1 1998/09/14 15:04:21 bmaddox Exp bmaddox $

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

class sb_DataDictSchema
{
   public:
     
     sb_DataDictSchema();
     sb_DataDictSchema(sb_DataDictSchema const& right); // Copy Constructor

     sb_DataDictSchema const& operator=(sb_DataDictSchema const& right);

     explicit sb_DataDictSchema(sc_Record& recprox);
        // recprox must be from a Data Dictionary/Schema module, or this won't
        // work.  recprox can't be const because we use its -> operator.


     // Accessors:

     string const& getModuleName() const;
     long getRecordID() const;
     string const& getName() const;
     string const& getType() const;
     string const& getEntityLbl() const;
     string const& getEntityAuth() const;
     string const& getAttributeLbl() const;
     string const& getAttributeAuth() const;
     string const& getFormat() const;
     string const& getUnit() const;
	 double getPrecision() const; // new to ANSI sdts
     long getMaxSubfieldLen() const;
     string const& getKey() const;

   private:

     string d_moduleName;
     long d_recordID;
     string d_name;
     string d_type;
     string d_entityLbl;
     string d_entityAuth;
     string d_attributeLbl;
     string d_attributeAuth; 
     string d_format;
     string d_unit;
	 double d_precision;
     long d_maxSubfieldLen;
     string d_key;

};

// inline methods

inline
string const&
sb_DataDictSchema::getModuleName() const
{
   return d_moduleName;
}

inline
long
sb_DataDictSchema::getRecordID() const
{
   return d_recordID;
}

inline
string const&
sb_DataDictSchema::getName() const
{
   return d_name;
}

inline
string const&
sb_DataDictSchema::getType() const
{
   return d_type;
}

inline
string const&
sb_DataDictSchema::getEntityLbl() const
{
   return d_entityLbl;
}

inline
string const&
sb_DataDictSchema::getEntityAuth() const
{
   return d_entityAuth;
}

inline
string const&
sb_DataDictSchema::getAttributeLbl() const
{
   return d_attributeLbl;
}

inline
string const&
sb_DataDictSchema::getAttributeAuth() const
{
   return d_attributeAuth;
}

inline
string const&
sb_DataDictSchema::getFormat() const
{
   return d_format;
}


inline
string const&
sb_DataDictSchema::getUnit() const
{
   return d_unit;
}

inline
double
sb_DataDictSchema::getPrecision() const
{
   return d_precision;
}

inline
long
sb_DataDictSchema::getMaxSubfieldLen() const
{
   return d_maxSubfieldLen;
}

inline
string const&
sb_DataDictSchema::getKey() const
{
   return d_key;
}

#endif // INCLUDED_SB_DATADICTSCHEMA_HXX
