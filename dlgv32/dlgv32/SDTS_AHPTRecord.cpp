// SDTS_AHPTRecord.cpp - implementation of SDTS_AHPTRecord class
//
// Developed by: Mike Childs
//      Started: 10/11/97

#include "SDTS_AttRecord.h"
#include "SDTS_Utils.h"
#include "sdtsxx/container/sc_Record.h"

// Define bitmasks for boolean values stored in flags variable

SDTS_AHPTRecord::SDTS_AHPTRecord( sc_Record& record )
: SDTS_AttRecord(record), d_elevation(-9999.99)
{
    // Get the primary attributes field, abort if there isn't one
    sc_FieldCntr::const_iterator curField;
    if ( !SDTS_Utils::getFieldByMnem( record, "ATTP", curField ) )
    {
        return;
    }

    // Get the ELEVATION subfield
    sc_SubfieldCntr::const_iterator curSubfield;
    if ( SDTS_Utils::getSubfieldByName( *curField, "ELEVATION         ", curSubfield ) )
    {
        curSubfield->getR( d_elevation );
    }
}

void
SDTS_AHPTRecord::getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const
{
    if ( -9999.99 != d_elevation )
    {
        char strTemp[20];
        sprintf( strTemp, "%g feet", d_elevation );
        pairs.push_back( SDTSAtt_LabelValuePair( "ELEVATION", strTemp ) );
    }
}