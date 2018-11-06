// SDTS_AttRecord.cpp - implementation of SDTS_AttRecord class
//
// Developed by: Mike Childs
//      Started: 10/9/97

#include "SDTS_AttRecord.h"
#include "SDTS_Utils.h"
#include "sdtsxx/container/sc_Record.h"

SDTS_AttRecord::SDTS_AttRecord( sc_Record& record )
: d_recordID(-1)
{
    // Get the attributes field, abort if there isn't one
    sc_FieldCntr::const_iterator curField;
    if ( !SDTS_Utils::getFieldByMnem( record, "ATPR", curField ) && 
         !SDTS_Utils::getFieldByMnem( record, "ATSC", curField ) )
    {       
        return;
    }

    // Get the RCID subfield
    sc_SubfieldCntr::const_iterator curSubfield;
    if ( SDTS_Utils::getSubfieldByMnem( *curField, "RCID", curSubfield ) )
    {
        curSubfield->getI( d_recordID );
    }
}

const string&
SDTS_AttRecord::trimRight( string& str )
{
    // Get rid of all trailing spaces and tabs
    str.resize( str.find_last_not_of( " \t" ) + 1 );
    return str;
}
