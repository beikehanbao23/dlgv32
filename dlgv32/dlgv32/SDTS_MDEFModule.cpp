// SDTS_MDEFModule.cpp - implementation of SDTS_MDEFModule class
//
// Developed by: Mike Childs
//      Started: 11/17/97

#include "SDTS_MDEFModule.h"
#include <fstream>

// SDTS includes
#include "SDTS_Utils.h"
#include "sdtsxx/container/sc_Record.h"
#include "sdtsxx/io/sio_Reader.h"

SDTS_MDEFModule::~SDTS_MDEFModule()
{
    // Delete all the MDEF records
    for ( list<MDEFRecord*>::iterator i = d_records.begin(); i != d_records.end(); i++ )
    {
        delete (*i);
    }
}

const string&
SDTS_MDEFModule::getEntityDesc( const string& strEntityLabel )
{
    // Look through all the records until we find a match
    for ( list<MDEFRecord*>::iterator i = d_records.begin(); i != d_records.end(); i++ )
    {
        if ( strEntityLabel == (*i)->d_strEntityLabel )
        {
            // We found a match!
            return (*i)->d_strText;
        }
    }

    return "";
}

bool
SDTS_MDEFModule::loadFromFile( const string& strFilename )
{
    // Make sure the filename isn't null
    if ( '\0' == strFilename.c_str()[0] )
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
    sc_FieldCntr::const_iterator curField;
    sc_SubfieldCntr::const_iterator curSubfield;
    string strTemp;
    MDEFRecord* pMDEFRec;
    for ( sio_8211ForwardIterator i( reader ); !i.done(); ++i )
    {
        // Get the record
        i.get( record );

        // Make sure this is a MDEF module record
        if ( SDTS_Utils::getFieldByMnem( record, "DDDF", curField )  )
        {
            // Make sure this is an entity record
            if ( SDTS_Utils::getSubfieldByMnem( *curField, "EORA", curSubfield ) )
            {
                // Make sure it equals "ENT"
                curSubfield->getA( strTemp );
                if ( "ENT" != strTemp )
                {
                    continue;
                }
            }
            else
            {
                continue;
            }

            // Create a new MDEF Record
            pMDEFRec = new MDEFRecord();

            // Get the entity label
            if ( SDTS_Utils::getSubfieldByMnem( *curField, "EALB", curSubfield ) )
            {
                curSubfield->getA( pMDEFRec->d_strEntityLabel );
            }

            // Get the definition for the label
            if ( SDTS_Utils::getSubfieldByMnem( *curField, "DFIN", curSubfield ) )
            {
                curSubfield->getA( pMDEFRec->d_strText );
            }

            // Add the MDEF record to the vector
            d_records.push_back( pMDEFRec );
        }
    }

    // Close the ddf stream
    ddf.close();

    return true;
}