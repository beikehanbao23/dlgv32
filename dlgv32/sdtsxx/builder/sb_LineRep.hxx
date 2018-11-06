#ifndef INCLUDED_SB_LINEREP_HXX
#define INCLUDED_SB_LINEREP_HXX

// $Id: sb_LineRep.hxx,v 1.1 1998/09/14 15:04:27 bmaddox Exp bmaddox $
// Note:  This class has been compiled, but has NOT been tested due to
//        the lack of data using the Line Representation module.

#include <string>

#ifndef INCLUDED_SB_FOREIGNID_HXX
#include "builder/sb_ForeignID.hxx"
#endif

#ifndef INCLUDED_SC_RECORD_H
#include "container/sc_Record.h"
#endif


class sb_LineRep
{
   public:
     sb_LineRep();
     sb_LineRep(sb_LineRep const& right);
     sb_LineRep const& operator=(sb_LineRep const& right);
     sb_LineRep(sc_Record& recprox);

     // Accessors 
     string const& getModuleName() const;
     long getRecordID() const;
     long getBaseScale() const;
     long getSmallScaleMin() const;
     long getLargeScaleMax() const;
     long getColorIndex() const;
     long getLineType() const;
     double getLineWidth() const;

   private:
     string d_moduleName;
     long d_recordID;
     long d_baseScale;
     long d_smallScaleMin;
     long d_largeScaleMax;
     long d_colorIndex;
     long d_lineType;
     double d_lineWidth;
};

inline
string const&
sb_LineRep::getModuleName() const
{
   return d_moduleName;
}

inline
long
sb_LineRep::getRecordID() const
{
   return d_recordID;
}

inline
long
sb_LineRep::getBaseScale() const
{
   return d_baseScale;
}

inline
long
sb_LineRep::getSmallScaleMin() const
{
   return d_smallScaleMin;
}

inline
long
sb_LineRep::getLargeScaleMax() const
{
   return d_largeScaleMax;
}

inline
long
sb_LineRep::getColorIndex() const
{
   return d_colorIndex;
}

inline
long
sb_LineRep::getLineType() const
{
   return d_lineType;
}

inline
double
sb_LineRep::getLineWidth() const
{
   return d_lineWidth;
}


  
#endif // INCLUDED_SB_LINEREP_HXX
