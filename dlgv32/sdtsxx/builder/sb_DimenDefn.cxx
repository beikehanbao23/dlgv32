// $Id: sb_DimenDefn.cxx,v 1.1 1998/09/14 15:04:21 bmaddox Exp bmaddox $

#ifdef _WIN32
   #include <iostream>
#else
   #include <iostream.h>
#endif

#ifndef INCLUDED_SB_UTILS_HXX
#include "builder/sb_Utils.hxx"
#endif

#ifndef INCLUDED_SB_DIMENDEFN_HXX
#include "builder/sb_DimenDefn.hxx"
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


sb_DimenDefn::sb_DimenDefn()
           : d_recordID(0),
             d_dimenCompRes(0)
{
}
  

sb_DimenDefn::sb_DimenDefn(sb_DimenDefn const& right)
{
   operator=(right);
}

sb_DimenDefn const&
sb_DimenDefn::operator=(sb_DimenDefn const& right)
{
    if(this==&right)
      return *this;
    d_moduleName = right.d_moduleName;
    d_recordID = right.d_recordID;
    d_dimenLbl = right.d_dimenLbl;
    d_dimenCompFormat = right.d_dimenCompFormat;
    d_dimenCompRes = right.d_dimenCompRes;
    d_dimenValMeasureUnit = right.d_dimenValMeasureUnit;
    d_dimenDescription = right.d_dimenDescription;
    d_dimenAttributeID = right.d_dimenAttributeID;
    return *this;
}

sb_DimenDefn::sb_DimenDefn(sc_Record& recprox)
{
   // Build an sb_DimenDefn from an sc_Record

   // Make sure we have a record from a Dimension Definition module.

   sc_FieldCntr::const_iterator curfield;
   if (!sb_Utils::getFieldByMnem(recprox,"DMDF",curfield))
      {
         cerr << "sb_DimenDefn::sb_DimenDefn(sc_Record const&): "
              << "Not a Dimension Definition record.";
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

   // DMLB 
   if (sb_Utils::getSubfieldByMnem(*curfield,"DMLB",cursubfield))
      cursubfield->getA(d_dimenLbl);

   // DFMT
   if (sb_Utils::getSubfieldByMnem(*curfield,"DFMT",cursubfield))
      cursubfield->getA(d_dimenCompFormat);


   // DRES
   if (sb_Utils::getSubfieldByMnem(*curfield,"DRES",cursubfield))
      cursubfield->getR(d_dimenCompRes);


   // DDMU
   if (sb_Utils::getSubfieldByMnem(*curfield,"DDMU",cursubfield))
      cursubfield->getA(d_dimenValMeasureUnit);

   // DDES
   if (sb_Utils::getSubfieldByMnem(*curfield,"DDES",cursubfield))
      cursubfield->getA(d_dimenDescription);

   // Secondary Fields

   // Dimension Attribute ID (DATP) Field
   if (sb_Utils::getFieldByMnem(recprox,"DATP",curfield))
      d_dimenAttributeID = sb_ForeignID(*curfield);

}
