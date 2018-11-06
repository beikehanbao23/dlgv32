#ifndef INCLUDED_SB_TEXTREP_HXX
#define INCLUDED_SB_TEXTREP_HXX

// $Id: sb_TextRep.hxx,v 1.1 1998/09/14 15:04:35 bmaddox Exp bmaddox $
// Note:  This class has been compiled, but has NOT been tested due to
//        the lack of data using the Text Representation module.

#include <string>

#ifndef INCLUDED_SB_FOREIGNID_HXX
#include "builder/sb_ForeignID.hxx"
#endif

#ifndef INCLUDED_SC_RECORD_H
#include "container/sc_Record.h"
#endif

class sb_TextRep
{
   public: 
     sb_TextRep();
     sb_TextRep(sb_TextRep const& right);
     sb_TextRep const& operator=(sb_TextRep const& right);
     sb_TextRep(sc_Record& recprox);

     // Accessors

     string const& getModuleName() const;
     long getRecordID() const;
     long getBaseScale() const;
     long getSmallScaleMin() const;
     long getLargeScaleMax() const;
     long getColorIndex() const;
     double getCharHeight() const;
     long getFontIndex() const;
     string const& getTextPath() const;
     string const& getHorizTextAlign() const;
     string const& getVertTextAlign() const;
     double getCharExpanFact() const;
     double getCharSpacing() const;
     double getSkewAngle() const; 

   private:
     string d_moduleName;
     long d_recordID;
     long d_baseScale;
     long d_smallScaleMin;
     long d_largeScaleMax;
     long d_colorIndex;
     double d_charHeight;
     long d_fontIndex;
     string d_textPath;
     string d_horizTextAlign;
     string d_vertTextAlign;
     double d_charExpanFact;
     double d_charSpacing;
     double d_skewAngle; 
};
inline
string const&
sb_TextRep::getModuleName() const
{
   return d_moduleName;
}

inline
long
sb_TextRep::getRecordID() const
{
   return d_recordID;
}

inline
long
sb_TextRep::getBaseScale() const
{
   return d_baseScale;
}

inline
long
sb_TextRep::getSmallScaleMin() const
{
   return d_smallScaleMin;
}

inline
long
sb_TextRep::getLargeScaleMax() const
{
   return d_largeScaleMax;
}

inline
long
sb_TextRep::getColorIndex() const
{
   return d_colorIndex;
}

inline
double
sb_TextRep::getCharHeight() const
{
   return d_charHeight;
}


inline
long
sb_TextRep::getFontIndex() const
{
   return d_fontIndex;
}

inline
string const& 
sb_TextRep::getTextPath() const
{
   return d_textPath;
}

inline
string const&
sb_TextRep::getHorizTextAlign() const
{
   return d_horizTextAlign;
}

inline
string const&
sb_TextRep::getVertTextAlign() const
{
   return d_vertTextAlign;
}

inline
double
sb_TextRep::getCharExpanFact() const
{
   return d_charExpanFact;
}


inline
double
sb_TextRep::getCharSpacing() const
{
   return d_charSpacing;
}

inline
double
sb_TextRep::getSkewAngle() const
{
   return d_skewAngle;
}

#endif // INCLUDED_SB_TEXTREP_HXX
