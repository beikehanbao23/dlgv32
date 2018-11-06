// SDTSDLGOverlay.h - interface for SDTSDLGOverlay class
//
// Developed by: Mike Childs
//      Started: 8/31/97

#ifndef _SDTSDLGOVERLAY_H_
#define _SDTSDLGOVERLAY_H_

// Disable warning about long debug strings
#pragma warning( disable : 4786 )

#include "StdAfx.h"
#include <list>
#include <string>
#include "DLGOverlay.h"
#include "SDTS_AttRecord.h"
#include "sdtsxx/builder/sb_Polygon.hxx"

// Forward declarations
class sb_AttAccuracy;
class sb_Completeness;
class sb_ExtSpatialRef;
class sb_IntSpatialRef;
class sb_Ident;
class sb_Lineage;
class sb_LogicalConsis;
class sb_PointNode;
class sb_PosAccuracy;
class sb_SpatialDom;
class CLoadingDialog;
class SDTS_AttModule;
class SDTS_MDEFModule;
class SDTSDLG_PropSheet;

class SDTSDLGOverlay : public DLGOverlay
{
    public:
	    // Constructors / Destructors
        SDTSDLGOverlay( CString& strCATDFilename, const CString& strAGOB,
                        const CString& strMap, const CString& strTheme, 
                        const CString& strPath );
	    ~SDTSDLGOverlay();

       	// Overridden functions
        CString getDescription() const;
	    BOOL load();
	    void showPropertiesDialog();
	    void calculateBoundingRect();

        // SDTSDLGOverlay specific functions
        void convertPoint( double& x, double& y );
        const CString& getAggregateObjectID() const;
        const CString& getMapName() const;
        const CString& getTheme() const;
        void getAttLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs,
                                    const CString& strModuleName, UINT index ) const;
        const string& getEntityDesc( const vector<SDTSAtt_LabelValuePair>& pairs ) const;
        void getPolygonAttLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs,
                                           UINT rcid ) const;

    protected:
        // Helper functions
        bool processCATD( void );
        bool loadAttributeHeaderModule( void );
        bool loadAttributeModules( void );
        bool loadControlPoints( void );
        bool loadDataQualityModules( void );
        bool loadDQAA( void );
        bool loadDQCG( void );
        bool loadDQHL( void );
        bool loadDQLC( void );
        bool loadDQPA( void );
        bool loadExternalRef( void );
        bool loadInternalRef( void );
        bool loadIdent( void );
        bool loadTransferStats( void );
        bool readAreas( CLoadingDialog& dlgLoading );
        bool readDegLines( CLoadingDialog& dlgLoading );
        bool readNodes( CLoadingDialog& dlgLoading );
        bool readLines( CLoadingDialog& dlgLoading );
        bool readPolygons( CLoadingDialog& dlgLoading );
        bool setupProjection();
        int     getAHDRRecordNum( void );
        void    getAttForeignKeys( SDTS_AttRecord* pRecord, 
                                   vector<SDTSAtt_LabelValuePair>& pairs ) const;
        void    getAttModuleNameFromTheme( void );
        PROJSYS getGndRefSys( void );
        DATUM   getHorizDatum( void );
        long    getZone( void );

        // Thread functions
        static UINT loadAttModulesThreadFunc( LPVOID pParam );
        static UINT loadAttHeaderThreadFunc( LPVOID pParam );
        static UINT loadDataQualityThreadFunc( LPVOID pParam );

        // Member data passed into the constructor
        CString d_strAGOB;
        CString d_strDescription;
        CString d_strMap;
        CString d_strTheme;
        CString d_strPath;
        
        // Filenames gathered from the CATD file
        CString d_strAHDRFilename;
        CString d_strAreasFilename;
        CString d_strDegLinesFilename;
        CString d_strDQAAFilename;
        CString d_strDQCGFilename;
        CString d_strDQHLFilename;
        CString d_strDQLCFilename;
        CString d_strDQPAFilename;
        CString d_strFF01Filename;
        CString d_strIdentFilename;
        CString d_strIntRefFilename;
        CString d_strLinesFilename;
        CString d_strNodesFilename;
        CString d_strNPFilename;
        CString d_strPolygonFilename;
        CString d_strSpatialDomFilename;
        CString d_strTransferStatsFilename;
        CString d_strXRefFilename;
        
        // Builder objects
        sb_AttAccuracy*     d_pDQAA;
        sb_Completeness*    d_pDQCG;
        sb_ExtSpatialRef*   d_pExternalRef;
        sb_IntSpatialRef*   d_pInternalRef;
        sb_Ident*           d_pIdent;
        sb_Lineage*         d_pDQHL;
        sb_LogicalConsis*   d_pDQLC;
        sb_PointNode*       d_pControlPoints[4];
        sb_PosAccuracy*     d_pDQPA;
        sb_SpatialDom*      d_pSpatialDom;
        vector<sb_Polygon*> d_pPolygons;

        // Transfer statistics
        long d_numAreas;
        long d_numDegLines;
        long d_numNodes;
        long d_numLines;
        long d_numPolygons;

        // Property Sheet
        SDTSDLG_PropSheet* d_pPropertySheet;

        // Attribute stuff
        bool getModuleFromName( const CString& strName, SDTS_AttModule** ppModule ) const;
        class AttMapRecord
        {
        public:
            // Constructor
            AttMapRecord( const CString& strName ) ;

            // Data members
            CString         d_strName;
            CString         d_strFilename;
            SDTS_AttModule* d_pModule;
        };
        bool                d_bDestroying;
        bool                d_bUnknownTheme;
        int                 d_ahdrRecordNum;
        float               d_moduleVersion;
        list<AttMapRecord*> d_attModuleMap;
        SDTS_AttModule*     d_pAHDRModule;
        SDTS_MDEFModule*    d_pMDEFModule;
        string              d_strMDEFStatus;

        // Threads
        CWinThread* d_pAttHeaderThread;
        CWinThread* d_pAttModuleThread;
        CWinThread* d_pDataQualityThread;
};

inline const CString&
SDTSDLGOverlay::getAggregateObjectID() const
{
    return d_strAGOB;
}

inline const CString&
SDTSDLGOverlay::getMapName() const
{
    return d_strMap;
}

inline const CString&
SDTSDLGOverlay::getTheme() const
{
    return d_strTheme;
}

inline CString
SDTSDLGOverlay::getDescription() const
{
    return d_strDescription;
}

#endif