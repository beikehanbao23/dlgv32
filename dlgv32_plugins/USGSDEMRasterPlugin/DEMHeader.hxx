#ifndef INCLUDED_DEMHEADER_HXX
#define INCLUDED_DEMHEADER_HXX

//$Id: DEMHeader.hxx,v 1.1 1998/08/14 14:55:21 bmaddox Exp bmaddox $


#ifdef WIN32
#include <iostream>
#include <string>
using namespace std;
#else
#include <iostream.h>
#include <string>
#endif


#ifndef INCLUDED_DEMTYPES_HXX
#include "DEMTypes.hxx"
#endif

#ifndef INCLUDED_DEMPOINT_HXX
#include "DEMPoint.hxx"
#endif

class DEMHeader;
ostream& operator<<(ostream& s, DEMHeader& header);
istream& operator>>(istream& s, DEMHeader& header);

class DEMHeader
{
   public:

      DEMHeader();
      friend ostream& operator<<(ostream& s, DEMHeader& header);
      friend istream& operator>>(istream& s, DEMHeader& header);
   
      // Accessors

      string const& getQuadName() const;
         // Quadrangle name.

      string const& getProcessInfo () const;
         // Free format desciptor field containing process information

	  double getSEGeoCornerX () const;
         // SE geographic corner orderd as:
         // x == Longitude == SDDDMMSS.SSSS
         // (neg sign (s) right justified, no leading zeros, 
         // plus sign (s) implied

	  double getSEGeoCornerY () const;
         // SE geographic corner orderd as:
         // y == Latitude == SDDMMSS.SSSS
         // (neg sign (s) right justified, no leading zeros, 
         // plus sign (s) implied

      long getProcessCode () const;
         // 1 == Autocorrelation resample simple bilinear
         // 2 == Manual profile GRIDEM simple bilinear
         // 3 == DLG/hypsography CTOG 8-direction bilinear
         // 4 == Interpolation from photogrammetic system contours DCASS 
         // 4-direction bilinear
         // 5 == DLG/hypsography LINETRACE, LT4X complex linear
         // 6 == DLG/hypsography CPS-3, ANUDEM, GRASS complex polynomial
         // 7 == Electronic imaging (non-photogrammetric), active or passive
         // sensor systems

      string const& getSectionIndicator() const;
         // Used for 30 minute DEMs - Identifies 1:100,000 scale sections
         // Formatted as XNN, wher X is "S" == 7.5 min. & "F" == 15 min.
         // NN is a two digit sequence number

	  string const& getMappingCenterCode() const;
         // Mapping Center origin code. "EMC","WMC","MCMC","RMMC","FS" and "GPM2"

      long getLevelCode() const;
         // 1 == DEM-1
         // 2 == DEM-2
         // 3 == DEM-3

      long getElevPattern() const;
         // 1 == Regular
         // 2 == Random (reserved for future use).

      long getGroundRefSysCode() const;
         // Code defining ground planimetric reference system.
         // 0 == Geographic
         // 1 == UTM
         // 2 == State Plane
    
      long getGroundRefSysZone() const;
         // Code defining zone in ground planimetric reference system. 

      long getGroundRefSysUnits() const;
         // Code defining unit of measure for ground planimetric coordinates
         // used throughout the file.
         // 0 == Radians
         // 1 == Feet
         // 2 == Meters
         // 3 == Arc Seconds

      long getElevationUnits() const;
         // Code defining unit of measure for elevation coordinates used
         // throughout the file.
         // 1 == Feet
         // 2 == Meters

      long getNumPolySides() const;
         // Set n == 4

	  DEMPointVector const& getDEMCorners() const;
         // The coordinates of the quadrangle corners are ordered in a clockwise
         // direction beginning with the southwest corner.

	  double getCounterclockAngle() const;
          // In Radians the counterclockwise angle from the primary axis of ground
          // planimetric reference to the primary axis of the DEM local reference
          // system. Set to 0 to align with the coordinate system

      long getElevAccuracyCode() const;
          // 0 == unknown accuracy
          // 1 == accuracy info is given in logical record type C

      double getMinimumElev() const;
         // Minimum elevation in the DEM.

      double getMaximumElev() const;
         // Maximum elevation in the DEM.

      double getSpatialResX() const;
      double getSpatialResY() const;
      double getSpatialResZ() const;

      // The number of rows and columns in profiles in the DEM. 
      // NOTE: When profile rows == 1, profile columns is the number of profiles
      // in the DEM.
      long getProfileRows() const;
      long getProfileColumns() const;      

	  long getLargeContInt() const;
         // Present only if two or more primary intervals exist (level 2 DEM's only)

      long getMaxSourceUnits() const;
         // 0 == NA
         // 1 == feet
         // 2 == meters
         // (level two DEM's only)

      long getSmallContInt() const;
         // Smallest or only primary contour interval (level 2 DEM's only)
      
      long getMinSourceUnits() const;
		  // 1 == feet
		  // 2 == meters

	  long getSourceDate() const;
	      // YYYY

	  long getInspRevDate() const;
	      // YYYY
 
	  string const& getInspFlag() const;
	      // "I" indicates all processes of part3, Quality Control have been performed.

	  long getDataValFlag() const;
	      // 0 == No Validation
	      // 1 == RSME computed from test points, no quantative test or interactive editing/review
	      // 2 == Batch process water body edit and RSME computed from test points
	      // 3 == Review and edit, including water edit. No RSME computed from test points
	      // 4 == Level 1 DEM's reviewed & edited. RSME computed from test points
	      // 5 == Level 2 & 3 DEM's reviewed & edited. RSME computed from test points
	  
	  long getSuspectVoidFlag() const;
	      // 0 == none
	      // 1 == suspect areas
	      // 2 == void areas
	      // 3 == suspect & void areas
	  
	  long getVertDatum() const;
	      // 1 == local mean sea level
	      // 2 == National Geodetic Vertical Datum 1929
	      // 3 == North American Vertical Datum 1988

	  long getHorizDatum() const;
	      // 1 == North Amercian Datum 1927 (NAD 27)
	      // 2 == World Geoditic System 1972 (WGS 72)
	      // 3 == WGS 84
	      // 4 == NAD 83
	      // 5 == Old Hawaii Datum
	      // 6 == Puerto Rico Datum

	  long getDataEdition() const;
	      // 01-99 Primarily a DMA specfic field. (For USGS use set to 01)

	  long getPerctVoid() const;
	      // Contains the percentage of nodes in the file set to void
       
	  long getWestEdgeFlag() const;
          // West edge match status flag

	  long getNorthEdgeFlag() const;
	      // North edge match status flag

	  long getEastEdgeFlag() const;
	      // East edge match staus flag

	  long getSouthEdgeFlag() const;
	      // South edge match status flag

	  double getVertDatumShift() const;
	      // Vertical datum shift - value is in the form of SFFF.DD Value is the average
	      // shift value for the four quadrangle corners obtained from program VERTCOM.
	 
   private:

     
      string _quadName;
	  string _processInfo;
	  double _seGeoCornerX;
	  double _seGeoCornerY;
	  long _processCode;
	  string _sectionIndicator;
      string _mapCenterCode;
      long _levelCode;
      long _elevPattern;
      long _groundRefSysCode;
      long _groundRefSysZone;
      long _groundRefSysUnits;
      long _elevUnits;
	  long _numPolySides;
      DEMPointVector _demCorners;
	  double _counterclockAngle;
	  long _elevAccuracyCode;
      double _minElevation;
      double _maxElevation;
      double _spatialResX;
      double _spatialResY;
      double _spatialResZ;
      long _profileRows;
      long _profileColumns;
	  long _largeContInt;
	  long _maxSourceUnits;
	  long _smallContInt;
	  long _minSourceUnits;
	  long _sourceDate;
	  long _inspRevDate;
	  string _inspFlag;
	  long _valFlag;
	  long _suspectVoidFlg;
	  long _vertDatum;
	  long _horizDatum;
	  long _dataEdition;
	  long _perctVoid;
	  long _westEdgeFlag;
	  long _northEdgeFlag;
	  long _eastEdgeFlag;
	  long _southEdgeFlag;
	  double _vertDatumShift;
};

#endif  // INCLUDED_DEMHEADER_HXX



