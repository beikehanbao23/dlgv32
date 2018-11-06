#ifndef INCLUDED_SB_AREAFILLREP_HXX
#define INCLUDED_SB_AREAFILLREP_HXX

// $Id: sb_AreaFillRep.hxx,v 1.1 1998/09/14 15:04:13 bmaddox Exp bmaddox $
// Note:  This class has been compiled, but has NOT been tested due to
//        the lack of data using the Area Fill Representation module.

#include <string>

#ifndef INCLUDED_SB_FOREIGNID_HXX
#include "builder/sb_ForeignID.hxx"
#endif

#ifndef INCLUDED_SC_RECORD_H
#include "container/sc_Record.h"
#endif

class sb_AreaFillRep
{
   public:

     sb_AreaFillRep();
     sb_AreaFillRep(sb_AreaFillRep const& right);
     sb_AreaFillRep const& operator=(sb_AreaFillRep const& right);
     explicit sb_AreaFillRep(sc_Record& recprox);

     // Accessors
     string const& getModuleName() const;
     long getRecordID() const;
     long getBaseScale() const;
     long getSmallScaleMin() const;
     long getLargeScaleMax() const;
     long getColorIndex() const;
     string const& getFillStyleType() const;
     long getHatchIndex() const;
     long getPatternIndex() const;

   private:
  
     string d_moduleName;
     long d_recordID;
     long d_baseScale;
     long d_smallScaleMin;
     long d_largeScaleMax;
     long d_colorIndex;
     string d_fillStyleType;
     long d_hatchIndex;
     long d_patternIndex;
   
};

inline
string const&
sb_AreaFillRep::getModuleName() const
{   
   return d_moduleName;
}

inline
long
sb_AreaFillRep::getRecordID() const
{
   return d_recordID;
}

inline
long
sb_AreaFillRep::getBaseScale() const
{
   return d_baseScale;
}


inline
long
sb_AreaFillRep::getSmallScaleMin() const
{
   return d_smallScaleMin;
}

inline
long
sb_AreaFillRep::getLargeScaleMax() const
{
   return d_largeScaleMax;
}

inline
long
sb_AreaFillRep::getColorIndex() const
{
   return d_colorIndex;
}

inline
string const&
sb_AreaFillRep::getFillStyleType() const
{
   return d_fillStyleType;
}

inline
long
sb_AreaFillRep::getHatchIndex() const
{
   return d_hatchIndex;
}


inline
long
sb_AreaFillRep::getPatternIndex() const
{
   return d_patternIndex;
}
  
#endif // INCLUDED_SB_AREAFILLREP_HXX

