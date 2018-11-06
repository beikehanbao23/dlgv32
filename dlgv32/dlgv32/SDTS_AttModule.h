// SDTS_AttModule.h - interface for SDTS_AttModule class
//
// Developed by: Mike Childs
//      Started: 9/11/97

#ifndef _SDTS_ATTMODULE_H_
#define _SDTS_ATTMODULE_H_

#include "SDTS_AttRecord.h"
#include <vector>
#include <string>
using namespace std;

class SDTS_AttModule
{
public:
    // Constructor
    SDTS_AttModule( const string& strName );

    // Destructor
    virtual ~SDTS_AttModule();

    // Operations
    virtual bool loadFromFile( const string& strFilename );
    SDTS_AttRecord* getRecord( unsigned int index ) const;
    void getLabelValuePairsByFK( vector<SDTSAtt_LabelValuePair>& pairs,
                                 const vector<SDTS_AttForeignKey>& foreignKeys ) const;

protected:
    vector<SDTS_AttRecord*> d_records;

    // Allocator functions
    typedef SDTS_AttRecord* (REC_ALLOCATOR_FN)( sc_Record& record );
    static REC_ALLOCATOR_FN allocateAHPF;
    static REC_ALLOCATOR_FN allocateAHYF;
    static REC_ALLOCATOR_FN allocateASCF;
    static REC_ALLOCATOR_FN allocateANVF;
    static REC_ALLOCATOR_FN allocateABDF;
    static REC_ALLOCATOR_FN allocateASMF;
    static REC_ALLOCATOR_FN allocateARDF;
    static REC_ALLOCATOR_FN allocateARRF;
    static REC_ALLOCATOR_FN allocateAMTF;
    static REC_ALLOCATOR_FN allocateAMSF;
    static REC_ALLOCATOR_FN allocateAPLF;
    static REC_ALLOCATOR_FN allocateACOI;
    static REC_ALLOCATOR_FN allocateAHPR;
    static REC_ALLOCATOR_FN allocateAHPT;
    static REC_ALLOCATOR_FN allocateARDM;
    static REC_ALLOCATOR_FN allocateABDM;
    static REC_ALLOCATOR_FN allocateBFPS;
    static REC_ALLOCATOR_FN allocateBFPC;
    static REC_ALLOCATOR_FN allocateBMSP;
    static REC_ALLOCATOR_FN allocateBMTA;
    static REC_ALLOCATOR_FN allocateBGRL;
    static REC_ALLOCATOR_FN allocateGeneric;
    void getAllocator( const string& strModuleName );
    REC_ALLOCATOR_FN* d_allocatorFunc;
};

inline SDTS_AttRecord* 
SDTS_AttModule::allocateAHPF( sc_Record& record )
{
    return ( new SDTS_AHPFRecord( record ) );
}

inline SDTS_AttRecord* 
SDTS_AttModule::allocateAHYF( sc_Record& record )
{
    return ( new SDTS_AHYFRecord( record ) );
}

inline SDTS_AttRecord* 
SDTS_AttModule::allocateASCF( sc_Record& record )
{
    return ( new SDTS_ASCFRecord( record ) );
}

inline SDTS_AttRecord* 
SDTS_AttModule::allocateANVF( sc_Record& record )
{
    return ( new SDTS_ANVFRecord( record ) );
}

inline SDTS_AttRecord* 
SDTS_AttModule::allocateABDF( sc_Record& record )
{
    return ( new SDTS_ABDFRecord( record ) );
}

inline SDTS_AttRecord* 
SDTS_AttModule::allocateASMF( sc_Record& record )
{
    return ( new SDTS_ASMFRecord( record ) );
}

inline SDTS_AttRecord* 
SDTS_AttModule::allocateARDF( sc_Record& record )
{
    return ( new SDTS_ARDFRecord( record ) );
}

inline SDTS_AttRecord* 
SDTS_AttModule::allocateARRF( sc_Record& record )
{
    return ( new SDTS_ARRFRecord( record ) );
}

inline SDTS_AttRecord* 
SDTS_AttModule::allocateAMTF( sc_Record& record )
{
    return ( new SDTS_AMTFRecord( record ) );
}

inline SDTS_AttRecord* 
SDTS_AttModule::allocateAMSF( sc_Record& record )
{
    return ( new SDTS_AMSFRecord( record ) );
}

inline SDTS_AttRecord* 
SDTS_AttModule::allocateAPLF( sc_Record& record )
{
    return ( new SDTS_APLFRecord( record ) );
}

inline SDTS_AttRecord* 
SDTS_AttModule::allocateACOI( sc_Record& record )
{
    return ( new SDTS_ACOIRecord( record ) );
}

inline SDTS_AttRecord* 
SDTS_AttModule::allocateAHPR( sc_Record& record )
{
    return ( new SDTS_AHPRRecord( record ) );
}

inline SDTS_AttRecord* 
SDTS_AttModule::allocateAHPT( sc_Record& record )
{
    return ( new SDTS_AHPTRecord( record ) );
}

inline SDTS_AttRecord* 
SDTS_AttModule::allocateARDM( sc_Record& record )
{
    return ( new SDTS_ARDMRecord( record ) );
}

inline SDTS_AttRecord* 
SDTS_AttModule::allocateABDM( sc_Record& record )
{
    return ( new SDTS_ABDMRecord( record ) );
}

inline SDTS_AttRecord* 
SDTS_AttModule::allocateBFPS( sc_Record& record )
{
    return ( new SDTS_BFPSRecord( record ) );
}

inline SDTS_AttRecord* 
SDTS_AttModule::allocateBFPC( sc_Record& record )
{
    return ( new SDTS_BFPCRecord( record ) );
}

inline SDTS_AttRecord* 
SDTS_AttModule::allocateBMSP( sc_Record& record )
{
    return ( new SDTS_BMSPRecord( record ) );
}

inline SDTS_AttRecord* 
SDTS_AttModule::allocateBMTA( sc_Record& record )
{
    return ( new SDTS_BMTARecord( record ) );
}

inline SDTS_AttRecord* 
SDTS_AttModule::allocateBGRL( sc_Record& record )
{
    return ( new SDTS_BGRLRecord( record ) );
}

inline SDTS_AttRecord*
SDTS_AttModule::allocateGeneric( sc_Record& record )
{
    return ( new SDTS_GenericAttRecord( record ) );
}

#endif