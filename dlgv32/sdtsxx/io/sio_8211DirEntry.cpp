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
// sio_8211DirEntry.cpp
//

#include "io/sio_8211DirEntry.h"

#ifndef INCLUDED_SIO_8211LEADER_H
#include "io/sio_8211Leader.h"
#endif

#ifndef INCLUDED_SIO_UTILS_H
#include "io/sio_Utils.h"
#endif


sio_8211DirEntry::sio_8211DirEntry()
                : _fieldLength(0),
                  _fieldPos(0),
                  _field(0),
                  _leader(0)
{
}

sio_8211DirEntry::sio_8211DirEntry(sio_8211Leader & leader)
                : _fieldLength(0),
                  _fieldPos(0),
                  _field(0),
                  _leader( & leader )
{
}

sio_8211DirEntry::sio_8211DirEntry(sio_8211DirEntry const& rhs)
   :  _fieldTag( rhs._fieldTag ), 
      _fieldPos( rhs._fieldPos ), 
      _fieldLength( rhs._fieldLength ),
      _field( rhs._field ), 
      _leader( rhs._leader )
{}

sio_8211DirEntry const&
sio_8211DirEntry::operator=(sio_8211DirEntry const& rhs)
{
   if (&rhs == this)
      return *this;

   _fieldTag      = rhs._fieldTag;
   _fieldPos      = rhs._fieldPos;
   _fieldLength   = rhs._fieldLength;

   _field  = rhs._field;
   _leader = rhs._leader;

   return *this;
}



sio_8211DirEntry::~sio_8211DirEntry()
{}




long
sio_8211DirEntry::getFieldLength() const
{
   return _fieldLength;
}




long
sio_8211DirEntry::getPosition() const
{
   return _fieldPos;
}



string const&
sio_8211DirEntry::getTag() const
{
   return _fieldTag;
}



sio_8211Field const*
sio_8211DirEntry::getField() const
{
   return _field;
}




sio_8211Leader const*
sio_8211DirEntry::getLeader() const
{
   return _leader;
} // sio_8211DirEntry::getLeader



//
// returns how many character positions >= 5 that the
// value will need
//
// XXX must be a more elegant way to do this
static
int
_maxWidth( long value )
{
   int width = 5;

   for ( long max_value = 10000; max_value != 0; max_value /= 10, width-- )
   {
      if ( value / max_value ) return width;
   }

   return ( width ) ? width : 1; // will at least be one character wide
} // _maxWidth



void
sio_8211DirEntry::setFieldLength( long length )
{
   _fieldLength = length;

   long width = _maxWidth( _fieldLength );
   if ( width > _leader->getSizeOfFieldLengthField() )
   {
      _leader->setSizeOfFieldLengthField( width );
   }
} // sio_8211DirEntry::setFieldLength()



void
sio_8211DirEntry::setPosition(long pos)
{
   _fieldPos = pos;

   long width = _maxWidth( _fieldPos );
   if ( width > _leader->getSizeOfFieldPosField() )
   {
      _leader->setSizeOfFieldPosField( width );
   }
} // sio_8211DirEntry::setPosition


void
sio_8211DirEntry::setTag(string const& tag)
{
   _fieldTag = tag;

   if ( _fieldTag.length() > _leader->getSizeOfFieldTagField() )
   {
      _leader->setSizeOfFieldTagField( _fieldTag.length() );
   }
} // sio_8211DirEntry::setTag


void
sio_8211DirEntry::setField(sio_8211Field const* field)
{
   _field = field;
} // sio_8211DirEntry::setField



void
sio_8211DirEntry::setLeader(sio_8211Leader * leader)
{
   _leader = leader;
} // sio_8211DirEntry::setLeader



istream& 
operator>>(istream& istr, sio_8211DirEntry& dirEntry)
{
   // Assumes that istr is positioned on byte 0 of an ISO8211 record directory entry.
   // Reads the directory entry, leaving the stream pointer positioned on the byte
   // after the last byte in the entry.

   long totalLength = dirEntry.getLeader()->getSizeOfFieldLengthField()+ 
                      dirEntry.getLeader()->getSizeOfFieldPosField()+ 
                      dirEntry.getLeader()->getSizeOfFieldTagField();

   char* entryBuffer = new char[totalLength]; // XXX check that we actually got it

   istr.read(entryBuffer, totalLength);
   if ((istr.gcount() < totalLength) || (!istr))
      {
         istr.clear(ios::failbit);
         delete [] entryBuffer;
         return istr;
      }

   long rp = 0;  // relative position
   dirEntry._fieldTag = sio_Utils::getString(entryBuffer,rp,dirEntry.getLeader()->getSizeOfFieldTagField());
   rp = rp + dirEntry.getLeader()->getSizeOfFieldTagField();
   dirEntry._fieldLength = sio_Utils::getLong(entryBuffer,rp,dirEntry.getLeader()->getSizeOfFieldLengthField());
   rp = rp + dirEntry.getLeader()->getSizeOfFieldLengthField();
   dirEntry._fieldPos = sio_Utils::getLong(entryBuffer,rp,dirEntry.getLeader()->getSizeOfFieldPosField());

   delete [] entryBuffer;

   return istr;

} // operator>>



ostream& 
sio_8211DirEntry::streamInsert(ostream& ostr)
{
   // Stuff the directory entry out to the ostream.
   // XXX - The _xxxxSize fields really should be set somewhere, as well as 
   // sanity checked.
   ostr << setw(getLeader()->getSizeOfFieldTagField())      << _fieldTag;
   ostr << setw(getLeader()->getSizeOfFieldLengthField())   << _fieldLength;
   ostr << setw(getLeader()->getSizeOfFieldPosField())      << _fieldPos;
   return ostr;
}


ostream&
operator<<(ostream& ostr, sio_8211DirEntry& dirEntry)
{
   return dirEntry.streamInsert(ostr);
}