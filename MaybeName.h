// MaybeName.h: interface for the CMaybeName class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAYBENAME_H__FF8FCFD3_2A5B_40C2_B194_6B73ED7DB042__INCLUDED_)
#define AFX_MAYBENAME_H__FF8FCFD3_2A5B_40C2_B194_6B73ED7DB042__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMaybeName : public CObject  
{
public:
	//CMaybeName();
	virtual ~CMaybeName();
	long offset,length;
	double fee;
	CMaybeName(long off,long len,double f){offset=off;length=len;fee=f;}
};

#endif // !defined(AFX_MAYBENAME_H__FF8FCFD3_2A5B_40C2_B194_6B73ED7DB042__INCLUDED_)
