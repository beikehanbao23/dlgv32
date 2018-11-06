#ifndef INCLUDED_SB_SECURITY_HXX
#define INCLUDED_SB_SECURITY_HXX

// $Id: sb_Security.hxx,v 1.1 1998/09/14 15:04:32 bmaddox Exp bmaddox $
// Note:  This class has been compiled, but has NOT been tested due to
//        the lack of data using the Security module.  

#include <string>

#ifndef INCLUDED_SB_FOREIGNID_HXX
#include "builder/sb_ForeignID.hxx"
#endif

#ifndef INCLUDED_SC_RECORD_H
#include "container/sc_Record.h"
#endif

class sb_Security
{
   public:

      sb_Security();
      sb_Security(sb_Security const& right); // Copy Constructor

      sb_Security const& operator=(sb_Security const& right);

      explicit sb_Security(sc_Record& recprox);
         // recprox must be from a Security module, or this won't work.
         // recprox can't be const because we use its -> operator.

      // Accessors:  function which returns the value of a data member
      // const member functions: may not modify data members.

      string const& getModuleName() const;
      long getRecordID() const;
      string const& getSecurityClass() const;
      string const& getControl() const;
      string const& getReleaseInstruct() const;
      string const& getReviewDate() const;
      string const& getReviewInstruct() const;
      string const& getComment() const;

      sb_ForeignID const& getForeignID() const;
   
   private:

      string d_moduleName;
      long d_recordID;
      string d_securityClass;
      string d_control;
      string d_releaseInstruct;
      string d_reviewDate;
      string d_reviewInstruct;
      string d_comment;
      
      sb_ForeignID d_foreignID; 
};

// Inline methods

inline
string const&
sb_Security::getModuleName() const
{
    return d_moduleName;
}

inline
long
sb_Security::getRecordID() const
{
    return d_recordID;
}

inline
string const&
sb_Security::getSecurityClass() const
{
    return d_securityClass;
}

inline
string const&
sb_Security::getControl() const
{
    return d_control;
}

inline
string const&
sb_Security::getReleaseInstruct() const
{
    return d_releaseInstruct;
}

inline
string const&
sb_Security::getReviewDate() const
{
    return d_reviewDate;
}

inline
string const&
sb_Security::getReviewInstruct() const
{
    return d_reviewInstruct;
}

inline
string const&
sb_Security::getComment() const
{
    return d_comment;
}

inline
sb_ForeignID const&
sb_Security::getForeignID() const
{
    return d_foreignID;
}



#endif // INCLUDED_SB_SECURITY_HXX

   
