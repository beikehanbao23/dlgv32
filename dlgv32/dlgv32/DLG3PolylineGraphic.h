// DLG3PolylineGraphic.h - interface for DLG3PolylineGraphic class
//
// Developed by: Mike Childs
//      Started: 10/21/96
//

#ifndef _DLG3POLYLINEGRAPHIC_H_
#define _DLG3POLYLINEGRAPHIC_H_

#include "StdAfx.h"
#include "dlg\DLGLine.hxx"
#include "DLG3OverlayComponent.h"

class DLG3Overlay; // forward declaration for DLG3Overlay class

class DLG3PolylineGraphic : public DLG3OverlayComponent
{
public:
	// Constructors
  DLG3PolylineGraphic( DLG3Overlay* dlg, DLGLine& line );
	DLG3PolylineGraphic( const DLG3PolylineGraphic& polyline ); //copy constructor
	
	// Overridden functions
	void draw( CDC* pDC, CRect* pClipRect = NULL );
	void calculateBoundingRect();
	int pick( const CRect& pickRect, 
            CTypedPtrArray< CPtrArray, OverlayComponent* > *oc_list,
            int start, const CRect& clientRect );
  DLGElement& getDLGElement( void );

protected:
	DLGLine d_line;
};

inline DLGElement& DLG3PolylineGraphic::getDLGElement()
{
  return d_line;
}

#endif