//
// This file is part of the SDTS++ toolkit, written by the U.S.
// Geological Survey.  It is experimental software, written to support
// USGS research and cartographic data production.
// 
// SDTS++ is public domain software.  It may be freely copied,
// distributed, and modified.  The USGS welcomes user feedback, but makes
// no committment to any level of support for this code.  See the SDTS
// web site at http://mcmcweb.er.usgs.gov/sdts for more information,
// including points of contact.
//
//
// sio_8211Field.h
//

#ifndef INCLUDED_SIO_8211FIELD_H
#define INCLUDED_SIO_8211FIELD_H


#ifdef WIN32
#include <iostream>
#include <string>
   using namespace std;
#else
#include <iostream.h>
#include <string.h>
#endif

#ifndef INCLUDED_SIO_8211UTILS_H
#include "io/sio_8211Utils.h"
#endif

#ifndef INCLUDED_SIO_BUFFER_H
#include "io/sio_Buffer.h"
#endif


class sio_8211DirEntry;
class sio_8211DDRLeader;

class sio_8211Field;
istream& operator>>(istream& istr, sio_8211Field& field);
ostream& operator<<(ostream& ostr, sio_8211Field const& field);

class sio_8211Field
{
   // This represents a generic ISO 8211 field.

   public:

      sio_8211Field();

      explicit sio_8211Field(long fieldSize);
         // fieldSize is the size of this field, in bytes.

      sio_8211Field( sio_Buffer const& buffer );

      sio_8211Field(sio_8211Field const& rhs);

      sio_8211Field const& operator=(sio_8211Field const& rhs);

      virtual ~sio_8211Field();


      // All fields have two things we're interested in... the raw data it contains,
      // and how much of that data there is.

      long getDataLength() const;

      char const* getData() const;


      bool setData(char const* data, long dataLength);
         // Sets the contents of the field. A copy of 'data' is made.


      // All getVariableSubfield() operations attempt to extract a variable width
      // value. By default, the variable width subfield delimeter is the ISO8211 
      // Unit Terminator. This can be overridden.

      // Value should refer to a buffer that's allocated enough space to hold
      // the subfield, in the case of the char*.  'startPos' should indicate 
      // where in the field's data area the subfield starts.  It will be changed
      // to refer to the next position in the field's data area; this will
      // either be the first byte of the next subfield, or one past the last
      // byte of the field's data area.

      bool getVariableSubfield(char* value,
                               long& startPos,
                               char delim = sio_8211UnitTerminator) const;

      // returns the data area
      sio_Buffer getField() const;

      friend istream& operator>>(istream& istr, sio_8211Field& field);
      friend ostream& operator<<(ostream& ostr, sio_8211Field const& field);

   protected:

      long _dataLength; // XXX this should be replaced by safer sio_Buffer
      char* _data;

      virtual istream& streamExtract(istream& istr);
      virtual ostream& streamInsert(ostream& ostr) const;
};



#endif  // INCLUDED_SIO_8211FIELD_H
