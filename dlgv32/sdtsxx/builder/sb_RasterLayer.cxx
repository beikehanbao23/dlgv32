
#ifndef INCLUDED_SB_RASTERLAYER_HXX
#include "builder/sb_RasterLayer.hxx"
#endif

#ifdef _MSC_VER
   #include <iostream>
   using namespace std;
#else
   #include <iostream.h>
#endif

#ifndef INCLUDED_SB_UTIL_HXX
#include "builder/sb_Utils.hxx"
#endif

sb_RasterLayer::sb_RasterLayer() :
          d_layerName("") ,
          d_cellCode("") ,
          d_format("") ,
          d_bitmask("") ,
          d_numberRows(0) ,
          d_numberCols(0) ,
/*          d_minimumValue() ,
          d_maximumValue() , */
          d_scanOriginRow(0) ,
          d_scanOriginCol(0) ,
          d_rowOffsetOrigin(0) ,
          d_colOffsetOrigin (0) ,
          d_intracellRefLocation("") ,
	  d_comment("")
{
}


sb_RasterLayer::sb_RasterLayer(sb_RasterLayer const& right)
{
   operator=(right);
}

sb_RasterLayer const&
sb_RasterLayer::operator=(sb_RasterLayer const& right)
{
   if (this == &right)
     return *this;
   d_layerName = right.d_layerName ;
   d_cellCode = right.d_cellCode ;
   d_format = right.d_format ;
   d_bitmask = right.d_bitmask ;
   d_numberRows = right.d_numberRows ;
   d_numberCols = right.d_numberCols ;
   d_minimumValue = right.d_minimumValue ;
   d_maximumValue = right.d_maximumValue ;
   d_scanOriginRow = right.d_scanOriginRow ;
   d_scanOriginCol = right.d_scanOriginCol ;
   d_rowOffsetOrigin = right.d_rowOffsetOrigin ;
   d_colOffsetOrigin  = right.d_colOffsetOrigin ;
   d_intracellRefLocation = right.d_intracellRefLocation ;
   d_comment = right.d_comment;

   return *this;
}

sb_RasterLayer::sb_RasterLayer(sc_Field const& rlfield)
{
   // Build an sb_RasterLayer from an sc_Field

   sc_SubfieldCntr::const_iterator cursubfield;

   // Layer name type A
   if (sb_Utils::getSubfieldByMnem(rlfield,"LNAM",cursubfield))
      cursubfield->getA(d_layerName);

   // Cell Code Type A
   if (sb_Utils::getSubfieldByMnem(rlfield,"CODE",cursubfield))
      cursubfield->getA(d_cellCode);

   // Format [M] Type A
   if (sb_Utils::getSubfieldByMnem(rlfield,"FMT",cursubfield))
      cursubfield->getA(d_format);

   // Bitmask type C
   if (sb_Utils::getSubfieldByMnem(rlfield,"BMSK",cursubfield))
      cursubfield->getC(d_bitmask);

   // Number of Rows type I
   if (sb_Utils::getSubfieldByMnem(rlfield,"NROW",cursubfield))
      cursubfield->getI(d_numberRows);

   // Number of Columns type I
   if (sb_Utils::getSubfieldByMnem(rlfield,"NCOL",cursubfield))
      cursubfield->getI(d_numberCols);

   //  Minimum Value type [A|I|R|S|B|C]
   if (sb_Utils::getSubfieldByMnem(rlfield,"MINV",cursubfield))
      cursubfield ->getA(d_minimumValue); // loadMinValue(cursubfield) ; 

   //  Maximum value type [A|I|R|S|B|C]
   if (sb_Utils::getSubfieldByMnem(rlfield,"MAXV",cursubfield))
      cursubfield ->getA(d_maximumValue); // loadMaxValue(cursubfield ); 

   //  (d)Scan Origin Row [M/default Imp=NON] type I
   if (sb_Utils::getSubfieldByMnem(rlfield,"SORI",cursubfield))
      cursubfield->getI(d_scanOriginRow);

   //(d)Scan Origin Column[m/default impl=non] type I
   if (sb_Utils::getSubfieldByMnem(rlfield,"SOCI",cursubfield))
      cursubfield->getI(d_scanOriginCol);

   //(d) Row offset origin [m/default impl=non type I
   if (sb_Utils::getSubfieldByMnem(rlfield,"RWOO",cursubfield))
      cursubfield->getI(d_rowOffsetOrigin);

   //(d)Colum Offset Origin[m/default impl=non] type I
   if (sb_Utils::getSubfieldByMnem(rlfield,"CLOO",cursubfield))
      cursubfield->getI(d_colOffsetOrigin);

   // (d) Intracell Reference Location[m/def impl=non] type A
   if (sb_Utils::getSubfieldByMnem(rlfield,"INTR",cursubfield))
      cursubfield->getA(d_intracellRefLocation);

   // Comment type A
   if (sb_Utils::getSubfieldByMnem(rlfield,"COMT",cursubfield))
      cursubfield->getA(d_comment);

/*

   // 
   if (sb_Utils::getSubfieldByMnem(rlfield,"",cursubfield))
      cursubfield->get ();

*/
/*
   // Secondary Fields

   // Spatial Address, non-repeating (SADR) Field
   if (sb_Utils::getFieldByMnem(recprox,"SADR",curfield))
      d_spatialAddr = sb_SpatialAddr(rlfield);
*/

}
/*

bool loadMinValue( sc_SubfieldCntr::const_iterator cursubfield )
{
    switch( d_format ) {

	case "A":
		cursubfield->getA(d_minimumValue);
		break;
	case "I":
		cursubfield->getI(d_minimumValue);
		break;
	case "C":
		cursubfield->getC(d_minimumValue);
		break;
	case " ":
		cursubfield->get (d_minimumValue);
		break;
	case " ":
		cursubfield->get (d_minimumValue);
		break;
	case " ":
		cursubfield->get (d_minimumValue);
		break;
	case " ":
		cursubfield->get (d_minimumValue);
		break;
	default:
		cerr << "sb_RasterLayer: loadMinValue() " << eol
		     << "Invalid information sent in subfield" <<eol;

    }
}
bool loadMaxValue( sc_SubfieldCntr::const_iterator cursubfield);
{
    switch( d_format ) {

	case "A":
		cursubfield->getA(d_maximumValue);
		break;
	case " ":
		cursubfield->get (d_maximumValue);
		break;
	default:
		cerr << "sb_RasterLayer: loadMaxValue() " << eol
		     << "Invalid information sent in subfield" <<eol;

    }
}
*/
