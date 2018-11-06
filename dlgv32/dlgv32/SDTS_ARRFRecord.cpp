// SDTS_ARRFRecord.cpp - implementation of SDTS_ARRFRecord class
//
// Developed by: Mike Childs
//      Started: 10/11/97

#include "SDTS_AttRecord.h"
#include "SDTS_Utils.h"
#include "sdtsxx/container/sc_Record.h"

// Define bitmasks for boolean values stored in flags variable
#define ARRF_RELATION_TO_GROUND         0x0003  // Bits 1-2
    #define ARRF_RTG_TUNNEL         0x0001
    #define ARRF_RTG_ELEVATED       0x0002
    #define ARRF_RTG_DRAWBRIDGE     0x0003
#define ARRF_VERTICAL_RELATION          0x000C  // Bits 3-4
    #define ARRF_VR_OVERPASSING     0x0004
    #define ARRF_VR_UNDERPASSING    0x0008
#define ARRF_OPERATIONAL_STATUS         0x0030  // Bits 5-6
    #define ARRF_OS_ABANDONED       0x0010
    #define ARRF_OS_DISMANTLED      0x0020
    #define ARRF_OS_UC              0x0030
#define ARRF_ACCESS_RESTRICTIONS        0x00C0  // Bits 7-8
    #define ARRF_AR_PRIVATE         0x0040
    #define ARRF_AR_USGOVT          0x0080
#define ARRF_NARROW_GAUGE               0x0100
#define ARRF_IN_SNOWSHED                0x0200
#define ARRF_RAPID_TRANSIT              0x0400
#define ARRF_JUXTAPOSITION              0x0800
#define ARRF_ARBITRARY_EXT              0x1000
#define ARRF_HISTORICAL                 0x2000
#define ARRF_PHOTOREVISED               0x4000
#define ARRF_BEST_ESTIMATE              0x8000

SDTS_ARRFRecord::SDTS_ARRFRecord( sc_Record& record )
: SDTS_AttRecord(record), d_flags(0), d_tracks(-9), d_rotationAngle(-99)
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

        if ( "T" == strTemp )
        {
            d_flags |= ARRF_RTG_TUNNEL;
        }
        else if ( "E" == strTemp )
        {
            d_flags |= ARRF_RTG_ELEVATED;
        }
        else if ( "R" == strTemp )
        {
            d_flags |= ARRF_RTG_DRAWBRIDGE;
        }
    }

    // Get the VERTICAL_RELATION subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "VERTICAL_RELATION ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "O" == strTemp )
        {
            d_flags |= ARRF_VR_OVERPASSING;
        }
        else if ( "U" == strTemp )
        {
            d_flags |= ARRF_VR_UNDERPASSING;
        }
    }

    // Get the OPERATIONAL_STATUS subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "OPERATIONAL_STATUS", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "A" == strTemp )
        {
            d_flags |= ARRF_OS_ABANDONED;
        }
        else if ( "D" == strTemp )
        {
            d_flags |= ARRF_OS_DISMANTLED;
        }
        else if ( "U" == strTemp )
        {
            d_flags |= ARRF_OS_UC;
        }
    }

    // Get the ACCESS_RESTRICTION subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "ACCESS_RESTRICTION", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "P" == strTemp )
        {
            d_flags |= ARRF_AR_PRIVATE;
        }
        else if ( "G" == strTemp )
        {
            d_flags |= ARRF_AR_USGOVT;
        }
    }

    // Get the NARROW_GAUGE subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "NARROW_GAUGE      ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= ARRF_NARROW_GAUGE;
        }
    }

    // Get the IN_SNOWSHED subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "IN_SNOWSHED       ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= ARRF_IN_SNOWSHED;
        }
    }

    // Get the RAPID_TRANSIT subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "RAPID_TRANSIT     ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= ARRF_RAPID_TRANSIT;
        }
    }

    // Get the JUXTAPOSITION subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "JUXTAPOSITION     ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= ARRF_JUXTAPOSITION;
        }
    }

    // Get the ARBITRARY_EXT subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "ARBITRARY_EXT     ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= ARRF_ARBITRARY_EXT;
        }
    }

    // Get the HISTORICAL subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "HISTORICAL        ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= ARRF_HISTORICAL;
        }
    }

    // Get the PHOTOREVISED subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "PHOTOREVISED      ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= ARRF_PHOTOREVISED;
        }
    }

    // Get the TRACKS subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "TRACKS            ", curSubfield ) )
    {
        curSubfield->getI( d_tracks );
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
            d_flags |= ARRF_BEST_ESTIMATE;
        }
    }
}

void
SDTS_ARRFRecord::getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const
{
    char strTemp[20];
    
    if ( d_flags & ARRF_BEST_ESTIMATE )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "BEST_ESTIMATE", "Y" ) );
    }

    if ( -99 != d_rotationAngle )
    {
        sprintf( strTemp, "%ld°", d_rotationAngle );
        pairs.push_back( SDTSAtt_LabelValuePair( "ROTATION_ANGLE", strTemp ) );
    }

    if ( -9 != d_tracks )
    {
        sprintf( strTemp, "%ld", d_tracks );
        pairs.push_back( SDTSAtt_LabelValuePair( "TRACKS", strTemp ) );
    }

    if ( d_flags & ARRF_PHOTOREVISED )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "PHOTOREVISED", "Y" ) );
    }

    if ( d_flags & ARRF_HISTORICAL )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "HISTORICAL", "Y" ) );
    }

    if ( d_flags & ARRF_ARBITRARY_EXT )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "ARBITRARY_EXT", "Y" ) );
    }

    if ( d_flags & ARRF_JUXTAPOSITION )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "JUXTAPOSITION", "Y" ) );
    }

    if ( d_flags & ARRF_RAPID_TRANSIT )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "RAPID_TRANSIT", "Y" ) );
    }

    if ( d_flags & ARRF_IN_SNOWSHED )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "IN_SNOWSHED", "Y" ) );
    }

    if ( d_flags & ARRF_NARROW_GAUGE )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "NARROW_GAUGE", "Y" ) );
    }

    switch ( d_flags & ARRF_ACCESS_RESTRICTIONS )
    {
        case ARRF_AR_PRIVATE:   
            pairs.push_back( SDTSAtt_LabelValuePair( "ACCESS_RESTRICTIONS", "PRIVATE" ) );
            break;
        case ARRF_AR_USGOVT:
            pairs.push_back( SDTSAtt_LabelValuePair( "ACCESS_RESTRICTIONS", "US GOVT." ) );
            break;
    }

    switch ( d_flags & ARRF_OPERATIONAL_STATUS )
    {
        case ARRF_OS_ABANDONED:
            pairs.push_back( SDTSAtt_LabelValuePair( "OPERATIONAL_STATUS", "ABANDONED" ) );
            break;
        case ARRF_OS_DISMANTLED:
            pairs.push_back( SDTSAtt_LabelValuePair( "OPERATIONAL_STATUS", "DISMANTLED" ) );
            break;
        case ARRF_OS_UC:
            pairs.push_back( SDTSAtt_LabelValuePair( "OPERATIONAL_STATUS", "UNDER CONSTRUCTION" ) );
            break;
    }

    switch ( d_flags & ARRF_VERTICAL_RELATION )
    {
        case ARRF_VR_OVERPASSING:
            pairs.push_back( SDTSAtt_LabelValuePair( "VERTICAL_RELATION", "OVERPASSING" ) );
            break;
        case ARRF_VR_UNDERPASSING:
            pairs.push_back( SDTSAtt_LabelValuePair( "VERTICAL_RELATION", "UNDERPASSING" ) );
            break;
    }

    switch ( d_flags & ARRF_RELATION_TO_GROUND )
    {
        case ARRF_RTG_TUNNEL:   
            pairs.push_back( SDTSAtt_LabelValuePair( "RELATION_TO_GROUND", "TUNNEL" ) );
            break;
        case ARRF_RTG_ELEVATED:
            pairs.push_back( SDTSAtt_LabelValuePair( "RELATION_TO_GROUND", "ELEVATED" ) );
            break;
        case ARRF_RTG_DRAWBRIDGE:
            pairs.push_back( SDTSAtt_LabelValuePair( "RELATION_TO_GROUND", "DRAWBRIDGE" ) );
            break;
    }

    if ( !d_strEntityLabel.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "ENTITY_LABEL", d_strEntityLabel ) );
    }
}   
