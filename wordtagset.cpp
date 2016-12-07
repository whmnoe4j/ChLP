// WordTagSet.cpp : implementation file
//

#include "stdafx.h"
#include "现代汉语自动分析.h"
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
	m_WordParam="";		// 给词语参数赋值
	m_TagParam="";		// 给词性标记参数赋值
	m_nParams=2;			// 参数个数为2
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
	m_WordParam=w;  m_TagParam=t;		// 给两个参数变量赋值
	m_strFilter="words.wid=poss.wid AND word =wordParam AND pos=tagParam";
	// 设置筛选条件
	Requery( );		// 重新查询
	if(GetRecordCount( )==0) return -1;	// 没有找到
	else return m_pfreq;	// 返回该词该标记的出现次数
}

int CWordTagSet::GetFreqs(CString w, CObArray& a)
{ // 第二个参数是一个动态数组，存放查询到的标记及其出现次数作为输出
  m_WordParam=w;	// 只给一个参数变量赋值
	m_strFilter="words.wid=poss.wid AND word=wordParam";
	// 设置新的筛选条件
	Requery( );	// 重新查询
	if(GetRecordCount( )==0) return 0; // 没有找到该词的任何标记
  for(int i=0; i<a.GetSize( ); i++) if(a[i]) delete a[i]; 
	a.RemoveAll( );  i=0; 		// 清除数组中原有内容
	CTagFreq *pt;
	while(!IsEOF( )) {	// 记录没有取完时
		pt=new CTagFreq(m_pos, m_pfreq);	// 取一条记录的两个字段
		a.Add(pt);  i++;	// 放到数组里去
		MoveNext( );		// 移向下一条记录
	}
	return i;	// 一共取到i个记录
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
  pDatabase->Open("mydict.mdb"); // 打开数据库
	  // 用数据库文件名作为参数
  pWordsDef=new CDaoTableDef(pDatabase);
  pWordsDef->Open("words"); // 打开词表结构，用词表名作为参数
  pWords=new CDaoRecordset(pDatabase);  
  pWords->Open(pWordsDef); // 打开词表记录集，用词表结构指针作为参数
  
  pTagsDef=new CDaoTableDef(pDatabase);
  pTagsDef->Open("poss");  // 打开词性表结构，用词性表名作为参数
  pTags=new CDaoRecordset(pDatabase);
  pTags->Open(pTagsDef);  // 打开词性表记录集，用词性表结构指针作为参数

	pNamesDef=new CDaoTableDef(pDatabase);
  pNamesDef->Open("chineseNames");  // 打开人名表结构，用人名表名作为参数
  pNames=new CDaoRecordset(pDatabase);
  pNames->Open(pNamesDef);  // 打开人名表记录集，用人名表结构指针作为参数
}

CMyDictionary::~CMyDictionary( )
{
  if(pWords) { pWords->Close( ); delete pWords; } // 关闭词表记录集
  if(pTags) { pTags->Close( ); delete pTags; }  // 关闭词性表记录集
	if(pNames) { pNames->Close( ); delete pNames; }  // 关闭人名表记录集

  if(pWordsDef) { pWordsDef->Close( ); delete pWordsDef; } // 关闭词表结构
  if(pTagsDef) { pTagsDef->Close( ); delete pTagsDef; } // 关闭词性表结构
	if(pNamesDef) { pNamesDef->Close( ); delete pNamesDef; } // 关闭人名表结构

  if(pDatabase) { pDatabase->Close( ); delete pDatabase; } // 关闭数据库
}

long CMyDictionary::GetWordID(CString w)
{
  COleVariant kw(w, VT_BSTRT), kwi;
  pWords->SetCurrentIndex("word"); // 正确设置索引是调用Seek( )的前提
  if(pWords->Seek("=", &kw)) {  // 如果找到了
    kwi=pWords->GetFieldValue("wid"); // 取wid字段的值
 		return kwi.lVal; // 返回一个长整数
  }
  else return -1;  // 没找到
}

long CMyDictionary::GetFreq(CString w)
{
  COleVariant kw(w, VT_BSTRT),  kf;
  pWords->SetCurrentIndex("word");
  if(pWords->Seek("=", &kw)) {
		kf=pWords->GetFieldValue("wfreq"); // 取wfreq字段的值
		return kf.lVal;
  }
  else return -1;  // 没找到
}

long CMyDictionary::GetFreq(CString w, CObArray& a)
{
  long i;	for(i=0; i<a.GetSize( ); i++) delete a[i];
  a.RemoveAll( );  // 先清除数组中的原有内容
  i=GetWordID(w); // 取词的代号
  if(i==-1) return 0; // 如果没找到该词，数组长度为0
  pTags->SetCurrentIndex("wid"); // 为词性表设置索引
  CTagFreq *p;		COleVariant kwi(i,VT_I4), kt, kf; 
  if(!pTags->Seek("=", &kwi)) return 0;  // 如果没找到该词代号，数组长度为0
  while(!pTags->IsEOF( )) { // 找到了，从当前记录开始
    kwi=pTags->GetFieldValue("wid");  // 取词语代号
		if(kwi.lVal!=i) break;	// 如果词语代号变了，则中止
    kt=pTags->GetFieldValue("pos"); // 取词性标记
    kf=pTags->GetFieldValue("pfreq"); // 取标记的出现次数
    p=new CTagFreq((LPCSTR)(kt.bstrVal), kf.lVal); // 生成一个元素
    a.Add(p);  // 插到数组中去
    pTags->MoveNext( );  // 移向下一条记录
  } 
  return a.GetSize( ); // 返回数组长度
}

double CMyDictionary::GetFee(CString name, BOOL full)
{ 
	if(full) { // 查姓名的费用
	  COleVariant kw1(name.Left(2), VT_BSTRT),  
		  kw2(name.Mid(2), VT_BSTRT), kf;
	  pNames->SetCurrentIndex("name");
		if(pNames->Seek("=", &kw1, &kw2)) {
			kf=pNames->GetFieldValue("fee");
			return kf.dblVal;  // 找到了
		}
		else return 20.0;  // 没找到
	}
	else {  // 查人名的费用
		COleVariant kw(name, VT_BSTRT), kf;
		pNames->SetCurrentIndex("gname");
    if(pNames->Seek("=", &kw)) {
		  kf=pNames->GetFieldValue("fee"); 
			return kf.dblVal;  // 找到了
		}
		else return 20.0;  // 没找到
	}
}

long CMyDictionary::Insert(CString w, long freq)
{
  if(w.GetLength( )>10) return -1;  // 如果词语太长，超过字段宽度，则失败
  COleVariant kw(w, VT_BSTRT), kf;
  pWords->SetCurrentIndex("word"); // 设置索引
  if(pWords->Seek("=", &kw)) {  // 如果找到了
		kf=pWords->GetFieldValue("wfreq"); // 取出wfreq字段的值
		kf.lVal+=freq;	// 增加出现次数，注意是用它的长整数值
		pWords->Edit( );		// 准备修改字段的值
		pWords->SetFieldValue("wfreq", kf);	// 修改字段的值
		pWords->Update( );	    // 更新记录
		kf=pWords->GetFieldValue("wid");  // 取词语代号
		return kf.lVal;  // 返回词语代号
	}
  else {	// 否则
		long recn=pWords->GetRecordCount( );  // 查现有记录个数
		pWords->AddNew( );	// 增加一空白记录
		pWords->SetFieldValue("word", kw);	// 设置word字段的值
		kf=freq;	// 这个freq是参数变量
		pWords->SetFieldValue("wfreq", kf);	// 设置freq字段的值
		kf=recn;
		pWords->SetFieldValue("wid", kf);	// 设置wid字段的值
		pWords->Update( );		// 更新数据
		return recn; // 返回词语代号
  }
}

long CMyDictionary::Insert(CString w, CString t, long freq)
{
  if(w.GetLength( )>10 || t.GetLength( )>4) return -1;
  // 词语太长，或者词性标记太长，则不插入
	long i=Insert(w);  // 先插入词语,得到词语代号

  COleVariant kt(t, VT_BSTRT), kwi(i, VT_I4), kf;
  pTags->SetCurrentIndex("widTag");  // 设置索引
  if(pTags->Seek("=", &kwi, &kt)) {  // 如果找到了
		kf=pTags->GetFieldValue("pfreq"); // 取出pfreq字段的值
		kf.lVal+=freq;	// 增加频度，注意是用它的长整数值
		pTags->Edit( );		// 准备修改字段的值
		pTags->SetFieldValue("pfreq", kf);	// 修改字段的值
		pTags->Update( );	
		kf=pTags->GetFieldValue("pid"); // 取该词、该标记代号
		return kf.lVal;  // 返回该词、该标记代号
	}
  else {	// 否则
		long recn=pTags->GetRecordCount( );  // 查现有记录个数
		pTags->AddNew( );	// 增加一空白记录
		pTags->SetFieldValue("pos", kt);	// 设置pos字段的值
		kf=freq;	// 这个freq是参数变量
		pTags->SetFieldValue("pfreq", kf);	// 设置pfreq字段的值
		pTags->SetFieldValue("wid", kwi);	// 设置wid字段的值
		kf=recn;
		pTags->SetFieldValue("pid", kf);  // 设置pid字段的值
		pTags->Update( );		// 更新数据
		return recn; // 返回该词、该标记的代号
  }
}

BOOL CMyDictionary::Insert(CString sName, CString gName, double f)
{		// 插入一个中文姓名
	pNames->SetCurrentIndex("name");
	COleVariant kw1(sName, VT_BSTRT), kw2(gName, VT_BSTRT);
	if(pNames->Seek("=", &kw1, &kw2)) return FALSE;
	// 该姓名已经在表中，不必插入
	pNames->AddNew( ); 
	COleVariant kf(f);
	pNames->SetFieldValue("sname", kw1);
	pNames->SetFieldValue("gname", kw2);
	pNames->SetFieldValue("fee", kf);
	pNames->Update( ); // 将该姓名加到姓名表中去
	return TRUE;
}
