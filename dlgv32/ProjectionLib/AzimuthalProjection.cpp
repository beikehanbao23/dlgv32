// AzimuthalProjection.cpp: implementation of the AzimuthalProjection class.
//
// Developed by: Mike Childs
//      Started: 1/18/98
//////////////////////////////////////////////////////////////////////

#include "AzimuthalProjection.h"
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

AzimuthalProjection::AzimuthalProjection( double centralLongitude, 
                                          double centralLatitude,
                                          double falseEasting,
                                          double falseNorthing,
                                          double sphereRadius, DATUM d,
                                          UNIT u,
                                          DATUM geoDatum, UNIT geoUnit )
: Projection( d, u, geoDatum, geoUnit ), d_badDegreeRadius(4.0)
{
  // Initialize all the projection parameters to zero
  for ( int i = 0; i < 15; i++ )
  {
    d_projectionParameters[i] = 0.0;
  }

  setCentralLatitude( centralLatitude );
  setCentralLongitude( centralLongitude );
  setFalseEasting( falseEasting );
  setFalseNorthing( falseNorthing );
  setSphereRadius( sphereRadius );
}

AzimuthalProjection::AzimuthalProjection( const AzimuthalProjection& p )
: Projection(p)
{
  if ( this != &p )
  {
    setCentralLatitude( p.getCentralLatitude() );
    setCentralLongitude( p.getCentralLongitude() );
    setFalseEasting( p.getFalseEasting() );
    setFalseNorthing( p.getFalseNorthing() );
    setSphereRadius( p.getSphereRadius() );
    d_badDegreeRadius = p.d_badDegreeRadius;
  }
}

// Operator overloads
bool
AzimuthalProjection::operator==( const Projection& p ) const
{
  const AzimuthalProjection* pRHS = 
    dynamic_cast<const AzimuthalProjection*>(&p);
  if ( NULL != pRHS )
  {
    if ( getCentralLatitude()  == pRHS->getCentralLatitude()  &&
         getCentralLongitude() == pRHS->getCentralLongitude() &&
         getFalseEasting()     == pRHS->getFalseEasting()     &&
         getFalseNorthing()    == pRHS->getFalseNorthing()    &&
         getSphereRadius()     == pRHS->getSphereRadius() )
    {
      return Projection::operator==(p);
    }
  }

  return false;
}

// Projection functions
bool
AzimuthalProjection::projectToGeo( double x, double y, 
                                   double& latitude, double& longitude ) const
{
	double incoor[2];	// input coordinates (x, y)
	long   insys;		  // input projection system
	long   inzone;		// input zone
	long   inunit;		// input units
	long   indatum;		// input spheroid code
	long   ipr;			  // error message print flag
	char*  efile;		  // file to contain output error messages
	long   jpr;			  // projection parameter print flag
	char*  pfile;		  // file to contain output projection parameter messages
	double outcoor[2];	// output coordinates (x, y)
	long   outsys;		  // output projection system
	long   outzone;		  // output zone
	double outparm[15];	// output parameter array
	long   outunit;		  // output units
	long   outdatum;	  // output spheroid code
	char*  fn27;		    // file containing NAD 1927 state plane zones
	char*  fn83;		    // file containing NAD 1983 state plane zones
	long   iflg;		    // error flag

	// Variable initialization
	incoor[0] = x;
	incoor[1] = y;
	insys     = getProjectionSystem();
	inzone    = 0;
	inunit    = getUnit();
	indatum	  = DatumConvertor::getDatumEllipsoid( getDatum() );
	ipr		    = -1;				// Do not print error messages
	efile     = NULL;			// No error file
	jpr       = -1;				// Do not print projection parameters
	pfile     = NULL;			// No projection parameter file
	outsys    = GEO;			// Output in geographic (lat, long)
	outzone   = 0;	            // No zones for geographic
	outunit   = getGeoUnit();
	outdatum  = DatumConvertor::getDatumEllipsoid( getGeoDatum() );
	fn27      = NULL;           // No NAD27 State Plane parameter file
	fn83      = NULL;           // No NAD83 State Plane parameter file
  
  // Set all the output projection parameters to zero
  for ( int i = 0; i < 15; i++ )
  {
    outparm[i] = 0.0;
  }

	// Do transformation
	gctp( incoor, &insys, &inzone, const_cast<double*>(d_projectionParameters),
        &inunit, &indatum, &ipr, efile, &jpr, pfile, outcoor, &outsys,
        &outzone, outparm, &outunit, &indatum, fn27, fn83, &iflg );

	// Set latitude and longitude
	longitude = outcoor[0];
	latitude  = outcoor[1];

  // Convert the datums
  return convertDatum( latitude, longitude, getDatum(), getGeoDatum() );
}

bool
AzimuthalProjection::projectFromGeo( double latitude, double longitude,
                                     double& x, double& y ) const
{
  // Convert the datums
  if ( !convertDatum( latitude, longitude, getGeoDatum(), getDatum() ) )
  {
    return false;
  }

	double incoor[2];	// input coordinates (x, y)
	long   insys;		  // input projection system
	long   inzone;		// input zone
	long   inunit;		// input units
	long   indatum;		// input spheroid code
  double inparm[15];  // input parameter array
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
	ipr		    = -1;				// Do not print error messages
	efile     = NULL;			// No error file
	jpr       = -1;				// Do not print projection parameters
	pfile     = NULL;			// No projection parameter file
	outsys    = getProjectionSystem();
	outzone   = 0;
	outunit   = getUnit();
	outdatum  = DatumConvertor::getDatumEllipsoid( getDatum() );
	fn27      = NULL;           // No NAD27 State Plane parameter file
	fn83      = NULL;           // No NAD83 State Plane parameter file

  // Initialize the projection parameter arrays to all zeroes
  for ( int i = 0; i < 15; i++ )
  {
    inparm[i] = 0.0;
  }

	// Do transformation
	gctp( incoor, &insys, &inzone, inparm, &inunit, &outdatum, 
  		  &ipr, efile, &jpr, pfile, outcoor, &outsys, &outzone, 
	  	  const_cast<double*>(d_projectionParameters), &outunit, 
        &outdatum, fn27, fn83, &iflg );

	// Set the coordinates
	x = outcoor[0];
	y = outcoor[1];

  return true;
}

string
AzimuthalProjection::toString() const
{
  string str = Projection::toString();
  str += "\r\nCENTRAL LATITUDE: ";
  str += packedDMSToString( getCentralLatitude(), true );
  str += "\r\nCENTRAL LONGITUDE: ";
  str += packedDMSToString( getCentralLongitude(), false );

  char strFalseEasting[40];
  sprintf( strFalseEasting, "\r\nFALSE EASTING: %g", getFalseEasting() );
  str += strFalseEasting;
    
  char strFalseNorthing[40];
  sprintf( strFalseNorthing, "\r\nFALSE NORTHING: %g", getFalseNorthing() );
  str += strFalseNorthing;

  char strSphereRadius[40];
  sprintf( strSphereRadius, "\r\nSPHERE RADIUS: %g", getSphereRadius() );
  str += strSphereRadius;

  return str;
}

bool 
AzimuthalProjection::checkCoordinateRange( double latitude, 
                                           double longitude ) const
{
  if ( !Projection::checkCoordinateRange( latitude, longitude ) )
  {
    return false;
  }

  // The out of range areas will be on the opposite side of the globe from the
  // center of the projection
  double badLat = -packedDMSToDouble( getCentralLatitude() );
  double badLon = packedDMSToDouble( getCentralLongitude() ) + 180;
  if ( badLon > 180.0 ) badLon -= 360.0;

  // The point is out of range if the point is within the bad degree radius of
  // the bad center
  double top = badLat + d_badDegreeRadius;
  double bottom = badLat - d_badDegreeRadius;
  double left = badLon - d_badDegreeRadius;
  double right = badLon + d_badDegreeRadius;
  if ( ( latitude > bottom && latitude < top ) &&
       ( longitude > left && longitude < right ) )
  {
    return false;
  }
  else
  {
    return true;
  }
}