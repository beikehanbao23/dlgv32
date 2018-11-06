// SDTS_ARDFRecord.cpp - implementation of SDTS_ARDFRecord class
//
// Developed by: Mike Childs
//      Started: 10/11/97

#include "SDTS_AttRecord.h"
#include "SDTS_Utils.h"
#include "sdtsxx/container/sc_Record.h"

// Define bitmasks for boolean values stored in flags variable
#define ARDF_ARBITRARY_EXT              0x000001
#define ARDF_RELATION_TO_GROUND         0x00000E  // Bits 2-4
    #define ARDF_RTG_TUNNEL         0x000002
    #define ARDF_RTG_SUBMERGED      0x000004
    #define ARDF_RTG_DOUBLE_DECKED  0x000006
    #define ARDF_RTG_ELEVATED       0x000008
    #define ARDF_RTG_ON_DRAWBRIDGE  0x00000A
#define ARDF_VERTICAL_RELATION          0x000030  // Bits 5-6
    #define ARDF_VR_OVERPASSING     0x000010
    #define ARDF_VR_UNDERPASSING    0x000020
#define ARDF_OPERATIONAL_STATUS         0x0000C0  // Bits 7-8
    #define ARDF_OS_UC_KNOWN        0x000040
    #define ARDF_OS_UC_UNKNOWN      0x000080
    #define ARDF_OS_PROPOSED        0x0000C0
#define ARDF_ACCESS_RESTRICTION         0x000300  // Bits 9-10
    #define ARDF_AR_TOLL_ROAD       0x000100
    #define ARDF_AR_PRIVATE         0x000200
#define ARDF_OLD_RAILROAD_GRADE         0x000400
#define ARDF_WITH_RAILROAD              0x000800
#define ARDF_COVERED                    0x001000
#define ARDF_HISTORICAL                 0x002000
#define ARDF_LIMITED_ACCESS             0x004000
#define ARDF_PHOTOREVISED               0x008000
#define ARDF_BEST_ESTIMATE              0x010000

SDTS_ARDFRecord::SDTS_ARDFRecord( sc_Record& record )
: SDTS_AttRecord(record), d_flags(0), d_lanes(-9), d_roadWidth(-99)
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

    // Get the ARBITRARY_EXT subfield
    string strTemp;
    if ( SDTS_Utils::getSubfieldByName( *curField, "ARBITRARY_EXT     ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= ARDF_ARBITRARY_EXT;
        }
    }

    // Get the RELATION_TO_GROUND subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "RELATION_TO_GROUND", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "T" == strTemp )
        {
            d_flags |= ARDF_RTG_TUNNEL;
        }
        else if ( "S" == strTemp )
        {
            d_flags |= ARDF_RTG_SUBMERGED;
        }
        else if ( "D" == strTemp )
        {
            d_flags |= ARDF_RTG_DOUBLE_DECKED;
        }
        else if ( "E" == strTemp )
        {
            d_flags |= ARDF_RTG_ELEVATED;
        }
        else if ( "R" == strTemp )
        {
            d_flags |= ARDF_RTG_ON_DRAWBRIDGE;
        }
    }

    // Get the VERTICAL_RELATION subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "VERTICAL_RELATION ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "O" == strTemp )
        {
            d_flags |= ARDF_VR_OVERPASSING;
        }
        else if ( "U" == strTemp )
        {
            d_flags |= ARDF_VR_UNDERPASSING;
        }
    }

    // Get the OPERATIONAL_STATUS subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "OPERATIONAL_STATUS", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "U" == strTemp )
        {
            d_flags |= ARDF_OS_UC_KNOWN;
        }
        else if ( "X" == strTemp )
        {
            d_flags |= ARDF_OS_UC_UNKNOWN;
        }
        else if ( "P" == strTemp )
        {
            d_flags |= ARDF_OS_PROPOSED;
        }
    }

    // Get the ACCESS_RESTRICTION subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "ACCESS_RESTRICTION", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "T" == strTemp )
        {
            d_flags |= ARDF_AR_TOLL_ROAD;
        }
        else if ( "P" == strTemp )
        {
            d_flags |= ARDF_AR_PRIVATE;
        }
    }

    // Get the OLD_RAILROAD_GRADE subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "OLD_RAILROAD_GRADE", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= ARDF_OLD_RAILROAD_GRADE;
        }
    }

    // Get the WITH_RAILROAD subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "WITH_RAILROAD     ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= ARDF_WITH_RAILROAD;
        }
    }

    // Get the COVERED subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "COVERED           ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= ARDF_COVERED;
        }
    }

    // Get the HISTORICAL subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "HISTORICAL        ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= ARDF_HISTORICAL;
        }
    }

    // Get the LIMITED_ACCESS subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "LIMITED_ACCESS    ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= ARDF_LIMITED_ACCESS;
        }
    }

    // Get the PHOTOREVISED subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "PHOTOREVISED      ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= ARDF_PHOTOREVISED;
        }
    }

    // Get the LANES subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "LANES             ", curSubfield ) )
    {
        curSubfield->getI( d_lanes );
    }

    // Get the ROAD_WIDTH subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "ROAD_WIDTH        ", curSubfield ) )
    {
        curSubfield->getI( d_roadWidth );
    }

    // Get the BEST_ESTIMATE subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "BEST_ESTIMATE     ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= ARDF_BEST_ESTIMATE;
        }
    }
}

void
SDTS_ARDFRecord::getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const
{
    char strTemp[30];
    
    if ( d_flags & ARDF_BEST_ESTIMATE )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "BEST_ESTIMATE", "Y" ) );
    }
    
    if ( -99 != d_roadWidth )
    {
        sprintf( strTemp, "%ld feet", d_roadWidth );
        pairs.push_back( SDTSAtt_LabelValuePair( "ROAD_WIDTH", strTemp ) );
    }
    
    if ( -9 != d_lanes )
    {
        sprintf( strTemp, "%ld", d_lanes );
        pairs.push_back( SDTSAtt_LabelValuePair( "LANES", strTemp ) );
    }
    
    if ( d_flags & ARDF_PHOTOREVISED )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "PHOTOREVISED", "Y" ) );
    }
    
    if ( d_flags & ARDF_LIMITED_ACCESS )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "LIMITED_ACCESS", "Y" ) );
    }
    
    if ( d_flags & ARDF_HISTORICAL )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "HISTORICAL", "Y" ) );
    }
    
    if ( d_flags & ARDF_COVERED )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "COVERED", "Y" ) );
    }
    
    if ( d_flags & ARDF_WITH_RAILROAD )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "WITH_RAILROAD", "Y" ) );
    }
    
    if ( d_flags & ARDF_OLD_RAILROAD_GRADE )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "OLD_RAILROAD_GRADE", "Y" ) );
    }
    
    switch ( d_flags & ARDF_ACCESS_RESTRICTION )
    {
        case ARDF_AR_TOLL_ROAD:
            pairs.push_back( SDTSAtt_LabelValuePair( "ACCESS_RESTRICTION", "TOLL ROAD" ) );
            break;
        case ARDF_AR_PRIVATE:
            pairs.push_back( SDTSAtt_LabelValuePair( "ACCESS_RESTRICTION", "PRIVATE" ) );
            break;
    }

    switch ( d_flags & ARDF_OPERATIONAL_STATUS )
    {
        case ARDF_OS_UC_KNOWN:
            pairs.push_back( SDTSAtt_LabelValuePair( "OPERATIONAL_STATUS", 
                                                     "UNDER CONSTRUCTION, CLASSIFICATION KNOWN" ) );
            break;
        case ARDF_OS_UC_UNKNOWN:
            pairs.push_back( SDTSAtt_LabelValuePair( "OPERATIONAL_STATUS", 
                                                     "UNDER CONSTRUCTION, CLASSIFICATION UNKNOWN" ) );
            break;
        case ARDF_OS_PROPOSED:
            pairs.push_back( SDTSAtt_LabelValuePair( "OPERATIONAL_STATUS", "PROPOSED" ) );
            break;
    }

    switch ( d_flags & ARDF_VERTICAL_RELATION )
    {
        case ARDF_VR_OVERPASSING:
            pairs.push_back( SDTSAtt_LabelValuePair( "VERTICAL_RELATION", "OVERPASSING" ) );
            break;
        case ARDF_VR_UNDERPASSING:
            pairs.push_back( SDTSAtt_LabelValuePair( "VERTICAL_RELATION", "UNDERPASSING" ) );
            break;
    }

    switch ( d_flags & ARDF_RELATION_TO_GROUND )
    {
        case ARDF_RTG_TUNNEL:
            pairs.push_back( SDTSAtt_LabelValuePair( "RELATION_TO_GROUND", "TUNNEL" ) );
            break;
        case ARDF_RTG_SUBMERGED:
            pairs.push_back( SDTSAtt_LabelValuePair( "RELATION_TO_GROUND", "SUBMERGED" ) );
            break;
        case ARDF_RTG_DOUBLE_DECKED:
            pairs.push_back( SDTSAtt_LabelValuePair( "RELATION_TO_GROUND", "DOUBLE-DECKED" ) );
            break;
        case ARDF_RTG_ELEVATED:
            pairs.push_back( SDTSAtt_LabelValuePair( "RELATION_TO_GROUND", "ELEVATED" ) );
            break;
        case ARDF_RTG_ON_DRAWBRIDGE:
            pairs.push_back( SDTSAtt_LabelValuePair( "RELATION_TO_GROUND", "ON_DRAWBRIDGE" ) );
            break;
    }

    if ( d_flags & ARDF_ARBITRARY_EXT )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "ARBITRARY_EXT", "Y" ) );
    }

    if ( !d_strEntityLabel.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "ENTITY_LABEL", d_strEntityLabel ) );
    }
}