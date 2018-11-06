// DLG3PointGraphic.h - header file for DLG3PointGraphic class
//
// Developed by: Mike Childs
//      Started: 10/22/96
//

#ifndef _DLG3POINTGRAPHIC_H_
#define _DLG3POINTGRAPHIC_H_

#include "DLGPointGraphic.h"
#include "DLG3OverlayComponent.h"
#include "dlg\DLGPointElement.hxx"

class DLG3Overlay;  //forward declaration of DLG3Overlay class

class DLG3PointGraphic : public DLGPointGraphic,
                         public DLG3OverlayComponent
{
public:
	// Constructors
	DLG3PointGraphic( DLG3Overlay* dlg, DLGPointElement& elem, SHAPE shape );

	// Overridden functions
  void        getPoint( double& x, double& y ) const;
  DLGElement& getDLGElement( void );

protected:
	DLGPointElement d_elem;
};

inline void 
DLG3PointGraphic::getPoint( double& x, double& y ) const
{
  d_elem.getPoint( x, y );
}

inline DLGElement&
DLG3PointGraphic::getDLGElement( void )
{
  return d_elem;
}

#endif
