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
// sio_8211FieldFormat.h
//


#ifndef INCLUDED_SIO8211FIELDFORMAT_H
#define INCLUDED_SIO8211FIELDFORMAT_H




#ifndef INCLUDED_SIO8211SUBFIELDFORMAT_H
#include "../io/sio_8211SubfieldFormat.h"
#endif


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#ifdef WIN32
#include <list>
#include <map>
#include <string>
   using namespace std;
#else
#include <list.h>
#include <map.h>
#include <string.h>
#endif



struct sio_8211FieldFormatImp;


/**

  Each 8211 field has several features.  It has an optional name.  It has
  a tag, which is used to locate the field formatting information in the
  DR's.  It also has a type.  Morever, a field format can consist of several
  subfield formats.  (Which is why it's implemented as a container of subfield
  formats.

  This is used to pull in field values from an 8211 DR.  Given the start 
  position and length of a field's data in an 8211 DR, you need to then 
  find out how to convert that data into something meaningful.  You
  would do so by getting the appropriate field format for that data, 
  and use it to convert the data.

  No internal consistency checking is done.  It is possible, for example, to
  have a field format set as an elementary data structure that has subfields; 
  this violates the standard as field formats only have subfields if it's a 
  vector or an array field.

  */
class sio_8211FieldFormat : public list<sio_8211SubfieldFormat>
{
public:

	///
	typedef list<sio_8211SubfieldFormat>::iterator iterator;

	///
	typedef list<sio_8211SubfieldFormat>::const_iterator const_iterator;


	/// XXX using ``vector'' as one of the enumerated names may cause problems.
	typedef enum { elementary, vector, array, concatenated } data_struct_code;

	/** 
		XXX these are a bit verbose, though they do comply with the standard's
		nomenclature.
	*/
	typedef enum { char_string, 
						implicit_point, 
						explicit_point, 
						explicit_point_scaled, 
						char_bit_string, 
						bit_string, 
						mixed_data_type } data_type_code;

	///
	sio_8211FieldFormat();

	///
	sio_8211FieldFormat( sio_8211FieldFormat const & );

	///
	~sio_8211FieldFormat();



	///
	sio_8211FieldFormat& operator=( sio_8211FieldFormat const & );




	///
	data_struct_code	getDataStructCode( ) const;

	///
	data_type_code		getDataTypeCode( ) const;

	///
	string const&		getTag( ) const;

	///
	string const&     getName( ) const;

	/// XXX do we really care?
	char					getFieldTerm( ) const;

	/// XXX do we ever really care?
	char					getUnitTerm( ) const;

   /// returns true if this is a repeatin field
   /** XXX for binary repeating field special case **/
   bool              isRepeating() const;



	///
	void setDataStructCode( data_struct_code );

	///
	void setDataTypeCode( data_type_code );

	///
	void setTag( string const & );

	///
	void setName( string const& );

	/// XXX do we ever ever really care?
	void setFieldTerm( char );

	/// XXX  I mean, really?
	void setUnitTerm( char );

   ///
   void setIsRepeating( bool repeating );


	/// XXX returns comparison of the two field tags -- sensible?  or goofy?
	bool operator<( sio_8211FieldFormat const& rhs ) const;

	/// XXX returns comparison of the two field tags -- sensible?  or goofy?
	bool operator>( sio_8211FieldFormat const& rhs ) const;

	/// XXX returns comparison of the two field tags -- sensible?  or goofy?
	bool operator==( sio_8211FieldFormat const& rhs ) const;

	/// XXX returns comparison of the two field tags -- sensible?  or goofy?
	/**  This special string comparison is needed by find(). */
	bool operator==( string const& rhs ) const;

	/// XXX returns comparison of the two field tags -- sensible?  or goofy?
	bool operator!=( sio_8211FieldFormat const& rhs ) const { return ! (*this == rhs); }


private:

	/// hidden implementation details
	sio_8211FieldFormatImp* _imp;

}; // class sio_8211FieldFormat




class sio_8211DDRField;
class sio_8211Converter;

/** 

	Takes the given DDR field and modifies the given field format object
	to hold the field and subfield formats found in the DDR field.  The map
	of a string to a pointer to a converter class is important.  It allows
	this function to properly bind a binary conversion function for a given
	subfield label.  In other words, for each subfield format, there exists
	a corresponding converter class that will convert a raw DR subfield into
	an equivalent sc_Subfield.  For 8211 A, I, R, and S types, this is fairly
	straightforward.  The binary types are a bit of a problem; e.g., a SADR
	could be a BI32 or a BU16.  That type information isn't stored in the 8211
	file that the SADR was found in, so the user has to supply that information
	to give the reader a hint as to how to cope with that data.


	Returns true if successful, else false.

 XXX Does this belong here?  And what about the field tag information?  
 XXX Should that be passed in separately, or should we make the 
 XXX DDRField know its tag?

  */
bool sio_8211MakeFieldFormat( sio_8211FieldFormat & ff ,
									   sio_8211DDRField const & ddr_field,
									   string const & field_tag,
										map<string, sio_8211Converter* > const* binary_converter_hints = 0

// XXX need to change map instantiation from above to below for GNU C++
// XXX map<string, sio_Converter*, less<string> > const* binary_converter_hints = 0
									   );

#endif // INCLUDED_SIO8211FIELDFORMAT_H
