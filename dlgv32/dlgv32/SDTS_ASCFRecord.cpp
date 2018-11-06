// SDTS_ASCFRecord.cpp - implementation of SDTS_ASCFRecord class
//
// Developed by: Mike Childs
//      Started: 10/9/97

#include "SDTS_AttRecord.h"
#include "SDTS_Utils.h"
#include "sdtsxx/container/sc_Record.h"

// Define bitmasks for boolean values stored in flags variable
#define ASCF_BEST_ESTIMATE 0x01

SDTS_ASCFRecord::SDTS_ASCFRecord( sc_Record& record )
: SDTS_AttRecord(record), d_flags(0)
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

    // Get the BEST_ESTIMATE subfield
    string strTemp;
    if ( SDTS_Utils::getSubfieldByName( *curField, "BEST_ESTIMATE     ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( strTemp == "Y" )
        {
            d_flags |= ASCF_BEST_ESTIMATE;
        }
    }
}

void
SDTS_ASCFRecord::getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const
{
    if ( d_flags & ASCF_BEST_ESTIMATE )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "BEST_ESTIMATE", "Y" ) );
    }

    if ( !d_strEntityLabel.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "ENTITY_LABEL", d_strEntityLabel ) );
    }
}