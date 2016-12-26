#if !defined(AFX_HZPAIR_H__C976CFEE_7B27_4C99_8E2F_3F64412EAF0A__INCLUDED_)
#define AFX_HZPAIR_H__C976CFEE_7B27_4C99_8E2F_3F64412EAF0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HZPair.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// HZPair document

class HZPair : public CObject
{
protected:
	HZPair();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(HZPair)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(HZPair)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	//}}AFX_VIRTUAL

// Implementation
public:
	HZPair(const char*z2);
	void AddFreq();
	int freq;
	char zz[4];
	virtual ~HZPair();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(HZPair)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HZPAIR_H__C976CFEE_7B27_4C99_8E2F_3F64412EAF0A__INCLUDED_)
