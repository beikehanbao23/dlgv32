// DLGOverlayComponent.h - header file for DLGOverlayComponent class
//
// Developed by: Mike Childs
//      Started: 1/23/97
//

#ifndef _DLGOVERLAYCOMPONENT_H_
#define _DLGOVERLAYCOMPONENT_H_

#include "OverlayComponent.h"

class DLGOverlay;	// forward declaration of DLGOverlay class

class DLGOverlayComponent : public OverlayComponent
{
public:
	// Constructors
	DLGOverlayComponent( DLGOverlay* pDLG );

	// DLGOverlayComponent specific functions
	UINT getPenWidth();
	UINT getShapeSize() const;
	void setShapeSize( UINT size );

protected:
	UINT d_shapeSize;
	
	// Helper functions
	DLGOverlay* getParentOverlay() const;
};

inline DLGOverlay*
DLGOverlayComponent::getParentOverlay() const
{
	return (DLGOverlay*)d_parentOverlay;
}

inline UINT
DLGOverlayComponent::getShapeSize() const
{
	return d_shapeSize;
}

inline void
DLGOverlayComponent::setShapeSize(UINT size)
{
	d_shapeSize = size;
	calculateBoundingRect();
}

#endif