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
// sio_8211DDR.cpp
//


#include "io/sio_8211DDR.h"


#ifndef INCLUDED_SIO_8211DDRLEADER_H
#include "io/sio_8211DDRLeader.h"
#endif

#ifndef INCLUDED_SIO_8211DIRENTRY_H
#include "io/sio_8211DirEntry.h"
#endif

#ifndef INCLUDED_SIO_8211DIRECTORY_H
#include "io/sio_8211Directory.h"
#endif


sio_8211DDR::sio_8211DDR()
{
   _getDirectory().setLeader( _leader );
}


istream&
sio_8211DDR::streamExtract(istream& istr)
{
   // Assume istr is positioned on byte zero of an ISO8211 DDR.

   // Get the leader.
   istr >> _getLeader();

   sio_8211DDRLeader& ddrLeader = static_cast<sio_8211DDRLeader&>(_getLeader()); // reference for convenience

   // Get the directory.
   istr >> _getDirectory();

   // Get the fields. 
   long fieldAreaStart = ddrLeader.getBaseAddrOfFieldArea();

   for ( sio_8211Directory::iterator i = _getDirectory().begin(); 
         i != _getDirectory().end(); 
         i++ )
      { 
         istr.seekg(fieldAreaStart + i->getPosition());

         string fieldTag = i->getTag();

         // note that when we add this new field to the field area, we
         // set its length to be one less than what the directory says
         // its length is -- this is to clip the field terminator, which
         // we don't want to keep around

         _getFieldArea().push_back(sio_8211Field(i->getFieldLength() - 1));

#if 0
         // XXX Dealing with special fields. Yuck.
         if (fieldTag.substr(0,3) == "000")  // It's a reserved tag. 
            {
               _fieldArea.push_back(new sio_8211Field((*i)->getFieldLength() - 1));
            }
         else
            {
               // Assume it's a Data Descriptive Field.
               _fieldArea.push_back(new sio_8211DDRField(*ddrLeader,
                                                         (*i)->getFieldLength() - 1));
            }
#endif

         istr >> _getFieldArea().back();
         i->setField( &(_getFieldArea().back()) );
      }

   return istr;
} // sio_8211DDR::streamExtract(istream& istr)



sio_8211Leader const&
sio_8211DDR::getLeader() const
{
   return _leader;
}


sio_8211Leader &
sio_8211DDR::_getLeader()
{
   return _leader;
}
