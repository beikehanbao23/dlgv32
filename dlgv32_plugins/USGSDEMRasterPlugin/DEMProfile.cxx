
#include "shortnam.hxx"

#ifdef WIN32
#else
#include <iostream.h>
#include <strstream.h>
#endif

#include <stdlib.h>

#ifndef INCLUDED_DEMPROFILE_HXX
#include "DEMProfile.hxx"
#endif

#ifndef INCLUDED_DEMUTIL_HXX
#include "DEMUtil.hxx"
#endif

DEMProfile::DEMProfile()
          : _row(0),
            _column(0),
            _numberElevations(0),
            _locDatumElev(0.0),
            _minElev(0.0),
            _maxElev(0.0)
{
}

DEMProfile::DEMProfile(DEMProfile const& right)
{
   operator=(right);
}

DEMProfile const&
DEMProfile::operator=(DEMProfile const& right)
{
   if (this == &right)
      return *this;

   _row = right._row;
   _column = right._column;
   _numberElevations = right._numberElevations;
   _profileLocation = right._profileLocation;
   _locDatumElev = right._locDatumElev;
   _minElev = right._minElev;
   _maxElev = right._maxElev;
   _elevations = right._elevations;

   return *this;
}

long
DEMProfile::getRowNumber() const
{
   return _row;
}

long
DEMProfile::getColumnNumber() const
{
   return _column;
}

long
DEMProfile::getNumberOfElevations() const
{
   return _numberElevations;
}

DEMPoint const&
DEMProfile::getProfileLocation() const
{
   return _profileLocation;
}

double
DEMProfile::getLocalDatumElevation() const
{
   return _locDatumElev;
}

double
DEMProfile::getMinimumElev() const
{
   return _minElev;
}

double
DEMProfile::getMaximumElev() const
{
   return _maxElev;
}

DEMElevationVector const&
DEMProfile::getElevations() const
{
   return _elevations;
}

istream&
operator>>(istream& s, DEMProfile& demp)
{
//   string bufstr;
   char bufstr[1024];

   DEMUtil::getRecord(s,bufstr);

   demp._row = DEMUtil::getLong(bufstr, 0, 6);
   demp._column = DEMUtil::getLong(bufstr, 6, 6);
   demp._numberElevations = DEMUtil::getLong(bufstr, 12, 6);

   double x,y;
   DEMUtil::getDouble(bufstr, 24, 24, x);
   DEMUtil::getDouble(bufstr, 48, 24, y);
   demp._profileLocation.setXY(x,y);

   DEMUtil::getDouble(bufstr, 72, 24, demp._locDatumElev);
   DEMUtil::getDouble(bufstr, 96, 24, demp._minElev);
   DEMUtil::getDouble(bufstr, 120, 24, demp._maxElev);

   demp._elevations.erase(demp._elevations.begin(), demp._elevations.end());   
   demp._elevations.reserve(demp._numberElevations);

   // Extract elevations in this record.
   long count = 0;
   while ((count < 146) && (count < demp._numberElevations))
      {
         demp._elevations.push_back(DEMUtil::getLong(bufstr, 144+(count*6), 6));
         count++;
      }
   
   long t;
   while (count < demp._numberElevations)
      {
         t = (count - 146) % 170;
         if (t == 0)
            DEMUtil::getRecord(s,bufstr);
         demp._elevations.push_back(DEMUtil::getLong(bufstr, t*6, 6));
         count++;
      }

   return s;
}


ostream&
operator<<(ostream& s, DEMProfile& demp)
{
   return s;
}


