// WordTagSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWordTagSet DAO recordset
class CTagFreq: public CObject 
{
public:
  CString Tag;  int Freq;  // ���Ա�ǣ����ִ���
  CTagFreq(LPCSTR t, long f) { Tag=t; Freq=f; } // ���캯��
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
	CDaoDatabase *pDatabase; // ���ݿ���ָ��
	CDaoRecordset *pWords, *pTags, *pNames;  // �ʱ�ʹ��Ա��¼��ָ��
	CDaoTableDef  *pWordsDef, *pTagsDef, *pNamesDef;  // �ʱ�ʹ��Ա�ṹָ��
public:
	CMyDictionary( );  // ���캯���������ݿ⡢��ṹ�ͼ�¼��
	~CMyDictionary( ); // �����������ر����ݿ⡢��ṹ�ͼ�¼����
 	 // �ͷŸ�ָ��������ڴ�
	long GetWordID(CString w);  // ��ʵĴ���
	long GetFreq(CString w);  // ��ʵĳ��ִ���
	long GetFreq(CString w, CString t); // ��ĳ�ʡ�ĳ��ǵĳ��ִ���
	long GetFreq(CString w, CObArray& a); // ��ʵĸ���Ǽ�����ִ���
	double GetFee(CString name, BOOL full); // �飨���ϣ������ķ���
	long Insert(CString w, long freq=1);  	// ����һ����
	long Insert(CString w, CString t, long freq=1); // ����ĳ�ʡ�ĳ���
	BOOL Insert(CString sName, CString gName, double f); // ����һ����������
};


