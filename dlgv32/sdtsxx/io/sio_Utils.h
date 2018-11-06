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

#ifndef INCLUDED_SIO_UTILS_H
#define INCLUDED_SIO_UTILS_H


#ifdef WIN32
#include <string>
   using namespace std;
#else
#include <string.h>
#endif

class sio_Utils
{
   public:
      
      static long getLong(char const* buf, long startpos, long length);

      static string getString(char const* buf, long startpos, long length);

   private:
      sio_Utils();
};

#endif  // INCLUDED_SIO_UTILS_H
