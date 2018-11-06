// SDTS_ABDFRecord.cpp - implementation of SDTS_ABDFRecord class
//
// Developed by: Mike Childs
//      Started: 10/11/97

#include "SDTS_AttRecord.h"
#include "SDTS_Utils.h"
#include "sdtsxx/container/sc_Record.h"

// Define bitmasks for boolean values stored in flags variable
#define ABDF_CIVIL_TOWNSHIP         0x0001
#define ABDF_CITY                   0x0002
#define ABDF_NATIONAL_FOREST        0x0004
#define ABDF_WILDERNESS_AREA        0x0008
#define ABDF_AHUPUAA                0x0010
#define ABDF_HAWAIIAN_HOMESTEAD     0x0020
#define ABDF_FEDERALLY_ADMIN        0x0040
#define ABDF_IN_DISPUTE             0x0080
#define ABDF_PHOTOREVISED           0x0100
#define ABDF_BEST_ESTIMATE          0x0200

SDTS_ABDFRecord::SDTS_ABDFRecord( sc_Record& record )
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

    // Get the CIVIL_TOWNSHIP subfield
    string strTemp;
    if ( SDTS_Utils::getSubfieldByName( *curField, "CIVIL_TOWNSHIP    ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= ABDF_CIVIL_TOWNSHIP;
        }
    }

    // Get the CITY subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "CITY              ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= ABDF_CITY;
        }
    }

    // Get the NATIONAL_FOREST subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "NATIONAL_FOREST   ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= ABDF_NATIONAL_FOREST;
        }
    }

    // Get the WILDERNESS_AREA subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "WILDERNESS_AREA   ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= ABDF_WILDERNESS_AREA;
        }
    }

    // Get the AHUPUAA subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "AHUPUAA           ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= ABDF_AHUPUAA;
        }
    }

    // Get the HAWAIIAN_HOMESTEAD subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "HAWAIIAN_HOMESTEAD", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= ABDF_HAWAIIAN_HOMESTEAD;
        }
    }

    // Get the FEDERALLY_ADMIN subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "FEDERALLY_ADMIN   ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= ABDF_FEDERALLY_ADMIN;
        }
    }

    // Get the IN_DISPUTE subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "IN_DISPUTE        ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= ABDF_IN_DISPUTE;
        }
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

    // Get the TOWNSHIP_CODE subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "TOWNSHIP_CODE     ", curSubfield ) )
    {
        curSubfield->getA( d_strTownshipFIPS );
        trimRight( d_strTownshipFIPS );
    }

    // Get the PHOTOREVISED subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "PHOTOREVISED      ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= ABDF_PHOTOREVISED;
        }
    }

    // Get the MONUMENT_NUMBER subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "MONUMENT_NUMBER   ", curSubfield ) )
    {
        curSubfield->getA( d_strMonumentNumber );
        trimRight( d_strMonumentNumber );
    }

    // Get the BEST_ESTIMATE subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "BEST_ESTIMATE     ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= ABDF_BEST_ESTIMATE;
        }
    }
}

void
SDTS_ABDFRecord::getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const
{
    if ( d_flags & ABDF_BEST_ESTIMATE )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "BEST_ESTIMATE", "Y" ) );
    }

    if ( !d_strMonumentNumber.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "MONUMENT_NUMBER", d_strMonumentNumber ) );
    }

    if ( d_flags & ABDF_PHOTOREVISED )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "PHOTOREVISED", "Y" ) );
    }

    if ( !d_strTownshipFIPS.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "TOWNSHIP_CODE", d_strTownshipFIPS ) );
    }

    if ( !d_strCountyFIPS.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "COUNTY", d_strCountyFIPS ) );
    }

    if ( !d_strStateFIPS.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "STATE", d_strStateFIPS ) );
    }

    if ( d_flags & ABDF_IN_DISPUTE )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "IN_DISPUTE", "Y" ) );
    }

    if ( d_flags & ABDF_FEDERALLY_ADMIN )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "FEDERALLY_ADMIN", "Y" ) );
    }

    if ( d_flags & ABDF_HAWAIIAN_HOMESTEAD )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "HAWAIIAN_HOMESTEAD", "Y" ) );
    }

    if ( d_flags & ABDF_AHUPUAA )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "AHUPUAA", "Y" ) );
    }

    if ( d_flags & ABDF_WILDERNESS_AREA )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "WILDERNESS_AREA", "Y" ) );
    }

    if ( d_flags & ABDF_NATIONAL_FOREST )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "NATIONAL_FOREST", "Y" ) );
    }

    if ( d_flags & ABDF_CITY )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "CITY", "Y" ) );
    }

    if ( d_flags & ABDF_BEST_ESTIMATE )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "CIVIL_TOWNSHIP", "Y" ) );
    }

    if ( !d_strEntityLabel.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "ENTITY_LABEL", d_strEntityLabel ) );
    }
}

void 
SDTS_ABDFRecord::getAttReferenceInfo( vector<SDTS_AttReferenceInfo>& attRefInfo ) const
{
    SDTS_AttReferenceInfo ref( "BFPC" );

    // Add the county reference
    if ( !d_strStateFIPS.empty() && !d_strCountyFIPS.empty() )
    {
        ref.addForeignKey( "STATE             ", "STATE             ", d_strStateFIPS );
        ref.addForeignKey( "COUNTY            ", "COUNTY            ", d_strCountyFIPS );
        attRefInfo.push_back( ref );
    }

    // Add the state reference
    if ( !d_strStateFIPS.empty() )
    {
        ref.setModuleName( "BFPS" );
        ref.addForeignKey( "STATE             ", "STATE             ", d_strStateFIPS );
        attRefInfo.push_back( ref );
    }
}
