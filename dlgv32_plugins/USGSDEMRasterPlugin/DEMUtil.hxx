#ifndef INCLUDED_DEMUTIL_HXX
#define INCLUDED_DEMUTIL_HXX


#ifdef WIN32
#include <string>
using namespace std;
#else
#include <string>
#include <iostream.h>
#endif

class DEMUtil
{
   public:

      static bool getRecord(istream& s, string& strbuf, long reclength = 1024);
         // Reads a single record from a DEM. 
         // Returns true if succesful. Returns false if EOF or error.

      static bool getRecord(istream& s, char* buf, long reclength = 1024);
         // Same as getRecord above. buf should be at least reclength+1 in size.

 //     static long getLong(string const& strbuf, // string to extract long from
//                         long const startpos,  // starting position of field
 //                         long const width)     // width of field
//         {
//            return atol(strbuf.substr(startpos,width).c_str());
//         }

//      static long getLong(char* const strbuf, // string to extract long from
//                          long const startpos,  // starting position of field
 //                         long const width)     // width of field
//         {
//			char temp[1024];
//			return atol(strncpy(temp,strbuf+startpos,width));
//         }

	  static long getLong(char* const strbuf, // string to extract long from
                         long const startpos,  // starting position of field
                          long const width)     // width of field
         {
			char temp[1024];
			strncpy(temp,strbuf+startpos,width);
			temp[width] = '\0';
			return atol(temp);
         }

      static bool getDouble(string const& strbuf, // string to extract double from
                            long const startpos,  // starting position of field
                            long const width,     // width of field
                            double& val);         // value extracted from field.

   private:

      DEMUtil();
};

#endif  // INCLUDED_DEMUTIL_HXX