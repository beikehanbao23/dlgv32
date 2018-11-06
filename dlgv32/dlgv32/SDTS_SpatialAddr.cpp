
// $Id: SDTS_SpatialAddr.cpp,v 1.1 1998/09/14 15:02:46 bmaddox Exp bmaddox $
#include "SDTS_SpatialAddr.h"
#include "SDTS_Utils.h"
#include "sdtsxx/container/sc_Subfield.h"
#include "sdtsxx/builder/sb_Utils.hxx"

SDTS_SpatialAddr::SDTS_SpatialAddr()
: d_x(0.0), d_y(0.0)
{
}

SDTS_SpatialAddr::SDTS_SpatialAddr( const sc_Field& sadrField)
: d_x(0.0), d_y(0.0)
{
    // sadrField should be a Spatial Address field.

    sc_SubfieldCntr::const_iterator cursubfield;

    /*
     *  Use sb_Utils::getDoubleFromSubfield to try real hard
	 *  to convert any data in the passed in subfield into
	 *  a double value.
	 */
    // X
    if ( SDTS_Utils::getSubfieldByMnem( sadrField, "X", cursubfield ) )
    {
        sb_Utils::getDoubleFromSubfield( cursubfield, d_x );
    }
   
    // Y
    if ( SDTS_Utils::getSubfieldByMnem( sadrField, "Y", cursubfield ) )
    {
        sb_Utils::getDoubleFromSubfield( cursubfield, d_y );
    }
}
