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
// sio_Writer.h
//


#ifndef INCLUDED_SIO_WRITER_H
#define INCLUDED_SIO_WRITER_H


class sio_8211DR;
class sio_8211DDR;
class sc_Record;

#ifdef WIN32

#include <string>
#include <fstream>
#include <list>

using namespace std;
#pragma warning( disable : 4786 )

#else

#include <list.h>

#endif



#ifndef INCLUDED_SIO8211FIELDFORMAT_H
#include "io/sio_8211FieldFormat.h"
#endif


//  This provides a prototypical interface for all SDTS writers.

class sio_Writer
{
   public:

      // sio_Writer( ) NOT NEEDED
	   // sio_Writer( const sio_Writer& ) NOT NEEDED
      // operator=(  const sio_Writer& ) NOT NEEDED

      virtual ~sio_Writer() = 0;

      /// Will write the given record out to the stream.
      virtual bool put( sc_Record& ) = 0;

      /// Returns true if the writer is in a usable state.
      virtual bool good( ) const = 0;

}; // class sio_Writer




// forward declaration for hidden sio_8211Writer internals

struct sio_8211Writer_Imp;



// An sio_8211Writer needs to know all the fields and subfields that
// can be written out for a given record.  It needs to know all this
// information up front (i.e., at construct time) so that it can
// write out a proper DDR.  The writer also needs to know field and subfield
// formatting information so that it can properly write out each record
// it gets via sio_Writer::put().  All this information is conveniently
// wrapped up in a container of field formats, sio_8211Schema.

// Each schema will be unique for a module type.  For example, an IDEN
// module schema will have field formats for the identification,
// conformance, and attribute id fields.  This will include all the 
// subfield label and type information.  See build_iden_schema() in
// the test app "../sio_Writer_t/sio_Writer.cpp".

typedef list <sio_8211FieldFormat> sio_8211Schema;


//
// A writer for ISO 8211 files.
//
class sio_8211Writer : public sio_Writer
{
   public:

   	sio_8211Writer( ofstream & ofs, 
                      string const & title,
                      sio_8211Schema const & schema );

	   // sio_8211Writer( const sio_8211Writer& ) NOT NEEDED
   	// operator=(  const sio_8211Writer& ) NOT NEEDED

   	~sio_8211Writer();

      bool put( sc_Record& record );
      // Writes the contents of the given record to the ``ofs'' given
      // to the ctor.


      bool good( ) const;
      // Returns true if the writer can write a record and if
      // the last operation worked ok.


      void reuseLeaderAndDirectory();
      // The next put() will emit a special leader and a directory.  All
      // subsequent put() invocations will emit only field data areas --
      // the last leader and directory will be 're-used' to save space.
      // (C.f., ISO/IEC 8211:1994(E), page 44, C.1.5.2, "repeating leaders
      // and directories").
      //
      // PLEASE NOTE THAT THIS ASSUMES THAT ALL SUBSEQUENT RECORDS HAVE
      // IDENTICAL RECORD LENGTHS AND FORMATS.  The behavior of put()
      // is undefined for records that do not match the format found in
      // the last leader and directory.

   private:

      sio_8211Writer(); // made private because of embedded reference

      sio_8211Writer_Imp* _imp;

      bool _makeDDR();

}; // class sio_Writer


#endif
