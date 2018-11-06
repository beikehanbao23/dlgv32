
#include <string>

#ifdef _WIN32
   #include <algorithm>
   #include <functional>
   using namespace std;
#else
   #include <algo.h>
   #include <function.h>
#endif

#ifndef INCLUDED_SB_UTILS_HXX
#include "builder/sb_Utils.hxx"
#endif

/*
 * Support Functions for sb_Utils 
 */


// Generic utility things.
//
// XXX You better _believe_ this is temporary.

// This algorithm is used in find_if calls to locate fields
// or subfields that have a given mnemonic.

// Q.v., sc_Record:getRecordID() for an example of its use.

template< class T >
struct equalMnemonic : binary_function<T, const string, bool>
{
  bool operator()( const T& x, const string& y ) const
  { return x.getMnemonic() == y; }

};
// comparison class equalMnemonic

template< class T >
struct equalName : binary_function<T, const string, bool>
{
  bool operator()( const T& x, const string& y ) const
  { return x.getName() == y; }

};
// comparison class equalName

// This algorithm is used in find_if calls to locate modules with a 
// given module type.

template< class T >
struct equalModuleType : binary_function<T, const string, bool>
{
  bool operator()( const T& x, const string& y ) const
  { return x.getModuleType() == y; }

}; 
// comparison class equalModuleType

/*
 * Implimentation of the sb_Utils functions.
 */

bool
sb_Utils::getFieldByMnem(sc_Record& rec,
                       string const& mnemonic,
                       sc_Record::const_iterator& thefield)
{
   list<sc_Field> const& fields = rec; // ->getFields();
   thefield = find_if(fields.begin(),fields.end(),
                      bind2nd(equalMnemonic<sc_Field>(), mnemonic));
   if (thefield != fields.end())
      return true;

   return false;
}

bool
sb_Utils::getSubfieldByMnem(sc_Field const& field,
                           string const& mnemonic,
                           sc_Field::const_iterator& thesubf)
{
   list<sc_Subfield> const& subfields = field; // .getSubfields();
   thesubf = find_if(subfields.begin(),subfields.end(),
                      bind2nd(equalMnemonic<sc_Subfield>(), mnemonic));
   if (thesubf != subfields.end())
      return true;

   return false;
}

bool
sb_Utils::getSubfieldByName(sc_Field const& field,
                           string const& name,
                           sc_Field::const_iterator& thesubf)
{
   list<sc_Subfield> const& subfields = field; // .getSubfields();
   thesubf = find_if(subfields.begin(),subfields.end(),
                      bind2nd(equalName<sc_Subfield>(), name));
   if (thesubf != subfields.end())
      return true;

   return false;
}

// Tries to convert a subfield into a double.
// If it succeeds returns True, else False.
// Place the convert value into the dataTo passed in parameter
bool
sb_Utils::getDoubleFromSubfield(sc_SubfieldCntr::const_iterator const& subf, //sc_Subfield const& subf,
		    double& dataOut )
{

	bool rc;
	unsigned long tempULong;
	long tempLong;
    float tempFloat;
	sc_Subfield::SubfieldType sType = subf->getSubfieldType();

	switch(sType) {

		// Not supported at this time.
		// convert string class to double
		case(sc_Subfield::is_A):
		case(sc_Subfield::is_C):
				return false;
				break;

		// convert long to double
		case(sc_Subfield::is_I):
				rc = subf->getI( tempLong );
				dataOut = double(tempLong);
				break;
		case(sc_Subfield::is_BI8):
				rc = subf->getBI8( tempLong );
				dataOut = double(tempLong);
				break;
		case(sc_Subfield::is_BI16):
				rc = subf->getBI16( tempLong );
				dataOut = double(tempLong);
				break;
		case(sc_Subfield::is_BI24):
				rc = subf->getBI24( tempLong );
				dataOut = double(tempLong);
				break;
		case(sc_Subfield::is_BI32):
				rc = subf->getBI32( tempLong );
				dataOut = double(tempLong);
				break;

		// Convert unsigned long to double
		case(sc_Subfield::is_BUI8):
				rc = subf->getBUI8( tempULong );
				dataOut = double(tempULong );
				break;
		case(sc_Subfield::is_BUI16):
				rc = subf->getBUI16( tempULong );
				dataOut = double(tempULong );
				break;
		case(sc_Subfield::is_BUI24):
				rc = subf->getBUI24( tempULong );
				dataOut = double(tempULong );
				break;
		case(sc_Subfield::is_BUI32):
				rc = subf->getBUI32( tempULong );
				dataOut = double(tempULong );
				break;

		//convert double to double
		case(sc_Subfield::is_R):
				rc = subf->getR( dataOut );
				break;
		case(sc_Subfield::is_S):
				rc = subf->getS( dataOut );
				break;

		// non-implimented return false
		case(sc_Subfield::is_B):
		case(sc_Subfield::is_BUI):
				rc = false;
				break;
		case(sc_Subfield::is_BFP32):
                rc = subf->getBFP32( tempFloat );
                dataOut = static_cast<double>( tempFloat );
                break;
		case(sc_Subfield::is_BFP64):
                rc = subf->getBFP64( dataOut );
                break;
		
		// Shouldn't get here, except in an error situation
		default:
				rc = false;
	}

	return rc;
}
/* Numberic -> optionalSign Digits FrationalPart ExponentPart
 */
/*
 *
 *  <number>    ->  [ <sign> ] <digit> { <digit> } [ <deciaml> ] [ <exponent> ]
 *
 *  <sign>       ->  '+' | '-'
 *
 *  <decimal>   ->  '.' { <digit> }
 *
 *  <exponent>  ->  'E' [ <sign> ] <digit> { <digit> }
 *
 *  <digits>    ->  1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0
 *
 */
/*
bool String2double(sc_SubfieldCntr::const_iterator const& subf, double &dataOut );

inline
bool
String2double( sc_SubfieldCntr::const_iterator const& subf,
		double &dataOut )
{
	sc_Subfield::SubfieldType sType = subf->getSubfieldType();
	string tempString;
	bool rc;
	switch(sType){
		case(sc_Subfield::is_A):
				rc = subf->getA( tempString );
				break;
		case(sc_Subfield::is_C):
				rc = subf->getC( tempString );
				break;
	    	default:
		// Error!
		// Illegal subfield type passed to function.
				return false;
	}
	if ( rc == false ) // get on subfield failed pass it on.
		return false;
	// Verfiy string is only digits,
	// convert
	return true;
}
*/