#if !defined(AFX_FILEATTRIBUTES_H__3F64D47B_13DB_4EDC_A64C_89493FF3BB9D__INCLUDED_)
#define AFX_FILEATTRIBUTES_H__3F64D47B_13DB_4EDC_A64C_89493FF3BB9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileAttributes.h : header file
//
#define HZ_NUM 6768
#define HZ_ID(c1,c2)	((c1)-176)*94+((c2)-161)
//���㺺���±�ĺ�
void LoadHZFreq();
void StoreHZFreq();
void HZPairInFile(CString FileName);
/////////////////////////////////////////////////////////////////////////////
// CFileAttributes dialog

class CFileAttributes : public CDialog
{
// Construction
public:
	CFileAttributes(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileAttributes)
	enum { IDD = IDD_FILE_ATTRIBUTES };
	CComboBox	m_SourceCtrl;
	CSpinButtonCtrl	m_SpinYear;
	BOOL	m_Sample;
	short	m_Year;
	CString	m_Author;
	int		m_Category;
	CString	m_Source;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileAttributes)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileAttributes)
	virtual BOOL OnInitDialog();
	afx_msg void OnOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGetDataDlg dialog

class CGetDataDlg : public CDialog
{
		CString PromptStr;
// Construction
public:
	CGetDataDlg(char*Prompt,CWnd*pParent=NULL);
	CGetDataDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGetDataDlg)
	enum { IDD = IDD_GET_DATA };
	CString DataString;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetDataDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGetDataDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
	BOOL GetData(const char*Prompt,CString&Data);
	BOOL GetData(const char*Prompt,int&Data);
	BOOL GetData(const char*Prompt,double&Data);
	void CountLinesInAFile(CString fname);
	int ProcessFiles(void(*ProcessAFile)(CString fileName));
	int ProcessFiles(char*Ext,char*Name,void(*ProcessAFile)(CString fileName));
#endif // !defined(AFX_FILEATTRIBUTES_H__3F64D47B_13DB_4EDC_A64C_89493FF3BB9D__INCLUDED_)
