// SDTS_BMTARecord.cpp - implementation of SDTS_BMTARecord class
//
// Developed by: Mike Childs
//      Started: 10/11/97

#include "SDTS_AttRecord.h"
#include "SDTS_Utils.h"
#include "sdtsxx/container/sc_Record.h"

SDTS_BMTARecord::SDTS_BMTARecord( sc_Record& record )
: SDTS_AttRecord(record)
{
    // Get the primary attributes field, abort if there isn't one
    sc_FieldCntr::const_iterator curField;
    if ( !SDTS_Utils::getFieldByMnem( record, "ATTS", curField ) )
    {
        return;
    }

    // Get the AIRPORT subfield
    sc_SubfieldCntr::const_iterator curSubfield;
    if ( SDTS_Utils::getSubfieldByName( *curField, "AIRPORT           ", curSubfield ) )
    {
        curSubfield->getA( d_strAirport );
        trimRight( d_strAirport );
    }

    // Get the AIRPORT_NAME subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "AIRPORT_NAME      ", curSubfield ) )
    {
        curSubfield->getA( d_strAirportName );
        trimRight( d_strAirportName );
    }
}

void
SDTS_BMTARecord::getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const
{
    if ( !d_strAirportName.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "AIRPORT_NAME", d_strAirportName ) );
    }
}

bool 
SDTS_BMTARecord::checkForForeignKeyMatch( const vector<SDTS_AttForeignKey>& foreignKeys ) const
{
    // Find the AIRPORT field of the foreign keys
    for ( vector<SDTS_AttForeignKey>::const_iterator i = foreignKeys.begin();
          i != foreignKeys.end(); i++ )
    {
        if ( i->getForeignKeyFieldName() == "AIRPORT           " )
        {
            // Check for a value match
            if ( i->getForeignKeyValue() == d_strAirport )
            {
                return true;
            }
        }
    }

    return false;
}