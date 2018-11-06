// SDTS_AttModuleFactory.cpp - implementation of class
//
// Developed by: Mike Childs
//      Started: 9/18/97

#include "SDTS_AttModuleFactory.h"
#include "SDTS_AttModule.h"

// Initialize static variables
list<SDTS_AttModuleFactory::ModuleCounter*> SDTS_AttModuleFactory::d_modules;
CCriticalSection                            SDTS_AttModuleFactory::d_cs;

// Constructor for ModuleCounter class
SDTS_AttModuleFactory::ModuleCounter::ModuleCounter( const string& strFilename )
: d_strFilename(strFilename), d_pModule(NULL), d_refCount(0)
{
}

// Destructor for ModuleCounter class
SDTS_AttModuleFactory::ModuleCounter::~ModuleCounter()
{
    // Delete module
    delete d_pModule;
}

// AddRef - this function searches through the list of already
//          opened modules looking for one that has the same
//          name as <strFilename>.  If one is found, its ref
//          count is incremented, otherwise a new module
//          counter class is added to the list and it is
//          loaded
SDTS_AttModule*
SDTS_AttModuleFactory::AddRef( const string& strFilename, const string& strName )
{
    // Lock this function so that only one thread can access it at a time
    CSingleLock lock( &d_cs, TRUE );

    // Search through the list of already open modules looking for
    // one that matches the filename passed in
    for ( list<ModuleCounter*>::iterator i = d_modules.begin(); 
          i != d_modules.end(); i++ )
    {
        if ( strFilename == (*i)->d_strFilename )
        {
            // We've found a match, just add a reference and return the
            // pointer to the module
            ASSERT( (*i)->d_refCount > 0 );
            (*i)->d_refCount++;
            return (*i)->d_pModule;
        }
    }

    // The module specified is not already open, create a new module counter
    // and load the module
    ModuleCounter* pModuleCtr = new ModuleCounter( strFilename );
    pModuleCtr->d_pModule = new SDTS_AttModule( strName );
    pModuleCtr->d_pModule->loadFromFile( strFilename.c_str() );
    pModuleCtr->d_refCount = 1;

    // Add the module counter to the list
    d_modules.push_back( pModuleCtr );

    return pModuleCtr->d_pModule;
}

// Release - this function releases the reference to the specified
//           attribute primary module.  If that was the last reference,
//           the memory for the attribute primary module and its counter
//           are released.  The number of references to the module prior
//           to decrementing the reference count is returned.  If the module
//           could not be found, 0 is returned.
UINT
SDTS_AttModuleFactory::Release( SDTS_AttModule* pModule )
{
    // Make this function thread-safe
    CSingleLock lock( &d_cs, TRUE );

    // Search through the list of already open modules looking for a match
    for ( list<ModuleCounter*>::iterator i = d_modules.begin(); 
          i != d_modules.end(); i++ )
    {
        if ( pModule == (*i)->d_pModule )
        {
            // The ref count better be at least one and the module shouldn't be NULL
            ASSERT( (*i)->d_refCount > 0 && NULL != (*i)->d_pModule );

            // We've found a match, check to see if there is only one reference to it
            if ( 1 ==(*i)->d_refCount )
            {
                // Last reference, delete the module counter and remove the reference from
                // the list
                delete *i;
                d_modules.erase( i );
                return 1;
            }
            else
            {
                // Just decrement the reference counter
                return  ( (*i)->d_refCount-- );
            }
        }
    }

    // No match found, return 0
    return 0;
}