// myResourceClass.h : header file
//
#define e_puncture1  ".!?:;"		// 西文句末点号
#define e_puncture2  "')\042"	// 西文括号、单引号、双引号
#define c_puncture1  "。 ！ ？ ： ； …" // 中文句末点号
#define c_puncture2  "” ’ ）"  // 中文右侧标号

BOOL GetData(const char *Prompt, CString& Data);
BOOL GetData(const char *Prompt, int& Data);
BOOL GetData(const char *Prompt, double& Data);
int ProcessFiles(void (*ProcessAFile)(CString fileName));
int ProcessFiles(char *Ext, char *Name, void (*ProcessAFile)(CString fileName));
int  FindOneHZ (const char *str,  const char *hz);
CString wordType(CString & w);
int GetSentence(CString& s);
CString ChangeExt(CString oldName, CString newExt);

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
	CComboBox	m_NewspaperCtrl;
	CSpinButtonCtrl	m_SpinYear;
	BOOL	m_Sample;
	CString	m_Author;
	int		m_Category;
	CString	m_Newspaper;
	short	m_Year;
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
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CGetDataDlg dialog

class CGetDataDlg : public CDialog
{
	CString PromptStr;  // 提示信息
// Construction
public:
	CGetDataDlg(const char *Prompt, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGetDataDlg)
	enum { IDD = IDD_GET_DATA };
	CString	DataString;
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

///////////////////////
class  HZPair : public CObject  
{  // 从CObject派生
  DECLARE_SERIAL( HZPair )
  //序列化函数声明宏
	  char zz[4]; 	// 双字
    int freq; 	// 出现次数
	public:
		HZPair() {}  // 缺省的构造函数
	  HZPair(const char *z2) { strncpy(zz, z2, 4);  freq=1; } // 构造函数
	  void AddFreq( ) { freq++; }	// 增加出现次数
	  virtual void Serialize(CArchive& ar);  // 重载序列化函数
};

class CSortedPairs: public CObArray
{
public:
  CSortedPairs( ) : CObArray( ) { }    // 仅调用基类的构造函数
  BOOL Search(const char *zz, int &id); 		// 查找双字
  void Insert(const char *zz);	// 插入双字
};
