// RegistryAccessor.cpp - implementation of RegistryAccessor class
//
// Developed by: Mike Childs
//      Started: 5/2/97
//

#include "RegistryAccessor.h"
#include <string.h>

// BOOL openKey( path, phKey )
// Returns: TRUE if the key was opened successfully, FALSE otherwise
// Function: opens the registry key specified by <path> and puts a
//           handle to it in <phKey>
// NOTE: the handle returned in <phKey> must be closed when you are done with it
BOOL
RegistryAccessor::openKey( const CString& path, HKEY* phKey )
{
	// Get a copy of the path
	CString keyName = path;

	// Trim leading and trailing whitespace from the key name
	keyName.TrimRight();
	keyName.TrimLeft();

	// Find the first occurence of the backslash (\) character
	int pos = keyName.Find( '\\' );
	if ( pos == -1 )
	{
		return FALSE;
	}

	// Open the first key
	HKEY hTempKey;
	CString subString = keyName.Left( pos );
	if ( subString.CompareNoCase( "HKEY_LOCAL_MACHINE" ) == 0 )
	{
		hTempKey = HKEY_LOCAL_MACHINE;
	}
	else if ( subString.CompareNoCase( "HKEY_USERS" ) == 0 )
	{
		hTempKey = HKEY_USERS;
	}
	else if ( subString.CompareNoCase( "HKEY_DYN_DATA" ) == 0 )
	{
		hTempKey = HKEY_DYN_DATA;
	}
	else if ( subString.CompareNoCase( "HKEY_CLASSES_ROOT" ) == 0 )
	{
		hTempKey = HKEY_CLASSES_ROOT;
	}
	else if ( subString.CompareNoCase( "HKEY_CURRENT_USER" ) == 0 )
	{
		hTempKey = HKEY_CURRENT_USER;
	}
	else if ( subString.CompareNoCase( "HKEY_CURRENT_CONFIG" ) == 0 )
	{
		hTempKey = HKEY_CURRENT_CONFIG;
	}
	else
	{
		return FALSE;
	}

	// Lop off the first part of the string
	subString = keyName.Right( keyName.GetLength() - pos - 1 );

	// Loop until we get to the last key
	while ( ( pos = subString.Find( '\\' ) ) != -1 )
	{
		// Get the next subKey name
		CString subName = subString.Left( pos );

		// Lop off the first part of the string
		subString = subString.Right( subString.GetLength() - pos - 1 );

		if ( ::RegCreateKeyEx( hTempKey, subName, 0, NULL, 0, KEY_ALL_ACCESS, NULL, phKey, NULL )
			 != ERROR_SUCCESS )
		{
			::RegCloseKey( hTempKey );
			return FALSE;
		}

		// Close the temporary key
		::RegCloseKey( hTempKey );

		hTempKey = *phKey;
	}

	// Get the last subkey handle
	if ( ::RegCreateKeyEx( hTempKey, subString, 0, NULL, 0, KEY_ALL_ACCESS, NULL, phKey, NULL )
		 != ERROR_SUCCESS )
	{
		::RegCloseKey( hTempKey );
		return FALSE;
	}

	ASSERT( phKey != NULL );
	return TRUE;
}

// BOOL setRegistryKey( path, name, val )
// Returns: TRUE if successful, false otherwise
// Function: Places <val> into the registry key specified by <path>:<name>
BOOL
RegistryAccessor::setRegistryKey( const CString& path, const CString& name, DWORD val )
{
	// Get the handle to the key specified by <path>
	HKEY hKey;
	if ( !openKey( path, &hKey ) )
	{
		return FALSE;
	}

	// Get the value
	if ( ::RegSetValueEx( hKey, name, 0, REG_DWORD, (BYTE*)(&val), sizeof(DWORD) )
		 == ERROR_SUCCESS )
	{
		// Close the key
		::RegCloseKey( hKey );
		return TRUE;
	}
	else
	{
		// Close the key
		::RegCloseKey( hKey );
		return FALSE;
	}
}
	
// BOOL setRegistryKey( path, name, val )
// Returns: TRUE if successful, false otherwise
// Function: Places <val> into the registry key specified by <path>:<name>
BOOL
RegistryAccessor::setRegistryKey( const CString& path, const CString& name, const CString& val )
{
	// Get the handle to the key specified by <path>
	HKEY hKey;
	if ( !openKey( path, &hKey ) )
	{
		return FALSE;
	}

	// Get the value
	DWORD size = sizeof(char) * ( val.GetLength() + 1 );
	char* temp = new char[val.GetLength() + 1];
	strcpy( temp, val );
	if ( ::RegSetValueEx( hKey, name, 0, REG_SZ, (BYTE *)temp, size )
		 == ERROR_SUCCESS )
	{
		// Deallocate string
		delete[] temp;

		// Close the key
		::RegCloseKey( hKey );
		return TRUE;
	}
	else
	{
		// Deallocate string
		delete[] temp;

		// Close the key
		::RegCloseKey( hKey );
		return FALSE;
	}
}
	
// BOOL getRegistryKey( path, name, val, def )
// Returns: TRUE if successful, false otherwise
// Function: Places the value of the registry key specified by 
//           <path>:<name> into <val>.  If the registry key cannot be accesses,
//			 <def> is placed into <val>.
BOOL
RegistryAccessor::getRegistryKey( const CString& path, const CString& name, CString& val, 
								  const CString& def )
{
	// Get the handle to the key specified by <path>
	HKEY hKey;
	if ( !openKey( path, &hKey ) )
	{
		val = def;
		return FALSE;
	}

	// Get the size of the value
	DWORD size;
	DWORD type;
	if ( ::RegQueryValueEx( hKey, name, NULL, &type, NULL, &size ) != ERROR_SUCCESS )
	{
		// Use the default value
		val = def;

		// Close the key
		::RegCloseKey( hKey );
		return FALSE;
	}

	// Check to make sure the value is a string
	if ( type != REG_SZ )
	{
		// Use the default value
		val = def;

		// Close the key
		::RegCloseKey( hKey );
		return FALSE;
	}

	// Get the value
	char* temp = new char[size];
	if ( ::RegQueryValueEx( hKey, name, NULL, &type, (BYTE*)temp, &size )
		 == ERROR_SUCCESS )
	{
		val = temp;

		// Deallocate the string
		delete[] temp;

		// Close the key
		::RegCloseKey( hKey );
		return TRUE;
	}
	else
	{
		// Use the default value
		val = def;

		// Deallocate the string
		delete[] temp;

		// Close the key
		::RegCloseKey( hKey );
		return FALSE;
	}
}

// BOOL getRegistryKey( path, name, val, def )
// Returns: TRUE if successful, false otherwise
// Function: Places the value of the registry key specified by 
//           <path>:<name> into <val>.  If the registry key cannot be accesses,
//			 <def> is placed into <val>.
BOOL
RegistryAccessor::getRegistryKey( const CString& path, const CString& name, DWORD& val, 
								  const DWORD& def )
{
	// Get the handle to the key specified by <path>
	HKEY hKey;
	if ( !openKey( path, &hKey ) )
	{
		return FALSE;
	}

	// Get the size of the value
	DWORD size;
	DWORD type;
	if ( ERROR_SUCCESS != ::RegQueryValueEx( hKey, name, NULL, &type, NULL, &size ) )
	{
		// Use the default value
		val = def;

		// Close the key
		::RegCloseKey( hKey );
		return FALSE;
	}

	// Check to make sure the value is a DWORD
	if ( REG_DWORD != type )
	{
		// Use the default value
		val = def;

		// Close the key
		::RegCloseKey( hKey );
		return FALSE;
	}

	// Get the value
	if ( ::RegQueryValueEx( hKey, name, NULL, &type, (BYTE *)(&val), &size )
		 == ERROR_SUCCESS )
	{
		ASSERT( type == REG_DWORD );

		// Close the key
		::RegCloseKey( hKey );
		return TRUE;
	}
	else
	{
		// Use the default value
		val = def;

		// Close the key
		::RegCloseKey( hKey );
		return FALSE;
	}
}
