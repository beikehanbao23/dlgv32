// SDTS_BGRLRecord.cpp - implementation of SDTS_BGRLRecord class
//
// Developed by: Mike Childs
//      Started: 10/11/97

#include "SDTS_AttRecord.h"
#include "SDTS_Utils.h"
#include "sdtsxx/container/sc_Record.h"

SDTS_BGRLRecord::SDTS_BGRLRecord( sc_Record& record )
: SDTS_AttRecord(record)
{
    // Get the primary attributes field, abort if there isn't one
    sc_FieldCntr::const_iterator curField;
    if ( !SDTS_Utils::getFieldByMnem( record, "ATTS", curField ) )
    {
        return;
    }

    // Get the LAND_GRANT subfield
    sc_SubfieldCntr::const_iterator curSubfield;
    if ( SDTS_Utils::getSubfieldByName( *curField, "LAND_GRANT        ", curSubfield ) )
    {
        curSubfield->getA( d_strLandGrant );
        trimRight( d_strLandGrant );
    }

    // Get the LAND_GRANT_NAME subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "LAND_GRANT_NAME   ", curSubfield ) )
    {
        curSubfield->getA( d_strLandGrantName );
        trimRight( d_strLandGrantName );
    }
}

void
SDTS_BGRLRecord::getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const
{
    if ( !d_strLandGrantName.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "LAND_GRANT_NAME", d_strLandGrantName ) );
    }
}

bool 
SDTS_BGRLRecord::checkForForeignKeyMatch( const vector<SDTS_AttForeignKey>& foreignKeys ) const
{
    // Find the LAND_GRANT field of the foreign keys
    for ( vector<SDTS_AttForeignKey>::const_iterator i = foreignKeys.begin();
          i != foreignKeys.end(); i++ )
    {
        if ( i->getForeignKeyFieldName() == "LAND_GRANT        " )
        {
            // Check for a value match
            if ( i->getForeignKeyValue() == d_strLandGrant )
            {
                return true;
            }
        }
    }

    return false;
}