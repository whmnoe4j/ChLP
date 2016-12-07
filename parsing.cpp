#include "stdafx.h"
#include "�ִ������Զ�����.h"
#include "parsing.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CRule::CRule(CString Line)
{	// ����һ������
	int i=Line.Find("-->");
	Ls=Line.Left(i);	Ls.TrimRight( ); Ls.TrimLeft( );
	Line=Line.Mid(i+3);	Line.TrimLeft( );

	i=Line.Find(' ');
	if(i<0) { Rs1=Line; Rs2=""; }
	else {
		Rs1=Line.Left(i); Line=Line.Mid(i+1);	
		Line.TrimLeft( );	  Rs2=Line;
	}
}

extern CObArray  rules,  edges;

BOOL GetRule(CString& ls, CString rs1, CString rs2)
{
  CRule *r;	// ����ָ��
  for(int i=0; i<rules.GetSize( ); i++) {
		r=(CRule *)rules[i];
		if(r->Rs1==rs1 && r->Rs2==rs2) { // ����ҵ���
		  ls=r->Ls;  return TRUE;
		}
  }
  return FALSE; // û���ҵ����ʵĹ���
}

CEdge::CEdge(CString wt, int wid)
{ // Ϊһ�����ｨ��һ���ֲ�����
	int i=wt.Find('/'); 
 	if(i<0) Root=wt;  // ֻ�д��Ա��
	else Root=wt.Mid(i+1)+'('+wt.Left(i)+')';  // �д���ʹ��Ա��
	First=Last=wid; // �������յ�����Ϊ�ʵ����
	Sub1=Sub2=-1;	// ���ɳɷ�Ϊ��
}

CEdge::CEdge(CEdge *p, int pid, CString r)
{ // ������������һ���ֲ�����
	Root=r;	First=p->First;	Last=p->Last;	// ��㡢�յ��ԭ�ֲ�������ͬ
  Sub1=pid;	Sub2=-1;  // ��ԭ�ֲ�����Ϊ��������������Ϊ��
}

CEdge::CEdge(CEdge *p1, CEdge *p2, int pid1, int pid2, CString r)
{ // �����������һ���ֲ�����
	Root=r;		First=p1->First; 	Last=p2->Last;	
		// ���������������㣬�յ������������յ�
  Sub1=pid1;	Sub2=pid2;
}

void Expanding( )
{ // ���ݹ������Ӿֲ�����
  int i=edges.GetSize( )-1, j=0; // i�Ǹո�Ϊ�������ӵ�һ���ֲ����������
  CString nr;		// �µľֲ������ĸ�
  CEdge *e, *e2;		// �����ֲ�������ָ��
  BOOL Raising=FALSE;	// �Ƿ��Ѿ�ʹ������������
  while(i<edges.GetSize( )) { 
		e=(CEdge *)edges[i];
		e2=(CEdge *)edges[j];
		if(!Raising && GetRule(nr, e->GetRoot( ))) {
			// �����δʹ���������򣬲����ܹ��ҵ�һ����������
		  edges.Add(new CEdge(e,i, nr)); // ��������������һ���ֲ�����
		  Raising=TRUE;
		}
		if(e2->Last+1==e->First && GetRule(nr, e2->GetRoot( ),e->GetRoot( ))) 
			// ����ܹ��ҵ�һ���������
		  edges.Add(new CEdge(e2,e, j, i, nr)); //�������������һ���ֲ�����
		j++;
		if(j>=i) { 
		  i++; j=0; // ʹ��һ���ֲ�������Ϊ��ǰ�ֲ�����
		  Raising=FALSE; // �����ٴ�ʹ����������
		}
	}
}

extern CObArray rules, edges;
CString Parsing(CString s)
{	// ����һ������
  CEdge *e=NULL;  // �ֲ�����ָ��
  int wid=1;	    // �������
  CString t;		// �ַ�������Ŵ���
  for(int i=0; i<edges.GetSize( ); i++) 
		if(edges[i]!=NULL) delete edges[i];
  edges.RemoveAll( );
		// �����������������һ������ʱ���µľֲ�������

  while(s.GetLength( )>0) { // ����䲻Ϊ��ʱ
		int i=s.Find(' ');	// �Ҵʽ���
		if(i<0) { t=s; s=""; }
		else { t=s.Left(i); s=s.Mid(i+1); s.TrimLeft( ); }
		e=new CEdge(t,wid);  edges.Add(e); // Ϊ��ǰ�ʽ���һ���ֲ�����
		wid++;
		Expanding( ); // ���ݹ������Ӿֲ�����
  }
  return GetTrees(wid-1);	// ���ط������
}

CString GetTrees(int wid)
{	// ��ȡ�������
  CString s="", tmp;	// ��ŷ������
  CEdge *e;	// �ֲ�����ָ��
  for(int i=0; i<edges.GetSize( ); i++) {
		e=(CEdge *)edges[i];
		if(e->First==1 && e->Last==wid && e->GetRoot( )=="S") 
			// ����þֲ���������ȫ�䣬���Ҹ�Ϊ��ʼ��
		  s+=GetOneTree(e)+"\n\n"; // ��Ӹþֲ��������
  }
  tmp.Format("�ֲ�����%d����", edges.GetSize( ));
  if(s.IsEmpty( )) s=tmp+"���Ӳ����﷨";	else s=tmp+'\n'+s;
  return s;
}

CString GetOneTree(CEdge *e)
{	// ��ȡһ�÷�����
	if(e->Sub1==-1 && e->Sub2==-1) return e->Root;
		// ����þֲ������ĸ����ս�����������ĸ����������
	CEdge *e1, *e2; // �����ֲ�����ָ��
	CString s=e->Root+'(';
	e1=(CEdge *)edges[e->Sub1];
	s+=GetOneTree(e1); // ����������
	
	if(e->Sub2>=0) { // �������������
		e2=(CEdge *)edges[e->Sub2];
		s+='+'+GetOneTree(e2); // ����������
	}
	s+=')';
	return s;
}

////////
CProbRule::CProbRule(CString Line)
{
	DesireCount=0.0;
	int i=Line.Find("-->");
	Ls=Line.Left(i);	Ls.TrimRight(); Ls.TrimLeft();
	Line=Line.Mid(i+3);	Line.TrimLeft();

	i=Line.ReverseFind(' ');
	if(i<0) return;
	Prob=atof(Line.Mid(i+1));
	Line=Line.Left(i);  Line.TrimRight();

	i=Line.Find(' ');
	if(i<0) {	Rs1=Line; return; }
	Rs1=Line.Left(i);
	Line=Line.Mid(i+1);
	Line.TrimLeft();

	if(Line.GetLength()>0) Rs2=Line;
	else Rs2="";
}

CProbEdge::CProbEdge(CProbEdge *p, int pid, int Rid)
{
	RuleId=Rid;	OutsideProb=0.0; Parent="";
	CProbRule *r=(CProbRule *)rules[Rid];
	Root=r->Ls;		First=p->First;
	Last=p->Last;	Sub1=pid;	Sub2=-1;
	InsideProb=InProbAddUp=r->Prob*p->InProbAddUp;
}

CProbEdge::CProbEdge(CProbEdge *p1, CProbEdge *p2, int pid1, int pid2, int Rid)
{
	RuleId=Rid;	OutsideProb=0.0; Parent="";	
	CProbRule *r=(CProbRule *)rules[Rid];
	Root=r->Ls;		First=p1->First;
	Last=p2->Last;	Sub1=pid1;	Sub2=pid2;
	InsideProb=InProbAddUp=r->Prob*p1->InProbAddUp*p2->InProbAddUp;
}

CString ProbParsing(CString s, double& sProb)
{
  int i, j, pid, rid, wn=0;  // wn�����s�дʵĸ���
  CString w;  CProbEdge *e;
  CProbRule *r;

  for(i=0; i<edges.GetSize( ); i++) 
    if(edges[i]!=NULL) delete edges[i];
  edges.RemoveAll( ); // �����һ�����ӵľֲ�������

  while(!s.IsEmpty( )) {  // Ϊÿ���ʽ����ֲ�����
    wn++;  i=s.Find(' ');
    if(i<0) { w=s;  s=""; }
    else { w=s.Left(i);  s=s.Mid(i);  s.TrimLeft( ); }
    e=new CProbEdge(w, wn);    
    edges.Add(e); pid=edges.GetSize( )-1;
    rid=GetProbRule(e->GetRoot( ));
    if(rid>=0) {// ������������
      r=(CProbRule *)rules[rid];
      edges.Add(new CProbEdge(e, pid, rid));
    }
  }
  for(j=1; j<=wn; j++) // Ϊ���ⳤ�ȵĴʴ������ֲ�����
    for(i=1; i+j<=wn; i++) InsertEdges(i, i+j);

  sProb=0.0;    // ���Ӹ���
  for(i=edges.GetSize( )-1; i>=0; i--) { // ���ж����ֺϷ��ķ������
    e=(CProbEdge *)edges[i];
    if(e->Root=="S" && e->First==1 && e->Last==wn) sProb+=e->InsideProb;
    else break;
  }
  if(sProb>0.0) {
    GetOutsideProb(wn); // ��ȡ�ⲿ����
    GetDesireCount(sProb);  // ��ȡ����ʹ�õ���������
  }  
  
  CString t=GetProbTrees(wn); // ��������ʵķ�����
  return t; // ����������
}

void GetRuleNewProb( )    
{    
  int i, j, start=0;   // start��ÿ�����ĵ�һ�������λ�� 
  CProbRule *r, *r0;    
  r=(CProbRule *)rules[0];    
  double sumCount=r->DesireCount; // ÿ��������������֮��   
  CString Ls=r->Ls;    // ÿ�������󲿷���
    
  for(i=1; i<rules.GetSize( ); i++) {    
    r=(CProbRule *)rules[i];    
    if(r->Ls==Ls)  sumCount+=r->DesireCount;    
    else {    // Ϊ����ÿ����������µĸ���
      for(j=start; j<i; j++) {    
        r0=(CProbRule *)rules[j];    
        r0->Prob=r0->DesireCount/sumCount;    
      }    
      start=i;  sumCount=r->DesireCount;   Ls=r->Ls;      
    }    
  }    
  for(j=start; j<rules.GetSize( ); j++) {  // Ϊ���һ���������µĸ���
    r0=(CProbRule *)rules[j];    
    r0->Prob=r0->DesireCount/sumCount;    
  }    
}    

void InsertEdges(int first, int last)
  { 
    int i, j,  rid;
    CProbEdge *e, *e1, *e2, *e0;
  
    for(i=0; i<edges.GetSize( ); i++) {
      e1=(CProbEdge *)edges[i];
      if(e1->First!=first) continue;
  	    if(e1->Last==last && (rid=GetProbRule(e1->GetRoot( )))>=0) {
    	  e=new CProbEdge(e1,i,rid); edges.Add(e); // ������������
        for(int k=edges.GetSize( )-2; k>=0; k--) { // ����ͬ��ֲ�����
          e0=(CProbEdge *)edges[k];
          if(e0->First!=e->First || e0->Last!=e->Last) break;
			// ��Ϊ��e����㡢�յ���ͬ�ľֲ�������Ȼ�������У�
			// ����ֻҪ�����յ㲻ͬ���ɽ�������
          if(e0->GetRoot( )==e->GetRoot( )) {
            e0->InProbAddUp+=e->InsideProb;
            e->InProbAddUp+=e0->InsideProb;
          }
        }
        continue; 
      }
      for(j=0; j<edges.GetSize( ); j++) {
        e2=(CProbEdge *)edges[j];
        if(e2->Last!=last||e1->Last+1!=e2->First) continue;
        rid=GetProbRule(e1->GetRoot( ),e2->GetRoot( ));
        if(rid<0) continue; 
        e=new CProbEdge(e1,e2,i,j,rid); edges.Add(e); // ����������� 
        for(int k=edges.GetSize( )-2; k>=0; k--) { // ����ͬ��ֲ�����
          e0=(CProbEdge *)edges[k];
          if(e0->First!=e->First || e0->Last!=e->Last) break;
          if(e0->GetRoot( )==e->GetRoot( )) {
            e0->InProbAddUp+=e->InsideProb;
            e->InProbAddUp+=e0->InsideProb;
          }
        }
      }
    }
  }

void GetOutsideProb(int wn)
  {  
    int i, j, pid, bid;  CString tmp;
    CProbEdge *e, *pe, *be;    CProbRule *r;
   
    for(i=edges.GetSize( )-1; i>=0; i--) {
      e=(CProbEdge *)edges[i];  e->Parent.TrimRight( );
      if(e->First==1 && e->Last==wn && e->Root=="S") e->OutsideProb=1.0;
      else if(e->Sub1<0 || e->Parent.IsEmpty( )) continue;
      else while(!e->Parent.IsEmpty( )) { // ��ÿһ������ľֲ�����
        j=e->Parent.Find(' ');
        if(j>0) { tmp=e->Parent.Left(j); e->Parent=e->Parent.Mid(j+1); }
        else { tmp=e->Parent; e->Parent=""; }
        pid=atoi((const char *)tmp); // �������ַ���ת��Ϊ����
        pe=(CProbEdge *)edges[pid];
        r=(CProbRule *)rules[pe->RuleId];
        double outProb=pe->OutsideProb*r->Prob;
        if(pe->Sub1>=0 && pe->Sub1!=i) bid=pe->Sub1; 
        else if(pe->Sub2>=0 && pe->Sub2!=i) bid=pe->Sub2;
        else bid=-1; // "�ֵ�"�ֲ�����ΪSub1��Sub2��û��
        if(bid>=0) { // �����"�ֵ�"�ֲ�����
  be=(CProbEdge *)edges[bid]; 
  outProb*=be->InProbAddUp; 
}
        e->OutsideProb+=outProb;
      }
      if(e->Sub1>=0) { // ����е�һ�����ɳɷ�
        CProbEdge *s1=(CProbEdge *)edges[e->Sub1];
        tmp.Format("%d ", i);
        s1->Parent+=tmp;
      }
      if(e->Sub2>=0) { // ����еڶ������ɳɷ�
        CProbEdge *s2=(CProbEdge *)edges[e->Sub2];
        tmp.Format("%d ", i);
        s2->Parent+=tmp;
      }
    }
  }

void GetDesireCount(double sProb)
  {  
    CProbRule *r;  CProbEdge *e, *e1, *e2;
    double dCount; // ��������
    for(int i=0; i<edges.GetSize( ); i++) {
      e=(CProbEdge *)edges[i];
      if(e->OutsideProb==0.0) continue;
      r=(CProbRule *)rules[e->RuleId];
      dCount=r->Prob*e->OutsideProb; // ������ʳ����ⲿ����
      if(e->Sub1>=0) {
        e1=(CProbEdge *)edges[e->Sub1]; 
        dCount*=e1->InProbAddUp; // �ٳ��Թ��ɳɷֵ��ڲ�����
      }
      if(e->Sub2>=0) {
        e2=(CProbEdge *)edges[e->Sub2];
        dCount*=e2->InProbAddUp; // �ٳ��Թ��ɳɷֵ��ڲ�����
      }
      dCount/=sProb; // ����������
      r->DesireCount+=dCount; // �ۼӵ��ù��������������ȥ
    }
  }

int  GetProbRule(CString rs1, CString rs2)
{
	CProbRule *r;	
	for(int i=0; i<rules.GetSize(); i++) {
		r=(CProbRule *)rules[i];
		if(r->Rs1==rs1 && r->Rs2==rs2) return i;
	}
	return -1;
}

CString GetProbTrees(int wid)
{
	CString s="", tmp;		CProbEdge *e;
	double prob=0.0;

	for(int i=edges.GetSize()-1; i>=0; i--) {
		// ȫ�ַ���һ�������
		e=(CProbEdge *)edges[i];
		if(e->First==1 && e->Last==wid && e->GetRoot()=="S") {
			tmp.Format("%7.5f: ", e->InsideProb);
			s+=tmp+GetOneProbTree(e)+"\n\n";
		}
		else break;
	}
	tmp.Format("�ֲ�����%d����", edges.GetSize());
	if(s.IsEmpty()) s=tmp+"���Ӳ����﷨\n\n";
	else s=tmp+'\n'+s;

	return s;
}

CString GetOneProbTree(CProbEdge *e)
{
	if(e->Sub1==-1 && e->Sub2==-1)	return e->Root;
	CProbEdge *e1, *e2;

	CString s=e->Root+'(';
	e1=(CProbEdge *)edges[e->Sub1];
	s+=GetOneProbTree(e1);
	
	if(e->Sub2>=0) {
		e2=(CProbEdge *)edges[e->Sub2];
		s+='+'+GetOneProbTree(e2);
	}
	s+=')';
	return s;
}
