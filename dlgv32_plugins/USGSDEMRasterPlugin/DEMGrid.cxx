
#ifdef WIN32
#include <vector>
using namespace std;
#else
#include <iostream.h>
#include <vector.h>
#endif

#ifndef INCLUDED_DEMPROFILE_HXX
#include "DEMProfile.hxx"
#endif

#ifndef INCLUDED_DEMGRID_HXX
#include "DEMGrid.hxx"
#endif

#ifndef INCLUDED_DEMHEADER_HXX
#include "DEMHeader.hxx"
#endif

#ifndef INCLUDED_DEMPOINT_HXX
#include "DEMPoint.hxx"
#endif

#ifndef INCLUDED_DEMUTIL_HXX
#include "DEMUtil.hxx"
#endif

DEMGrid::DEMGrid(float missingDataValue)
       : _missDataVal(missingDataValue),
         _width(0),
         _height(0),
         _grid(0),
         _firstTime(true),
         _curProfile(0)
{        
}

DEMGrid::~DEMGrid()
{
   delete _grid;
}

long
DEMGrid::read(istream& dem, bool incrementalRead)
{
   if (_firstTime)
      {
         dem >> _header;
      }

   long retval;
   if (_header.getGroundRefSysCode() == 0)  // Geographic
      retval = fillGeographic(dem,incrementalRead);
   else
      retval = fillUTM(dem,incrementalRead);   // This may not work if it's 
                                               // really in State Plane.

   if (_firstTime)
      _firstTime = false;

   return retval;
}

DEMHeader const&
DEMGrid::getHeader() const
{
   return _header;
}

long
DEMGrid::getWidth() const
{
   return _width;
}

long
DEMGrid::getHeight() const
{
   return _height;
}

float
DEMGrid::getElevation(long x, long y) const
{
   if (_grid == 0)
      return _missDataVal;

   if ((x < 0) || (y < 0) || (x >= _width) || (y >= _height))
      return _missDataVal;

   return _grid[(y * _width) + x];
}

float
DEMGrid::getMissingDataValue() const
{
   return _missDataVal;
}

long
DEMGrid::fillGeographic(istream& dem,bool incrementalRead)
{
	if (_firstTime) {
      _curProfile = 0;
      _width = _header.getProfileColumns();
	}

   while (_curProfile < _width)
   {
         _profiles.push_back(DEMProfile());
         dem >> _profiles.back();
         _curProfile++;
         if (incrementalRead)
            return _width - _curProfile + 1;
   }

   // Assume all profiles have as many elevations as the first.
   _height = _profiles[0].getNumberOfElevations();
   _grid = new float[_width * _height];

   DEMPoint sw_corner = _profiles[0].getProfileLocation();
   _northwest_x = sw_corner.getX();
   _northwest_y = sw_corner.getY() + ((_profiles[0].getNumberOfElevations() - 1) * _header.getSpatialResY());


   long i,j;
   for (i = 0; i < _width; i++)
      {
         DEMElevationVector const& elev = _profiles[i].getElevations();
         for (j = 0; j < elev.size(); j++)
            {
               setElevation(i, _height - j - 1, elev[j]);
            }
      }

   _profiles.erase(_profiles.begin(), _profiles.end());

   return 0;
}

long
DEMGrid::fillUTM(istream& dem, bool incrementalRead)
{
   // 7.5 UTM DEMs are small enough we can get away with doing this stupid...

   long i;
   long x,y;
   // static vector<DEMProfile> profiles;

   if (_firstTime)
      {
         _curProfile = 0;
         _width = _header.getProfileColumns();
      }


   while (_curProfile < _width)
      {
         _profiles.push_back(DEMProfile());
         dem >> _profiles.back();
         _curProfile++;
         if (incrementalRead)
            return _width - _curProfile + 1;
      }

   double dy = _header.getSpatialResY();

   // Determine min and max Y values.
   // Some DEMs can have profiles which do not have any
   // elevations, and erroneous (x,y) values. I suspect
   // these are probably illegal DEMs, but we'll try to
   // do the right thing anyway.
   DEMPoint curpoint;
   i = 0;
   while ((_profiles[i].getNumberOfElevations() == 0) &&
          (i < _profiles.size()))
      i++;
   if (i < _profiles.size())
      curpoint = _profiles[i].getProfileLocation();
   else
      {
         // XXX This isn't the best way to handle this...
         cerr << "Yikes! All profiles have zero elevations!\n";
         exit(1);
      }
 
   double miny, maxy;
   miny = curpoint.getY();
   maxy = miny;
   double profymin, profymax;  // Min and max y values for current profile.
   for (i = 0; i < _profiles.size(); i++)
      {
         if (_profiles[i].getNumberOfElevations() > 0)
         {
            curpoint = _profiles[i].getProfileLocation();
            profymin = curpoint.getY();
            profymax = profymin + ((_profiles[i].getNumberOfElevations() - 1) * dy);

            if (profymin < miny)
               miny = profymin;
            if (profymax > maxy)
               maxy = profymax;
         }
      }

   // We now have minimum and maximum y values over all profiles in the DEM.
   // Allocate a rectangular array large enough to hold them.

   _height = static_cast<long>(((maxy - miny) / dy) + 1);
   _grid = new float[_width * _height];

   // Fill grid with the "missing data" value.
   for (i = 0; i < _width * _height; i++)
      _grid[i] = _missDataVal;

   DEMPoint sw_corner = _profiles[0].getProfileLocation();
   _northwest_x = sw_corner.getX();
   _northwest_y = maxy;


   // Now, insert the elevations in the profiles in the appropriate place in the grid.

   long startpos;
   for (x = 0; x < _width; x++)
      {
         DEMElevationVector const& elev = _profiles[x].getElevations();
         curpoint = _profiles[x].getProfileLocation();
         startpos = static_cast<long>((curpoint.getY() - miny) / dy);
         for (y = 0; y < elev.size(); y++)
            {
               setElevation(x, _height - startpos - y - 1, elev[y]);
            }
      }

   _profiles.erase(_profiles.begin(), _profiles.end());

   return 0;
}

void
DEMGrid::getGroundCoords(long x, long y, double& ground_x, double& ground_y)
{
   ground_x = _northwest_x + (x * _header.getSpatialResX());
   ground_y = _northwest_y - (y * _header.getSpatialResY());
}
