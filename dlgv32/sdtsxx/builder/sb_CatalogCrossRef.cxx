// $Id: sb_CatalogCrossRef.cxx,v 1.1 1998/09/14 15:04:14 bmaddox Exp bmaddox $

#include <iostream.h>

#ifndef INCLUDED_SB_UTILS_HXX
#include "builder/sb_Utils.hxx"
#endif

#ifndef INCLUDED_SB_CATALOGCROSSREF_HXX
#include "builder/sb_CatalogCrossRef.hxx"
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

sb_CatalogCrossRef::sb_CatalogCrossRef()
                 : d_recordID(0)
{
}

sb_CatalogCrossRef::sb_CatalogCrossRef(sb_CatalogCrossRef const& right)
{
   operator=(right);
}

sb_CatalogCrossRef const&
sb_CatalogCrossRef::operator=(sb_CatalogCrossRef const& right)
{
   if(this==&right)  // Takes care of the s=s case.
     return *this;
   d_moduleName = right.d_moduleName;
   d_recordID = right.d_recordID;
   d_name1 = right.d_name1;
   d_type1 = right.d_type1;
   d_name2 = right.d_name2;
   d_type2 = right.d_type2;
   d_comment = right.d_comment;
   return *this;
}

sb_CatalogCrossRef::sb_CatalogCrossRef(sc_Record& recprox)
{
   // Build an sb_CatalogCrossRef from an sc_Record.

   // Make sure we have a record from a Catalog/Cross-Reference module.

   sc_FieldCntr::const_iterator curfield;

   if (!sb_Utils::getFieldByMnem(recprox,"CATX",curfield))
      {
         cerr << "sb_CatalogCrossRef::sb_CatalogCrossRef(sc_Record const&): "
              << "Not a CATALOG/CROSS-REFERENCE record.\n";
         return;
      }

   // We have a primary field from a Catalog/Cross-Reference module. 
   // Start picking it apart.

   sc_SubfieldCntr::const_iterator cursubfield;

   // MODN
   if (sb_Utils::getSubfieldByMnem(*curfield,"MODN",cursubfield))
      cursubfield->getA(d_moduleName);

   // RCID
   if (sb_Utils::getSubfieldByMnem(*curfield,"RCID",cursubfield))
      cursubfield->getI(d_recordID);

   // NAM1
   if (sb_Utils::getSubfieldByMnem(*curfield,"NAM1",cursubfield))
      cursubfield->getA(d_name1);

   // TYP1
   if (sb_Utils::getSubfieldByMnem(*curfield,"TYP1",cursubfield))
      cursubfield->getA(d_type1);

   // NAM2
   if (sb_Utils::getSubfieldByMnem(*curfield,"NAM2",cursubfield))
      cursubfield->getA(d_name2);

   // TYP2
   if (sb_Utils::getSubfieldByMnem(*curfield,"TYP2",cursubfield))
      cursubfield->getA(d_type2);

   // COMT
   if (sb_Utils::getSubfieldByMnem(*curfield,"COMT",cursubfield))
      cursubfield->getA(d_comment);

 }
