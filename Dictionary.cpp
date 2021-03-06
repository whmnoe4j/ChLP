// Dictionary.cpp: implementation of the CDictionary class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "chlp.h"
#include "Dictionary.h"
#include "tagfreq.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDictionary::CDictionary()
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
	//CFileDialog inDlg(true);
	//if(inDlg.DoModal()==IDOK)
	//{
		//pDatabase->Open(inDlg.GetFileName());
	//}
}

CDictionary::~CDictionary()
{
	if(pWords){
		pWords->Close();delete pWords;
	}
	if(pTags){
		pTags->Close();delete pTags;
	}
	if(pNames){
		pNames->Close();delete pNames;
	}
	if(pWordsDef){
		pWordsDef->Close();delete pWordsDef;
	}
	if(pTagsDef){
		pTagsDef->Close();delete pTagsDef;
	}
	if(pNamesDef){
		pNamesDef->Close();delete pNamesDef;
	}
	if(pDatabase){
		pDatabase->Close();delete pDatabase;
	}
}

long CDictionary::GetWordID(CString w)
{
	COleVariant kw(w,VT_BSTRT),kwi;
	pWords->SetCurrentIndex("word");
	if(pWords->Seek("=",&kw)){
		kwi=pWords->GetFieldValue("wid");
		return kwi.lVal;
	}
	else return -1;
}

long CDictionary::GetFreq(CString w)
{
	COleVariant kw(w,VT_BSTRT),kf;
	pWords->SetCurrentIndex("word");
	if(pWords->Seek("=",&kw)){
		kf=pWords->GetFieldValue("wfreq");
		return kf.lVal;
	}
	else return -1;
}

long CDictionary::GetFreq(CString w, CString t)
{
	long i;
	i=GetWordID(w);
	if(i==-1)
		return 0;
	pTags->SetCurrentIndex("wid");
	COleVariant kwi(i,VT_I4),kt,kf;
	if(!pTags->Seek("=",&kwi))
		return 0;
	while(!pTags->IsEOF()){
		kwi=pTags->GetFieldValue("wid");
		if(kwi.lVal!=i)
			break;
		kt=pTags->GetFieldValue("pos");
		if(kt.bstrVal==t){
			kf=pTags->GetFieldValue("pfreq");
			break;
		}
		pTags->MoveNext();
	}
	return kf.lVal;
}

long CDictionary::GetFreq(CString w, CObArray &a)
{
	long i;
	for(i=0;i<a.GetSize();i++)
		delete a[i];
	a.RemoveAll();
	i=GetWordID(w);
	if(i==-1)
		return 0;
	pTags->SetCurrentIndex("wid");
	CTagFreq*p;
	COleVariant kwi(i,VT_I4),kt,kf;
	if(!pTags->Seek("=",&kwi))
		return 0;
	while(!pTags->IsEOF()){
		kwi=pTags->GetFieldValue("wid");
		if(kwi.lVal!=i)
			break;
		kt=pTags->GetFieldValue("pos");
		kf=pTags->GetFieldValue("pfreq");
		p=new CTagFreq((LPCSTR)(kt.bstrVal),kf.lVal);
		a.Add(p);
		pTags->MoveNext();
	}
	return a.GetSize();
}

long CDictionary::Insert(CString w, long freq)
{
	if(w.GetLength()>10)
		return -1;
	COleVariant kw(w,VT_BSTRT),kf;
	pWords->SetCurrentIndex("word");
	if(pWords->Seek("=",&kw)){
		kf=pWords->GetFieldValue("wfreq");
		kf.lVal+=freq;
		pWords->Edit();
		pWords->SetFieldValue("wfreq",kf);
		pWords->Update();
		kf=pWords->GetFieldValue("wid");
		return kf.lVal;
	}
	else{
		long recn=pWords->GetRecordCount();
		pWords->AddNew();
		pWords->SetFieldValue("word",kw);
		kf=freq;
		pWords->SetFieldValue("wfreq",kf);
		kf=recn;
		pWords->SetFieldValue("wid",kf);
		pWords->Update();
		return recn;
	}
}

long CDictionary::Insert(CString w, CString t, long freq)
{
	if(w.GetLength()>10||t.GetLength()>4)return -1;
	long i=Insert(w);
	COleVariant kt(t,VT_BSTRT),kwi(i,VT_I4),kf;
	pTags->SetCurrentIndex("widTag");
	if(pTags->Seek("=",&kwi,&kt)){
		kf=pTags->GetFieldValue("freq");
		kf.lVal+=freq;
		pTags->Edit();
		pTags->SetFieldValue("pfreq",kf);
		pTags->Update();
		kf=pTags->GetFieldValue("pid");
		return kf.lVal;
	}
	else{
		long recn=pTags->GetRecordCount();
		pTags->AddNew();
		pTags->SetFieldValue("pos",kt);
		kf=freq;
		pTags->SetFieldValue("pfreq",kf);
		pTags->SetFieldValue("wid",kwi);
		kf=recn;
		pTags->SetFieldValue("pid",kf);
		pTags->Update();
		return recn;
	}
}

double CDictionary::GetFee(CString name, BOOL full)
{
	if(full){
		return 20.0;
	}
	else
		return 20.0;
}

BOOL CDictionary::Insert(CString sName, CString gName, double f)
{
	// 插入一个中文姓名
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
