//
// sio_8211Field.cpp
//

#include <string.h>


#ifndef INCLUDED_SIO_8211FIELD_H
#include "io/sio_8211Field.h"
#endif

#ifndef INCLUDED_SIO_8211DIRENTRY_H
#include "io/sio_8211DirEntry.h"
#endif

#ifndef INCLUDED_SIO_8211DDRLEADER_H
#include "io/sio_8211DDRLeader.h"
#endif

#ifndef INCLUDED_SIO_8211UTILS_H
#include "io/sio_8211Utils.h"
#endif


sio_8211Field::sio_8211Field()
             : _data(0),
               _dataLength(0)
{
   // XXX Supplied just because the VC++ 5.0 STL stuff needs one. -- jamie
}               

sio_8211Field::sio_8211Field(long fieldSize)
             : _data(0),
               _dataLength(fieldSize)
{

}

sio_8211Field::sio_8211Field( sio_Buffer const& buffer )
   : _data(0), _dataLength(0)
{
   setData( buffer.data(), buffer.length() );
}



sio_8211Field::sio_8211Field(sio_8211Field const& rhs)
             : _data(0),
               _dataLength(0)
{
   operator=(rhs);
}

sio_8211Field const&
sio_8211Field::operator=(sio_8211Field const& rhs)
{
   if (this == &rhs)
      return *this;

   setData(rhs._data, rhs._dataLength);

   return *this;
}

sio_8211Field::~sio_8211Field()
{
   delete _data;
}

long
sio_8211Field::getDataLength() const
{
   return _dataLength;
}

char const*
sio_8211Field::getData() const
{
   return _data;
}

bool
sio_8211Field::setData(char const* data, long dataLength)
{
   delete [] _data;
   _data = 0;

   _dataLength = dataLength;
   
   if ((_dataLength > 0) && (data != 0))
      {
         _data = new char[_dataLength];
         memcpy(_data,data,_dataLength);
      }

   return true;
}

bool
sio_8211Field::getVariableSubfield(char* value,
                                   long& startPos,
                                   char delim) const
{
   // Attempt to extract a character subfield, terminated by delim.
   // XXX This should probably accept a length argument for 'value' so 
   // XXX we don't overfill it.

   char* tmpbuf = new char[_dataLength];  // We know it won't be longer than this.
   long numchars = 0;
   long pos;
   if ((startPos >= 0) && (startPos < _dataLength))
      pos = startPos;
   else
      return false;

   while ((pos < _dataLength) && (_data[pos] != delim))
      {
         tmpbuf[numchars] = _data[pos];
         numchars++;
         pos++;
      }

   tmpbuf[numchars] = 0;
   strcpy(value, tmpbuf);
   startPos = startPos + numchars + 1;

   delete [] tmpbuf;

   return true;
} // sio_8211Field::getVariableSubfield.


istream&
sio_8211Field::streamExtract(istream& istr)
{
   // Assume istr is positioned on byte zero of a field.

   // XXX We need some error checking here.
   delete _data;
   _data = new char[_dataLength];
   istr.read(_data,_dataLength);

   if (istr)
      {
         // Gobble up field terminator.
         char tempChar;
         istr.get(tempChar);

         // If we don't have a field terminator, then there's something
         // seriously wrong.  Set the stream's bad bit.
         if ( sio_8211FieldTerminator != tempChar )
         {
            istr.setf( ios::badbit );
#ifdef DEBUG
            cerr << __FILE__ << ":" << __LINE__ 
                 << " extra character before terminator at offset "
                 << istr.tellg() << "\n";
#endif
         }


      }

   return istr;  
}  // sio_8211Field::streamExtract



ostream&
sio_8211Field::streamInsert(ostream& ostr) const
{

   // Assume istr is positioned at the start of where this field 
   // should be written.

   ostr.write(_data, _dataLength);

   return ostr;
} // sio_8211Field::streamInsert



sio_Buffer
sio_8211Field::getField() const
{
   return sio_Buffer( getData(), getDataLength() );
}


istream&
operator>>(istream& istr, sio_8211Field& field)
{
   return field.streamExtract(istr);
}




ostream&
operator<<(ostream& ostr, sio_8211Field const& field)
{
   return field.streamInsert(ostr);
}



