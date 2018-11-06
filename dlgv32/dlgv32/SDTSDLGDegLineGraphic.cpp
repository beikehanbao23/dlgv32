// SDTSDLGDegLineGraphic.cpp - implementation for SDTSDLGDegLineGraphic class
//
// Developed by: Mike Childs
//      Started: 9/5/97

#include "SDTSDLGDegLineGraphic.h"
#include "SDTSDLGOverlay.h"

// Constructors
SDTSDLGDegLineGraphic::SDTSDLGDegLineGraphic( SDTSDLGOverlay* pOverlay, sc_Record& rec )
: DLGOverlayComponent(pOverlay), SDTSDLGPointGraphic(pOverlay, rec, diamond)
{
}
