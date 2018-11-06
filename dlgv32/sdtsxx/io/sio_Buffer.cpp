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
// sio_Buffer.cpp
//

#include "io/sio_Buffer.h"


#include <memory.h>
#include <math.h>



//
// Implementation for sio_Buffer.
//


class sio_BufferImp
{
public:

   sio_BufferImp() : _buffer(0), _length(0), _size(0) {}

   sio_BufferImp( const char* data, long length ) 
      : _buffer(0), _length(0), _size(0) 
   {
      write( data, length );
   }

   sio_BufferImp( sio_BufferImp const & rhs )
      : _buffer(0), _length( 0 ), _size( 0 )
   {
      if ( _size = rhs._size )
      {
         _buffer = new char[_size];

         if ( _length = rhs._length )
         {
            memcpy( _buffer, rhs._buffer, _length );
         }

      }
   }

   ~sio_BufferImp() // { reset(); }
   { 
      if (_buffer) 
      { 
         delete [] _buffer; 
         _buffer = 0; 
         _length = 0; 
         _size   = 0;
      }
   }

   bool reset() 
   { 
//      if (_buffer) 
//      { 
//         delete [] _buffer; 
//         _buffer = 0; 
         _length = 0; 
//         _size   = 0;
//      }
      return true;
   }

   const char* data() const { return _buffer; }

   long length() const { return _length; }

   bool write( char const* data, long length ) 
   { 
 
      if ( _size < _length + length )
      {
         if ( ! grow( length ) ) return false;
      }

      memcpy( _buffer + _length, data, length ); 

      _length += length;

      return true;
   }


   bool write( char data )
   {
      return write( &data, 1 );
   }

private:

   // increase the internal buffer by "increment" -- but do so in 
   // _growthFactor sized chunks
   bool grow( long increment )
   {
      // calculate new buffer size, which should accomodate the increment --
      // but grow in _growthFactor multiples

      // shut off stupid whining about double to long conversion -- this is
      // innocuous
#ifdef WIN32
#pragma warning(disable : 4244)
#endif

      // XXX I think there might be a better way to do this; but this works.
//      long new_size = _growthFactor * ceil((_size + increment) / _growthFactor + 0.5);

      // XXX This is a quick and dirty hack, based solely on my "top of my head" 
      // XXX guesstimates, but it improves performance by a factor of over 100 for
      // XXX a few pathelogical cases.
      long new_size = _ps * ((_size + increment)/_ps + 1) * _growth;

      // XXX Bounds Checker asserts that a memory leak starts here.  I don't
      // XXX think so!      
      char * new_buffer = new char[new_size];

      if ( ! new_buffer ) return false;

      memcpy( new_buffer, _buffer, _length ); // XXX add checking here

      delete [] _buffer;

      _buffer = new_buffer;
      _size   = new_size;

      return true;
   }

//   static const long _growthFactor;
   static const long _ps;
   static const float _growth;
   
   operator=( sio_BufferImp const & ); // NOT NEEDED

   char * _buffer;
   long _size;       // total buffer size
   long _length;     // length of actual data

}; // sio_BufferImp

// amount to grow buffer by every time we need to add more to it
//const long sio_BufferImp::_growthFactor = 16;

// The page size, in bytes.
const long sio_BufferImp::_ps = 16;

// The ammount of space to allocate in the buffer during reallocation. 1.0 would be
// no expansion (100%), while 1.125 allocates an extra 12.5% towards future usage.
const float sio_BufferImp::_growth = 1.125;


sio_Buffer::sio_Buffer()
: _imp( new sio_BufferImp() )
{
} // sio_Buffer ctor

sio_Buffer::sio_Buffer( const char* data, long length )
: _imp( new sio_BufferImp( data, length ) )
{
} // sio_Buffer ctor


sio_Buffer::sio_Buffer( sio_Buffer const& rhs )
: _imp( new sio_BufferImp( *rhs._imp ) )
{
} // sio_Buffer copy ctor



sio_Buffer::~sio_Buffer()
{
   delete _imp;
} //sio_Buffer dtor



bool
sio_Buffer::addData(char const* data, long length)
{
   return _imp->write( data, length );
} // sio_Buffer::addData


bool
sio_Buffer::addData(char data)
{
   return _imp->write( data );
} // sio_Buffer::addData



bool
sio_Buffer::reset()
{
   return _imp->reset();
} // sio_Buffer::reset


const char* 
sio_Buffer::data() const
{
   return _imp->data();
} // sio_Buffer::data



long
sio_Buffer::length() const
{
   return _imp->length();
} // sio_Buffer::length
