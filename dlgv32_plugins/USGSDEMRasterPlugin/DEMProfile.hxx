#ifndef INCLUDED_DEMPROFILE_HXX
#define INCLUDED_DEMPROFILE_HXX

#ifndef INCLUDED_DEMPOINT_HXX
#include "DEMPoint.hxx"
#endif

#ifdef WIN32
#include <vector>
using namespace std;
#else
#include <vector.h>
#endif

typedef vector<long> DEMElevationVector;

class DEMProfile
{
   public:

      DEMProfile();
      DEMProfile(DEMProfile const& right);
      DEMProfile const& operator=(DEMProfile const& right);

      friend ostream& operator<<(ostream& s, DEMProfile& demp);
      friend istream& operator>>(istream& s, DEMProfile& demp);

      // Accessors

      long getRowNumber() const;
         // Row identification number. Typically set to 1.

      long getColumnNumber() const;
         // Column identification number. This is the profile sequence number.

      long getNumberOfElevations() const;
         // Number of elevations in this profile.

      DEMPoint const& getProfileLocation() const;
         // Location (in ground planimetric coordinates) of the first
         // elevation in the profile.

      double getLocalDatumElevation() const;
         // Elevation of local datum for the profile.
         // Value is in units of measure given by the Elevation Units field
         // found in the DEM header.

      double getMinimumElev() const;
         // Minimum elevation for this profile.

      double getMaximumElev() const;
         // Maximum elevation for this profile.

      DEMElevationVector const& getElevations() const;
         // Elevation values.
         // From the DEM standard:
         // "A value in this array would be multiplied by the spatial resolution
         // value and added to the elevation of the local elevation datum for the
         // element profile to obtain the elevation for the point."
      bool operator<(DEMProfile const& rhs) const {return false;}
      bool operator==(DEMProfile const& rhs) const {return false;}

   private:

      long _row;
      long _column;
      long _numberElevations;
      DEMPoint _profileLocation;
      double _locDatumElev;
      double _minElev;
      double _maxElev;
      DEMElevationVector _elevations;
};

#endif  // INCLUDED_DEMPROFILE_HXX
