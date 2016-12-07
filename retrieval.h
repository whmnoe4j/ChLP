// retrieval.h
class CHzInfo : public CObject
{
DECLARE_SERIAL(CHzInfo)   // 序列化声明
public:
  int Count;				  // 出现次数
	CWordArray TextID;		  // 地址串
	CHzInfo( ) { Count=0; }
 	void AddTextID(WORD id);		// 往地址串里增加一个地址
	virtual void Serialize(CArchive& ar); // 序列化函数
};


/////////////////////////////////////////////////////////////////////////////
// CTitlesDlg dialog

class CTitlesDlg : public CDialog
{
// Construction
public:
	CTitlesDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTitlesDlg)
	enum { IDD = IDD_TITLES_DLG };
	CListBox	tlist;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTitlesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTitlesDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTextContent();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CHzCountDlg dialog

class CHzCountDlg : public CDialog
{
// Construction
public:
	CHzCountDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHzCountDlg)
	enum { IDD = IDD_HZ_COUNT_DLG };
	CListBox	hzList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHzCountDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHzCountDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
