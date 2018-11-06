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
// sio_8211DR.cpp
//


#include "io/sio_8211DR.h"


#ifndef INCLUDED_SIO_8211DRLEADER_H
#include "io/sio_8211DRLeader.h"
#endif

#ifndef INCLUDED_SIO_8211DIRENTRY_H
#include "io/sio_8211DirEntry.h"
#endif

#ifndef INCLUDED_SIO_8211DIRECTORY_H
#include "io/sio_8211Directory.h"
#endif




sio_8211DR::sio_8211DR()
          : _reuseLeaderAndDir(false), _wroteDroppedLeaderAndDir(false)
{
   _getDirectory().setLeader( _getLeader() );
}


sio_8211DR::sio_8211DR(sio_8211DRLeader const& leader,
                       sio_8211Directory const& dir)
          : _reuseLeaderAndDir(true), _wroteDroppedLeaderAndDir(false)
{
   setLeader( leader );
   setDirectory( dir );
   _getDirectory().setLeader( _getLeader() );
}



void
sio_8211DR::reuseLeaderAndDirectory(bool flag)
{
   if ( _reuseLeaderAndDir = flag )
   {  // This is harmless if we're reading as the leader identifier
      // should already be set to this value.
      _getLeader().setLeaderIdentifier('R');
   }
}


// If this is set, then the leader and directory will
// not be emitted in streamInsert().  Note that for this
// to happen is like having two keys to open a safe.
// _reuseLeaderAndDir has to be set as well as this flag.
void
sio_8211DR::wroteDroppedLeaderAndDir( bool flag )
{
   _wroteDroppedLeaderAndDir = flag;
} // sio_8211DR::wroteDroppedLeaderAndDir( bool flag )



bool
sio_8211DR::isReusingLeaderAndDirectory() const
{
   return _reuseLeaderAndDir;
}          



// A repeating field is a field that has multiple instances of the same
// field.  When this is invoked, we want to add the raw data contents of 
// the given buffer to the last field, thus making it a repeating field.
// (Although it may already be one if this function was already invoked
// on it.)  We _could_ have just added another field, but that would 
// have wasted space by adding another directory entry and field terminator.
bool
sio_8211DR::addRepeatingField( sio_Buffer const& buffer )
{
   // concatenate the data area of the last field with the new field
   // ( -1 for the field terminator we're going to over-write)

   long new_data_length = _getFieldArea().back().getDataLength() + buffer.length() - 1;
   char* new_data = new char [ new_data_length ];

   // copy over everything but the field terminator
   memcpy( new_data, _getFieldArea().back().getData(), _getFieldArea().back().getDataLength() - 1 );

   // now concatenate the new data
   memcpy( new_data + _getFieldArea().back().getDataLength() - 1, buffer.data(), buffer.length() );

   // now set that field to the new data
   _getFieldArea().back().setData( new_data, new_data_length );

   // make sure that the record's directory is in the loop and knows about
   // fatter field
   _getDirectory().back().setFieldLength( new_data_length );

   delete [] new_data;

   return true;

} // sio_8211DR::addRepeatingField




istream&
sio_8211DR::streamExtract(istream& istr)
{
   if ( ! istr ) { return istr ; } // bail immediately if problem with stream

   // Assume istr is positioned on byte zero of an ISO8211 DR.

   sio_8211DRLeader tmpLeader;

   if (!_reuseLeaderAndDir)
      {
         // Get the leader.
         istr >> tmpLeader;
         if ( ! istr ) { return istr ; } // bail immediately if problem with stream

         // insure that the leader information is set up properly
         setLeader( tmpLeader );

         // Get the directory.
         istr >> _getDirectory();
         if ( ! istr ) { return istr ; } // bail immediately if problem with stream

      }

   // Erase any previous fields.
   _getFieldArea().erase( _getFieldArea().begin(), _getFieldArea().end() );

   // Get the new fields.
   long fieldAreaStart = istr.tellg();

   for ( sio_8211Directory::iterator i = _getDirectory().begin(); 
         i != _getDirectory().end(); 
         i++)
      { 
         istr.seekg(fieldAreaStart + i->getPosition());

         // add a new field of the size that the directory says it has to the
         // field area
         _getFieldArea().push_back(sio_8211Field(i->getFieldLength() - 1));

         istr >> _getFieldArea().back();

         if ( ! istr ) { return istr ; } // bail immediately if problem with stream

         // set the directory's link to its corresponding field.
         i->setField(&_getFieldArea().back());
      }


   if (!_reuseLeaderAndDir)
      {
         _getLeader() = tmpLeader;
      }

   return istr;

} // streamExtract()



ostream& 
sio_8211DR::streamInsert(ostream& ostr)
{
   ostr << setfill('0');


   // Don't blat out the leader and directory if we're in
   // dropped leader and directory mode and we already wrote
   // the dropped leader and directory.

   if ( ! (isReusingLeaderAndDirectory() && _wroteDroppedLeaderAndDir) )
   {
      // insure that the leader is up to date with the record
      _synchLeaderWithRecord( );

      ostr << getLeader();
      ostr << getDirectory();
   }

   ostr << getFieldArea();

   return ostr;

} // sio_8211DR::streamInsert



sio_8211Leader const&
sio_8211DR::getLeader() const
{
   return _leader;
}


sio_8211Leader &
sio_8211DR::_getLeader()
{
   return _leader;
}
