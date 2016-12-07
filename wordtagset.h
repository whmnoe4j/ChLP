// WordTagSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWordTagSet DAO recordset
class CTagFreq: public CObject 
{
public:
  CString Tag;  int Freq;  // 词性标记，出现次数
  CTagFreq(LPCSTR t, long f) { Tag=t; Freq=f; } // 构造函数
};

class CWordTagSet : public CDaoRecordset
{
public:
	CWordTagSet(CDaoDatabase* pDatabase = NULL);
	int CWordTagSet::GetFreq(CString w, CString t);
	int CWordTagSet::GetFreqs(CString w, CObArray& a);

	DECLARE_DYNAMIC(CWordTagSet)
	

// Field/Param Data
	//{{AFX_FIELD(CWordTagSet, CDaoRecordset)
	CString	m_pos;
	long	m_pfreq;
	CString	m_word;
	long	mp_wid;
	long	mw_wid;
	//}}AFX_FIELD
  CString m_WordParam;
	CString m_TagParam;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWordTagSet)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

///////////////////
class CMyDictionary
{
	CDaoDatabase *pDatabase; // 数据库类指针
	CDaoRecordset *pWords, *pTags, *pNames;  // 词表和词性表记录集指针
	CDaoTableDef  *pWordsDef, *pTagsDef, *pNamesDef;  // 词表和词性表结构指针
public:
	CMyDictionary( );  // 构造函数，打开数据库、表结构和记录集
	~CMyDictionary( ); // 构析函数，关闭数据库、表结构和记录集，
 	 // 释放各指针申请的内存
	long GetWordID(CString w);  // 查词的代号
	long GetFreq(CString w);  // 查词的出现次数
	long GetFreq(CString w, CString t); // 查某词、某标记的出现次数
	long GetFreq(CString w, CObArray& a); // 查词的各标记及其出现次数
	double GetFee(CString name, BOOL full); // 查（姓氏）人名的费用
	long Insert(CString w, long freq=1);  	// 插入一个词
	long Insert(CString w, CString t, long freq=1); // 插入某词、某标记
	BOOL Insert(CString sName, CString gName, double f); // 插入一个中文姓名
};


