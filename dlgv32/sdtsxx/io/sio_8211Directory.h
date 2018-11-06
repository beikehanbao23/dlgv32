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
// sio_8211Directory.h
//

#ifndef INCLUDED_SIO_8211DIRECTORY_H
#define INCLUDED_SIO_8211DIRECTORY_H


#ifdef WIN32
#include <iostream>
#include <list>
   using namespace std;
#else
#include <iostream.h>
#include <list.h>
#endif


#ifndef INCLUDED_SIO_8211LEADER_H
#include "io/sio_8211Leader.h"
#endif

#ifndef INCLUDED_SIO_8211DIRENTRY_H
#include "io/sio_8211DirEntry.h"
#endif

#ifndef INCLUDED_SIO_8211UTILS_H
#include "io/sio_8211Utils.h"
#endif




typedef list<sio_8211DirEntry> sio_8211DirEntryContainer;

class sio_8211Directory;
istream& operator>>(istream& istr, sio_8211Directory& dir);
ostream& operator<<(ostream& ostr, sio_8211Directory const& dir);


class sio_8211Directory : public sio_8211DirEntryContainer
{
   public:
      sio_8211Directory(); // XXX experimentally public

      explicit sio_8211Directory(sio_8211Leader & leader);
         // The leader is required to determine the widths of the various
         // subfields in a directory entry. Once the values are determined,
         // the leader is no longer required (may be deleted).
         // XXX synch comment with new sio_8211Leader reality

      // Does a 'deep copy' of the directory contents.
      sio_8211Directory const& operator=(sio_8211Directory const& rhs);

      friend istream& operator>>(istream& istr, sio_8211Directory& dir);
      friend ostream& operator<<(ostream& ostr, sio_8211Directory const& dir);

      void setLeader( sio_8211Leader & leader ) { _leader = &leader; }

   private:

      sio_8211Directory(sio_8211Directory const& dir); // ditto

      // the leader, which is stored in the encompassing sio_8211Record,
      // contains formatting information used to read and write directory
      // entries
      //
      // writable because adding directory entries might change the width values
      sio_8211Leader * _leader;

}; // sio_8211Directory 



#endif  // INCLUDED_SIO_8211DIRECTORY_H
