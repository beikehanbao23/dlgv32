// $Id: sb_TextRep.cxx,v 1.1 1998/09/14 15:04:35 bmaddox Exp bmaddox $

#ifdef _WIN32
   #include <iostream>
#else
   #include <iostream.h>
#endif

#ifndef INCLUDED_SB_UTILS_HXX
#include "builder/sb_Utils.hxx"
#endif

#ifndef INCLUDED_SB_TEXTREP_HXX
#include "builder/sb_TextRep.hxx"
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

sb_TextRep::sb_TextRep()
         : d_recordID(0),
           d_baseScale(0),
           d_smallScaleMin(0),
           d_largeScaleMax(0),
           d_colorIndex(0),
           d_charHeight(0),
           d_fontIndex(0),
           d_textPath("RIGHT"),
           d_horizTextAlign("LEFT"),
           d_vertTextAlign("BASE"),
           d_charExpanFact(1),
           d_charSpacing(0),
           d_skewAngle(90)
{
}

sb_TextRep::sb_TextRep(sb_TextRep const& right)
{
   operator=(right);
}

sb_TextRep const& 
sb_TextRep::operator=(sb_TextRep const& right)
{
   if (this == &right)
     return *this;

   d_moduleName = right.d_moduleName;
   d_recordID = right.d_recordID;
   d_baseScale = right.d_baseScale;
   d_smallScaleMin = right.d_smallScaleMin;
   d_largeScaleMax = right.d_largeScaleMax;
   d_colorIndex = right.d_colorIndex;
   d_charHeight = right.d_charHeight;
   d_fontIndex = right.d_fontIndex;
   d_textPath = right.d_textPath;
   d_horizTextAlign = right.d_horizTextAlign;
   d_vertTextAlign = right.d_vertTextAlign;
   d_charExpanFact = right.d_charExpanFact;
   d_charSpacing = right.d_charSpacing;
   d_skewAngle = right.d_skewAngle;
 
   return *this;
}   

sb_TextRep::sb_TextRep(sc_Record& recprox)
{
   // Build an sb_TextRep from an sc_Record

   // Make sure we have a record from a Text Representation module.

   sc_FieldCntr::const_iterator curfield;
   if (!sb_Utils::getFieldByMnem(recprox,"TEXT",curfield))
      {
         cerr << "sb_TextRep::sb_TextRep(sc_Record&): "
              << "Not a Text Representation record.";
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

   // CHHT
   if (sb_Utils::getSubfieldByMnem(*curfield,"CHHT",cursubfield))
      cursubfield->getR(d_charHeight);

   // FTDX
   if (sb_Utils::getSubfieldByMnem(*curfield,"FTDX",cursubfield))
      cursubfield->getI(d_fontIndex);

   // TPTH
   if (sb_Utils::getSubfieldByMnem(*curfield,"TPTH",cursubfield))
      cursubfield->getA(d_textPath);

   // UTXA
   if (sb_Utils::getSubfieldByMnem(*curfield,"UTXA",cursubfield))
      cursubfield->getA(d_horizTextAlign);

   // VTXA
   if (sb_Utils::getSubfieldByMnem(*curfield,"VTXA",cursubfield))
      cursubfield->getA(d_vertTextAlign);

   // CHEX
   if (sb_Utils::getSubfieldByMnem(*curfield,"CHEX",cursubfield))
      cursubfield->getR(d_charExpanFact);

   // CHSP
   if (sb_Utils::getSubfieldByMnem(*curfield,"CHSP",cursubfield))
      cursubfield->getR(d_charSpacing);

   // SANG
   if (sb_Utils::getSubfieldByMnem(*curfield,"SANG",cursubfield))
      cursubfield->getR(d_skewAngle);

}
