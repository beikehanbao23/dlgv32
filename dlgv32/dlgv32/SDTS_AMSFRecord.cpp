// SDTS_AMSFRecord.cpp - implementation of SDTS_AMSFRecord class
//
// Developed by: Mike Childs
//      Started: 10/11/97

#include "SDTS_AttRecord.h"
#include "SDTS_Utils.h"
#include "sdtsxx/container/sc_Record.h"

// Define bitmasks for boolean values stored in flags variable
#define AMSF_RELATION_TO_GROUND         0x000003    // Bits 1-2
    #define AMSF_RTG_UNDERGROUND    0x000001
    #define AMSF_RTG_SUBMERGED      0x000002
#define AMSF_OPERATIONAL_STATUS         0x00000C    // Bits 3-4
    #define AMSF_OS_UC              0x000004
    #define AMSF_OS_ABANDONED       0x000008
    #define AMSF_OS_RUIN            0x00000C
#define AMSF_PRODUCT                    0x0000F0    // Bits 5-8
    #define AMSF_PROD_WATER         0x000010
    #define AMSF_PROD_OIL           0x000020
    #define AMSF_PROD_GAS           0x000030
    #define AMSF_PROD_CHEMICAL      0x000040
    #define AMSF_PROD_GRAVEL        0x000050
    #define AMSF_PROD_SAND          0x000060
    #define AMSF_PROD_CLAY          0x000070
    #define AMSF_PROD_BORROW        0x000080
    #define AMSF_PROD_CALICHE       0x000090
    #define AMSF_PROD_CHERT         0x0000A0
    #define AMSF_PROD_CINDER        0x0000B0
    #define AMSF_PROD_PUMICE        0x0000C0
    #define AMSF_PROD_SHALE         0x0000D0
    #define AMSF_PROD_SCORIA        0x0000E0
#define AMSF_COVERED                    0x000100
#define AMSF_TOWER_TYPE                 0x000600    // Bits 10-11
    #define AMSF_TT_RADIO           0x000200
    #define AMSF_TT_LOOKOUT         0x000400
#define AMSF_UNINCORPORATED             0x000800
#define AMSF_NO_POPULATION              0x001000
#define AMSF_NATIONAL_CAPITAL           0x002000
#define AMSF_STATE_CAPITAL              0x004000
#define AMSF_COUNTY_SEAT                0x008000
#define AMSF_PHOTOREVISED               0x010000
#define AMSF_BEST_ESTIMATE              0x020000

SDTS_AMSFRecord::SDTS_AMSFRecord( sc_Record& record )
: SDTS_AttRecord(record), d_flags(0), d_populationClass(-9), d_rotationAngle(-99), d_width(-999)
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
            d_flags |= AMSF_RTG_UNDERGROUND;
        }
        else if ( "S" == strTemp )
        {
            d_flags |= AMSF_RTG_SUBMERGED;
        }
    }

    // Get the OPERATIONAL_STATUS subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "OPERATIONAL_STATUS", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "C" == strTemp )
        {
            d_flags |= AMSF_OS_UC;
        }
        else if ( "A" == strTemp )
        {
            d_flags |= AMSF_OS_ABANDONED;
        }
        else if ( "R" == strTemp )
        {
            d_flags |= AMSF_OS_RUIN;
        }
    }

    // Get the PRODUCT subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "PRODUCT           ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "W" == strTemp )
        {
            d_flags |= AMSF_PROD_WATER;
        }
        else if ( "O" == strTemp )
        {
            d_flags |= AMSF_PROD_OIL;
        }
        else if ( "G" == strTemp )
        {
            d_flags |= AMSF_PROD_GAS;
        }
        else if ( "C" == strTemp )
        {
            d_flags |= AMSF_PROD_CHEMICAL;
        }
        else if ( "V" == strTemp )
        {
            d_flags |= AMSF_PROD_GRAVEL;
        }
        else if ( "S" == strTemp )
        {
            d_flags |= AMSF_PROD_SAND;
        }
        else if ( "L" == strTemp )
        {
            d_flags |= AMSF_PROD_CLAY;
        }
        else if ( "B" == strTemp )
        {
            d_flags |= AMSF_PROD_BORROW;
        }
        else if ( "A" == strTemp )
        {
            d_flags |= AMSF_PROD_CALICHE;
        }
        else if ( "H" == strTemp )
        {
            d_flags |= AMSF_PROD_CHERT;
        }
        else if ( "I" == strTemp )
        {
            d_flags |= AMSF_PROD_CINDER;
        }
        else if ( "P" == strTemp )
        {
            d_flags |= AMSF_PROD_PUMICE;
        }
        else if ( "E" == strTemp )
        {
            d_flags |= AMSF_PROD_SHALE;
        }
        else if ( "R" == strTemp )
        {
            d_flags |= AMSF_PROD_SCORIA;
        }
    }

    // Get the COVERED subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "COVERED           ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= AMSF_COVERED;
        }
    }

    // Get the TOWER_TYPE subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "TOWER_TYPE        ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "R" == strTemp )
        {
            d_flags |= AMSF_TT_RADIO;
        }
        else if ( "L" == strTemp )
        {
            d_flags |= AMSF_TT_LOOKOUT;
        }
    }

    // Get the UNINCORPORATED subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "UNINCORPORATED    ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= AMSF_UNINCORPORATED;
        }
    }

    // Get the NO_POPULATION subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "NO_POPULATION     ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= AMSF_NO_POPULATION;
        }
    }

    // Get the NATIONAL_CAPITAL subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "NATIONAL_CAPITAL  ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= AMSF_NATIONAL_CAPITAL;
        }
    }

    // Get the STATE_CAPITAL subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "STATE_CAPITAL     ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= AMSF_STATE_CAPITAL;
        }
    }

    // Get the COUNTY_SEAT subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "COUNTY_SEAT       ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= AMSF_COUNTY_SEAT;
        }
    }

    // Get the POPULATION_CLASS subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "POPULATION_CLASS  ", curSubfield ) )
    {
        curSubfield->getI( d_populationClass );
    }

    // Get the PHOTOREVISED subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "PHOTOREVISED      ", curSubfield ) )
    {
        curSubfield->getA( strTemp );

        if ( "Y" == strTemp )
        {
            d_flags |= AMSF_PHOTOREVISED;
        }
    }

    // Get the WIDTH subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "WIDTH             ", curSubfield ) )
    {
        curSubfield->getI( d_width );
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
            d_flags |= AMSF_BEST_ESTIMATE;
        }
    }

    // Get the STATE subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "STATE             ", curSubfield ) )
    {
        curSubfield->getA( d_strStateFIPS );
        trimRight( d_strStateFIPS );
    }

    // Get the POPULATED_PLACE subfield
    if ( SDTS_Utils::getSubfieldByName( *curField, "POPULATED_PLACE   ", curSubfield ) )
    {
        curSubfield->getA( d_strPopulatedPlace );
        trimRight( d_strPopulatedPlace );
    }
}

void
SDTS_AMSFRecord::getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const
{
    char strTemp[20];

    if ( !d_strPopulatedPlace.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "POPULATED_PLACE", d_strPopulatedPlace ) );
    }

    if ( !d_strStateFIPS.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "STATE", d_strStateFIPS ) );
    }

    if ( d_flags & AMSF_BEST_ESTIMATE )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "BEST_ESTIMATE", "Y" ) );
    }

    if ( -99 != d_rotationAngle )
    {
        sprintf( strTemp, "%ld°", d_rotationAngle );
        pairs.push_back( SDTSAtt_LabelValuePair( "ROTATION_ANGLE", strTemp ) );
    }

    if ( -999 != d_width )
    {
        sprintf( strTemp, "%ld mils on map", d_width );
        pairs.push_back( SDTSAtt_LabelValuePair( "WIDTH", strTemp ) );
    }

    if ( d_flags & AMSF_PHOTOREVISED )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "PHOTOREVISED", "Y" ) );
    }

    if ( -9 != d_populationClass )
    {
        sprintf( strTemp, "%ld", d_populationClass );
        pairs.push_back( SDTSAtt_LabelValuePair( "POPULATION_CLASS", strTemp ) );
    }

    if ( d_flags & AMSF_COUNTY_SEAT )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "COUNTY_SEAT", "Y" ) );
    }

    if ( d_flags & AMSF_STATE_CAPITAL )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "STATE_CAPITAL", "Y" ) );
    }

    if ( d_flags & AMSF_NATIONAL_CAPITAL )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "NATIONAL_CAPITAL", "Y" ) );
    }

    if ( d_flags & AMSF_NO_POPULATION )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "NO_POPULATION", "Y" ) );
    }

    if ( d_flags & AMSF_UNINCORPORATED )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "UNINCORPORATED", "Y" ) );
    }

    switch ( d_flags & AMSF_TOWER_TYPE )
    {
        case AMSF_TT_RADIO:
            pairs.push_back( SDTSAtt_LabelValuePair( "TOWER_TYPE", "RADIO" ) );
            break;
        case AMSF_TT_LOOKOUT:
            pairs.push_back( SDTSAtt_LabelValuePair( "TOWER_TYPE", "LOOKOUT" ) );
            break;
    }

    if ( d_flags & AMSF_COVERED )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "COVERED", "Y" ) );
    }

    switch ( d_flags & AMSF_PRODUCT )
    {
        case AMSF_PROD_WATER:
            pairs.push_back( SDTSAtt_LabelValuePair( "PRODUCT", "WATER" ) );
            break;
        case AMSF_PROD_OIL:
            pairs.push_back( SDTSAtt_LabelValuePair( "PRODUCT", "OIL" ) );
            break;
        case AMSF_PROD_GAS:
            pairs.push_back( SDTSAtt_LabelValuePair( "PRODUCT", "GAS" ) );
            break;
        case AMSF_PROD_CHEMICAL:
            pairs.push_back( SDTSAtt_LabelValuePair( "PRODUCT", "CHEMICAL" ) );
            break;
        case AMSF_PROD_GRAVEL:
            pairs.push_back( SDTSAtt_LabelValuePair( "PRODUCT", "GRAVEL" ) );
            break;
        case AMSF_PROD_SAND:
            pairs.push_back( SDTSAtt_LabelValuePair( "PRODUCT", "SAND" ) );
            break;
        case AMSF_PROD_CLAY:
            pairs.push_back( SDTSAtt_LabelValuePair( "PRODUCT", "CLAY" ) );
            break;
        case AMSF_PROD_BORROW:
            pairs.push_back( SDTSAtt_LabelValuePair( "PRODUCT", "BORROW" ) );
            break;
        case AMSF_PROD_CALICHE:
            pairs.push_back( SDTSAtt_LabelValuePair( "PRODUCT", "CALICHE" ) );
            break;
        case AMSF_PROD_CHERT:
            pairs.push_back( SDTSAtt_LabelValuePair( "PRODUCT", "CHERT" ) );
            break;
        case AMSF_PROD_CINDER:
            pairs.push_back( SDTSAtt_LabelValuePair( "PRODUCT", "CINDER" ) );
            break;
        case AMSF_PROD_PUMICE:
            pairs.push_back( SDTSAtt_LabelValuePair( "PRODUCT", "PUMICE" ) );
            break;
        case AMSF_PROD_SHALE:
            pairs.push_back( SDTSAtt_LabelValuePair( "PRODUCT", "SHALE" ) );
            break;
        case AMSF_PROD_SCORIA:
            pairs.push_back( SDTSAtt_LabelValuePair( "PRODUCT", "SCORIA" ) );
            break;
    }

    switch ( d_flags & AMSF_OPERATIONAL_STATUS )
    {
        case AMSF_OS_UC:
            pairs.push_back( SDTSAtt_LabelValuePair( "OPERATIONAL_STATUS", "UNDER CONSTRUCTION" ) );
            break;
        case AMSF_OS_ABANDONED:
            pairs.push_back( SDTSAtt_LabelValuePair( "OPERATIONAL_STATUS", "ABANDONED" ) );
            break;
        case AMSF_OS_RUIN:
            pairs.push_back( SDTSAtt_LabelValuePair( "OPERATIONAL_STATUS", "RUIN" ) );
            break;
    }

    switch ( d_flags & AMSF_RELATION_TO_GROUND )
    {
        case AMSF_RTG_UNDERGROUND:
            pairs.push_back( SDTSAtt_LabelValuePair( "RELATION_TO_GROUND", "UNDERGROUND" ) );
            break;
        case AMSF_RTG_SUBMERGED:
            pairs.push_back( SDTSAtt_LabelValuePair( "RELATION_TO_GROUND", "SUBMERGED" ) );
            break;
    }

    if ( !d_strEntityLabel.empty() )
    {
        pairs.push_back( SDTSAtt_LabelValuePair( "ENTITY_LABEL", d_strEntityLabel ) );
    }
}

void 
SDTS_AMSFRecord::getAttReferenceInfo( vector<SDTS_AttReferenceInfo>& attRefInfo ) const
{
    SDTS_AttReferenceInfo ref( "BFPS" );

    // Add the state reference
    if ( !d_strStateFIPS.empty() )
    {
        ref.addForeignKey( "STATE             ", "STATE             ", d_strStateFIPS );
        attRefInfo.push_back( ref );
    }

    // Add the populated place reference
    if ( !d_strPopulatedPlace.empty() )
    {
        ref.setModuleName( "BMSP" );
        ref.addForeignKey( "POPULATED_PLACE   ", "POPULATED_PLACE   ", d_strPopulatedPlace );
        attRefInfo.push_back( ref );
    }
}
