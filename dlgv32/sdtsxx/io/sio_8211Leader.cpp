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

#ifndef INCLUDED_SIO_8211LEADER_H
#include "io/sio_8211Leader.h"
#endif

sio_8211Leader::sio_8211Leader()
              : _recLength(0),
                _fieldAreaStart(0),
                _sizeFieldLength(0),
                _sizeFieldPos(0),
                _sizeFieldTag(0)
{
}

sio_8211Leader::~sio_8211Leader()
{

}


sio_8211Leader const &
sio_8211Leader::operator=( sio_8211Leader const & rhs )
{
   if ( &rhs == this ) return *this;

   _recLength        = rhs._recLength;
   _leaderIden       = rhs._leaderIden;
   _fieldAreaStart   = rhs._fieldAreaStart;
   _sizeFieldLength  = rhs._sizeFieldLength;
   _sizeFieldPos     = rhs._sizeFieldPos;
   _sizeFieldTag     = rhs._sizeFieldTag;

   return *this;
} // operator=()



long
sio_8211Leader::getRecordLength() const
{
   return _recLength;
}

void
sio_8211Leader::setRecordLength(long length)
{
   _recLength = length;
}

char
sio_8211Leader::getLeaderIdentifier() const
{
   return _leaderIden;
}

void
sio_8211Leader::setLeaderIdentifier(char identifier)
{
   _leaderIden = identifier;
}

long
sio_8211Leader::getBaseAddrOfFieldArea() const
{
   return _fieldAreaStart;
}

void
sio_8211Leader::setBaseAddrOfFieldArea(long base)
{
   _fieldAreaStart = base;
}

long
sio_8211Leader::getSizeOfFieldLengthField() const
{
   return _sizeFieldLength;
}

void
sio_8211Leader::setSizeOfFieldLengthField(long size)
{
   _sizeFieldLength = size;
}

long
sio_8211Leader::getSizeOfFieldPosField() const
{
   return _sizeFieldPos;
}

void
sio_8211Leader::setSizeOfFieldPosField(long size)
{ 
   _sizeFieldPos = size;
}

long
sio_8211Leader::getSizeOfFieldTagField() const
{
   return _sizeFieldTag;
}

void
sio_8211Leader::setSizeOfFieldTagField(long size)
{
   _sizeFieldTag = size;
}

istream&
operator>>(istream& istr, sio_8211Leader& leader)
{
   return leader.streamExtract(istr);
}

ostream&
operator<<(ostream& ostr, sio_8211Leader const& leader)
{
   return leader.streamInsert(ostr);
}
