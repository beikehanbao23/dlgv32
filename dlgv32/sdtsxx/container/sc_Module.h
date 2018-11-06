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

#ifndef INCLUDED_SC_MODULE_H
#define INCLUDED_SC_MODULE_H

#include <string>
#include <list>

#ifdef WIN32
   using namespace std;
#endif


#ifndef INCLUDED_SC_RECORD_H
#include "container/sc_Record.h"
#endif


/// Canonical record container type
typedef list<sc_Record> sc_RecordCntr;

class sc_Module : public sc_RecordCntr
{
   // An SDTS Module.

   public:
      
      sc_Module();

      ~sc_Module();

		typedef sc_RecordCntr::iterator iterator;
		typedef sc_RecordCntr::const_iterator const_iterator;

}; // sc_Module

#endif  // INCLUDED_SC_MODULE_H
