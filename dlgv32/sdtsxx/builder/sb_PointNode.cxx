// $Id: sb_PointNode.cxx,v 1.1 1998/09/14 15:04:28 bmaddox Exp bmaddox $

#ifdef _WIN32
   #include <iostream>
#else
   #include <iostream.h>
#endif


#ifndef INCLUDED_SB_UTILS_HXX
#include "builder/sb_Utils.hxx"
#endif

#ifndef INCLUDED_SB_POINTNODE_HXX
#include "builder/sb_PointNode.hxx"
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

sb_PointNode::sb_PointNode()
           : d_recordID(0)
{
}


sb_PointNode::sb_PointNode(sb_PointNode const& right)
{
   operator=(right);
}

sb_PointNode const&
sb_PointNode::operator=(sb_PointNode const& right)
{
   if(this==&right)
     return *this;
 
   d_moduleName = right.d_moduleName;
   d_recordID = right.d_recordID;
   d_objectRep = right.d_objectRep;
   
   d_spatialAddrs = right.d_spatialAddrs;
   d_attributeID = right.d_attributeID;
   d_lineID = right.d_lineID;
   d_areaID = right.d_areaID;
   d_compositeID = right.d_compositeID;
   d_repModuleID = right.d_repModuleID;
   d_orientSpatialAddrs = right.d_orientSpatialAddrs;
   d_attPrimaryID = right.d_attPrimaryID;
   d_attLbl = right.d_attLbl;
   d_symbolOrientSpatialAddrs = right.d_symbolOrientSpatialAddrs;

   return *this;
}

sb_PointNode::sb_PointNode(sc_Record& recprox)
{
   // Build an sb_PointNode from an sc_Record
   
   // Make sure we have a Point-Node module.

   sc_FieldCntr::const_iterator curfield;
   if (!sb_Utils::getFieldByMnem(recprox,"PNTS",curfield))
      {
         cerr << "sb_PointNode::sb_PointNode(sc_Record const&): "
              << "Not a Point-Node record.";
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


   // OBRP
   if (sb_Utils::getSubfieldByMnem(*curfield,"OBRP",cursubfield))
      cursubfield->getA(d_objectRep);

   // Secondary Fields

   // SADR Field ... Not repeating
   sc_FieldCntr const& sadrfields = recprox;
   for (curfield = sadrfields.begin();
        curfield != sadrfields.end();
        curfield++)
      {
         if (curfield->getMnemonic() == "SADR")
            d_spatialAddrs.push_back(sb_SpatialAddr(*curfield));
      }


   // Attribute ID (ATID)
   if (sb_Utils::getFieldByMnem(recprox,"ATID", curfield))
      d_attributeID = sb_ForeignID(*curfield);

   // Line ID (LNID)
   if (sb_Utils::getFieldByMnem(recprox,"LNID", curfield))
      d_lineID = sb_ForeignID(*curfield);

   // Area ID (ARID)
   if (sb_Utils::getFieldByMnem(recprox,"ARID", curfield))
      d_areaID = sb_ForeignID(*curfield);

   // Composite ID (CPID)
   if (sb_Utils::getFieldByMnem(recprox,"CPID", curfield))
      d_compositeID = sb_ForeignID(*curfield);

   // Representation Module ID (RPID)
   if (sb_Utils::getFieldByMnem(recprox,"RPID", curfield))
      d_repModuleID = sb_ForeignID(*curfield);

   // OSAD Fields
   sc_FieldCntr const& osadfields = recprox; 
   for (curfield = osadfields.begin();
        curfield != osadfields.end();
        curfield++)
      {
         if (curfield->getMnemonic() == "OSAD")
            d_orientSpatialAddrs.push_back(sb_SpatialAddr(*curfield));
      }


   if (sb_Utils::getFieldByMnem(recprox,"PAID",curfield))
      {
        // found a PAID field, now pick it apart
        d_attPrimaryID = sb_ForeignID(*curfield); 

        // Attribute Label (ATLB)
        if (sb_Utils::getSubfieldByMnem(*curfield,"ATLB",cursubfield))
           cursubfield->getA(d_attLbl);
      }

   // SSAD Fields
   sc_FieldCntr const& ssadfields = recprox;
   for (curfield = ssadfields.begin();
        curfield != ssadfields.end();
        curfield++)
      {
         if (curfield->getMnemonic() == "SSAD")
            d_symbolOrientSpatialAddrs.push_back(sb_SpatialAddr(*curfield));
      }
}
