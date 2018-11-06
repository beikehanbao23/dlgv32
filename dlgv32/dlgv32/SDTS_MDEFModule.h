// SDTS_MDEFModule.h - interface for SDTS_MDEFModule class
//
// Developed by: Mike Childs
//      Started: 11/17/97

#ifndef _SDTS_MDEFMODULE_H_
#define _SDTS_MDEFMODULE_H_

#include <list>
#include <string>
using namespace std;

class SDTS_MDEFModule
{
public:
    // Constructor
    SDTS_MDEFModule() {};

    // Destructor
    ~SDTS_MDEFModule();

    // Accessor
    const string& getEntityDesc( const string& strEntityLabel );

    // Operations
    bool loadFromFile( const string& strFilename );

protected:
    class MDEFRecord
    {
    public:
        string d_strEntityLabel;
        string d_strText;
    };

    // Records
    list<MDEFRecord*> d_records;
};

#endif