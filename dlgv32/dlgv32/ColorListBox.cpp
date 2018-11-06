// ColorListBox.cpp : implementation file
//

#include "stdafx.h"
#include "ColorListBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ColorListBox

ColorListBox::ColorListBox()
: d_pColors(NULL), d_numColors(0)
{
}

ColorListBox::~ColorListBox()
{
	// Deallocate space for array of colors
	delete[] d_pColors;
}


BEGIN_MESSAGE_MAP(ColorListBox, CListBox)
	//{{AFX_MSG_MAP(ColorListBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ColorListBox message handlers

void ColorListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// Get a DC from the DRAWITEMSTRUCT
	CDC dc;
	dc.Attach( lpDrawItemStruct->hDC );

	// Get the items bounding rectangle
	CRect rect = lpDrawItemStruct->rcItem;

	// Get the index of the item being drawn
	UINT index = lpDrawItemStruct->itemID;

	// Set the text color to the negation of the 

	// Draw the background based on whether the item is selected or not
	COLORREF fillColor = ::GetSysColor( lpDrawItemStruct->itemState & ODS_SELECTED ?
								        COLOR_HIGHLIGHT : COLOR_WINDOW );
	CBrush brush( fillColor );
	dc.FillRect( rect, &brush );

	// Set the text color to the inverse of the fill color
	COLORREF textColor = ~fillColor & 0x00FFFFFF;
	COLORREF oldTextColor = dc.SetTextColor( textColor );

	// Draw a focus rectangle around the item if it has focus
	if ( lpDrawItemStruct->itemState & ODS_FOCUS )
	{
		dc.DrawFocusRect( rect );
	}

	// Draw the item if it's valid
	if ( index != (UINT)-1 )
	{
		// Get the width and height of the item's rectangle
		int width = rect.Width();
		int height = rect.Height();

		// Get the left and top values of the item's rectangle
		int left = rect.TopLeft().x;
		int top  = rect.TopLeft().y;

		// Draw a rectangle with the color currently being drawn
		// in the left 20% of the item's rectangle
		CRect box( left + width * 0.03, top + height * 0.1,
			       left + width * 0.13, top + height * 0.9 );
		CBrush boxBrush( getColor( index ) );
		CBrush* pOldBrush = dc.SelectObject( &boxBrush );
		dc.Rectangle( box );
		dc.SelectObject( pOldBrush );

		// Put the RGB value in the rest of the item's rect
		CString text = getColorString( index );
		CRect strRect( left + width * 0.15, top, 
			           left + width,        top + height );
		int oldBkMode = dc.SetBkMode( TRANSPARENT );
		dc.DrawText( text, strRect, DT_LEFT | DT_VCENTER | DT_NOCLIP );
		dc.SetBkMode( oldBkMode );
	}

	// Restore the dc's text color
	dc.SetTextColor( oldTextColor );
	
	// Detach the handle from dc
	dc.Detach();
}

void ColorListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// Set item height to 16 pixels
	lpMeasureItemStruct->itemHeight = 16;
}

void ColorListBox::setColors( RGBQUAD colors[], UINT numColors )
{
	d_numColors = numColors;
	
	// Allocate and copy the colors array
	delete[] d_pColors;
	d_pColors = new RGBQUAD[numColors];
	for ( int i = 0; i < numColors; i++ )
	{
		d_pColors[i] = colors[i];
	}
}

COLORREF ColorListBox::getColor( UINT numColor )
{
	// Make sure numColor in range
	ASSERT( numColor < d_numColors );
	numColor %= d_numColors;

	RGBQUAD quadColor = d_pColors[numColor];
	return RGB( quadColor.rgbRed, quadColor.rgbGreen, quadColor.rgbBlue );
}

BOOL ColorListBox::PreCreateWindow(CREATESTRUCT& cs) 
{
	if ( !CListBox::PreCreateWindow(cs) )
	{
		return FALSE;
	}

	// Make sure the style doesn't have sorted or variable owner draw
	cs.style &= ~(LBS_OWNERDRAWVARIABLE | LBS_SORT);
	cs.style |= LBS_OWNERDRAWFIXED;
	return TRUE;
}

CString ColorListBox::getColorString( UINT numColor )
{
	// Make sure numColor in range
	ASSERT( numColor < d_numColors );
	numColor %= d_numColors;

	// Get the color
	RGBQUAD quadColor = d_pColors[numColor];

	// Create a string representation of the color
	CString color;
	color.Format( "RGB ( %d, %d, %d )", 
		          quadColor.rgbRed, quadColor.rgbGreen, quadColor.rgbBlue );
	return color;
}

UINT ColorListBox::getNumColors()
{
	return d_numColors;
}
