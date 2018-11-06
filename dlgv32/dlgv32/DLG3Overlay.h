// DLG3Overlay.h - header file for DLG3Overlay class
//
// Developed by: Mike Childs
//      Started: 8/29/97
//

#ifndef _DLG3OVERLAY_H_
#define _DLG3OVERLAY_H_

#include "DLGOverlay.h"
#include "dlg\DLGHeader.hxx"

// Forward declarations
class DLGLine;
class DLGOPropertySheet;

class DLG3Overlay : public DLGOverlay
{
public:
  // Constructors / Destructors
  DLG3Overlay( CString& filename );
	~DLG3Overlay();

  // Overridden functions
  CString getDescription() const;
	BOOL load();
	void showPropertiesDialog();
	void calculateBoundingRect();

  // Function specific to DLG3Overlay
  const DLGHeader& getHeader() const;

protected:
  // Helper functions
  static bool isDegenerate( DLGLine& line );
  bool setupProjection();

  // Data members
  DLGHeader          d_header;
  DLGOPropertySheet* d_pPropertySheet;
};

inline const DLGHeader&
DLG3Overlay::getHeader() const
{
	return d_header;
}

#endif