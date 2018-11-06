// SDTS_AHPFRecord.cpp - implementation of SDTS_AHPFRecord class
//
// Developed by: Mike Childs
//      Started: 10/5/97

#include "SDTS_AttRecord.h"
#include "SDTS_Utils.h"
#include "sdtsxx/container/sc_Record.h"

// Define bitmasks for boolean values stored in flags variable
#define AHPF_SUPPLEMENTARY    0x01
#define AHPF_AMENDED          0x02
#define AHPF_APPROXIMATE      0x04
#define AHPF_DEPRESSION       0x08
#define AHPF_GLACIER_OR_SNOW  0x10
#define AHPF_UNDERWATER       0x20
#define AHPF_BEST_ESTIMATE    0x40
#define AHPF_PHOTOREVISED     0x80

SDTS_AHPFRecord::SDTS_AHPFRecord( sc_Record& record )
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

    // Get the SUPPLEMENTARY subfield
    string strTemp;
    if ( SDTS_Utils::getSubfieldByName( *curField, "SUPPLEMENTARY     ", curSubfield ) )
    {
        curSubfield->getA( strTemp );
        if ( strTemp == "Y" )
        {
            d_flags |= AHPF_SUPPLEMENTARY;
        }
    }

    // Get the AMENDED subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "AMENDED           ", curSubfield ) )
    {
        curSubfield->getA( strTemp );
        if ( strTemp == "Y" )
        {
            d_flags |= AHPF_AMENDED;
        }
    }

    // Get the APPROXIMATE subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "APPROXIMATE       ", curSubfield ) )
    {
        curSubfield->getA( strTemp );
        if ( strTemp == "Y" )
        {
            d_flags |= AHPF_APPROXIMATE;
        }
    }

    // Get the DEPRESSION subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "DEPRESSION        ", curSubfield ) )
    {
        curSubfield->getA( strTemp );
        if ( strTemp == "Y" )
        {
            d_flags |= AHPF_DEPRESSION;
        }
    }

    // Get the GLACIER_OR_SNOW subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "GLACIER_OR_SNOW   ", curSubfield ) )
    {
        curSubfield->getA( strTemp );
        if ( strTemp == "Y" )
        {
            d_flags |= AHPF_GLACIER_OR_SNOW;
        }
    }

    // Get the UNDERWATER subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "UNDERWATER        ", curSubfield ) )
    {
        curSubfield->getA( strTemp );
        if ( strTemp == "Y" )
        {
            d_flags |= AHPF_UNDERWATER;
        }
    }

    // Get the BEST_ESTIMATE subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "BEST_ESTIMATE     ", curSubfield ) )
    {
        curSubfield->getA( strTemp );
        if ( strTemp == "Y" )
        {
            d_flags |= AHPF_BEST_ESTIMATE;
        }
    }

    // Get the SPOT_CATEGORY subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "SPOT_CATEGORY     ", curSubfield ) )
    {
        curSubfield->getA( d_strSpotCategory );
        trimRight( d_strSpotCategory );
    }

    // Get the PHOTOREVISED subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "PHOTOREVISED      ", curSubfield ) )
    {
        curSubfield->getA( strTemp );
        if ( strTemp == "Y" )
        {
            d_flags |= AHPF_PHOTOREVISED;
        }
    }
}

void
SDTS_AHPFRecord::getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const
{
    if ( d_flags & AHPF_PHOTOREVISED )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "PHOTOREVISED", "Y" ) );
    }

    if ( !d_strSpotCategory.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "SPOT_CATEGORY", d_strSpotCategory ) );
    }

    if ( d_flags & AHPF_BEST_ESTIMATE )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "BEST_ESTIMATE", "Y" ) );
    }

    if ( d_flags & AHPF_UNDERWATER )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "UNDERWATER", "Y" ) );
    }

    if ( d_flags & AHPF_GLACIER_OR_SNOW )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "GLACIER_OR_SNOW", "Y" ) );
    }

    if ( d_flags & AHPF_DEPRESSION )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "DEPESSION", "Y" ) );
    }

    if ( d_flags & AHPF_APPROXIMATE )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "APPROXIMATE", "Y" ) );
    }

    if ( d_flags & AHPF_AMENDED )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "AMENDED", "Y" ) );
    }

    if ( d_flags & AHPF_SUPPLEMENTARY )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "SUPPLEMENTARY", "Y" ) );
    }

    if ( !d_strEntityLabel.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "ENTITY_LABEL", d_strEntityLabel ) );
    }
}
