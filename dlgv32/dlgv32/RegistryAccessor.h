// RegistryAccessor.h - interface for RegistryAccessor class
//
// Developed by: Mike Childs
//      Started: 5/2/97
//

#ifndef _REGISTRYACCESSOR_H_
#define _REGISTRYACCESSOR_H_

#include "StdAfx.h"

class RegistryAccessor
{
public:
	static BOOL getRegistryKey( const CString& path,
					const CString& name, DWORD& val, const DWORD& def );
	static BOOL getRegistryKey( const CString& path,
					const CString& name, CString& val, const CString& def );
	static BOOL setRegistryKey( const CString& path,
					const CString& name, DWORD val );
	static BOOL setRegistryKey( const CString& path,
					const CString& name, const CString& val );

protected:
	static BOOL openKey( const CString& path, HKEY* phKey );
};

#endif