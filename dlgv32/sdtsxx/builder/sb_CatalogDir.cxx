// $Id: sb_CatalogDir.cxx,v 1.1 1998/09/14 15:04:14 bmaddox Exp bmaddox $ 


#include <iostream.h>

#ifndef INCLUDED_SB_UTILS_HXX
#include "builder/sb_Utils.hxx"
#endif

#ifndef INCLUDED_SB_CATALOGDIR_HXX
#include "builder/sb_CatalogDir.hxx"
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

sb_CatalogDir::sb_CatalogDir()
            : d_recordID(0)
{
}

sb_CatalogDir::sb_CatalogDir(sb_CatalogDir const& right)
{
   operator=(right);
}

sb_CatalogDir const&
sb_CatalogDir::operator=(sb_CatalogDir const& right)
{
    if(this==&right)         // deals with the s=s case
      return *this;
    d_moduleName = right.d_moduleName;
    d_recordID = right.d_recordID;
    d_name = right.d_name;
    d_type = right.d_type;
    d_volume = right.d_volume;
    d_file = right.d_file;
    d_record = right.d_record;
    d_external = right.d_external;
    d_moduleVer = right.d_moduleVer;
    d_comment = right.d_comment;
    return *this;
}

sb_CatalogDir::sb_CatalogDir(sc_Record& recprox)
{
   // Build an sb_CatalogDir from an sc_Record
   
   // Make sure we have a record from a Catalog/Directory module.  

   sc_FieldCntr::const_iterator curfield;
   if (!sb_Utils::getFieldByMnem(recprox,"CATD",curfield))
      {
         cerr << "sb_CatalogDir::sb_CatalogDir(sc_Record const&): "
              << "Not a Catalog/Directory record.\n";
         return;
      }

   // We have a primary field from a Catalog/Directory module. Start 
   // picking it apart.
   
   sc_SubfieldCntr::const_iterator cursubfield;
  
   // MODN
   if (sb_Utils::getSubfieldByMnem(*curfield,"MODN",cursubfield))
      cursubfield->getA(d_moduleName);


   // RCID
   if (sb_Utils::getSubfieldByMnem(*curfield,"RCID",cursubfield))
      cursubfield->getI(d_recordID);


   // NAME
   if (sb_Utils::getSubfieldByMnem(*curfield,"NAME",cursubfield))
      cursubfield->getA(d_name);

   // TYPE
   if (sb_Utils::getSubfieldByMnem(*curfield,"TYPE",cursubfield))
      cursubfield->getA(d_type);


   // VOLM
   if (sb_Utils::getSubfieldByMnem(*curfield,"VOLM",cursubfield))
      cursubfield->getA(d_volume);

   // FILE
   if (sb_Utils::getSubfieldByMnem(*curfield,"FILE",cursubfield))
      cursubfield->getA(d_file);

   // RECD
   if (sb_Utils::getSubfieldByMnem(*curfield,"RECD",cursubfield))
//ccc  hmm not sure of which get I | A is in the spec
      cursubfield->getA(d_record);

   // EXTR
   if (sb_Utils::getSubfieldByMnem(*curfield,"EXTR",cursubfield))
      cursubfield->getA(d_external);

   // MVER
   if (sb_Utils::getSubfieldByMnem(*curfield,"MVER",cursubfield))
      cursubfield->getA(d_moduleVer);

   // COMT
   if (sb_Utils::getSubfieldByMnem(*curfield,"COMT",cursubfield))
      cursubfield->getA(d_comment);

}
