// DLGOverlayComponent.cpp - implementation file for DLGOverlayComponent class
//
// Developed By: Mike Childs
//      Started: 1/23/97
//


//#include <iostream>

#include "DLGOverlayComponent.h"
#include "DLGOverlay.h"
#include <iostream>
#ifdef _WIN32
	using namespace std;
#endif



// Constructors
DLGOverlayComponent::DLGOverlayComponent( DLGOverlay* pDLG )
: OverlayComponent(pDLG), d_shapeSize(4)
{
}

UINT
DLGOverlayComponent::getPenWidth()
{
	if ( highlighted() )
	{
		return ( 4 * getParentOverlay()->getPenWidth() );
	}
	else
	{
		return getParentOverlay()->getPenWidth();
	}
}

