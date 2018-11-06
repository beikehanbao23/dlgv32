// $Id: sb_IntSpatialRef.cxx,v 1.1 1998/09/14 15:04:25 bmaddox Exp bmaddox $

#ifdef _WIN32
   #include <iostream>
#else
   #include <iostream.h>
#endif

#ifndef INCLUDED_SB_UTILS_HXX
#include "builder/sb_Utils.hxx"
#endif

#ifndef INCLUDED_SB_INTSPATIALREF_HXX
#include "builder/sb_IntSpatialRef.hxx"
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

sb_IntSpatialRef::sb_IntSpatialRef()
               : d_recordID(0),
                 d_scaleFactX(0),
                 d_scaleFactY(0),
                 d_scaleFactZ(0),
                 d_xOrigin(0),
                 d_yOrigin(0),
                 d_zOrigin(0),
                 d_xCompHorizRes(0),
                 d_yCompHorizRes(0),
                 d_verticalResComp(0)
{
}

sb_IntSpatialRef::sb_IntSpatialRef(sb_IntSpatialRef const& right)
{
   operator=(right);
}

sb_IntSpatialRef const&
sb_IntSpatialRef::operator=(sb_IntSpatialRef const& right)
{
    if(this==&right)
      return *this;

    d_moduleName = right.d_moduleName;
    d_recordID = right.d_recordID;
    d_comment = right.d_comment;

    d_spatialAddType = right.d_spatialAddType;
    d_spatialAddXCompLbl = right.d_spatialAddXCompLbl;
    d_spatialAddYCompLbl = right.d_spatialAddYCompLbl;
    d_horizontalCompFmt = right.d_horizontalCompFmt;
    d_verticalCompFmt = right.d_verticalCompFmt;

    d_scaleFactX = right.d_scaleFactX;
    d_scaleFactY = right.d_scaleFactY;
    d_scaleFactZ = right.d_scaleFactZ;
    d_xOrigin = right.d_xOrigin;
    d_yOrigin = right.d_yOrigin;
    d_zOrigin = right.d_zOrigin;

    d_xCompHorizRes = right.d_xCompHorizRes;
    d_yCompHorizRes = right.d_yCompHorizRes;
    d_verticalResComp = right.d_verticalResComp;

    d_dimensionID = right.d_dimensionID;

    return *this;
}

sb_IntSpatialRef::sb_IntSpatialRef(sc_Record& recprox)
               : d_recordID(0),
                 d_scaleFactX(0),
                 d_scaleFactY(0),
                 d_scaleFactZ(0),
                 d_xOrigin(0),
                 d_yOrigin(0),
                 d_zOrigin(0),
                 d_xCompHorizRes(0),
                 d_yCompHorizRes(0),
                 d_verticalResComp(0)
{
   // Build an sb_IntSpatialRef from an sc_Record

   // Make sure we have a record from a Internal Spatial Reference module.

   sc_FieldCntr::const_iterator curfield;
   if (!sb_Utils::getFieldByMnem(recprox,"IREF",curfield))
      {
         cerr << "sb_IntSpatialRef::sb_IntSpatialRef(sc_Record const&): "
              << "Not an Internal Spatial Reference record.";
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

   // SATP 
   if (sb_Utils::getSubfieldByMnem(*curfield,"SATP",cursubfield))
      cursubfield->getA(d_spatialAddType);

   // XLBL
   if (sb_Utils::getSubfieldByMnem(*curfield,"XLBL",cursubfield))
      cursubfield->getA(d_spatialAddXCompLbl);

   // YLBL
   if (sb_Utils::getSubfieldByMnem(*curfield,"YLBL",cursubfield))
      cursubfield->getA(d_spatialAddYCompLbl);

   // HFMT
   if (sb_Utils::getSubfieldByMnem(*curfield,"HFMT",cursubfield))
      cursubfield->getA(d_horizontalCompFmt);

   // VFMT
   if (sb_Utils::getSubfieldByMnem(*curfield,"VFMT",cursubfield))
      cursubfield->getA(d_verticalCompFmt);

   // SFAX
   if (sb_Utils::getSubfieldByMnem(*curfield,"SFAX",cursubfield))
      cursubfield->getR(d_scaleFactX);

   // SFAY
   if (sb_Utils::getSubfieldByMnem(*curfield,"SFAY",cursubfield))
      cursubfield->getR(d_scaleFactY);

   // SFAZ
   if (sb_Utils::getSubfieldByMnem(*curfield,"SFAZ",cursubfield))
      cursubfield->getR(d_scaleFactZ);
 
   // XORG
   if (sb_Utils::getSubfieldByMnem(*curfield,"XORG",cursubfield))
      cursubfield->getR(d_xOrigin);

   // YORG
   if (sb_Utils::getSubfieldByMnem(*curfield,"YORG",cursubfield))
      cursubfield->getR(d_yOrigin);

   // ZORG
   if (sb_Utils::getSubfieldByMnem(*curfield,"ZORG",cursubfield))
      {
//         cout << d_zOrigin << endl;
         cursubfield->getR(d_zOrigin);
//         cout << d_zOrigin << endl;
      }

   // XHRS
   if (sb_Utils::getSubfieldByMnem(*curfield,"XHRS",cursubfield))
      sb_Utils::getDoubleFromSubfield( cursubfield, d_xCompHorizRes);
     
   // YHRS
   if (sb_Utils::getSubfieldByMnem(*curfield,"YHRS",cursubfield))
      sb_Utils::getDoubleFromSubfield( cursubfield,d_yCompHorizRes);
	 
   // VRES
   if (sb_Utils::getSubfieldByMnem(*curfield,"VRES",cursubfield))
      sb_Utils::getDoubleFromSubfield( cursubfield, d_verticalResComp);
 


// Secondary Fields

   // Dimension ID (DMID) Field
   //if (sb_Utils::getFieldByMnem(recprox,"DMID",curfield))
   //   d_dimensionID = sb_ForeignID(*curfield);

   sc_FieldCntr const& fields = recprox; 
   for (curfield = fields.begin();
        curfield != fields.end();
        curfield++)
      {
         if (curfield->getMnemonic() == "DMID")
			 d_dimensionID.push_back(sb_ForeignID(*curfield) );
      }


}
