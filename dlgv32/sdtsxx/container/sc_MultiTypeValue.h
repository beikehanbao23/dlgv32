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
#ifndef INCLUDED_SCMULTITYPEVALUE_HXX
#define INCLUDED_SCMULTITYPEVALUE_HXX

// $Id: sc_MultiTypeValue.h,v 1.1 1998/09/14 15:04:38 bmaddox Exp bmaddox $



#include <string>



#ifdef WIN32

   using namespace std;

#endif




class sc_MultiTypeValue
{
   // An sc_MultiTypeValue is a container for a single value that may be
   // one of several types.
   //
   // Using one of the 'set' methods sets both the value *and* the type.
   // There is no way to set a value without setting the type. There is 
   // no way to "lock" the type; setting an instance to a new value with
   // a different type will change the type associated with the instance.
   // This models the behavior of a variable whose type has run-time binding.
   // The type of the variable depends on the type of the value assigned to it.
   // 
   // 'get'ting the value of an instance will fail unless the member function
   // corresponding to the current type of the instance is used. In other words,
   // no conversions are performed. If the current type of an instance is 'isLong',
   // the the 'getLong()' member function must be used.
 
   public:

      enum ValueType {isLong, isUnsignedLong, isDouble, isString};
         // The type of the value stored in an sc_MultiTypeValue instance.

      sc_MultiTypeValue();
         // Default Type: isLong
         // Default Value: 0 (zero)

      sc_MultiTypeValue(sc_MultiTypeValue const& right);
      ~sc_MultiTypeValue();
      sc_MultiTypeValue const& operator=(sc_MultiTypeValue const& right);
      bool operator==(sc_MultiTypeValue const& right) const;
      
      // Accessors

      ValueType getValueType() const;
         // Returns the type of the current value.

      // All 'get' member functions return false unless the type specified in
      // the member function name matches the current type.
      bool getLong(long& val) const;
      bool getUnsignedLong(unsigned long& val) const;
      bool getDouble(double& val) const;
      bool getString(string& val) const;

      // Modifiers
      void setLong(long val);
      void setUnsignedLong(unsigned long val);
      void setDouble(double val);
      void setString(string const& val);

   private:

      union Value
      {
         long lval;
         unsigned long ulval;
         double dval;
         string* sval;
      };

      Value _val;
      ValueType _type;

      void reset();
         // Resets Value to a long and sets it to zero.

};

#endif  // INCLUDED_SC_MULTITYPEVALUE_HXX