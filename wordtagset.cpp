// WordTagSet.cpp : implementation file
//

#include "stdafx.h"
#include "�ִ������Զ�����.h"
#include "WordTagSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWordTagSet

IMPLEMENT_DYNAMIC(CWordTagSet, CDaoRecordset)

CWordTagSet::CWordTagSet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CWordTagSet)
	m_pos = _T("");
	m_pfreq = 0;
	m_word = _T("");
	mp_wid = 0;
	mw_wid = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenSnapshot;
	m_WordParam="";		// �����������ֵ
	m_TagParam="";		// �����Ա�ǲ�����ֵ
	m_nParams=2;			// ��������Ϊ2
}


CString CWordTagSet::GetDefaultDBName()
{
	return _T("myDict.mdb");
}

CString CWordTagSet::GetDefaultSQL()
{
	return _T("[poss],[words]");
}

void CWordTagSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CWordTagSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[pos]"), m_pos);
	DFX_Long(pFX, _T("[pfreq]"), m_pfreq);
	DFX_Text(pFX, _T("[word]"), m_word);
	DFX_Long(pFX, _T("[poss].[wid]"), mp_wid);
	DFX_Long(pFX, _T("[words].[wid]"), mw_wid);
	//}}AFX_FIELD_MAP
	pFX->SetFieldType(CDaoFieldExchange::param); 
	DFX_Text(pFX, "wordParam", m_WordParam);
	DFX_Text(pFX, "tagParam", m_TagParam);
}

int CWordTagSet::GetFreq(CString w, CString t)
{
	m_WordParam=w;  m_TagParam=t;		// ����������������ֵ
	m_strFilter="words.wid=poss.wid AND word =wordParam AND pos=tagParam";
	// ����ɸѡ����
	Requery( );		// ���²�ѯ
	if(GetRecordCount( )==0) return -1;	// û���ҵ�
	else return m_pfreq;	// ���ظôʸñ�ǵĳ��ִ���
}

int CWordTagSet::GetFreqs(CString w, CObArray& a)
{ // �ڶ���������һ����̬���飬��Ų�ѯ���ı�Ǽ�����ִ�����Ϊ���
  m_WordParam=w;	// ֻ��һ������������ֵ
	m_strFilter="words.wid=poss.wid AND word=wordParam";
	// �����µ�ɸѡ����
	Requery( );	// ���²�ѯ
	if(GetRecordCount( )==0) return 0; // û���ҵ��ôʵ��κα��
  for(int i=0; i<a.GetSize( ); i++) if(a[i]) delete a[i]; 
	a.RemoveAll( );  i=0; 		// ���������ԭ������
	CTagFreq *pt;
	while(!IsEOF( )) {	// ��¼û��ȡ��ʱ
		pt=new CTagFreq(m_pos, m_pfreq);	// ȡһ����¼�������ֶ�
		a.Add(pt);  i++;	// �ŵ�������ȥ
		MoveNext( );		// ������һ����¼
	}
	return i;	// һ��ȡ��i����¼
}

/////////////////////////////////////////////////////////////////////////////
// CWordTagSet diagnostics

#ifdef _DEBUG
void CWordTagSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CWordTagSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG

////////////
CMyDictionary::CMyDictionary( )
{
  pDatabase=new CDaoDatabase;
  pDatabase->Open("mydict.mdb"); // �����ݿ�
	  // �����ݿ��ļ�����Ϊ����
  pWordsDef=new CDaoTableDef(pDatabase);
  pWordsDef->Open("words"); // �򿪴ʱ�ṹ���ôʱ�����Ϊ����
  pWords=new CDaoRecordset(pDatabase);  
  pWords->Open(pWordsDef); // �򿪴ʱ��¼�����ôʱ�ṹָ����Ϊ����
  
  pTagsDef=new CDaoTableDef(pDatabase);
  pTagsDef->Open("poss");  // �򿪴��Ա�ṹ���ô��Ա�����Ϊ����
  pTags=new CDaoRecordset(pDatabase);
  pTags->Open(pTagsDef);  // �򿪴��Ա��¼�����ô��Ա�ṹָ����Ϊ����

	pNamesDef=new CDaoTableDef(pDatabase);
  pNamesDef->Open("chineseNames");  // ��������ṹ��������������Ϊ����
  pNames=new CDaoRecordset(pDatabase);
  pNames->Open(pNamesDef);  // ���������¼������������ṹָ����Ϊ����
}

CMyDictionary::~CMyDictionary( )
{
  if(pWords) { pWords->Close( ); delete pWords; } // �رմʱ��¼��
  if(pTags) { pTags->Close( ); delete pTags; }  // �رմ��Ա��¼��
	if(pNames) { pNames->Close( ); delete pNames; }  // �ر��������¼��

  if(pWordsDef) { pWordsDef->Close( ); delete pWordsDef; } // �رմʱ�ṹ
  if(pTagsDef) { pTagsDef->Close( ); delete pTagsDef; } // �رմ��Ա�ṹ
	if(pNamesDef) { pNamesDef->Close( ); delete pNamesDef; } // �ر�������ṹ

  if(pDatabase) { pDatabase->Close( ); delete pDatabase; } // �ر����ݿ�
}

long CMyDictionary::GetWordID(CString w)
{
  COleVariant kw(w, VT_BSTRT), kwi;
  pWords->SetCurrentIndex("word"); // ��ȷ���������ǵ���Seek( )��ǰ��
  if(pWords->Seek("=", &kw)) {  // ����ҵ���
    kwi=pWords->GetFieldValue("wid"); // ȡwid�ֶε�ֵ
 		return kwi.lVal; // ����һ��������
  }
  else return -1;  // û�ҵ�
}

long CMyDictionary::GetFreq(CString w)
{
  COleVariant kw(w, VT_BSTRT),  kf;
  pWords->SetCurrentIndex("word");
  if(pWords->Seek("=", &kw)) {
		kf=pWords->GetFieldValue("wfreq"); // ȡwfreq�ֶε�ֵ
		return kf.lVal;
  }
  else return -1;  // û�ҵ�
}

long CMyDictionary::GetFreq(CString w, CObArray& a)
{
  long i;	for(i=0; i<a.GetSize( ); i++) delete a[i];
  a.RemoveAll( );  // ����������е�ԭ������
  i=GetWordID(w); // ȡ�ʵĴ���
  if(i==-1) return 0; // ���û�ҵ��ôʣ����鳤��Ϊ0
  pTags->SetCurrentIndex("wid"); // Ϊ���Ա���������
  CTagFreq *p;		COleVariant kwi(i,VT_I4), kt, kf; 
  if(!pTags->Seek("=", &kwi)) return 0;  // ���û�ҵ��ôʴ��ţ����鳤��Ϊ0
  while(!pTags->IsEOF( )) { // �ҵ��ˣ��ӵ�ǰ��¼��ʼ
    kwi=pTags->GetFieldValue("wid");  // ȡ�������
		if(kwi.lVal!=i) break;	// ���������ű��ˣ�����ֹ
    kt=pTags->GetFieldValue("pos"); // ȡ���Ա��
    kf=pTags->GetFieldValue("pfreq"); // ȡ��ǵĳ��ִ���
    p=new CTagFreq((LPCSTR)(kt.bstrVal), kf.lVal); // ����һ��Ԫ��
    a.Add(p);  // �嵽������ȥ
    pTags->MoveNext( );  // ������һ����¼
  } 
  return a.GetSize( ); // �������鳤��
}

double CMyDictionary::GetFee(CString name, BOOL full)
{ 
	if(full) { // �������ķ���
	  COleVariant kw1(name.Left(2), VT_BSTRT),  
		  kw2(name.Mid(2), VT_BSTRT), kf;
	  pNames->SetCurrentIndex("name");
		if(pNames->Seek("=", &kw1, &kw2)) {
			kf=pNames->GetFieldValue("fee");
			return kf.dblVal;  // �ҵ���
		}
		else return 20.0;  // û�ҵ�
	}
	else {  // �������ķ���
		COleVariant kw(name, VT_BSTRT), kf;
		pNames->SetCurrentIndex("gname");
    if(pNames->Seek("=", &kw)) {
		  kf=pNames->GetFieldValue("fee"); 
			return kf.dblVal;  // �ҵ���
		}
		else return 20.0;  // û�ҵ�
	}
}

long CMyDictionary::Insert(CString w, long freq)
{
  if(w.GetLength( )>10) return -1;  // �������̫���������ֶο�ȣ���ʧ��
  COleVariant kw(w, VT_BSTRT), kf;
  pWords->SetCurrentIndex("word"); // ��������
  if(pWords->Seek("=", &kw)) {  // ����ҵ���
		kf=pWords->GetFieldValue("wfreq"); // ȡ��wfreq�ֶε�ֵ
		kf.lVal+=freq;	// ���ӳ��ִ�����ע���������ĳ�����ֵ
		pWords->Edit( );		// ׼���޸��ֶε�ֵ
		pWords->SetFieldValue("wfreq", kf);	// �޸��ֶε�ֵ
		pWords->Update( );	    // ���¼�¼
		kf=pWords->GetFieldValue("wid");  // ȡ�������
		return kf.lVal;  // ���ش������
	}
  else {	// ����
		long recn=pWords->GetRecordCount( );  // �����м�¼����
		pWords->AddNew( );	// ����һ�հ׼�¼
		pWords->SetFieldValue("word", kw);	// ����word�ֶε�ֵ
		kf=freq;	// ���freq�ǲ�������
		pWords->SetFieldValue("wfreq", kf);	// ����freq�ֶε�ֵ
		kf=recn;
		pWords->SetFieldValue("wid", kf);	// ����wid�ֶε�ֵ
		pWords->Update( );		// ��������
		return recn; // ���ش������
  }
}

long CMyDictionary::Insert(CString w, CString t, long freq)
{
  if(w.GetLength( )>10 || t.GetLength( )>4) return -1;
  // ����̫�������ߴ��Ա��̫�����򲻲���
	long i=Insert(w);  // �Ȳ������,�õ��������

  COleVariant kt(t, VT_BSTRT), kwi(i, VT_I4), kf;
  pTags->SetCurrentIndex("widTag");  // ��������
  if(pTags->Seek("=", &kwi, &kt)) {  // ����ҵ���
		kf=pTags->GetFieldValue("pfreq"); // ȡ��pfreq�ֶε�ֵ
		kf.lVal+=freq;	// ����Ƶ�ȣ�ע���������ĳ�����ֵ
		pTags->Edit( );		// ׼���޸��ֶε�ֵ
		pTags->SetFieldValue("pfreq", kf);	// �޸��ֶε�ֵ
		pTags->Update( );	
		kf=pTags->GetFieldValue("pid"); // ȡ�ôʡ��ñ�Ǵ���
		return kf.lVal;  // ���ظôʡ��ñ�Ǵ���
	}
  else {	// ����
		long recn=pTags->GetRecordCount( );  // �����м�¼����
		pTags->AddNew( );	// ����һ�հ׼�¼
		pTags->SetFieldValue("pos", kt);	// ����pos�ֶε�ֵ
		kf=freq;	// ���freq�ǲ�������
		pTags->SetFieldValue("pfreq", kf);	// ����pfreq�ֶε�ֵ
		pTags->SetFieldValue("wid", kwi);	// ����wid�ֶε�ֵ
		kf=recn;
		pTags->SetFieldValue("pid", kf);  // ����pid�ֶε�ֵ
		pTags->Update( );		// ��������
		return recn; // ���ظôʡ��ñ�ǵĴ���
  }
}

BOOL CMyDictionary::Insert(CString sName, CString gName, double f)
{		// ����һ����������
	pNames->SetCurrentIndex("name");
	COleVariant kw1(sName, VT_BSTRT), kw2(gName, VT_BSTRT);
	if(pNames->Seek("=", &kw1, &kw2)) return FALSE;
	// �������Ѿ��ڱ��У����ز���
	pNames->AddNew( ); 
	COleVariant kf(f);
	pNames->SetFieldValue("sname", kw1);
	pNames->SetFieldValue("gname", kw2);
	pNames->SetFieldValue("fee", kf);
	pNames->Update( ); // ���������ӵ���������ȥ
	return TRUE;
}
