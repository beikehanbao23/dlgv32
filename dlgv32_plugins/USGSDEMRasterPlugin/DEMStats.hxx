#ifndef INCLUDE_DEMSTATS_HXX
#define INCLUDE_DEMSTATS_HXX

//#ifdef WIN32
   #include <iostream>
   #include <string>
   using namespace std;
//#else
//   #include <iostream.h>
//   #include <string>
//#endif	

class DEMStats;
ostream& operator<<(ostream& s, DEMStats const& stats);
istream& operator>>(istream& s, DEMStats& stats);

class DEMStats
{
public:

	DEMStats();
	friend ostream& operator<<(ostream& s, DEMStats const& stats);
	friend istream& operator>>(istream& s, DEMStats& stats);

	~DEMStats();

	//Accessors

	long getAvailCodeDE2() const;
	// 1 = available
	// 2 = unavailable
	//The code defines the availability of statics

	long getRSMEDE2x () const;

	long getRSMEDE2y () const;

	long getRSMEDE2z () const;
	
    long getSampleSizeDE2() const;
	// This code defines the sample size use
	// to compute the accuracy, if 0 then the
	// accuracy is estimated.

    long getAvailCodeDE5() const;
	// 1 = available
	// 2 = unavailable
	//The code defines the availability of statics

	long getRSMEDE5x () const;

	long getRSMEDE5y () const;

	long getRSMEDE5z () const;
	

	long getSampleSizeDE5() const;
	// This code defines the sample size use
	// to compute the accuracy, if 0 then the
	// accuracy is estimated.



private:

	long _availCodeDE2;
	long _rsmeDE2x;
	long _rsmeDE2y;
	long _rsmeDE2z;
	long _sampleSizeDE2;
	long _availCodeDE5;
	long _rsmeDE5x;
	long _rsmeDE5y;
	long _rsmeDE5z;
	long _sampleSizeDE5;


};

#endif //INCLUDE_DEMSTATS_HXX
