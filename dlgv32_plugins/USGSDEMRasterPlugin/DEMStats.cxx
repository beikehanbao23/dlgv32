#include <stdlib.h>

#ifndef INCLUDE_DEMSTATS_HXX
#include "DEMStats.hxx"
#endif

#ifndef INCLUDED_DEMUTIL_HXX
#include "DEMUtil.hxx"
#endif

DEMStats::DEMStats()
        :_availCodeDE2(0),
		 _rsmeDE2x(0),
		 _rsmeDE2y(0),
         _rsmeDE2z(0),
		 _sampleSizeDE2(0),
         _availCodeDE5(0),
		 _rsmeDE5x(0),
		 _rsmeDE5y(0),
         _rsmeDE5z(0),
		 _sampleSizeDE5(0)

{
}

DEMStats::~DEMStats()
{
}

long
DEMStats::getAvailCodeDE2() const
{
	return _availCodeDE2;
}

long
DEMStats::getRSMEDE2x() const
{
	return _rsmeDE2x;
}

long
DEMStats::getRSMEDE2y() const
{
	return _rsmeDE2y;
}

long
DEMStats::getRSMEDE2z() const
{
	return _rsmeDE2z;
}

long
DEMStats::getSampleSizeDE2() const
{
	return _sampleSizeDE2;
}

long
DEMStats::getAvailCodeDE5() const
{
	return _availCodeDE5;
}

long
DEMStats::getRSMEDE5x() const
{
	return _rsmeDE5x;
}

long
DEMStats::getRSMEDE5y() const
{
	return _rsmeDE5y;
}

long
DEMStats::getRSMEDE5z() const
{
	return _rsmeDE5z;
}

long
DEMStats::getSampleSizeDE5() const
{
	return _sampleSizeDE5;
}

ostream&
operator<<(ostream& s,  DEMStats const& stats)
{
	return s;
}

istream&
operator>>(istream& s, DEMStats& stats)
{

	char bufstr[1024];

	DEMUtil::getRecord(s, bufstr);


	stats._availCodeDE2 = DEMUtil::getLong(bufstr, 0, 6);
	stats._rsmeDE2x = DEMUtil::getLong(bufstr, 6, 6);
	stats._rsmeDE2y = DEMUtil::getLong(bufstr, 12, 6);
	stats._rsmeDE2z = DEMUtil::getLong(bufstr, 18, 6);
	stats._sampleSizeDE2 = DEMUtil::getLong(bufstr, 24, 6);
	stats._availCodeDE5 = DEMUtil::getLong(bufstr, 30, 6);
	stats._rsmeDE5x = DEMUtil::getLong(bufstr, 36, 6);
	stats._rsmeDE5y = DEMUtil::getLong(bufstr, 42, 6);
	stats._rsmeDE5z = DEMUtil::getLong(bufstr, 48, 6);
	stats._sampleSizeDE5 = DEMUtil::getLong(bufstr, 54, 6);


	return s;
}