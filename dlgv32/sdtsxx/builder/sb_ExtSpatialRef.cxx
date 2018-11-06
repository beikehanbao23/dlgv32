// $Id: sb_ExtSpatialRef.cxx,v 1.1 1998/09/14 15:04:22 bmaddox Exp bmaddox $

#ifdef _WIN32
   #include <iostream>
#else
   #include <iostream.h>
#endif

#ifndef INCLUDED_SB_UTILS_HXX
#include "builder/sb_Utils.hxx"
#endif

#ifndef INCLUDED_SB_EXTSPATIALREF_HXX
#include "builder/sb_ExtSpatialRef.hxx"
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

sb_ExtSpatialRef::sb_ExtSpatialRef()
               : d_recordID(0)
{
}

sb_ExtSpatialRef::sb_ExtSpatialRef(sb_ExtSpatialRef const& right)
{
   operator=(right);
}

sb_ExtSpatialRef const&
sb_ExtSpatialRef::operator=(sb_ExtSpatialRef const& right)
{
    if(this==&right)
      return *this;
    d_moduleName = right.d_moduleName;
    d_recordID = right.d_recordID;
    d_comment = right.d_comment;
    d_refDoc = right.d_refDoc;
    d_refSysName = right.d_refSysName;
    d_vertDatum = right.d_vertDatum;
    d_soundDatum = right.d_soundDatum;
    d_horizDatum = right.d_horizDatum;
    d_zoneNum = right.d_zoneNum;
    d_projection = right.d_projection;
    d_attID = right.d_attID;
    return *this;
}

sb_ExtSpatialRef::sb_ExtSpatialRef(sc_Record& recprox)
{
   // Build an sb_ExtSpatialRef from an sc_Record

   // Make sure we have a record from an External Spatial Reference module.

   sc_FieldCntr::const_iterator curfield;
   if (!sb_Utils::getFieldByMnem(recprox,"XREF",curfield))
      {
         cerr << "sb_ExtSpatialRef::sb_ExtSpatialRef(sc_Record const&): "
              << "Not an External Spatial Reference module record.";
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

   // RDOC
   if (sb_Utils::getSubfieldByMnem(*curfield,"RDOC",cursubfield))
      cursubfield->getA(d_refDoc);

   // RSNM
   if (sb_Utils::getSubfieldByMnem(*curfield,"RSNM",cursubfield))
      cursubfield->getA(d_refSysName);

   // VDAT
   if (sb_Utils::getSubfieldByMnem(*curfield,"VDAT",cursubfield))
      cursubfield->getA(d_vertDatum);

   // SDAT
   if (sb_Utils::getSubfieldByMnem(*curfield,"SDAT",cursubfield))
      cursubfield->getA(d_soundDatum);

   // HDAT
   if (sb_Utils::getSubfieldByMnem(*curfield,"HDAT",cursubfield))
      cursubfield->getA(d_horizDatum);

   // ZONE
   if (sb_Utils::getSubfieldByMnem(*curfield,"ZONE",cursubfield))
      cursubfield->getA(d_zoneNum);

   // PROJ
   if (sb_Utils::getSubfieldByMnem(*curfield,"PROJ",cursubfield))
      cursubfield->getA(d_projection);

// Secondary Fields

   // Attribute ID (ATID) Field
   if (sb_Utils::getFieldByMnem(recprox,"ATID",curfield))
      d_attID = sb_ForeignID(*curfield);

}
