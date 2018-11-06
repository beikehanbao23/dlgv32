// DoubleByteGridFile.cpp - implementation of DoubleByteGridFile class
//
// Developed by: Mike Childs
//      Started: 3/11/98

#include "DoubleByteGridFile.h"

// Construction
DoubleByteGridFile::DoubleByteGridFile()
: d_hDataFile(INVALID_HANDLE_VALUE), 
  d_hDataFileMapping(NULL),
  d_pDataFileBytes(NULL)
{
}

// Destruction
DoubleByteGridFile::~DoubleByteGridFile()
{
    // Get rid of the file mapping
    if ( NULL != d_pDataFileBytes )
    {
        ::UnmapViewOfFile( d_pDataFileBytes );
    }

    if ( NULL != d_hDataFileMapping )
    {
        ::CloseHandle( d_hDataFileMapping );
    }

    if ( INVALID_HANDLE_VALUE != d_hDataFile )
    {
        ::CloseHandle( d_hDataFile );
    }
}

// Creation
bool
DoubleByteGridFile::create( const char* strFilename )
{
    // Open the data file
    d_hDataFile = ::CreateFile( strFilename, GENERIC_READ, FILE_SHARE_READ,
                                NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

    // Make sure the file was successfully opened
    if ( INVALID_HANDLE_VALUE == d_hDataFile )
    {
        return false;
    }

    // Create a file mapping object for the file
    d_hDataFileMapping = ::CreateFileMapping( d_hDataFile, NULL, PAGE_READONLY, 0, 0, NULL );

    // Make sure the file mapping was successfully created
    if ( NULL == d_hDataFileMapping )
    {
        return false;
    }

    // Map a view of the file
    d_pDataFileBytes = (BYTE*)::MapViewOfFile( d_hDataFileMapping, FILE_MAP_READ, 0, 0, 0 );

    // Make sure the file mapping occurred successfully
    if ( NULL == d_pDataFileBytes )
    {
        return false;
    }
                                               
    return true;
}