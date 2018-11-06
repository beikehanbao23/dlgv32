// DoubleByteGridFile.h - interface for DoubleByteGridFile class
//
// Developed by: Mike Childs
//      Started: 3/11/98

#ifndef _DOUBLEBYTEGRIDFILE_H_
#define _DOUBLEBYTEGRIDFILE_H_

#include "StdAfx.h"

class DoubleByteGridFile
{
public:
  // Construction/Destruction
  DoubleByteGridFile();
  virtual ~DoubleByteGridFile();

  // Creation
  bool create( const CString& strFilename );

  // Access
  short getBigEndianValue( unsigned long index ) const;
  short getLittleEndianValue( unsigned long index ) const;

private:
  // File mapping data members
  HANDLE d_hDataFile;
  HANDLE d_hDataFileMapping;
  BYTE*  d_pDataFileBytes;
};

inline short
DoubleByteGridFile::getBigEndianValue( unsigned long index ) const
{
  short elev;
  BYTE* pElevBytes = reinterpret_cast<BYTE*>( &elev );
  index *= 2;
  pElevBytes[0] = d_pDataFileBytes[index + 1];
  pElevBytes[1] = d_pDataFileBytes[index];
  return elev;
}

inline short
DoubleByteGridFile::getLittleEndianValue( unsigned long index ) const
{
  short elev;
  BYTE* pElevBytes = reinterpret_cast<BYTE*>( &elev );
  index *= 2;
  pElevBytes[0] = d_pDataFileBytes[index];
  pElevBytes[1] = d_pDataFileBytes[index + 1];
  return elev;
}

#endif