// SDTS_BFPCRecord.cpp - implementation of SDTS_BFPCRecord class
//
// Developed by: Mike Childs
//      Started: 10/11/97

#include "SDTS_AttRecord.h"
#include "SDTS_Utils.h"
#include "sdtsxx/container/sc_Record.h"

SDTS_BFPCRecord::SDTS_BFPCRecord( sc_Record& record )
: SDTS_AttRecord(record)
{
    // Get the secondary attributes field, abort if there isn't one
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

    // Get the COUNTY subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "COUNTY            ", curSubfield ) )
    {
        curSubfield->getA( d_strCountyFIPS );
        trimRight( d_strCountyFIPS );
    }

    // Get the AREA_NAME subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "AREA_NAME         ", curSubfield ) )
    {
        curSubfield->getA( d_strAreaName );
        trimRight( d_strAreaName );
    }
}

void
SDTS_BFPCRecord::getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const
{
    if ( !d_strAreaName.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "AREA_NAME", d_strAreaName ) );
    }
}

bool 
SDTS_BFPCRecord::checkForForeignKeyMatch( const vector<SDTS_AttForeignKey>& foreignKeys ) const
{
    bool statesMatch = false, countiesMatch = false;
    
    // Find the STATE and COUNTY fields of the foreign keys
    for ( vector<SDTS_AttForeignKey>::const_iterator i = foreignKeys.begin();
          i != foreignKeys.end(); i++ )
    {
        if ( i->getForeignKeyFieldName() == "STATE             " )
        {
            // Check for a value match
            if ( i->getForeignKeyValue() == d_strStateFIPS )
            {
                statesMatch = true;
            }
        }

        if ( i->getForeignKeyFieldName() == "COUNTY            " )
        {
            // Check for a value match
            if ( i->getForeignKeyValue() == d_strCountyFIPS )
            {
                countiesMatch = true;
            }
        }
    }

    return ( statesMatch && countiesMatch );
}