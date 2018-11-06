#ifndef INCLUDED_SB_COLORINDEX_HXX
#define INCLUDED_SB_COLORINDEX_HXX

// $Id: sb_ColorIndex.hxx,v 1.1 1998/09/14 15:04:17 bmaddox Exp bmaddox $
// Note:  This class has been compiled, but has NOT been tested due to
//        the lack of data using the Color Index module.

#include <string>

#ifndef INCLUDED_SB_FOREIGNID_HXX
#include "builder/sb_ForeignID.hxx"
#endif

#ifndef INCLUDED_SC_RECORD_H
#include "container/sc_Record.h"
#endif

class sb_ColorIndex
{
   public:

     sb_ColorIndex();
     sb_ColorIndex(sb_ColorIndex const& right);
     sb_ColorIndex const& operator=(sb_ColorIndex const& right);
     explicit sb_ColorIndex(sc_Record& recprox);

     // Accessors
     string const& getModuleName() const;
     long getRecordID() const;
     double getRedComp() const;
     double getGreenComp() const;
     double getBlueComp() const;
     double getBlackIntensityComp() const;

   private:

     string d_moduleName;
     long d_recordID;
     double d_redComp;
     double d_greenComp;
     double d_blueComp;
     double d_blackIntensityComp;
};

inline
string const&
sb_ColorIndex::getModuleName() const
{
   return d_moduleName;
}

inline
long 
sb_ColorIndex::getRecordID() const
{
   return d_recordID;
}

inline
double
sb_ColorIndex::getRedComp() const
{
   return d_redComp;
}

inline
double
sb_ColorIndex::getGreenComp() const
{
   return d_greenComp;
}

inline
double
sb_ColorIndex::getBlueComp() const
{
   return d_blueComp;
}

inline
double
sb_ColorIndex::getBlackIntensityComp() const
{
   return d_blackIntensityComp;
}  

#endif // INCLUDED_SB_COLORINDEX_HXX
