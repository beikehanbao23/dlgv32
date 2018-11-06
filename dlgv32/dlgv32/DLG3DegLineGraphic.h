// DLG3DegLineGraphic.h - interface for DLG3DegLineGraphic class
//
// Developed by: Mike Childs
//      Started: 9/29/97

#ifndef _DLG3DEGLINEGRAPHIC_H_
#define _DLG3DEGLINEGRAPHIC_H_

#include "DLGPointGraphic.h"
#include "dlg\DLGLine.hxx"
#include "DLG3OverlayComponent.h"

// Forward declarations
class DLG3Overlay;

class DLG3DegLineGraphic : public DLGPointGraphic,
                           public DLG3OverlayComponent
{
public:
  // Constructor
  DLG3DegLineGraphic( DLG3Overlay* pOverlay, DLGLine& line );

  // Overrides
  void        getPoint( double& x, double& y ) const;
  DLGElement& getDLGElement( void );

protected:
  DLGLine d_line;
};


inline void
DLG3DegLineGraphic::getPoint( double& x, double& y ) const
{
  const_cast<DLGLine&>(d_line).getPoints().begin()->getXY( x, y );
}

inline DLGElement&
DLG3DegLineGraphic::getDLGElement( void )
{
  return d_line;
}

#endif