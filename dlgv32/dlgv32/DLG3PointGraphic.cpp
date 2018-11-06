// DLG3PointGraphic.cpp - implementation file for DLG3PointGraphic class
//
// Developed by: Mike Childs
//      Started: 10/22/96
//

#include "DLG3PointGraphic.h"
#include "DLG3Overlay.h"

DLG3PointGraphic::DLG3PointGraphic( DLG3Overlay* dlg, DLGPointElement& elem,
                                    SHAPE shape )
: DLGOverlayComponent(dlg), DLGPointGraphic(dlg, shape), 
  DLG3OverlayComponent(dlg), d_elem(elem)
{
  calculateBoundingRect();
}