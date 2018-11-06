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
// sio_8211Record.cpp
//

#include "io/sio_8211Record.h"

#ifndef INCLUDED_SIO_8211DIRENTRY_H
#include "io/sio_8211DirEntry.h"
#endif

#ifndef INCLUDED_SIO_8211FIELD_H
#include "io/sio_8211Field.h"
#endif

#ifndef INCLUDED_SIO_8211FIELDAREA_H
#include "io/sio_8211FieldArea.h"
#endif

#include <memory.h>




sio_8211Record::sio_8211Record()
{
}         

sio_8211Record::~sio_8211Record()
{
   // Does nothing. Just here so that we can have a virtual destructor.
}

sio_8211Directory const&
sio_8211Record::getDirectory() const
{
   return _dir;
}



sio_8211Directory &
sio_8211Record::_getDirectory()
{
   return _dir;
} // sio_8211Record::getDirectory


sio_8211FieldArea const&
sio_8211Record::getFieldArea() const
{
   return _fieldArea;
}


sio_8211FieldArea &
sio_8211Record::_getFieldArea()
{
   return _fieldArea;
}


void
sio_8211Record::setLeader( sio_8211Leader const& leader )
{
   _getLeader() = leader; // XXX check for slicing problem
} // sio_8211Record::setLeader()


void
sio_8211Record::setDirectory( sio_8211Directory const& dir )
{
   _dir = dir;
} // sio_8211Record::setDirectory()


void
sio_8211Record::setFieldArea( sio_8211FieldArea const& fieldArea )
{
   _fieldArea = fieldArea;
} // sio_8211Record::setFieldArea




bool
sio_8211Record::addField( string const & tag, sio_8211Field const& field )
{
   // add the field to the field area

   _fieldArea.push_back( field );

   // create a directory entry with the given tag; have it refer to
   // the newly added field

   sio_8211DirEntryContainer::iterator curr_dir_entry = _dir.end();

    // append to list
   curr_dir_entry = _dir.insert( curr_dir_entry, sio_8211DirEntry( _getLeader() ) );

                                    // note that we can use back() reference as we're
                                    // referring to the last element

   _dir.back().setField( &(_fieldArea.back()) ); // make sure directory entry can get to field
   _dir.back().setTag( tag );

   // now set the field positions and lengths

   if ( 1 == _dir.size() )
   {
      _dir.back().setPosition( 0 );
   }
   else
   {
      --curr_dir_entry;    // move to previous directory entry

                           // calculate new position as being the previous directory
                           // entry's position plus that entry's length

      _dir.back().setPosition( 
         curr_dir_entry->getPosition() + curr_dir_entry->getFieldLength() );
   }

   _dir.back().setFieldLength( field.getDataLength() );

   return true;

} // sio_8211Record::addField



bool
sio_8211Record::addField( string const & tag, sio_Buffer const& field_data )
{
   return addField( tag, sio_8211Field( field_data ) );
} // sio_8211Record::addField()




istream&
operator>>(istream& istr, sio_8211Record& record)
{
   return record.streamExtract(istr);
}

ostream&
operator<<(ostream& ostr, sio_8211Record& record)
{
   return record.streamInsert(ostr);
}



// Insure that the given leader has the correct record length and
// field area offsets.
void
sio_8211Record::_synchLeaderWithRecord( )
{
   long length = 24; // initially include the leader itself

   // add the directory size

   length += getDirectory().size() * ( _getLeader().getSizeOfFieldLengthField() +
                                       _getLeader().getSizeOfFieldPosField() +
                                       _getLeader().getSizeOfFieldTagField() );
   // add the field area size

   for ( sio_8211FieldAreaContainer::const_iterator i = getFieldArea().begin();
         i != getFieldArea().end();
         i++ )
   {
      length += i->getDataLength();
   }

   // The obvious question: "Why + 1?" The answer is "Because there's a
   // terminator at the end of the record."
   _getLeader().setRecordLength( length + 1 );

   // XXX but have we included all the field and unit terminators?

   _getLeader().setBaseAddrOfFieldArea( 24 + getDirectory().size() * 
                                  ( _getLeader().getSizeOfFieldLengthField() +
                                    _getLeader().getSizeOfFieldPosField() +
                                    _getLeader().getSizeOfFieldTagField() ) + 1 );

} // _synchLeaderWithRecord


ostream& 
sio_8211Record::streamInsert(ostream& ostr)
{
   // insure that the leader is up to date with the record
   _synchLeaderWithRecord(  );

   ostr << setfill('0');
   ostr << getLeader();
   ostr << getDirectory();
   ostr << getFieldArea();

   return ostr;
} // sio_8211Record::streamInsert()