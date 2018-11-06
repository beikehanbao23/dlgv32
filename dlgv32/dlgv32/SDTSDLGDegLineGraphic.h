// SDTSDLGDegLineGraphic.h - interface for SDTSDLGDegLineGraphic class
//
// Developed by: Mike Childs
//      Started: 9/5/97

#ifndef _SDTSDLGDEGLINEGRAPHIC_H_
#define _SDTSDLGDEGLINEGRPAHIC_H_

#include "SDTSDLGPointGraphic.h"

class SDTSDLGDegLineGraphic : public SDTSDLGPointGraphic
{
public:
	// Constructors
	SDTSDLGDegLineGraphic( SDTSDLGOverlay* pOverlay, sc_Record& rec );
};

#endif