
// $Id: sb_ForeignID.cxx,v 1.1 1998/09/14 15:04:23 bmaddox Exp bmaddox $

#ifndef INCLUDED_SB_FOREIGNID_HXX
#include "builder/sb_ForeignID.hxx"
#endif

#ifndef INCLUDED_SB_UTILS_HXX
#include "builder/sb_Utils.hxx"
#endif

sb_ForeignID::sb_ForeignID()
           : d_recordID(0)
{
}

sb_ForeignID::sb_ForeignID(sb_ForeignID const& right)
{
   operator=(right);
}

sb_ForeignID::sb_ForeignID(sc_Field const& fidField)
{
   // Make a sb_ForeignID from a ForeignID sc_Field.
   
   sc_SubfieldCntr::const_iterator cursubfield;

   // MODN
   if (sb_Utils::getSubfieldByMnem(fidField,"MODN",cursubfield))
      cursubfield->getA(d_moduleName);

   // RCID
   if (sb_Utils::getSubfieldByMnem(fidField,"RCID",cursubfield))
      cursubfield->getI(d_recordID);

   // USAG
   if (sb_Utils::getSubfieldByMnem(fidField,"USAG",cursubfield))
      cursubfield->getA(d_usageModifier);
}

sb_ForeignID const&
sb_ForeignID::operator=(sb_ForeignID const& right)
{
   if(this == &right) 
     return *this;

   d_moduleName = right.d_moduleName;
   d_recordID = right.d_recordID;
   d_usageModifier = right.d_usageModifier;

   return *this;
}

bool
sb_ForeignID::operator==(sb_ForeignID const& right) const
{
   return (d_moduleName == right.d_moduleName) &&
          (d_recordID == right.d_recordID) &&
          (d_usageModifier == right.d_usageModifier);
}
