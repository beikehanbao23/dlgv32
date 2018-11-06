#ifndef INCLUDED_SB_TRANSFERSTATS_HXX
#define INCLUDED_SB_TRANSFERSTATS_HXX

class sc_Record;

class sb_TransferStats
{
   public:

      sb_TransferStats();
      sb_TransferStats(sb_TransferStats const& right);
      sb_TransferStats const& operator=(sb_TransferStats const& right);
      explicit sb_TransferStats(sc_Record& recprox);
         // recprox must be from a Transfer Statistics module.

      // Accessors

      string const& getModuleName() const;
      long getRecordID() const;
      string const& getModuleTypeReferred() const;
      string const& getModuleNameReferred() const;
      long getModuleRecCount() const;
      long getSpatialAddrCount() const;

   private:

      string d_moduleName;
      long d_recordID;
      string d_modTypeRef;
      string d_modNameRef;
      long d_modRecCount;
      long d_sadrCount;
};

inline
string const&
sb_TransferStats::getModuleName() const
{
   return d_moduleName;
}

inline
long
sb_TransferStats::getRecordID() const
{
   return d_recordID;
}

inline
string const&
sb_TransferStats::getModuleTypeReferred() const
{
   return d_modTypeRef;
}

inline
string const&
sb_TransferStats::getModuleNameReferred() const
{
   return d_modNameRef;
}

inline
long
sb_TransferStats::getModuleRecCount() const
{
   return d_modRecCount;
}

inline
long
sb_TransferStats::getSpatialAddrCount() const
{
   return d_sadrCount;
}

#endif  // INCLUDED_SB_TRANSFERSTATS_HXX
