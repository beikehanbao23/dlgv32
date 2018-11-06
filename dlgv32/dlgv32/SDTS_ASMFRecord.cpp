// SDTS_ASMFRecord.cpp - implementation of SDTS_ASMFRecord class
//
// Developed by: Mike Childs
//      Started: 10/11/97

#include "SDTS_AttRecord.h"
#include "SDTS_Utils.h"
#include "sdtsxx/container/sc_Record.h"

// Define bitmasks for boolean values stored in flags variable

SDTS_ASMFRecord::SDTS_ASMFRecord( sc_Record& record )
: SDTS_AttRecord(record), d_elevation(9999.99)
{
    // Get the primary attributes field, abort if there isn't one
    sc_FieldCntr::const_iterator curField;
    if ( !SDTS_Utils::getFieldByMnem( record, "ATTP", curField ) )
    {
        return;
    }

    // Get the ENTITY_LABEL subfield
    sc_SubfieldCntr::const_iterator curSubfield;
    if ( SDTS_Utils::getSubfieldByName( *curField, "ENTITY_LABEL      ", curSubfield ) )
    {
        curSubfield->getA( d_strEntityLabel );
        trimRight( d_strEntityLabel );
    }

    // Get the STATE subfield
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

    // Get the ELEVATION subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "ELEVATION         ", curSubfield ) )
    {
        curSubfield->getR( d_elevation );
    }
}

void
SDTS_ASMFRecord::getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const
{
    if ( 9999.99 != d_elevation )
    {
        char strElevation[20];
        sprintf( strElevation, "%g", d_elevation );
        pairs.push_back( SDTSAtt_LabelValuePair( "ELEVATION", strElevation ) );
    }

    if ( !d_strCountyFIPS.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "COUNTY", d_strCountyFIPS ) );
    }

    if ( !d_strStateFIPS.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "STATE", d_strStateFIPS ) );
    }

    if ( !d_strEntityLabel.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "ENTITY_LABEL", d_strEntityLabel ) );
    }
}   
