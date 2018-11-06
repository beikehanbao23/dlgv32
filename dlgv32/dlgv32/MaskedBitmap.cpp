// MaskedBitmap.cpp - implementation of CMaskedBitmap class
//
// Developed by: Mike Childs

#include "MaskedBitmap.h"

// Construction/Destruction
CMaskedBitmap::CMaskedBitmap()
: CBitmap(), d_pMaskBits(NULL)
{
}

CMaskedBitmap::~CMaskedBitmap()
{
    // Free the mask bits
    delete[] d_pMaskBits;
}

// TransparentBlt - Copies a bitmap transparently onto the destination DC
// hdcDest		- Handle to destination device context 
// nXDest		- x-coordinate of destination rectangle's upper-left corner 
// nYDest		- y-coordinate of destination rectangle's upper-left corner 
// nWidth		- Width of destination rectangle 
// nHeight		- height of destination rectangle 
// hBitmap		- Handle of the source bitmap
// nXSrc		- x-coordinate of source rectangle's upper-left corner 
// nYSrc		- y-coordinate of source rectangle's upper-left corner 
// colorTransparent	- The transparent color
// hPal			- Logical palette to be used with bitmap. Can be NULL

void CMaskedBitmap::TransparentBlt( HDC hdcDest, int nXDest, int nYDest,
                                   int nWidth, int nHeight, HBITMAP hBitmap,
                                   int nXSrc, int nYSrc, 
                                   COLORREF colorTransparent, HPALETTE hPal,
                                   CBitmap* pMask )
{
	CDC dc, memDC, maskDC, tempDC;
	dc.Attach( hdcDest );
	maskDC.CreateCompatibleDC(&dc);
	
	// add these to store return of SelectObject() calls
	CBitmap* pOldMemBmp = NULL;
	CBitmap* pOldMaskBmp = NULL;
	HBITMAP hOldTempBmp = NULL;
	
	memDC.CreateCompatibleDC(&dc);
  tempDC.CreateCompatibleDC(&dc);

	CBitmap bmpImage;
	bmpImage.CreateCompatibleBitmap( &dc, nWidth, nHeight );
	pOldMemBmp = memDC.SelectObject( &bmpImage );
	
	// Select and realize the palette
	if( dc.GetDeviceCaps(RASTERCAPS) & RC_PALETTE && hPal )
	{
		::SelectPalette( dc, hPal, FALSE );
		dc.RealizePalette();
		
		::SelectPalette( memDC, hPal, FALSE );
	}
	
	hOldTempBmp = (HBITMAP) ::SelectObject( tempDC.m_hDC, hBitmap );
	
	memDC.BitBlt( 0,0,nWidth, nHeight, &tempDC, nXSrc, nYSrc, SRCCOPY );

	// Create monochrome bitmap for the mask if necessary
  if ( NULL == pMask )
  {
    CBitmap maskBitmap;
	  maskBitmap.CreateBitmap( nWidth, nHeight, 1, 1, NULL );
	  pOldMaskBmp = maskDC.SelectObject( &maskBitmap );
    memDC.SetBkColor( colorTransparent );
	
	  // Create the mask from the memory DC
	  maskDC.BitBlt( 0, 0, nWidth, nHeight, &memDC, 0, 0, SRCCOPY );
  }
  else
  {
    maskDC.SelectObject( pMask );
  }
	
	// Set the background in memDC to black. Using SRCPAINT with black 
	// and any other color results in the other color, thus making 
	// black the transparent color
	memDC.SetBkColor(RGB(0,0,0));
	memDC.SetTextColor(RGB(255,255,255));
	memDC.BitBlt(0, 0, nWidth, nHeight, &maskDC, 0, 0, SRCAND);
	
	// Set the foreground to black. See comment above.
	dc.SetBkColor(RGB(255,255,255));
	dc.SetTextColor(RGB(0,0,0));
	dc.BitBlt(nXDest, nYDest, nWidth, nHeight, &maskDC, 0, 0, SRCAND);
	
	// Combine the foreground with the background
	dc.BitBlt(nXDest, nYDest, nWidth, nHeight, &memDC, 0, 0, SRCPAINT);
	
	if (hOldTempBmp)
		::SelectObject( tempDC.m_hDC, hOldTempBmp);
	if (pOldMaskBmp)
		maskDC.SelectObject( pOldMaskBmp );
	if (pOldMemBmp)
		memDC.SelectObject( pOldMemBmp );
	
	dc.Detach();
}

/////////////////////////////////////////////////////////////////////////
// CMaskedBitmap member functions

void CMaskedBitmap::Draw (CDC* pDC, int x, int y)
{
  BITMAP bm;
  GetObject (sizeof (BITMAP), &bm);
  CSize size (bm.bmWidth, bm.bmHeight);
  pDC->DPtoLP (&size);

  CSize org (0, 0);
  pDC->DPtoLP (&org);

  CDC dcMem;
  dcMem.CreateCompatibleDC(pDC);

  CBitmap* pOldBitmap = dcMem.SelectObject (this);
  dcMem.SetMapMode (pDC->GetMapMode ());

  pDC->BitBlt (x, y, size.cx, size.cy, &dcMem, org.cx, org.cy, SRCCOPY);

  dcMem.SelectObject (pOldBitmap);
}

void CMaskedBitmap::DrawMasked( CDC* pDC, int x, int y )
{    
  if ( NULL == d_pMaskBits )
  {
    Draw( pDC, x, y );
    return;
  }

  // Create a bitmap based on the mask
  CMaskedBitmap maskBitmap;
  maskBitmap.CreateBitmap( d_maskWidth, d_maskHeight, 1, 1, d_pMaskBits );

  // Get the bitmap info
  BITMAP bm;
  GetObject( sizeof(BITMAP), &bm);

  ASSERT( bm.bmWidth == d_maskWidth );
  ASSERT( bm.bmHeight == d_maskHeight );

  // Get the size of the bitmap in logical coordinates
  CSize size( bm.bmWidth, bm.bmHeight );
  pDC->DPtoLP( &size);

  // Get the origin of the bitmap in logical coordinates
  CSize org( 0, 0 );
  pDC->DPtoLP( &org );

  // Draw the bitmap using the mask
  TransparentBlt( pDC->GetSafeHdc(), x, y, size.cx, size.cy,
                  (HBITMAP)(*this), org.cx, org.cy, 0, NULL, &maskBitmap );
}

void CMaskedBitmap::DrawTransparent( CDC* pDC, int x, int y, COLORREF crColor )
{
  // Get the bitmap info
  BITMAP bm;
  GetObject( sizeof(BITMAP), &bm);

  // Get the size of the bitmap in logical coordinates
  CSize size(bm.bmWidth, bm.bmHeight);
  pDC->DPtoLP(&size);

  // Get the origin of the bitmap in logical coordinates
  CSize org(0, 0);
  pDC->DPtoLP(&org);

  // Draw the bitmap transparently
  TransparentBlt( pDC->GetSafeHdc(), x, y, size.cx, size.cy,
                  (HBITMAP)(*this), org.cx, org.cy, crColor, NULL );
}

// Mask functions
void CMaskedBitmap::CreateMask( UINT width, UINT height, UINT widthBytes )
{
  d_maskWidth = width;
  d_maskHeight = height;
  d_maskWidthBytes = widthBytes;

  // Remove any old mask
  delete[] d_pMaskBits;

  // Allocate a new mask
  d_pMaskBits = new BYTE[widthBytes * height];

  // Set all the bits in the mask to 0
  memset( d_pMaskBits, 0, widthBytes * height );
}

void CMaskedBitmap::TurnPixelOff( UINT x, UINT y )
{
  ASSERT( NULL != d_pMaskBits );
  ASSERT( x < d_maskWidth );
  ASSERT( y < d_maskHeight );

	BYTE* pCurrentByte = &d_pMaskBits[ d_maskWidthBytes * y + ( x >> 3 ) ];
  BYTE bitToSet = 7 - ( x % 8 );
  *pCurrentByte |= ( 1 << bitToSet );
}