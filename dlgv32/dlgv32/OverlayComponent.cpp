// OverlayComponent.cpp - implementation of OverlayComponent class
//
// Developed by: Mike Childs
//      Started: 12/4/96
//

#include "OverlayComponent.h"
#include "CoordinateTransforms.h"
#include "GeographicOverlay.h"

// Initialize static variables
CPickDialog OverlayComponent::d_pickDialog;

// Constructors
OverlayComponent::OverlayComponent( GeographicOverlay* parent )
: GraphicsObject(), d_highlighted(FALSE), d_parentOverlay(parent)
{
}

void 
OverlayComponent::showInfoDialog()
{
	// This does nothing in the base class
}

void 
OverlayComponent::closeInfoDialog()
{
	// Hide the window if it's been created
	if ( d_pickDialog.created() )
	{
		d_pickDialog.ShowWindow( SW_HIDE );
	}
}

int
OverlayComponent::pick( const CRect& pickRect, 
                        CTypedPtrArray< CPtrArray, OverlayComponent* > *oc_list,
                        int start, const CRect& clientRect )
{
	CRect logBoundingRect;
	CRect intersection;

	// Convert the bounding rectangle to logical coordinates
	logBoundingRect = CoordinateTransforms::GndRefSystoLP( d_boundingRect );

	// if the pick rectangle intersects the bounding rectangle, add the
	// current object to the pick list
	if ( intersection.IntersectRect( &logBoundingRect, &pickRect ) )
	{
		// Don't pick the overlay if it's not visible
		CRect tempRect;	
		if ( ! tempRect.IntersectRect( &clientRect, &logBoundingRect ) )
		{
			return 0;
		}

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
			if ( ! pClipRgn->RectInRegion( &tempRect ) )
			{
				delete pClipRgn;
				return 0;
			}

			delete pClipRgn;
		}

		oc_list->Add( this );
		return 1;
	}
	else
	{
		return 0;	// The current object wasn't picked
	}
}

void OverlayComponent::showEmptyInfoDialog()
{
	// Set DCU name to inform user that nothing was picked
	d_pickDialog.d_DCUName = "Nothing picked";
	d_pickDialog.d_category = "";
	d_pickDialog.d_ID = "";
	d_pickDialog.d_elemType = "";

	// Create Pick Dialog or just update it if already created
	if ( !d_pickDialog.created() )
	{
		d_pickDialog.Create();
	}
	else
	{
		d_pickDialog.clearColumns();
        d_pickDialog.setEntityDesc( "No entity picked" );
		d_pickDialog.UpdateData( FALSE );
	}

	// The point graphic has no attribute codes, put N/A in the boxes
	d_pickDialog.addRow( "N/A", "N/A" );

	// Show the info dialog box
	d_pickDialog.ShowWindow( SW_SHOW );
}
