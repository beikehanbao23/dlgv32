// DLG3DegLineGraphic.cpp - implementation of DLG3DegLineGraphic class
//
// Developed by: Mike Childs
//      Started: 9/29/97

#include "DLG3DegLineGraphic.h"
#include "DLG3Overlay.h"

// Constructor
DLG3DegLineGraphic::DLG3DegLineGraphic( DLG3Overlay* pOverlay, DLGLine& line )
: DLGOverlayComponent(pOverlay), DLGPointGraphic(pOverlay, diamond), 
  DLG3OverlayComponent(pOverlay), d_line(line)
{
}

