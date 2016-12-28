// Dictionary.h: interface for the CDictionary class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DICTIONARY_H__871F2468_A4C2_40E7_97BE_AEB51EB96AA2__INCLUDED_)
#define AFX_DICTIONARY_H__871F2468_A4C2_40E7_97BE_AEB51EB96AA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDictionary  
{
public:
	BOOL Insert(CString sName,CString gName,double f);
	double GetFee(CString name,BOOL full);
	CDaoTableDef* pNamesDef;
	CDaoRecordset* pNames;
	long Insert(CString w,CString t,long freq=1);
	long Insert(CString w,long freq=1);
	long GetFreq(CString w,CObArray&a);
	long GetFreq(CString w,CString t);
	long GetFreq(CString w);
	long GetWordID(CString w);
	CDaoTableDef* pTagsDef;
	CDaoTableDef* pWordsDef;
	CDaoRecordset* pTags;
	CDaoRecordset* pWords;
	CDaoDatabase* pDatabase;
	CDictionary();
	virtual ~CDictionary();
	
};

#endif // !defined(AFX_DICTIONARY_H__871F2468_A4C2_40E7_97BE_AEB51EB96AA2__INCLUDED_)
