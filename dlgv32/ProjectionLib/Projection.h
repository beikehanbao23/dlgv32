// Projection.h: interface for the Projection class.
//
// Developed by: Mike Childs
//      Started: 1/16/98
//////////////////////////////////////////////////////////////////////

#ifndef _PROJECTION_H_
#define _PROJECTION_H_

#include <string>
#include "ProjectionTypes.h"

#ifdef WIN32
using namespace std;
#endif

class Projection  
{
public:
    // Constructors/Destructors
    Projection( DATUM d, UNIT u, DATUM geoDatum = DEFAULT_DATUM, UNIT geoUnit = ARC_DEGREES );
    Projection( const Projection& p );
    virtual ~Projection();

    // Accessors
    DATUM getDatum() const;
        /* Returns the datum for the projection coordinates in the projection functions */

    DATUM getGeoDatum() const;
        /* Returns the datum for the lat-long coordinates in the projection functions */

    UNIT  getUnit()  const;
        /* Returns the unit for the projection coordinates given in the projection functions */

    UNIT  getGeoUnit() const;
        /* Returns the unit for lat-long coordinates in the projection functions */

    virtual PROJSYS getProjectionSystem() const = 0;
        /* Returns the PROJSYS code.  This must be overriden in derived classes */

    virtual string toString() const;
        /* Returns a string representation of the projection */

    // Modifiers
    void setDatum( DATUM d );
        /* Sets the datum for the projection */

    void setGeoDatum( DATUM d );
        /* Sets the datum which the lat-long coordinates in the projection functions
           are given in */

    void setUnit( UNIT u );
        /* Sets the unit for coordinates in the projection */

    void setGeoUnit( UNIT u );
        /* Sets the unit for the lat-long coordinates in the projection functions
           are given in */

    // Projection functions
    virtual bool projectToGeo( double x, double y, 
                               double& latitude, double& longitude ) const = 0;
        /* Projects the point (x,y) which is in the projection to lat-long.  This
           function must be overriden in derived classes. If the coordinates cannot be
           projected, false should be returned. */

    virtual bool projectFromGeo( double latitude, double longitude,
                                 double& x, double& y ) const = 0;
        /* Projects the latitude and longitude given to the projection.  This function
           must be overriden in derived classes.  If the coordinates cannot be
           projected, false should be returned. */

    // Operator overloads
    virtual bool operator==( const Projection& p ) const;
    bool operator!=( const Projection& p ) const;

    // Cloning functions
    virtual Projection* clone() const = 0;
        /* Creates a copy of the projection and returns a pointer to it.  It is the
           callers responsibility to destroy the pointer when done with it.  This
           function must be overriden in derived classes */
    
    // Helpful functions for getting the string representations of units and datums
    static string datumToString( DATUM d );
    static string unitToString( UNIT u );
    static double packedDMSToDouble( double packedDMS );
    static string packedDMSToString( double packedDMS, bool bLat );

protected:
    bool convertDatum( double& latitude, double& longitude, DATUM from, DATUM to ) const;
    virtual bool checkCoordinateRange( double latitude, double longitude ) const;
        /* Return true if the given coordinate (in arc degrees) is within the range
           allowed for this projection, false if it's not */

private:
    // Data members
    DATUM d_datum;
    DATUM d_geoDatum;
    UNIT  d_unit;
    UNIT  d_geoUnit;
};

inline DATUM
Projection::getDatum() const
{
    return d_datum;
}

inline DATUM
Projection::getGeoDatum() const
{
    return d_geoDatum;
}


inline UNIT
Projection::getUnit() const
{
    return d_unit;
}

inline UNIT
Projection::getGeoUnit() const
{
    return d_geoUnit;
}

inline void
Projection::setDatum( DATUM d )
{
    d_datum = d;
}

inline void
Projection::setGeoDatum( DATUM d )
{
    d_geoDatum = d;
}

inline void
Projection::setUnit( UNIT u )
{
    d_unit = u;
}

inline void
Projection::setGeoUnit( UNIT u )
{
    d_geoUnit = u;
}

inline bool
Projection::checkCoordinateRange( double latitude, double longitude ) const
{
    return ( ( latitude <= 90.0 && latitude >= -90.0 ) &&
             ( longitude <= 180.0 && longitude >= -180.0 ) );
}

#endif