// $Id: sb_Ring.cxx,v 1.1 1998/09/14 15:04:32 bmaddox Exp bmaddox $

#ifdef _WIN32
   #include <iostream>
#else
   #include <iostream.h>
#endif

#ifndef INCLUDED_SB_UTILS_HXX
#include "builder/sb_Utils.hxx"
#endif

#ifndef INCLUDED_SB_RING_HXX
#include "builder/sb_Ring.hxx"
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

sb_Ring::sb_Ring()
      : d_recordID(0)
{
}

sb_Ring::sb_Ring(sb_Ring const& right)
{
   operator=(right);
}

sb_Ring const&
sb_Ring::operator=(sb_Ring const& right)
{
   if (this == &right)
     return *this;

   d_moduleName = right.d_moduleName;
   d_recordID = right.d_recordID;
   d_objectRep = right.d_objectRep;
   d_lineOrArcForeignID = right.d_lineOrArcForeignID;
   d_polygonID = right.d_polygonID;

   return *this;
}

sb_Ring::sb_Ring(sc_Record& recprox)
{
   // Build an sb_Ring from an sc_Record

   // Make sure we have a record from a Ring module.

   sc_FieldCntr::const_iterator curfield;
   if (!sb_Utils::getFieldByMnem(recprox,"RING",curfield))
      {
         cerr << "sb_Ring::sb_Ring(sc_Record&): "
              << "Not a Ring record.";
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

   // Line or Arc Foreign ID (LAID) Fields
   sc_FieldCntr const& laid_fields = recprox;
   for (curfield = laid_fields.begin();
        curfield != laid_fields.end();
        curfield++)
      {
         if (curfield->getMnemonic() == "LAID")
            d_lineOrArcForeignID.push_back(sb_ForeignID(*curfield));
      }

   // Polygon ID (PLID) Fields
   sc_FieldCntr const& plid_fields = recprox;
   for (curfield = plid_fields.begin();
        curfield != plid_fields.end();
        curfield++)
      {
         if (curfield->getMnemonic() == "PLID")
            d_polygonID.push_back(sb_ForeignID(*curfield));
      }
}
