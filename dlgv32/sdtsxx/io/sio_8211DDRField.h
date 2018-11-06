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
// sio_8211DDRField.h
//

#ifndef INCLUDED_SIO_8211DDRFIELD_H
#define INCLUDED_SIO_8211DDRFIELD_H

#ifdef WIN32
#include <string>
   using namespace std;
#else
#include <string.h>
#endif


#ifndef INCLUDED_SIO_BUFFER_H
#include "io/sio_Buffer.h"
#endif

#ifndef INCLUDED_SIO8211FIELDFORMAT_H
#include "io/sio_8211FieldFormat.h"
#endif


class sio_8211DDRLeader;
class sio_8211Field;

class sio_8211DDRField
{
   // An sio_8211DDRField is used to interpret the data in a raw
   // sio_8211Field.

   public:
      sio_8211DDRField();
      sio_8211DDRField(sio_8211DDRLeader const& leader,
                                sio_8211Field const& field);

      virtual ~sio_8211DDRField();

      char getDataStructCode() const;
      char getDataTypeCode() const;

      // XXX There are other values (such as printable graphics) that I'm
      // XXX not interested in right now.

      string const& getDataFieldName() const;
      string const& getArrayDescriptor() const;
      string const& getFormatControls() const;

      //virtual sio_8211Field getField() const;
      virtual sio_Buffer getField() const;

      void setDataFieldName( string const &name );
      void setDataStructCode( char code );
      void setDataTypeCode( char code );
      void setDataStructCode( sio_8211FieldFormat::data_struct_code dsc );
      void setDataTypeCode( sio_8211FieldFormat::data_type_code dtc );
      void setArrayDescriptor( string const &descriptor );
      void setFormatControls( string const &control );
      
   private:

      char _dataStructCode;
      char _dataTypeCode;
      string _fieldName;
      string _arrayDescr;
      string _formatControls;

      long _fieldControlLength;  // From the ddr leader.

}; // sio_8211DDRField




class sio_8211FileTitleField : public sio_8211DDRField
{
   public:

      sio_8211FileTitleField( );

      sio_8211FileTitleField( string const& title );

      sio_Buffer getField() const; // XXX should be defined in parent

}; // class sio_8211FileTitleField




class sio_8211RecordIdentifierField : public sio_8211DDRField
{
   public:

      // XXX We need set/get for the actual record identifier.  Or do we?

      sio_8211RecordIdentifierField();

}; // class sio_8211FileTitleField



#endif  // INCLUDED_SIO_8211DDRFIELD_H
