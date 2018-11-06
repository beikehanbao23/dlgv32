// DLG3OverlayComponent.cpp - implementation of DLG3OverlayComponent class
//
// Developed by: Mike Childs
//      Started: 9/29/97

#include "DLG3OverlayComponent.h"
#include "DLG3Overlay.h"
#include "dlg\DLGElement.hxx"
#include "dlg\DLGHeader.hxx"

DLG3OverlayComponent::DLG3OverlayComponent( DLG3Overlay* pOverlay )
: DLGOverlayComponent(pOverlay)
{
}

CString DLG3OverlayComponent::getBrowseText( void ) const
{
	CString text;
  DLGElement& elem = const_cast<DLG3OverlayComponent*>(this)->getDLGElement();
	long elemID = elem.getID();

	// Put the elem type and ID in the string
  const string& strRecType = elem.getRecordType();
	if ( strRecType == "N" )
	{
		text.Format( "N%ld", elemID );
	}
	else if ( strRecType == "A" )
	{
		text.Format( "A%ld", elemID );
	}
  else if ( strRecType == "L" )
  {
    text.Format( "L%ld", elemID );
  }

	// Get the major and minor codes	
	short major, minor;
	vector<DLGAttribute>& attributes = elem.getAttributes();

	// Append all of the major-minor pairs to the string
	for ( vector<DLGAttribute>::iterator i = attributes.begin();
	      i != attributes.end(); i++ )
	{
		CString temp;
		major = i->getMajorCode();
		minor = i->getMinorCode();
		temp.Format( "( %d, %d ) ", major, minor );
		text += temp;
	}

	return text;
}

void DLG3OverlayComponent::showInfoDialog( void )
{
  // Get the DLGElement
  DLGElement& elem = getDLGElement();

	// Initialize the dialog variables
	const DLGHeader& header = ( (DLG3Overlay*)getParentOverlay() )->getHeader();
	DLGCategory dlgcat;
	header.getCategoryInfo( 0, dlgcat );
	d_pickDialog.d_DCUName = header.getDCU_Name().c_str();
	d_pickDialog.d_category = dlgcat.name.c_str();
	d_pickDialog.d_ID.Format( "%d", elem.getID() );
	
	const string& strRecType = elem.getRecordType();
  if ( strRecType == "N" )
	{
		d_pickDialog.d_elemType = "Node";
	}
	else if ( strRecType == "A" )
	{
		d_pickDialog.d_elemType = "Area";
	}
  else if ( strRecType == "L" )
  {
    d_pickDialog.d_elemType = "Line";
  }

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

  // Set the entity label
  d_pickDialog.setEntityDesc("Descriptions not available for DLG-O data sets");

	// Fill the major and minor code lists	
	vector<DLGAttribute>& attributes = elem.getAttributes();
	
	// If the point graphic has no attribute codes put N/A in the boxes
	if ( attributes.begin() == attributes.end() )
	{
    d_pickDialog.addRow( "N/A", "N/A" );
	}
	
	for ( vector<DLGAttribute>::iterator i = attributes.begin();
        i != attributes.end(); i++ )
	{
		// Add major-minor code pair to list
		d_pickDialog.addMajorMinorPair( i->getMajorCode(), i->getMinorCode() );
	}

  // Force the dialog to do dynamic data exchange (DDE)
  d_pickDialog.UpdateData( FALSE );

	// Show the info dialog box
	d_pickDialog.ShowWindow( SW_SHOW );
}
