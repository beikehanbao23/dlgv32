// $Id: sb_Polygon.cxx,v 1.1 1998/09/14 15:04:28 bmaddox Exp bmaddox $

#ifdef _WIN32
   #include <iostream>
#else
   #include <iostream.h>
#endif

#ifndef INCLUDED_SB_UTILS_HXX
#include "builder/sb_Utils.hxx"
#endif

#ifndef INCLUDED_SPOLYGON_HXX
#include "builder/sb_Polygon.hxx"
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


sb_Polygon::sb_Polygon()
         : d_recordID(0)
{
}

sb_Polygon::sb_Polygon(sb_Polygon const& right)
{
    operator=(right);
}

sb_Polygon const&
sb_Polygon::operator=(sb_Polygon const& right)
{
    if(this==&right)
      return *this;

    d_moduleName = right.d_moduleName;
    d_recordID = right.d_recordID;
    d_objectRep = right.d_objectRep;
    
    d_attributeID = right.d_attributeID;
    d_ringID = right.d_ringID;
    d_chainID = right.d_chainID;
    d_compositeID = right.d_compositeID;
    d_repModuleID = right.d_repModuleID;

    return *this;
}

sb_Polygon::sb_Polygon(sc_Record& recprox)
{
    // Build an sb_Polygon from an sc_Record
    
    // Make sure we have a record from a Polygon module.

    sc_FieldCntr::const_iterator curfield;
    if (!sb_Utils::getFieldByMnem(recprox,"POLY",curfield))
       {
         cerr << "sb_Polygon::sb_Polygon(sc_Record const&): "
              << "Not a Polygon record." ;
         cerr << endl;
         return;
       }

   // We have a primary field from a module.  Start picking it apart.

   sc_SubfieldCntr::const_iterator cursubfield;
   
   // MODN
   if (sb_Utils::getSubfieldByMnem(*curfield,"MODN", cursubfield))
      cursubfield->getA(d_moduleName);

   // RCID
   if (sb_Utils::getSubfieldByMnem(*curfield,"RCID",cursubfield))
      cursubfield->getI(d_recordID);

   // OBRP 
   if (sb_Utils::getSubfieldByMnem(*curfield,"OBRP",cursubfield))
      cursubfield->getA(d_objectRep);

// Secondary Fields

// Attribute ID (ATID) Field
   if (sb_Utils::getFieldByMnem(recprox,"ATID",curfield))
      d_attributeID = sb_ForeignID(*curfield);

// Ring ID (RFID) Field
   if (sb_Utils::getFieldByMnem(recprox,"RFID",curfield))
      d_ringID = sb_ForeignID(*curfield);

// Chain ID (CHID) Field
   if (sb_Utils::getFieldByMnem(recprox,"CHID",curfield))
      d_chainID = sb_ForeignID(*curfield);

// Composite ID (CPID) Field
   if (sb_Utils::getFieldByMnem(recprox,"CPID",curfield))
      d_compositeID = sb_ForeignID(*curfield);

// Representation Module ID (RPID)
   if (sb_Utils::getFieldByMnem(recprox,"RPID",curfield))
      d_repModuleID = sb_ForeignID(*curfield);

}
