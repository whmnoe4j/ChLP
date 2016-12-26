// ChLPDoc.h : interface of the CChLPDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHLPDOC_H__094B66A5_8600_444D_B936_065E980677E5__INCLUDED_)
#define AFX_CHLPDOC_H__094B66A5_8600_444D_B936_065E980677E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

void hzInFile(CString FileName);

class CChLPDoc : public CDocument
{
protected: // create from serialization only
	CChLPDoc();
	DECLARE_DYNCREATE(CChLPDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChLPDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChLPDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CChLPDoc)
	afx_msg void OnFileAddLineNumber();
	afx_msg void OnFileClass();
	afx_msg void OnFileBinary();
	afx_msg void OnFileCfile();
	afx_msg void OnFileLines();
	afx_msg void OnFileBatch();
	afx_msg void OnStatisticsSingle();
	afx_msg void OnStatisticsDouble();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHLPDOC_H__094B66A5_8600_444D_B936_065E980677E5__INCLUDED_)
