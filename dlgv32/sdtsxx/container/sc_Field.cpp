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
// sc_Field.cpp: implementation of the sc_Field class.
//
//////////////////////////////////////////////////////////////////////


#include "container/sc_Field.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

sc_Field::sc_Field()
{

}

sc_Field::~sc_Field()
{

}


string const&
sc_Field::getName() const
{
   return _name;
}


string const&
sc_Field::getMnemonic() const
{
   return _mnemonic;
}


string const&
sc_Field::setName(string const& name)
{
   return _name = name;
}


string const&
sc_Field::setMnemonic(string const& mnem)
{
   return _mnemonic = mnem;
}

