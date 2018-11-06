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
// $Id: sc_Subfield.cpp,v 1.1 1998/09/14 15:04:39 bmaddox Exp bmaddox $
//

//#ifndef INCLUDED_CONVERSIONS_HXX
//#include "container/conversions.h"
//#endif

#include "container/sc_Subfield.h"


static const char* const _iden = "$Id: sc_Subfield.cpp,v 1.1 1998/09/14 15:04:39 bmaddox Exp bmaddox $";


static
bool
_isInt( sc_Subfield::SubfieldType type )
{
   return   type == sc_Subfield::is_I     ||
            type == sc_Subfield::is_BI8   ||
            type == sc_Subfield::is_BI16  ||
            type == sc_Subfield::is_BI24  ||
            type == sc_Subfield::is_BI32;
} // _isInt()


sc_Subfield::sc_Subfield()
   : _type( is_I )
{
}

sc_Subfield::sc_Subfield(sc_Subfield const& right)
{
   *this = right;
}

sc_Subfield::~sc_Subfield()
{ 
}

sc_Subfield& sc_Subfield::operator=(const sc_Subfield& right)
{
   if (this == &right)
      return *this;

   _name = right._name;
   _mnemonic = right._mnemonic;
   _value = right._value;
   _type = right._type;

   return *this;
}

bool
sc_Subfield::operator==(const sc_Subfield &right) const
{
   return (_mnemonic == right._mnemonic) &&
          (_name     == right._name) &&
          (_type     == right._type) &&
          (_value    == right._value);
}

bool
sc_Subfield::operator!=(sc_Subfield const& right) const
{
  return ! this->operator==(right);
}

sc_Subfield::SubfieldType
sc_Subfield::getSubfieldType() const
{
   return _type;
}

string const&
sc_Subfield::getName() const
{
   return _name;
}

string const&
sc_Subfield::getMnemonic() const
{
   return _mnemonic;
}

bool
sc_Subfield::getA(string& val) const
{
   if (_type == is_A)
      return _value.getString(val);
   return false;
}

bool
sc_Subfield::getI(long& val) const
{
   if ( _isInt(_type) )
      return _value.getLong(val);
   return false;
}

bool
sc_Subfield::getR(double& val) const
{
   if (_type == is_R)
      return _value.getDouble(val);
   return false;
}

bool
sc_Subfield::getS(double& val) const
{
   if (_type == is_S)
      return _value.getDouble(val);
   return false;
}

bool
sc_Subfield::getC(string& val) const
{
   if (_type == is_C)
      return _value.getString(val);
   return false;
}

bool
sc_Subfield::getBI8(long& val) const
{
   if ( _isInt( _type ) )
      return _value.getLong(val);
   return false;
}

bool
sc_Subfield::getBI16(long& val) const
{
   if ( _isInt( _type ) )
      return _value.getLong(val);
   return false;
}

bool
sc_Subfield::getBI24(long& val) const
{
   if ( _isInt( _type ) )
      return _value.getLong(val);
   return false;
}

bool
sc_Subfield::getBI32(long& val) const
{
   if ( _isInt( _type ) )
      return _value.getLong(val);
   return false;
}

bool
sc_Subfield::getBUI8(unsigned long& val) const
{
   if (_type == is_BUI8)
      return _value.getUnsignedLong(val);
   return false;
}

bool
sc_Subfield::getBUI16(unsigned long& val) const
{
   if (_type == is_BUI16)
      return _value.getUnsignedLong(val);
   return false;
}

bool
sc_Subfield::getBUI24(unsigned long& val) const
{
   if (_type == is_BUI24)
      return _value.getUnsignedLong(val);
   return false;
}

bool
sc_Subfield::getBUI32(unsigned long& val) const
{
   if (_type == is_BUI32)
      return _value.getUnsignedLong(val);
   return false;
}

bool
sc_Subfield::getBFP32(float& val) const
{
// We're doing this because the float->double conversion loses a bit along 
// the way. This way, we just deal with a 32-bit integer, rather than 
// converting to 64-bit floating point.
   bool retval;
   union{
      float foo;
      long  bar;
   } val1;

   if (_type == is_BFP32)
   {
      retval = _value.getLong(val1.bar);
      val = val1.foo;
      return retval;
   }
   return false;
}

bool
sc_Subfield::getBFP64(double& val) const
{
   if (_type == is_BFP64)
      return _value.getDouble(val);
   return false;
}

sc_MultiTypeValue const&
sc_Subfield::getValue() const
{
   return _value;
}

string const&
sc_Subfield::setName(string const& name)
{
   return _name = name;
}

string const&
sc_Subfield::setMnemonic(string const& mnem)
{
   return _mnemonic = mnem;
}

void
sc_Subfield::setA(string const& val)
{
   _type = is_A;
   _value.setString(val);
}

void
sc_Subfield::setI(long val)
{
   _type = is_I;
   _value.setLong(val);
}

void
sc_Subfield::setR(double val)
{
   _type = is_R;
   _value.setDouble(val);
}

void
sc_Subfield::setS(double val)
{
   _type = is_S;
   _value.setDouble(val);
}

void
sc_Subfield::setC(string const& val)
{
   _type = is_C;
   _value.setString(val);
}

void
sc_Subfield::setBI8(long val)
{
   _type = is_BI8;
   _value.setLong(val);
}

void
sc_Subfield::setBI16(long val)
{
   _type = is_BI16;
   _value.setLong(val);
}

void
sc_Subfield::setBI24(long val)
{
   _type = is_BI24;
   _value.setLong(val);
}

void
sc_Subfield::setBI32(long val)
{
   _type = is_BI32;
   _value.setLong(val);
}

void
sc_Subfield::setBUI8(unsigned long val)
{
   _type = is_BUI8;
   _value.setUnsignedLong(val);
}

void
sc_Subfield::setBUI16(unsigned long val)
{
   _type = is_BUI16;
   _value.setUnsignedLong(val);
}

void
sc_Subfield::setBUI24(unsigned long val)
{
   _type = is_BUI24;
   _value.setUnsignedLong(val);
}

void
sc_Subfield::setBUI32(unsigned long val)
{
   _type = is_BUI32;
   _value.setUnsignedLong(val);
}

void
sc_Subfield::setBFP32(float val)
{
   union{
      float foo;
      long  bar;
   } val1;
   _type = is_BFP32;
   val1.foo = val;
   _value.setLong(val1.bar);
}

void
sc_Subfield::setBFP64(double val)
{
   _type = is_BFP64;
   _value.setDouble(val);
}

#if 0
ostream&
operator<<(ostream& s, const sc_Subfield& sf)
{
   // Dump the given sc_Subfield to stream s in a format suitable for 
   // use in debugging.

  string tmp_string;

  s << "\tsubfield " 
    << sf.getMnemonic() << ":" << sf.getName() << " is ";

  switch (sf._rep)
     {
        case sc_Subfield::is_null:
           s << "uninitialized subfield\n";
           return s;
           break;
        case sc_Subfield::is_long:
           s << sf._value.ival;
           break;
        case sc_Subfield::is_ulong:
           s << sf._value.uival;
           break;
        case sc_Subfield::is_double:
           s << sf._value.dval;
           break;
        case sc_Subfield::is_string:
           s << *(sf._value.sval);
           break;
        case sc_Subfield::is_raw:
           if ( rawtohex( *(sf._value.cval), tmp_string ) )
              s << tmp_string;
           else
              s << "cannot convert raw binary to hex, result: " << tmp_string ;
           break;
        default:
           break;
      }
  
   switch (sf._type)
      {
         case sc_Subfield::is_A :
            s << " (A)";
            break;
         case sc_Subfield::is_I :
            s << " (I)";
            break;
         case sc_Subfield::is_R :
            s << " (R)";
            break;
         case sc_Subfield::is_S :
            s << " (S)";
            break;
         case sc_Subfield::is_C :
            s << " (C)";
            break;
         case sc_Subfield::is_B :
            s << " (B)";
            break;
         case sc_Subfield::is_BI8 :
            s << " (BI8)";
            break;
         case sc_Subfield::is_BI16 :
            s << " (BI16)";
            break;
         case sc_Subfield::is_BI24 :
            s << " (BI24)";
            break;
         case sc_Subfield::is_BI32 :
            s << " (BI32)";
            break;
         case sc_Subfield::is_BUI :
            s << " (BUI)";
            break;
         case sc_Subfield::is_BUI8 :
            s << " (BUI8)";
            break;
         case sc_Subfield::is_BUI16 :
            s << " (BUI16)";
            break;
         case sc_Subfield::is_BUI24 :
            s << " (BUI24)";
            break;
         case sc_Subfield::is_BUI32 :
            s << " (BUI32)";
            break;
         case sc_Subfield::is_BFP32 :
            s << " (FP32)";
            break;
         case sc_Subfield::is_BFP64 :
            s << " (FP64)";
            break;
      }
  s << endl;
  return s;
}
#endif
