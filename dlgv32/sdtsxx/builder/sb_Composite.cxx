// $Id: sb_Composite.cxx,v 1.1 1998/09/14 15:04:18 bmaddox Exp bmaddox $

#ifdef _WIN32
   #include <iostream>
#else
   #include <iostream.h>
#endif

#ifndef INCLUDED_SB_UTILS_HXX
#include "builder/sb_Utils.hxx"
#endif

#ifndef INCLUDED_SB_COMPOSITE_HXX
#include "builder/sb_Composite.hxx"
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

sb_Composite::sb_Composite()
           : d_recordID(0)
{
}

sb_Composite::sb_Composite(sb_Composite const& right)
{
   operator=(right);
}


sb_Composite const&
sb_Composite::operator=(sb_Composite const& right)
{
   if (this == &right)
     return *this;
   
   d_moduleName = right.d_moduleName;
   d_recordID = right.d_recordID;
   d_objectRep = right.d_objectRep;
   d_attributeID = right.d_attributeID;
   d_foreignID = right.d_foreignID;
   d_compositeID = right.d_compositeID;

   return *this;
}

sb_Composite::sb_Composite(sc_Record& recprox)
{

   // Build an sb_Composite from an sc_Record

   // Make sure we have a record from a Composite module.

   sc_FieldCntr::const_iterator curfield;
   if (!sb_Utils::getFieldByMnem(recprox,"COMP",curfield))
      {
         cerr << "sb_Composite::sb_Composite(sc_Record&): "
              << "Not a Composite record.";
         cerr << endl;
         return;
      }

   // We have a primary field from a module. Start
   // picking it apart.

   sc_SubfieldCntr::const_iterator cursubfield;

   // MODN
   if (sb_Utils::getSubfieldByMnem(*curfield,"MODN",cursubfield))
      cursubfield->getA(d_moduleName);


   // RCID
   if (sb_Utils::getSubfieldByMnem(*curfield,"RCID",cursubfield))
      cursubfield->getI(d_recordID);


   // OBRP
   if (sb_Utils::getSubfieldByMnem(*curfield,"OBRP",cursubfield))
      cursubfield->getA(d_objectRep);

   // Secondary Fields  ... all repeating

   // Attribute ID (ATID) Field
   if (sb_Utils::getFieldByMnem(recprox,"ATID",curfield))
      d_attributeID = sb_ForeignID(*curfield);

   
   // Foreign ID (FRID) Fields
   sc_FieldCntr const& fields = recprox;
   for (curfield = fields.begin();
        curfield != fields.end();
        curfield++)
      {
         if (curfield->getMnemonic() == "FRID")
            d_foreignID.push_back(sb_ForeignID(*curfield));
      }


   // Composite ID (CPID) Field
   if (sb_Utils::getFieldByMnem(recprox,"CPID",curfield))
      d_compositeID = sb_ForeignID(*curfield);

}
