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

#ifndef INCLUDED_SIO_8211FIELDAREA_H
#include "io/sio_8211FieldArea.h"
#endif

ostream&
sio_8211FieldArea::streamInsert(ostream& ostr) const
{
   sio_8211FieldArea foo = *this;

	// Create a basic iterator to step through the field area.
   for(sio_8211FieldAreaContainer::iterator areaIterator = foo.begin();
       areaIterator != foo.end(); areaIterator++)
      {
         // Write out the field entry.
         ostr << *areaIterator;
      }

   return ostr;
}

ostream& operator<<(ostream& ostr, sio_8211FieldArea const& area)
{
   return area.streamInsert(ostr);
}
