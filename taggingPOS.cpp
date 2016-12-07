// taggingPOS.cpp

#include "stdafx.h"
#include "�ִ������Զ�����.h"
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

	return 0;  // �Ƿ����
}

CString CCoMatrix::GetTagOf(uchar i)	// �����ת��Ϊ���Ա��
{
	if(i>=0 && i<pTags->GetSize()) return pTags->GetAt(i);
	else return "**";	// �Ƿ����
}

int CCoMatrix::GetTagFreq(uchar i)
{
	return TagFreqs[i];
}

double CCoMatrix::GetCoProb(uchar tag1, uchar tag2) 
{ // ��������������ǵ����
  if(TagFreqs[tag1]==0) return 0.00001; // ���ǰһ�����δ���ֹ������ؼ�Сֵ
  uchar n=pTags->GetSize( );
  return 0.3*TagFreqs[tag2]/(double)CorpusSize +
	0.7*Matrix[tag1*n+tag2]/(double)TagFreqs[tag1];
}
	
double CCoMatrix::GetWordProb(double wtFreq, uchar tag)
{ // �������ôʡ��ñ�ǳ��ִ������ñ�����
  if(TagFreqs[tag]>0)
  	return (double)(wtFreq+1)/TagFreqs[tag];
	else return 0.00001; // ����ñ��δ���ֹ������ؼ�Сֵ
}

void CCoMatrix::Create(CStdioFile& tagFile)
{	// ��������ű�Ǽ����ı��ļ�
  if(Ready( )) Clean; // ���ԭ�б�Ǽ�
  CString line;
  pTags=new CStringArray; // ��ű�Ǽ����ַ�������
  pTags->Add("$%"); // ���������
  pOpenTags=new CStringArray; // ��ſ������ǵ��ַ�������
  while(pTags->GetSize( )<256 && tagFile.ReadString(line)) {
    int i=line.Find(';');  // �ֺ�֮����ע��
    if(i>=0) line=line.Left(i);	else continue;
	  line.TrimLeft( );  line.TrimRight( );
	  if(line.IsEmpty( )) continue;  // �����п���
	  if(line.Left(1)=="#" && pOpenTags->GetSize( )<10) {
		  // ���ű��ǰ��"#"�����ó���10��
	    line=line.Mid(1);
	    pOpenTags->Add(line);  // ��ӿ�������
		}
	  pTags->Add(line);  // ��Ӵ��Ա��
  }
  tagFile.Close( );
  int n=pTags->GetSize( );  // �����ж��ٸ����
  TagFreqs=new int[n];	   // �������Ƶ������
  Matrix=new int[n * n];     // ������ǹ���Ƶ������
  for(int i=0; i<n; i++) { // ����ֵ
	  TagFreqs[i]=0;
	  for(int j=0; j<n; j++) Matrix[i*n+j]=0;
  }
  CorpusSize=0; Modified=TRUE; 
  line.Format("���� %d �����Ա��", n);
  if(pOpenTags->GetSize( )==0) 
	  line+="\nû�ж��忪���࣬���޷��²��´ʴ���";
  AfxMessageBox(line);
}

void CCoMatrix::Clean( )
{
  if(Modified) { // ������Ͽ��޸Ĺ�
	  CFile tf; char buf[512];
	  if(tf.Open((const char *)FileName, CFile::modeCreate|CFile::modeWrite)) {
		  CArchive ar(&tf, CArchive::store, 512, buf);
		  Serialize(ar); // ����
    }
	}
	 
  if(pTags) delete pTags;  
  if(pOpenTags) delete pOpenTags;
  if(TagFreqs) delete [] TagFreqs;
  if(Matrix) delete [] Matrix;
}

extern CMyDictionary *pDict; // �ʿ�ָ��
void CCoMatrix::AddCorpus(CStdioFile& trainFile)
{  // ������ѵ�������ļ����ı���ÿ��һ�У�
  char line[80];
	
  int n=pTags->GetSize( );
  int lastID=0;  // ������
  while(trainFile.ReadString(line, 80)) { // ѭ������ÿһ��
    CString s(line);
    s.TrimLeft( ); s.TrimRight( );
    
 	CString w,t;
	int i=s.Find(' ');
	if(i<0) { lastID=0; continue; }
	w=s.Left(i);  t=s.Mid(i+1);
	if(w[0]=='#') w=w.Mid(2);  // ȥ����#P���͡�#S��
	if(w.GetLength()==0 || t.GetLength()==0) continue; 
      
	CorpusSize++; // �������Ͽ��ģ
	    
	// if(t[0]=='H') t=t.Mid(1);  // ��HV�ļ���ȥ����һ��
    pDict->Insert(w, t); // �ӵ��ʿ���ȥ
    int curID=GetIndexOf(t); // ���㵱ǰ��ǵ����
    if(curID>0) {
		  TagFreqs[curID]++; // ���Ӹñ�ǵĳ��ִ���
		  if(lastID>=0) Matrix[lastID*n+curID]++; // �������ڱ�ǵĹ��ִ���
    }
    lastID=curID; // ����ǰ�������Ϊǰһ�����
  }
  trainFile.Close( ); // �ر�ѵ�������ļ�
  Modified=TRUE;  // ���Ͽ��޸Ĺ�
}

/*  
void CCoMatrix::AddCorpus(CStdioFile& trainFile)
{  // ������ѵ�������ļ����ı���ÿ��һ�У�
  char line[3000];
	
  int n=pTags->GetSize( );
  while(trainFile.ReadString(line, 3000)) { // ѭ������ÿһ��
    CString s(line);
    s.TrimLeft( ); s.TrimRight( );
    int lastID=0;  // ������
    while(!s.IsEmpty( )) {  // ѭ������ÿһ����
		CString w,t;
	    w=s.SpanExcluding(" "); // ȡ��һ����
	    s=s.Mid(w.GetLength( ));	s.TrimLeft( ); // ��s��ȥ�������
	    int i=w.Find('/');   // �Ҵ������ǵĽ��ޱ��
	    if(i<0) { lastID=0; continue; } // ѵ����������
			
		t=w.Mid(i+1);  w=w.Left(i); // �����������п�
		if(w.GetLength()==0 || t.GetLength()==0) continue; 
      
		CorpusSize++; // �������Ͽ��ģ
	    
		if(t[0]=='H') t=t.Mid(1);  // ��HV�ļ���ȥ����һ��
	    pDict->Insert(w, t); // �ӵ��ʿ���ȥ
	    int curID=GetIndexOf(t); // ���㵱ǰ��ǵ����
	    if(curID>0) {
			  TagFreqs[curID]++; // ���Ӹñ�ǵĳ��ִ���
			  if(lastID>=0) Matrix[lastID*n+curID]++; // �������ڱ�ǵĹ��ִ���
 	    }
	    lastID=curID; // ����ǰ�������Ϊǰһ�����
	}
  }
  trainFile.Close( ); // �ر�ѵ�������ļ�
  Modified=TRUE;  // ���Ͽ��޸Ĺ�
}
*/

IMPLEMENT_SERIAL(CCoMatrix, CObject, 0)
void CCoMatrix::Serialize(CArchive& ar)
{
  if(ar.IsStoring( ) && !Modified) return; // ���δ�޸����������
  if(!ar.IsStoring( )) { // ����Ƕ��룬�Ƚ��������ַ��������Զ����Ǽ�
  	pTags=new CStringArray;
	  pOpenTags=new CStringArray;
  }
  pTags->Serialize(ar);  // ��Ǽ����л�
  pOpenTags->Serialize(ar); // �����������л�
  int n=pTags->GetSize( ); // ������Ǽ��Ĺ�ģ
  if(!ar.IsStoring( )) {  // ����Ƕ��룬�����ڴ��Դ��Ƶ������
		TagFreqs=new int[n];
	  Matrix=new int[n*n];
  }
  if(ar.IsStoring( )) { // ����Ǵ��̣�д����������
		ar << CorpusSize;  
	  for(int i=0; i<pTags->GetSize( ); i++) {
  	  ar << TagFreqs[i];
	    for(int j=0; j<pTags->GetSize( ); j++)
		    ar << Matrix[i*n+j];
	  }
  }
  else {  // ���������������
		ar >> CorpusSize;  
	  for(int i=0; i<pTags->GetSize( ); i++) {
 		  ar >> TagFreqs[i];
	    for(int j=0; j<pTags->GetSize( ); j++) ar >> Matrix[i*n+j];
		}
  }
}

/////////
extern CCoMatrix coMatrix;

void CSpan::GetFrom(CString& s)	// ���ַ�����ȡ���ɸ���
{
  CObArray a;
  s.TrimLeft( ); s.TrimRight( );
  for(uchar i=1; i<20 && !s.IsEmpty( ); i++) { // �ӵ�1���ʿ�ʼ
		Words[i]=s.SpanExcluding(" ");  // ȡ��
		s=s.Mid(Words[i].GetLength( ));
		s.TrimLeft( );
		pDict->GetFreq(Words[i], a);   // ��ʿ�
/*
		if(a.GetSize( )==0) GuessTag(i); // ���û���ҵ���²����
		else {  // ������Ӹ�����Ǽ�����ִ���
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
			if(tmp>0) { // �ȼ���Ƿ�Ϸ����
				Tags[i][j]=tmp; n++; 
				Freqs[i][j]=p->Freq;
			}
		}
		if(n==0) GuessTag(i);


		Tags[i][j]=0;  // 0��ʾ�����ǣ��������������
		  if(j==1) { i++; break; } // ����ô�û�д������壬��ֹͣ

	}
	CurLength=i; // �ʵĸ�����������0����
}
	
void CSpan::GuessTag(char i)	// �²��i���ʵĴ��Ա��
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

void CSpan::Disamb( )	// �ų��������壬���д��Ա�ע
{
  uchar i,j,k, m;		double minFee, tmp;
  for(i=1; i<CurLength; i++) { // ��ÿһ����
		for(j=0; Tags[i][j]>0; j++) { // ������ÿ�����
		  m=11;
		  for(k=0; Tags[i-1][k]>0 ||i==1 && k==0; k++) { // ��ǰһ�ʵ�ÿ�����
			  tmp=coMatrix.GetCoProb(Tags[i-1][k], Tags[i][j]);
				// ת�Ƹ���
			  tmp=-log(tmp);  // ת��Ϊ����
			  tmp+=Freqs[i-1][k]; // �����ۼƷ���
			  if(m>10 || tmp<minFee) {	m=k;  minFee=tmp; } // ȡ��С����
		  }
		  GoodPrev[i][j]=m; // ��j����ǵ����ǰ��
		  tmp=coMatrix.GetWordProb(Freqs[i][j], Tags[i][j]); // �ʵĸ���
		  Freqs[i][j]=minFee+-log(tmp);  // ���ϴʵķ���
		}
	}
}

void CSpan::WriteTo(CStdioFile out) // ������/��Ǵ�д������ļ���ȥ
{
  CString s="";
  for(int i=CurLength-1, j=0; i>0; i--) {
		s=Words[i]+'/'+coMatrix.GetTagOf(Tags[i][j]) + " " +s;
		j=GoodPrev[i][j];
  }
  out.WriteString(s);
}
