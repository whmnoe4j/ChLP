#include "stdafx.h"
#include "现代汉语自动分析.h"
#include "parsing.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CRule::CRule(CString Line)
{	// 读入一条规则
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
  CRule *r;	// 规则指针
  for(int i=0; i<rules.GetSize( ); i++) {
		r=(CRule *)rules[i];
		if(r->Rs1==rs1 && r->Rs2==rs2) { // 如果找到了
		  ls=r->Ls;  return TRUE;
		}
  }
  return FALSE; // 没有找到合适的规则
}

CEdge::CEdge(CString wt, int wid)
{ // 为一个词语建立一个局部分析
	int i=wt.Find('/'); 
 	if(i<0) Root=wt;  // 只有词性标记
	else Root=wt.Mid(i+1)+'('+wt.Left(i)+')';  // 有词语和词性标记
	First=Last=wid; // 将起点和终点设置为词的序号
	Sub1=Sub2=-1;	// 构成成分为空
}

CEdge::CEdge(CEdge *p, int pid, CString r)
{ // 用提升规则建立一个局部分析
	Root=r;	First=p->First;	Last=p->Last;	// 起点、终点跟原局部分析相同
  Sub1=pid;	Sub2=-1;  // 以原局部分析为左子树，右子树为空
}

CEdge::CEdge(CEdge *p1, CEdge *p2, int pid1, int pid2, CString r)
{ // 用捆绑规则建立一个局部分析
	Root=r;		First=p1->First; 	Last=p2->Last;	
		// 起点是左子树的起点，终点是右子树的终点
  Sub1=pid1;	Sub2=pid2;
}

void Expanding( )
{ // 根据规则，增加局部分析
  int i=edges.GetSize( )-1, j=0; // i是刚刚为词语增加的一个局部分析的序号
  CString nr;		// 新的局部分析的根
  CEdge *e, *e2;		// 两个局部分析的指针
  BOOL Raising=FALSE;	// 是否已经使用了提升规则
  while(i<edges.GetSize( )) { 
		e=(CEdge *)edges[i];
		e2=(CEdge *)edges[j];
		if(!Raising && GetRule(nr, e->GetRoot( ))) {
			// 如果尚未使用提升规则，并且能够找到一条提升规则
		  edges.Add(new CEdge(e,i, nr)); // 用提升规则增加一个局部分析
		  Raising=TRUE;
		}
		if(e2->Last+1==e->First && GetRule(nr, e2->GetRoot( ),e->GetRoot( ))) 
			// 如果能够找到一条捆绑规则
		  edges.Add(new CEdge(e2,e, j, i, nr)); //用捆绑规则增加一个局部分析
		j++;
		if(j>=i) { 
		  i++; j=0; // 使下一个局部分析成为当前局部分析
		  Raising=FALSE; // 允许再次使用提升规则
		}
	}
}

extern CObArray rules, edges;
CString Parsing(CString s)
{	// 分析一个句子
  CEdge *e=NULL;  // 局部分析指针
  int wid=1;	    // 词语序号
  CString t;		// 字符串，存放词语
  for(int i=0; i<edges.GetSize( ); i++) 
		if(edges[i]!=NULL) delete edges[i];
  edges.RemoveAll( );
		// 以上是先清除分析上一个句子时留下的局部分析。

  while(s.GetLength( )>0) { // 输入句不为空时
		int i=s.Find(' ');	// 找词界标记
		if(i<0) { t=s; s=""; }
		else { t=s.Left(i); s=s.Mid(i+1); s.TrimLeft( ); }
		e=new CEdge(t,wid);  edges.Add(e); // 为当前词建立一个局部分析
		wid++;
		Expanding( ); // 根据规则，增加局部分析
  }
  return GetTrees(wid-1);	// 返回分析结果
}

CString GetTrees(int wid)
{	// 获取分析结果
  CString s="", tmp;	// 存放分析结果
  CEdge *e;	// 局部分析指针
  for(int i=0; i<edges.GetSize( ); i++) {
		e=(CEdge *)edges[i];
		if(e->First==1 && e->Last==wid && e->GetRoot( )=="S") 
			// 如果该局部分析覆盖全句，并且根为起始符
		  s+=GetOneTree(e)+"\n\n"; // 添加该局部分析结果
  }
  tmp.Format("局部分析%d个；", edges.GetSize( ));
  if(s.IsEmpty( )) s=tmp+"句子不合语法";	else s=tmp+'\n'+s;
  return s;
}

CString GetOneTree(CEdge *e)
{	// 获取一棵分析树
	if(e->Sub1==-1 && e->Sub2==-1) return e->Root;
		// 如果该局部分析的根是终结符，返回它的根（包括词语）
	CEdge *e1, *e2; // 两个局部分析指针
	CString s=e->Root+'(';
	e1=(CEdge *)edges[e->Sub1];
	s+=GetOneTree(e1); // 加上左子树
	
	if(e->Sub2>=0) { // 如果还有右子树
		e2=(CEdge *)edges[e->Sub2];
		s+='+'+GetOneTree(e2); // 加上右子树
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
  int i, j, pid, rid, wn=0;  // wn是语句s中词的个数
  CString w;  CProbEdge *e;
  CProbRule *r;

  for(i=0; i<edges.GetSize( ); i++) 
    if(edges[i]!=NULL) delete edges[i];
  edges.RemoveAll( ); // 清除上一个句子的局部分析表

  while(!s.IsEmpty( )) {  // 为每个词建立局部分析
    wn++;  i=s.Find(' ');
    if(i<0) { w=s;  s=""; }
    else { w=s.Left(i);  s=s.Mid(i);  s.TrimLeft( ); }
    e=new CProbEdge(w, wn);    
    edges.Add(e); pid=edges.GetSize( )-1;
    rid=GetProbRule(e->GetRoot( ));
    if(rid>=0) {// 运用提升规则
      r=(CProbRule *)rules[rid];
      edges.Add(new CProbEdge(e, pid, rid));
    }
  }
  for(j=1; j<=wn; j++) // 为任意长度的词串建立局部分析
    for(i=1; i+j<=wn; i++) InsertEdges(i, i+j);

  sProb=0.0;    // 句子概率
  for(i=edges.GetSize( )-1; i>=0; i--) { // 看有多少种合法的分析结果
    e=(CProbEdge *)edges[i];
    if(e->Root=="S" && e->First==1 && e->Last==wn) sProb+=e->InsideProb;
    else break;
  }
  if(sProb>0.0) {
    GetOutsideProb(wn); // 获取外部概率
    GetDesireCount(sProb);  // 获取规则使用的期望次数
  }  
  
  CString t=GetProbTrees(wn); // 构造带概率的分析串
  return t; // 输出分析结果
}

void GetRuleNewProb( )    
{    
  int i, j, start=0;   // start是每组规则的第一条规则的位置 
  CProbRule *r, *r0;    
  r=(CProbRule *)rules[0];    
  double sumCount=r->DesireCount; // 每组规则的期望次数之和   
  CString Ls=r->Ls;    // 每组规则的左部符号
    
  for(i=1; i<rules.GetSize( ); i++) {    
    r=(CProbRule *)rules[i];    
    if(r->Ls==Ls)  sumCount+=r->DesireCount;    
    else {    // 为组内每条规则计算新的概率
      for(j=start; j<i; j++) {    
        r0=(CProbRule *)rules[j];    
        r0->Prob=r0->DesireCount/sumCount;    
      }    
      start=i;  sumCount=r->DesireCount;   Ls=r->Ls;      
    }    
  }    
  for(j=start; j<rules.GetSize( ); j++) {  // 为最后一组规则计算新的概率
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
    	  e=new CProbEdge(e1,i,rid); edges.Add(e); // 运用提升规则
        for(int k=edges.GetSize( )-2; k>=0; k--) { // 查找同类局部分析
          e0=(CProbEdge *)edges[k];
          if(e0->First!=e->First || e0->Last!=e->Last) break;
			// 因为跟e的起点、终点相同的局部分析必然连续排列，
			// 所以只要起点或终点不同即可结束查找
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
        e=new CProbEdge(e1,e2,i,j,rid); edges.Add(e); // 运用捆绑规则 
        for(int k=edges.GetSize( )-2; k>=0; k--) { // 查找同类局部分析
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
      else while(!e->Parent.IsEmpty( )) { // 对每一个更大的局部分析
        j=e->Parent.Find(' ');
        if(j>0) { tmp=e->Parent.Left(j); e->Parent=e->Parent.Mid(j+1); }
        else { tmp=e->Parent; e->Parent=""; }
        pid=atoi((const char *)tmp); // 将数字字符串转换为整数
        pe=(CProbEdge *)edges[pid];
        r=(CProbRule *)rules[pe->RuleId];
        double outProb=pe->OutsideProb*r->Prob;
        if(pe->Sub1>=0 && pe->Sub1!=i) bid=pe->Sub1; 
        else if(pe->Sub2>=0 && pe->Sub2!=i) bid=pe->Sub2;
        else bid=-1; // "兄弟"局部分析为Sub1或Sub2或没有
        if(bid>=0) { // 如果有"兄弟"局部分析
  be=(CProbEdge *)edges[bid]; 
  outProb*=be->InProbAddUp; 
}
        e->OutsideProb+=outProb;
      }
      if(e->Sub1>=0) { // 如果有第一个构成成分
        CProbEdge *s1=(CProbEdge *)edges[e->Sub1];
        tmp.Format("%d ", i);
        s1->Parent+=tmp;
      }
      if(e->Sub2>=0) { // 如果有第二个构成成分
        CProbEdge *s2=(CProbEdge *)edges[e->Sub2];
        tmp.Format("%d ", i);
        s2->Parent+=tmp;
      }
    }
  }

void GetDesireCount(double sProb)
  {  
    CProbRule *r;  CProbEdge *e, *e1, *e2;
    double dCount; // 期望次数
    for(int i=0; i<edges.GetSize( ); i++) {
      e=(CProbEdge *)edges[i];
      if(e->OutsideProb==0.0) continue;
      r=(CProbRule *)rules[e->RuleId];
      dCount=r->Prob*e->OutsideProb; // 规则概率乘以外部概率
      if(e->Sub1>=0) {
        e1=(CProbEdge *)edges[e->Sub1]; 
        dCount*=e1->InProbAddUp; // 再乘以构成成分的内部概率
      }
      if(e->Sub2>=0) {
        e2=(CProbEdge *)edges[e->Sub2];
        dCount*=e2->InProbAddUp; // 再乘以构成成分的内部概率
      }
      dCount/=sProb; // 除以语句概率
      r->DesireCount+=dCount; // 累加到该规则的期望次数中去
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
		// 全局分析一定在最后
		e=(CProbEdge *)edges[i];
		if(e->First==1 && e->Last==wid && e->GetRoot()=="S") {
			tmp.Format("%7.5f: ", e->InsideProb);
			s+=tmp+GetOneProbTree(e)+"\n\n";
		}
		else break;
	}
	tmp.Format("局部分析%d个；", edges.GetSize());
	if(s.IsEmpty()) s=tmp+"句子不合语法\n\n";
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
