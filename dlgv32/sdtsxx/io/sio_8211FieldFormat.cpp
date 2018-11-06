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
// sio_8211FieldFormat.cpp: implementation of the sio_8211FieldFormat class.
//
//////////////////////////////////////////////////////////////////////

#ifdef WIN32
#pragma warning(once:4786)
#endif

#include "io/sio_8211FieldFormat.h"

#include <iostream>

#ifndef INCLUDED_SIO8211DDRFIELD_H
#include "io/sio_8211DDRField.h"
#endif

#ifndef INCLUDED_SIO_CONVERTER_H
#include "io/sio_Converter.h"
#endif

#ifndef INCLUDED_SIO_8211CONVERTER_H
#include "io/sio_8211Converter.h"
#endif

/**

  sio_8211FieldFormat's implementation structure

  */
struct
sio_8211FieldFormatImp
{
	sio_8211FieldFormat::data_struct_code _data_struct_code;

	sio_8211FieldFormat::data_type_code _data_type_code;

	string _tag;

	string _name;

	char _field_term; // XXX probably no point in actually keeping these two
	char _unit_term;

   bool _isRepeating; // true if this is a repeating field

	sio_8211FieldFormatImp()
		:	_data_struct_code( sio_8211FieldFormat::elementary ),
			_data_type_code( sio_8211FieldFormat::implicit_point ),
			_tag(""),
			_field_term(';'), // XXX if we keep these, then I need to move
			_unit_term('&'),	// XXX these hard-coded values outside the struct
         _isRepeating(false)
	{}

}; // sio_8211FieldFormatImp




sio_8211FieldFormat::sio_8211FieldFormat()
: _imp( new sio_8211FieldFormatImp )
{} // sio_8211FieldFormat ctor



sio_8211FieldFormat::sio_8211FieldFormat( sio_8211FieldFormat const & ff )
:	_imp( new sio_8211FieldFormatImp(*ff._imp) )
{} // sio_8211FieldFormat copy ctor



sio_8211FieldFormat::~sio_8211FieldFormat()
{
	delete _imp;
} // sio_8211FieldFormat dtor




sio_8211FieldFormat&
sio_8211FieldFormat::operator=( sio_8211FieldFormat const & rhs )
{
	if ( &rhs != this )
	{
		*_imp = *rhs._imp;
	}

	return *this;
} // sio_8211FieldFormat::operator=




bool
sio_8211FieldFormat::operator<( sio_8211FieldFormat const & rhs ) const
{
	return _imp->_tag.compare( rhs._imp->_tag ) < 0;
} // sio_8211FieldFormat::operator=




bool
sio_8211FieldFormat::operator>( sio_8211FieldFormat const & rhs ) const
{
	return _imp->_tag.compare( rhs._imp->_tag ) > 0;
} // sio_8211FieldFormat::operator=



bool
sio_8211FieldFormat::operator==( sio_8211FieldFormat const & rhs ) const
{
	return _imp->_tag.compare( rhs._imp->_tag ) == 0;
} // sio_8211FieldFormat::operator=


bool
sio_8211FieldFormat::operator==( string const & rhs ) const
{
	return _imp->_tag.compare( rhs ) == 0;
} // sio_8211FieldFormat::operator=



sio_8211FieldFormat::data_struct_code 
sio_8211FieldFormat::getDataStructCode( ) const
{
	return _imp->_data_struct_code;
} // sio_8211FieldFormat::getDataStructCode



sio_8211FieldFormat::data_type_code 
sio_8211FieldFormat::getDataTypeCode( ) const
{
	return _imp->_data_type_code;
} // sio_8211FieldFormat::getDataTypeCode



string const& 
sio_8211FieldFormat::getTag( ) const
{
	return _imp->_tag;
} // sio_8211FieldFormat::getTag



string const& 
sio_8211FieldFormat::getName( ) const
{
	return _imp->_name;
} // sio_8211FieldFormat::getName()



char 
sio_8211FieldFormat::getFieldTerm( ) const
{
	return _imp->_field_term;
} // sio_8211FieldFormat::getFieldTerm



char 
sio_8211FieldFormat::getUnitTerm( ) const
{
	return _imp->_unit_term;
} // sio_8211FieldFormat::getUnitTerm


bool 
sio_8211FieldFormat::isRepeating( ) const
{
	return _imp->_isRepeating;
} // sio_8211FieldFormat::isRepeating




void 
sio_8211FieldFormat::setDataStructCode( data_struct_code dsc )
{
	_imp->_data_struct_code = dsc;
} // sio_8211FieldFormat::setDataStructCode



void 
sio_8211FieldFormat::setDataTypeCode( data_type_code dtc )
{
	_imp->_data_type_code = dtc;
} // sio_8211FieldFormat::setDataTypeCode



void 
sio_8211FieldFormat::setTag( string const & tag )
{
	_imp->_tag = tag;
} // sio_8211FieldFormat::setTag



void 
sio_8211FieldFormat::setName( string const & name )
{
	_imp->_name = name;
} // sio_8211FieldFormat::setName()



void 
sio_8211FieldFormat::setFieldTerm( char ft )
{
	_imp->_field_term = ft;
} // sio_8211FieldFormat::setFieldTerm



void 
sio_8211FieldFormat::setUnitTerm( char ut )
{
	_imp->_unit_term = ut;
} // sio_8211FieldFormat::setUnitTerm




void 
sio_8211FieldFormat::setIsRepeating( bool repeating )
{
	_imp->_isRepeating = repeating;
} // sio_8211FieldFormat::setIsRepeating




// buffer containing current subfield format string for the parser
const char * sio_8211_subfield_format_buffer = "";


// container of hints for resolving binary subfield types in the format parser
map<string, sio_8211Converter*> const* sio_8211_binary_converter_hints;

// XXX need to change map instantiation from above to below
// XXX map< string, sio_Converter*, less<string> > const* sio_8211_binary_converter_hints;


// cursor into a subfield format to be set by the format string by the parser
sio_8211FieldFormat::iterator current_sio_8211Subfield;


// three guesses what this is ... and the first two don't count
extern int sio_8211_yyparse();




struct yy_buffer_state;		// opaque type used by flex

// used by flex to get its input from a string and not from a stream
yy_buffer_state* sio_8211_yy_scan_bytes( const char*, int s );

// frees up resources used by a yy_buffer_state
void sio_8211_yy_delete_buffer( yy_buffer_state* bs );



//
// Simple debugging function that can be called from sio_8211MakeFieldFormat()
//
static
void
_dumpConverterMap( map<string, sio_8211Converter* > const* c_map )
{
   if ( ! c_map ) 
      {
         cerr << __FILE__ << " no map\n";
         return;
      }

   cerr << "converter map:\n";

   for ( map<string, sio_8211Converter* >::const_iterator i = c_map->begin();
         i != c_map->end();
         i++ )
      {
         cerr << "\t" << i->first << "\t" << i->second << "\n";
      }
} // _dumpConverterMap



bool 
sio_8211MakeFieldFormat( sio_8211FieldFormat &		ff,
								 sio_8211DDRField const &	ddr_field,
								 string const &				field_tag,
								 map<string, sio_8211Converter* > const* binary_converter_hints )

// XXX need to change map from above to below to work with GNU C++
// XXX map<string, sio_Converter*, less<string> > const* binary_converter_hints
 
{
   // _dumpConverterMap( binary_converter_hints );


											// set field specific stuff first
	ff.setTag( field_tag );
	ff.setName( ddr_field.getDataFieldName() );

	switch ( ddr_field.getDataStructCode() )
	{
	case '0' : ff.setDataStructCode( sio_8211FieldFormat::elementary ); break;
	case '1' : ff.setDataStructCode( sio_8211FieldFormat::vector ); break;
	case '2' : ff.setDataStructCode( sio_8211FieldFormat::array ); break;
	case '3' : ff.setDataStructCode( sio_8211FieldFormat::concatenated ); break;
	default : return false;
	}


	switch ( ddr_field.getDataTypeCode() )
	{
	case '0' : ff.setDataTypeCode( sio_8211FieldFormat::char_string); break;
	case '1' : ff.setDataTypeCode( sio_8211FieldFormat::implicit_point ); break;
	case '2' : ff.setDataTypeCode( sio_8211FieldFormat::explicit_point ); break;
	case '3' : ff.setDataTypeCode( sio_8211FieldFormat::explicit_point_scaled); break;
	case '4' : ff.setDataTypeCode( sio_8211FieldFormat::char_bit_string ); break;
	case '5' : ff.setDataTypeCode( sio_8211FieldFormat::bit_string ); break;
	case '6' : ff.setDataTypeCode( sio_8211FieldFormat::mixed_data_type ); break;
	default : return false;
	}

	// XXX Again, do we really need to keep this information around in the format?

	// XXX These aren't (yet) proviced.  In fact, they may never be.

	// xxx ff.setFieldTerm( ddr_field.getFieldControls().[4] );
	// xxx ff.setUnitTerm( ddr_field.getFieldControls().[5] );


											// for each subfield label, create a 
											// subfield format

	string const & array_descriptor = ddr_field.getArrayDescriptor();

	string temp_label("");			// label string re-used for each subfield

	int i = 0;

											// if we're dealing with the array, then
											// there _should_ be an '*' as the first
											// character of the subfield labels; if so,
											// skip that character

	if ( sio_8211FieldFormat::array == ff.getDataStructCode() &&
		  '*' == array_descriptor[0] )
	{
		i++;
	}

	for (;;)
	{
											// grab the next '!' delimited subfield label

		while( i < array_descriptor.length() && 
				 array_descriptor[i] != '!' ) 
		{
			temp_label += array_descriptor[i++];
		}

											// if the label is empty, then either there was no
											// label or we're out of labels; regardless
											// we're done so bail

		if ( 0 == temp_label.length() ) break;

		ff.push_back( sio_8211SubfieldFormat() );	// add a new subfield format and set
		ff.back().setLabel( temp_label );			// its label

		i++;								// move over the '!' delimiter or one beyond the
											// subfield label string

		temp_label = "";				// reset the label for the next subfield format in line
	};

											// now parse the format string and set the type
											// for each subfield format that was created

	// Set an iterator to the first subfield format, then have a parser grind 
   // its way through the format string, setting each subfield format to 
   // reasonable values along the way.

											// set the string buffer pointer to the start of
											// the field format controls string

	sio_8211_subfield_format_buffer = ddr_field.getFormatControls().c_str();

											// set the global hints for the parser
	
	sio_8211_binary_converter_hints = binary_converter_hints;

											// set the global subfield format cursor to the first
											// subfield

	current_sio_8211Subfield = ff.begin();

	yy_buffer_state* bf;
	bf = sio_8211_yy_scan_bytes( sio_8211_subfield_format_buffer, ddr_field.getFormatControls().length() );

	sio_8211_yyparse();

	sio_8211_yy_delete_buffer( bf );


	return true;

} // sio_8211MakeFieldFormat



