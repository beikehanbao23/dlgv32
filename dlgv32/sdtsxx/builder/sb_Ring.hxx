#ifndef INCLUDED_SB_RING_HXX
#define INCLUDED_SB_RING_HXX

// $Id: sb_Ring.hxx,v 1.1 1998/09/14 15:04:32 bmaddox Exp bmaddox $
// Note:  This class has been compiled, but has NOT been tested due to
//        the lack of data using the Ring module.

#include <string>

#ifdef _WIN32
   #include <vector>
#else
   #include <vector.h>
#endif

#ifndef INCLUDED_SB_FOREIGNID_HXX
#include "builder/sb_ForeignID.hxx"
#endif

#ifndef INCLUDED_SC_RECORD_H
#include "container/sc_Record.h"
#endif

class sb_Ring
{
   public:

     sb_Ring();
     sb_Ring(sb_Ring const& right);
     sb_Ring const& operator=(sb_Ring const& right);
     explicit sb_Ring(sc_Record& recprox);

     // Accessors
     string const& getModuleName() const;
     long getRecordID() const;
     string const& getObjectRep() const;
    
     vector<sb_ForeignID> const& getLineOrArcForeignID() const;
     vector<sb_ForeignID> const& getPolygonID()const;
     
   private:

     string d_moduleName;
     long d_recordID;
     string d_objectRep;
     vector<sb_ForeignID> d_lineOrArcForeignID;
     vector<sb_ForeignID> d_polygonID;
};

inline
string const&
sb_Ring::getModuleName() const
{
   return d_moduleName;
}


inline
long
sb_Ring::getRecordID() const
{
   return d_recordID;
}

inline
string const&
sb_Ring::getObjectRep() const
{
   return d_objectRep;
}

inline
vector<sb_ForeignID> const&
sb_Ring::getLineOrArcForeignID() const
{
   return d_lineOrArcForeignID;
}

inline
vector<sb_ForeignID> const&
sb_Ring::getPolygonID() const
{
   return d_polygonID;
}

#endif // INCLUDED_SB_RING_HXX

