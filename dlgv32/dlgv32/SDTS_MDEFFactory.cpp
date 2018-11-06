// SDTS_MDEFFactory.cpp - implementation of SDTS_MDEFFactory class
//
// Developed by: Mike Childs
//      Started: 11/17/97

#include "SDTS_MDEFFactory.h"
#include "SDTS_MDEFModule.h"
#include <string>
#include <fstream>

// SDTS includes
#include "sdtsxx/builder/sb_Utils.hxx"
#include "sdtsxx/container/sc_Record.h"
#include "sdtsxx/container/sc_Field.h"
#include "sdtsxx/container/sc_Subfield.h"
#include "sdtsxx/io/sio_Reader.h"

// Initialize static variables
SDTS_MDEFFactory::ModuleCounter SDTS_MDEFFactory::d_24K;
SDTS_MDEFFactory::ModuleCounter SDTS_MDEFFactory::d_100K;
SDTS_MDEFFactory::ModuleCounter SDTS_MDEFFactory::d_2M;
CCriticalSection SDTS_MDEFFactory::d_cs;

// Constructor for ModuleCounter class
SDTS_MDEFFactory::ModuleCounter::ModuleCounter()
: d_pModule(NULL), d_refCount(0), d_version(0)
{
}

// Destructor for ModuleCounter class
SDTS_MDEFFactory::ModuleCounter::~ModuleCounter()
{
    // Delete module
    delete d_pModule;
}

// AddRef - this function checks to see if the MDEF module for the
//          indicated scale has already been loaded.  If it has, its
//          ref count is incremented, otherwise it first checks the
//          Registry for a filename, if it exists, it uses that, otherwise
//          it prompts the user for the name of the MDEF module.
SDTS_MDEFModule*
SDTS_MDEFFactory::AddRef( int scale, float version )
{
    // Lock this function so that only one thread can access it at a time
    CSingleLock lock( &d_cs, TRUE );

    // Get the module to check in
    ModuleCounter* pMC = NULL;
    CString strRegEntryName;
    CString strDialogTitle;
    switch ( scale )
    {
        case 24000:
            pMC = &d_24K;
            strRegEntryName = "24K_MDIR";
            strDialogTitle = "Open 24K MDIR Module";
            break;
        case 25000:
            pMC = &d_24K;
            strRegEntryName = "24K_MDIR";
            strDialogTitle = "Open 24K MDIR Module";
            break;
        case 20000:
            pMC = &d_24K;
            strRegEntryName = "24K_MDIR";
            strDialogTitle = "Open 24K MDIR Module";
            break;
        case 30000:
            pMC = &d_24K;
            strRegEntryName = "24K_MDIR";
            strDialogTitle = "Open 24K MDIR Module";
            break;
        case 63360:
            pMC = &d_24K;
            strRegEntryName = "24K_MDIR";
            strDialogTitle = "Open 24K MDIR Module";
            break;
        case 100000:
            pMC = &d_100K;
            strRegEntryName = "100K_MDIR";
            strDialogTitle = "Open 100K MDIR Module";
            break;
        case 2000000:
            pMC = &d_2M;
            strRegEntryName = "2M_MDIR";
            strDialogTitle = "Open 2M MDIR Module";
            break;
        default:
            // This is not a valid scale! Abort.
            return NULL;
    }
    
    // See if the module we need has already been loaded
    if ( NULL != pMC->d_pModule )
    {
        // Check version numbers
        if ( version > pMC->d_version )
        {
            if ( IDYES == showVersionError( version, pMC->d_version ) )
            {
                // The user wants to get a new MDEF, clear the registry entry
                AfxGetApp()->WriteProfileString( "", strRegEntryName, "" );
            }
            else
            { 
                // We've found a match, just add a reference and return the
                // pointer to the module
                ASSERT( pMC->d_refCount > 0 );
                pMC->d_refCount++;
                return pMC->d_pModule;
            }
        }
        else
        { 
            // We've found a match, just add a reference and return the
            // pointer to the module
            ASSERT( pMC->d_refCount > 0 );
            pMC->d_refCount++;
            return pMC->d_pModule;
        }
    }

    // Load the MDIR and get the version number
    CString strMDEFFilename;
    float mdef_version = 0;
    do
    {
        getMDEFInfo( strRegEntryName, strDialogTitle, strMDEFFilename, mdef_version );

        // Check to make sure the MDEF version number is OK
        if ( version > mdef_version )
        {
            // See if the user wants to find a new MDEF
            if ( IDNO == showVersionError( version, mdef_version ) )
            {
                // User doesn't care, go ahead and load it
                break;
            }
        }
    } while ( version > mdef_version );

    // Abort if no MDEF file was selected
    if ( strMDEFFilename.IsEmpty() )
    {
        return NULL;
    }

    // Create the MDEF Module
    SDTS_MDEFModule* pMDEF = new SDTS_MDEFModule();

    // Load the module
    if ( !pMDEF->loadFromFile( (LPCTSTR)strMDEFFilename ) )
    {
        // Load unsuccessful, delete the module
        delete pMDEF;
    }
    else
    {
        // Load successful, setup the module counter
        delete pMC->d_pModule;
        pMC->d_pModule = pMDEF;
        pMC->d_version = mdef_version;
        pMC->d_refCount = 1;
    }

    return pMC->d_pModule;
}

// Release - this function releases the reference to the specified
//           attribute primary module.  If that was the last reference,
//           the memory for the attribute primary module and its counter
//           are released.  The number of references to the module prior
//           to decrementing the reference count is returned.  If the module
//           could not be found, 0 is returned.
UINT
SDTS_MDEFFactory::Release( int scale )
{
    // Make this function thread-safe
    CSingleLock lock( &d_cs, TRUE );

    // Make sure the scale is valid
    ASSERT( 25000 == scale || 24000 == scale || 100000 == scale || 2000000 == scale );

    // Get the module to check in
    ModuleCounter* pMC = NULL;
    switch ( scale )
    {
        case 24000:
            pMC = &d_24K;
            break;
        case 25000:
            pMC = &d_24K;
            break;
        case 100000:
            pMC = &d_100K;
            break;
        case 2000000:
            pMC = &d_2M;
            break;
        default:
            // This is not a valid scale! Abort.
            return 0;
    }

    // Check to see if there is only one reference to the module
    if ( 1 == pMC->d_refCount )
    {
        // Last reference, delete the module counter
        delete pMC->d_pModule;
        pMC->d_pModule = NULL;
        pMC->d_refCount = 0;
        return 1;
    }
    else
    {
        // Just decrement the reference counter
        return  ( pMC->d_refCount-- );
    }
}

CString
SDTS_MDEFFactory::getModuleName( const CString& strTitle, const CString& strRegEntryName )
{
    CString strMDIRFilename; 

    // Show a dialog about what MDEF files are
    CString strMsg = "In order to get information about SDTS Elements, the Master Data "
                     "Dictionary must be referenced.  The next dialog will ask you to "
                     "select the Master Data Dictionary Directory (MDIR) file for the scale of "
                     "the data to be viewed.  Once you have successfully selected the MDIR "
                     "module your selection will be stored and you will not be asked again. "
                     "Press OK to continue and make your selection.";
    ::MessageBox( AfxGetMainWnd()->GetSafeHwnd(), strMsg, "MDIR Info", MB_OK | MB_APPLMODAL );

    // Get the MDIR filename from the user
  	CString strFilter( "SDTS Master Data Directory Module (*mdir.ddf)|*mdir.ddf||" );
    CFileDialog openDialog( TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, strFilter);
    openDialog.m_ofn.lpstrTitle = (LPCTSTR)strTitle;

    if ( IDOK == openDialog.DoModal() )
    {
        strMDIRFilename = openDialog.GetPathName();

        // Write the path to the Registry
        AfxGetApp()->WriteProfileString( "", strRegEntryName, strMDIRFilename );
    }

    return strMDIRFilename;
}

bool
SDTS_MDEFFactory::processMDIR( const CString& strMDIRFilename, CString& strMDEFFilename,
                               float& version )
{
    if ( strMDIRFilename.IsEmpty() )
    {
        return false;
    }

    ifstream ddf( strMDIRFilename, ios::binary );

	if ( !ddf )
    {
        return false;
    }

    sio_8211Reader                  reader( ddf );				
	sc_Record	                    record;
    string                          strMDIREntryName;
    sc_FieldCntr::const_iterator    curfield;
    sc_SubfieldCntr::const_iterator cursubfield;    
	for ( sio_8211ForwardIterator iterator( reader ); !iterator.done(); ++iterator )									
    {			
		// Get the next record from the MDIR file
        iterator.get( record );

        // Get the module field, abort if not of the correct type
        if ( !sb_Utils::getFieldByMnem( record, "CATD", curfield ) )
        {
             return false;
        }
  
        // Get the module name
        if ( sb_Utils::getSubfieldByMnem( *curfield, "NAME", cursubfield ) )
        {
            cursubfield->getA( strMDIREntryName );
        }

        // Check for an MDEF module
        if ( "MDEF" == strMDIREntryName )
        {
            // Get the module version
            if ( sb_Utils::getSubfieldByMnem( *curfield, "MVER", cursubfield ) )
            {
                string strVersion;
                cursubfield->getA( strVersion );
                version = atof( strVersion.c_str() );
            }

            // Get the module filename
            if ( sb_Utils::getSubfieldByMnem( *curfield, "FILE", cursubfield ) )
            {
                string strFile;
                cursubfield->getA( strFile );

                // Prepend the MDIR path to the MDEF filename
                strMDEFFilename = getPath( strMDIRFilename );
                strMDEFFilename += strFile.c_str();
            }
        
            // We're done once this is found
            return true;
        }
    }

    return false;
}

void
SDTS_MDEFFactory::getMDEFInfo( const CString& strRegEntryName, const CString& strDialogTitle,
                               CString& strMDEFFilename, float& version )
{
    // The module hasn't been loaded, check to see if a filename for it is
    // stored in the Registry
    CString strMDIRFilename = AfxGetApp()->GetProfileString( "", strRegEntryName, "" );
    while ( !processMDIR( strMDIRFilename, strMDEFFilename, version ) )
    {
        strMDIRFilename = getModuleName( strDialogTitle, strRegEntryName );

        // Abort if the user didn't select a MDIR file
        if ( strMDIRFilename.IsEmpty() )
        {
            version = 0.0;
            break;
        }
    }
}

CString 
SDTS_MDEFFactory::getPath( const CString& strFilename )
{
	int pos;

	// Find the last occurence of the backslash character
	if ( ( pos = strFilename.ReverseFind( '\\' ) ) != -1 )
	{
		return strFilename.Left( pos + 1 );
	}
	else
	{
		return "";
	}
}

UINT
SDTS_MDEFFactory::showVersionError( float moduleVersion, float mdefVersion )
{
    CString strMessage;
    strMessage.Format( "The SDTS transfer references a module with the version number %g "
                       "but the MDEF module you selected has a version of %g.  Would you "
                       "like to select a new MDEF module?", moduleVersion, mdefVersion );
    return AfxMessageBox( strMessage, MB_YESNO );
}