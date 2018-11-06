#ifndef INCLUDED_SB_SYMBOL_HXX
#define INCLUDED_SB_SYMBOL_HXX

// $Id: sb_SymbolRep.hxx,v 1.1 1998/09/14 15:04:34 bmaddox Exp bmaddox $
// Note:  This class has been compiled, but has NOT been tested due to
//        the lack of data using the Symbol Representation module.

#include <string>

#ifndef INCLUDED_SB_FOREIGNID_HXX
#include "builder/sb_ForeignID.hxx"
#endif

#ifndef INCLUDED_SC_RECORD_H
#include "container/sc_Record.h"
#endif

class sb_SymbolRep
{
   public:
     
     sb_SymbolRep();
     sb_SymbolRep(sb_SymbolRep const& right);
     sb_SymbolRep const& operator=(sb_SymbolRep const& right);
     explicit sb_SymbolRep(sc_Record& recprox);

     // Accessors
     string const& getModuleName() const;
     long getRecordID() const;
     long getBaseScale() const;
     long getSmallScaleMin() const;
     long getLargeScaleMax() const;
     long getColorIndex() const;
     long getSymMarkerType() const;
     double getMarkerSize() const;

   private:
    
     string d_moduleName;
     long d_recordID;
     long d_baseScale;
     long d_smallScaleMin;
     long d_largeScaleMax;
     long d_colorIndex;
     long d_symMarkerType;
     double d_markerSize;

};

inline
string const&
sb_SymbolRep::getModuleName() const
{
   return d_moduleName;
}

inline
long 
sb_SymbolRep::getRecordID() const
{
   return d_recordID;
}

inline
long
sb_SymbolRep::getBaseScale() const
{
   return d_baseScale;
}

inline
long
sb_SymbolRep::getSmallScaleMin() const
{
   return d_smallScaleMin;
}

inline
long
sb_SymbolRep::getLargeScaleMax() const
{   
   return d_largeScaleMax;
}

inline
long
sb_SymbolRep::getColorIndex() const
{
   return d_colorIndex;
}

inline
long
sb_SymbolRep::getSymMarkerType() const
{
   return d_symMarkerType;
}

inline
double
sb_SymbolRep::getMarkerSize() const
{
   return d_markerSize;
}

#endif // INCLUDED_SB_SYMBOLREP_HXX
