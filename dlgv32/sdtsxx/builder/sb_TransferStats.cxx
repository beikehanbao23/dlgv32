#include <iostream>

#ifndef INCLUDED_SB_UTILS_HXX
#include "builder/sb_Utils.hxx"
#endif

#ifndef INCLUDED_SB_TRANSFERSTATS_HXX
#include "builder/sb_TransferStats.hxx"
#endif

sb_TransferStats::sb_TransferStats()
               : d_recordID(0),
                 d_modRecCount(0),
                 d_sadrCount(0)
{
}

sb_TransferStats::sb_TransferStats(sb_TransferStats const& right)
{
   operator=(right);
}

sb_TransferStats const&
sb_TransferStats::operator=(sb_TransferStats const& right)
{
   if (this == &right) return *this;

   d_moduleName = right.d_moduleName;
   d_recordID = right.d_recordID;
   d_modTypeRef = right.d_modTypeRef;
   d_modNameRef = right.d_modNameRef;
   d_modRecCount = right.d_modRecCount;
   d_sadrCount = right.d_sadrCount;

   return *this;
}

sb_TransferStats::sb_TransferStats(sc_Record& recprox)
{
   sc_FieldCntr::const_iterator curfield;
   if (!sb_Utils::getFieldByMnem(recprox,"STAT",curfield))
      {
         cerr << "sb_TransferStats::sb_TransferStats(sc_Record const&):";
         cerr << " Not a STAT record.\n";
         return;
      }
   
   // We have a primary field from a STAT module. Start picking it apart.

   sc_SubfieldCntr::const_iterator cursubfield;
   
   // MODN
   if (sb_Utils::getSubfieldByMnem(*curfield,"MODN",cursubfield))
      cursubfield->getA(d_moduleName);

   // RCID
   if (sb_Utils::getSubfieldByMnem(*curfield,"RCID",cursubfield))
      cursubfield->getI(d_recordID);

   // MNTF
   if (sb_Utils::getSubfieldByMnem(*curfield,"MNTF",cursubfield))
      cursubfield->getA(d_modTypeRef);

   // MNRF
   if (sb_Utils::getSubfieldByMnem(*curfield,"MNRF",cursubfield))
      cursubfield->getA(d_modNameRef);

   // NREC
   if (sb_Utils::getSubfieldByMnem(*curfield,"NREC",cursubfield))
      cursubfield->getI(d_modRecCount);

   // NSAD
   if (sb_Utils::getSubfieldByMnem(*curfield,"NSAD",cursubfield))
      cursubfield->getI(d_sadrCount);

}


