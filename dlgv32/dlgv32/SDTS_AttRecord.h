// SDTS_AttRecord.h - interface for all SDTS_AttRecord derived classes
//
// Developed by: Mike Childs
//      Started: 10/5/97

#ifndef _SDTS_ATTRECORD_H_
#define _SDTS_ATTRECORD_H_

#include <vector>
#include <string>
using namespace std;

// Forward declarations
class sc_Record;

// SDTS_AttForeignKey helper class
class SDTS_AttForeignKey
{
public:
    // Constructors
    SDTS_AttForeignKey( void ) {};
    SDTS_AttForeignKey( const string& strRefField, const string& strFKField,
                        const string& strValue ) : d_strRefFieldName(strRefField),
                                                   d_strForeignKeyFieldName(strFKField), 
                                                   d_strForeignKeyValue(strValue) {};

    // Accessors
    const string& getReferencingFieldName( void ) const { return d_strRefFieldName; };
    const string& getForeignKeyFieldName( void ) const { return d_strForeignKeyFieldName; };
    const string& getForeignKeyValue( void ) const { return d_strForeignKeyValue; };

    // Operator overloads for VC5.0 STL support
    bool operator< ( const SDTS_AttForeignKey& rhs ) const { return false; };
    bool operator> ( const SDTS_AttForeignKey& rhs ) const { return false; };
    bool operator==( const SDTS_AttForeignKey& rhs ) const { return false; }; 

protected:
    string d_strRefFieldName;
    string d_strForeignKeyFieldName;
    string d_strForeignKeyValue;
};

// SDTS_AttReferenceInfo helper class
class SDTS_AttReferenceInfo
{
public:
    // Constructors
    SDTS_AttReferenceInfo( void ) {};
    SDTS_AttReferenceInfo( const string& strModuleName ) : d_strModuleName(strModuleName) {};

    // Accessors
    const string& getModuleName( void ) { return d_strModuleName; };
    const vector<SDTS_AttForeignKey>& getForeignKeys( void ) const { return d_foreignKeys; };
    
    // Modifiers
    void addForeignKey( const string& strRefName, const string& strFKName, const string& strValue )
        { d_foreignKeys.push_back( SDTS_AttForeignKey( strRefName, strFKName, strValue ) ); };
    void setModuleName( const string& strModuleName ) { d_strModuleName = strModuleName; };

    // Operator overloads for VC5.0 STL support
    bool operator< ( const SDTS_AttReferenceInfo& rhs ) const { return false; };
    bool operator> ( const SDTS_AttReferenceInfo& rhs ) const { return false; };
    bool operator==( const SDTS_AttReferenceInfo& rhs ) const { return false; }; 

protected:
    string                     d_strModuleName;
    vector<SDTS_AttForeignKey> d_foreignKeys;
};

// SDTSAtt_LabelValuePair Helper class
class SDTSAtt_LabelValuePair
{
public:
    // Constructors
    SDTSAtt_LabelValuePair( void ) {};
    SDTSAtt_LabelValuePair( const string& strLabel, const string& strValue )
        : d_strLabel(strLabel), d_strValue(strValue) {};

    const string& getLabel( void ) const { return d_strLabel; };
    const string& getValue( void ) const { return d_strValue; };

    // Operator overloads for VC5.0 STL support
    bool operator< ( const SDTSAtt_LabelValuePair& rhs ) const { return false; };
    bool operator> ( const SDTSAtt_LabelValuePair& rhs ) const { return false; };
    bool operator==( const SDTSAtt_LabelValuePair& rhs ) const { return false; }; 

protected:
    string d_strLabel;
    string d_strValue;
};

// Attribute Record base class
class SDTS_AttRecord
{
public:
    // Constructor
    SDTS_AttRecord( sc_Record& record );

    // Destructor
    virtual ~SDTS_AttRecord() {};

    // Accessors
    long getRecordID( void ) const { return d_recordID; };
    virtual void getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const = 0;
    virtual void getAttReferenceInfo( vector<SDTS_AttReferenceInfo>& attRefInfo ) const { };
    virtual bool checkForForeignKeyMatch( const vector<SDTS_AttForeignKey>& foreignKeys ) const
        { return false; };

protected:
    // Utility function
    static const string& trimRight( string& str );
    long d_recordID;
};

// Generic class for unknown Attribute record types
class SDTS_GenericAttRecord: public SDTS_AttRecord
{
public:
    // Constructor
    explicit SDTS_GenericAttRecord( sc_Record& record );

    // Overrides
    void getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const;

protected:
    vector<SDTSAtt_LabelValuePair> d_pairs;
};

// AHPF - Hyspography Attribute Primary Record class
class SDTS_AHPFRecord : public SDTS_AttRecord
{
public:
    // Constructor
    explicit SDTS_AHPFRecord( sc_Record& record );

    // Overrides
    void getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const;

protected:
    string       d_strEntityLabel;
    string       d_strSpotCategory;
    unsigned int d_flags;
};

// AHYF - Hydrography Attribute Primary Record class
class SDTS_AHYFRecord : public SDTS_AttRecord
{
public:
    // Constructor
    explicit SDTS_AHYFRecord( sc_Record& record );

    // Overrides
    void getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const;

protected:
    string       d_strEntityLabel;
    double       d_elevation;
    long         d_rotationAngle;
    double       d_riverMile;
    unsigned int d_flags;
};

// ASCF - Vegetative Surface Cover Attribute Primary Record class
class SDTS_ASCFRecord : public SDTS_AttRecord
{
public:
    // Constructor
    explicit SDTS_ASCFRecord( sc_Record& record );

    // Overrides
    void getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const;

protected:
    string       d_strEntityLabel;
    unsigned int d_flags;
};

// ANVF - Non-vegatitive Features Attribute Primary Record class
class SDTS_ANVFRecord : public SDTS_AttRecord
{
public:
    // Constructor
    explicit SDTS_ANVFRecord( sc_Record& record );

    // Overrides
    void getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const;

protected:
    string       d_strEntityLabel;
    unsigned int d_flags;
};

// ABDF - Boundaries Attribute Primary Record class
class SDTS_ABDFRecord : public SDTS_AttRecord
{
public:
    // Constructor
    explicit SDTS_ABDFRecord( sc_Record& record );

    // Overrides
    void getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const;
    void getAttReferenceInfo( vector<SDTS_AttReferenceInfo>& attRefInfo ) const;

protected:
    string       d_strEntityLabel;
    string       d_strStateFIPS;
    string       d_strCountyFIPS;
    string       d_strTownshipFIPS;
    string       d_strMonumentNumber;
    unsigned int d_flags;
};

// ASMF - Survey Control Attribute Primary Record class
class SDTS_ASMFRecord : public SDTS_AttRecord
{
public:
    // Constructor
    explicit SDTS_ASMFRecord( sc_Record& record );

    // Overrides
    void getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const;

protected:
    string       d_strEntityLabel;
    string       d_strStateFIPS;
    string       d_strCountyFIPS;
    double       d_elevation;
};

// ARDF - Roads and Trails Attribute Primary Record class
class SDTS_ARDFRecord : public SDTS_AttRecord
{
public:
    // Constructor
    explicit SDTS_ARDFRecord( sc_Record& record );

    // Overrides
    void getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const;

protected:
    string       d_strEntityLabel;
    long         d_roadWidth;
    long         d_lanes;
    unsigned int d_flags;
};

// ARRF - Railroads Attribute Primary Record class
class SDTS_ARRFRecord : public SDTS_AttRecord
{
public:
    // Constructor
    explicit SDTS_ARRFRecord( sc_Record& record );

    // Overrides
    void getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const;

protected:
    string       d_strEntityLabel;
    long         d_tracks;
    long         d_rotationAngle;
    unsigned int d_flags;
};

// AMTF - Pipelines Attribute Primary Record class
class SDTS_AMTFRecord : public SDTS_AttRecord
{
public:
    // Constructor
    explicit SDTS_AMTFRecord( sc_Record& record );

    // Overrides
    void getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const;
    void getAttReferenceInfo( vector<SDTS_AttReferenceInfo>& attRefInfo ) const;

protected:
    string       d_strEntityLabel;
    long         d_rotationAngle;
    string       d_strStateFIPS;
    string       d_strAirportName;
    unsigned int d_flags;
};

// AMSF - Manmade Features Attribute Primary Record class
class SDTS_AMSFRecord : public SDTS_AttRecord
{
public:
    // Constructor
    explicit SDTS_AMSFRecord( sc_Record& record );

    // Overrides
    void getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const;
    void getAttReferenceInfo( vector<SDTS_AttReferenceInfo>& attRefInfo ) const;

protected:
    string       d_strEntityLabel;
    long         d_populationClass;
    long         d_width;
    long         d_rotationAngle;
    string       d_strStateFIPS;
    string       d_strPopulatedPlace;
    unsigned int d_flags;
};

// APLF - Public Land Survey Attribute Primary Record class
class SDTS_APLFRecord : public SDTS_AttRecord
{
public:
    // Constructor
    explicit SDTS_APLFRecord( sc_Record& record );

    // Overrides
    void getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const;
    void getAttReferenceInfo( vector<SDTS_AttReferenceInfo>& attRefInfo ) const;

protected:
    string       d_strEntityLabel;
    long         d_surveyOrigin;
    string       d_strTownship;
    string       d_strRange;
    string       d_strSection;
    string       d_strLandGrant;
    string       d_strMonumentNumber;
    unsigned int d_flags;
};

// ACOI - Coincidence Attribute Primary Record class
class SDTS_ACOIRecord : public SDTS_AttRecord
{
public:
    // Constructor
    explicit SDTS_ACOIRecord( sc_Record& record );

    // Overrides
    void getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const;

protected:
    string d_strCoincident;
};

// AHPR - Hypsography Elevation (Meters) Attribute Primary Record class
class SDTS_AHPRRecord : public SDTS_AttRecord
{
public:
    // Constructor
    explicit SDTS_AHPRRecord( sc_Record& record );

    // Overrides
    void getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const;

protected:
    double d_elevation;
};

// AHPT - Hypsography Elevation (Feet) Attribute Primary Record class
class SDTS_AHPTRecord : public SDTS_AttRecord
{
public:
    // Constructor
    explicit SDTS_AHPTRecord( sc_Record& record );

    // Overrides
    void getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const;

protected:
    double d_elevation;
};

// ARDM - Roads and Trails Routes Attribute Primary Record class
class SDTS_ARDMRecord : public SDTS_AttRecord
{
public:
    // Constructor
    explicit SDTS_ARDMRecord( sc_Record& record );

    // Overrides
    void getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const;

protected:
    string d_strRouteNumber;
    string d_strRouteType;
};

// ABDM - Boundaries Agency Attribute Primary Record class
class SDTS_ABDMRecord : public SDTS_AttRecord
{
public:
    // Constructor
    explicit SDTS_ABDMRecord( sc_Record& record );

    // Overrides
    void getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const;

protected:
    long d_agency;
};

// BFPS - Boundaries, Transportation, and Manmade Features Attribute Secondary Record class
class SDTS_BFPSRecord : public SDTS_AttRecord
{
public:
    // Constructor
    explicit SDTS_BFPSRecord( sc_Record& record );

    // Overrides
    void getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const;
    bool checkForForeignKeyMatch( const vector<SDTS_AttForeignKey>& foreignKeys ) const;

protected:
    string d_strStateFIPS;
    string d_strStateName;
};

// BFPC - Boundaries and Mandmade Features County Attribute Secondary Record class
class SDTS_BFPCRecord : public SDTS_AttRecord
{
public:
    // Constructor
    explicit SDTS_BFPCRecord( sc_Record& record );

    // Overrides
    void getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const;
    bool checkForForeignKeyMatch( const vector<SDTS_AttForeignKey>& foreignKeys ) const;

protected:
    string d_strStateFIPS;
    string d_strCountyFIPS;
    string d_strAreaName;
};

// BMSP - Manmade Features Populate Place Attribute Secondary Record class
class SDTS_BMSPRecord : public SDTS_AttRecord
{
public:
    // Constructor
    explicit SDTS_BMSPRecord( sc_Record& record );

    // Overrides
    void getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const;
    bool checkForForeignKeyMatch( const vector<SDTS_AttForeignKey>& foreignKeys ) const;

protected:
    string d_strPopulatedPlace;
    string d_strPopPlaceName;
    string d_strCounty;
    long   d_population;
};

// BMTA - Transportation Airport Names Attribute Secondary Record class
class SDTS_BMTARecord : public SDTS_AttRecord
{
public:
    // Constructor
    explicit SDTS_BMTARecord( sc_Record& record );

    // Overrides
    void getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const;
    bool checkForForeignKeyMatch( const vector<SDTS_AttForeignKey>& foreignKeys ) const;

protected:
    string d_strAirport;
    string d_strAirportName;
};

// BGRL - US Public Land Survey Land Grant Attribute Secondary Record class
class SDTS_BGRLRecord : public SDTS_AttRecord
{
public:
    // Constructor
    explicit SDTS_BGRLRecord( sc_Record& record );

    // Overrides
    void getLabelValuePairs( vector<SDTSAtt_LabelValuePair>& pairs ) const;
    bool checkForForeignKeyMatch( const vector<SDTS_AttForeignKey>& foreignKeys ) const;

protected:
    string d_strLandGrant;
    string d_strLandGrantName;
};

#endif