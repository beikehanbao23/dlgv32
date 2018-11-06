// DLG3Overlay.cpp - implementation of DLG3Overlay class
//
// Developed by: Mike Childs
//      Started: 8/29/97

#include <fstream>
#include "DLG3Overlay.h"
#include "LoadingDialog.h"
#include "DLG3PolylineGraphic.h"
#include "DLG3PointGraphic.h"
#include "DLG3DegLineGraphic.h"
#include "DLGOPropertySheet.h"

// Projection includes
#include "ProjectionLib/AlbersConicProjection.h"
#include "ProjectionLib/UTMProjection.h"

DLG3Overlay::DLG3Overlay(CString& filename) 
: DLGOverlay( filename ), d_pPropertySheet(NULL)
{
}

DLG3Overlay::~DLG3Overlay()
{
  // Reclaim property sheet
  delete d_pPropertySheet;
}

BOOL DLG3Overlay::load()
{
	ifstream ins;

	// Do not attempt to read in the file if it has no name
	if ( getFilename() == "")
	{
		return FALSE;
	}

	// Open the DLG
	ins.open( getFilename() );

	// Abort load if failed to open stream
	if ( ins.fail() )
	{
		AfxMessageBox( "Error opening file: " + getFilename() + 
                   ", aborting load..." );
		ins.close();
		return FALSE;
	}

	try
	{
		// Read in the header
		ins >> d_header;
	}
	catch ( ... )
	{
		AfxMessageBox( "Exception loading DLG header\nLoad will be aborted" );
		ins.close();
		return FALSE;
	}

  // Initialize the projection from the header
  if ( !setupProjection() )
  {
    AfxMessageBox( "The projection could not be setup\nLoad will abort" );
    ins.close();
    return FALSE;
  }

	// NOTE: I'm assuming that there's only one category per file

	// Get category info from header
	DLGCategory dlgcat;
	d_header.getCategoryInfo( 0, dlgcat );

	// Create and initialize a dialog to display load progress
	CLoadingDialog loadingDialog;
	CString strTitle = "Loading " + getFilenameWithoutPath();
	loadingDialog.SetWindowText( strTitle );
	int size;
	size = dlgcat.numActualNodes + dlgcat.numActualAreas + 4 * dlgcat.numActualLines;
	loadingDialog.d_progressControl.SetRange( 0, size );
	loadingDialog.d_progressControl.SetPos( 0 );
	
	// Reserve space for nodes
	d_pNodes.reserve( dlgcat.numActualNodes );
	
	// Read in all of the nodes
	DLGPointElement pt_elem;
  DLG3PointGraphic* pPointGraphic = NULL;
	for ( int j = 0; j < dlgcat.numActualNodes; j++ )
	{
		ins >> pt_elem;
    pPointGraphic = new DLG3PointGraphic( this, pt_elem, d_nodeShape );
		d_pNodes.push_back( pPointGraphic );
		loadingDialog.d_progressControl.OffsetPos( 1 );
	}

	// Reserve space for areas
	d_pAreas.reserve( dlgcat.numActualAreas );
	
	// Read in all of the areas
	for ( j = 0; j < dlgcat.numActualAreas; j++ )
	{
		ins >> pt_elem;
    pPointGraphic = new DLG3PointGraphic( this, pt_elem, d_areaShape );
		d_pAreas.push_back( pPointGraphic );
		loadingDialog.d_progressControl.OffsetPos( 1 );
	}

	// Reserve space for lines
	d_pLines.reserve( dlgcat.numActualLines );

	// Read in all of the lines
	DLGLine line;
	for ( j = 0; j < dlgcat.numActualLines; j++ )
	{
		ins >> line;
    // Check to see if the line is degenerate
    if ( isDegenerate( line ) )
    {
      d_pLines.push_back( new DLG3DegLineGraphic( this, line ) );
    }
    else
    {
      d_pLines.push_back( new DLG3PolylineGraphic( this, line ) );
    }
		loadingDialog.d_progressControl.OffsetPos( 4 );
	}

	// Close the file stream
	ins.close();
	
	// Set the color to the default for this overlay type
	d_header.getCategoryInfo( 0, dlgcat );
	CString strType( dlgcat.name.c_str() );
	d_color = getDefaultColor( strType.Left(4) );

	d_loaded = TRUE;
	calculateBoundingRect();

  // Handle the change in projecion
  handleProjectionChanged();

	return TRUE;
}

void
DLG3Overlay::calculateBoundingRect()
// This function computes the bounding rectangle for the DLGOverlay using the
// information stored in the Control Points.  This should be a O(1) function.
{
	double min_x, min_y, max_x, max_y;

	// Don't attempt to calculate a bounding rectangle if nothing is loaded
	if ( !d_loaded )
	{
		return;
	}

	DLGControlPoint controlPt;

	for ( int n = 0; n < 4; n++ )
	{
		d_header.getControlPointInfo( n, controlPt );
		
		// If at the first control point, initialize variables
		if ( n == 0 )
		{
			min_x = max_x = controlPt.x;
			min_y = max_y = controlPt.y;
		}
		else
		{
			if ( controlPt.x < min_x )
			{
				min_x = controlPt.x;
			}
			else if ( controlPt.x > max_x )
			{
				max_x = controlPt.x;
			}

			if ( controlPt.y < min_y )
			{
				min_y = controlPt.y;
			}
			else if ( controlPt.y > max_y )
			{
				max_y = controlPt.y;
			}
		}
	}

	d_boundingRect.setPoints( min_x, min_y, max_x, max_y );

  // Expand the bounding rectangle by 1% to account for the pen width
  d_boundingRect.inflateRect( d_boundingRect.width() / 100 );

  // Call the base class implementation
  DLGOverlay::calculateBoundingRect();

  // Check to see if the control points are all zero.  If they are build a
  // bounding rectangle out of all of the components bounding boxes
  if ( min_x == max_x && min_y == max_y )
  {
    double x1, y1, x2, y2;
    for ( vector<DLGOverlayComponent*>::iterator i = d_pLines.begin(); 
	        i != d_pLines.end(); i++)
	  {
      (*i)->getBoundingRect().getPoints( x1, y1, x2, y2 );
            
      min_x = min( min_x, min( x1, x2 ) );
      min_y = min( min_y, min( y1, y2 ) );
      max_x = max( max_x, max( x1, x2 ) );
      max_y = max( max_y, max( y1, y2 ) );
	  }

    d_boundingRect.setPoints( min_x, min_y, max_x, max_y );
	  d_boundingRect.inflateRect(CoordinateTransforms::LPtoGndRefSys(d_penWidth));
  }
}

void DLG3Overlay::showPropertiesDialog()
{
  // Create the dialog if necessary
  if ( NULL == d_pPropertySheet )
  {
    d_pPropertySheet = new DLGOPropertySheet( "DLG-O Metadata", getHeader(),
                                              getNativeProjection() );
    d_pPropertySheet->Create( AfxGetMainWnd() );
  }

  // Show the dialog
  d_pPropertySheet->ShowWindow( SW_SHOWNORMAL );
}

// Determines whether the DLG line is a degenerate line.  A DLG
// line is degenerate if the start and end node are the same and
// there are exactly two points in the line
bool DLG3Overlay::isDegenerate( DLGLine& line )
{
	// Check to make sure the start and end nodes are the same
	if ( line.getEndNodeID() != line.getStartNodeID() )
	{
		return false;
	}

	// Count the number of points
	vector<DLGPoint>& points = line.getPoints();
	long counter = 0;
	for (vector<DLGPoint>::iterator i = points.begin(); i != points.end(); i++)
	{
		counter++;
	}

	// Check that there are exactly two points in the line
	return ( 2 == counter );
}

bool DLG3Overlay::setupProjection()
{
  ASSERT( NULL == d_pProjection );

  const DLGHeader& h = d_header;

  // Get the datum
  DATUM d;
  switch( h.getHorizontalDatum() )
  {
    case 0:
      d = NAD27;
      break;
    case 1:
      d = NAD83;
      break;
    default:
      d = UNKNOWN_DATUM;
      break;
  }

  long zone = h.getGrndRefSysZone();

  // Get the units
  UNIT u;
  switch ( h.getGrndRefSysUnits() )
  {
    case 2:
      u = METERS;
      break;
    default:
      u = UNKNOWN_UNIT;
      break;
  }

  // Create the projection
  switch( static_cast<PROJSYS>( h.getGrndRefSys() ) )
  {
    case UTM:
    {
      d_pProjection = new UTMProjection( zone, d, u );
      break;
    }
    case ALBERS:
    {
      d_pProjection = new AlbersConicProjection( h.getProjectionParameter(2),
                                                 h.getProjectionParameter(3),
                                                 h.getProjectionParameter(0),
                                                 h.getProjectionParameter(1),
                                                 h.getProjectionParameter(4),
                                                 h.getProjectionParameter(5),
                                                 h.getProjectionParameter(6),
                                                 h.getProjectionParameter(7),
                                                 d, u );
      break;
    }
  }

  // Check for errors
  if ( NULL == d_pProjection )
  {
    AfxMessageBox( "Unable to create projection\nLoad will abort" );
    return false;
  }

  // Setup the global projection if one hasn't been setup yet
  if ( NULL == CoordinateTransforms::getProjection() )
  {
    CoordinateTransforms::setProjection( d_pProjection );
  }

  return true;
}

CString DLG3Overlay::getDescription() const
{
  CString strDesc;
  strDesc += "<" + getFilenameWithoutPath() + "> ";
  strDesc += d_header.getDCU_Name().c_str();
  strDesc.TrimRight();
  strDesc += " - ";

  DLGCategory cat;
  d_header.getCategoryInfo( 0, cat );
  strDesc += cat.name.c_str();
  strDesc.TrimRight();

  return strDesc;
}
