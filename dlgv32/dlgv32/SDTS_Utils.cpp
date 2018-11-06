// SDTS_Utils.cpp - implementation of SDTS_Utils class
//
// Developed by: Mike Childs
//      Started: 1/13/98

#include "SDTS_Utils.h"
#include <string.h>

bool
SDTS_Utils::getFieldByMnem( sc_Record& rec, 
                            const char* strMnem,
                            sc_Record::const_iterator& thefield )
{
    for ( thefield = rec.begin(); thefield != rec.end(); thefield++ )
    {
        if ( 0 == strcmp( strMnem, thefield->getMnemonic().c_str() ) )
        {
            return true;
        }
    }

    return false;
}

bool
SDTS_Utils::getSubfieldByMnem( sc_Field const& field, const char* strMnem,
                               sc_Field::const_iterator& thesubf)
{
    for ( thesubf = field.begin(); thesubf != field.end(); 
          thesubf++ )
    {
        if ( 0 == strcmp( strMnem, thesubf->getMnemonic().c_str() ) )
        {
            return true;
        }
    }

    return false;
}


bool
SDTS_Utils::getSubfieldByName( sc_Field const& field, const char* strName,
                               sc_Field::const_iterator& thesubf)
{
    for ( thesubf = field.begin(); thesubf != field.end(); 
          thesubf++ )
    {
        if ( 0 == strcmp( strName, thesubf->getName().c_str() ) )
        {
            return true;
        }
    }

    return false;
}
