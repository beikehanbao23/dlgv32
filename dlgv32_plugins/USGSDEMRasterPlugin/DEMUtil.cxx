#include <stdlib.h>

#ifndef INCLUDED_DEMUTIL_HXX
#include "DEMUtil.hxx"
#endif

bool
DEMUtil::getRecord(istream& s, string& strbuf, long reclength)
{
   char* buf = new char[reclength + 1];

   bool flag = DEMUtil::getRecord(s,buf,reclength);
   if (flag == true)
      strbuf = buf;

   delete [] buf;

   return flag;
}

bool
DEMUtil::getRecord(istream& s, char* buf, long reclength)
{
   // buf is assumed to be at least reclength+1 in size.

   if (!s)
      return false;

   long curpos = 0;
   buf[curpos] = s.get();
   while ((buf[curpos] != EOF) && 
          (buf[curpos] != '\n') &&
          (curpos < reclength-1))
      {
         curpos++;
         buf[curpos] = s.get();
      }
   buf[curpos] = '\0';

   if (s.peek() == '\n')
      s.get();

   return true;

}

bool
DEMUtil::getDouble(string const& strbuf,
                   long const startpos,
                   long const width,
                   double& val)
{
   if ((startpos + width - 1) > strbuf.length())
      return false;

   // Convert FORTRAN 'D' exponent indicator to 'E'.
   string tempbuf(strbuf.substr(startpos,width));
   for (int i = 0; i < tempbuf.length(); i++)
      if (tempbuf[i] == 'D')
         tempbuf[i] = 'E';

   val = atof(tempbuf.c_str());
   return true;
}
