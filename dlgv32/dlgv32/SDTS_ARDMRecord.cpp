// SDTS_ARDMRecord.cpp - implementation of SDTS_ARDMRecord class
//
// Developed by: Mike Childs
//      Started: 10/9/97

#include "SDTS_AttRecord.h"
#include "SDTS_Utils.h"
#include "sdtsxx/container/sc_Record.h"

SDTS_ARDMRecord::SDTS_ARDMRecord( sc_Record& record )
: SDTS_AttRecord(record)
{
    // Get the primary attributes field, abort if there isn't one
    sc_FieldCntr::const_iterator curField;
    if ( !SDTS_Utils::getFieldByMnem( record, "ATTP", curField ) )
    {
        return;
    }

    // Get the ROUTE_NUMBER subfield
    sc_SubfieldCntr::const_iterator curSubfield;
    if ( SDTS_Utils::getSubfieldByName( *curField, "ROUTE_NUMBER      ", curSubfield ) )
    {
        curSubfield->getA( d_strRouteNumber );
        trimRight( d_strRouteNumber );
    }

    // Get the ROUTE_TYPE subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "ROUTE_TYPE        ", curSubfield ) )
    {
        curSubfield->getA( d_strRouteType );
        trimRight( d_strRouteType );
    }
}

void
SDTS_ARDMRecord::getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const
{
    if ( !d_strRouteType.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "ROUTE_TYPE", d_strRouteType ) );
    }

    if ( !d_strRouteNumber.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "ROUTE_NUMBER", d_strRouteNumber ) );
    }
}
