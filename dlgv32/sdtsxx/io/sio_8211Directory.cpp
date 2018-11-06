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
// sio_8211Directory.cpp
//


#include "io/sio_8211Directory.h"

#ifndef INCLUDED_SIO_8211DIRENTRY_H
#include "io/sio_8211DirEntry.h"
#endif

#ifndef INCLUDED_SIO_8211UTILS_H
#include "io/sio_8211Utils.h"
#endif


#include <algorithm>



sio_8211Directory::sio_8211Directory()
   : _leader( 0 )
{
}


sio_8211Directory::sio_8211Directory(sio_8211Leader & leader)
   : _leader( &leader )
{
}

sio_8211Directory::sio_8211Directory(sio_8211Directory const& rhs )
   : _leader( rhs._leader )
{
   assign( rhs.begin(), rhs.end() );
}


sio_8211Directory const&
sio_8211Directory::operator=(sio_8211Directory const& rhs)
{
   if (&rhs == this)
   {
      return *this;
   }

   assign( rhs.begin(), rhs.end() );

   _leader = rhs._leader;

   return *this;
} // operator=()



istream& operator>>(istream& istr, sio_8211Directory& dir)
{
   // First, make sure that we're starting with a clean directory.
   dir.erase( dir.begin(), dir.end() );


   // Read in the individual directory entries. Assumes the stream is positioned
   // on byte 0 of the first directory entry.

   while ((istr.peek() != sio_8211FieldTerminator) && (istr))
      {
         dir.push_back(  sio_8211DirEntry( )  );
         dir.back().setLeader( dir._leader );
         istr >> dir.back();
      }

   if (istr)
      {
         // Gobble up the field terminator at the end of the directory.
         char tempChar;
         istr.get(tempChar);
      }

   return istr;
} // operator>>




ostream& operator<<(ostream& ostr, sio_8211Directory const& dir)
{
//   long PositionCounter = 0;
   sio_8211Directory foo = dir;

   for(sio_8211DirEntryContainer::iterator dirIterator = foo.begin();
       dirIterator != foo.end(); dirIterator++)
      {
         // Set the position of the field to the sum of the sizes of the fields that have
         // come before it.
//         dirIterator->setPosition(PositionCounter);

         // Add the size of the field to the sum to be ready for the next DirEntry.
//         PositionCounter = PositionCounter + dirIterator->getFieldLength();

         // Write out the directory entry.
         ostr << *dirIterator;
      }

   // Write a field terminator to end the directory area.
   ostr << sio_8211FieldTerminator;

   // write out field data area
   return ostr;

} // operator<<