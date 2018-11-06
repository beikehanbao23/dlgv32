//	MC_SBAR.CPP - Scot Wingo for VC++ Masterclass
//	
//	I've got WROX in my head!!
//	
//	


#include "stdafx.h"
#include <afxcmn.h>

#include "MC_SBAR.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MCStatusBar

MCStatusBar::MCStatusBar()
{
  m_pProgressCtrl = NULL; //Create on an 'as-needed' basis...
}

MCStatusBar::~MCStatusBar()
{
  if (m_pProgressCtrl != NULL)
  {
	  delete m_pProgressCtrl;
	  m_pProgressCtrl = NULL;
  }
}

BOOL MCStatusBar::StartProgress(int nLower, int nUpper, CString strCaption)
{
  //Hey the user needs a progress bar - create him!
  if (m_pProgressCtrl == NULL)
    m_pProgressCtrl = new CProgressCtrl;	
    
  ASSERT(m_pProgressCtrl != NULL);
    
  SetWindowText(strCaption);
	UpdateWindow(); //force update...

  CDC* pDC = GetDC();
  CSize sizeCaption = pDC->GetTextExtent(strCaption);

	// Get the rectangle for the left pane of the status bar
  CRect rectSB;
  GetItemRect( 0, &rectSB);
    
  CRect rectProgress;
  rectProgress.left = sizeCaption.cx;
  rectProgress.right = rectSB.Width() * 0.95; // 95% across left pane
  rectProgress.top = 0.1 * rectSB.Height();   // start 10% down
  rectProgress.bottom = rectSB.Height();      // end at bottom
    
  // Create the control
  BOOL bResult = m_pProgressCtrl->Create(WS_BORDER, rectProgress, this, 1);
  ASSERT(bResult == TRUE);

  m_pProgressCtrl->SetRange(nLower, nUpper);
  m_pProgressCtrl->ShowWindow(SW_SHOW);
    
  return bResult;
}

int MCStatusBar::SetProgressPos(int nPos)
{
  ASSERT(m_pProgressCtrl != NULL);
  //ASSERT-> Did you call StartProgress first!?
  return m_pProgressCtrl->SetPos(nPos);    
}

int MCStatusBar::StepIt()
{
  ASSERT(m_pProgressCtrl != NULL);
  //    ASSERT-> Did you call StartProgress first?!
  return m_pProgressCtrl->StepIt();
}

int MCStatusBar::SetStep(int nPos)
{
  ASSERT(m_pProgressCtrl != NULL);
  //ASSERT->Did you call StartProgress First?
  return m_pProgressCtrl->SetStep(nPos);
}

void MCStatusBar::StopProgress()
{
  ASSERT(m_pProgressCtrl != NULL);
  //ASSERT->Did you call StartProgress first?

  //Don't delete this guy - we've alreay incurred
  //the expense of displaying it, why do it again?
  //If the user's used it once, likely to do so again..
    
  //Cache that puppy and reset to the CProgressCtrl defaults
  //for next time.

  m_pProgressCtrl->ShowWindow(SW_HIDE);

  // Refresh the status bar
  SetWindowText(NULL);
  UpdateWindow(); //force update
    
  //Nuke its window
  m_pProgressCtrl->DestroyWindow();
}

BEGIN_MESSAGE_MAP(MCStatusBar, CStatusBar)

END_MESSAGE_MAP()

/////////////////////////Debug stuff ////////////////////////////
#ifdef _DEBUG
void MCStatusBar::Dump(CDumpContext& dc) const
{
  CStatusBar::Dump(dc);

  if (m_pProgressCtrl != NULL)
  {
  	dc << "\nMCStatusBar has a progress control--->\n";
	  dc << m_pProgressCtrl;
  }
  else
  	dc << "\nMCStatusBar does not have a progress control\n";
}

void MCStatusBar::AssertValid()	const
{
  CStatusBar::AssertValid();
  if (m_pProgressCtrl != NULL)
  	ASSERT_VALID(m_pProgressCtrl);
}

#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// MCStatusBar message handlers
