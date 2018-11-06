// $Id: sb_Completeness.cxx,v 1.1 1998/09/14 15:04:18 bmaddox Exp bmaddox $

#ifdef _WIN32
   #include <iostream>
#else
   #include <iostream.h>
#endif

#ifndef INCLUDED_SB_UTILS_HXX
#include "builder/sb_Utils.hxx"
#endif

#ifndef INCLUDED_SB_COMPLETENESS_HXX
#include "builder/sb_Completeness.hxx"
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

sb_Completeness::sb_Completeness()
              : d_recordID(0)
{
}

sb_Completeness::sb_Completeness(sb_Completeness const& right)
{
   operator=(right);
}

sb_Completeness const&
sb_Completeness::operator=(sb_Completeness const& right)
{
   if (this == &right)
     return *this;

   d_moduleName = right.d_moduleName;
   d_recordID = right.d_recordID;
   d_comment = right.d_comment;
   d_attributeID = right.d_attributeID;
   d_foreignID = right.d_foreignID;

   return *this;
}
   
sb_Completeness::sb_Completeness(sc_Record& recprox)
{
   // Build an sb_Completeness from an sc_Record

   // Make sure we have a record from a Completeness module.

   sc_FieldCntr::const_iterator curfield;
   if (!sb_Utils::getFieldByMnem(recprox,"DQCG",curfield))
      {
         cerr << "sb_Completeness::sb_Completeness(sc_Record const&): "
              << "Not a Completeness record.\n";
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


   // COMT 
   if (sb_Utils::getSubfieldByMnem(*curfield,"COMT",cursubfield))
      cursubfield->getA(d_comment);

   // Secondary Fields

   // Attribute ID (ATID) Field
   if (sb_Utils::getFieldByMnem(recprox,"ATID",curfield))
      d_attributeID = sb_ForeignID(*curfield);

   // Foreign ID (FRID) Field
   if (sb_Utils::getFieldByMnem(recprox,"FRID",curfield))
      d_foreignID = sb_ForeignID(*curfield);

}
