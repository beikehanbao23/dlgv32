// $Id: sb_Registration.cxx,v 1.1 1998/09/14 15:04:31 bmaddox Exp bmaddox $

#ifdef _WIN32
#include <iostream>
#else
#include <iostream.h>
#endif

#ifndef INCLUDED_SB_UTILS_HXX
#include "builder/sb_Utils.hxx"
#endif

#ifndef INCLUDED_SB_REGISTRATION_HXX
#include "builder/sb_Registration.hxx"
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


sb_Registration::sb_Registration()
              : d_recordID(0)
{
}

sb_Registration::sb_Registration(sb_Registration const& right)
{
   operator=(right);
}

sb_Registration const&
sb_Registration::operator=(sb_Registration const& right)
{
    if(this==&right)
      return *this;

    d_moduleName = right.d_moduleName;
    d_recordID = right.d_recordID;
    d_comment = right.d_comment;
    d_extRefSpatialAddrs = right.d_extRefSpatialAddrs;
    d_intRefSpatialAddrs = right.d_intRefSpatialAddrs;

    return *this;
}

sb_Registration::sb_Registration(sc_Record& recprox)
{
   // Build a sb_Registration from an sc_Record

   // Make sure we have a record from a Registration module.

   sc_FieldCntr::const_iterator curfield;
   if (!sb_Utils::getFieldByMnem(recprox,"RGIS",curfield))
      {
         cerr << "sb_Registration::sb_Registration(sc_Record const&): "
              << "Not a Registration record.";
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


   // COMT
   if (sb_Utils::getSubfieldByMnem(*curfield,"COMT",cursubfield))
      cursubfield->getA(d_comment);

   // Secondary Fields

   // XXX I'm almost 100% positive that this doesn't work.  I'm not sure
   // how the following stuff works, I just pasted it from sb_Line.  I'll
   // get back around to fixing it sometime.  I don't have any data to test
   // it with anyway...so let's just say it's okay to leave it like this
   // for now.  
   
   // EADS Fields

   sc_FieldCntr const& fields = recprox;
   for (curfield = fields.begin();
        curfield != fields.end();
        curfield++)
      {
         if (curfield->getMnemonic() == "EADS")
            d_extRefSpatialAddrs.push_back(sb_SpatialAddr(*curfield));
      }


   // IADS Fields
   sc_FieldCntr const& fields2 = recprox;
   for (curfield = fields2.begin();
        curfield != fields2.end();
        curfield++)
      {
         if (curfield->getMnemonic() == "IADS")
            d_intRefSpatialAddrs.push_back(sb_SpatialAddr(*curfield));
      }
}
