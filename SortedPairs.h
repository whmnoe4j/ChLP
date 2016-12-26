// SortedPairs.h: interface for the CSortedPairs class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SORTEDPAIRS_H__ADDA6B46_1406_4A49_9670_7FBE84A6A131__INCLUDED_)
#define AFX_SORTEDPAIRS_H__ADDA6B46_1406_4A49_9670_7FBE84A6A131__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSortedPairs : public CObArray  
{
public:
	void Insert(const char*zz);
	BOOL Search(const char*zz, int &id);
	CSortedPairs();
	virtual ~CSortedPairs();

};

#endif // !defined(AFX_SORTEDPAIRS_H__ADDA6B46_1406_4A49_9670_7FBE84A6A131__INCLUDED_)
