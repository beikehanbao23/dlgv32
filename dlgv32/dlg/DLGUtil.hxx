#ifndef INCLUDED_DLGUTIL_HXX
#define INCLUDED_DLGUTIL_HXX

#ifdef _WIN32
   #include <iostream>
   using namespace std;
#else
 #include <iostream.h>
#endif
#include <string>

class DLGUtil
{
   public:

      static bool getRecord(istream& s, string& strbuf, long reclength = 80);
         // Reads a single record from a DLG. 
         // This is more difficult than it should be. According to the standard,
         // DLG-Optional format DLGs should have a fixed record length of 80 characters.
         // It says nothing about line termination. In practice, I've seen:
         //    * 80 character records and no line termination.
         //    * 80 character records terminated with '\n'.
         //    * varying length records terminated with '\n'.
         //
         // Returns true if succesful. Returns false if EOF or error.

      static bool getRecord(istream& s, char* buf, long reclength = 80);
         // Same as getRecord above. buf should be at least reclength+1 in size.

};

#endif  // INCLUDED_DLGUTIL_HXX