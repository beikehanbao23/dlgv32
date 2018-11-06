// OverlayComponent.h - header file for OverlayComponent class
//
// Developed by: Mike Childs
//      Started: 12/4/96
//

#ifndef _OVERLAYCOMPONENT_H_
#define _OVERLAYCOMPONENT_H_

#include "StdAfx.h"
#include "GraphicsObject.h"
#include "PickDialog.h"

class GeographicOverlay;	// forward declaration of GeographicOverlay class

class OverlayComponent : public GraphicsObject
{
public:
	// Constructors
	OverlayComponent( GeographicOverlay* parent );

	// Polymorphic class-specific functions
	virtual void showInfoDialog();
	virtual CString getBrowseText() const;
	
	// pick is a virtual function which selects objects within the pick
	// rectangle passed into the function and stores pointers to those objects
	// inside the specified CTypedPtrArray.  The function returns the number 
	// of objects that it added to the list
	virtual int pick( const CRect& pickRect,
                    CTypedPtrArray< CPtrArray, OverlayComponent* > *oc_list,
			              int start, const CRect& clientRect );

	// Non-polymorphic class-specific functions
	void highlight( BOOL flag );
	BOOL highlighted();
	UINT getPenWidth();
	static void showEmptyInfoDialog();
	static void closeInfoDialog();

protected:
	static CPickDialog  d_pickDialog;
	BOOL                d_highlighted;
	GeographicOverlay*  d_parentOverlay;
};

inline void
OverlayComponent::highlight( BOOL flag = TRUE )
{
	d_highlighted = flag;

	// Recalculate bounding rectangle
	calculateBoundingRect();
}

inline BOOL
OverlayComponent::highlighted()
{
	return d_highlighted;
}

inline UINT
OverlayComponent::getPenWidth()
{
	return 1;	// default returns 1
}

inline CString
OverlayComponent::getBrowseText() const
{
	return "NONE";
}

#endif