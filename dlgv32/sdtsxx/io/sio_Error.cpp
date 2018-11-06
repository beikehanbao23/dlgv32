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
// sio_Error.cpp
//

#include "io/sio_Error.h"


sio_Error::sio_Error() 
   : _state( goodbit ) 
{}



bool 
sio_Error::good() const 
{ return ! _state; }



bool 
sio_Error::bad() const 
{ return _state & badbit; }



bool 
sio_Error::fail() const 
{ return _state & (failbit | badbit); }



int  
sio_Error::rdstate() const 
{ return _state; }



int  
sio_Error::setstate( int state ) 
{ return _state = state; }



int  
sio_Error::clear() 
{ return _state = goodbit; }

