#ifndef INCLUDED_SB_UTILS_HXX
#define INCLUDED_SB_UTILS_HXX


#ifndef INCLUDED_SC_RECORD_H
#include "container/sc_Record.h"
#endif

#ifndef INCLUDED_SC_FIELD_H
#include "container/sc_Field.h"
#endif

#ifndef INCLUDED_SC_SUBFIELD_H
#include "container/sc_Subfield.h"
#endif

// Several useful utility functions for use with the sb_* layer classes.

class sb_Utils
{
   // This class is not meant to be instantiated. It just serves as a namespace
   // for the utility functions.

   public:

      static
      bool getFieldByMnem(sc_Record& rec,
                          string const& mnemonic,
                          sc_Record::const_iterator& thefield);
         // Searches 'rec' for the first field with a mnemonic matching 'mnemonic'.
         // If found, sets 'thefield' to point it and returns true. Returns false
         // if not found.

      static
      bool getSubfieldByMnem(sc_Field const& field,
                             string const& mnemonic,
                             sc_Field::const_iterator& thesubf);
         // Searches 'field' for the first subfield with a mnemonic matching 'mnemonic'.
         // If found, sets 'thesubf' to point to it and returns true. Returns false
         // if not found.

      static
      bool getSubfieldByName(sc_Field const& field,
                             string const& name,
                             sc_Field::const_iterator& thesubf);
         // Searches 'field' for the first subfield with a name matching 'name'.
         // If found, sets 'thesubf' to point to it and returns true. Returns false
         // if not found.

      static
	  bool getDoubleFromSubfield(sc_SubfieldCntr::const_iterator const& subf,
		     double& dataOut );
	// Tries to convert a subfield into a double.
	// If it succeeds returns True, else False.
	// Place the convert value into the dataTo passed in parameter


   private:
//      SfUtils() {}   // Prevent construction of this class.
// I think the above should be sb_Utils() {}
      sb_Utils() {}
};


#endif  // INCLUDED_SB_UTILS_HXX

