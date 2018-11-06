// $Id: sb_AreaFillRep.cxx,v 1.1 1998/09/14 15:04:12 bmaddox Exp bmaddox $

#ifdef _WIN32
   #include <iostream>
#else
   #include <iostream.h>
#endif

#ifndef INCLUDED_SB_UTILS_HXX
#include "builder/sb_Utils.hxx"
#endif

#ifndef INCLUDED_SB_AREAFILLREP_HXX
#include "builder/sb_AreaFillRep.hxx"
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


sb_AreaFillRep::sb_AreaFillRep()
             : d_recordID(0),
               d_baseScale(0),
               d_smallScaleMin(0),
               d_largeScaleMax(0),
               d_colorIndex(0),
               d_hatchIndex(0),
               d_patternIndex(0)
{
}

sb_AreaFillRep::sb_AreaFillRep(sb_AreaFillRep const& right)
{
   operator=(right);
}

sb_AreaFillRep const&
sb_AreaFillRep::operator=(sb_AreaFillRep const& right)
{
   if (this == &right)
     return *this;

   d_moduleName = right.d_moduleName;
   d_recordID = right.d_recordID;
   d_baseScale = right.d_baseScale;
   d_smallScaleMin = right.d_smallScaleMin;
   d_largeScaleMax = right.d_largeScaleMax;
   d_colorIndex = right.d_colorIndex;
   d_fillStyleType = right.d_fillStyleType;
   d_hatchIndex = right.d_hatchIndex;
   d_patternIndex = right.d_patternIndex;

   return *this;

}

sb_AreaFillRep::sb_AreaFillRep(sc_Record& recprox)
{
   // Build an sb_AreaFillRep from an sc_Record

   // Make sure we have a record from an Area Fill Representation module.

   sc_Record::const_iterator curfield;
   if (!sb_Utils::getFieldByMnem(recprox,"AFIL",curfield))
      {
         cerr << "sb_AreaFillRep::sb_AreaFillRep(sc_Record&): "
              << "Not an Area Fill Representation record.";
         cerr << endl;
         return;
      }

   // We have a primary field from a module. Start
   // picking it apart.

   sc_Field::const_iterator cursubfield;

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

   // FTYP 
   if (sb_Utils::getSubfieldByMnem(*curfield,"FTYP",cursubfield))
      cursubfield->getA(d_fillStyleType);

   // HIDX
   if (sb_Utils::getSubfieldByMnem(*curfield,"HIDX",cursubfield))
      cursubfield->getI(d_hatchIndex);

   // PIDX
   if (sb_Utils::getSubfieldByMnem(*curfield,"PIDX",cursubfield))
      cursubfield->getI(d_patternIndex);

}
