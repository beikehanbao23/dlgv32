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
// sio_8211DRLeader.cpp
//

#ifndef INCLUDED_SIO_8211DRLEADER_H
#include "io/sio_8211DRLeader.h"
#endif

#ifndef INCLUDED_SIO_UTILS_H
#include "io/sio_Utils.h"
#endif

sio_8211DRLeader::sio_8211DRLeader()
{
   setLeaderIdentifier('D');
}

sio_8211DRLeader::~sio_8211DRLeader()
{

}

istream&
sio_8211DRLeader::streamExtract(istream& istr)
{

   // Assume istr is positioned on byte 0 of a DR Leader. Read the leader,
   // leaving istr positioned on the byte after the last byte in the leader.

   char leader[24];

   istr.read(leader,24);
   if ((istr.gcount() < 24) || (!istr))
      {
         istr.clear(ios::failbit);
         return istr;
      }
      
   _recLength        = sio_Utils::getLong(leader,0,5);
   _leaderIden       = leader[6];
   _fieldAreaStart   = sio_Utils::getLong(leader,12,5);
   _sizeFieldLength  = sio_Utils::getLong(leader,20,1);
   _sizeFieldPos     = sio_Utils::getLong(leader,21,1);
   _sizeFieldTag     = sio_Utils::getLong(leader,23,1);

   return istr;

} // sio_8211DRLeader:;streamExtract()



ostream&
sio_8211DRLeader::streamInsert(ostream& ostr) const
{
   // This code assumes a NEW stream pointing to an existing, empty file.
   // Write a DDR header to the file

   ostr << setw(5) << _recLength;       // Record Length
   ostr << setw(1) << ' ';              // Interchange Level
   ostr << setw(1) << _leaderIden;      // Leader Identifier
   ostr << setw(1) << ' ';              // Inline Code Extension Indicator
   ostr << setw(1) << '1';              // Version Number
   ostr << setw(1) << ' ';              // Application Indicator
   ostr << setw(2) << "  ";             // Field Control Length
   ostr << setw(5) << _fieldAreaStart;  // Base Address of Field Area
   ostr << setw(3) << "   ";            // Extended Character Set Indicator
   ostr << setw(1) << _sizeFieldLength; // Size of Field Length Field
   ostr << setw(1) << _sizeFieldPos;    // Size of Field Position Field
   ostr << setw(1) << '0';              // Reserved
   ostr << setw(1) << _sizeFieldTag;    // Size if Field Tag Field

   return ostr; 

}