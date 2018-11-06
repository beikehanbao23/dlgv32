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

#include <stdlib.h>
#include <string.h>


#ifndef INCLUDED_SIO_UTILS_H
#include "io/sio_Utils.h"
#endif

long
sio_Utils::getLong(char const* buf, long startpos, long length)
{
   // XXX There's probably a better way to do this, but I don't see it right now.

   char* tempBuf = new char[length+1];

   strncpy(tempBuf, buf + startpos, length);
   tempBuf[length] = '\0';

   long result = atol(tempBuf);

   delete tempBuf;

   return result;
}

string
sio_Utils::getString(char const* buf, long startpos, long length)
{
   char* tempBuf = new char[length+1];

   strncpy(tempBuf, buf + startpos, length);
   tempBuf[length] = '\0';

   string result = tempBuf;

   delete tempBuf;

   return result;
}