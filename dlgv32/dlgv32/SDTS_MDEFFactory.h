// SDTS_MDEFFactory.h - interface for SDTS_MDEFFactory class
//
// Developed by: Mike Childs
//      Started: 11/17/97

#ifndef _SDTS_MDEFFACTORY_H_
#define _SDTS_MDEFFACTORY_H_

#include "StdAfx.h"
#include <afxmt.h>  // Multi-threaded support

// Forward declarations
class SDTS_MDEFModule;

class SDTS_MDEFFactory
{
public:
    // Referencing functions
    static SDTS_MDEFModule* AddRef( int scale, float version );
    static UINT Release( int scale );

protected:
    // Helper functions
    static CString getModuleName( const CString& strTitle, const CString& strRegEntryName );
    static bool processMDIR( const CString& strMDIRFilename, CString& strMDEFFilename,
                             float& version );
    static CString getPath( const CString& strFilename );
    static UINT showVersionError( float moduleVersion, float mdefVersion );
    static void getMDEFInfo( const CString& strRegEntryName, const CString& strDialogTitle,
                             CString& strMDEFFilename, float& version );

    // Internal class
    class ModuleCounter
    {
    public:
        // Constructor
        ModuleCounter();

        // Destructor
        ~ModuleCounter();

        // Public Data Members
        SDTS_MDEFModule* d_pModule;
        UINT             d_refCount;
        float            d_version;
    };

    // Open modules
    static ModuleCounter d_24K;
    static ModuleCounter d_100K;
    static ModuleCounter d_2M;

    // Critical section for thread synchronization
    static CCriticalSection d_cs;
};

#endif