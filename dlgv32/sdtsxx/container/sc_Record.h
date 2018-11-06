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

#ifndef INCLUDED_SC_RECORD_H
#define INCLUDED_SC_RECORD_H

#include <list>


#include "container/sc_Field.h"


#ifdef WIN32
   using namespace std;
#endif

/// Canonical field container
typedef list<sc_Field> sc_FieldCntr;


class sc_Record : public sc_FieldCntr
{
   public:
      
		typedef sc_FieldCntr::iterator iterator;
		typedef sc_FieldCntr::const_iterator const_iterator;

      sc_Record();
      explicit sc_Record( int size );

      ~sc_Record();

}; // sc_Record


#endif  // INCLUDED_SC_RECORD_H
