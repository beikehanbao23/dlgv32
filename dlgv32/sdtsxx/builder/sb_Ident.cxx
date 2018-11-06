// $Id: sb_Ident.cxx,v 1.1 1998/09/14 15:04:24 bmaddox Exp bmaddox $

#ifdef _WIN32
   #include <iostream>
#else
   #include <iostream.h>
#endif

#ifndef INCLUDED_SB_UTILS_HXX
#include "builder/sb_Utils.hxx"
#endif

#ifndef INCLUDED_SB_IDENT_HXX
#include "builder/sb_Ident.hxx"
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


sb_Ident::sb_Ident()
       : d_recordID(0),
         d_scale(0),
         d_externSpatRef(0),
         d_featuresLevel(0)
{
}

sb_Ident::sb_Ident(sb_Ident const& right)
{
   operator=(right);
}

sb_Ident const&
sb_Ident::operator=(sb_Ident const& right)
{
   if(this==&right)
     return *this;

   d_moduleName = right.d_moduleName;
   d_recordID = right.d_recordID;
   d_standardIdent = right.d_standardIdent;
   d_standardVer = right.d_standardVer;
   d_profileIdent = right.d_profileIdent;
   d_profileVer = right.d_profileVer;
   d_profileDocRef = right.d_profileDocRef;
   d_title = right.d_title;
   d_dataID = right.d_dataID;
   d_dataStruct = right.d_dataStruct;
   d_mapDate = right.d_mapDate;
   d_dataSetCreationDate = right.d_dataSetCreationDate;
   d_scale = right.d_scale;
   d_comment = right.d_comment;
   
   d_composites = right.d_composites;
   d_vectorGeom = right.d_vectorGeom;
   d_vectorTopol = right.d_vectorTopol;
   d_raster = right.d_raster;
   d_externSpatRef = right.d_externSpatRef;
   d_featuresLevel = right.d_featuresLevel;

   d_attrID = right.d_attrID;

   return *this; 
}


sb_Ident::sb_Ident(sc_Record& recprox)
{
   // Build an sb_Ident from an sc_Record.

   // Make sure we have a record from a Identification module.

   sc_FieldCntr::const_iterator curfield;
   if (!sb_Utils::getFieldByMnem(recprox,"IDEN",curfield))
      {
         cerr << "sb_Ident::sb_Ident(sc_Record const&): Not a IDEN record.";
         cerr << endl;
         return;
      }

   // We have a primary field from a Identification module. Start picking 
   // it apart.

   sc_SubfieldCntr::const_iterator cursubfield;

   // MODN
   if (sb_Utils::getSubfieldByMnem(*curfield,"MODN",cursubfield))
      cursubfield->getA(d_moduleName);

   // RCID
   if (sb_Utils::getSubfieldByMnem(*curfield,"RCID",cursubfield))
      cursubfield->getI(d_recordID);

   // STID
   if (sb_Utils::getSubfieldByMnem(*curfield,"STID",cursubfield))
      cursubfield->getA(d_standardIdent);

   // STVS
   if (sb_Utils::getSubfieldByMnem(*curfield,"STVS",cursubfield))
      cursubfield->getA(d_standardVer);

   // DOCU
   if (sb_Utils::getSubfieldByMnem(*curfield,"DOCU",cursubfield))
      cursubfield->getA(d_standardDocRef);

   // PRID
   if (sb_Utils::getSubfieldByMnem(*curfield,"PRID",cursubfield))
      cursubfield->getA(d_profileIdent);
 
   // PRVS
   if (sb_Utils::getSubfieldByMnem(*curfield,"PRVS",cursubfield))
      cursubfield->getA(d_profileVer);

   // PDOC
   if (sb_Utils::getSubfieldByMnem(*curfield,"PDOC",cursubfield))
      cursubfield->getA(d_profileDocRef);

   // TITL
   if (sb_Utils::getSubfieldByMnem(*curfield,"TITL",cursubfield))
      cursubfield->getA(d_title);

   // DAID
   if (sb_Utils::getSubfieldByMnem(*curfield,"DAID",cursubfield))
      cursubfield->getA(d_dataID);

   // DAST
   if (sb_Utils::getSubfieldByMnem(*curfield,"DAST",cursubfield))
      cursubfield->getA(d_dataStruct);

   // MPDT
   if (sb_Utils::getSubfieldByMnem(*curfield,"MPDT",cursubfield))
      cursubfield->getA(d_mapDate);

   // DCDT
   if (sb_Utils::getSubfieldByMnem(*curfield,"DCDT",cursubfield))
      cursubfield->getA(d_dataSetCreationDate);

   // SCAL
   if (sb_Utils::getSubfieldByMnem(*curfield,"SCAL",cursubfield))
      cursubfield->getI(d_scale);

   // COMT
   if (sb_Utils::getSubfieldByMnem(*curfield,"COMT",cursubfield))
      cursubfield->getA(d_comment);

   // Secondary Fields

   // Conformance (CONF) Field
   if (!sb_Utils::getFieldByMnem(recprox,"CONF",curfield))
      {
         cerr << "sb_Ident::sb_Ident(sc_Record const&): Not a Conformance "
              << "field to be found.";
         cerr << endl;
         return;
      }

   // We have a secondary field from a Identification module. Start picking 
   // it apart.

   // FFYN 
   if (sb_Utils::getSubfieldByMnem(*curfield,"FFYN",cursubfield))
      cursubfield->getA(d_composites);

   // VGYN
   if (sb_Utils::getSubfieldByMnem(*curfield,"VGYN",cursubfield))
      cursubfield->getA(d_vectorGeom);

   // GTYN
   if (sb_Utils::getSubfieldByMnem(*curfield,"GTYN",cursubfield))
      cursubfield->getA(d_vectorTopol);

   // RCYN
   if (sb_Utils::getSubfieldByMnem(*curfield,"RCYN",cursubfield))
      cursubfield->getA(d_raster);

   // EXSP
   if (sb_Utils::getSubfieldByMnem(*curfield,"EXSP",cursubfield))
      cursubfield->getI(d_externSpatRef);

   // FTLV
   if (sb_Utils::getSubfieldByMnem(*curfield,"FTLV",cursubfield))
      cursubfield->getI(d_featuresLevel);

   // CDLV - Coding level (I)
   if (sb_Utils::getSubfieldByMnem(*curfield,"CDLV",cursubfield))
      cursubfield->getI(d_codingLevel);

   // NGDM = nongeospatila deminsions (A)
   if (sb_Utils::getSubfieldByMnem(*curfield,"NGDM",cursubfield))
      cursubfield->getA(d_nongeoDeminsion);

   // Attribute ID (ATID) Field
   if (sb_Utils::getFieldByMnem(recprox,"ATID",curfield))
      d_attrID = sb_ForeignID(*curfield);

}
