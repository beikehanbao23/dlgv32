#ifndef INCLUDED_SB_IDENT_HXX
#define INCLUDED_SB_IDENT_HXX

// $Id: sb_Ident.hxx,v 1.1 1998/09/14 15:04:24 bmaddox Exp bmaddox $

#include <string>

#ifndef INCLUDED_SB_FOREIGNID_HXX
#include "builder/sb_ForeignID.hxx"
#endif

#ifndef INCLUDED_SC_RECORD_H
#include "container/sc_Record.h"
#endif



class sb_Ident
{
   public:

      sb_Ident();
      sb_Ident(sb_Ident const& right);  // copy constructor
      sb_Ident const& operator=(sb_Ident const& right); // assignment operator
      
      explicit sb_Ident(sc_Record& recprox);
         // recprox must be from an Identification module, or this won't work.
         // recprox can't be const because we use its -> operator.

      // Accessors

      string const& getModuleName() const;
      long getRecordID() const;
      string const& getStandardIdent() const;
      string const& getStandardVer() const;
      string const& getStandardDocRef() const;
      string const& getProfileIdent() const;
      string const& getProfileVer() const;
      string const& getProfileDocRef() const;
      string const& getTitle() const;
      string const& getDataID() const;
      string const& getDataStruct() const;
      string const& getMapDate() const;
      string const& getDataSetCreationDate() const;
      long getScale() const;
      string const& getComment() const;

//  The following are associated with the Conformance field?  -- Yes.

      string const& getComposites() const;
      string const& getVectorGeom() const;
      string const& getVectorTopol() const;
      string const& getRaster() const;
      long getExternSpatRef() const;
      long getFeaturesLevel() const;
      long getCodingLevel() const;
      string const& getNongeoDeminsion() const;
      
      sb_ForeignID const& getAttributeID() const;

   private:
     
      string d_moduleName;
      long d_recordID;  
      string d_standardIdent;
      string d_standardVer;
      string d_standardDocRef;
      string d_profileIdent;
      string d_profileVer;
      string d_profileDocRef;
      string d_title;
      string d_dataID;
      string d_dataStruct;
      string d_mapDate;
      string d_dataSetCreationDate;
      long d_scale;
      string d_comment;

      string d_composites;
      string d_vectorGeom;
      string d_vectorTopol;
      string d_raster;
      long d_externSpatRef;
      long d_featuresLevel;
      long d_codingLevel;
      string d_nongeoDeminsion;
       
       
      sb_ForeignID d_attrID; 
};

// Inline methods

inline
string const&
sb_Ident::getModuleName() const
{
   return d_moduleName;
}


inline 
long
sb_Ident::getRecordID() const
{
   return d_recordID;
}

inline
string const&
sb_Ident::getStandardIdent() const
{
   return d_standardIdent;
}

inline
string const&
sb_Ident::getStandardVer() const
{
   return d_standardVer;
}

inline
string const&
sb_Ident::getStandardDocRef() const
{
   return d_standardDocRef;
}

inline
string const& 
sb_Ident::getProfileIdent() const
{  
   return d_profileIdent;
}

inline
string const&
sb_Ident::getProfileVer() const
{
   return d_profileVer;
}

inline 
string const&
sb_Ident::getProfileDocRef() const
{
   return d_profileDocRef;
}

inline
string const&
sb_Ident::getTitle() const
{
   return d_title;
}

inline
string const&
sb_Ident::getDataID() const
{
   return d_dataID;
}

inline
string const&
sb_Ident::getDataStruct() const
{
   return d_dataStruct;
}

inline
string const&
sb_Ident::getMapDate() const
{
   return d_mapDate;
}

inline
string const&
sb_Ident::getDataSetCreationDate() const
{
   return d_dataSetCreationDate;
}

inline 
long
sb_Ident::getScale() const
{
   return d_scale;
}

inline
string const&
sb_Ident::getComment() const
{
   return d_comment;
}

inline
string const&
sb_Ident::getComposites() const
{
   return d_composites;
}

inline
string const&
sb_Ident::getVectorGeom() const
{
   return d_vectorGeom;
}

inline
string const&
sb_Ident::getVectorTopol() const
{
   return d_vectorTopol;
}

inline 
string const&
sb_Ident::getRaster() const
{
   return d_raster;
}

inline
long
sb_Ident::getExternSpatRef() const
{
   return d_externSpatRef;
}

inline
long
sb_Ident::getFeaturesLevel() const
{
   return d_featuresLevel;
}

inline
long
sb_Ident::getCodingLevel() const
{
    return d_codingLevel;
}
      

inline
string const&
sb_Ident::getNongeoDeminsion() const
{
    return d_nongeoDeminsion;
}
      
inline
sb_ForeignID const&
sb_Ident::getAttributeID() const
{
   return d_attrID;
}



#endif INCLUDED_SB_IDENT_HXX
