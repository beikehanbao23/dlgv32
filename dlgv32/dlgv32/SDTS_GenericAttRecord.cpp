// SDTS_GenericAttRecord.cpp - implementation of SDTS_GenericAttRecord class
//
// Developed by: Mike Childs
//      Started: 12/9/97

#include "SDTS_AttRecord.h"
#include "SDTS_Utils.h"
#include "sdtsxx/container/sc_Record.h"

SDTS_GenericAttRecord::SDTS_GenericAttRecord( sc_Record& record )
: SDTS_AttRecord(record)
{
    // Get the Attribute Primary or Secondary field
    sc_FieldCntr::const_iterator curField;
    if ( !SDTS_Utils::getFieldByMnem( record, "ATTP", curField ) )
    {
        // It's not an attribute primary, check for attribute secondary
        if ( !SDTS_Utils::getFieldByMnem( record, "ATTS", curField ) )
        {
            return;
        }
    }

    // Get each attribute and it's value and push it into the attribute value pair
    char strTemp[10];
    string strName;
    string strValue;
    for ( sc_SubfieldCntr::const_iterator i = curField->begin(); i != curField->end(); i++ )
    {
        // Get the subfield name and value
        strName = i->getName();
        const sc_MultiTypeValue& val = i->getValue();

        // Conver the Multi-value to a string
        switch ( val.getValueType() )
        {
            case sc_MultiTypeValue::isLong:
                long lVal;
                val.getLong( lVal );
                sprintf( strTemp, "%ld", lVal );
                strValue = strTemp;
                break;
            case sc_MultiTypeValue::isUnsignedLong:
                unsigned long ulVal;
                val.getUnsignedLong( ulVal );
                sprintf( strTemp, "%lu", ulVal );
                strValue = strTemp;
                break;
            case sc_MultiTypeValue::isDouble:
                double dVal;
                val.getDouble( dVal );
                sprintf( strTemp, "%g", dVal );
                strValue = strTemp;
                break;
            case sc_MultiTypeValue::isString:
                val.getString( strValue );
                break;
        }

        // Get rid of trailing spaces in the name and value
        trimRight( strName );
        trimRight( strValue );

        d_pairs.push_back( SDTSAtt_LabelValuePair( strName, strValue ) );
    }
}

void
SDTS_GenericAttRecord::getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const
{
    // Stick all of the value pairs in the vector passed in
    for ( vector<SDTSAtt_LabelValuePair>::const_iterator i = d_pairs.begin(); 
          i != d_pairs.end(); i++ )
    {
        pairs.push_back( *i );
    }
}
