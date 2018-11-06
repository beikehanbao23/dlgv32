// SDTS_AttModuleFactory.h - interface for SDTS_AttModuleFactory class
//
// Developed by: Mike Childs
//      Started: 9/18/97

#ifndef _SDTS_ATTMODULEFACTORY_H_
#define _SDTS_ATTMODULEFACTORY_H_

#include "StdAfx.h"
#include <afxmt.h>  // Multi-threaded support
#include <list>
using namespace std;

// Forward declarations
class SDTS_AttModule;

class SDTS_AttModuleFactory
{
public:
    // Referencing functions
    static SDTS_AttModule* AddRef( const string& strFilename, const string& strName );
    static UINT Release( SDTS_AttModule* pModule );

protected:
    // Internal class
    class ModuleCounter
    {
    public:
        // Constructor
        ModuleCounter( const string& d_strFilename );

        // Destructor
        ~ModuleCounter();

        // Public Data Members
        string                 d_strFilename;
        SDTS_AttModule*        d_pModule;
        UINT                   d_refCount;
    };

    // List of opened module
    static list<ModuleCounter*> d_modules;

    // Critical section for thread synchronization
    static CCriticalSection d_cs;
};

#endif