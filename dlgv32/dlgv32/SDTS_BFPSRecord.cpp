// SDTS_BFPSRecord.cpp - implementation of SDTS_BFPSRecord class
//
// Developed by: Mike Childs
//      Started: 10/11/97

#include "SDTS_AttRecord.h"
#include "SDTS_Utils.h"
#include "sdtsxx/container/sc_Record.h"

SDTS_BFPSRecord::SDTS_BFPSRecord( sc_Record& record )
: SDTS_AttRecord(record)
{
    // Get the primary attributes field, abort if there isn't one
    sc_FieldCntr::const_iterator curField;
    if ( !SDTS_Utils::getFieldByMnem( record, "ATTS", curField ) )
    {
        return;
    }

    // Get the STATE subfield
    sc_SubfieldCntr::const_iterator curSubfield;
    if ( SDTS_Utils::getSubfieldByName( *curField, "STATE             ", curSubfield ) )
    {
        curSubfield->getA( d_strStateFIPS );
        trimRight( d_strStateFIPS );
    }

    // Get the STATE_NAME subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "STATE_NAME        ", curSubfield ) )
    {
        curSubfield->getA( d_strStateName );
        trimRight( d_strStateName );
    }
}

void
SDTS_BFPSRecord::getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const
{
    if ( !d_strStateName.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "STATE_NAME", d_strStateName ) );
    }
}

bool 
SDTS_BFPSRecord::checkForForeignKeyMatch( const vector<SDTS_AttForeignKey>& foreignKeys ) const
{
    // Find the STATE field of the foreign keys
    for ( vector<SDTS_AttForeignKey>::const_iterator i = foreignKeys.begin();
          i != foreignKeys.end(); i++ )
    {
        if ( i->getForeignKeyFieldName() == "STATE             " )
        {
            // Check for a value match
            if ( i->getForeignKeyValue() == d_strStateFIPS )
            {
                return true;
            }
        }
    }

    return false;
}