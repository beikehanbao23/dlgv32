// SDTS_ACOIRecord.cpp - implementation of SDTS_ACOIRecord class
//
// Developed by: Mike Childs
//      Started: 10/11/97

#include "SDTS_AttRecord.h"
#include "SDTS_Utils.h"
#include "sdtsxx/container/sc_Record.h"

// Define bitmasks for boolean values stored in flags variable

SDTS_ACOIRecord::SDTS_ACOIRecord( sc_Record& record )
: SDTS_AttRecord(record)
{
    // Get the primary attributes field, abort if there isn't one
    sc_FieldCntr::const_iterator curField;
    if ( !SDTS_Utils::getFieldByMnem( record, "ATTP", curField ) )
    {
        return;
    }

    // Get the COINCIDENT subfield
    sc_SubfieldCntr::const_iterator curSubfield;
    if ( SDTS_Utils::getSubfieldByName( *curField, "COINCIDENT        ", curSubfield ) )
    {
        curSubfield->getA( d_strCoincident );
        trimRight( d_strCoincident );
    }
}

void
SDTS_ACOIRecord::getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const
{
    if ( !d_strCoincident.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "COINCIDENT", d_strCoincident ) );
    }
}