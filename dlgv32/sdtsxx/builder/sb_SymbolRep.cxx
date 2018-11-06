// $Id: sb_SymbolRep.cxx,v 1.1 1998/09/14 15:04:34 bmaddox Exp bmaddox $

#ifdef _WIN32
   #include <iostream>
#else
   #include <iostream.h>
#endif



 #ifndef INCLUDED_SB_UTILS_HXX
 #include "builder/sb_Utils.hxx"
 #endif

 #ifndef INCLUDED_SB_SYMBOLREP_HXX
 #include "builder/sb_SymbolRep.hxx"
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

 sb_SymbolRep::sb_SymbolRep()
           : d_recordID(0),
            d_baseScale(0),
             d_smallScaleMin(0),
             d_largeScaleMax(0),
             d_colorIndex(0),
             d_symMarkerType(0),
             d_markerSize(0)
{
}

sb_SymbolRep::sb_SymbolRep(sb_SymbolRep const& right)
{
   operator=(right);
}

sb_SymbolRep const& 
sb_SymbolRep::operator=(sb_SymbolRep const& right)
{
   if (this == & right)
     return *this;
   
   d_moduleName = right.d_moduleName;
   d_recordID = right.d_recordID;
   d_baseScale = right.d_baseScale;
   d_smallScaleMin = right.d_smallScaleMin;
   d_largeScaleMax = right.d_largeScaleMax;
   d_colorIndex = right.d_colorIndex;
   d_symMarkerType = right.d_symMarkerType;
   d_markerSize = right.d_markerSize;

   return *this;
}

sb_SymbolRep::sb_SymbolRep(sc_Record& recprox)
{

   // Build an sb_SymbolRep from an sc_Record

   // Make sure we have a record from a Symbol Representation module.

   sc_FieldCntr::const_iterator curfield;
   if (!sb_Utils::getFieldByMnem(recprox,"SYRP",curfield))
      {
         cerr << "sb_SymbolRep::sb_SymbolRep(sc_Record&): "
              << "Not a Symbol Representation record.";
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

   // BSCL
   if (sb_Utils::getSubfieldByMnem(*curfield,"BSCL",cursubfield))
      cursubfield->getI(d_baseScale);

   // SSCL
   if (sb_Utils::getSubfieldByMnem(*curfield,"SSCL",cursubfield))
      cursubfield->getI(d_smallScaleMin);

   // LSCL
   if (sb_Utils::getSubfieldByMnem(*curfield,"LSCL",cursubfield))
      cursubfield->getI(d_largeScaleMax);

   // CLDX
   if (sb_Utils::getSubfieldByMnem(*curfield,"CLDX",cursubfield))
      cursubfield->getI(d_colorIndex);

   // SMKR
   if (sb_Utils::getSubfieldByMnem(*curfield,"SMKR",cursubfield))
      cursubfield->getI(d_symMarkerType);

   // MKSZ
   if (sb_Utils::getSubfieldByMnem(*curfield,"MKSZ",cursubfield))
      cursubfield->getR(d_markerSize);

 }
