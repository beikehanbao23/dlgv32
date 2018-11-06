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
// sio_8211DirEntry.h
//

#ifndef INCLUDED_SIO_8211DIRENTRY_H
#define INCLUDED_SIO_8211DIRENTRY_H

#ifdef WIN32
#include <iostream>
#include <iomanip>
#include <string>
   using namespace std;
#else
#include <iostream.h>
#include <iomanip.h>
#include <string.h>
#endif

class sio_8211Leader;
class sio_8211Field;

class sio_8211DirEntry;
istream& operator>>(istream& istr, sio_8211DirEntry& dirEntry);
ostream& operator<<(ostream& ostr, sio_8211DirEntry& dirEntry);

class sio_8211DirEntry
{
   // An ISO8211 Directory Entry.

   public:

      sio_8211DirEntry();
         // You can't really construct a valid DirEntry without a leader. This ctor
         // allows sio_8211DirEntry to be stored in an STL container.

      sio_8211DirEntry(sio_8211Leader & leader);
         // The leader is required to determine the widths of the various
         // subfields in a directory entry. Once the values are determined,
         // the leader is no longer required (may be deleted).

      sio_8211DirEntry(sio_8211DirEntry const& dirEntry);
      sio_8211DirEntry const& operator=(sio_8211DirEntry const& rhs);

      ~sio_8211DirEntry();

      // We keep a ptr to the field we describe. We do _not_ own it.
      sio_8211Field const* getField() const;
      void                 setField(sio_8211Field const* field);

      // We keep a ptr to the leader we need for sizes. We do _not_ own it.
      sio_8211Leader const*   getLeader() const;
      void                    setLeader(sio_8211Leader * leader);

      void setPosition(long pos);
      void setFieldLength( long length );
      void setTag(string const& tag);

      long           getFieldLength() const;
      long           getPosition() const;
      string const&  getTag() const;
      
      ostream& streamInsert(ostream& ostr);

      friend istream& operator>>(istream& istr, sio_8211DirEntry& dirEntry);
      friend ostream& operator<<(ostream& ostr, sio_8211DirEntry& dirEntry);

   private:

      long     _fieldLength;
      long     _fieldPos;
      string   _fieldTag;

      sio_8211Field const* _field;     // pointer to corresponding field

      sio_8211Leader * _leader;        // pointer to corresponding leader
                                       // leader's widths changed dynamically
                                       // with each sio_8211DirEntry::set*()

}; // class sio_8211DirEntry




#endif  // INCLUDED_SIO_8211DIRENTRY_H
