
// $Id: sb_SpatialAddr.cxx,v 1.1 1998/09/14 15:04:33 bmaddox Exp bmaddox $

#ifndef INCLUDED_SB_SPATIALADDR_HXX
#include "builder/sb_SpatialAddr.hxx"
#endif

#ifndef INCLUDED_SC_SUBFIELD_H
#include "container/sc_Subfield.h"
#endif

#ifndef INCLUDED_SB_UTILS_HXX
#include "builder/sb_Utils.hxx"
#endif

sb_SpatialAddr::sb_SpatialAddr()
             : d_x(0.0), d_y(0.0), d_z(0.0)
{
}

sb_SpatialAddr::sb_SpatialAddr(sc_Field const& sadrField)
{
   // sadrField should be a Spatial Address field.

   d_x = 0.0;
   d_y = 0.0;
   d_z = 0.0;

   sc_SubfieldCntr::const_iterator cursubfield;

   /*
    *  Use sb_Utils::getDoubleFromSubfield to try real hard
	*  to convert any data in the passed in subfield into
	*  a double value.
	*/
   // X
   if (sb_Utils::getSubfieldByMnem(sadrField,"X",cursubfield))
      sb_Utils::getDoubleFromSubfield( cursubfield, d_x ); 
   
   // Y
   if (sb_Utils::getSubfieldByMnem(sadrField,"Y",cursubfield))
      sb_Utils::getDoubleFromSubfield( cursubfield, d_y );

   // Z
   if (sb_Utils::getSubfieldByMnem(sadrField,"Z",cursubfield))
      sb_Utils::getDoubleFromSubfield( cursubfield, d_z );
}

