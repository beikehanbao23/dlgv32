
// $Id: DEMHeader.cxx,v 1.1 1998/08/14 14:55:20 bmaddox Exp bmaddox $

#include <stdlib.h>

#ifndef INCLUDED_DEMHEADER_HXX
#include "DEMHeader.hxx"
#endif

#ifndef INCLUDED_DEMUTIL_HXX
#include "DEMUtil.hxx"
#endif

DEMHeader::DEMHeader()
         : _seGeoCornerX(0.0),
		   _seGeoCornerY(0.0),
		   _processCode(0),
           _levelCode(0),
           _elevPattern(0),
           _groundRefSysCode(0),
           _groundRefSysZone(0),
           _groundRefSysUnits(0),
           _elevUnits(0),
		   _numPolySides(0),
		   _counterclockAngle(0.0),
		   _elevAccuracyCode(0),
           _minElevation(0),
           _maxElevation(0),
           _spatialResX(0.0),
           _spatialResY(0.0),
           _spatialResZ(0.0),
           _profileRows(0),
           _profileColumns(0),
		   _largeContInt(0),
		   _maxSourceUnits(0),
		   _smallContInt(0),
		   _minSourceUnits(0),
		   _sourceDate(0),
		   _inspRevDate(0),
		   _valFlag(0),
		   _suspectVoidFlg(0),
		   _vertDatum(0),
		   _horizDatum(0),
		   _dataEdition(0),
		   _perctVoid(0),
		   _westEdgeFlag(0),
		   _northEdgeFlag(0),
		   _eastEdgeFlag(0),
		   _southEdgeFlag(0),
		   _vertDatumShift(0.0)
{
}
   
string const&
DEMHeader::getQuadName() const
{
   return _quadName;
}

string const&
DEMHeader::getProcessInfo() const
{
	return _processInfo;
}

double
DEMHeader::getSEGeoCornerX() const
{
	return _seGeoCornerX;
}

double
DEMHeader::getSEGeoCornerY() const
{
	return _seGeoCornerY;
}

long
DEMHeader::getProcessCode() const
{
	return _processCode;
}

string const&
DEMHeader::getSectionIndicator() const
{
	return _sectionIndicator;
}

string const&
DEMHeader::getMappingCenterCode() const
{
   return _mapCenterCode;
}

long
DEMHeader::getLevelCode() const
{
   return _levelCode;
}
         
long
DEMHeader::getElevPattern() const
{
   return _elevPattern;
}

long
DEMHeader::getGroundRefSysCode() const
{
   return _groundRefSysCode;
}
    
long
DEMHeader::getGroundRefSysZone() const
{
   return _groundRefSysZone;
}

long
DEMHeader::getGroundRefSysUnits() const
{
   return _groundRefSysUnits;
}

long
DEMHeader::getElevationUnits() const
{
   return _elevUnits;
}

long
DEMHeader::getNumPolySides() const
{
	return _numPolySides;
}

DEMPointVector const&
DEMHeader::getDEMCorners() const
{
    return _demCorners;
}

double
DEMHeader::getCounterclockAngle() const
{
	return _counterclockAngle;
}

long
DEMHeader::getElevAccuracyCode() const
{
	return _elevAccuracyCode;
}

double
DEMHeader::getMinimumElev() const
{
   return _minElevation;
}

double
DEMHeader::getMaximumElev() const
{
   return _maxElevation;
}

double
DEMHeader::getSpatialResX() const
{
   return _spatialResX;
}

double
DEMHeader::getSpatialResY() const
{
   return _spatialResY;
}

double
DEMHeader::getSpatialResZ() const
{
   return _spatialResZ;
}

long
DEMHeader::getProfileRows() const
{
   return _profileRows;
}

long
DEMHeader::getProfileColumns() const
{
   return _profileColumns;
}

long
DEMHeader::getLargeContInt() const
{
	return _largeContInt;
}

long
DEMHeader::getMaxSourceUnits() const
{
	return _maxSourceUnits;
}

long
DEMHeader::getSmallContInt() const
{
	return _smallContInt;
}

long
DEMHeader::getMinSourceUnits() const
{
	return _minSourceUnits;
}

long
DEMHeader::getSourceDate() const
{
	return _sourceDate;
}

long
DEMHeader::getInspRevDate() const
{
	return _inspRevDate;
}

string const&
DEMHeader::getInspFlag() const
{
	return _inspFlag;
}

long
DEMHeader::getDataValFlag() const
{
	return _valFlag;
}

long
DEMHeader::getSuspectVoidFlag() const
{
	return _suspectVoidFlg;
}

long
DEMHeader::getVertDatum () const
{
	return _vertDatum;
}

long
DEMHeader::getHorizDatum() const
{
	return _horizDatum;
}

long
DEMHeader::getDataEdition() const
{
	return _dataEdition;
}

long
DEMHeader::getPerctVoid() const
{
	return _perctVoid;
}

long
DEMHeader::getWestEdgeFlag() const
{
	return _westEdgeFlag;
}

long
DEMHeader::getNorthEdgeFlag() const
{
	return _northEdgeFlag;
}

long
DEMHeader::getEastEdgeFlag() const
{
	return _eastEdgeFlag;
}

long
DEMHeader::getSouthEdgeFlag() const
{
	return _southEdgeFlag;
}

double
DEMHeader::getVertDatumShift() const
{
	return _vertDatumShift;
}

ostream&
operator<<(ostream& s, DEMHeader& header)
{
   return s;
}

istream&
operator>>(istream& s, DEMHeader& header)
{
	char bufstr[1024];
	char temp[1024];
   long i;

   DEMUtil::getRecord(s,bufstr);

   strncpy(temp, bufstr, 40);
   temp[40] = '\0';
   header._quadName = temp;

   strncpy(temp,bufstr+40,40);
   temp[40] = '\0';
   header._processInfo = temp;
   
   DEMUtil::getDouble(bufstr, 109, 13, header._seGeoCornerX);
   DEMUtil::getDouble(bufstr, 122, 13, header._seGeoCornerY);
   header._processCode = DEMUtil::getLong(bufstr, 135, 1);

   strncpy(temp,bufstr+137,3);
   temp[3] = '\0';
   header._sectionIndicator = temp;

   strncpy(temp,bufstr+140,4);
   temp[4] = '\0';
   header._mapCenterCode = temp;
    
   header._levelCode = DEMUtil::getLong(bufstr, 144, 6);
   header._elevPattern = DEMUtil::getLong(bufstr, 150, 6);
   header._groundRefSysCode = DEMUtil::getLong(bufstr, 156, 6);
   header._groundRefSysZone = DEMUtil::getLong(bufstr, 162, 6);
   header._groundRefSysUnits = DEMUtil::getLong(bufstr, 528, 6);
   header._elevUnits = DEMUtil::getLong(bufstr, 534, 6);
   header._numPolySides = DEMUtil::getLong(bufstr, 540, 6);

   for (i = 0; i < 4; i++)
      {
         double x,y;
         long pos = 546 + (i * 48);
         DEMUtil::getDouble(bufstr, pos, 24, x);
         DEMUtil::getDouble(bufstr, pos + 24, 24, y);
         header._demCorners.push_back(DEMPoint(x,y));
      }

   DEMUtil::getDouble(bufstr, 738, 24, header._minElevation);
   DEMUtil::getDouble(bufstr, 762, 24, header._maxElevation);
   DEMUtil::getDouble(bufstr, 786, 24, header._counterclockAngle );
   header._elevAccuracyCode = DEMUtil::getLong(bufstr, 810, 6);
   DEMUtil::getDouble(bufstr, 816, 12, header._spatialResX);
   DEMUtil::getDouble(bufstr, 828, 12, header._spatialResY);
   DEMUtil::getDouble(bufstr, 840, 12, header._spatialResZ);
   header._profileRows = DEMUtil::getLong(bufstr, 852, 6);
   header._profileColumns = DEMUtil::getLong(bufstr, 858, 6);
   header._largeContInt = DEMUtil::getLong(bufstr, 864, 5);
   header._maxSourceUnits = DEMUtil::getLong(bufstr, 869, 1);
   header._smallContInt = DEMUtil::getLong(bufstr, 870, 5);
   header._minSourceUnits = DEMUtil::getLong(bufstr, 875, 1);
   header._sourceDate = DEMUtil::getLong(bufstr, 876, 4);
   header._inspRevDate = DEMUtil::getLong(bufstr, 880, 4);
   
   strncpy(temp, bufstr+884,1);
   temp[1]='\0';
   header._inspFlag = temp;

   header._valFlag = DEMUtil::getLong(bufstr, 885, 1);
   header._suspectVoidFlg = DEMUtil::getLong(bufstr, 886, 2);
   header._vertDatum = DEMUtil::getLong(bufstr, 888, 2);
   header._horizDatum = DEMUtil::getLong(bufstr, 890, 2);
   if (header._horizDatum == 0)
      header._horizDatum = 1;   // Default to NAD27

   header._dataEdition = DEMUtil::getLong(bufstr, 892, 4);
   header._perctVoid = DEMUtil::getLong(bufstr, 896, 4);
   header._westEdgeFlag = DEMUtil::getLong(bufstr, 900, 2);
   header._northEdgeFlag = DEMUtil::getLong(bufstr, 902, 2);
   header._eastEdgeFlag = DEMUtil::getLong(bufstr, 904, 2);
   header._southEdgeFlag = DEMUtil::getLong(bufstr, 906, 2);
   DEMUtil::getDouble(bufstr, 908, 7, header._vertDatumShift);






   return s;  
}
