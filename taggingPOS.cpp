// taggingPOS.cpp

#include "stdafx.h"
#include "现代汉语自动分析.h"
#include "wordtagset.h"
#include <math.h>
#include "taggingPOS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif 


uchar CCoMatrix::GetIndexOf(CString tag)	
{
	if(tag=="ww") tag="w";
	for(int i=0; i<pTags->GetSize(); i++)
		if(pTags->GetAt(i)==tag) return i;

	return 0;  // 非法标记
}

CString CCoMatrix::GetTagOf(uchar i)	// 将序号转换为词性标记
{
	if(i>=0 && i<pTags->GetSize()) return pTags->GetAt(i);
	else return "**";	// 非法标记
}

int CCoMatrix::GetTagFreq(uchar i)
{
	return TagFreqs[i];
}

double CCoMatrix::GetCoProb(uchar tag1, uchar tag2) 
{ // 参数：相邻两标记的序号
  if(TagFreqs[tag1]==0) return 0.00001; // 如果前一个标记未出现过，返回极小值
  uchar n=pTags->GetSize( );
  return 0.3*TagFreqs[tag2]/(double)CorpusSize +
	0.7*Matrix[tag1*n+tag2]/(double)TagFreqs[tag1];
}
	
double CCoMatrix::GetWordProb(double wtFreq, uchar tag)
{ // 参数：该词、该标记出现次数，该标记序号
  if(TagFreqs[tag]>0)
  	return (double)(wtFreq+1)/TagFreqs[tag];
	else return 0.00001; // 如果该标记未出现过，返回极小值
}

void CCoMatrix::Create(CStdioFile& tagFile)
{	// 参数：存放标记集的文本文件
  if(Ready( )) Clean; // 清除原有标记集
  CString line;
  pTags=new CStringArray; // 存放标记集的字符串数组
  pTags->Add("$%"); // 添加虚设标记
  pOpenTags=new CStringArray; // 存放开放类标记的字符串数组
  while(pTags->GetSize( )<256 && tagFile.ReadString(line)) {
    int i=line.Find(';');  // 分号之后是注释
    if(i>=0) line=line.Left(i);	else continue;
	  line.TrimLeft( );  line.TrimRight( );
	  if(line.IsEmpty( )) continue;  // 允许有空行
	  if(line.Left(1)=="#" && pOpenTags->GetSize( )<10) {
		  // 开放标记前加"#"，不得超过10个
	    line=line.Mid(1);
	    pOpenTags->Add(line);  // 添加开放类标记
		}
	  pTags->Add(line);  // 添加词性标记
  }
  tagFile.Close( );
  int n=pTags->GetSize( );  // 看看有多少个标记
  TagFreqs=new int[n];	   // 建立标记频度数组
  Matrix=new int[n * n];     // 建立标记共现频度数组
  for(int i=0; i<n; i++) { // 赋初值
	  TagFreqs[i]=0;
	  for(int j=0; j<n; j++) Matrix[i*n+j]=0;
  }
  CorpusSize=0; Modified=TRUE; 
  line.Format("共有 %d 个词性标记", n);
  if(pOpenTags->GetSize( )==0) 
	  line+="\n没有定义开放类，将无法猜测新词词性";
  AfxMessageBox(line);
}

void CCoMatrix::Clean( )
{
  if(Modified) { // 如果语料库修改过
	  CFile tf; char buf[512];
	  if(tf.Open((const char *)FileName, CFile::modeCreate|CFile::modeWrite)) {
		  CArchive ar(&tf, CArchive::store, 512, buf);
		  Serialize(ar); // 存盘
    }
	}
	 
  if(pTags) delete pTags;  
  if(pOpenTags) delete pOpenTags;
  if(TagFreqs) delete [] TagFreqs;
  if(Matrix) delete [] Matrix;
}

extern CMyDictionary *pDict; // 词库指针
void CCoMatrix::AddCorpus(CStdioFile& trainFile)
{  // 参数：训练语料文件（文本：每词一行）
  char line[80];
	
  int n=pTags->GetSize( );
  int lastID=0;  // 虚设标记
  while(trainFile.ReadString(line, 80)) { // 循环处理每一行
    CString s(line);
    s.TrimLeft( ); s.TrimRight( );
    
 	CString w,t;
	int i=s.Find(' ');
	if(i<0) { lastID=0; continue; }
	w=s.Left(i);  t=s.Mid(i+1);
	if(w[0]=='#') w=w.Mid(2);  // 去掉“#P”和“#S”
	if(w.GetLength()==0 || t.GetLength()==0) continue; 
      
	CorpusSize++; // 计算语料库规模
	    
	// if(t[0]=='H') t=t.Mid(1);  // 非HV文件则去掉这一句
    pDict->Insert(w, t); // 加到词库中去
    int curID=GetIndexOf(t); // 计算当前标记的序号
    if(curID>0) {
		  TagFreqs[curID]++; // 增加该标记的出现次数
		  if(lastID>=0) Matrix[lastID*n+curID]++; // 增加相邻标记的共现次数
    }
    lastID=curID; // 将当前标记设置为前一个标记
  }
  trainFile.Close( ); // 关闭训练语料文件
  Modified=TRUE;  // 语料库修改过
}

/*  
void CCoMatrix::AddCorpus(CStdioFile& trainFile)
{  // 参数：训练语料文件（文本：每句一行）
  char line[3000];
	
  int n=pTags->GetSize( );
  while(trainFile.ReadString(line, 3000)) { // 循环处理每一行
    CString s(line);
    s.TrimLeft( ); s.TrimRight( );
    int lastID=0;  // 虚设标记
    while(!s.IsEmpty( )) {  // 循环处理每一个词
		CString w,t;
	    w=s.SpanExcluding(" "); // 取出一个词
	    s=s.Mid(w.GetLength( ));	s.TrimLeft( ); // 从s中去掉这个词
	    int i=w.Find('/');   // 找词语跟标记的界限标记
	    if(i<0) { lastID=0; continue; } // 训练语料有误
			
		t=w.Mid(i+1);  w=w.Left(i); // 将词语跟标记切开
		if(w.GetLength()==0 || t.GetLength()==0) continue; 
      
		CorpusSize++; // 计算语料库规模
	    
		if(t[0]=='H') t=t.Mid(1);  // 非HV文件则去掉这一句
	    pDict->Insert(w, t); // 加到词库中去
	    int curID=GetIndexOf(t); // 计算当前标记的序号
	    if(curID>0) {
			  TagFreqs[curID]++; // 增加该标记的出现次数
			  if(lastID>=0) Matrix[lastID*n+curID]++; // 增加相邻标记的共现次数
 	    }
	    lastID=curID; // 将当前标记设置为前一个标记
	}
  }
  trainFile.Close( ); // 关闭训练语料文件
  Modified=TRUE;  // 语料库修改过
}
*/

IMPLEMENT_SERIAL(CCoMatrix, CObject, 0)
void CCoMatrix::Serialize(CArchive& ar)
{
  if(ar.IsStoring( ) && !Modified) return; // 如果未修改则无须存盘
  if(!ar.IsStoring( )) { // 如果是读入，先建立两个字符串数组以读入标记集
  	pTags=new CStringArray;
	  pOpenTags=new CStringArray;
  }
  pTags->Serialize(ar);  // 标记集序列化
  pOpenTags->Serialize(ar); // 开放类标记序列化
  int n=pTags->GetSize( ); // 看看标记集的规模
  if(!ar.IsStoring( )) {  // 如果是读入，申请内存以存放频度数据
		TagFreqs=new int[n];
	  Matrix=new int[n*n];
  }
  if(ar.IsStoring( )) { // 如果是存盘，写出以下数据
		ar << CorpusSize;  
	  for(int i=0; i<pTags->GetSize( ); i++) {
  	  ar << TagFreqs[i];
	    for(int j=0; j<pTags->GetSize( ); j++)
		    ar << Matrix[i*n+j];
	  }
  }
  else {  // 否则读入以下数据
		ar >> CorpusSize;  
	  for(int i=0; i<pTags->GetSize( ); i++) {
 		  ar >> TagFreqs[i];
	    for(int j=0; j<pTags->GetSize( ); j++) ar >> Matrix[i*n+j];
		}
  }
}

/////////
extern CCoMatrix coMatrix;

void CSpan::GetFrom(CString& s)	// 从字符串获取若干个词
{
  CObArray a;
  s.TrimLeft( ); s.TrimRight( );
  for(uchar i=1; i<20 && !s.IsEmpty( ); i++) { // 从第1个词开始
		Words[i]=s.SpanExcluding(" ");  // 取词
		s=s.Mid(Words[i].GetLength( ));
		s.TrimLeft( );
		pDict->GetFreq(Words[i], a);   // 查词库
/*
		if(a.GetSize( )==0) GuessTag(i); // 如果没有找到则猜测词性
		else {  // 否则添加各个标记及其出现次数
		  for(uchar j=0; j<10 && j<a.GetSize( ); j++) {
			  CTagFreq *p=(CTagFreq *)a.GetAt(j);
			  Tags[i][j]=coMatrix.GetIndexOf(p->Tag);
			  Freqs[i][j]=p->Freq;
		  }
*/
		uchar n=0;
		for(uchar j=0; j<10 && j<a.GetSize(); j++) {
			CTagFreq *p=(CTagFreq *)a.GetAt(j);
			uchar tmp=coMatrix.GetIndexOf(p->Tag);
			if(tmp>0) { // 先检查是否合法标记
				Tags[i][j]=tmp; n++; 
				Freqs[i][j]=p->Freq;
			}
		}
		if(n==0) GuessTag(i);


		Tags[i][j]=0;  // 0表示虚设标记，或已无其他标记
		  if(j==1) { i++; break; } // 如果该词没有词性歧义，则停止

	}
	CurLength=i; // 词的个数（包括第0个）
}
	
void CSpan::GuessTag(char i)	// 猜测第i个词的词性标记
{
	for(uchar k=0; k<coMatrix.pOpenTags->GetSize( ); k++) {
		Tags[i][k]=coMatrix.GetIndexOf(coMatrix.pOpenTags->GetAt(k));
		Freqs[i][k]=1;
	}
	Tags[i][k]=0;
}

void CSpan::Reset( )	
{
  Tags[0][0]=Tags[CurLength-1][0];	
  Tags[0][1]=0;		Freqs[0][0]=0.0; 
  CurLength=1;
}

void CSpan::Disamb( )	// 排除词性歧义，进行词性标注
{
  uchar i,j,k, m;		double minFee, tmp;
  for(i=1; i<CurLength; i++) { // 对每一个词
		for(j=0; Tags[i][j]>0; j++) { // 对它的每个标记
		  m=11;
		  for(k=0; Tags[i-1][k]>0 ||i==1 && k==0; k++) { // 对前一词的每个标记
			  tmp=coMatrix.GetCoProb(Tags[i-1][k], Tags[i][j]);
				// 转移概率
			  tmp=-log(tmp);  // 转换为费用
			  tmp+=Freqs[i-1][k]; // 加上累计费用
			  if(m>10 || tmp<minFee) {	m=k;  minFee=tmp; } // 取最小费用
		  }
		  GoodPrev[i][j]=m; // 第j个标记的最佳前趋
		  tmp=coMatrix.GetWordProb(Freqs[i][j], Tags[i][j]); // 词的概率
		  Freqs[i][j]=minFee+-log(tmp);  // 加上词的费用
		}
	}
}

void CSpan::WriteTo(CStdioFile out) // 将词语/标记串写到输出文件中去
{
  CString s="";
  for(int i=CurLength-1, j=0; i>0; i--) {
		s=Words[i]+'/'+coMatrix.GetTagOf(Tags[i][j]) + " " +s;
		j=GoodPrev[i][j];
  }
  out.WriteString(s);
}
