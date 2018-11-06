#ifndef _SDTS_UTILS_H_
#define _SDTS_UTILS_H_

#include "sdtsxx/container/sc_Record.h"
#include "sdtsxx/container/sc_Field.h"
#include "sdtsxx/container/sc_Subfield.h"

// Several useful utility functions for use with the SDTS layer classes.

class SDTS_Utils
{
   // This class is not meant to be instantiated. It just serves as a namespace
   // for the utility functions.

   public:

      static
      bool getFieldByMnem(sc_Record& rec,
                          const char* strMnem,
                          sc_Record::const_iterator& thefield);
         // Searches 'rec' for the first field with a mnemonic matching 'strMnem'.
         // If found, sets 'thefield' to point it and returns true. Returns false
         // if not found.

      static
      bool getSubfieldByMnem(sc_Field const& field,
                             const char* strMnem,
                             sc_Field::const_iterator& thesubf);
         // Searches 'field' for the first subfield with a mnemonic matching 'strMnem'.
         // If found, sets 'thesubf' to point to it and returns true. Returns false
         // if not found.

      static
      bool getSubfieldByName(sc_Field const& field,
                             const char* strName,
                             sc_Field::const_iterator& thesubf);
         // Searches 'field' for the first subfield with a name matching 'strName'.
         // If found, sets 'thesubf' to point to it and returns true. Returns false
         // if not found.
};


#endif

