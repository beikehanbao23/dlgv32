// SDTS_ABDMRecord.cpp - implementation of SDTS_ABDMRecord class
//
// Developed by: Mike Childs
//      Started: 10/11/97

#include "SDTS_AttRecord.h"
#include "SDTS_Utils.h"
#include "sdtsxx/container/sc_Record.h"

// Define bitmasks for boolean values stored in flags variable

SDTS_ABDMRecord::SDTS_ABDMRecord( sc_Record& record )
: SDTS_AttRecord(record), d_agency(-1)
{
    // Get the primary attributes field, abort if there isn't one
    sc_FieldCntr::const_iterator curField;
    if ( !SDTS_Utils::getFieldByMnem( record, "ATTP", curField ) )
    {
        return;
    }

    // Get the AGENCY subfield
    sc_SubfieldCntr::const_iterator curSubfield;
    if ( SDTS_Utils::getSubfieldByName( *curField, "AGENCY            ", curSubfield ) )
    {
        curSubfield->getI( d_agency );
    }
}

void
SDTS_ABDMRecord::getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const
{
    if ( -1 != d_agency )
    {
        char strTemp[10];
        sprintf( strTemp, "%ld", d_agency );
        pairs.push_back( SDTSAtt_LabelValuePair( "AGENCY", strTemp ) );
    }
}
