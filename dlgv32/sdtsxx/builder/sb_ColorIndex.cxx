// $Id: sb_ColorIndex.cxx,v 1.1 1998/09/14 15:04:17 bmaddox Exp bmaddox $

#ifdef _WIN32
   #include <iostream>
#else
   #include <iostream.h>
#endif

#ifndef INCLUDED_SB_UTILS_HXX
#include "builder/sb_Utils.hxx"
#endif

#ifndef INCLUDED_SB_COLORINDEX_HXX
#include "builder/sb_ColorIndex.hxx"
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


sb_ColorIndex::sb_ColorIndex()
            : d_recordID(0),
              d_redComp(0),
              d_greenComp(0),
              d_blueComp(0),
              d_blackIntensityComp(0)
{
}

sb_ColorIndex::sb_ColorIndex(sb_ColorIndex const& right)
{
   operator=(right);
}

sb_ColorIndex const&
sb_ColorIndex::operator=(sb_ColorIndex const& right)
{
   if (this == &right)
     return *this;

   d_moduleName = right.d_moduleName;
   d_recordID = right.d_recordID;
   d_redComp = right.d_redComp;
   d_greenComp = right.d_greenComp;
   d_blueComp = right.d_blueComp;
   d_blackIntensityComp = right.d_blackIntensityComp;

   return *this;
}

sb_ColorIndex::sb_ColorIndex(sc_Record& recprox)
{

   // Build an sb_ColorIndex from an sc_Record

   // Make sure we have a record from a Color Index module.

   sc_FieldCntr::const_iterator curfield;
   if (!sb_Utils::getFieldByMnem(recprox,"CLRX",curfield))
      {
         cerr << "sb_ColorIndex::sb_ColorIndex(sc_Record&): "
              << "Not a Color Index record.\n";
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

   // RED
   if (sb_Utils::getSubfieldByMnem(*curfield,"RED",cursubfield))
      cursubfield->getR(d_redComp);

   // GREN
   if (sb_Utils::getSubfieldByMnem(*curfield,"GREN",cursubfield))
      cursubfield->getR(d_greenComp);

   // BLUE
   if (sb_Utils::getSubfieldByMnem(*curfield,"BLUE",cursubfield))
      cursubfield->getR(d_blueComp);

   // BLCK
   if (sb_Utils::getSubfieldByMnem(*curfield,"BLCK",cursubfield))
      cursubfield->getR(d_blackIntensityComp);

}
