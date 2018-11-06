// SDTS_AHYFRecord.cpp - implementation of SDTS_AHYFRecord class
//
// Developed by: Mike Childs
//      Started: 10/8/97

#include "SDTS_AttRecord.h"
#include "SDTS_Utils.h"
#include "sdtsxx/container/sc_Record.h"

// Define bitmasks for boolean values stored in flags variable
#define AHYF_PHOTOREVISED         0x000001
#define AHYF_RELATION_TO_GROUND   0x000006  // Bits 2-3 Mask
    #define AHYF_RTG_U     0x000002
    #define AHYF_RTG_E     0x000004
    #define AHYF_RTG_T     0x000005
#define AHYF_VERTICAL_RELATION    0x000018  // Bits 4-5 Mask
    #define AHYF_VR_O      0x000008
    #define AHYF_VR_U      0x000010
#define AHYF_BANK                 0x000060  // Bits 6-7 Mask
    #define AHYF_BANK_R    0x000020
    #define AHYF_BANK_L    0x000040
#define AHYF_OPERATIONAL_STATUS   0x000180  // Bits 8-9 Mask   
    #define AHYF_OS_U      0x000080
    #define AHYF_OS_A      0x000100
#define AHYF_SALT                 0x000200
#define AHYF_UNSURVEYED           0x000400
#define AHYF_INTERMITTENT         0x000800
#define AHYF_SUBMERGED            0x001000
#define AHYF_DRY                  0x002000
#define AHYF_MINERAL_OR_HOT       0x004000
#define AHYF_NAVIGABLE            0x008000
#define AHYF_EARTHEN              0x010000
#define AHYF_INTERPOLATED         0x020000
#define AHYF_BEST_ESTIMATE        0x040000

SDTS_AHYFRecord::SDTS_AHYFRecord( sc_Record& record )
: SDTS_AttRecord(record), d_elevation(-9999.99), d_rotationAngle(-99), 
  d_riverMile(-999.9), d_flags(0)
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

    // Get the PHOTOREVISED subfield
    string strTemp;
    if ( SDTS_Utils::getSubfieldByName( *curField, "PHOTOREVISED      ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( strTemp == "Y" )
        {
            d_flags |= AHYF_PHOTOREVISED;
        }
    }

    // Get the RELATION_TO_GROUND subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "RELATION_TO_GROUND", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( strTemp == "U" )
        {
            d_flags |= AHYF_RTG_U;
        }
        else if ( strTemp == "E" )
        {
            d_flags |= AHYF_RTG_E;
        }
        else if ( strTemp == "T" )
        {
            d_flags |= AHYF_RTG_T;
        }
    }

    // Get the VERTICAL_RELATION subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "VERTICAL_RELATION ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( strTemp == "O" )
        {
            d_flags |= AHYF_VR_O;
        }
        else if ( strTemp == "U" )
        {
            d_flags |= AHYF_VR_U;
        }
    }

    // Get the BANK subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "BANK              ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( strTemp == "R" )
        {
            d_flags |= AHYF_BANK_R;
        }
        else if ( strTemp == "L" )
        {
            d_flags |= AHYF_BANK_L;
        }
    }

    // Get the OPERATIONAL_STATUS subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "OPERATIONAL_STATUS", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( strTemp == "U" )
        {
            d_flags |= AHYF_OS_U;
        }
        else if ( strTemp == "A" )
        {
            d_flags |= AHYF_OS_A;
        }
    }

    // Get the SALT subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "SALT              ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( strTemp == "Y" )
        {
            d_flags |= AHYF_SALT;
        }
    }

    // Get the UNSURVEYED subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "UNSURVEYED        ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( strTemp == "Y" )
        {
            d_flags |= AHYF_UNSURVEYED;
        }
    }

    // Get the INTERMITTENT subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "INTERMITTENT      ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( strTemp == "Y" )
        {
            d_flags |= AHYF_INTERMITTENT;
        }
    }

    // Get the SUBMERGED subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "SUBMERGED         ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( strTemp == "Y" )
        {
            d_flags |= AHYF_SUBMERGED;
        }
    }

    // Get the DRY subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "DRY               ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( strTemp == "Y" )
        {
            d_flags |= AHYF_DRY;
        }
    }

    // Get the MINERAL_OR_HOT subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "MINERAL_OR_HOT    ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( strTemp == "Y" )
        {
            d_flags |= AHYF_MINERAL_OR_HOT;
        }
    }

    // Get the NAVIGABLE subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "NAVIGABLE         ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( strTemp == "Y" )
        {
            d_flags |= AHYF_NAVIGABLE;
        }
    }

    // Get the EARTHEN subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "EARTHEN           ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( strTemp == "Y" )
        {
            d_flags |= AHYF_EARTHEN;
        }
    }

    // Get the INTERPOLATED subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "INTERPOLATED      ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( strTemp == "Y" )
        {
            d_flags |= AHYF_INTERPOLATED;
        }
    }

    // Get the ELEVATION subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "ELEVATION         ", curSubfield ) )
    {
        curSubfield->getR( d_elevation );
    }

    // Get the ROTATION_ANGLE subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "ROTATION_ANGLE    ", curSubfield ) )
    {
        curSubfield->getI( d_rotationAngle );
    }

    // Get the RIVER_MILE subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "RIVER_MILE        ", curSubfield ) )
    {
        curSubfield->getR( d_riverMile );
    }

    // Get the BEST_ESTIMATE subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "BEST_ESTIMATE     ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( strTemp == "Y" )
        {
            d_flags |= AHYF_BEST_ESTIMATE;
        }
    }
}

void
SDTS_AHYFRecord::getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const
{
    char strTemp[20];

    if ( d_flags & AHYF_BEST_ESTIMATE )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "BEST_ESTIMATE", "Y" ) );
    }

    if ( -999.9 != d_riverMile )
    {
        sprintf( strTemp, "%g MILES", d_riverMile );
        pairs.push_back( SDTSAtt_LabelValuePair( "RIVER_MILE", strTemp ) );
    }

    if ( -99 != d_rotationAngle )
    {
        sprintf( strTemp, "%ld°", d_rotationAngle );
        pairs.push_back( SDTSAtt_LabelValuePair( "ROTATION_ANGLE", strTemp ) );
    }

    if ( -9999.99 != d_elevation )
    {
        sprintf( strTemp, "%g m", d_elevation );
        pairs.push_back( SDTSAtt_LabelValuePair( "ELEVATION", strTemp ) );
    }

    if ( d_flags & AHYF_INTERPOLATED )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "INTERPOLATED", "Y" ) );
    }

    if ( d_flags & AHYF_EARTHEN )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "EARTHEN", "Y" ) );
    }

    if ( d_flags & AHYF_NAVIGABLE )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "NAVIGABLE", "Y" ) );
    }

    if ( d_flags & AHYF_MINERAL_OR_HOT )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "MINERAL_OR_HOT", "Y" ) );
    }

    if ( d_flags & AHYF_DRY )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "DRY", "Y" ) );
    }

    if ( d_flags & AHYF_SUBMERGED )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "SUBMERGED", "Y" ) );
    }

    if ( d_flags & AHYF_INTERMITTENT )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "INTERMITTENT", "Y" ) );
    }

    if ( d_flags & AHYF_UNSURVEYED )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "UNSURVEYED", "Y" ) );
    }

    if ( d_flags & AHYF_SALT )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "SALT", "Y" ) );
    }

    switch ( d_flags & AHYF_OPERATIONAL_STATUS )
    {
        case AHYF_OS_U:
            pairs.push_back( SDTSAtt_LabelValuePair( "OPERATIONAL_STATUS", "UNDER CONSTRUCTION" ) );
            break;
        case AHYF_OS_A:
            pairs.push_back( SDTSAtt_LabelValuePair( "OPERATIONAL_STATUS", "ABANDONED" ) );
            break;
    }

    switch ( d_flags & AHYF_BANK )
    {
        case AHYF_BANK_R:
            pairs.push_back( SDTSAtt_LabelValuePair( "BANK", "RIGHT BANK" ) );
            break;
        case AHYF_BANK_L:
            pairs.push_back( SDTSAtt_LabelValuePair( "BANK", "LEFT BANK" ) );
            break;
    }

    switch ( d_flags & AHYF_VERTICAL_RELATION )
    {
        case AHYF_VR_O:
            pairs.push_back( SDTSAtt_LabelValuePair( "VERTICAL_RELATION", "OVERPASSING" ) );
            break;
        case AHYF_VR_U:
            pairs.push_back( SDTSAtt_LabelValuePair( "VERTICAL_RELATION", "UNDERPASSING" ) );
            break;
    }

    switch ( d_flags & AHYF_RELATION_TO_GROUND )
    {
        case AHYF_RTG_U:
            pairs.push_back( SDTSAtt_LabelValuePair( "RELATION_TO_GROUND", "UNDERGROUND" ) );
            break;
        case AHYF_RTG_E:
            pairs.push_back( SDTSAtt_LabelValuePair( "RELATION_TO_GROUND", "ELEVATED" ) );
            break;
        case AHYF_RTG_T:
            pairs.push_back( SDTSAtt_LabelValuePair( "RELATION_TO_GROUND", "TUNNEL" ) );
            break;
    }

    if ( d_flags & AHYF_PHOTOREVISED )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "PHOTOREVISED", "Y" ) );
    }

    if ( !d_strEntityLabel.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "ENTITY_LABEL", d_strEntityLabel ) );
    }
}