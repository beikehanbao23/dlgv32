// SDTS_AttModule.cpp - implementation of SDTS_AttModule class
//
// Developed by: Mike Childs
//      Started: 9/11/97

#include <fstream>
#include "SDTS_AttModule.h"

// SDTS includes
#include "SDTS_Utils.h"
#include "sdtsxx/container/sc_Record.h"
#include "sdtsxx/io/sio_Reader.h"

// Constructor
SDTS_AttModule::SDTS_AttModule( const string& strName )
: d_allocatorFunc(NULL)
{
    getAllocator( strName );
}

// Destructor
SDTS_AttModule::~SDTS_AttModule()
{
    for ( vector<SDTS_AttRecord*>::iterator i = d_records.begin();
          i != d_records.end(); i++ )
    {
        delete *i;
    }
}

void
SDTS_AttModule::getAllocator( const string& strName )
{
    // Determine which allocator to use
    if ( "AHPF" == strName )
    {
        d_allocatorFunc = allocateAHPF;
    }
    else if ( "AHYF" == strName )
    {
        d_allocatorFunc = allocateAHYF;
    }
    else if ( "ASCF" == strName )
    {
        d_allocatorFunc = allocateASCF;
    }
    else if ( "ANVF" == strName )
    {
        d_allocatorFunc = allocateANVF;
    }
    else if ( "ABDF" == strName )
    {
        d_allocatorFunc = allocateABDF;
    }
    else if ( "ASMF" == strName )
    {
        d_allocatorFunc = allocateASMF;
    }
    else if ( "ARDF" == strName )
    {
        d_allocatorFunc = allocateARDF;
    }
    else if ( "ARRF" == strName )
    {
        d_allocatorFunc = allocateARRF;
    }
    else if ( "AMTF" == strName )
    {
        d_allocatorFunc = allocateAMTF;
    }
    else if ( "AMSF" == strName )
    {
        d_allocatorFunc = allocateAMSF;
    }
    else if ( "APLF" == strName )
    {
        d_allocatorFunc = allocateAPLF;
    }
    else if ( "ACOI" == strName )
    {
        d_allocatorFunc = allocateACOI;
    }
    else if ( "AHPR" == strName )
    {
        d_allocatorFunc = allocateAHPR;
    }
    else if ( "AHPT" == strName )
    {
        d_allocatorFunc = allocateAHPT;
    }
    else if ( "ARDM" == strName )
    {
        d_allocatorFunc = allocateARDM;
    }
    else if ( "ABDM" == strName )
    {
        d_allocatorFunc = allocateABDM;
    }
    else if ( "BFPS" == strName )
    {
        d_allocatorFunc = allocateBFPS;
    }
    else if ( "BFPC" == strName )
    {
        d_allocatorFunc = allocateBFPC;
    }
    else if ( "BMSP" == strName )
    {
        d_allocatorFunc = allocateBMSP;
    }
    else if ( "BMTA" == strName )
    {
        d_allocatorFunc = allocateBMTA;
    }
    else if ( "BGRL" == strName )
    {
        d_allocatorFunc = allocateBGRL;
    }
    else
    {
        // The Generic SDTS Attribute Record allocator is used if
        // a specialized SDTS Attribute Record class doesn't exist
        d_allocatorFunc = allocateGeneric;
    }
}

bool
SDTS_AttModule::loadFromFile( const string& strFilename )
{
    // Make sure the allocator isn't NULL
    if ( NULL == d_allocatorFunc )
    {
        return false;
    }

    // Create an input stream based on the file name
    ifstream ddf( strFilename.c_str(), ios::binary );

	// Abort load if failed to open stream
	if ( !ddf )
	{
		return false;
	}

    // Create a reader for reading in the records
    sio_8211Reader reader( ddf );

    // Read in the records
    sc_Record record;
    for ( sio_8211ForwardIterator i( reader ); !i.done(); ++i )
    {
        // Get the record
        i.get( record );

        // Make sure it's an attribute primary or secondary record
        sc_FieldCntr::const_iterator curField;
        if ( SDTS_Utils::getFieldByMnem( record, "ATPR", curField ) ||
             SDTS_Utils::getFieldByMnem( record, "ATSC", curField ) )
        {
            // Put the record in the record container
            d_records.push_back( d_allocatorFunc( record ) );
        }
    }

    // Close the ddf stream
    ddf.close();

    return true;
}

SDTS_AttRecord* 
SDTS_AttModule::getRecord( unsigned int index ) const
{
    // XXX - Make this use a binary search since the TVP guarantees that the
    //       record IDs will be in order

    // Search through the records until one that matches <index> is found.
    for ( vector<SDTS_AttRecord*>::const_iterator i = d_records.begin();
          i != d_records.end(); i++ )
    {
        if ( index == (*i)->getRecordID() )
        {
            return *i;
        }
        else if ( index < (*i)->getRecordID() )
        {
            // The record ID is larger than what we are looking for therefore
            // the record we want doesn't exist
            return NULL;
        }
    }

    // Record not found, return NULL
    return NULL;
}

void 
SDTS_AttModule::getLabelValuePairsByFK( vector<SDTSAtt_LabelValuePair>& pairs,
                                        const vector<SDTS_AttForeignKey>& foreignKeys ) const
{
    // Find a record whose foreign key matches
    for ( vector<SDTS_AttRecord*>::const_iterator i = d_records.begin();
          i != d_records.end(); i++ )
    {
        // Check to see if the foreign key's match
        if ( (*i)->checkForForeignKeyMatch( foreignKeys ) )
        {
            // It's a match! Get the record's data
            (*i)->getLabelValuePairs( pairs );
            return;
        }
    }
}
