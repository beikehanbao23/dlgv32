//
// This file is part of the SDTS++ toolkit, written by the U.S.
// Geological Survey.  It is experimental software, written to support
// USGS research and cartographic data production.
// 
// SDTS++ is public domain software.  It may be freely copied,
// distributed, and modified.  The USGS welcomes user feedback, but makes
// no committment to any level of support for this code.  See the SDTS
// web site at http://mcmcweb.er.usgs.gov/sdts for more information,
// including points of contact.
//
//
// sio_8211Record.h
//


#ifndef INCLUDED_SIO_8211RECORD_H
#define INCLUDED_SIO_8211RECORD_H


#ifdef WIN32
#include <iostream>
   using namespace std;
#else
#include <iostream.h>
#endif


#ifndef INCLUDED_SIO_8211DIRECTORY_H
#include "io/sio_8211Directory.h"
#endif

#ifndef INCLUDED_SIO_8211FIELDAREA_H
#include "io/sio_8211FieldArea.h"
#endif

#ifndef INCLUDED_SIO_8211LEADER_H
#include "io/sio_8211Leader.h"
#endif


class sio_8211Field;
class sio_Buffer;

class sio_8211Record;
istream& operator>>(istream& istr, sio_8211Record& record);
ostream& operator<<(ostream& ostr, sio_8211Record & record);

class sio_8211Record
{
   // Abstract class. Represents the commonality between a DDR and a DR.

   public:

      sio_8211Record();
      virtual ~sio_8211Record();

      // Pure virtual because child classes define their own leaders.  That
      // is, sio_8211DR has an sio_8211DRLeader and an sio_8211DDR has an
      // sio_8211DDRLeader.
      virtual sio_8211Leader const& getLeader() const = 0;

      sio_8211Directory const& getDirectory() const;
      sio_8211FieldArea const& getFieldArea() const;

      // Add a field to the record that has the given tag.
      bool addField(string const & tag, sio_8211Field const& field);
      bool addField(string const & tag, sio_Buffer const& field_data); 

      friend istream& operator>>(istream& istr, sio_8211Record& record);
      friend ostream& operator<<(ostream& ostr, sio_8211Record & record);

   protected:

      virtual istream& streamExtract(istream& istr) = 0;
      virtual ostream& streamInsert(ostream& ostr) ;

      virtual void setLeader( sio_8211Leader const& );
      void setDirectory( sio_8211Directory const& );
      void setFieldArea( sio_8211FieldArea const& );

      sio_8211Directory& _getDirectory();  // non-const version for streamExtract()

      sio_8211FieldArea& _getFieldArea();

      virtual sio_8211Leader& _getLeader() = 0;

      // Uility for making sure that the given leader accurately
      // reflects the current state of the record.  That is, that
      // is the various lengths are all updated appropriately.
      virtual void _synchLeaderWithRecord( );

   private:

      // An 8211 Record has a leader, a directory and a field area.

      sio_8211Directory    _dir;
      sio_8211FieldArea    _fieldArea;

}; // class sio_8211Record




#endif  // INCLUDED_SIO_8211RECORD_H
