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
// sio_8211DDRField.cpp
//

#include "io/sio_8211DDRField.h"

#ifndef INCLUDED_SIO_8211FIELD_H
#include "io/sio_8211Field.h"
#endif

#ifndef INCLUDED_SIO_8211DDRLEADER_H
#include "io/sio_8211DDRLeader.h"
#endif

// Needed to define this else VC++ whines about no default ctor's for the 
// derived classes.
sio_8211DDRField::sio_8211DDRField() 
   : _fieldName(""), _arrayDescr(""), _formatControls("")
{
   _fieldName.reserve(256);         // having to reserve enough space
   _arrayDescr.reserve(256);        // by hand to work around bug in
   _formatControls.reserve(256);    // VC++ <1>
} // sio_8211DDRField ctor

// <1> this bug basically involves assigning string values to strings that
// already have enough space to accomodate the new value; then a memcpy()
// call gets called that over-runs the allocated space somehow.  I've not
// been able to consistently reproduce this error though; and it was only
// thanks to BoundsChecker that I was able to find this problem at all.


sio_8211DDRField::sio_8211DDRField(sio_8211DDRLeader const& leader,
                                   sio_8211Field const& field)
                : _fieldControlLength(leader.getFieldControlLength())
{
   char const* data = field.getData();

   _dataStructCode = data[0];
   _dataTypeCode = data[1];

   // Starting at the end of the field controls, look for an optional data field
   // name followed by a unit terminator.

   char tmpbuf[1000];

   long pos = _fieldControlLength;
   if (!field.getVariableSubfield(tmpbuf,pos))
      {
         // XXX Error!
      }
   _fieldName = tmpbuf;

   if (!field.getVariableSubfield(tmpbuf,pos))
      {
         // XXX Error!
      }
   _arrayDescr = tmpbuf;

   if (!field.getVariableSubfield(tmpbuf,pos))
      {
         // XXX Error!
      }
   _formatControls = tmpbuf;
}

sio_8211DDRField::~sio_8211DDRField()
   {
   }

char
sio_8211DDRField::getDataStructCode() const
{
   return _dataStructCode;
}

char
sio_8211DDRField::getDataTypeCode() const
{
   return _dataTypeCode;
}

string const&
sio_8211DDRField::getDataFieldName() const
{
   return _fieldName;
}

string const&
sio_8211DDRField::getArrayDescriptor() const
{
   return _arrayDescr;
}

string const&
sio_8211DDRField::getFormatControls() const
{
   return _formatControls;
}      

void 
sio_8211DDRField::setDataFieldName( string const &name ) 
{
   _fieldName = name;
}

void 
sio_8211DDRField::setDataStructCode( char code ) 
{
   _dataStructCode = code;
}

void 
sio_8211DDRField::setDataTypeCode( char code ) 
{
   _dataTypeCode = code;
}

void 
sio_8211DDRField::setDataStructCode( sio_8211FieldFormat::data_struct_code dsc ) 
{
   switch ( dsc )
   {
      case sio_8211FieldFormat::elementary :
         setDataStructCode( '0' );
         break;
      case sio_8211FieldFormat::vector :
         setDataStructCode( '1' );
         break;
      case sio_8211FieldFormat::array :
         setDataStructCode( '2' );
         break;
      case sio_8211FieldFormat::concatenated :
         setDataStructCode( '3' );
         break;
   }
}

void 
sio_8211DDRField::setDataTypeCode( sio_8211FieldFormat::data_type_code dtc ) 
{
   switch ( dtc )
   {
      case  sio_8211FieldFormat::char_string :
         setDataTypeCode( '0' );
         break;
      case 	sio_8211FieldFormat::implicit_point :
         setDataTypeCode( '1' );
         break;
		case	sio_8211FieldFormat::explicit_point :
         setDataTypeCode( '2' );
         break;
		case	sio_8211FieldFormat::explicit_point_scaled :
         setDataTypeCode( '3' );
         break;
		case	sio_8211FieldFormat::char_bit_string :
         setDataTypeCode( '4' );
         break;
		case	sio_8211FieldFormat::bit_string :
         setDataTypeCode( '5' );
         break;
		case	sio_8211FieldFormat::mixed_data_type :
         setDataTypeCode( '6' );
         break;
   }
}
            
void 
sio_8211DDRField::setArrayDescriptor( string const &descriptor ) 
{
   _arrayDescr.assign( descriptor );
}

void 
sio_8211DDRField::setFormatControls( string const &control ) 
{
   _formatControls = control;
}



#if 0
istream&
sio_8211DDRField::streamExtract(istream& istr)
{
   // Assume istr is positioned on byte zero of a DDR field.

   // XXX We need some error checking here.
   delete _data;
   _data = new unsigned char[_dataLength];
   istr.read(reinterpret_cast<char*>(_data),_dataLength);

   if (!istr)
      return istr;

   // Gobble up field terminator.
   char tempChar;
   istr.get(tempChar);  // XXX Should check to see if this really _is_ 
                        // XXX a field terminator.

   // Ok. We've got the raw data. Now, break it apart.
   _dataStructCode = _data[0];
   _dataTypeCode = _data[1];

   // Starting at the end of the field controls, look for an optional data field
   // name followed by a unit terminator.

   char tmpbuf[1000];

   if (!getVariableSubfield(tmpbuf,sio_8211UnitTerminator,_fieldControlLength))
      {
         istr.clear(ios::failbit); 
         return istr;
      }
   _fieldName = tmpbuf;

   if (!getVariableSubfield(tmpbuf))
      {
         istr.clear(ios::failbit);
         return istr;
      }
   _arrayDescr = tmpbuf;

   if (!getVariableSubfield(tmpbuf))
      {
         istr.clear(ios::failbit);
         return istr;
      }
   _formatControls = tmpbuf;

   return istr;
}

#endif



sio_Buffer
sio_8211DDRField::getField() const
{
   sio_Buffer buffer;

   // first add the format controls

   buffer.addData( getDataStructCode() );
   buffer.addData( getDataTypeCode() );
   buffer.addData( "00", 2 ); // unused auxiliary controls
   buffer.addData( ";&", 2 ); // stupid print characters

   // then the data field name

   buffer.addData( getDataFieldName().c_str(), getDataFieldName().length() );
   buffer.addData( sio_8211UnitTerminator );

   // then the array descriptors (subfield labels)

   buffer.addData( getArrayDescriptor().c_str(), getArrayDescriptor().length() );
   buffer.addData( sio_8211UnitTerminator );

   // then the field formats

   buffer.addData( getFormatControls().c_str(), getFormatControls().length() );

   // add final field terminator

   buffer.addData( sio_8211FieldTerminator );

   return buffer;
} // sio_8211DDRField::getField() const







sio_8211FileTitleField::sio_8211FileTitleField()
{
   setDataStructCode( '0' );
   setDataTypeCode( '0' );
   setDataFieldName( "" ); // file name
} // sio_8211FileTitleField ctor



sio_8211FileTitleField::sio_8211FileTitleField( string const& title )
{
   setDataStructCode( '0' );
   setDataTypeCode( '0' );
   setDataFieldName( title ); // file name
} // sio_8211FileTitleField ctor



sio_Buffer
sio_8211FileTitleField::getField() const
{
   sio_Buffer buffer;

   // first add the format controls

   buffer.addData( getDataStructCode() );
   buffer.addData( getDataTypeCode() );
   buffer.addData( "00", 2 ); // unused auxiliary controls
   buffer.addData( ";&", 2 ); // stupid print characters

   // then the data field name

   buffer.addData( getDataFieldName().c_str(), getDataFieldName().length() );

   // add final field terminator

   buffer.addData( sio_8211FieldTerminator );

   return buffer;
} // sio_8211FileTitleField::getField() const








sio_8211RecordIdentifierField::sio_8211RecordIdentifierField()
{
   setDataStructCode( '0' );
   setDataTypeCode( '1' );
   setDataFieldName( "DDF RECORD IDENTIFIER" );
} // sio_8211RecordIdentifierField ctor