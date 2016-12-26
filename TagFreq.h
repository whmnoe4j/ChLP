// TagFreq.h: interface for the CTagFreq class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TAGFREQ_H__7A0023B0_1A6D_4187_92E1_40BA7034CCAE__INCLUDED_)
#define AFX_TAGFREQ_H__7A0023B0_1A6D_4187_92E1_40BA7034CCAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTagFreq:public CObject
{
public:
	int Freq;
	CString Tag;
	CTagFreq(LPCSTR t, long f);
	virtual ~CTagFreq();

};

#endif // !defined(AFX_TAGFREQ_H__7A0023B0_1A6D_4187_92E1_40BA7034CCAE__INCLUDED_)
