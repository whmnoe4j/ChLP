// HZPair.cpp : implementation file
//

#include "stdafx.h"
#include "chlp.h"
#include "HZPair.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// HZPair

IMPLEMENT_DYNCREATE(HZPair, CObject)

HZPair::HZPair()
{
}


HZPair::~HZPair()
{
}


/////////////////////////////////////////////////////////////////////////////
// HZPair diagnostics

#ifdef _DEBUG
void HZPair::AssertValid() const
{
	CObject::AssertValid();
}

void HZPair::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// HZPair serialization

void HZPair::Serialize(CArchive& ar)
{
	int i;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		for(i=0;i<4;i++) ar<<zz[i];
		ar<<freq;
	}
	else
	{
		// TODO: add loading code here
		for(i=0;i<4;i++) ar>>zz[i];
		ar>>freq;
	}
}

/////////////////////////////////////////////////////////////////////////////
// HZPair commands

void HZPair::AddFreq()
{
	freq++;
}

HZPair::HZPair(const char *z2)
{
	strncpy(zz,z2,4);
	freq=1;
}
