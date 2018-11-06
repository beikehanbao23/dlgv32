// $Id: sb_DataDictSchema.cxx,v 1.1 1998/09/14 15:04:20 bmaddox Exp bmaddox $

#ifdef _WIN32
   #include <iostream>
#else
   #include <iostream.h>
#endif

#ifndef INCLUDED_SB_UTILS_HXX
#include "builder/sb_Utils.hxx"
#endif

#ifndef INCLUDED_SB_DATADICTSCHEMA_HXX
#include "builder/sb_DataDictSchema.hxx"
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

sb_DataDictSchema::sb_DataDictSchema()
                : d_recordID(0),
                  d_maxSubfieldLen(0)
{
}

sb_DataDictSchema::sb_DataDictSchema(sb_DataDictSchema const& right)
{
   operator=(right);
}

sb_DataDictSchema const&
sb_DataDictSchema::operator=(sb_DataDictSchema const& right)
{
   if(this==&right)
     return *this;
   d_moduleName = right.d_moduleName;
   d_recordID = right.d_recordID;
   d_name = right.d_name;
   d_type = right.d_type;
   d_entityLbl = right.d_entityLbl;
   d_entityAuth = right.d_entityAuth;
   d_attributeLbl = right.d_attributeLbl;
   d_attributeAuth = right.d_attributeAuth;
   d_format = right.d_format;
   d_unit = right.d_unit;
   d_maxSubfieldLen = right.d_maxSubfieldLen;
   d_key = right.d_key;
   return *this;
}

sb_DataDictSchema::sb_DataDictSchema(sc_Record& recprox)
{
   // Build an sb_DataDictSchema from an sc_Record

   // Make sure we have a record from a Data Dictionary/Schema module.

   sc_FieldCntr::const_iterator curfield;
   if (!sb_Utils::getFieldByMnem(recprox,"DDSH",curfield))
      {
         cerr << "sb_DataDictSchema:sb_DataDictSchema(sc_Record const&): "
              << "Not a Data Dictionary/Schema record.";
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


   // NAME
   if (sb_Utils::getSubfieldByMnem(*curfield,"NAME",cursubfield))
      cursubfield->getA(d_name);

   // TYPE
   if (sb_Utils::getSubfieldByMnem(*curfield,"TYPE",cursubfield))
      cursubfield->getA(d_type);

   // ETLB
   if (sb_Utils::getSubfieldByMnem(*curfield,"ETLB",cursubfield))
      cursubfield->getA(d_entityLbl);

   // EUTH
   if (sb_Utils::getSubfieldByMnem(*curfield,"EUTH",cursubfield))
      cursubfield->getA(d_entityAuth);

   // ATLB
   if (sb_Utils::getSubfieldByMnem(*curfield,"ATLB",cursubfield))
      cursubfield->getA(d_attributeLbl);

   // AUTH
   if (sb_Utils::getSubfieldByMnem(*curfield,"AUTH",cursubfield))
      cursubfield->getA(d_attributeAuth);

   // FMT
   if (sb_Utils::getSubfieldByMnem(*curfield,"FMT",cursubfield))
      cursubfield->getA(d_format);

   // UNIT
   if (sb_Utils::getSubfieldByMnem(*curfield,"UNIT",cursubfield))
      cursubfield->getA(d_unit);

   // PREC
   if (sb_Utils::getSubfieldByMnem(*curfield,"PREC",cursubfield))
      cursubfield->getR(d_precision);

   // MXLN
   if (sb_Utils::getSubfieldByMnem(*curfield,"MXLN",cursubfield))
      cursubfield->getI(d_maxSubfieldLen);

   // KEY
   if (sb_Utils::getSubfieldByMnem(*curfield,"KEY",cursubfield))
      cursubfield->getA(d_key);
}

