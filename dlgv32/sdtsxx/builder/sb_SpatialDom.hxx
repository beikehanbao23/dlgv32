#ifndef INCLUDED_SB_SPATIALDOM_HXX
#define INCLUDED_SB_SPATIALDOM_HXX

// $Id: sb_SpatialDom.hxx,v 1.1 1998/09/14 15:04:34 bmaddox Exp bmaddox $
// Note:  This class has been compiled, but has NOT been tested due to
//        the lack of data using the Spatial Domain module.


#include <string>

#ifdef _WIN32
#include <vector>
#else
#include <vector.h>
#endif

#ifndef INCLUDED_SB_FOREIGNID_HXX
#include "builder/sb_ForeignID.hxx"
#endif

#ifndef INCLUDED_SB_SPATIALADDR_HXX
#include "builder/sb_SpatialAddr.hxx"
#endif

#ifndef INCLUDED_SC_RECORD_H
#include "container/sc_Record.h"
#endif

class sb_SpatialDom
{
   public:
     
     sb_SpatialDom();
     sb_SpatialDom(sb_SpatialDom const& right);
     explicit sb_SpatialDom(sc_Record& recprox);
     sb_SpatialDom const& operator=(sb_SpatialDom const& right);

     // Accessors
     string const& getModuleName() const;
     long getRecordID() const;
     string const& getSpatialDomType() const;
     string const& getDomSpatialAddType() const;
     string const& getComment() const;

     vector<sb_SpatialAddr> const& getDomSpatialAddrs() const;


   private:
   
     string d_moduleName;
     long d_recordID;
     string d_spatialDomType;
     string d_domSpatialAddType;
     string d_comment;

     vector<sb_SpatialAddr> d_domSpatialAddrs;
};

inline
string const&
sb_SpatialDom::getModuleName() const
{
   return d_moduleName;
}

inline
long
sb_SpatialDom::getRecordID() const
{
   return d_recordID;
}

inline
string const&
sb_SpatialDom::getSpatialDomType() const
{
   return d_spatialDomType;
}

inline
string const&
sb_SpatialDom::getDomSpatialAddType() const
{
   return d_domSpatialAddType;
}

inline
string const& 
sb_SpatialDom::getComment() const
{
   return d_comment;
}

inline
vector<sb_SpatialAddr> const&
sb_SpatialDom::getDomSpatialAddrs() const
{
   return d_domSpatialAddrs;
}

#endif // INCLUDED_SB_SPATIALDOM_HXX

