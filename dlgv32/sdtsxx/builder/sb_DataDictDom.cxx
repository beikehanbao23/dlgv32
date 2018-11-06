// $Id: sb_DataDictDom.cxx,v 1.1 1998/09/14 15:04:20 bmaddox Exp bmaddox $

#ifdef _WIN32
   #include <iostream>
#else
   #include <iostream.h>
#endif

#ifndef INCLUDED_SB_UTILS_HXX
#include "builder/sb_Utils.hxx"
#endif

#ifndef INCLUDED_SB_DATADICTDOM_HXX
#include "builder/sb_DataDictDom.hxx"
#endif

#ifndef INCLUDED_SC_RECORD_H
#include "container/sc_Record.h"
#endif

#ifndef INCLUDED_SC_FIELD_H
#include "container/sc_Field.h"
#endif

#ifndef INCLUDED_SC_SUBFIELD_H
#include "container/sc_Subfield.h"
#endif

sb_DataDictDom::sb_DataDictDom()
             : d_recordID(0)
{
}

sb_DataDictDom::sb_DataDictDom(sb_DataDictDom const& right)
{
   operator=(right);
}

sb_DataDictDom const&
sb_DataDictDom::operator=(sb_DataDictDom const& right)
{
   if(this==&right)
     return *this;
   d_moduleName = right.d_moduleName;
   d_recordID = right.d_recordID;
   d_attLbl = right.d_attLbl;
   d_attAuth = right.d_attLbl;
   d_attDomType = right.d_attDomType;
   d_attDomValFmt = right.d_attDomValFmt;
   d_attDomValMsmtUnit = right.d_attDomValMsmtUnit;
   d_rangeOrValue = right.d_rangeOrValue;
   d_domainValue = right.d_domainValue;
   d_domainValueDefn = right.d_domainValueDefn;
   return *this;
}

sb_DataDictDom::sb_DataDictDom(sc_Record& recprox)
{
   // Build an sb_DataDictDom from an sc_Record

   // Make sure we have a record from a Data Dictionary/Domain module.

   sc_FieldCntr::const_iterator curfield;
   if (!sb_Utils::getFieldByMnem(recprox,"DDOM",curfield))
      {
         cerr << "sb_DataDictDom::sb_DataDictDom(sc_Record const&): "
              << "Not a Data Dictionary/Domain record.";
         cerr << endl;
         return;
      }

   // We have a primary field from a  module. Start
   // picking it apart.

   sc_SubfieldCntr::const_iterator cursubfield;

   // MODN
   if (sb_Utils::getSubfieldByMnem(*curfield,"MODN",cursubfield))
      cursubfield->getA(d_moduleName);


   // RCID
   if (sb_Utils::getSubfieldByMnem(*curfield,"RCID",cursubfield))
      cursubfield->getI(d_recordID);


   // ATLB
   if (sb_Utils::getSubfieldByMnem(*curfield,"ATLB",cursubfield))
      cursubfield->getA(d_attLbl);

   // AUTH
   if (sb_Utils::getSubfieldByMnem(*curfield,"AUTH",cursubfield))
      cursubfield->getA(d_attAuth);

   // ATYP
   if (sb_Utils::getSubfieldByMnem(*curfield,"ATYP",cursubfield))
      cursubfield->getA(d_attDomType);

   // ADVF
   if (sb_Utils::getSubfieldByMnem(*curfield,"ADVF",cursubfield))
      cursubfield->getA(d_attDomValFmt);

   // ADMU
   if (sb_Utils::getSubfieldByMnem(*curfield,"ADMU",cursubfield))
      cursubfield->getA(d_attDomValMsmtUnit);

   // RAVA
   if (sb_Utils::getSubfieldByMnem(*curfield,"RAVA",cursubfield))
      cursubfield->getA(d_rangeOrValue);

   // DVAL
   if (sb_Utils::getSubfieldByMnem(*curfield,"DVAL",cursubfield))
   {
      d_domainValueSubfield = *cursubfield;
      cursubfield->getA(d_domainValue);
//ccc variable type based on  ADVF value. A|I|R|S|B|C
   }
   // DVDF
   if (sb_Utils::getSubfieldByMnem(*curfield,"DVDF",cursubfield))
      cursubfield->getA(d_domainValueDefn);

}
