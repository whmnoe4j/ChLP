// TagFreq.cpp: implementation of the CTagFreq class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "chlp.h"
#include "TagFreq.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTagFreq::CTagFreq(LPCSTR t,long f)
{
	Tag=t;
	Freq=f;
}

CTagFreq::~CTagFreq()
{

}
