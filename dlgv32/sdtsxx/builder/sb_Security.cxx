// $Id: sb_Security.cxx,v 1.1 1998/09/14 15:04:32 bmaddox Exp bmaddox $

#ifdef _WIN32
   #include <iostream>
#else
   #include <iostream.h>
#endif

#ifndef INCLUDED_SB_UTILS_HXX
#include "builder/sb_Utils.hxx"
#endif

#ifndef INCLUDED_SB_SECURITY_HXX
#include "builder/sb_Security.hxx"
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

sb_Security::sb_Security()
          : d_recordID(0)
{
}

sb_Security::sb_Security(sb_Security const& right)
{
   operator=(right);
}

sb_Security const&
sb_Security::operator=(sb_Security const& right)
{
    if(this==&right)
      return *this;

    d_moduleName = right.d_moduleName;
    d_recordID = right.d_recordID;
    d_securityClass = right.d_securityClass;
    d_control = right.d_control;
    d_releaseInstruct = right.d_releaseInstruct;
    d_reviewDate = right.d_reviewDate;
    d_reviewInstruct = right.d_reviewInstruct;
    d_comment = right.d_comment;
    d_foreignID = right.d_foreignID;

    return *this;
}

sb_Security::sb_Security(sc_Record& recprox)
{
   // Build an sb_Security from an sc_Record

   // Make sure we have a record from a Security module.

   sc_FieldCntr::const_iterator curfield;
   if (!sb_Utils::getFieldByMnem(recprox,"SCUR",curfield))
      {
         cerr << "sb_Security::sb_Security(sc_Record const&): "
              << "Not a Security record.";
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


   // CLAS 
   if (sb_Utils::getSubfieldByMnem(*curfield,"CLAS",cursubfield))
      cursubfield->getA(d_securityClass);

   // CTRL
   if (sb_Utils::getSubfieldByMnem(*curfield,"CTRL",cursubfield))
      cursubfield->getA(d_control);


   // RLIS
   if (sb_Utils::getSubfieldByMnem(*curfield,"RLIS",cursubfield))
      cursubfield->getA(d_releaseInstruct);

   // RVDT
   if (sb_Utils::getSubfieldByMnem(*curfield,"RVDT",cursubfield))
      cursubfield->getA(d_reviewDate);

   // RVIS 
   if (sb_Utils::getSubfieldByMnem(*curfield,"RVIS",cursubfield))
      cursubfield->getA(d_reviewInstruct);

   // COMT
   if (sb_Utils::getSubfieldByMnem(*curfield,"COMT",cursubfield))
      cursubfield->getA(d_comment);

   // Secondary Fields

   // Foreign ID (FRID) Field
   if (sb_Utils::getFieldByMnem(recprox,"FRID",curfield))
      d_foreignID = sb_ForeignID(*curfield);
}
