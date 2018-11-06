#ifndef INCLUDED_SB_RASTERLAYER_HXX
#define INCLUDED_SB_RASTERLAYER_HXX

// Note:  This class has been compiled, but has NOT been tested due to
//        the lack of data using the RasterLayer module.
#include <string>

#ifdef _MSC_VER
   #include <vector>
   using namespace std;
#else
   #include <vector.h>
#endif


#ifndef INCLUDED_SB_FOREIGNID_HXX
#include "builder/sb_ForeignID.hxx"
#endif

#ifndef INCLUDED_SC_FIELD_H
#include "container/sc_Field.h"
#endif

class sb_RasterLayer
{
 
   public:
     sb_RasterLayer();
     explicit sb_RasterLayer(sb_RasterLayer const& right);
     explicit sb_RasterLayer(sc_Field const& rlfield);
     sb_RasterLayer const& operator=(sb_RasterLayer const& right);
     bool operator==(sb_RasterLayer const& right) const;
     bool operator<(sb_RasterLayer const& right) const;

     // Accessors
     string const& getLayerName() const;
     string const& getCellCode() const;
     string const& getFormat() const;
     string const& getBitmask() const;
     long getNumberRows() const;
     long getNumberColumns() const;
     string const& getMinValue() const;
     string const& getMaxValue() const;
     long getScanOriginRow() const;
     long getScanOriginColumn() const;
     long getRowOffsetOrigin() const;
     long getColumnOffsetOrigin() const;
     string const& getIntracellReferenceLocation() const;
     string const& getComment() const;
     
   private:
     // Field Name Layer Definition
     string d_layerName;
     string d_cellCode;
     string d_format;
     string d_bitmask;
     long d_numberRows;
     long d_numberCols;
     // [A|I|R|S|B|C] d_minimumValue;
     // [A|I|R|S|B|C] d_maximumValue;
     string  d_minimumValue;
     string  d_maximumValue;
     
     // Next group of subfields has info about the scan ref system origin for
     // the layer
     long d_scanOriginRow;
     long d_scanOriginCol;
     long d_rowOffsetOrigin;
     long d_colOffsetOrigin;
     string d_intracellRefLocation;
     string d_comment;

};

//XXX  need to impliment the operators == and < for sb_RasterLayer
inline
bool
sb_RasterLayer::operator==(sb_RasterLayer const& right) const
{
   return d_layerName == right.d_layerName &&
          d_cellCode == right.d_cellCode &&
          d_format == right.d_format &&
          d_bitmask == right.d_bitmask &&
          d_numberRows == right.d_numberRows &&
          d_numberCols == right.d_numberCols &&
          d_minimumValue == right.d_minimumValue &&
          d_maximumValue == right.d_maximumValue &&
          d_scanOriginRow == right.d_scanOriginRow &&
          d_scanOriginCol == right.d_scanOriginCol &&
          d_rowOffsetOrigin == right.d_rowOffsetOrigin &&
          d_colOffsetOrigin  == right.d_colOffsetOrigin &&
          d_intracellRefLocation == right.d_intracellRefLocation &&
	  d_comment == right.d_comment;
}

inline
bool
sb_RasterLayer::operator<(sb_RasterLayer const& right) const
{
   return false;
}

inline
string const& 
sb_RasterLayer::getLayerName() const
{
   return d_layerName;
}
inline
string const& 
sb_RasterLayer::getCellCode() const
{
   return d_cellCode;
}
     
inline
string const& 
sb_RasterLayer::getFormat() const
{
   return d_format;
}
     
     
inline
string const& 
sb_RasterLayer::getBitmask() const
{
   return d_bitmask;
}
    
     
inline
long 
sb_RasterLayer::getNumberRows() const
{
   return d_numberRows;
}
     
     
inline
long 
sb_RasterLayer::getNumberColumns() const
{
   return d_numberCols;
}
     
     
inline
string const& 
sb_RasterLayer::getMinValue() const
{
   return d_minimumValue;
}
     
     
inline
string const& 
sb_RasterLayer::getMaxValue() const
{
   return d_maximumValue;
}
    
     
inline
long 
sb_RasterLayer::getScanOriginRow() const
{
   return d_scanOriginRow;
}
     
     
inline
long 
sb_RasterLayer::getScanOriginColumn() const
{
   return d_scanOriginCol;
}
     
     
inline
long 
sb_RasterLayer::getRowOffsetOrigin() const
{
   return d_rowOffsetOrigin;
}
     
inline
long 
sb_RasterLayer::getColumnOffsetOrigin() const
{
   return d_colOffsetOrigin;
}
     
inline
string const& 
sb_RasterLayer::getIntracellReferenceLocation() const
{
   return d_intracellRefLocation;
}
     
inline
string const& 
sb_RasterLayer::getComment() const
{
   return d_comment;
}
/*
inline

sb_RasterLayer::
{
   return d_;
}
*/ 
#endif // INCLUDED_SB_RASTERLAYER_HXX
