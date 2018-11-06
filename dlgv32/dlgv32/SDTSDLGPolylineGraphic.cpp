// SDTSDLGPolylineGraphic.cpp - implementation for SDTSDLGPolylineGraphic class
//
// Developed by: Mike Childs
//      Started: 9/2/97

// Disable warning about long debug symbols
#pragma warning( disable : 4786 )

#include "SDTSDLGPolylineGraphic.h"
#include "SDTSDLGOverlay.h"
#include "SDTS_Utils.h"
#include "mvc/MVCUtils.h"

// Constructors
SDTSDLGPolylineGraphic::SDTSDLGPolylineGraphic( SDTSDLGOverlay* pOverlay, sc_Record& rec )
: DLGOverlayComponent(pOverlay), d_recordID(0)
{
    // Make sure this is a line module
    sc_FieldCntr::const_iterator curfield;
    if ( !SDTS_Utils::getFieldByMnem( rec, "LINE", curfield ) )
    {
        return;
    }

    // Get the RCID subfield
    sc_SubfieldCntr::const_iterator cursubfield;
    if ( SDTS_Utils::getSubfieldByMnem( *curfield, "RCID", cursubfield ) )
    {
        cursubfield->getI( d_recordID );
    }

    // Get the spatial address (SADR) and attribute ID (ATID) subfields
    const sc_FieldCntr& fields = rec;
    for ( curfield = fields.begin(); curfield != fields.end(); curfield++ )
    {
        if ( "SADR" == curfield->getMnemonic() )
        {
            d_spatialAddrs.push_back( SDTS_SpatialAddr( *curfield ) );
        }
        else if ( "ATID" == curfield->getMnemonic() )
        {
            d_attrIDs.push_back( sb_ForeignID( *curfield ) );
        }
    }

    // Convert all the spatial addresses using the overlays IREF paramters
    double x, y;
    for ( vector<SDTS_SpatialAddr>::iterator i = d_spatialAddrs.begin();
          i != d_spatialAddrs.end(); i++ )
    {
        i->getXY( x, y );
        pOverlay->convertPoint( x, y );
        i->setXY( x, y );
    }
}

// Destructor
SDTSDLGPolylineGraphic::~SDTSDLGPolylineGraphic()
{
}
	    
void 
SDTSDLGPolylineGraphic::draw( CDC* pDC, CRect* pClipRect )
{
	// Convert the bounding rectangle to logical coordinates from GndRefSys
	CRect logicalBoundingRect = CoordinateTransforms::GndRefSystoLP( d_boundingRect );
    logicalBoundingRect.InflateRect( 1, 1 );

	// Don't draw the line if it's not in the clipping region
	CRect tempRect;	
	if ( ! tempRect.IntersectRect( pClipRect, &logicalBoundingRect ) )
		return;

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

	// Get the vector containing all of the points on the line
	const vector<SDTS_SpatialAddr>& vecPoints = d_spatialAddrs;

	// Iterate through all of the points in the line, saving them
	// in an array as we go
	double curx, cury;
	CPoint *tmp_pts = new CPoint[vecPoints.size()];
	long   counter = 0;
	for ( vector<SDTS_SpatialAddr>::const_iterator i = vecPoints.begin(); 
          i != vecPoints.end(); i++)
	{
		// Get the coordinates of the current point
		i->getXY( curx, cury );

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
	pDC->Polyline( tmp_pts, vecPoints.size() );

	// Reclaim space used by polyline
	delete[] tmp_pts;

	if ( d_highlighted )
	{
		// Restore the device context to its previous state
		pDC->SelectObject( pOldPen );
		pDC->SetROP2( oldROP2 );

		// Reclaim memory used by the highlight pen
		delete pNewPen;
	}
}

void 
SDTSDLGPolylineGraphic::calculateBoundingRect()
{
	double min_x, min_y, max_x, max_y;

	// Iterate through all of the points in the line, connecting the points
	// as you go
    double tmpx, tmpy;
	for ( vector<SDTS_SpatialAddr>::const_iterator i = d_spatialAddrs.begin(); 
          i != d_spatialAddrs.end(); i++)
	{
        i->getXY( tmpx, tmpy );
        getParentOverlay()->projectNativeToGlobal( tmpx, tmpy );

		// if it's the first Point in the vector, simply initialize the variables
		if ( i == d_spatialAddrs.begin() )
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

void 
SDTSDLGPolylineGraphic::showInfoDialog()
{
    // Get the overlay containing this polyline
    SDTSDLGOverlay* pParent = dynamic_cast<SDTSDLGOverlay*>( getParentOverlay() );

	if ( NULL != pParent )
    {
        d_pickDialog.d_DCUName = pParent->getMapName();
        d_pickDialog.d_category = pParent->getTheme();
        d_pickDialog.d_ID.Format( "<LE%s, %ld>", pParent->getAggregateObjectID(), d_recordID );
    }
	d_pickDialog.d_elemType = "SDTS Line";

    // Create Pick Dialog or just update it if already created
	if ( !d_pickDialog.created() )
	{
		d_pickDialog.Create();
	}
	else
	{
        // Clear the columns
		d_pickDialog.clearColumns();
	}

    // Set the column titles for SDTS
    d_pickDialog.setColumnTitles( "Label", "Value" );

    // Get the attribute IDs
    vector<SDTSAtt_LabelValuePair> pairs;
    for ( vector<sb_ForeignID>::const_iterator i = d_attrIDs.begin();
          i != d_attrIDs.end(); i++ )
    {
        pParent->getAttLabelValuePairs( pairs, i->getModuleName().c_str(), i->getRecordID() );
    }

    // Get the description of the entity
    const string& strEntityDesc = pParent->getEntityDesc( pairs );

    // Set the entity decription
    d_pickDialog.setEntityDesc( strEntityDesc.c_str() );

    // Insert all the attribute label-value pairs
    for ( vector<SDTSAtt_LabelValuePair>::iterator j = pairs.begin(); j != pairs.end(); j++)
    {
        d_pickDialog.addRow( j->getLabel().c_str(), j->getValue().c_str() );
    }

    // Force the dialog to do dynamic data exchange (DDE)
    d_pickDialog.UpdateData( FALSE );

	// Show the info dialog box
	d_pickDialog.ShowWindow( SW_SHOW );
}

int 
SDTSDLGPolylineGraphic::pick( const CRect& pickRect, 
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
		double rect_x1, rect_y1, rect_x2, rect_y2;
		Rectangle2D pickRectGndRefSys = CoordinateTransforms::LPtoGndRefSys( pickRect );
		pickRectGndRefSys.getPoints( rect_x1, rect_y1, rect_x2, rect_y2 );

		// Get rectangle points in lower_left, upper right form
		if ( rect_x1 > rect_x2 )
		{
			double temp = rect_x1;
			rect_x1 = rect_x2;
			rect_x2 = temp;
		}

		if ( rect_y1 > rect_y2 )
		{
			double temp = rect_y1;
			rect_y1 = rect_y2;
			rect_y2 = temp;
		}			

		// Check to see if the pick rectangle intersects any of
		// the line segments of the line
		CPoint last_point;
		double last_x, last_y;
		for ( vector<SDTS_SpatialAddr>::const_iterator i = d_spatialAddrs.begin(); 
              i != d_spatialAddrs.end(); i++)
		{
			double tmpx, tmpy;
			double LPx, LPy;
	
			// Get the coordinates of the current point
			i->getXY(tmpx, tmpy);

            // Convert the point to global coordinates
            getParentOverlay()->projectNativeToGlobal( tmpx, tmpy );

			// Setup the logical coordinate variable
			LPx = tmpx;
			LPy = tmpy;

			// Convert the points from GndRefSys to logical coordinates
			CoordinateTransforms::GndRefSystoLP( LPx, LPy );

			// Check to see if the current segment intersects the pick
			// box and add the Line if it does
			if ( i != d_spatialAddrs.begin() )
			{
				CRect  segmentBoundingRect;
				segmentBoundingRect = CRect( last_point.x, last_point.y,
					                         LPx, LPy );
                segmentBoundingRect.InflateRect( 1, 1 );
				segmentBoundingRect.NormalizeRect();
				
				// Add the line if any segment is picked and visible
				double line_x1, line_y1, line_x2, line_y2;
				line_x1 = last_x;  line_y1 = last_y;
				line_x2 = tmpx;    line_y2 = tmpy;
				if ( clip_line( &line_x1, &line_y1, &line_x2, &line_y2,
					             rect_x1,  rect_y1,  rect_x2,  rect_y2 ) )
				{
					// Add the line if the segment is visible
					if ( intersection.IntersectRect( &clientRect, &segmentBoundingRect ) )
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

CString 
SDTSDLGPolylineGraphic::getBrowseText() const
{
    CString strTemp;
    SDTSDLGOverlay* pParent = dynamic_cast<SDTSDLGOverlay*>( getParentOverlay() );
    if ( NULL != pParent )
    {
        strTemp.Format( "<LE%s, %ld>", pParent->getAggregateObjectID(), d_recordID );
    }
    return strTemp;;
}
