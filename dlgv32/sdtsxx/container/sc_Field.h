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
// sc_Field.h: interface for the sc_Field class.
//
//////////////////////////////////////////////////////////////////////

#if !defined INCLUDED_SC_FIELD_H
#define INCLUDED_SC_FIELD_H

#include <list>

#ifdef WIN32
   using namespace std;
#endif



#ifndef INCLUDED_SC_SUBFIELD_H
#include "container/sc_Subfield.h"
#endif


/// Canonical library type for containing subfields.
typedef list<sc_Subfield> sc_SubfieldCntr;


class sc_Field : public sc_SubfieldCntr
{
   public:

		typedef sc_SubfieldCntr::iterator iterator;
		typedef sc_SubfieldCntr::const_iterator const_iterator;

      sc_Field();
	   ~sc_Field();

     // Accessors
     string const& getName() const;
        // Returns the SDTS Name of this field (if one has been set).
     string const& getMnemonic() const;
        // Returns the SDTS Mnemonic of this field (if one has been set).
      // Mutators
     string const& setName(string const& name);
     string const& setMnemonic(string const& mnem);

   private:

     string _name;      // SDTS Field Name
     string _mnemonic;  // SDTS Field Mnemonic

}; // class sc_Field

#endif
