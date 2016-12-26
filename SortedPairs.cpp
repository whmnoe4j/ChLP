// SortedPairs.cpp: implementation of the CSortedPairs class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "chlp.h"
#include "SortedPairs.h"
#include "hzpair.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSortedPairs::CSortedPairs()
{
	CObArray();
}

CSortedPairs::~CSortedPairs()
{

}

BOOL CSortedPairs::Search(const char *zz, int &id)
{
	HZPair*hp;
	int left=0,mid,right=GetSize()-1,cmp;
	while(left<=right)
	{
		mid=(left+right)/2;
		hp=(HZPair*)GetAt(mid);
		cmp=strncmp(hp->zz,zz,4);
		if(cmp<0)
			left=mid+1;
		else if(cmp>0)
			right=mid-1;
		else
		{
			id=mid;
			return TRUE;
		}
	}
	id=left;
	return FALSE;
}

void CSortedPairs::Insert(const char *zz)
{
	HZPair*hp;
	int id;
	if(Search(zz,id))
	{
		hp=(HZPair*)GetAt(id);
		hp->AddFreq();
	}
	else
	{
		hp=new HZPair(zz);
		InsertAt(id,hp);
	}
}