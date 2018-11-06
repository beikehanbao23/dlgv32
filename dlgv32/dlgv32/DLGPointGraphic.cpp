// DLGPointGraphic.cpp - implementation of DLGPointGraphic class
//
// Developed by: Mike Childs
//      Started: 8/30/97

#include "CoordinateTransforms.h"
#include "DLGOverlay.h"
#include "DLGPointGraphic.h"

// Constructors
DLGPointGraphic::DLGPointGraphic( DLGOverlay* dlg, SHAPE shape )
: DLGOverlayComponent(dlg), d_shape(shape)
{
}

void
DLGPointGraphic::calculateBoundingRect()
{
	double tmpx, tmpy;
	double shapeSizeGndRefSys = 
    CoordinateTransforms::LPtoGndRefSys( d_shapeSize );

	// Get the global coordinates of the point
    getPoint(tmpx, tmpy);
    getParentOverlay()->projectNativeToGlobal( tmpx, tmpy );

	d_boundingRect.setPoints( tmpx - shapeSizeGndRefSys, 
                            tmpy - shapeSizeGndRefSys,
		                        tmpx + shapeSizeGndRefSys,
                            tmpy + shapeSizeGndRefSys );
	d_boundingRect.inflateRect(CoordinateTransforms::LPtoGndRefSys(getPenWidth()));
}

// This function draws the PointGraphic object.  If the object isn't
// currently highlighted, the pen currently selected into the DC is
// used for the drawing
void DLGPointGraphic::draw(CDC* pDC, CRect* pClipRect)
{
	// Convert the bounding rectangle to logical coordinates from GndRefSys
	CRect logicalBoundingRect = 
    CoordinateTransforms::GndRefSystoLP( d_boundingRect );
  logicalBoundingRect.InflateRect( 1, 1 );

	// Don't draw the point graphic if it's not in the clipping region
	CRect tempRect;	
	if ( ! tempRect.IntersectRect( pClipRect, &logicalBoundingRect ) )
  {
		return;
  }

	// Get the coordinates of the center of the PointGraphic
	double tmpx, tmpy;
	getPoint(tmpx, tmpy);
	
	// Convert the point from native to logical coordinates
  if ( !getParentOverlay()->projectNativeToGlobal( tmpx, tmpy ) )
  {
    return;
  }
	CoordinateTransforms::GndRefSystoLP(tmpx, tmpy);

	CPen *pOldPen, *pNewPen;
	int   oldROP2;
	if ( d_highlighted )
	{
		// Draw using the NOT mode
		oldROP2 = pDC->SetROP2( R2_NOT );

		// Create a new pen
		pNewPen = new CPen();
		COLORREF penColor = PALETTERGB( 0, 0, 0 );
		if ( !pNewPen->CreatePen( PS_SOLID, getPenWidth(), penColor ) )
		{
			AfxMessageBox( "System resources low, unable to create pen" );
			delete pNewPen;
			return; // return if pen is not successfully created
		}
		
		// Select the new pen into the device context
		pOldPen = pDC->SelectObject( pNewPen );
	}

	// If printing, convert the shape size to hundreths of an inch,
	// otherwise leave it in pixels
	int dx, dy;
	if ( pDC->IsPrinting() )
	{
		dx = d_shapeSize * pDC->GetDeviceCaps( LOGPIXELSX ) / 75;
		dy = d_shapeSize * pDC->GetDeviceCaps( LOGPIXELSY ) / 75;
	}
	else
	{
		dx = dy = d_shapeSize;
	}

	// Draw the point with the specified shape
	switch ( d_shape )
	{
		case circle:
		{
			// Draw two unfilled arcs to form the circle
			pDC->Arc( tmpx - dx, tmpy - dy,
                tmpx + dx, tmpy + dy,
					      tmpx,      tmpy + dy,
					      tmpx,      tmpy - dy );
			pDC->Arc( tmpx - dx, tmpy - dy,
				        tmpx + dx, tmpy + dy,
					      tmpx,      tmpy - dy,
					      tmpx,      tmpy + dy );
			break;
		}
		case square:
		{
			// Draw four lines to make a square
			CPoint pt_arr[5];
			pt_arr[0] = CPoint( tmpx - dx, tmpy - dy );
			pt_arr[1] = CPoint( tmpx - dx, tmpy + dy );
			pt_arr[2] = CPoint( tmpx + dx, tmpy + dy );
			pt_arr[3] = CPoint( tmpx + dx, tmpy - dy );
			pt_arr[4] = CPoint( tmpx - dx, tmpy - dy );
			pDC->Polyline(pt_arr, 5);
			break;
		}
		case triangle:
		{
			// draw three lines to make a triangle
			CPoint pt_arr[4];
			pt_arr[0] = CPoint( tmpx - dx, tmpy - dy );
			pt_arr[1] = CPoint( tmpx,      tmpy + dy );
			pt_arr[2] = CPoint( tmpx + dx, tmpy - dy );
			pt_arr[3] = CPoint( tmpx - dx, tmpy - dy);
			pDC->Polyline(pt_arr, 4);
			break;
		}
    case diamond:
    {
      CPoint pt_arr[5];
			pt_arr[0] = CPoint( tmpx     , tmpy - dy );
			pt_arr[1] = CPoint( tmpx - dx, tmpy      );
			pt_arr[2] = CPoint( tmpx     , tmpy + dy );
			pt_arr[3] = CPoint( tmpx + dx, tmpy      );
			pt_arr[4] = CPoint( tmpx     , tmpy - dy );
			pDC->Polyline(pt_arr, 5);
			break;
    }
		default:
		{
			// don't draw
			break;
		}
	}

	if ( highlighted() )
	{
		// Restore the device context to its previous state
		pDC->SelectObject( pOldPen );
		pDC->SetROP2( oldROP2 );

		// Reclaim memory used by the highlight pen
		delete pNewPen;
	}

	return;
}


int 
DLGPointGraphic::pick( const CRect& pickRect, 
                       CTypedPtrArray< CPtrArray, OverlayComponent* > *oc_list,
                       int start, const CRect& clientRect )
{
	// Recalculate bounding rectangle in case it the shape size
	// changed due to a zoom
	calculateBoundingRect();

	// Call the base class' implementation
	return OverlayComponent::pick( pickRect, oc_list, start, clientRect );
}
