// $Id: sb_DataDictDefn.cxx,v 1.1 1998/09/14 15:04:19 bmaddox Exp bmaddox $

#ifdef _WIN32
   #include <iostream>
#else
   #include <iostream.h>
#endif

#ifndef INCLUDED_SB_UTILS_HXX
#include "builder/sb_Utils.hxx"
#endif

#ifndef INCLUDED_SB_DATADICTDEFN_HXX
#include "builder/sb_DataDictDefn.hxx"
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


sb_DataDictDefn::sb_DataDictDefn()
              : d_recordID(0)
{
}

sb_DataDictDefn::sb_DataDictDefn(sb_DataDictDefn const& right)
{
   operator=(right);
}


sb_DataDictDefn const&
sb_DataDictDefn::operator=(sb_DataDictDefn const& right)
{
    if(this==&right)
      return *this;
    d_moduleName = right.d_moduleName;
    d_recordID = right.d_recordID;
    d_entOrAtt = right.d_entOrAtt;
    d_entAttLbl = right.d_entAttLbl;
    d_source = right.d_source;
    d_definition = right.d_definition;
    d_attAuthority = right.d_attAuthority;
    d_attAuthorityDes = right.d_attAuthorityDes;
    return *this;
}

sb_DataDictDefn::sb_DataDictDefn(sc_Record& recprox)
{
   // Build an sb_DataDictDefn from an sc_Record

   // Make sure we have a record from a Data Dictionary/Definition module.

   sc_FieldCntr::const_iterator curfield;
   if (!sb_Utils::getFieldByMnem(recprox,"DDDF",curfield))
      {
         cerr << "sb_DataDictDefn::sb_DataDictDefn(sc_Record const&): "
              << "Not a Data Dictionary/Definition record.";
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


   // EORA
   if (sb_Utils::getSubfieldByMnem(*curfield,"EORA",cursubfield))
      cursubfield->getA(d_entOrAtt);

   // EALB
   if (sb_Utils::getSubfieldByMnem(*curfield,"EALB",cursubfield))
      cursubfield->getA(d_entAttLbl);

   // SRCE
   if (sb_Utils::getSubfieldByMnem(*curfield,"SRCE",cursubfield))
      cursubfield->getA(d_source);

   // DFIN
   if (sb_Utils::getSubfieldByMnem(*curfield,"DFIN",cursubfield))
      cursubfield->getA(d_definition);

   // AUTH
   if (sb_Utils::getSubfieldByMnem(*curfield,"AUTH",cursubfield))
      cursubfield->getA(d_attAuthority);

   // ADSC
   if (sb_Utils::getSubfieldByMnem(*curfield,"ADSC",cursubfield))
      cursubfield->getA(d_attAuthorityDes);

}
