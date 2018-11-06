#ifndef INCLUDED_SB_FONTINDEX_HXX
#define INCLUDED_SB_FONTINDEX_HXX

// $Id: sb_FontIndex.hxx,v 1.1 1998/09/14 15:04:23 bmaddox Exp bmaddox $
// Note:  This class has been compiled, but has NOT been tested due to
//        the lack of data using the Font Index module.

#include <string>

#ifndef INCLUDED_SB_FOREIGNID_HXX
#include "builder/sb_ForeignID.hxx"
#endif

#ifndef INCLUDED_SC_RECORD_H
#include "container/sc_Record.h"
#endif

class sb_FontIndex
{
   public:

     sb_FontIndex();
     sb_FontIndex(sb_FontIndex const& right);
     sb_FontIndex const& operator=(sb_FontIndex const& right);
     explicit sb_FontIndex(sc_Record& recprox);

     // Accessors
     string const& getModuleName() const;
     long getRecordID() const;
     // XXX the following return type might not be correct for getFont()
     long getFont() const;     
   private:
     
     string d_moduleName;
     long d_recordID;

     // XXX Not sure which type this subfield should be. It could be I or A,
     // depending upon what the Data/Dictionary/Domain module says?
     // Probably should be both.
     long d_font;  // string d_font?     
     
};

inline
string const&
sb_FontIndex::getModuleName() const
{
   return d_moduleName;
}

inline
long
sb_FontIndex::getRecordID() const
{
   return d_recordID;
}

inline
long
sb_FontIndex::getFont() const
{
   return d_font;
}

#endif // INCLUDED_SB_FONTINDEX_HXX
