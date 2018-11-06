// MercatorProjection.cpp: implementation of the MercatorProjection class.
//
// Developed by: Mike Childs
//      Started: 4/4/98
//////////////////////////////////////////////////////////////////////

#include "MercatorProjection.h"
#include "DatumConvertor.h"

// GCTPC includes
#include "gctpc/gctpc.h"
#include "gctpc/proj.h"

#ifndef NULL
#define NULL 0
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MercatorProjection::MercatorProjection( double sMajor, double sMinor, double centMer, 
                                        double originLat, double fe, double fn, 
                                        DATUM d, UNIT u, DATUM geoDatum, UNIT geoUnit )
: Projection(d,u,geoDatum,geoUnit)
{
    // Initialize all the projection parameters to zero
    for ( int i = 0; i < 15; i++ )
    {
        d_projParams[i] = 0.0;
    }

    setSemiMajorAxis( sMajor );
    setSemiMinorAxis( sMinor );
    setCentralMeridian( centMer );
    setOriginLatitude( originLat );
    setFalseEasting( fe );
    setFalseNorthing( fn );
}

MercatorProjection::MercatorProjection( const MercatorProjection& p )
: Projection(p)
{
    if ( this != &p )
    {
        setCentralMeridian( p.getCentralMeridian() );
        setFalseEasting( p.getFalseEasting() );
        setFalseNorthing( p.getFalseNorthing() );
        setOriginLatitude( p.getOriginLatitude() );
        setSemiMajorAxis( p.getSemiMajorAxis() );
        setSemiMinorAxis( p.getSemiMinorAxis() );
    }
}

// Comparison functions
bool 
MercatorProjection::operator==( const Projection& p ) const
{
    const MercatorProjection* pRHS = dynamic_cast<const MercatorProjection*>(&p);
    if ( NULL != pRHS )
    {
        if ( getCentralMeridian() == pRHS->getCentralMeridian() &&
             getFalseEasting()    == pRHS->getFalseEasting()    &&
             getFalseNorthing()   == pRHS->getFalseNorthing()   &&
             getOriginLatitude()  == pRHS->getOriginLatitude()  &&
             getSemiMajorAxis()   == pRHS->getSemiMajorAxis() )
        {
            return Projection::operator==( p );
        }
    }

    return false;
}

// toString override
string
MercatorProjection::toString() const
{
    string str = "Mercator Projection\r\n";
    str += Projection::toString();
    str += "CENTRAL MERIDIAN: ";
    str += packedDMSToString( getCentralMeridian(), false );
    str += "\r\nORIGIN LATITUDE: ";
    str += packedDMSToString( getOriginLatitude(), true );

    char strFalseEasting[40];
    sprintf( strFalseEasting, "\r\nFALSE EASTING: %g", getFalseEasting() );
    str += strFalseEasting;

    char strFalseNorthing[40];
    sprintf( strFalseNorthing, "\r\nFALSE NORTHING: %g", getFalseNorthing() );
    str += strFalseNorthing;

    char strSemiMajorAxis[40];
    sprintf( strSemiMajorAxis, "\r\nSEMI-MAJOR AXIS: %g", getSemiMajorAxis() );
    str += strSemiMajorAxis;

    char strSemiMinorAxis[40];
    sprintf( strSemiMinorAxis, "\r\nSEMI-MINOR AXIS: %g", getSemiMinorAxis() );
    str += strSemiMinorAxis;

    return str;
}

// Projection functions
bool
MercatorProjection::projectToGeo( double x, double y, 
                                  double& latitude, double& longitude ) const
{
    static double outparm[15] = { 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0 };  // output parameter array

	double incoor[2];	// input coordinates (x, y)
	long   insys;		// input projection system
	long   inzone;		// input zone
	long   inunit;		// input units
	long   indatum;		// input spheroid code
	long   ipr;			// error message print flag
	char*  efile;		// file to contain output error messages
	long   jpr;			// projection parameter print flag
	char*  pfile;		// file to contain output projection parameter messages
	double outcoor[2];	// output coordinates (x, y)
	long   outsys;		// output projection system
	long   outzone;		// output zone
	long   outunit;		// output units
	long   outdatum;	// output spheroid code
	char*  fn27;		// file containing NAD 1927 state plane zones
	char*  fn83;		// file containing NAD 1983 state plane zones
	long   iflg;		// error flag

	// Variable initialization
	incoor[0] = x;
	incoor[1] = y;
	insys     = getProjectionSystem();
	inzone    = 0;
	inunit    = getUnit();
	indatum	  = DatumConvertor::getDatumEllipsoid( getDatum() );
	ipr		  = -1;				// Do not print error messages
	efile     = NULL;			// No error file
	jpr       = -1;				// Do not print projection parameters
	pfile     = NULL;			// No projection parameter file
	outsys    = GEO;			// Output in geographic (lat, long)
	outzone   = 0;	            // No zones for geographic
	outunit   = getGeoUnit();
	outdatum  = DatumConvertor::getDatumEllipsoid( getGeoDatum() );
	fn27      = NULL;           // No NAD27 State Plane parameter file
	fn83      = NULL;           // No NAD83 State Plane parameter file
  
	// Do transformation
	gctp( incoor, &insys, &inzone, const_cast<double*>(d_projParams), &inunit, 
          &indatum, &ipr, efile, &jpr, pfile, outcoor, &outsys, &outzone, 
		  outparm, &outunit, &indatum, fn27, fn83, &iflg );

	// Set latitude and longitude
	longitude = outcoor[0];
	latitude  = outcoor[1];

    // Convert the datums
    return convertDatum( latitude, longitude, getDatum(), getGeoDatum() );
}

bool 
MercatorProjection::projectFromGeo( double latitude, double longitude,
                                    double& x, double& y ) const
{
    static double inparm[15] = { 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0 };  // input parameter array

    // Convert the datums
    if ( !convertDatum( latitude, longitude, getGeoDatum(), getDatum() ) )
    {
        return false;
    }

    double incoor[2];	// input coordinates (x, y)
	long   insys;		// input projection system
	long   inzone;		// input zone
	long   inunit;		// input units
	long   indatum;		// input spheroid code
	long   ipr;			// error message print flag
	char*  efile;		// file to contain output error messages
	long   jpr;			// projection parameter print flag
	char*  pfile;		// file to contain output projection parameter messages
	double outcoor[2];	// output coordinates (x, y)
	long   outsys;		// output projection system
	long   outzone;		// output zone
	long   outunit;		// output units
	long   outdatum;	// output spheroid code
	char*  fn27;		// file containing NAD 1927 state plane zones
	char*  fn83;		// file containing NAD 1983 state plane zones
	long   iflg;		// error flag

	// Variable initialization
	incoor[0] = longitude;
	incoor[1] = latitude;
	insys     = GEO;
	inzone    = 0;
	inunit    = getGeoUnit();
    indatum	  = DatumConvertor::getDatumEllipsoid( getGeoDatum() );
	ipr		  = -1;				// Do not print error messages
	efile     = NULL;			// No error file
	jpr       = -1;				// Do not print projection parameters
	pfile     = NULL;			// No projection parameter file
	outsys    = getProjectionSystem();
	outzone   = 0;
	outunit   = getUnit();
	outdatum  = DatumConvertor::getDatumEllipsoid( getDatum() );
	fn27      = NULL;           // No NAD27 State Plane parameter file
	fn83      = NULL;           // No NAD83 State Plane parameter file

	// Do transformation
	gctp( incoor, &insys, &inzone, inparm, &inunit, &outdatum, 
		  &ipr, efile, &jpr, pfile, outcoor, &outsys, &outzone, 
		  const_cast<double*>(d_projParams), &outunit, 
          &outdatum, fn27, fn83, &iflg );

	// Set the coordinates
	x = outcoor[0];
	y = outcoor[1];

    return true;
}

// Cloning
Projection*
MercatorProjection::clone() const
{
    return ( new MercatorProjection( *this ) );
}

// Coordinate checking
bool
MercatorProjection::checkCoordinateRange( double latitude, double longitude ) const
{
    if ( !Projection::checkCoordinateRange( latitude, longitude ) )
    {
        return false;
    }

    return ( latitude >= -86.0 && latitude <= 86.0 );
}