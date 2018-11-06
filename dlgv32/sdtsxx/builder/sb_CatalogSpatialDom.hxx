#ifndef INCLUDED_SB_CATALOGSPATIALDOM_HXX
#define INCLUDED_SB_CATALOGSPATIALDOM_HXX

// $Id: sb_CatalogSpatialDom.hxx,v 1.1 1998/09/14 15:04:15 bmaddox Exp bmaddox $

#include <string>

#ifndef INCLUDED_SC_RECORD_H
#include "container/sc_Record.h"
#endif

class sb_CatalogSpatialDom
{
   public:
   
      sb_CatalogSpatialDom();
      sb_CatalogSpatialDom(sb_CatalogSpatialDom const& right);
      sb_CatalogSpatialDom const& operator=(sb_CatalogSpatialDom const& right);
      explicit sb_CatalogSpatialDom(sc_Record& recprox);
         // recprox must be from a Catalog/Spatial Domain module, or this 
         // won't work.  recprox can't be const because we use its -> operator.

      string const& getModuleName() const; 
      long getRecordID() const;
      string const& getName() const;
      string const& getType() const;
      string const& getDomain() const;
      string const& getMap() const;
      string const& getTheme() const;
      string const& getAggregateObj() const;
      string const& getAggregateObjType() const;
      string const& getComment() const;


   private:
      
      string d_moduleName;
      long   d_recordID;
      string d_name;
      string d_type;
      string d_domain;
      string d_map;
      string d_theme;
      string d_aggregateObj;
      string d_aggregateObjType;
      string d_comment;
};

// Inline methods

inline
string const&
sb_CatalogSpatialDom::getModuleName() const
{
   return d_moduleName;
}

inline
long
sb_CatalogSpatialDom::getRecordID() const
{
   return d_recordID;
}

inline
string const&
sb_CatalogSpatialDom::getName() const
{
   return d_name;
}

inline
string const&
sb_CatalogSpatialDom::getType() const
{
   return d_type;
}

inline 
string const&
sb_CatalogSpatialDom::getDomain() const
{
   return d_domain;
}

inline 
string const&
sb_CatalogSpatialDom::getMap() const
{
   return d_map; 
}

inline 
string const&
sb_CatalogSpatialDom::getTheme() const
{
   return d_theme;
}

inline
string const&
sb_CatalogSpatialDom::getAggregateObj() const
{
   return d_aggregateObj;
}

inline
string const&
sb_CatalogSpatialDom::getAggregateObjType() const
{
   return d_aggregateObjType;
}

inline
string const&
sb_CatalogSpatialDom::getComment() const
{
   return d_comment;
}


#endif // INCLUDED_SB_CATALOGSPATIALDOM_HXX

