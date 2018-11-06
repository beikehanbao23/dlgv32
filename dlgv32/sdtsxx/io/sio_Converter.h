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
#ifndef INCLUDED_SIO_CONVERTER_H
#define INCLUDED_SIO_CONVERTER_H


#ifdef WIN32
#include <string>
   using namespace std;
#else
#include <string.h>
#endif

#ifndef INCLUDED_SIO_BUFFER_H
#include "io/sio_Buffer.h"
#endif

class sc_Subfield;

class sio_Converter
{

   public:

		sio_Converter() {};
      virtual ~sio_Converter() {};

      // These are the normal constructors and destructors.

      virtual long makeFixedSubfield(sc_Subfield* subfield,
                                     char const* data,
                                     long length) const = 0;
      // Make a fixed subfield. Return the length of the data converted.
      // This method works to turn data from the file into the format used 
      // internally.

      virtual long makeVarSubfield(sc_Subfield* subfield,
                                char const* data,
                                long maxLength,
                                char delimiter) const = 0;
      // Make a variable-length subfield. Return the length of the data
      // converted. This method works to turn data read from file into the
      // format used internally by the library.

	   virtual long addEmptySubfield(sio_Buffer& buffer) const = 0;
      // Append an end-of-unit marker to the output buffer. Useful mainly
      // for adding subfields that do not contain data.

      virtual long addSubfield(sc_Subfield const& subf,
                                 sio_Buffer& buffer) const = 0;
      // Add a subfield (complete with it's values) to the output buffer.

   protected:

      virtual long findVariableSubfieldLength(char const* data,
                                   long maxLength,
                                   char delimiter) const;
      // Find the length of a variable-length subfield.
};


#endif  // INCLUDED_SIO_CONVERTER_H
