// SDTSDLGPolylineGraphic.h - interface for SDTSDLGPolylineGraphic class
//
// Developed by: Mike Childs
//      Started: 9/2/97

#ifndef _SDTSDLGPOLYLINEGRAPHIC_H_
#define _SDTSDLGPOLYLINEGRAPHIC_H_

#include "StdAfx.h"
#include <vector>
#include "DLGOverlayComponent.h"

// SDTS includes
#include "SDTS_SpatialAddr.h"
#include "sdtsxx/builder/sb_ForeignID.hxx"

// Forward declarations
class SDTSDLGOverlay;
class sc_Record;

class SDTSDLGPolylineGraphic : public DLGOverlayComponent
{
    public:
        // Constructors
        SDTSDLGPolylineGraphic( SDTSDLGOverlay* pOverlay, sc_Record& rec );
        
        // Destructor
        ~SDTSDLGPolylineGraphic();
	    
	    // Overridden functions
	    void draw( CDC* pDC, CRect* pClipRect = NULL );
	    void calculateBoundingRect();
	    void showInfoDialog();
	    int pick( const CRect& pickRect, 
			      CTypedPtrArray< CPtrArray, OverlayComponent* > *oc_list,
			      int start, const CRect& clientRect );
	    CString getBrowseText() const;

    protected:
        // Member data
        long                     d_recordID;
        vector<sb_ForeignID>     d_attrIDs;
        vector<SDTS_SpatialAddr> d_spatialAddrs;
};

#endif