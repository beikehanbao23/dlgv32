// StatePlaneProjection.h: interface for the StatePlaneProjection class.
//
// Developed by: Mike Childs
//      Started: 3/18/98
//////////////////////////////////////////////////////////////////////

#ifndef _STATEPLANEPROJECTION_H_
#define _STATEPLANEPROJECTION_H_

#include "Projection.h"
#include "ZonedProjection.h"
#include <string>

#ifdef WIN32
using namespace std;
#endif

class StatePlaneProjection : public Projection, public ZonedProjection 
{
public:
    // Construction/Destruction
    StatePlaneProjection( long zone, 
                          DATUM d, UNIT u, 
                          DATUM geoDatum = DEFAULT_DATUM, UNIT geoUnit = ARC_DEGREES );
    StatePlaneProjection( const StatePlaneProjection& p );
	virtual ~StatePlaneProjection();

    // Accessors
    PROJSYS getProjectionSystem() const;

    // Modifiers
    void setZone( long zone );

    // Projection functions
    bool projectToGeo( double x, double y, 
                       double& latitude, double& longitude ) const;
    bool projectFromGeo( double latitude, double longitude,
                         double& x, double& y ) const;

    // String overload
    string toString() const;

    // Operator overloads
    bool operator==( const Projection& p ) const;

    // Cloning
    Projection* clone() const;

    // Parameter file name modifiers
    static void setNAD27ParameterFilename( const string& strNAD27 );
    static void setNAD83ParameterFilename( const string& strNAD83 );

protected:
    // Overrides
    bool checkCoordinateRange( double latitude, double longitude ) const;

private:
    // Parameter file names
    static string d_strNAD27ParamFilename;
    static string d_strNAD83ParamFilename;
};

inline PROJSYS
StatePlaneProjection::getProjectionSystem() const
{
    return SPCS;
}

inline void
StatePlaneProjection::setNAD27ParameterFilename( const string& strNAD27 )
{
    d_strNAD27ParamFilename = strNAD27;
}

inline void
StatePlaneProjection::setNAD83ParameterFilename( const string& strNAD83 )
{
    d_strNAD83ParamFilename = strNAD83;
}

#endif
