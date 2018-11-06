// $Id: sb_Arc.cxx,v 1.1 1998/09/14 15:04:11 bmaddox Exp bmaddox $ 

#ifdef _WIN32
   #include <iostream>
#else
   #include <iostream.h>
#endif

#ifndef INCLUDED_SB_UTILS_HXX
#include "builder/sb_Utils.hxx"
#endif

#ifndef INCLUDED_SB_ARC_HXX
#include "builder/sb_Arc.hxx"
#endif

#ifndef INCLUDED_SC_RECORD_H
#include "container/sc_Record.h"
#endif
#ifndef INCLUDED_SC_Field_H
#include "container/sc_Field.h"
#endif
#ifndef INCLUDED_SC_SUBFIELD_H
#include "container/sc_Subfield.h"
#endif

sb_Arc::sb_Arc()
     : d_recordID(0)
{
}

sb_Arc::sb_Arc(sb_Arc const& right)
{
   operator=(right);
}

sb_Arc const&
sb_Arc::operator=(sb_Arc const& right)
{
   if (this == &right)
     return *this;
   
   d_moduleName = right.d_moduleName;
   d_recordID = right.d_recordID;
   d_objectRep = right.d_objectRep;
   d_surface = right.d_surface;
   d_order = right.d_order;
   d_centerAddr = right.d_centerAddr;
   d_startAddr = right.d_startAddr;
   d_endAddr = right.d_endAddr;
   d_mJRA = right.d_mJRA;
   d_mNRA = right.d_mNRA;
   d_curveAddrs = right.d_curveAddrs;
   d_attributeID = right.d_attributeID;
   d_compositeID = right.d_compositeID;
   d_repModuleID = right.d_repModuleID; 
  
   return *this;
}

sb_Arc::sb_Arc(sc_Record& recprox)
{
   // Build an sb_Arc from an sc_Record

   // Make sure we have a record from an Arc module.

   sc_Record::const_iterator curfield, curfield2;

   if (!sb_Utils::getFieldByMnem(recprox,"ARC",curfield))
      {
         cerr << "sb_Arc::sb_Arc(sc_Record&): "
              << "Not an Arc record.";
         cerr << endl;
         return;
      }

   // We have a primary field from a  module. Start
   // picking it apart.

   sc_Field::const_iterator cursubfield;

   // MODN
   if (sb_Utils::getSubfieldByMnem(*curfield,"MODN",cursubfield))
      cursubfield->getA(d_moduleName);


   // RCID
   if (sb_Utils::getSubfieldByMnem(*curfield,"RCID",cursubfield))
      cursubfield->getI(d_recordID);

   // OBRP
   if (sb_Utils::getSubfieldByMnem(*curfield,"OBRP",cursubfield))
      cursubfield->getA(d_objectRep);

   // SRFC
   if (sb_Utils::getSubfieldByMnem(*curfield,"SRFC",cursubfield))
      cursubfield->getA(d_surface);

   // ORDR
   if (sb_Utils::getSubfieldByMnem(*curfield,"ORDR",cursubfield))
      cursubfield->getI(d_order);

   // Secondary Fields
   if (!sb_Utils::getFieldByMnem(recprox,"ARAD",curfield))
      {
         cerr << "sb_Arc::sb_Arc(sc_Record&): "
              << "Didn't find an Arc Address Field ";
         cerr << endl;
         return;
      }
   else  
      {
                    // Get Subfields of ARAD
        // CTAD
        if (sb_Utils::getFieldByMnem(recprox,"CTAD",curfield2))
          d_centerAddr = sb_SpatialAddr(*curfield2);

        // STAD
        if (sb_Utils::getFieldByMnem(recprox,"STAD",curfield2))
	       d_startAddr = sb_SpatialAddr(*curfield2);	

        // ENAD
        if (sb_Utils::getFieldByMnem(recprox,"ENAD",curfield2))
          d_endAddr = sb_SpatialAddr(*curfield2);
      }

   // Ellipse Address Field
   if (!sb_Utils::getFieldByMnem(recprox,"ELAD",curfield))
      {
         cerr << "sb_Arc::sb_Arc(sc_Record&): "
              << "Didn't find an Ellipse Address Field ";
         cerr << endl;
         return;
      }
   else
      {        // Get ELAD Subfields
        // MJRA 
        if (sb_Utils::getFieldByMnem(recprox,"MJRA",curfield2))
          d_mJRA = sb_SpatialAddr(*curfield2);

        // MNRA
        if (sb_Utils::getFieldByMnem(recprox,"MNRA",curfield2))
	       d_mNRA = sb_SpatialAddr(*curfield2);
      }

   // CADR Fields.
   sc_FieldCntr const& cadr_fields = recprox; 
   for (curfield = cadr_fields.begin();
        curfield != cadr_fields.end();
        curfield++)
      {
         if (curfield->getMnemonic() == "CADR")
            d_curveAddrs.push_back(sb_SpatialAddr(*curfield));
      }

   // ATID Fields
   sc_FieldCntr const& atid_fields = recprox;
   for (curfield = atid_fields.begin();
        curfield != atid_fields.end();
        curfield++)
      {
         if (curfield->getMnemonic() == "ATID")
            d_attributeID.push_back(sb_ForeignID(*curfield));
      }
 

   // CPID Fields
   sc_FieldCntr const& cpid_fields =  recprox; 
   for (curfield = cpid_fields.begin();
        curfield != cpid_fields.end();
        curfield++)
      {
         if (curfield->getMnemonic() == "CPID")
            d_compositeID.push_back(sb_ForeignID(*curfield));
      }

   // RPID Fields
   sc_FieldCntr const& rpid_fields =  recprox; 
   for (curfield = rpid_fields.begin();
        curfield != rpid_fields.end();
        curfield++)
      {
         if (curfield->getMnemonic() == "RPID")
            d_repModuleID.push_back(sb_ForeignID(*curfield));
      }

}   
