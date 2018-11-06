
// $Id: sb_CatalogSpatialDom.cxx,v 1.1 1998/09/14 15:04:15 bmaddox Exp bmaddox $

#ifdef _WIN32
   #include <iostream>
#else
   #include <iostream.h>
#endif

#ifndef INCLUDED_SB_UTILS_HXX
#include "builder/sb_Utils.hxx"
#endif

#ifndef INCLUDED_SB_CATALOGSPATIALDOM_HXX
#include "builder/sb_CatalogSpatialDom.hxx"
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


sb_CatalogSpatialDom::sb_CatalogSpatialDom()
                   : d_recordID(0)
{
}

sb_CatalogSpatialDom::sb_CatalogSpatialDom(sb_CatalogSpatialDom const& right)
{
   operator=(right);
}

sb_CatalogSpatialDom const&
sb_CatalogSpatialDom::operator=(sb_CatalogSpatialDom const& right)
{
   if(this==&right)
     return *this;
   d_moduleName = right.d_moduleName;
   d_recordID = right.d_recordID;
   d_name = right.d_name;
   d_type = right.d_type;
   d_domain = right.d_domain;
   d_map = right.d_map;
   d_theme = right.d_theme;
   d_aggregateObj = right.d_aggregateObj;
   d_aggregateObjType = right.d_aggregateObjType;
   d_comment = right.d_comment;
   return *this;
}

sb_CatalogSpatialDom::sb_CatalogSpatialDom(sc_Record& recprox)
{
   // Build an sb_CatalogSpatialDom from an sc_Record.

   // Make sure we have a record from a Catalog/Spatial Domain module.

   sc_FieldCntr::const_iterator curfield;
   if (!sb_Utils::getFieldByMnem(recprox,"CATS",curfield))
      {
         cerr << "sb_CatalogSpatialDom::sb_CatalogSpatialDom"
              << "(sc_Record const&): Not a CATALOG/SPATIAL DOMAIN record.";
         cerr << endl;
         return;
      }

   // We have a primary field from a Catalog/Spatial Domain module. Start
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

   // DOMN
   if (sb_Utils::getSubfieldByMnem(*curfield,"DOMN",cursubfield))
      cursubfield->getA(d_domain);
   
   // MAP
   if (sb_Utils::getSubfieldByMnem(*curfield,"MAP",cursubfield))
      cursubfield->getA(d_map);

   // THEM
   if (sb_Utils::getSubfieldByMnem(*curfield,"THEM",cursubfield))
      cursubfield->getA(d_theme);

   // AGOB
   if (sb_Utils::getSubfieldByMnem(*curfield,"AGOB",cursubfield))
      cursubfield->getA(d_aggregateObj);

   // AGTP
   if (sb_Utils::getSubfieldByMnem(*curfield,"AGTP",cursubfield))
      cursubfield->getA(d_aggregateObjType);

   // COMT
   if (sb_Utils::getSubfieldByMnem(*curfield,"MODN",cursubfield))
      cursubfield->getA(d_moduleName);

}


