
// $Id: sb_Line.cxx,v 1.1 1998/09/14 15:04:25 bmaddox Exp bmaddox $

#ifdef _WIN32
   #include <iostream>
#else
   #include <iostream.h>
#endif

#ifndef INCLUDED_SB_UTILS_HXX
#include "builder/sb_Utils.hxx"
#endif

#ifndef INCLUDED_SB_LINE_HXX
#include "builder/sb_Line.hxx"
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

sb_Line::sb_Line()
      : d_recordID(0)
{
}

sb_Line::sb_Line(sb_Line const& right)
{
   operator=(right);
}

sb_Line const&
sb_Line::operator=(sb_Line const& right)
{
   if(this==&right)
     return *this;

   d_moduleName = right.d_moduleName;
   d_recordID = right.d_recordID;
   d_objectRep = right.d_objectRep;

   d_polyIDLeft = right.d_polyIDLeft;
   d_polyIDRight = right.d_polyIDRight;
   d_startNodeID = right.d_startNodeID;
   d_endNodeID = right.d_endNodeID;

   d_attrIDs = right.d_attrIDs;
   d_spatialAddrs = right.d_spatialAddrs;
    
   return *this;
}

sb_Line::sb_Line(sc_Record& recprox)
{
   // Build an sb_Line from an sc_Record. 

   // Make sure we have a record from a line module.

   sc_FieldCntr::const_iterator curfield;
   if (!sb_Utils::getFieldByMnem(recprox,"LINE",curfield))
      {
         cerr << "sb_Line::sb_Line(sc_Record const&): Not a LINE record.";
         cerr << endl;
         return;
      }
   
   // We have a primary field from a LINE module. Start picking it apart.

   sc_SubfieldCntr::const_iterator cursubfield;
   
   // MODN
   if (sb_Utils::getSubfieldByMnem(*curfield,"MODN",cursubfield))
      cursubfield->getA(d_moduleName);

   // RCID
   if (sb_Utils::getSubfieldByMnem(*curfield,"RCID",cursubfield))
      cursubfield->getI(d_recordID);

   // OBRP
   if (sb_Utils::getSubfieldByMnem(*curfield,"OBRP",cursubfield))
      cursubfield->getA(d_objectRep);


   // Secondary Fields

   // Polygon ID Left (PIDL) Field
   if (sb_Utils::getFieldByMnem(recprox,"PIDL",curfield))
      d_polyIDLeft = sb_ForeignID(*curfield);

   // Polygon ID Right (PIDR) Field
   if (sb_Utils::getFieldByMnem(recprox,"PIDR",curfield))
      d_polyIDRight = sb_ForeignID(*curfield);

   // Startnode ID (SNID) Field
   if (sb_Utils::getFieldByMnem(recprox,"SNID",curfield))
      d_startNodeID = sb_ForeignID(*curfield);

   // Endnode ID (ENID) Field
   if (sb_Utils::getFieldByMnem(recprox,"ENID",curfield))
      d_endNodeID = sb_ForeignID(*curfield);


   // SADR and ATID Fields.
   sc_FieldCntr const& fields = recprox; 
   for (curfield = fields.begin();
        curfield != fields.end();
        curfield++)
      {
         if (curfield->getMnemonic() == "SADR")
         {
            d_spatialAddrs.push_back( sb_SpatialAddr( *curfield ) );
         }
         else if ( curfield->getMnemonic() == "ATID" )
         {
            d_attrIDs.push_back( sb_ForeignID( *curfield ) );
         }
      }

}

