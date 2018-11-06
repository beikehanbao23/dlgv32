// DLGOverlay.cpp - implementation of DLGOverlay class
//
// Developed by: Mike Childs
//      Started: 10/21/96

#include <fstream>

#include "StdAfx.h"
#include "DLGOverlay.h"
#include "CoordinateTransforms.h"
#include "DLGOptionsDialog.h"

// Setup static data members
BOOL DLGOverlay::d_hideAllNodes = FALSE;
BOOL DLGOverlay::d_hideAllAreas = FALSE;
BOOL DLGOverlay::d_hideAllLines = FALSE;

DLGOverlay::DLGOverlay(CString& filename) 
: GeographicOverlay( filename ),
  d_hideAreas(FALSE), d_hideNodes(FALSE), d_hideLines(FALSE),
  d_color(PALETTERGB(255,255,255))
{
	d_areaShape = triangle;		    // Set default area shape to a triangle
	d_nodeShape = square;		      // Set default node shape to a square
	d_penWidth  = 1;			        // Set default pen width to 1 logical units
}

DLGOverlay::~DLGOverlay()
{
  // Reclaim space used by nodes
  for ( vector<DLGPointGraphic*>::iterator i = d_pNodes.begin();
        i != d_pNodes.end(); i++)
	{
    delete (*i);
  }

  // Reclaim space used by areas
  for ( vector<DLGPointGraphic*>::iterator j = d_pAreas.begin();
        j != d_pAreas.end(); j++ )
  {
    delete (*j);
  }

  // Reclaim space used by lines
  for ( vector<DLGOverlayComponent*>::iterator k = d_pLines.begin();
        k != d_pLines.end(); k++ )
  {
    delete (*k);
  }

  // Clear out all vectors
	d_pLines.erase( d_pLines.begin(), d_pLines.end() );
	d_pNodes.erase( d_pNodes.begin(), d_pNodes.end() );
	d_pAreas.erase( d_pAreas.begin(), d_pAreas.end() );
}

void DLGOverlay::draw(CDC* pDC, CRect* pClipRect)
{
	// Do not attempt to draw if the DLG is not loaded or 
	// it is not supposed to be shown or there is no current
	// projection defined
	if ( !d_loaded || !d_show || CoordinateTransforms::getCurrentMapping() == 0 )
	{
		return;
	}

	// Find the total invalid region
	Rectangle2D intersectRect = calculateInvalidRect( pDC, pClipRect );

	// Draw the DLGOverlay if the clipping rectangle isn't empty
	if ( !intersectRect.isEmpty() )
	{
		// If the pen color is the same as the background color,
		// invert the color of the pen
		COLORREF penColor;
		if ( d_color == d_bgColor )
		{
			penColor = ~d_color;

			// Remove leading byte from color
			penColor = penColor & PALETTERGB( 255, 255, 255 );
		}
		else
		{
			penColor = getColor();
		}
			
		// Create pen for drawing
		CPen drawingPen;
		if ( !drawingPen.CreatePen(PS_SOLID, getPenWidth(), penColor ) )
		{
			AfxMessageBox( "System resources low, unable to create pen" );
			pDC->SelectClipRgn( NULL );
			return;	// abort draw if pen is not successfully created
		}

		// Save the state of the DC
		CPen* pOldPen = pDC->SelectObject( &drawingPen );

    // Get a LP version of the intersection rectangle
    CRect invalidRect = CoordinateTransforms::GndRefSystoLP( intersectRect );

		// Draw all of the lines if they aren't hidden
		if ( !( d_hideLines || d_hideAllLines ) )
		{
			for ( vector<DLGOverlayComponent*>::iterator i = d_pLines.begin();
				 i != d_pLines.end(); i++)
			{
				(*i)->draw(pDC, &invalidRect);
			}
		}

		// Draw all of the nodes if they aren't hidden
		if ( !( d_hideNodes || d_hideAllNodes ) )
		{
			for ( vector<DLGPointGraphic*>::iterator j = d_pNodes.begin();
            j != d_pNodes.end(); j++)
			{
				(*j)->draw(pDC, &invalidRect);
			}
		}
		
		// Draw all of the areas if they aren't hidden
		if ( !( d_hideAreas || d_hideAllAreas ) )
		{
			for ( vector<DLGPointGraphic*>::iterator k = d_pAreas.begin();
            k != d_pAreas.end(); k++)
			{
				(*k)->draw(pDC, &invalidRect);
			}
		}

		// Restore DC to its previous state
		pDC->SelectObject( pOldPen );
	}

	// Restore DC to previous state
	pDC->SelectClipRgn( NULL );
}

void DLGOverlay::calculateBoundingRect()
{
	// Make all of the lines recalculate their bounding rectangles
	for ( vector<DLGOverlayComponent*>::iterator i = d_pLines.begin(); 
	      i != d_pLines.end(); i++)
	{
		(*i)->calculateBoundingRect();
	}

	// Make all of the nodes recalculate their bounding rectangles
	for ( vector<DLGPointGraphic*>::iterator j = d_pNodes.begin();
        j != d_pNodes.end(); j++)
	{
		(*j)->calculateBoundingRect();
	}
		
	// Make all of the areas recalculate their bounding rectangles
	for ( vector<DLGPointGraphic*>::iterator k = d_pAreas.begin();
        k != d_pAreas.end(); k++)
	{
		(*k)->calculateBoundingRect();
	}
}

COLORREF DLGOverlay::getDefaultColor( CString strTheme ) const
{
  // Trim all trailing spaces from the theme
  strTheme.TrimRight();

  // Determine a default color to use if there isn't an appropriate
  // one given in the registry
  COLORREF defaultColor;
  if ( 0 == strTheme.CompareNoCase( "BOUN" ) )
  {
    defaultColor = PALETTERGB(0xff,0xff,0xff);
  }
  else if ( 0 == strTheme.CompareNoCase( "HYPS" ) )
  {
    defaultColor = PALETTERGB(0x99,0x8f,0x6a);
  }
  else if ( 0 == strTheme.CompareNoCase( "HYDR" ) )
  {
    defaultColor = PALETTERGB(0,0,0xff);
  }
  else if ( 0 == strTheme.CompareNoCase( "MANM" ) )
  {
    defaultColor = PALETTERGB(0xff,0,0);
  }
  else if ( 0 == strTheme.CompareNoCase( "PIPE" ) )
  {
    defaultColor = PALETTERGB(0x78,0x7d,0x8b);
  }
  else if ( 0 == strTheme.CompareNoCase( "NON-" ) )
  {
    defaultColor = PALETTERGB(0xff,0xff,0);
  }
  else if ( 0 == strTheme.CompareNoCase( "PUBL" ) )
  {
    defaultColor = PALETTERGB(0x9a,0x83,0xa0);
  }
  else if ( 0 == strTheme.CompareNoCase( "ROAD" ) )
  {
    defaultColor = PALETTERGB(0xf1,0x97,0x32);
  }
  else if ( 0 == strTheme.CompareNoCase( "RAIL" ) )
  {
    defaultColor = PALETTERGB(0xff,0,0xff);
  }
  else if ( 0 == strTheme.CompareNoCase( "SURV" ) )
  {
    defaultColor = PALETTERGB(0x1f,0xf4,0xfa);
  }
  else if ( 0 == strTheme.CompareNoCase( "VEG" ) )
  {
    defaultColor = PALETTERGB(0,0xff,0);
  }
  else
  {
    defaultColor = PALETTERGB(0xff,0xff,0xff);
  }

	return AfxGetApp()->GetProfileInt("DLG Colors", strTheme, defaultColor );
}

int DLGOverlay::pick ( const CRect& pickRect,
                       CTypedPtrArray< CPtrArray, OverlayComponent* > *oc_list,
                       int start, const CRect& clientRect, int maxToPick )
{
	int counter = 0;
	
	// Right now I'm assuming that there is only one category per DLG

	// Don't pick from the overlay if it's hidden
	if ( !d_show )
	{
		return counter;
	}

	// Pick from the nodes if they're not hidden
	if ( !( d_hideNodes || d_hideAllNodes ) )
	{
		for ( vector<DLGPointGraphic*>::iterator j = d_pNodes.begin();
          j != d_pNodes.end(); j++)
		{
			counter += (*j)->pick( pickRect, oc_list, start, clientRect );
		}

		// Abort if maxPicked reached
		if ( counter >= maxToPick && maxToPick > 0 )
		{
			return counter;
		}
	}
	
	// Pick from the areas if they're not hidden
	if ( !( d_hideAreas || d_hideAllAreas ) )
	{
		for ( vector<DLGPointGraphic*>::iterator k = d_pAreas.begin();
          k != d_pAreas.end(); k++)
		{
			counter += (*k)->pick( pickRect, oc_list, start, clientRect );
		}

		// Abort if maxPicked reached
		if ( counter >= maxToPick && maxToPick > 0 )
		{
			return counter;
		}
	}

	// Pick from the lines if they're not hidden
	if ( !( d_hideLines || d_hideAllLines ) )
	for ( vector<DLGOverlayComponent*>::iterator i = d_pLines.begin();
        i != d_pLines.end(); i++)
	{
		counter += (*i)->pick( pickRect, oc_list, start, clientRect );

		// Abort if maxPicked reached
		if ( counter >= maxToPick && maxToPick > 0 )
		{
			return counter;
		}
	}

	return counter;
}

bool DLGOverlay::getBrowseText( const CRect& pickRect, const CRect& clientRect,
                                CString& strBrowse ) const
{
  // Abort if the overlay is hidden
  if ( !getShow() )
  {
    return false;
  }

  CTypedPtrArray< CPtrArray, OverlayComponent* > ocList;

  // Get the first overlay component in the area
  if ( 0 < const_cast<DLGOverlay*>(this)->pick( pickRect, &ocList, 0, 
                                                clientRect, 1 ) )
  {
    strBrowse = ocList[0]->getBrowseText();
    strBrowse += " (" + getFilenameWithoutPath() + ")";
    return true;
  }

  return false;
}

void DLGOverlay::setNodeShape( SHAPE nodeShape )
{
	d_nodeShape = nodeShape;

	// Update shapes in nodes
	for ( vector<DLGPointGraphic*>::iterator j = d_pNodes.begin();
        j != d_pNodes.end(); j++)
	{
		(*j)->setShape( nodeShape );
	}
}

void DLGOverlay::setAreaShape( SHAPE areaShape )
{
	d_areaShape = areaShape;

	// Update shapes in nodes
	for ( vector<DLGPointGraphic*>::iterator j = d_pAreas.begin();
 	      j != d_pAreas.end(); j++)
	{
		(*j)->setShape( areaShape );
	}
}

BOOL DLGOverlay::showOptionsDialog( CDlgv32Doc* pDoc )
{
	CDLGOptionsDialog dlg;

	// Initialize dialog data
	dlg.m_nAreaShape = (int)d_areaShape;
	dlg.m_nNodeShape = (int)d_nodeShape;
	dlg.m_colorLine = d_color;
	dlg.d_hideAreas = d_hideAreas;
	dlg.d_hideNodes = d_hideNodes;
	dlg.d_hideLines = d_hideLines;
	dlg.setSlider( 1, 10, d_penWidth );

	// Invoke the dialog box
	if (dlg.DoModal() == IDOK)
	{
		// retrieve the dialog data
		setAreaShape( (SHAPE)dlg.m_nAreaShape );
		setNodeShape( (SHAPE)dlg.m_nNodeShape );
		d_penWidth  = dlg.getSliderPos();
		d_color     = dlg.m_colorLine;
		d_hideNodes = dlg.d_hideNodes;
		d_hideAreas = dlg.d_hideAreas;
		d_hideLines = dlg.d_hideLines;

		// Make sure the color is a palette color
		d_color &= 0x02FFFFFF;

		// return TRUE since the overlay has been modified
		return TRUE;
	}

	return FALSE;
}
