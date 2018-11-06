#ifndef INCLUDED_SIO_OSTREAMBUFFER_H
#include "io/sio_ostreamBuffer.h"
#endif

#ifndef INCLUDED_SIO_BUFFER_H
#include "io/sio_Buffer.h"
#endif

sio_ostreamBuffer::sio_ostreamBuffer()
{
   _privatebuf = 0;
};

void
sio_ostreamBuffer::reset()

{
   _buf.seekp(0);				  
};

bool
sio_ostreamBuffer::addData(char const* data,
                            long length)
{
   _buf.write(data, length);
   //XXX This needs to check the write, and return something useful.
   return true;
};

bool
sio_ostreamBuffer::getData(char const*& data,
                          long& length)
{
   delete[] _privatebuf;
   length = _buf.pcount();
   _privatebuf = new char[length];
   _buf.read(_privatebuf, length);
   data = _privatebuf;
   //XXX This needs to do some errorchecking, and return something meaningful.
   return true;
};