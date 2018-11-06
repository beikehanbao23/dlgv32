#ifndef INCLUDED_DLGELEMENT_HXX
#define INCLUDED_DLGELEMENT_HXX

#ifdef _WIN32
	#include <iostream>
	#include <vector>
	using namespace std;
#else
	#include <iostream.h>
   #include <vector.h>
	#include <string>
#endif

#include "DLGAttribute.hxx"

class DLGElement
{
   public:

      DLGElement(void);
      DLGElement(const DLGElement& element);
      virtual DLGElement& operator=(const DLGElement& element);
      virtual bool operator==(const DLGElement& element);
      virtual ~DLGElement(void);

      // Accessors
      const string& getRecordType(void) const;
      long getID(void) const;
      vector<DLGAttribute>& getAttributes(void);

   protected:

      bool readAttributes(istream& s, long numAttributes);
      bool writeAttributes(ostream& s);

      string _recordType;
      long   _id;
      vector<DLGAttribute> _attrs;

};

// Inline Member Function Definitions

inline vector<DLGAttribute>&
DLGElement::getAttributes(void)
{
   return _attrs;
}

inline
const string&
DLGElement::getRecordType(void) const
{
   return _recordType;
}

inline
long
DLGElement::getID(void) const
{
   return _id;
}


#endif  // INCLUDED_DLGELEMENT_HXX
