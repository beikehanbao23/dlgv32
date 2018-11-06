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
// sio_8211DDRLeader.h


#ifndef INCLUDED_SIO_8211DDRLEADER_H
#define INCLUDED_SIO_8211DDRLEADER_H

#ifdef WIN32
#include <iostream>
#include <iomanip>
   using namespace std;
#else
#include <iostream.h>
#include <iomanip.h>
#endif


#ifndef INCLUDED_SIO_8211LEADER_H
#include "sio_8211Leader.h"
#endif


class sio_8211DDRLeader : public sio_8211Leader  
{
   public:
	   sio_8211DDRLeader();
	   ~sio_8211DDRLeader();

      long getFieldControlLength() const;

   private:

      // all these are set either in the ctor or through streamExtract()
      char _interchangeLevel;
      char _inlineCodeExtensionIndicator;
      char _versionNumber;
      char _appIndicator;
      long _fieldControlLength;

      istream& streamExtract(istream& istr);
      ostream& streamInsert(ostream& ostr) const;

}; // class sio_8211DDRLeader


#endif  // INCLUDED_SIO_8211DDRLEADER_H

