// $Id: sb_SpatialDom.cxx,v 1.1 1998/09/14 15:04:33 bmaddox Exp bmaddox $

#ifdef _WIN32
#include <iostream>
#else
#include <iostream.h>
#endif

#ifndef INCLUDED_SB_UTILS_HXX
#include "builder/sb_Utils.hxx"
#endif

#ifndef INCLUDED_SB_SPATIALDOM_HXX
#include "builder/sb_SpatialDom.hxx"
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

sb_SpatialDom::sb_SpatialDom()
            : d_recordID(0)
{
}

sb_SpatialDom::sb_SpatialDom(sb_SpatialDom const& right)
{
   operator=(right);
}

sb_SpatialDom const&
sb_SpatialDom::operator=(sb_SpatialDom const& right)
{
   if (this == &right)
     return *this;

   d_moduleName = right.d_moduleName;
   d_recordID = right.d_recordID;
   d_spatialDomType = right.d_spatialDomType;
   d_domSpatialAddType = right.d_domSpatialAddType;
   d_comment = right.d_comment;
   d_domSpatialAddrs = right.d_domSpatialAddrs;
   
   return *this;
}

sb_SpatialDom::sb_SpatialDom(sc_Record& recprox)
{
   // Build an sb_SpatialDom from an sc_Record.

   // Make sure we have a record from a Spatial Domain module.

   sc_FieldCntr::const_iterator curfield;
   if (!sb_Utils::getFieldByMnem(recprox,"SPDM",curfield))
      {
         cerr << "sb_SpatialDom::sb_SpatialDom(sc_Record const&): "
              << "Not a Spatial Domain record.";
         cerr << endl;
         return;
      }
  
   // We have a primary field from a Spatial Domain module. 
   // Start picking it apart.

   sc_SubfieldCntr::const_iterator cursubfield;
  
   // MODN
   if (sb_Utils::getSubfieldByMnem(*curfield,"MODN",cursubfield))
      cursubfield->getA(d_moduleName);

   // RCID
   if (sb_Utils::getSubfieldByMnem(*curfield,"RCID",cursubfield))
      cursubfield->getI(d_recordID);

   // DTYP 
   if (sb_Utils::getSubfieldByMnem(*curfield,"DTYP",cursubfield))
      cursubfield->getA(d_spatialDomType);

   // DSTP
   if (sb_Utils::getSubfieldByMnem(*curfield,"DSTP",cursubfield))
      cursubfield->getA(d_domSpatialAddType);

   // COMT
   if (sb_Utils::getSubfieldByMnem(*curfield,"COMT",cursubfield))
      cursubfield->getA(d_comment);

   // DMSA Fields.
   sc_FieldCntr const& fields = recprox;
   for (curfield = fields.begin();
        curfield != fields.end();
        curfield++)
      {
         if (curfield->getMnemonic() == "DMSA")
           d_domSpatialAddrs.push_back(sb_SpatialAddr(*curfield));
      }
}
