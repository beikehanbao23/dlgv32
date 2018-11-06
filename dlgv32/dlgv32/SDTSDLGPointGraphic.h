// SDTSDLGPointGraphic.h - interface for SDTSDLGPointGraphic class
//
// Developed by: Mike Childs
//      Started: 9/2/97

#ifndef _SDTSDLGPOINTGRAPHIC_H_
#define _SDTSDLGPOINTGRAPHIC_H_

#include "DLGPointGraphic.h"

// SDTS includes
#include "sdtsxx/builder/sb_ForeignID.hxx"

// Forward declarations
class SDTSDLGOverlay;
class sc_Record;

class SDTSDLGPointGraphic : public DLGPointGraphic
{
    public:
	    // Constructors
	    SDTSDLGPointGraphic( SDTSDLGOverlay* pOverlay, sc_Record& rec, SHAPE shape );

        // Destructor
        ~SDTSDLGPointGraphic( void );

	    // Overridden functions
        void getPoint( double& x, double& y ) const;
	    void showInfoDialog();
	    CString getBrowseText() const;

    protected:
        double d_x, d_y;
        string d_strModuleName;
        long   d_recordID;
        string d_strObjectRep;

        sb_ForeignID d_attrID;
        sb_ForeignID d_areaID;
};

inline void 
SDTSDLGPointGraphic::getPoint( double& x, double& y ) const
{
    x = d_x;
    y = d_y;
}

#endif