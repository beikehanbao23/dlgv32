// SDTSDLGPointGraphic.cpp - implementation of SDTSDLGPointGraphic class
//
// Developed by: Mike Childs
//      Started: 9/4/97

#include "SDTSDLGOverlay.h"
#include "SDTSDLGPointGraphic.h"
#include "SDTS_SpatialAddr.h"
#include "SDTS_Utils.h"

// Constructors
SDTSDLGPointGraphic::SDTSDLGPointGraphic( SDTSDLGOverlay* pOverlay, sc_Record& rec, SHAPE shape )
: DLGOverlayComponent(pOverlay), DLGPointGraphic(pOverlay, shape)
{
    // Make sure we have a Point-Node module
    sc_FieldCntr::const_iterator curfield;
    if (!SDTS_Utils::getFieldByMnem( rec, "PNTS", curfield))
    {
        return;
    }

    // We have a primary field from a  module. Start
    // picking it apart.

    sc_SubfieldCntr::const_iterator cursubfield;

    // MODN
    if ( SDTS_Utils::getSubfieldByMnem( *curfield, "MODN", cursubfield) )
    {
       cursubfield->getA( d_strModuleName );
    }

    // RCID
    if ( SDTS_Utils::getSubfieldByMnem( *curfield, "RCID", cursubfield ) )
    {
       cursubfield->getI( d_recordID );
    }

    // OBRP
    if ( SDTS_Utils::getSubfieldByMnem( *curfield, "OBRP", cursubfield ) )
    {
       cursubfield->getA( d_strObjectRep );
    }

    // Secondary Fields

    // SADR Field ... Not repeating
    for ( curfield = rec.begin(); curfield != rec.end(); curfield++ )
    {
        if (curfield->getMnemonic() == "SADR")
        {
            // Get the spatial address
            SDTS_SpatialAddr spatialAddr( *curfield );

            // Get the coordinates from the spatial address
            spatialAddr.getXY( d_x, d_y );

            // We found the coordinates so we can stop
            break;
        }
    }

    // Attribute ID (ATID)
    if ( SDTS_Utils::getFieldByMnem( rec, "ATID", curfield ) )
    {
        d_attrID = sb_ForeignID( *curfield );
    }

    // Area ID (ARID)
    if ( SDTS_Utils::getFieldByMnem( rec, "ARID", curfield ) )
    {
        d_areaID = sb_ForeignID( *curfield );
    }

    // Convert points using internal reference data
    pOverlay->convertPoint( d_x, d_y );    
}

// Destructor
SDTSDLGPointGraphic::~SDTSDLGPointGraphic( void )
{
}

// Overridden functions
void 
SDTSDLGPointGraphic::showInfoDialog()
{
    // Get the overlay containing this point node
    SDTSDLGOverlay* pParent = dynamic_cast<SDTSDLGOverlay*>( getParentOverlay() );

	if ( NULL != pParent )
    {
        d_pickDialog.d_DCUName = pParent->getMapName();
        d_pickDialog.d_category = pParent->getTheme();
    }

	d_pickDialog.d_ID.Format( "<%s, %ld, %s>", d_strModuleName.c_str(),
                              d_recordID, d_strObjectRep.c_str() );
	
    // Determine the element type and get the attribute label value entries for this
    // point element
    vector<SDTSAtt_LabelValuePair> pairs;
    if ( "NO" == d_strObjectRep )
	{
		d_pickDialog.d_elemType = "SDTS Node";

        // Planar Node records use the Attribute ID field
        pParent->getAttLabelValuePairs( pairs, d_attrID.getModuleName().c_str(), 
                                        d_attrID.getRecordID() );
	}
	else if ( "NA" == d_strObjectRep )
	{
		d_pickDialog.d_elemType = "SDTS Area";

        // Area point records use the Area ID field (polygon stuff)
        pParent->getPolygonAttLabelValuePairs( pairs, d_areaID.getRecordID() );
	}
    else if ( "NE" == d_strObjectRep )
    {
        d_pickDialog.d_elemType = "SDTS Degenerate Line";

        // Entity points use both the attribute ID and the Area ID (polygon) fields
        pParent->getAttLabelValuePairs( pairs, d_attrID.getModuleName().c_str(), 
                                        d_attrID.getRecordID() );
        pParent->getPolygonAttLabelValuePairs( pairs, d_areaID.getRecordID() );        
    }
    else
    {
        d_pickDialog.d_elemType = "SDTS Unknown";
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

    // Set the column titles for SDTS
    d_pickDialog.setColumnTitles( "Label", "Value" );

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
	    
CString 
SDTSDLGPointGraphic::getBrowseText() const
{
    CString strTemp;
	strTemp.Format( "<%s, %ld, %s>", d_strModuleName.c_str(),
                    d_recordID, d_strObjectRep.c_str() );
    return strTemp;
}
