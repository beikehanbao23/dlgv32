
#ifndef INCLUDED_SB_RASTERDEFN_HXX
#include "builder/sb_RasterDefn.hxx"
#endif

#ifdef _MSC_VER
   #include <iostream>
#else
   #include <iostream.h>
#endif

#ifndef INCLUDED_SB_UTIL_HXX
#include "builder/sb_Utils.hxx"
#endif

sb_RasterDefn::sb_RasterDefn() :
           d_moduleName("") ,
           d_recordID(0) ,
           d_objectRep("") ,
           d_acqDev("") ,
           d_acqDate("") ,
           d_comments("") ,
           d_cellModName("") ,
           d_defImpl("") ,
           d_dataCompress("") ,
           d_dataCompressMethod("") ,
           d_rowExtent(0) ,
           d_colExtent(0) ,
           d_scanOrigin("") ,
           d_scanPattern("") ,
           d_tessIndex("") ,
           d_tessIndexFormat("") ,
           d_tessIndexDesc("") ,
           d_linesPerAlternation(0) ,
           d_firstScanDirection("") ,
           d_aspectRatio(0.0) ,
           d_numberLayers (0) ,
           d_rasterAttributeID() ,
           d_layerDefinition() ,
           d_layerAttributeID() ,
           d_compositeID() 
	   
{
}


sb_RasterDefn::sb_RasterDefn(sb_RasterDefn const& right)
{
   operator=(right);
}

sb_RasterDefn const&
sb_RasterDefn::operator=(sb_RasterDefn const& right)
{
   if (this == &right)
     return *this;

   d_moduleName = right.d_moduleName ;
   d_recordID = right.d_recordID ;
   d_objectRep = right.d_objectRep ;
   d_acqDev = right.d_acqDev ;
   d_acqDate = right.d_acqDate ;
   d_comments = right.d_comments ;
   d_cellModName = right.d_cellModName ;
   d_defImpl = right.d_defImpl ;
   d_dataCompress = right.d_dataCompress ;
   d_dataCompressMethod = right.d_dataCompressMethod ;
   d_rowExtent = right.d_rowExtent ;
   d_colExtent = right.d_colExtent ;
   d_scanOrigin = right.d_scanOrigin ;
   d_scanPattern = right.d_scanPattern ;
   d_tessIndex = right.d_tessIndex ;
   d_tessIndexFormat = right.d_tessIndexFormat ;
   d_tessIndexDesc = right.d_tessIndexDesc ;
   d_linesPerAlternation = right.d_linesPerAlternation ;
   d_firstScanDirection = right.d_firstScanDirection ;
   d_aspectRatio = right.d_aspectRatio ;
   d_numberLayers  = right.d_numberLayers  ;
   d_rasterAttributeID = right.d_rasterAttributeID ;
   d_layerDefinition = right.d_layerDefinition ;
   d_layerAttributeID = right.d_layerAttributeID ;
   d_compositeID = right.d_compositeID ;

   return  *this;
}

sb_RasterDefn::sb_RasterDefn(sc_Record& recprox)
{
   // Build an sb_RasterDefn from an sc_Record

   // Make sure we have a record from a RasterDefn module.

   sc_FieldCntr::const_iterator curfield;
   if (!sb_Utils::getFieldByMnem(recprox,"RSDF",curfield))
      {
         cerr << "sb_RasterDefn::sb_RasterDefn(sc_Record&): "
              << "Not a RasterDefn record.";
         cerr << endl;
         return;
      }

   // We have a primary field from a module. Start
   // picking it apart.

   sc_SubfieldCntr::const_iterator cursubfield;

   // Module Name type A
   if (sb_Utils::getSubfieldByMnem(*curfield,"MODN",cursubfield))
      cursubfield->getA(d_moduleName);

   // RCID Record ID type I
   if (sb_Utils::getSubfieldByMnem(*curfield,"RCID",cursubfield))
      cursubfield->getI(d_recordID);

   // Object Representation type A
   if (sb_Utils::getSubfieldByMnem(*curfield,"OBRP",cursubfield))
      cursubfield->getA(d_objectRep);

   // Acquisition Device Type A
   if (sb_Utils::getSubfieldByMnem(*curfield,"AQMD",cursubfield))
      cursubfield->getA(d_acqDev);

   // Acquisition Date Type A
   if (sb_Utils::getSubfieldByMnem(*curfield,"AQDT",cursubfield))
      cursubfield->getA(d_acqDate);

   //  Comments type A
   if (sb_Utils::getSubfieldByMnem(*curfield,"COMT",cursubfield))
      cursubfield->getA(d_comments);

   // Cell Module Name [o/"Catalog/CrossReference"][M] Type A
   if (sb_Utils::getSubfieldByMnem(*curfield,"CMNM",cursubfield))
      cursubfield->getA(d_cellModName);

   // Default Implimentation Type A
   if (sb_Utils::getSubfieldByMnem(*curfield,"DEFI",cursubfield))
      cursubfield->getA(d_defImpl);

   // Data Compression [M/Default Implementation = NON] Type A
   if (sb_Utils::getSubfieldByMnem(*curfield,"CMPR",cursubfield))
      cursubfield->getA(d_dataCompress);

   //  Data Compression Method [m/Data Compression = COM ] type A
   if (sb_Utils::getSubfieldByMnem(*curfield,"CMMD",cursubfield))
      cursubfield->getA(d_dataCompressMethod);

   //  Row Extent [m] type I
   if (sb_Utils::getSubfieldByMnem(*curfield,"RWXT",cursubfield))
      cursubfield->getI(d_rowExtent);

   // Column Extent [m] type I
   if (sb_Utils::getSubfieldByMnem(*curfield,"CLXT",cursubfield))
      cursubfield->getI(d_colExtent);

   // (d) Scan Origin [m/Defaul Implementation=NON] type A
   if (sb_Utils::getSubfieldByMnem(*curfield,"SCOR",cursubfield))
      cursubfield->getA(d_scanOrigin);

   // (d) Scan Pattern [M/Default Implementation = NON] type A
   if (sb_Utils::getSubfieldByMnem(*curfield,"SCPT",cursubfield))
      cursubfield->getA(d_scanPattern);

   // (d) Tesseral Indexing [M/Default Implementation=NON] type A
   if (sb_Utils::getSubfieldByMnem(*curfield,"TIDX",cursubfield))
      cursubfield->getA(d_tessIndex);

   //  Tesseral Index Foramt [m/Iesseral Index=TESS] type A
   if (sb_Utils::getSubfieldByMnem(*curfield,"TIFT",cursubfield))
      cursubfield->getA(d_tessIndexFormat);

   // Tesseral Indexing Desc[m/tesseral Indexing=Tess] type A
   if (sb_Utils::getSubfieldByMnem(*curfield,"TIDS",cursubfield))
      cursubfield->getA(d_tessIndexDesc);

   // (d) Number of Liners per Alternation[m/def impl=non] type i
   if (sb_Utils::getSubfieldByMnem(*curfield,"ALTN",cursubfield))
      cursubfield->getI(d_linesPerAlternation);

   // (d) First Scan Direction [m/default implementation=non] type A
   if (sb_Utils::getSubfieldByMnem(*curfield,"FSCN",cursubfield))
      cursubfield->getA(d_firstScanDirection);

   // (d) Aspect Ration [m/default Implementation=non] type R
   if (sb_Utils::getSubfieldByMnem(*curfield,"ASPR",cursubfield))
      cursubfield->getR(d_aspectRatio);

   //  Number of Layers type I
   if (sb_Utils::getSubfieldByMnem(*curfield,"NLAY",cursubfield))
      cursubfield->getI(d_numberLayers);


   //Secondary Fields

   // RasterDefn Attribute ID(R) Type (none) Foreign identifer. ATID Fields
   // Attribute ID, repeating (ATID) Fields
   sc_FieldCntr const& atid_fields = recprox;
   for (curfield = atid_fields.begin();
	curfield != atid_fields.end();
	curfield++)
      {
	 if (curfield->getMnemonic() == "RATP")
	    d_rasterAttributeID.push_back(sb_ForeignID(*curfield));
      }
   
	// Layer Definition Repeating field
   // Layer Definition (LDEF) (O) [M]
   for (curfield = atid_fields.begin();
	curfield != atid_fields.end();
	curfield++)
      {
	 if (curfield->getMnemonic() == "LDEF")
	    d_layerDefinition.push_back(sb_RasterLayer(*curfield));
      }

   // (^)Layer Attribute ID (O)  "LATP"
   for (curfield = atid_fields.begin();
	curfield != atid_fields.end();
	curfield++)
      {
	 if (curfield->getMnemonic() == "LATP")
	    d_layerAttributeID.push_back(sb_ForeignID(*curfield));
      }

   // (^) Compostie ID (R) "CPID"
   for (curfield = atid_fields.begin();
	curfield != atid_fields.end();
	curfield++)
      {
	 if (curfield->getMnemonic() == "CPID")
	    d_compositeID.push_back(sb_ForeignID(*curfield));
      }

/*
   // 
   if (sb_Utils::getSubfieldByMnem(*curfield,"",cursubfield))
      cursubfield->get ();
*/
/*
   // Secondary Fields

   // Spatial Address, non-repeating (SADR) Field
   if (sb_Utils::getFieldByMnem(recprox,"SADR",curfield))
      d_spatialAddr = sb_SpatialAddr(*curfield);
*/

}
