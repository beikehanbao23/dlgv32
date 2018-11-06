#ifndef INCLUDED_SB_CELL_HXX
#define INCLUDED_SB_CELL_HXX

// $Id: sb_Cell.hxx,v 1.1 1998/09/14 15:04:17 bmaddox Exp bmaddox $
// Note:  This class has been compiled, but has NOT been tested due to
//        the lack of data using the Cell module.

#ifdef _WIN32
   #include <vector>
#else
   #include <vector.h>
#endif

#include <string>

#ifndef INCLUDED_SB_FOREIGNID_HXX
#include "builder/sb_ForeignID.hxx"
#endif

#ifndef INCLUDED_SB_SPATIALADDR_HXX
#include "builder/sb_SpatialAddr.hxx"
#endif

#ifndef INCLUDED_SC_RECORD_H
#include "container/sc_Record.h"
#endif

class sb_Cell
{
   public:
      sb_Cell();
      sb_Cell(sb_Cell const& right);
      sb_Cell const& operator=(sb_Cell const& right);
      sb_Cell(sc_Record& recprox);

      // Accessors

      string const& getModuleName() const;
      long getRecordID() const;
      long getNumCells() const;
      long getRowIndex() const;
      long getColumnIndex() const;
      long getTesseralIndex() const;
    
      sb_SpatialAddr const& getSpatialAddr() const;
      vector<sb_ForeignID> const& getAttributeID() const;

//      vector<sc_Subfield> const& getCellValues() const;
         // Returns a list of the cell values in the record.
         // XXX This is likely to change. There is some nastiness in the 
         // SDTS about how CVAL subfields can repeat within CVLS repeating fields.

   private:
    
     string d_moduleName;
     long d_recordID;
     long d_numCells;
     long d_rowIndex;
     long d_columnIndex;
     long d_tesseralIndex;

     sb_SpatialAddr d_spatialAddr;
     vector<sb_ForeignID> d_attributeID;
  //   vector<sc_Subfield> d_cellValues;
};

inline
string const&
sb_Cell::getModuleName() const
{
   return d_moduleName;
}
   
inline
long
sb_Cell::getRecordID() const
{
   return d_recordID;
}


inline
long
sb_Cell::getNumCells() const
{
   return d_numCells;
}
 
inline
long
sb_Cell::getRowIndex() const
{
   return d_rowIndex;
}

inline
long
sb_Cell::getColumnIndex() const
{
   return d_columnIndex;
}

inline
long
sb_Cell::getTesseralIndex() const
{
   return d_tesseralIndex;
}

inline
sb_SpatialAddr const&
sb_Cell::getSpatialAddr() const
{
   return d_spatialAddr;
}

inline
vector<sb_ForeignID> const&
sb_Cell::getAttributeID() const
{
   return d_attributeID;
}
/*
vector<sc_Subfield> const&
sb_Cell::getCellValues() const
{
   return d_cellValues;
}
*/
#endif // INCLUDED_SB_CELL_HXX
