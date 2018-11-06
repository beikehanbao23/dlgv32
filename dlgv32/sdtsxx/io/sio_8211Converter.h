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
#ifndef INCLUDED_SIO_8211CONVERTER_H
#define INCLUDED_SIO_8211CONVERTER_H

#ifdef WIN32
#include <string>
#include <strstream>
#include <math.h>
//#include <winsock2.h> <- This shouldn't have to be in the .cpp file. 
// Due to the inability of MS to correctly write a .h file, it has to live
// there, because it causes a problem included here.
   using namespace std;
#else
#include <math.h>
#include <string.h>
#include <strstream.h>
#include <sys/types.h>
#include <netinet/in.h>
#endif

#ifndef INCLUDED_SIO_BUFFER_H
#include "io/sio_Buffer.h"
#endif

#ifndef INCLUDED_SIO_CONVERTER_H
#include "io/sio_Converter.h"
#endif

class sio_8211Converter : public sio_Converter
{

   // A Converter converts between an SDTS subfield and 'raw' data.

   public:

		sio_8211Converter() {}

      virtual ~sio_8211Converter();


      // NOTE: Niether the fixed or variable make() functions set the subfield
      //       mnemonic or the subfield name.

      // Fixed width subfields
      virtual long makeFixedSubfield(sc_Subfield* subfield,
                                     char const* data,
                                     long bitLength) const = 0;
         // Returns the length of the data actually converted. This may be
         // different than 'length' if an error occured.

      // Variable width subfields
      virtual long makeVarSubfield(sc_Subfield* subfield,
                                char const* data,
                                long maxLength,
                                char delimiter) const;
         // Returns the length of the data converted. This does _not_ included
         // the delimiter (if any).

	   virtual long addEmptySubfield(sio_Buffer& buffer) const;
         // Adds a "null field" (adds an end-of-field character) to the buffer.

      virtual long addSubfield(sc_Subfield const& subf,
                               sio_Buffer& buffer) const = 0;
	     // Adds a subfield, encoded in 8211 format, to the buffer

      virtual long addFixedSubfield(sc_Subfield const& subf,
                                    long length,
                                    sio_Buffer& buffer) const = 0;
         // Like addSubfield(), but for fixed length subfields.  Will not
         // be implemented for binary fields, obviously.
            
   protected:

      long findVariableSubfieldLength(char const* data,
                                   long maxLength,
                                   char delimiter) const;
         // Determines the length of a variable length subfield in 'data'
         // delimited by 'delimiter'.

};

class sio_8211Converter_A : public sio_8211Converter
{
   public:
 
		sio_8211Converter_A() {}

      long makeFixedSubfield(sc_Subfield* subfield,
                             char const* data,
                             long length) const;

      long addSubfield(sc_Subfield const& subf,
                               sio_Buffer& buffer) const;

      long addFixedSubfield(sc_Subfield const& subf,
                            long length,
                            sio_Buffer& buffer) const;
};

class sio_8211Converter_I : public sio_8211Converter
{
   public:
 
      sio_8211Converter_I() {}

      long makeFixedSubfield(sc_Subfield* subfield,
                             char const* data,
                             long length) const;

      long addSubfield(sc_Subfield const& subf,
                               sio_Buffer& buffer) const;

      long addFixedSubfield(sc_Subfield const& subf,
                            long length,
                            sio_Buffer& buffer) const;
};

class sio_8211Converter_R : public sio_8211Converter
{
   public:

      sio_8211Converter_R() {}

      long makeFixedSubfield(sc_Subfield* subfield,
                             char const* data,
                             long length) const;

      long addSubfield(sc_Subfield const& subf,
                               sio_Buffer& buffer) const;

      long addFixedSubfield(sc_Subfield const& subf,
                            long length,
                            sio_Buffer& buffer) const;
};

class sio_8211Converter_S : public sio_8211Converter
{
   public:

      sio_8211Converter_S() {}

      long makeFixedSubfield(sc_Subfield* subfield,
                             char const* data,
                             long length) const;

      long addSubfield(sc_Subfield const& subf,
                               sio_Buffer& buffer) const;

      long addFixedSubfield(sc_Subfield const& subf,
                            long length,
                            sio_Buffer& buffer) const;

};

class sio_8211Converter_BI8 : public sio_8211Converter
{
   public:
      sio_8211Converter_BI8() {}

      long makeFixedSubfield(sc_Subfield* subfield,
                             char const* data,
                             long bitLength) const;

      long addSubfield(sc_Subfield const& subfield,
                               sio_Buffer& buffer) const;

      long addFixedSubfield(sc_Subfield const& subf,
                            long length,
                            sio_Buffer& buffer) const
      { return addSubfield( subf, buffer ); }

};

class sio_8211Converter_BI16 : public sio_8211Converter
{
   public:
      sio_8211Converter_BI16() {}

      long makeFixedSubfield(sc_Subfield* subfield,
                             char const* data,
                             long bitLength) const;

  	   long addSubfield(sc_Subfield const& subfield,
                               sio_Buffer& buffer) const;

      long addFixedSubfield(sc_Subfield const& subf,
                            long length,
                            sio_Buffer& buffer) const
      { return addSubfield( subf, buffer ); }

};

class sio_8211Converter_BI24 : public sio_8211Converter
{
   public:
      sio_8211Converter_BI24() {}

      long makeFixedSubfield(sc_Subfield* subfield,
                             char const* data,
                             long bitLength) const;

      long addSubfield(sc_Subfield const& subfield,
                               sio_Buffer& buffer) const;

      long addFixedSubfield(sc_Subfield const& subf,
                            long length,
                            sio_Buffer& buffer) const
      { return addSubfield( subf, buffer ); }

};


class sio_8211Converter_BI32 : public sio_8211Converter
{
   public:
      sio_8211Converter_BI32() {}

      long makeFixedSubfield(sc_Subfield* subfield,
                             char const* data,
                             long bitLength) const;

      long addSubfield(sc_Subfield const& subfield,
                               sio_Buffer& buffer) const;

      long addFixedSubfield(sc_Subfield const& subf,
                            long length,
                            sio_Buffer& buffer) const
      { return addSubfield( subf, buffer ); }

};

class sio_8211Converter_BUI8 : public sio_8211Converter
{
   public:
      sio_8211Converter_BUI8() {}

      long makeFixedSubfield(sc_Subfield* subfield,
                             char const* data,
                             long bitLength) const;

      long addSubfield(sc_Subfield const& subfield,
                               sio_Buffer& buffer) const;

      long addFixedSubfield(sc_Subfield const& subf,
                            long length,
                            sio_Buffer& buffer) const
      { return addSubfield( subf, buffer ); }

};

class sio_8211Converter_BUI16 : public sio_8211Converter
{
   public:
      sio_8211Converter_BUI16() {}

      long makeFixedSubfield(sc_Subfield* subfield,
                             char const* data,
                             long bitLength) const;

      long addSubfield(sc_Subfield const& subfield,
                               sio_Buffer& buffer) const;

      long addFixedSubfield(sc_Subfield const& subf,
                            long length,
                            sio_Buffer& buffer) const
      { return addSubfield( subf, buffer ); }

};

class sio_8211Converter_BUI24 : public sio_8211Converter
{
   public:
      sio_8211Converter_BUI24() {}

      long makeFixedSubfield(sc_Subfield* subfield,
                             char const* data,
                             long bitLength) const;

      long addSubfield(sc_Subfield const& subfield,
                               sio_Buffer& buffer) const;

      long addFixedSubfield(sc_Subfield const& subf,
                            long length,
                            sio_Buffer& buffer) const
      { return addSubfield( subf, buffer ); }

};

class sio_8211Converter_BUI32 : public sio_8211Converter
{
   public:
      sio_8211Converter_BUI32() {}

      long makeFixedSubfield(sc_Subfield* subfield,
                             char const* data,
                             long bitLength) const;

      long addSubfield(sc_Subfield const& subfield,
                               sio_Buffer& buffer) const;

      long addFixedSubfield(sc_Subfield const& subf,
                            long length,
                            sio_Buffer& buffer) const
      { return addSubfield( subf, buffer ); }

};

class sio_8211Converter_BFP32 : public sio_8211Converter
{
   public:
      sio_8211Converter_BFP32() {}

      long makeFixedSubfield(sc_Subfield* subfield,
                             char const* data,
                             long bitLength) const;

      long addSubfield(sc_Subfield const& subfield,
                               sio_Buffer& buffer) const;

      long addFixedSubfield(sc_Subfield const& subf,
                            long length,
                            sio_Buffer& buffer) const
      { return addSubfield( subf, buffer ); }

};

class sio_8211Converter_BFP64 : public sio_8211Converter
{
   public:
      sio_8211Converter_BFP64() {}

      long makeFixedSubfield(sc_Subfield* subfield,
                             char const* data,
                             long bitLength) const;

      long addSubfield(sc_Subfield const& subfield,
                               sio_Buffer& buffer) const;

      long addFixedSubfield(sc_Subfield const& subf,
                            long length,
                            sio_Buffer& buffer) const
      { return addSubfield( subf, buffer ); }

};

#endif INCLUDED_SIO_8211_CONVERTER_H