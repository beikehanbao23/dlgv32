#ifndef INCLUDED_SIO_OSTREAMBUFFER_H
#define INCLUDED_SIO_OSTREAMBUFFER_H


#ifdef WIN32
#include <iostream>
#include <strstream>
#include <string>
   using namespace std;
#else
#include <iostream.h>
#include <strstream.h>
#include <string.h>
#endif

#ifndef INCLUDED_SIO_BUFFER_H
#include "io/sio_Buffer.h"
#endif

class sio_ostreamBuffer : public sio_Buffer
{  // Implement the buffer class using the strstream.
   public:
      sio_ostreamBuffer();

      void reset();

	  bool addData(char const* data,
                  long length);

	  bool getData(char const*& data,
                long& length);

   private: 
      strstream _buf;
   	  char* _privatebuf;
};

#endif
