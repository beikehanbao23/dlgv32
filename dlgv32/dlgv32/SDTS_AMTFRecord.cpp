// SDTS_AMTFRecord.cpp - implementation of SDTS_AMTFRecord class
//
// Developed by: Mike Childs
//      Started: 10/11/97

#include "SDTS_AttRecord.h"
#include "SDTS_Utils.h"
#include "sdtsxx/container/sc_Record.h"

// Define bitmasks for boolean values stored in flags variable
#define AMTF_RELATION_TO_GROUND         0x0003  // Bits 1-2
    #define AMTF_RTG_UNDERGROUND    0x0001
    #define AMTF_RTG_ABOVEGROUND    0x0002
    #define AMTF_RTG_SUBMERGED      0x0003
#define AMTF_OPERATIONAL_STATUS         0x000C  // Bits 3-4
    #define AMTF_OS_UC              0x0004
    #define AMTF_OS_ABANDONED       0x0008
    #define AMTF_OS_CLOSED          0x000C
#define AMTF_UNIMPROVED                 0x0010
#define AMTF_NUCLEAR                    0x0020
#define AMTF_ARBITRARY_EXT              0x0040
#define AMTF_PHOTOREVISED               0x0080
#define AMTF_BEST_ESTIMATE              0x0100

SDTS_AMTFRecord::SDTS_AMTFRecord( sc_Record& record )
: SDTS_AttRecord(record), d_flags(0), d_rotationAngle(-99)
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

    // Get the RELATION_TO_GROUND subfield
    string strTemp;
    if ( SDTS_Utils::getSubfieldByName( *curField, "RELATION_TO_GROUND", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "U" == strTemp )
        {
            d_flags |= AMTF_RTG_UNDERGROUND;
        }
        else if ( "A" == strTemp )
        {
            d_flags |= AMTF_RTG_ABOVEGROUND;
        }
        else if ( "S" == strTemp )
        {
            d_flags |= AMTF_RTG_SUBMERGED;
        }
    }

    // Get the OPERATIONAL_STATUS subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "OPERATIONAL_STATUS", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "U" == strTemp )
        {
            d_flags |= AMTF_OS_UC;
        }
        else if ( "A" == strTemp )
        {
            d_flags |= AMTF_OS_ABANDONED;
        }
        else if ( "C" == strTemp )
        {
            d_flags |= AMTF_OS_CLOSED;
        }
    }

    // Get the UNIMPROVED subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "UNIMPROVED        ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= AMTF_UNIMPROVED;
        }
    }

    // Get the NUCLEAR subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "NUCLEAR           ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= AMTF_NUCLEAR;
        }
    }

    // Get the ARBITRARY_EXT subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "ARBITRARY_EXT     ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= AMTF_ARBITRARY_EXT;
        }
    }

    // Get the PHOTOREVISED subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "PHOTOREVISED      ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= AMTF_PHOTOREVISED;
        }
    }

    // Get the ROTATION_ANGLE subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "ROTATION_ANGLE    ", curSubfield ) )
    {
        curSubfield->getI( d_rotationAngle );
    }

    // Get the BEST_ESTIMATE subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "BEST_ESTIMATE     ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= AMTF_BEST_ESTIMATE;
        }
    }

    // Get the STATE subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "STATE             ", curSubfield ) )
    {
        curSubfield->getA( d_strStateFIPS );
        trimRight( d_strStateFIPS );
    }
    
    // Get the AIRPORT subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "AIRPORT           ", curSubfield ) )
    {
        curSubfield->getA( d_strAirportName );
        trimRight( d_strAirportName );
    }
}

void
SDTS_AMTFRecord::getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const
{
    if ( !d_strAirportName.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "AIRPORT", d_strAirportName ) );
    }

    if ( !d_strStateFIPS.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "STATE", d_strStateFIPS ) );
    }

    if ( d_flags & AMTF_BEST_ESTIMATE )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "BEST_ESTIMATE", "Y" ) );
    }

    if ( -99 != d_rotationAngle )
    {
        char strTemp[20];
        sprintf( strTemp, "%ld°", d_rotationAngle );
        pairs.push_back( SDTSAtt_LabelValuePair( "ROTATION_ANGLE", strTemp ) );
    }

    if ( d_flags & AMTF_PHOTOREVISED )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "PHOTOREVISED", "Y" ) );
    }

    if ( d_flags & AMTF_ARBITRARY_EXT )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "ARBITRARY_EXT", "Y" ) );
    }

    if ( d_flags & AMTF_NUCLEAR )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "NUCLEAR", "Y" ) );
    }

    if ( d_flags & AMTF_UNIMPROVED )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "UNIMPROVED", "Y" ) );
    }

    switch ( d_flags & AMTF_OPERATIONAL_STATUS )
    {
        case AMTF_OS_UC:
            pairs.push_back( SDTSAtt_LabelValuePair( "OPERATIONAL_STATUS", "UNDER CONSTRUCTION" ) );
            break;
        case AMTF_OS_ABANDONED:
            pairs.push_back( SDTSAtt_LabelValuePair( "OPERATIONAL_STATUS", "ABANDONED" ) );
            break;
        case AMTF_OS_CLOSED:
            pairs.push_back( SDTSAtt_LabelValuePair( "OPERATIONAL_STATUS", "CLOSED" ) );
            break;
    }

    switch ( d_flags & AMTF_RELATION_TO_GROUND )
    {
        case AMTF_RTG_UNDERGROUND:
            pairs.push_back( SDTSAtt_LabelValuePair( "RELATION_TO_GROUND", "UNDERGROUND" ) );
            break;
        case AMTF_RTG_ABOVEGROUND:
            pairs.push_back( SDTSAtt_LabelValuePair( "RELATION_TO_GROUND", "ABOVE GROUND " ) );
            break;
        case AMTF_RTG_SUBMERGED:
            pairs.push_back( SDTSAtt_LabelValuePair( "RELATION_TO_GROUND", "SUBMERGED" ) );
            break;
    }

    if ( !d_strEntityLabel.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "ENTITY_LABEL", d_strEntityLabel ) );
    }
}

void 
SDTS_AMTFRecord::getAttReferenceInfo( vector<SDTS_AttReferenceInfo>& attRefInfo ) const
{
    SDTS_AttReferenceInfo ref( "BFPS" );

    // Add the state reference
    if ( !d_strStateFIPS.empty() )
    {
        ref.addForeignKey( "STATE             ", "STATE             ", d_strStateFIPS );
        attRefInfo.push_back( ref );
    }

    // Add the airport reference
    if ( !d_strAirportName.empty() )
    {
        ref.setModuleName( "BMTA" );
        ref.addForeignKey( "AIRPORT           ", "AIRPORT           ", d_strAirportName );
        attRefInfo.push_back( ref );
    }
}
