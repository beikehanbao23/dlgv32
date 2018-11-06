// SDTS_BMSPRecord.cpp - implementation of SDTS_BMSPRecord class
//
// Developed by: Mike Childs
//      Started: 10/11/97

#include "SDTS_AttRecord.h"
#include "SDTS_Utils.h"
#include "sdtsxx/container/sc_Record.h"

SDTS_BMSPRecord::SDTS_BMSPRecord( sc_Record& record )
: SDTS_AttRecord(record), d_population(-1)
{
    // Get the primary attributes field, abort if there isn't one
    sc_FieldCntr::const_iterator curField;
    if ( !SDTS_Utils::getFieldByMnem( record, "ATTS", curField ) )
    {
        return;
    }

    // Get the POPULATED_PLACE subfield
    sc_SubfieldCntr::const_iterator curSubfield;
    if ( SDTS_Utils::getSubfieldByName( *curField, "POPULATED_PLACE   ", curSubfield ) )
    {
        curSubfield->getA( d_strPopulatedPlace );
        trimRight( d_strPopulatedPlace );
    }

    // Get the POP_PLACE_NAME subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "POP_PLACE_NAME    ", curSubfield ) )
    {
        curSubfield->getA( d_strPopPlaceName );
        trimRight( d_strPopPlaceName );
    }
    
    // Get the COUNTY subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "COUNTY            ", curSubfield ) )
    {
        curSubfield->getA( d_strCounty );
        trimRight( d_strCounty );
    }

    // Get the POPULATION subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "POPULATION        ", curSubfield ) )
    {
        curSubfield->getI( d_population );
    }
}

void
SDTS_BMSPRecord::getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const
{
    if ( d_population >= 0 )
    {
        char strTemp[20];
        sprintf( strTemp, "%ld", d_population );
        pairs.push_back( SDTSAtt_LabelValuePair( "POPULATION", strTemp ) );
    }

    if ( !d_strPopPlaceName.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "POP_PLACE_NAME", d_strPopPlaceName ) );
    }
}

bool 
SDTS_BMSPRecord::checkForForeignKeyMatch( const vector<SDTS_AttForeignKey>& foreignKeys ) const
{
    // Find the POPULATED_PLACE field of the foreign keys
    for ( vector<SDTS_AttForeignKey>::const_iterator i = foreignKeys.begin();
          i != foreignKeys.end(); i++ )
    {
        if ( i->getForeignKeyFieldName() == "POPULATED_PLACE   " )
        {
            // Check for a value match
            if ( i->getForeignKeyValue() == d_strPopulatedPlace )
            {
                return true;
            }
        }
    }

    return false;
}