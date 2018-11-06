// Projection.cpp: implementation of the Projection class.
//
// Developed by: Mike Childs
//      Started: 1/16/98
//////////////////////////////////////////////////////////////////////

#include "Projection.h"
#include "DatumConvertor.h"
#include "GeographicProjection.h"
#include "gctpc/untfz.h"

#ifndef NULL
#define NULL 0
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Projection::Projection( DATUM d, UNIT u, DATUM geoDatum, UNIT geoUnit )
: d_datum(d), d_unit(u), d_geoDatum(geoDatum), d_geoUnit(geoUnit)
{
    // If the geographic datum is default just use the projection's datum
    if ( DEFAULT_DATUM == d_geoDatum )
    {
        d_geoDatum = d_datum;
    }
}

Projection::Projection( const Projection& p )
{
    if ( this != &p )
    {
        d_datum = p.d_datum;
        d_unit  = p.d_unit;
        d_geoDatum = p.d_geoDatum;
        d_geoUnit = p.d_geoUnit;
    }
}

Projection::~Projection()
{

}

// Operator overlays
bool
Projection::operator==( const Projection& p ) const
{
    if ( getDatum() == p.getDatum() &&
         getUnit()  == p.getUnit()  &&
         getProjectionSystem() == p.getProjectionSystem() )
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool
Projection::operator!=( const Projection& p ) const
{
    return ( !operator==( p ) );
}

string
Projection::toString() const
{
    // TODO: Make this better
    string str = "DATUM: ";
    str += datumToString( d_datum );
    str += "\r\nUNIT: ";
    str += unitToString( d_unit );
    str += "\r\n";
    return str;
}

double
Projection::packedDMSToDouble( double packedDMS )
{
    double sign = 1.0;
    if ( packedDMS < 0.0 )
    {
        sign = -1.0;
        packedDMS = -packedDMS;
    }

    short deg = packedDMS / 1000000;
    packedDMS -= deg * 1000000;
    short min = packedDMS / 1000;
    packedDMS -= min * 1000;

    double result = deg;
    result += min / 60.0;
    result += packedDMS / 3600.0;
    result *= sign;
    return result;
}

string
Projection::packedDMSToString( double packedDMS, bool bLat )
{
    char nsFlag = 'N';
    char ewFlag = 'E';
    if ( packedDMS < 0 )
    {
        nsFlag = 'S';
        ewFlag = 'W';
        packedDMS *= -1;
    }

    short deg = packedDMS / 1000000;
    packedDMS -= deg * 1000000;
    short min = packedDMS / 1000;
    packedDMS -= min * 1000;
    double sec = packedDMS;

    char flag = bLat ? nsFlag : ewFlag;
    char strTemp[20];
    sprintf( strTemp, "%d° %02d\' %05.2f\" %c", deg, min, sec, flag );

    return strTemp;
}

string
Projection::unitToString( UNIT u )
{
    switch ( u )
    {
        case RADIANS:
            return "radians";
        case US_FEET:
            return "feet";
        case METERS:
            return "meters";
        case ARC_SECONDS:
            return "arc seconds";
        case ARC_DEGREES:
            return "arc degrees";
        case INTERNATIONAL_FEET:
            return "international feet";
        case STATE_ZONE_TABLE:
            return "state zone table units";
        default:
            return "unknown units";
    }
}

string Projection::datumToString( DATUM d )
{
    switch ( d )
    {
        case ADINDAN:
            return "ADINDAN";
        case ARC1950:
            return "ARC1950";
        case ARC1960:
            return "ARC1960";
        case AUSTRALIAN_GEODETIC_1966:
            return "AUSTRALIAN GEODETIC 1966";
        case AUSTRALIAN_GEODETIC_1984:
            return "AUSTRALIAN GEODETIC 1984";
        case CAMP_AREA_ASTRO:
            return "CAMP AREA ASTRO";
        case CAPE:
            return "CAPE";
        case EUROPEAN_DATUM_1950:
            return "EUROPEAN DATUM 1950";
        case EUROPEAN_DATUM_1979:
            return "EUROPEAN DATUM 1979";
        case GEODETIC_DATUM_1949:
            return "GEODETIC DATUM 1949";
        case HONG_KONG_1963:
            return "HONG KONG 1963";
        case HU_TZU_SHAN:
            return "HU TZU SHAN";
        case INDIAN:
            return "INDIAN";
        case NAD27:
            return "NAD27";
        case NAD83:
            return "NAD83";
        case OLD_HAWAIIAN_MEAN:
            return "OLD HAWAIIAN MEAN";
        case OMAN:
            return "OMAN";
        case ORDNANCE_SURVEY_1936:
            return "ORDNANCE SURVEY 1936";
        case PULKOVO_1942:
            return "PULKOVO 1942";
        case PROVISIONAL_S_AMERICAN_1956:
            return "PROVISIONAL SOUTH AMERICAN 1956";
        case TOKYO:
            return "TOKYO";
        case WGS_72:
            return "WGS72";
        case WGS_84:
            return "WGS84";
        case NO_DATUM:
            return "NO DATUM";
        default:
            return "Unknown Datum";
    }
}

// Datum conversion
bool
Projection::convertDatum( double& latitude, double& longitude, DATUM from, DATUM to ) const
{
    // Convert the coordinates to degrees if they aren't there already
    double factor;
    untfz( d_geoUnit, ARC_DEGREES, &factor );
    latitude *= factor;
    longitude *= factor;

    // Make sure the coordinates are in the valid range for this projection
    bool bResult = true;
    if ( bResult = checkCoordinateRange( latitude, longitude ) )
    {
        // Convert the datum of the point if necessary
        if ( from != to )
        {
            bResult = DatumConvertor::convertDatum( latitude, longitude, from, to );
        }

        // Check the coordinate range again to make sure the datum stuff didn't
        // screw it up
        if ( bResult )
        {
            bResult = checkCoordinateRange( latitude, longitude );
        }
    }

    // Convert the point back to its original units
    latitude /= factor;
    longitude /= factor;

    return bResult;
}