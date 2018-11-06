#ifdef _WIN32
	#include <iostream>
	#include <iomanip>
	#include <strstream>
	#include <vector>
	using namespace std;
#else
 #include <iostream.h>
 #include <iomanip.h>
 #include <strstream.h>
#endif

#include <stdlib.h>

#ifndef INCLUDED_DLGPOINTELEMENT_HXX
#include "dlg/DLGPointElement.hxx"
#endif

#ifndef INCLUDED_DLPPOINT_HXX
#include "dlg/DLGPoint.hxx"
#endif

#ifndef INCLUDED_DLGUTIL_HXX
#include "dlg/DLGUtil.hxx"
#endif

DLGPointElement::DLGPointElement(void)
{
   _recordType = "";
   _id = 0;
   _numIslands = 0;
}

DLGPointElement::DLGPointElement(const DLGPointElement& pe)
{
   operator=(pe);
}

DLGPointElement::~DLGPointElement(void)
{
}

DLGPointElement&
DLGPointElement::operator=(const DLGPointElement& pe)
{
   if (this == &pe)
      return *this;

   DLGElement::operator=(pe);
   _point = pe._point;
   _lineSegments = pe._lineSegments;
   _numIslands = pe._numIslands;

   return *this;
}

bool
DLGPointElement::operator==(DLGPointElement& pe)
{
   if (&pe == this)
      return true;

	// XXX This _really_ needs to be looked at.

#if 0
   if (_point != pe._point)
      return false;

   if (_numIslands != pe._numIslands)
      return false;

   if (_lineSegments != pe._lineSegments)
      return false;

   if (_attrs != pe._attrs)
      return false;
#endif

   return true;
}

ostream&
operator<<(ostream& s, DLGPointElement& pe)
{
   ostrstream ostr;

   s.setf(ios::left);

   ostr << pe._recordType.substr(0,1);
   ostr << setw(5) << pe._id;
   ostr.setf(ios::fixed, ios::floatfield);
   ostr.precision(2);
   ostr << setw(12) << pe._point.getX();
   ostr << setw(12) << pe._point.getY();
   ostr << setw(6) << 0;   // Number of elements in area list or node list.
                           // Not currently included.
   ostr << setw(6) << pe._lineSegments.size();
   ostr << setw(6) << 0;  // Number of x,y or lat-long points in area coordinate lists.
                          // Not currently included.
   ostr << setw(6) << pe._attrs.size();
   ostr << setw(6) << 0;  // Number of text attributes.
   if (pe._recordType == "N")
      ostr << "      ";
   else
      ostr << setw(6) << pe._numIslands;


   ostr << ends;
   s << setw(80) << ostr.str() << endl;
   ostr.freeze(0);

   if (pe._lineSegments.size() > 0)
      {
         ostr.seekp(0,ios::beg);
         int count = 0;
         for (vector<long>::iterator i = pe._lineSegments.begin();
              i != pe._lineSegments.end();
              i++)
            {
               long tmplong;
               tmplong = *i;
               ostr << setw(6) << tmplong;
               count++;
               if ((count > 0) && ((count % 12) == 0))
                  {
                     ostr << ends;
                     s << setw(80) << ostr.str() << endl;
                     ostr.freeze(0);
                     ostr.seekp(0,ios::beg);
                  }
            }

         // Any left over?
         if ((pe._lineSegments.size() % 12) != 0)
            {
               ostr << ends;
               s << setw(80) << ostr.str() << endl;
               ostr.freeze(0);
            }
      }

   if (pe._attrs.size() > 0)
      pe.writeAttributes(s);

   return s;
}

istream&
operator>>(istream& s, DLGPointElement& pe)
{
	//istream_iterator< string, char, char_traits<char> > j(s); 
   ///string bufstr;//(*j);
   char bufstr[100];
   char tmpstr[100];

   pe._recordType = "";
   pe._id = 0;
   pe._numIslands = 0;

   DLGUtil::getRecord(s,bufstr);
   //pe._recordType = bufstr.substr(0,1);
   strncpy( tmpstr, bufstr, 1 );
   tmpstr[1] = '\0';
   pe._recordType = tmpstr;

   //pe._id = atoi(bufstr.substr(1,6).c_str());
   strncpy( tmpstr, bufstr + 1, 6 );
   tmpstr[6] = '\0';
   pe._id = atoi( tmpstr );

   //double tmpx = atof(bufstr.substr(6,12).c_str());
   //double tmpy = atof(bufstr.substr(18,12).c_str());
   strncpy( tmpstr, bufstr + 6, 12 );
   tmpstr[12] = '\0';
   double tmpx = atof( tmpstr );
   strncpy( tmpstr, bufstr + 18, 12 );
   tmpstr[12] = '\0';
   double tmpy = atof( tmpstr );
   pe._point.setXY(tmpx,tmpy);

   //long numLineSegs = atoi(bufstr.substr(36,6).c_str());
   //long numAttrs = atoi(bufstr.substr(48,6).c_str());
   strncpy( tmpstr, bufstr + 36, 6 );
   tmpstr[6] = '\0';
   long numLineSegs = atoi( tmpstr );
   strncpy( tmpstr, bufstr + 48, 6 );
   tmpstr[6] = '\0';
   long numAttrs = atoi( tmpstr );

   if (pe._recordType == "A")
   {
      //pe._numIslands = atoi(bufstr.substr(60,6).c_str());
	  strncpy( tmpstr, bufstr + 60, 6 );
	  tmpstr[6] = '\0';
	  pe._numIslands = atoi( tmpstr );
   }

   pe._lineSegments.erase(pe._lineSegments.begin(), pe._lineSegments.end());
   if (numLineSegs > 0)
      {
         pe._lineSegments.reserve(numLineSegs);
         long curlineseg;
         for (long i = 0; i < numLineSegs; i++)
            {
               if (i % 12 == 0)
                  DLGUtil::getRecord(s,bufstr);
			   strncpy( tmpstr, bufstr + (i%12) * 6, 6 );
			   tmpstr[6]= '\0';
			   curlineseg = atoi( tmpstr );
               //curlineseg = atoi(bufstr.substr((i%12) * 6, 6).c_str());
               pe._lineSegments.push_back(curlineseg);
            }
      }
	
   pe.readAttributes(s, numAttrs);

   return s;
}


