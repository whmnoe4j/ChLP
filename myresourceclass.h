// myResourceClass.h : header file
//
#define e_puncture1  ".!?:;"		// ���ľ�ĩ���
#define e_puncture2  "')\042"	// �������š������š�˫����
#define c_puncture1  "�� �� �� �� �� ��" // ���ľ�ĩ���
#define c_puncture2  "�� �� ��"  // �����Ҳ���

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
	CString PromptStr;  // ��ʾ��Ϣ
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
{  // ��CObject����
  DECLARE_SERIAL( HZPair )
  //���л�����������
	  char zz[4]; 	// ˫��
    int freq; 	// ���ִ���
	public:
		HZPair() {}  // ȱʡ�Ĺ��캯��
	  HZPair(const char *z2) { strncpy(zz, z2, 4);  freq=1; } // ���캯��
	  void AddFreq( ) { freq++; }	// ���ӳ��ִ���
	  virtual void Serialize(CArchive& ar);  // �������л�����
};

class CSortedPairs: public CObArray
{
public:
  CSortedPairs( ) : CObArray( ) { }    // �����û���Ĺ��캯��
  BOOL Search(const char *zz, int &id); 		// ����˫��
  void Insert(const char *zz);	// ����˫��
};
