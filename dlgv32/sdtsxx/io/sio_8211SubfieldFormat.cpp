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
// sio_8211SubfieldFormat.cpp
//


#include "../io/sio_8211SubfieldFormat.h"

#ifndef INCLUDED_SIO_8211UTILS_H
#include "../io/sio_8211Utils.h"
#endif



// This contains the implementation details for 
// sio_8211SubfieldFormat.

struct sio_8211SubfieldFormatImp
{
	sio_8211SubfieldFormatImp() : 
		_label(""), 
		_type(sio_8211SubfieldFormat::A), 
		_format(sio_8211SubfieldFormat::variable), 
		_control(sio_8211UnitTerminator), 
		_converter(0) {}


	// destructor, assignment operator, and copy ctor not
	// implemented

	string _label;	// a.k.a. subfield mnemonic

	sio_8211SubfieldFormat::type _type;

	sio_8211SubfieldFormat::format _format;

	sio_8211Converter const * _converter;

	// XXX Since a subfield format is either going to be 
	// XXX character delimited or read by length, there's no
	// XXX reason to store the character delimeter and length
	// XXX separately.  The union effects this and conveys
	// XXX this mutual exclusive nature.
	union control
	{
		char _delimiter;
		int  _length;

		explicit control( char delimiter ) : _delimiter( delimiter ) {}
		explicit control( int length ) : _length( length ) {}
	} _control;

}; // struct sio_8211SubfieldFormatImp






sio_8211SubfieldFormat::sio_8211SubfieldFormat()
:	_imp( new sio_8211SubfieldFormatImp )
{

} // sio_8211SubfieldFormat ctor



sio_8211SubfieldFormat::sio_8211SubfieldFormat( sio_8211SubfieldFormat const & sf )
:	_imp( new sio_8211SubfieldFormatImp(*sf._imp) )
{

} // sio_8211SubfieldFormat copy ctor



sio_8211SubfieldFormat::~sio_8211SubfieldFormat()
{
	delete _imp;
} // sio_8211SubfieldFormat dtor



sio_8211SubfieldFormat&
sio_8211SubfieldFormat::operator=( sio_8211SubfieldFormat const & rhs )
{
	if ( &rhs != this )
	{
		*_imp = *rhs._imp;
	}

	return *this;
} // sio_8211SubfieldFormat::operator=






string const &
sio_8211SubfieldFormat::getLabel() const
{
	return _imp->_label;
} // sio_8211SubfieldFormat::getLabel() const




sio_8211SubfieldFormat::type
sio_8211SubfieldFormat::getType() const
{
	return _imp->_type;
} // sio_8211SubfieldFormat::getType() const




sio_8211SubfieldFormat::format
sio_8211SubfieldFormat::getFormat() const
{
	return _imp->_format;
} // sio_8211SubfieldFormat::getFormat() const



int
sio_8211SubfieldFormat::getLength() const
{
	return _imp->_control._length;
} // sio_8211SubfieldFormat::getLabel() const



char
sio_8211SubfieldFormat::getDelimiter() const
{
	return _imp->_control._delimiter;
} // sio_8211SubfieldFormat::getDelimiter() const



sio_8211Converter const *
sio_8211SubfieldFormat::getConverter() const
{
	return _imp->_converter;
} // sio_8211SubfieldFormat::getConverter() const










void
sio_8211SubfieldFormat::setLabel( string const & label ) 
{
	_imp->_label = label;
} // sio_8211SubfieldFormat::setLabel()




void
sio_8211SubfieldFormat::setType( sio_8211SubfieldFormat::type t )
{
	_imp->_type = t;

#ifdef BOGUS
   // if the subfield type is binary, its length will be in _bits_ and
   // not in characters.  If so, convert to character units to be 
   // consistent with the other subfields.
   if ( _imp->_control._length > 0 && 
        _imp->_type == sio_8211SubfieldFormat::B )
      {
         _imp->_control._length /= 8;
      }
#endif

} // sio_8211SubfieldFormat::setType()




void
sio_8211SubfieldFormat::setFormat( sio_8211SubfieldFormat::format f )
{
	_imp->_format = f;
} // sio_8211SubfieldFormat::setFormat()



void
sio_8211SubfieldFormat::setLength( int val )
{
 
	_imp->_control._length = val;
	_imp->_format = sio_8211SubfieldFormat::fixed;
} // sio_8211SubfieldFormat::setLabel()



void
sio_8211SubfieldFormat::setDelimiter( char val )
{
	_imp->_control._delimiter = val;
	_imp->_format = sio_8211SubfieldFormat::variable;
} // sio_8211SubfieldFormat::setDelimiter()



void
sio_8211SubfieldFormat::setConverter( sio_8211Converter const * converter )
{
	_imp->_converter = converter;
} // sio_8211SubfieldFormat::setConverter()


