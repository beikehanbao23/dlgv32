// $Id: sb_Cell.cxx,v 1.1 1998/09/14 15:04:16 bmaddox Exp bmaddox $

#ifdef _WIN32
   #include <iostream>
#else
   #include <iostream.h>
#endif

#ifndef INCLUDED_SB_UTILS_HXX
#include "builder/sb_Utils.hxx"
#endif

#ifndef INCLUDED_SB_CELL_HXX
#include "builder/sb_Cell.hxx"
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

sb_Cell::sb_Cell()
      : d_recordID(0),
        d_numCells(0),
        d_rowIndex(0),
        d_columnIndex(0),
        d_tesseralIndex(0)
{
}


sb_Cell::sb_Cell(sb_Cell const& right)
{
   operator=(right);
}

sb_Cell const&
sb_Cell::operator=(sb_Cell const& right)
{
   if (this == &right)
     return *this;

   d_moduleName = right.d_moduleName;
   d_recordID = right.d_recordID;
   d_numCells = right.d_numCells;
   d_rowIndex = right.d_rowIndex;
   d_columnIndex = right.d_columnIndex;
   d_tesseralIndex = right.d_tesseralIndex;
   d_spatialAddr = right.d_spatialAddr;
   d_attributeID = right.d_attributeID;
//   d_cellValues = right.d_cellValues;

   return *this;
}

sb_Cell::sb_Cell(sc_Record& record)
{
   // Build an sb_Cell from an sc_Record

   // Make sure we have a record from a Cell module.

   sc_FieldCntr::const_iterator curFieldItr;

   if (!sb_Utils::getFieldByMnem(record,"CELL",curFieldItr))
      {
         // XXX This will almost certainly have to change. But for now,
         // XXX at least we know it didn't work. :) -- jamie
         cerr << "sb_Cell::sb_Cell(sc_Record&): "
              << "Not a Cell record.";
         cerr << endl;
         return;
      }

   // We have a primary field from a module. Start
   // picking it apart.

   sc_SubfieldCntr::const_iterator curSubfieldItr;

   // MODN
   if (sb_Utils::getSubfieldByMnem(*curFieldItr,"MODN",curSubfieldItr))
      curSubfieldItr->getA(d_moduleName);

   // RCID
   if (sb_Utils::getSubfieldByMnem(*curFieldItr,"RCID",curSubfieldItr))
      curSubfieldItr->getI(d_recordID);

   // NCEL
   if (sb_Utils::getSubfieldByMnem(*curFieldItr,"NCEL",curSubfieldItr))
      curSubfieldItr->getI(d_numCells);

   // ROWI
   if (sb_Utils::getSubfieldByMnem(*curFieldItr,"ROWI",curSubfieldItr))
      curSubfieldItr->getI(d_rowIndex);

   // COLI
   if (sb_Utils::getSubfieldByMnem(*curFieldItr,"COLI",curSubfieldItr))
      curSubfieldItr->getI(d_columnIndex);

   // TIND
   if (sb_Utils::getSubfieldByMnem(*curFieldItr,"TIND",curSubfieldItr))
      curSubfieldItr->getI(d_tesseralIndex);
//ccc The spec cals for a I|B unsigned int?

   // Secondary Fields

   // Spatial Address, non-repeating (SADR) Field
   if (sb_Utils::getFieldByMnem(record,"SADR",curFieldItr))
      d_spatialAddr = sb_SpatialAddr(*curFieldItr);

   // Attribute ID, repeating (ATID) Fields
   for (curFieldItr = record.begin();
        curFieldItr != record.end();
        curFieldItr++)
      {
         if (curFieldItr->getMnemonic() == "ATID")
            d_attributeID.push_back(sb_ForeignID(*curFieldItr));
      }

#if 0
   // Cell Values. repeating (CVLS) Fields
   for (curFieldItr = record.begin();
        curFieldItr != record.end();
        curFieldItr++)
      {
         // XXX This will most likely change. I'm _hoping_ (praying, really)
         // XXX that there's only one CVAL subfield per CVLS field. But the
         // XXX standard allows for a much more complicated relationship. -- jamie
         if (curFieldItr->getMnemonic() == "CVLS")
            {
               if (sb_Utils::getSubfieldByMnem(*curFieldItr, "CVAL", curSubfieldItr))
                  d_cellValues.push_back(*curSubfieldItr);
            }
      }
#endif
}
