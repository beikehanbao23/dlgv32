
#ifndef _MC_SBAR_H_
#define _MC_SBAR_H_

// MC_SBAR.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MCStatusBar window

class MCStatusBar : public CStatusBar
{
// Construction
public:
	MCStatusBar();

// Attributes
public:

// Operations
public:
  BOOL StartProgress(int nLower, int nUpper, CString strCaption);
  int SetProgressPos(int nPos);
  int StepIt();
  int SetStep(int nPos);
  void StopProgress();

// Overrides -none

// Implementation
public:
	virtual ~MCStatusBar();
#ifdef _DEBUG
    virtual void Dump(CDumpContext& dc) const;
    virtual void AssertValid() const;    
#endif //_DEBUG

protected:
  // Pointer to our progress control - no need for us to do the
  // drawing here.
  CProgressCtrl * m_pProgressCtrl;
    
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif //_MC_SBAR_H_
