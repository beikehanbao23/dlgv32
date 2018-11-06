// SDTSDEMOverlay.h - interface fo SDTSDEMOverlay class
//
// Developed by: Mike Childs
//      Started: 4/21/98

#ifndef _SDTSDEMOVERLAY_H_
#define _SDTSDEMOVERLAY_H_

#include "RasterOverlay.h"

// Forward declarations
class sb_DataDictSchema;
class sb_ExtSpatialRef;
class sb_IntSpatialRef;
class sb_RasterDefn;
class sb_SpatialDom;

class SDTSDEMOverlay : public RasterOverlay
{
public:
    // Constructors
    SDTSDEMOverlay( CString& strCATDFilename, const CString& strMap, const CString& strPath );
    ~SDTSDEMOverlay();

    // Overridden functions
    CString getDescription() const;
    long getImageHeight() const;
    long getImageWidth() const;
    bool isVertical() const;
    BOOL load();
    void calculateBoundingRect();

protected:
    // Overrides
    bool getElevation( long row, long col, float& elev ) const;
    void getMinMaxSampleValue( float& min, float& max ) const;

    // Helper functions
    bool isElevationValid( short elev ) const;
    bool loadDDSH();
    bool loadDDOM();
    bool loadInternalRef();
    bool loadExternalRef();
    bool loadRasterDef();
    bool loadSpatialDomain();
    bool processCATD();
    bool readData();
    bool setupProjection();

private:
    // Member data from the constructor
    CString d_strMap;
    CString d_strPath;

    // Filenames from the CATD file
    CString d_strCELLFilename;
    CString d_strDDSHFilename;
    CString d_strDDOMFilename;
    CString d_strIREFFilename;
    CString d_strRSDFFilename;
    CString d_strSPDMFilename;
    CString d_strXREFFilename;

    // Builder objects
    sb_DataDictSchema* d_pDDSH;
    sb_ExtSpatialRef*  d_pXREF;
    sb_IntSpatialRef*  d_pIREF;
    sb_RasterDefn*     d_pRSDF;
    sb_SpatialDom*     d_pSPDM;

    // Other member data
    CString       d_strDescription;
    long          d_minElev;
    long          d_maxElev;
    short*        d_pDataGrid;
    vector<short> d_invalidElevations;
};

inline bool
SDTSDEMOverlay::isVertical() const
{
    return true;
}

inline CString
SDTSDEMOverlay::getDescription() const
{
    return d_strDescription;
}

#endif