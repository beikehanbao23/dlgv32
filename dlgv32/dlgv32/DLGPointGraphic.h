// DLGPointGraphic.h - interface for DLGPointGraphic class
//
// Developed by: Mike Childs
//      Started: 8/30/97

#ifndef _DLGPOINTGRAPHIC_H_
#define _DLGPOINTGRAPHIC_H_

#include "DLGOverlayComponent.h"

enum SHAPE {circle, square, triangle, diamond};

class DLGPointGraphic : public virtual DLGOverlayComponent
{
public:
	// Constructors
	DLGPointGraphic( DLGOverlay* dlg, SHAPE shape );

  // Functions that must be overloaded in subclasses
  virtual void getPoint( double& x, double& y ) const = 0;

  // Overridden functions
  void draw( CDC* pDC, CRect* pClipRect );
	int pick( const CRect& pickRect, 
            CTypedPtrArray< CPtrArray, OverlayComponent* > *oc_list,
			      int start, const CRect& clientRect );
	const Rectangle2D& getBoundingRect() const;
	void calculateBoundingRect();

	// DLG3PointGraphic specific functions
	SHAPE getShape( void ) const;
	void setShape( SHAPE shape );

protected:
 	SHAPE d_shape;	
};

inline SHAPE
DLGPointGraphic::getShape( void ) const
{
	return d_shape;
}

inline void
DLGPointGraphic::setShape( SHAPE shape )
{
	d_shape = shape;
}

inline const Rectangle2D&
DLGPointGraphic::getBoundingRect() const
{
	// Recalculate bounding rectangle since it might have changed
	const_cast<DLGPointGraphic*>(this)->calculateBoundingRect();

	// return base class's version
	return DLGOverlayComponent::getBoundingRect();
}

#endif