// SDTS_APLFRecord.cpp - implementation of SDTS_APLFRecord class
//
// Developed by: Mike Childs
//      Started: 10/11/97

#include "SDTS_AttRecord.h"
#include "SDTS_Utils.h"
#include "sdtsxx/container/sc_Record.h"

// Define bitmasks for boolean values stored in flags variable
#define APLF_ID_IN_FIELD            0x01
#define APLF_WITH_HORIZONTAL        0x02
#define APLF_WITH_ELEVATION         0x04
#define APLF_APPROXIMATE_POS        0x08
#define APLF_PROTRACTED_POS         0x10
#define APLF_BEST_ESTIMATE          0x20

SDTS_APLFRecord::SDTS_APLFRecord( sc_Record& record )
: SDTS_AttRecord(record), d_flags(0), d_surveyOrigin(-9)
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

    // Get the ID_IN_FIELD subfield
    string strTemp;
    if ( SDTS_Utils::getSubfieldByName( *curField, "ID_IN_FIELD       ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= APLF_ID_IN_FIELD;
        }
    }
    
    // Get the WITH_HORIZONTAL field
    if ( SDTS_Utils::getSubfieldByName( *curField, "WITH_HORIZONTAL   ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= APLF_WITH_HORIZONTAL;
        }
    }
    
    // Get the WITH_ELEVATION field
    if ( SDTS_Utils::getSubfieldByName( *curField, "WITH_ELEVATION    ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= APLF_WITH_ELEVATION;
        }
    }
    
    // Get the APPROXIMATE_POS field
    if ( SDTS_Utils::getSubfieldByName( *curField, "APPROXIMATE_POS   ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= APLF_APPROXIMATE_POS;
        }
    }
    
    // Get the PROTRACTED_POS field
    if ( SDTS_Utils::getSubfieldByName( *curField, "PROTRACTED_POS    ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= APLF_PROTRACTED_POS;
        }
    }
    
    // Get the ORIGIN_OF_SURVEY field
    if ( SDTS_Utils::getSubfieldByName( *curField, "ORIGIN_OF_SURVEY  ", curSubfield ) )
    {
        curSubfield->getI( d_surveyOrigin );
    }
    
    // Get the TOWNSHIP field
    if ( SDTS_Utils::getSubfieldByName( *curField, "TOWNSHIP          ", curSubfield ) )
    {
        curSubfield->getA( d_strTownship );
        trimRight( d_strTownship );
    }
    
    // Get the RANGE field
    if ( SDTS_Utils::getSubfieldByName( *curField, "RANGE             ", curSubfield ) )
    {
        curSubfield->getA( d_strRange );
        trimRight( d_strRange );
    }
    
    // Get the SECTION field
    if ( SDTS_Utils::getSubfieldByName( *curField, "SECTION           ", curSubfield ) )
    {
        curSubfield->getA( d_strSection );
        trimRight( d_strSection );
    }
    
    // Get the LAND_GRANT field
    if ( SDTS_Utils::getSubfieldByName( *curField, "LAND_GRANT        ", curSubfield ) )
    {
        curSubfield->getA( d_strLandGrant );
        trimRight( d_strLandGrant );
    }
    
    // Get the MONUMENT_NUMBER field
    if ( SDTS_Utils::getSubfieldByName( *curField, "MONUMENT_NUMBER   ", curSubfield ) )
    {
        curSubfield->getA( d_strMonumentNumber );
        trimRight( d_strMonumentNumber );
    }
    
    // Get the BEST_ESTIMATE field
    if ( SDTS_Utils::getSubfieldByName( *curField, "BEST_ESTIMATE     ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= APLF_BEST_ESTIMATE;
        }
    } 
}

void
SDTS_APLFRecord::getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const
{
    if ( d_flags & APLF_BEST_ESTIMATE )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "BEST_ESTIMATE", "Y" ) );
    }

    if ( !d_strMonumentNumber.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "MONUMENT_NUMBER", d_strMonumentNumber ) );
    }

    if ( !d_strLandGrant.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "LAND_GRANT", d_strLandGrant ) );
    }

    if ( !d_strSection.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "SECTION", d_strSection ) );
    }

    if ( !d_strRange.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "RANGE", d_strRange ) );
    }

    if ( !d_strTownship.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "TOWNSHIP", d_strTownship ) );
    }

    if ( -9 != d_surveyOrigin )
    {
        char strTemp[10];
        sprintf( strTemp, "%ld", d_surveyOrigin );
        pairs.push_back( SDTSAtt_LabelValuePair( "ORIGIN_OF_SURVEY", strTemp ) );
    }

    if ( d_flags & APLF_PROTRACTED_POS )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "PROTRACTED_POS", "Y" ) );
    }

    if ( d_flags & APLF_APPROXIMATE_POS )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "APPROXIMATE_POS", "Y" ) );
    }

    if ( d_flags & APLF_WITH_ELEVATION )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "WITH_ELEVATION", "Y" ) );
    }

    if ( d_flags & APLF_WITH_HORIZONTAL )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "WITH_HORIZONTAL", "Y" ) );
    }
    
    if ( d_flags & APLF_ID_IN_FIELD )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "ID_IN_FIELD", "Y" ) );
    }

    if ( !d_strEntityLabel.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "ENTITY_LABEL", d_strEntityLabel ) );
    }
}   

void 
SDTS_APLFRecord::getAttReferenceInfo( vector<SDTS_AttReferenceInfo>& attRefInfo ) const
{
    SDTS_AttReferenceInfo ref( "BGRL" );

    // Add the land grant
    if ( !d_strLandGrant.empty() )
    {
        ref.addForeignKey( "LAND_GRANT        ", "LAND_GRANT        ", d_strLandGrant );
        attRefInfo.push_back( ref );
    }
}
