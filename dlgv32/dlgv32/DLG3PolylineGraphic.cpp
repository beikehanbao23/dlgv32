// DLG3PolylineGraphic.cpp - implementation of DLG3PolylineGraphic class
//
// Developed by: Mike Childs
//      Started: 10/21/96
//

#include "StdAfx.h"
#include "DLG3PolylineGraphic.h"
#include "DLG3Overlay.h"
#include "dlg\DLGPoint.hxx"
#include "CoordinateTransforms.h"
#include "MVC\MVCUtils.h"

DLG3PolylineGraphic::DLG3PolylineGraphic(DLG3Overlay* dlg, DLGLine& line)
: DLGOverlayComponent(dlg), DLG3OverlayComponent(dlg), d_line(line)
{
	calculateBoundingRect();
}

void
DLG3PolylineGraphic::draw(CDC* pDC, CRect* pClipRect)
{
	// Convert the bounding rectangle to logical coordinates from GndRefSys
	CRect logicalBoundingRect = 
    CoordinateTransforms::GndRefSystoLP( d_boundingRect );
  logicalBoundingRect.InflateRect( 1, 1 );

	// Don't draw the line if it's not in the clipping region
	CRect tempRect;	
	if ( ! tempRect.IntersectRect( pClipRect, &logicalBoundingRect ) )
		return;

	// Get the vector containing all of the points on the line
	vector<DLGPoint>& points = d_line.getPoints();

	// Create the highlight pen if highlight is set
	CPen *pOldPen, *pNewPen;
	int  oldROP2;
	if ( d_highlighted )
	{
		// Draw in NOT mode
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
    
  if ( pDC->IsPrinting() )
  {
    // Clip each line segment before drawing if we are printing
    double lastx, lasty, curx, cury;

    // Iterate through all of the points in the line, saving them
		// in an array as we go
		for (vector<DLGPoint>::iterator i = points.begin(); i != points.end();
         i++)
		{
      // Get the coordinates of the current point
			i->getXY(curx, cury);

      // Convert the coordinates to logical coordinates
      if ( !getParentOverlay()->projectNativeToGlobal( curx, cury ) )
      {
        continue;
      }

		  CoordinateTransforms::GndRefSystoLP( curx, cury );

      if ( i != points.begin() )
      {
        // Get temporary copies of the current point so that
        // clipping it doesn't change it
        double tempx = curx;
        double tempy = cury;
          
        // Clip the line endpoints to the clipping rectangle
        if ( clip_line( &lastx, &lasty, &tempx, &tempy, tempRect.left,
                        tempRect.top, tempRect.right, tempRect.bottom ) )
        {
          // Draw the line segment
          pDC->MoveTo( lastx, lasty );
          pDC->LineTo( tempx, tempy );
        }
      }

      lastx = curx;
      lasty = cury;
		}
  }
	else
	{
		double curx, cury;
		CPoint *tmp_pts = new CPoint[points.size()];
		long   counter = 0;

		// Iterate through all of the points in the line, saving them
		// in an array as we go
		for (vector<DLGPoint>::iterator i = points.begin(); i != points.end();
         i++)
		{
			// Get the coordinates of the current point
			i->getXY(curx, cury);

			// Convert the coordinates to logical coordinates
      if ( !getParentOverlay()->projectNativeToGlobal( curx, cury ) )
      {
        delete[] tmp_pts;
        return;
      }

			CoordinateTransforms::GndRefSystoLP( curx, cury );

			// Put the point in array
			tmp_pts[counter].x = curx;
			tmp_pts[counter].y = cury;
			counter++;
		}

		// Draw the line
		pDC->Polyline( tmp_pts, points.size() );

		// Reclaim space used by polyline
		delete[] tmp_pts;

	}

	if ( d_highlighted )
	{
		// Restore the device context to its previous state
		pDC->SelectObject( pOldPen );
		pDC->SetROP2( oldROP2 );

		// Reclaim memory used by the highlight pen
		delete pNewPen;
	}
}

void DLG3PolylineGraphic::calculateBoundingRect()
{
	// Get the vector containing all of the points on the line
	vector<DLGPoint>& points = d_line.getPoints();

	double min_x, min_y, max_x, max_y;

	// Iterate through all of the points in the line, connecting the points
	// as you go
	for (vector<DLGPoint>::iterator i = points.begin(); i != points.end(); i++)
	{
		double tmpx, tmpy;
		tmpx = i->getX();
		tmpy = i->getY();

    // Convert the points to global coordinates
    getParentOverlay()->projectNativeToGlobal( tmpx, tmpy );

		// if it's the first Point in the vector, simply initialize the variables
		if ( i == points.begin() )
		{
			min_x = max_x = tmpx;
			min_y = max_y = tmpy;
		}
		// otherwise check to see if the Point contains a new min or max
		else
		{
			if ( tmpx < min_x )
			{
				min_x = tmpx;
			}
			else if ( tmpx > max_x )
			{
				max_x = tmpx;
			}

      if ( tmpy < min_y )
			{
				min_y = tmpy;
			}
			else if ( tmpy > max_y )
			{
				max_y = tmpy;
			}
		}
	}

	d_boundingRect.setPoints( min_x, min_y, max_x, max_y);

	// Inflate rectangle to account for pen width
	d_boundingRect.inflateRect( CoordinateTransforms::LPtoGndRefSys( getPenWidth() ) );
}

int DLG3PolylineGraphic::pick(const CRect& pickRect, 
                              CTypedPtrArray< CPtrArray, OverlayComponent* > *oc_list,
                              int start, const CRect& clientRect )
{
	CRect logBoundingRect; 
	CRect intersection;

	// Convert the bounding Rectangle to logical coordinates from GndRefSys
	logBoundingRect = CoordinateTransforms::GndRefSystoLP( d_boundingRect );
  logBoundingRect.InflateRect( 1, 1 );

	// if the pick rectangle intersects the bounding rectangle, add the
	// current object to the pick list
	if ( intersection.IntersectRect( &logBoundingRect, &pickRect ) )
	{
		// Don't pick the line if it's not visible
		if ( ! intersection.IntersectRect( &clientRect, &logBoundingRect ) )
		{
			return 0;
		}

		// Create a GndRefSys version of the pick rectangle
		Rectangle2D pickRectGndRefSys;
		double rect_x1, rect_y1, rect_x2, rect_y2;
		pickRectGndRefSys = CoordinateTransforms::LPtoGndRefSys( pickRect );
    pickRectGndRefSys.normalize();
		pickRectGndRefSys.getPoints( rect_x1, rect_y1, rect_x2, rect_y2 );

		// Check to see if the pick rectangle intersects any of
		// the line segments of the line
		vector<DLGPoint>& points = d_line.getPoints();
		CPoint last_point;
		double last_x, last_y;
		for (vector<DLGPoint>::iterator i = points.begin(); i != points.end();
         i++)
		{
			double tmpx, tmpy;
			double LPx, LPy;
	
			// Get the coordinates of the current point
			i->getXY(tmpx, tmpy);

      // Convert the coordinates to the global coordinate system
      getParentOverlay()->projectNativeToGlobal( tmpx, tmpy );

			// Setup the logical coordinate variable
			LPx = tmpx;
			LPy = tmpy;

			// Convert the points from GndRefSys to logical coordinates
			CoordinateTransforms::GndRefSystoLP( LPx, LPy );

			// Check to see if the current segment intersects the pick
			// box and add the Line if it does
			if ( i != points.begin() )
			{
				CRect  segmentBoundingRect;
				segmentBoundingRect = CRect( last_point.x, last_point.y,
					                         LPx, LPy );
				segmentBoundingRect.NormalizeRect();
				
				// Add the line if any segment is picked and visible
				double line_x1, line_y1, line_x2, line_y2;
				line_x1 = last_x;  line_y1 = last_y;
				line_x2 = tmpx;    line_y2 = tmpy;
				if ( clip_line( &line_x1, &line_y1, &line_x2, &line_y2,
                        rect_x1,  rect_y1,  rect_x2,  rect_y2 ) )
				{
					// Add the line if the segment is visible
					if ( intersection.IntersectRect( &clientRect, 
                                           &segmentBoundingRect ) )
					{
						// Get a device context for the view
						POSITION pos = AfxGetApp()->GetFirstDocTemplatePosition();
						CDocTemplate* pTemplate = AfxGetApp()->GetNextDocTemplate( pos );
						pos = pTemplate->GetFirstDocPosition();
						CDocument* pDocument = pTemplate->GetNextDoc( pos );
						pos = pDocument->GetFirstViewPosition();
						CView* pView = pDocument->GetNextView( pos );
						CClientDC dc( pView );

						// Don't pick the component if it's not in the clipping region
						CRgn *pClipRgn = d_parentOverlay->getCRgn( &dc );
						if ( pClipRgn != NULL )
						{
							if ( ! pClipRgn->RectInRegion( &segmentBoundingRect ) )
							{
								delete pClipRgn;
								return 0;
							}

							delete pClipRgn;
						}

						oc_list->Add( this );
						return 1;
					}
				}

			}

			// Update the last point
			last_point.x = LPx;
			last_point.y = LPy;
			last_x       = tmpx;
			last_y       = tmpy;
		}
	}

	return 0;	// The current object wasn't picked
}

