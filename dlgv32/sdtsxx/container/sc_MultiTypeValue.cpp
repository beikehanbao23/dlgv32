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

// $Id: sc_MultiTypeValue.cpp,v 1.1 1998/09/14 15:04:38 bmaddox Exp bmaddox $

#ifndef INCLUDED_SCULTITYPEVALUE_HXX
#include "container/sc_MultiTypeValue.h"
#endif




sc_MultiTypeValue::sc_MultiTypeValue()
{
   _type = isLong;
   _val.lval = 0;
}

sc_MultiTypeValue::sc_MultiTypeValue(sc_MultiTypeValue const& right)
{
   operator=(right);
}

sc_MultiTypeValue::~sc_MultiTypeValue()
{
   reset();
}

sc_MultiTypeValue const&
sc_MultiTypeValue::operator=(sc_MultiTypeValue const& right)
{
   if (this == &right)
      return *this;

   reset();
   _type = right._type;
   switch(_type)
      {
         case(isLong):
            _val.lval = right._val.lval;
            break;
         case(isUnsignedLong):
            _val.ulval = right._val.ulval;
            break;
         case(isDouble):
            _val.dval = right._val.dval;
            break;
         case(isString):
            _val.sval = new string(*(right._val.sval));
            break;
      }
   return *this;
}

bool
sc_MultiTypeValue::operator==(sc_MultiTypeValue const& right) const
{
   if (this == &right)
      return true;

   if (_type != right._type)
      return false;

   switch(_type)
      {
         case(isLong):
            return _val.lval == right._val.lval;
         case(isUnsignedLong):
            return _val.ulval == right._val.ulval;
         case(isDouble):
            return _val.dval == right._val.dval;
         case(isString):
            return _val.sval == right._val.sval;
      }

   return false;
}

sc_MultiTypeValue::ValueType
sc_MultiTypeValue::getValueType() const
{
   return _type;
}

bool
sc_MultiTypeValue::getLong(long& val) const
{
   if (_type != isLong)
      return false;

   val = _val.lval;
   return true;
}

bool
sc_MultiTypeValue::getUnsignedLong(unsigned long& val) const
{
   if (_type != isUnsignedLong)
      return false;

   val = _val.ulval;
   return true;
}

bool
sc_MultiTypeValue::getDouble(double& val) const
{
   if (_type != isDouble)
      return false;

   val = _val.dval;
   return true;
}

bool
sc_MultiTypeValue::getString(string& val) const
{
   if (_type != isString)
      return false;

   val = *(_val.sval);
   return true;
}

void
sc_MultiTypeValue::setLong(long val)
{
   if (_type != isLong)
      {
         reset();
         _type = isLong;
      }
   _val.lval = val;
}

void
sc_MultiTypeValue::setUnsignedLong(unsigned long val)
{
   if (_type != isUnsignedLong)
      {
         reset();
         _type = isUnsignedLong;
      }
   _val.ulval = val;
}

void
sc_MultiTypeValue::setDouble(double val)
{
   if (_type != isDouble)
      {
         reset();
         _type = isDouble;
      }
   _val.dval = val;
}

void
sc_MultiTypeValue::setString(string const& val)
{
   if (_type != isString)
      {
         reset();
         _type = isString;
         _val.sval = new string;
      }
   *(_val.sval) = val;
}

void
sc_MultiTypeValue::reset()
{
   // Delete any dynamically allocated value
   switch(_type)
      {
         case isString:
            delete _val.sval;
            break;
      }
   _type = isLong;
   _val.lval = 0;
}
