// DLG3OverlayComponent.h - interface for DLG3OverlayComponent class
//
// Developed by: Mike Childs
//      Started: 9/29/97

#ifndef _DLG3OVERLAYCOMPONENT_H_
#define _DLG3OVERLAYCOMPONENT_H_

#include "DLGOverlayComponent.h"

// Forward declarations
class DLGElement;
class DLG3Overlay;

class DLG3OverlayComponent : public virtual DLGOverlayComponent
{
public:
  // Default constructor
  DLG3OverlayComponent( DLG3Overlay* pOverlay );

  // Overrides
  void showInfoDialog( void );
  CString getBrowseText( void ) const;

protected:
  // Functions that must be overriden in derived classes
  virtual DLGElement& getDLGElement( void ) = 0;
};

#endif