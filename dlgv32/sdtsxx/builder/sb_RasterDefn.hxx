#ifndef INCLUDED_SB_RASTERDEFN_HXX
#define INCLUDED_SB_RASTERDEFN_HXX

// Note:  This class has been compiled, but has NOT been tested due to
//        the lack of data using the RasterDefn module.


#ifdef _MSC_VER
   #include <string>
   #include <vector>
   using namespace std;
#else

   #include <string>
   #include <vector.h>
#endif


#ifndef INCLUDED_SB_RASTERLAYER_HXX
#include "builder/sb_RasterLayer.hxx"
#endif

#ifndef INCLUDED_SB_FOREIGNID_HXX
#include "builder/sb_ForeignID.hxx"
#endif

#ifndef INCLUDED_SC_RECORD_H
#include "container/sc_Record.h"
#endif

class sb_RasterDefn
{
   public:
     sb_RasterDefn();
     sb_RasterDefn(sb_RasterDefn const& right);
     sb_RasterDefn const& operator=(sb_RasterDefn const& right);
     sb_RasterDefn(sc_Record& recprox);
     bool operator==(sb_RasterDefn const& right) const;
     bool operator<(sb_RasterDefn const& right) const;

     // Accessors

     string const& getModuleName() const;
     long getRecordID() const;
     string const& getObjectRep() const;
     string const& getAcqDev() const;
     string const& getAcqDate() const ;
     string const& getComments () const;
     string const& getCellModName() const;
     string const& getDefImpl() const;
     string const& getDataCompress() const;
     string const& getDataCompressMethod() const;
     long getRowExtent() const;
     long getColExtent() const;
     string const& getScanOrigin() const;
     string const& getScanPattern() const;
     string const& getTessIndex() const;
     string const& getTessIndexFormat() const;
     string const& getTessIndexDesc() const;
     long getLinesPerAlternation() const ;
     string const& getFirstScanDirection() const;
     double getAspectRatio() const;
     long getNumberLayers() const;
    
     vector<sb_ForeignID> const& getRasterAttributeID() const;
     vector<sb_RasterLayer> const& getLayerDefinition() const;
     vector<sb_ForeignID> const& getLayerAttributeID() const;
     vector<sb_ForeignID> const& getCompositeID() const;

   private:
    
     string d_moduleName;
     long d_recordID;
     string d_objectRep;
     string d_acqDev;
     string d_acqDate;
     string d_comments;
     string d_cellModName;
     string d_defImpl;
     string d_dataCompress;
     string d_dataCompressMethod;
     long d_rowExtent;
     long d_colExtent;
     string d_scanOrigin;
     string d_scanPattern;
     string d_tessIndex;
     string d_tessIndexFormat;
     string d_tessIndexDesc;
     long d_linesPerAlternation;
     string d_firstScanDirection;
     double d_aspectRatio;
     long d_numberLayers ;
     vector<sb_ForeignID> d_rasterAttributeID;
     
     // Field Name: Layer Definition
     vector<sb_RasterLayer> d_layerDefinition;
     vector<sb_ForeignID> d_layerAttributeID;
     vector<sb_ForeignID> d_compositeID;
     
};


inline
bool
sb_RasterDefn::operator==(sb_RasterDefn const& right) const
{
    return 
           d_moduleName == right.d_moduleName &&
           d_recordID == right.d_recordID &&
           d_objectRep == right.d_objectRep &&
           d_acqDev == right.d_acqDev &&
           d_acqDate == right.d_acqDate &&
           d_comments == right.d_comments &&
           d_cellModName == right.d_cellModName &&
           d_defImpl == right.d_defImpl &&
           d_dataCompress == right.d_dataCompress &&
           d_dataCompressMethod == right.d_dataCompressMethod &&
           d_rowExtent == right.d_rowExtent &&
           d_colExtent == right.d_colExtent &&
           d_scanOrigin == right.d_scanOrigin &&
           d_scanPattern == right.d_scanPattern &&
           d_tessIndex == right.d_tessIndex &&
           d_tessIndexFormat == right.d_tessIndexFormat &&
           d_tessIndexDesc == right.d_tessIndexDesc &&
           d_linesPerAlternation == right.d_linesPerAlternation &&
           d_firstScanDirection == right.d_firstScanDirection &&
           d_aspectRatio == right.d_aspectRatio &&
           d_numberLayers  == right.d_numberLayers  &&
           d_rasterAttributeID == right.d_rasterAttributeID &&
           d_layerDefinition == right.d_layerDefinition &&
           d_layerAttributeID == right.d_layerAttributeID &&
           d_compositeID == right.d_compositeID ;
}

inline
bool
sb_RasterDefn::operator<(sb_RasterDefn const& right) const
{
   return false;
}

inline
string const&
sb_RasterDefn::getModuleName() const
{
   return d_moduleName;
}
   
inline
long
sb_RasterDefn::getRecordID() const
{
   return d_recordID;
}

     
inline
string const& 
sb_RasterDefn::getObjectRep() const
{
   return d_objectRep;
}


     
inline
string const& 
sb_RasterDefn::getAcqDev() const
{
   return d_acqDev;
}


     
inline
string const&
sb_RasterDefn::getAcqDate() const 
{
   return d_acqDate;
}

     
inline
string const& 
sb_RasterDefn::getComments () const
{
   return d_comments;
}

     
     
inline
string const& 
sb_RasterDefn::getCellModName() const
{
   return d_cellModName;
}

     
     
inline
string const& 
sb_RasterDefn::getDefImpl() const
{
   return d_defImpl;
}

     
     
inline
string const& 
sb_RasterDefn::getDataCompress() const
{
   return d_dataCompress;
}

     
     
inline
string const& 
sb_RasterDefn::getDataCompressMethod() const
{
   return d_dataCompressMethod;
}

     
     
inline
long 
sb_RasterDefn::getRowExtent() const
{
   return d_rowExtent;
}

     
     
inline
long 
sb_RasterDefn::getColExtent() const
{
   return d_colExtent;
}

     
     
inline
string const& 
sb_RasterDefn::getScanOrigin() const
{
   return d_scanOrigin;
}


     
inline
string const& 
sb_RasterDefn::getScanPattern() const
{
   return d_scanPattern;
}


     
inline
string const& 
sb_RasterDefn::getTessIndex() const
{
   return d_tessIndex;
}


     
inline
string const& 
sb_RasterDefn::getTessIndexFormat() const
{
   return d_tessIndexFormat;
}

     
     
inline
string const& 
sb_RasterDefn::getTessIndexDesc() const
{
   return d_tessIndexDesc;
}


     
inline
long 
sb_RasterDefn::getLinesPerAlternation() const 
{
   return d_linesPerAlternation;
}


     
inline
string const& 
sb_RasterDefn::getFirstScanDirection() const
{
   return d_firstScanDirection;
}


     
inline
double 
sb_RasterDefn::getAspectRatio() const
{
   return d_aspectRatio;
}


     
inline
long 
sb_RasterDefn::getNumberLayers() const
{
   return d_numberLayers ;
}

    
     
inline
vector<sb_ForeignID> const& 
sb_RasterDefn::getRasterAttributeID() const
{
   return d_rasterAttributeID;
}


     
inline
vector<sb_RasterLayer> const& 
sb_RasterDefn::getLayerDefinition() const
{
   return d_layerDefinition;
}


     
inline
vector<sb_ForeignID> const& 
sb_RasterDefn::getLayerAttributeID() const
{
   return d_layerAttributeID;
}


     
inline
vector<sb_ForeignID> const& 
sb_RasterDefn::getCompositeID() const
{
   return d_compositeID;
}

#endif // INCLUDED_SB_RASTERDEFN_HXX
