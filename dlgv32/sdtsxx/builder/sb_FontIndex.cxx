// $Id: sb_FontIndex.cxx,v 1.1 1998/09/14 15:04:23 bmaddox Exp bmaddox $

#ifdef _WIN32
   #include <iostream>
#else
   #include <iostream.h>
#endif

#ifndef INCLUDED_SB_UTILS_HXX
#include "builder/sb_Utils.hxx"
#endif

#ifndef INCLUDED_SB_FONTINDEX_HXX
#include "builder/sb_FontIndex.hxx" 
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

sb_FontIndex::sb_FontIndex()
           : d_recordID(0),
             d_font(0)
{
}


sb_FontIndex::sb_FontIndex(sb_FontIndex const& right)
{
   operator=(right);
}

sb_FontIndex const&
sb_FontIndex::operator=(sb_FontIndex const& right)
{
   if (this == &right)
     return *this;

   d_moduleName = right.d_moduleName;
   d_recordID = right.d_recordID;
   d_font = right.d_font;

   return *this;
}

sb_FontIndex::sb_FontIndex(sc_Record& recprox)
{

   // Make sure we have a record from a Font Index module.

   sc_FieldCntr::const_iterator curfield;
   if (!sb_Utils::getFieldByMnem(recprox,"FONT",curfield))
      {
         cerr << "sb_FontIndex::sb_FontIndex(sc_Record&): "
              << "Not a Font Index record.";
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

   // FNTN
   if (sb_Utils::getSubfieldByMnem(*curfield,"FNTN",cursubfield))
      cursubfield->getI(d_font);
//ccc in spec calls for I|A linked to dict/domain module


}
