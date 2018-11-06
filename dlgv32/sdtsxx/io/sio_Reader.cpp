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
// sio_Reader.cpp
//

#include "io/sio_Reader.h"

#include <algorithm>
#include <istream>

#ifndef INCLUDED_SIO_8211DIRECTORY_H
#include "io/sio_8211Directory.h"
#endif

#ifndef INCLUDED_SIO_8211DIRENTRY_H
#include "io/sio_8211DirEntry.h"
#endif

#ifndef INCLUDED_SIO_8211LEADER_H
#include "io/sio_8211Leader.h"
#endif

#ifndef INCLUDED_SIO_8211DDRLEADER_H
#include "io/sio_8211DDRLeader.h"
#endif

#ifndef INCLUDED_SIO_8211DDR_H
#include "io/sio_8211DDR.h"
#endif

#ifndef INCLUDED_SIO_8211DR_H
#include "io/sio_8211DR.h"
#endif

#ifndef INCLUDED_SIO_8211DDRFIELD_H
#include "io/sio_8211DDRField.h"
#endif

#ifndef INCLUDED_SIO_8211FIELD_H
#include "io/sio_8211Field.h"
#endif

#ifndef INCLUDED_SIO_CONVERTER_H
#include "io/sio_Converter.h"
#endif

#ifndef INCLUDED_SIO_8211CONVERTER_H
#include "io/sio_8211Converter.h"
#endif

#ifndef INCLUDED_SC_RECORD_H
#include "container/sc_Record.h"
#endif

#ifdef WIN32
#pragma warning(once:4786)
#endif

// Even though this is a pure virtual function, we can still
// define it.
sio_Reader::~sio_Reader()
   {
   } // sio_Reader dtor



//
// The guts for an sio_8211Reader object.
//
class sio_8211Reader_Imp
   {
   public:   

      sio_8211Reader_Imp( istream& file ) : _file( file ) {}


	   istream& _file;									// stream to an open 8211 file

	   sio_8211DDR _ddr;

	   list<sio_8211FieldFormat> _fieldFormats;

	   long _DRStart;									   // offset for first DR

   private:

      sio_8211Reader_Imp();                     // private due to reference
      sio_8211Reader_Imp( sio_8211Reader_Imp const &);// not needed

   }; // struct sio_8211Reader_Imp



#ifdef WIN32
#pragma warning( disable : 4786 )
#endif

sio_8211Reader::sio_8211Reader( istream & is, 
										  const map<string, sio_8211Converter*> * converters ) 
	: _imp(  new sio_8211Reader_Imp( is )  )
{
	_imp->_file >> _imp->_ddr; // grab the DDR

   if ( ! _imp->_file )
	{
		// XXX error handling
		return;
	}

   // After we read the DDR, the stream pointer will be sitting at the first
   // character in the first DR.  Remember that location in _DRStart.
	_imp->_DRStart = _imp->_file.tellg();

   // Now we need to build the field format "dictionary" that we'll later
   // use to properly parse a DR.
	//sio_8211Directory const & ddr_directory = _imp->_ddr.getDirectory();

	for ( sio_8211Directory::const_iterator dir_entry = 
            _imp->_ddr.getDirectory().begin();
		   dir_entry != _imp->_ddr.getDirectory().end();
			dir_entry++ )
	{

		if ( dir_entry->getTag().substr(0,3) == "000" )
		{
			continue;				// this must be reserved field, skip it
		}

										// build a ddr field given the DDR's leader
										// and the current field data

										// XXX This will need to change in the same way
										// XXX that DDRField changed.  That is, we get
										// XXX a leader and explicitly morph it into a 
										// XXX DDRLeader.

		sio_8211DDRLeader const * const ddr_leader = 
			dynamic_cast<sio_8211DDRLeader const * const>(&(_imp->_ddr.getLeader()));

		if ( ! ddr_leader ) return ; // XXX add error handling


										// XXX for some reason, I can't pass in
										// XXX the results of getField() directory to
										// XXX sio_8211DDRField's ctor.

		sio_8211Field const * field = dir_entry->getField();
		sio_8211DDRField ddr_field( *ddr_leader, *field );


		_imp->_fieldFormats.push_back( sio_8211FieldFormat() );


		sio_8211MakeFieldFormat( _imp->_fieldFormats.back(),
										 ddr_field,
										 dir_entry->getTag(), 
										 converters );

	} // for each DDR field tag


} // sio_8211Reader ctor



sio_8211Reader::~sio_8211Reader()
   {
      delete _imp;
   } // sio_8211Reader dtor




list<sio_8211FieldFormat> &
sio_8211Reader::getSchema()
{
   return _imp->_fieldFormats;
} // sio_8211Reader::getSchema() const


// fills the given sc_field with the subfields found in the given 8211 field
//
// Returns: < 0 if error, 0 if ok, > 0 for the field_data_pos if there're more fields
//				to read.
// 
// Fields of the same type that occur consecutively are called repeating fields.  If a field
// is processed and there's more "space" left over, then chances are you are dealing
// with repeating fields.  To deal with repeating fields, I return the last data position 
// of the current field.  That way the caller can invoke this function again with 
// the given data position so that the next field can be read.

static
int
_fillScField( sio_8211Field const &       dr_field, 
				  sio_8211FieldFormat const & field_format,
				  sc_Field&                   sc_field,
              long                        field_data_pos = 0 )
{
	const char * field_data        = dr_field.getData() + field_data_pos;
	const long   field_data_length = dr_field.getDataLength();
	

	sc_field.setMnemonic( field_format.getTag() );
	sc_field.setName( field_format.getName() );

								// SDTS attributes treat their subfields differently.

	bool is_attribute  = (field_format.getTag() == "ATTP" ||
								 field_format.getTag() == "ATTS" );


	sc_Field::iterator sc_subfield_itr = sc_field.begin();


	for ( list<sio_8211SubfieldFormat>::const_iterator subfield_format_itr = 
				field_format.begin(); 
		   subfield_format_itr != field_format.end();
			subfield_format_itr++, sc_subfield_itr++ )
	   {
      // This function takes into consideration that the client may be
      // reusing a sc_Field container.  If they are, then the iterator
      // will be pointing to the first subfield; in which case, we do nothing
      // here and just over-write the subfield that the iterator points at.
      // On the other hand, this could be a "virgin" sc_Field container --
      // we'll know that if the iterator is pointing off the end of the container.
      // In that case, we just insert a new subfield.  But.  We still need
      // a valid iterator.  So, we do everything in a oner: we insert a new
      // subfield just before the "end" of the container and take the resulting
      // iterator and use that for this current iteration. [1]

		   if ( sc_subfield_itr == sc_field.end() )
   		{
	   		sc_subfield_itr = sc_field.insert( sc_field.end(), sc_Subfield() );
		   }
								// set the subfield name (or mnemonic) first
		   if ( is_attribute )
   		{
	   		sc_subfield_itr->setName( subfield_format_itr->getLabel() );
		   }
   		else
	   	{
		   	sc_subfield_itr->setMnemonic( subfield_format_itr->getLabel() );
   		}  
	
								// fill the actual subfield value

	   	if ( subfield_format_itr->getConverter() )
		   {
   			long chunk_size; // how much data was converted in characters

            // now call the converter bound to the current subfield type to
            // convert the raw DR subfield into a proper sc_Subfield
	   		switch ( subfield_format_itr->getFormat() )
		   	{
			   case sio_8211SubfieldFormat::fixed : 
				   chunk_size =
					   subfield_format_itr->getConverter()->makeFixedSubfield( &(*sc_subfield_itr),
						   															        field_data, 
							   														        subfield_format_itr->getLength() );
				   break;
			   case sio_8211SubfieldFormat::variable :
				   chunk_size =
					   subfield_format_itr->getConverter()->makeVarSubfield( &(*sc_subfield_itr),
		   																	 		      field_data, 
			   																		      field_data_length - field_data_pos,
				   																	      subfield_format_itr->getDelimiter() );
   				field_data++;		// skip unit terminator
	   			field_data_pos++;
		   		break;
			   }
   			field_data     += chunk_size;
	   		field_data_pos += chunk_size;
		   }
		else
		   {  // XXX Yes, Virginia, there is such a thing as good error handling.
#ifdef DEBUG
			   cerr << subfield_format_itr->getLabel()
				     << " had no converter" << endl;
#endif
            return -1;
	   	}
	}

								// if we've re-used this subfield container, then
								// there may be some leftover subfields at the end;
								// if so, clean this up

	if ( sc_subfield_itr != sc_field.end() )
	{
		sc_field.erase( sc_subfield_itr, sc_field.end() );
	}


   // if the field data position is less than the length, then we're likely
   // dealing with a repeating field; so, return the position so that the
   // caller can invoke this function again to pick up the next field.
   // Otherwise, return zero indicating everything is ok.

   return ( field_data_pos < field_data_length ) ? field_data_pos : 0;

} // _fillScField





bool 
sio_8211Reader::_fillScRecord( sio_8211DR const & dr, sc_Record& sc_record )
{

	sio_8211Directory const& dr_directory = dr.getDirectory();


	list<sio_8211FieldFormat>::const_iterator field_format_itr;


	list<sc_Field>::iterator sc_field_itr = sc_record.begin();


   long field_data_pos = 0;

								// enumerate each DR field, converting and adding them
								// to the sc_record

	for ( sio_8211Directory::const_iterator dir_entry = dr_directory.begin();
		   dir_entry != dr_directory.end();
			dir_entry++ )
	{
										// find the field format
		field_format_itr = find( _imp->_fieldFormats.begin(), _imp->_fieldFormats.end(),
								       dir_entry->getTag() );

		if ( field_format_itr != _imp->_fieldFormats.end() )
		{
			sio_8211Field const * dr_field = dir_entry->getField();

         do
            {
													// if we're not reusing an existing record
													// and its empty, then add the first field
                                       // (see [1], above -- the same kind of thing
                                       // is going on here)

   			   if ( sc_field_itr == sc_record.end() )
	   		      {
		   		      sc_field_itr = sc_record.insert( sc_record.end(), sc_Field() );
			         }


			      field_data_pos = _fillScField( *dr_field,
			   	   			                   (*field_format_itr), 
		   			   		                   (*sc_field_itr),
                                              field_data_pos );

               if ( field_data_pos < 0 ) return false;

   			   sc_field_itr++;

            } 
         while ( field_data_pos > 0 ); // while we've got repeating fields
		}
		else
		{	// XXX Error handling, anyone?  (But for reserved tags, this is ok.)
#ifdef DEBUG
         cerr << "field format for " 
				  << (*dir_entry)->getTag() << " not found" << endl;
#endif
		}

		
	}

								// snip off any fields that may be left over
								// from the last time the record was used

	if ( sc_field_itr != sc_record.end() )
	{
		sc_record.erase( sc_field_itr, sc_record.end() );
	}

	return true;

} // sio_8211Reader::_fillScRecord()




bool 
sio_8211Reader::_fillScRecord( long DRoffset, sc_Record& sc_record )
{
	sio_8211DR dr;

	_imp->_file.seekg( DRoffset );

	_imp->_file >> dr;

	return _fillScRecord( dr, sc_record );

} // sio_8211Reader::_fillScRecord()




sio_8211ForwardIterator::sio_8211ForwardIterator( sio_8211Reader & reader ) 
: _reader( reader ), _isDone( false )
{ 
	// first insure that the reader is at the first DR
	_reader._imp->_file.seekg( _reader._imp->_DRStart );
	
   _reader._imp->_file.peek(); // FORCE stream to set fail bit if seek beyond end


	// if the stream is in an ok state, read in the first DR.

	if ( _reader._imp->_file.good() )
      {
	   // then snarf the first DR
	   _reader._imp->_file >> _DR;

	   // remember where we are because we'll need that information
	   // for operator++()

	   _DR_end = _reader._imp->_file.tellg(); 

	   // check to see if we're dealing with dropped leaders

	   if ( ! _DR.isReusingLeaderAndDirectory() &&
           'R' == _DR.getLeader().getLeaderIdentifier() )
	      {
   		   _DR.reuseLeaderAndDirectory( true );
	      }
      }
   else // in the unlikely event that there are NO DR's ...
      {
         _isDone = true;
      }

} // sio_8211ForwardIterator::ctor



bool
sio_8211ForwardIterator::get( sc_Record& record )
{
   // Set the bad bit if the record read failed -- this could have
   // happened because the proper converter couldn't be found,
   // there was no field terminator for one of 8211 records, or some
   // more mundane I/O related problem.
   if ( ! _reader._fillScRecord( _DR, record ) )
   {
      _reader._imp->_file.setf( ios::badbit );
      return false;
   }
	return true;
} // sio_8211ForwardIterator::get



void
sio_8211ForwardIterator::operator++()
{

	// first seek to where we supposedly left off with the last read as another 
	// iterator may have moved the stream

	_reader._imp->_file.seekg( _DR_end, ios::beg );
	_reader._imp->_file.peek(); // FORCE stream to set fail bit if seek beyond end

	// if the stream is in an ok state, read in the next DR.

	if ( _reader._imp->_file.good() )
   	{
	   	_reader._imp->_file >> _DR;
		   _DR_end = _reader._imp->_file.tellg(); // remember for next ++

		   // check to see if we're dealing with dropped leaders

   		if ( ! _DR.isReusingLeaderAndDirectory() &&
              'R' == _DR.getLeader().getLeaderIdentifier() )
		   {
			   _DR.reuseLeaderAndDirectory( true );
		   }

	   }
   else  // whoopsies ... no such record, so flag that we're done
      {
         _isDone = true;
      }

} // sio_8211ForwardIterator::get




bool
sio_8211ForwardIterator::done() const
{
	return _isDone;
} // sio_8211ForwardIterator::done




sio_8211ForwardIterator::operator void*() const
{
   return ( done() ) ?  reinterpret_cast<void*>(0x0) : 
                        reinterpret_cast<void*>(0x1);
} // sio_8211ForwardIterator::done
