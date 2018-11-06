// DLGOverlay.h - header file for DLGOverlay class
//
// Developed by: Mike Childs
//      Started: 10/21/96
//

#ifndef _DLGOVERLAY_H_
#define _DLGOVERLAY_H_

#include "StdAfx.h"
#include "GeographicOverlay.h"
#include "DLGPointGraphic.h"

class DLGOverlay : public GeographicOverlay
{
public:
	// Overridden functions
	DLGOverlay( CString& filename );
	~DLGOverlay();
	void draw( CDC* pDC, CRect* pClipRect = NULL );
	int  pick( const CRect& pickRect, 
             CTypedPtrArray< CPtrArray, OverlayComponent* > *list,
			       int start, const CRect& clientRect, int maxToPick = -1 );
  bool getBrowseText( const CRect& pickRect, const CRect& clientRect,
                      CString& strBrowse ) const;
	void calculateBoundingRect();
  BOOL showOptionsDialog( CDlgv32Doc* pDoc = NULL );
  void handleProjectionChanged();

	// functions specific to DLGOverlay
	COLORREF getColor() const;
	void setColor( COLORREF& color );
	UINT getPenWidth() const;
	void setPenWidth( UINT width );
	SHAPE getNodeShape() const;
	void setNodeShape( SHAPE nodeShape );
	SHAPE getAreaShape() const;
	void setAreaShape( SHAPE areaShape );
	BOOL getHideNodes() const;
	void setHideNodes( BOOL hide = TRUE );
	BOOL getHideAreas() const;
	void setHideAreas( BOOL hide = TRUE );
	BOOL getHideLines() const;
	void setHideLines( BOOL hide = TRUE );

	// Static non-polymorphic public member functions
	static BOOL getHideAllNodes();
	static void setHideAllNodes( BOOL hide = TRUE );
	static BOOL getHideAllAreas();
	static void setHideAllAreas( BOOL hide = TRUE );
	static BOOL getHideAllLines();
	static void setHideAllLines( BOOL hide = TRUE );

protected:
	COLORREF  d_color;
	SHAPE     d_areaShape;
	SHAPE     d_nodeShape;
	UINT      d_penWidth;
	BOOL      d_hideAreas;
	BOOL	  d_hideNodes;
	BOOL	  d_hideLines;
	vector<DLGOverlayComponent*> d_pLines;
	vector<DLGPointGraphic*>     d_pNodes;
	vector<DLGPointGraphic*>     d_pAreas;

	// Static protected data members
	static BOOL d_hideAllAreas;
	static BOOL d_hideAllNodes;
	static BOOL d_hideAllLines;

  // Helper functions
  COLORREF getDefaultColor( CString strTheme ) const;
};

inline COLORREF
DLGOverlay::getColor() const
{
	return d_color;
}

inline void
DLGOverlay::setColor( COLORREF& color )
{
	d_color = color;
}


inline UINT
DLGOverlay::getPenWidth() const
{
	return d_penWidth;
}

inline void
DLGOverlay::setPenWidth( UINT width )
{
	d_penWidth = width;
}

inline SHAPE
DLGOverlay::getNodeShape() const
{
	return d_nodeShape;
}

inline SHAPE
DLGOverlay::getAreaShape() const
{
	return d_areaShape;
}

inline BOOL
DLGOverlay::getHideNodes() const
{
	return d_hideNodes;
}

inline void
DLGOverlay::setHideNodes( BOOL hide )
{
	d_hideNodes = hide;
}

inline BOOL
DLGOverlay::getHideAreas() const
{
	return d_hideAreas;
}

inline void
DLGOverlay::setHideAreas( BOOL hide )
{
	d_hideAreas = hide;
}

inline BOOL
DLGOverlay::getHideLines() const
{
	return d_hideLines;
}

inline void
DLGOverlay::setHideLines( BOOL hide )
{
	d_hideLines = hide;
}

inline BOOL
DLGOverlay::getHideAllNodes()
{
	return d_hideAllNodes;
}

inline void
DLGOverlay::setHideAllNodes( BOOL hide )
{
	d_hideAllNodes = hide;
}

inline BOOL
DLGOverlay::getHideAllAreas()
{
	return d_hideAllAreas;
}

inline void
DLGOverlay::setHideAllAreas( BOOL hide )
{
	d_hideAllAreas = hide;
}

inline BOOL
DLGOverlay::getHideAllLines()
{
	return d_hideAllLines;
}

inline void
DLGOverlay::setHideAllLines( BOOL hide )
{
	d_hideAllLines = hide;
}

inline void
DLGOverlay::handleProjectionChanged()
{
  // Call the base class version
  GeographicOverlay::handleProjectionChanged();

  calculateBoundingRect();
}

#endif
