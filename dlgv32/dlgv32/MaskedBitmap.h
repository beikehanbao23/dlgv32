// MaskedBitmap.h - header file for CMaskedBitmap class
//
// Developed by: Mike Childs
//

#ifndef _CMASKEDBITMAP_H_
#define _CMASKEDBITMAP_H_

#include "StdAfx.h"

class CMaskedBitmap : public CBitmap
{
public:
  // Construction
  CMaskedBitmap();

  // Destruction
  virtual ~CMaskedBitmap();

  // Drawing function
  virtual void Draw( CDC* pDC, int x, int y );
  virtual void DrawMasked( CDC* pDC, int x, int y );
  virtual void DrawTransparent(CDC* pDC, int x, int y, COLORREF transColor);

  // Mask Functions
  void CreateMask( UINT width, UINT height, UINT widthBytes );
  void TurnPixelOff( UINT x, UINT y );

private:
  void TransparentBlt( HDC hdcDest, int nXDest, int nYDest, int nWidth, 
                       int nHeight, HBITMAP hBitmap, int nXSrc, int nYSrc,
                       COLORREF colorTransparent, HPALETTE hPal,
                       CBitmap* pMask = NULL );

  // Mask bitmap
  BYTE* d_pMaskBits;
  UINT  d_maskWidth;
  UINT  d_maskHeight;
  UINT  d_maskWidthBytes;
};

#endif