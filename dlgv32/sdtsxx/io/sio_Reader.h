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
#ifndef INCLUDED_SIO_READER_H
#define INCLUDED_SIO_READER_H
//
// sio_Reader.h
//


#ifdef WIN32

#pragma warning( disable : 4786 )

#include <list>
#include <map>

using namespace std;

#else

#include <list.h>
#include <map.h>

#endif



#ifndef INCLUDED_SIO_8211DR_H
#include "io/sio_8211DR.h"
#endif

#ifndef INCLUDED_SIO8211FIELDFORMAT_H
#include "io/sio_8211FieldFormat.h"
#endif


class sio_8211Converter;

/**

  This provides a prototypical interface for all SDTS readers.

 
XXX	 One possible change would be to follow more along the Iterator pattern,
XXX	 as described by Gamma, et al.  That is, the client goes to the container
XXX	 to fetch an iterator instance.  The container and iterator all inhereit
XXX	 from ABC containers and iterators.  In my model, there'd be an ABC reader
XXX	 and corresponding iterator; an iterator would be grabbed via a
XXX	 reader::createIterator().  The 8211 reader and iterator would, of course,
XXX	 specialize and implement the appropriate functions.  Moreover, the 8211
XXX	 reader would be sio_8211SequentialReader -- an random access reader would
XXX	 inherent, in turn, from that.  After all, a random access reader is basically
XXX	 the same, except that it has some additional features.

  */
class
sio_Reader
{
public:

   /** 
      A reader accepts a stream and a associative container.  This container
      maps a subfield label to an appropriate converter function.

      XXX _Nothing_ related to 8211 should be in this ABC.
   */
	sio_8211Reader( istream & is, 
                   const map<string, sio_8211Converter*> * converters = 0 );

	// sio_Reader( const sio_Reader& ) NOT NEEDED

	// operator=(  const sio_Reader& ) NOT NEEDED

	///
	virtual ~sio_Reader() = 0;

}; // class sio_Reader



class sio_8211Reader_Imp;
class sc_Record;

/**

  A reader for 8211 files.

  */
class
sio_8211Reader : public sio_Reader
{
public:

	sio_8211Reader( istream & is, const map<string, sio_8211Converter*> * converters = 0);

	~sio_8211Reader();

   // returns the schema that the reader built from the DDR
   list<sio_8211FieldFormat> & getSchema();

private:


	sio_8211Reader();											// not allowed
	sio_8211Reader( const sio_Reader& );				// not allowed
	sio_8211Reader& operator=( const sio_Reader& );	// now allowed


   sio_8211Reader_Imp* _imp; // implementation guts


   // helper function to fill the given sc_Record with the contents
   // found in the 8211 DR
	bool _fillScRecord( sio_8211DR const & dr, sc_Record& record );

   // same function as above, but the DR found at the given offset
   // is found first -- the the previous function is called
	bool _fillScRecord( long DRoffset, sc_Record& record );

	friend class sio_8211ForwardIterator;

}; // class sio_8211Reader




class sc_Record;



/**

  Prototypical forward iterator.


  */
class sio_ForwardIterator
{
public:

   ///
	virtual ~sio_ForwardIterator( ) {}

	// sio_ForwardIterator( sio_ForwardIterator const & ); NOT NEEDED
	// sio_ForwardIterator& operator=( sio_ForwardIterator const & ); NOT NEEDED

	/// returns true if get successful, else false
	virtual bool get( sc_Record& record )  = 0;

	/// sets to next DR
	virtual void operator++() = 0;

	/// returns non-zero if no more data or reader is in error state
	virtual bool done() const = 0;

	/// returns a non-null void * if there's still more data to read
	virtual operator void*() const = 0;

}; // class sio_ForwardIterator




class sio_8211ForwardIterator : public sio_ForwardIterator
{
public:
	
	sio_8211ForwardIterator( sio_8211Reader& reader ) ;

	/**
		This could've been an STL style operator*().  However, this implies that
		this class keeps its own copy of an sc_Record that it passes a reference from.
		In some cases, this additional copy is inefficient.  This member allows for
		the use of a single sc_Record.
	*/
	bool get( sc_Record& record ) ;

	void operator++();

	bool done() const;

   virtual operator void*() const;


private:

	// These guys are private all because of the reader reference.  (Although
	// the copy ctor should actually be ok.)  However, once this class is
	// fully insulated, then these guys can return to the public interface.

	sio_8211ForwardIterator( );			// not allowed
	sio_8211ForwardIterator( sio_ForwardIterator const & ); // not allowed
	sio_8211ForwardIterator& operator=( sio_ForwardIterator const & ); // not allowed


	long _DR_end;						// stream positioned just past current 
											// DR end
	sio_8211DR _DR;

	sio_8211Reader& _reader;

   bool _isDone;                 // true iff the iterator is pointing of the 
                                 // DA's "end"  XXX seems kludgy, but makes
                                 // iterator done() more intuitive and fixes
                                 // premature finishing behavior.

}; // class sio_8211ForwardIterator




#endif //INCLUDED_SIO_READER_H
