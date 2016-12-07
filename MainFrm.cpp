// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "�ִ������Զ�����.h"
#include "myResourceClass.h"
#include "wordtagset.h"
#include "retrieval.h"
#include "taggingPOS.h"
#include "parsing.h"
#include <math.h>
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_DATA_ATTRIBUTES, OnDataAttributes)
	ON_COMMAND(ID_TEST_FILES, OnTestFiles)
	ON_COMMAND(ID_TEST_GET_DATA, OnTestGetData)
	ON_COMMAND(ID_GB2312, OnGb2312)
	ON_COMMAND(ID_SINGLE_HZ, OnSingleHz)
	ON_COMMAND(ID_DOUBLE_HZ, OnDoubleHz)
	ON_COMMAND(ID_SEEK_HZ, OnSeekHz)
	ON_COMMAND(ID_HZ_REPORT, OnHzReport)
	ON_COMMAND(ID_SEGMENT_MM, OnSegmentMm)
	ON_COMMAND(ID_SEGMENT_MP, OnSegmentMp)
	ON_COMMAND(ID_SEGMENT_SENTENCE, OnSegmentSentence)
	ON_COMMAND(ID_BIND_DYNAMIC, OnBindDynamic)
	ON_COMMAND(ID_BIND_SNAPSHOT, OnBindSnapshot)
	ON_COMMAND(ID_CORPUS_CREATE, OnCorpusCreate)
	ON_COMMAND(ID_CORPUS_CLOSE, OnCorpusClose)
	ON_COMMAND(ID_CORPUS_BROWSE, OnCorpusBrowse)
	ON_COMMAND(ID_CORPUS_ADD, OnCorpusAdd)
	ON_COMMAND(ID_CORPUS_HANZI, OnCorpusHanzi)
	ON_COMMAND(ID_CORPUS_OPEN, OnCorpusOpen)
	ON_UPDATE_COMMAND_UI(ID_CORPUS_ADD, OnUpdateCorpusAdd)
	ON_UPDATE_COMMAND_UI(ID_CORPUS_BROWSE, OnUpdateCorpusBrowse)
	ON_UPDATE_COMMAND_UI(ID_CORPUS_CLOSE, OnUpdateCorpusClose)
	ON_UPDATE_COMMAND_UI(ID_CORPUS_HANZI, OnUpdateCorpusHanzi)
	ON_COMMAND(ID_RETRIEVE_HZSTR, OnRetrieveHzstr)
	ON_UPDATE_COMMAND_UI(ID_RETRIEVE_HZSTR, OnUpdateRetrieveHzstr)
	ON_COMMAND(ID_TAGGING_TAGGING, OnTaggingTagging)
	ON_COMMAND(ID_TAGGING_TAGSET, OnTaggingTagset)
	ON_COMMAND(ID_TAGGING_TRAIN, OnTaggingTrain)
	ON_COMMAND(ID_PARSING_BOTTOMUP, OnParsingBottomup)
	ON_COMMAND(ID_PARSING_PCFG, OnParsingPcfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction
void LoadHZFreq(), StoreHZFreq(), LoadNameZi();

CMyDictionary *pDict;  

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	LoadHZFreq();	
	pDict=new CMyDictionary;
	LoadNameZi();
}

BOOL ADD_HANZI=FALSE;

CMainFrame::~CMainFrame()
{
	if(ADD_HANZI) StoreHZFreq();
	if(pDict) delete pDict;
	OnCorpusClose();
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMDIFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnDataAttributes() 
{
	// TODO: Add your command handler code here
	CFileAttributes dlg;
	dlg.DoModal();
}

void CountLinesInAFile(CString fname)
{
  FILE *in;  CString  msg;
  in=fopen((const char *)fname, "rb");
  if(!in) { AfxMessageBox("�ļ��򲻿���");	return; }
	int count=0;
  while(!feof(in)) {
		char ch=fgetc(in);
		if(ch=='\n') count++;
  }
	fclose(in);
  msg.Format("%s: ����%d��", (const char *)fname, count);
	AfxMessageBox(msg);	
}

void CMainFrame::OnTestFiles() 
{
	// TODO: Add your command handler code here
	ProcessFiles(CountLinesInAFile);
	// ��ͨ���ѡ���ļ�
	ProcessFiles("txt", "*.txt", CountLinesInAFile);
	// �öԻ���ѡ���ļ�
}

void CMainFrame::OnTestGetData() 
{
	// TODO: Add your command handler code here
	CString s, msg;  int i;  double d;
  if(GetData("����һ���ַ�����", s)) 
	  AfxMessageBox("������ַ����ǣ�"+s);
	else AfxMessageBox("��û�������ַ�����");
	if(GetData("����һ��������", i)) {
	  msg.Format("���������Ϊ%d", i);
	  AfxMessageBox(msg);
	}
	else AfxMessageBox("��û������������");
	if(GetData("����һ��ʵ����", d)) {
	  msg.Format("�����ʵ��Ϊ��%7.2f", d);
	  AfxMessageBox(msg);
	}
	else AfxMessageBox("��û������ʵ����");
}

void CMainFrame::OnGb2312() 
{
	// TODO: Add your command handler code here
	// ���������ַ���
  FILE *outFile;  // ����ļ�
  unsigned char i, j;
  outFile=fopen("gb2312-80.chr", "wt");
  for ( i=161; i<255; i++)
		for ( j=161; j<255; j++)
	    fprintf ( outFile, "%c%c  %d  %d\n", i, j, i, j);
  fclose (outFile);
	AfxMessageBox("�����ɹ����ַ����ļ���gb2312-80.chr");
  return;
}

#define  HZ_NUM	6768
#define  HZ_ID(c1,c2) 	((c1)-176)*94 + ((c2)-161)
	// ���㺺���±�ĺ�
int  HZFreq[HZ_NUM];

struct  NameZi {
	int  sName,  gName;
} namezis[HZ_NUM];

void  hzInFile (CString FileName)
{
  FILE *in;		unsigned char  c1, c2;		int id;
  in=fopen((const char *)FileName, "rb");
  if(in==NULL) {	AfxMessageBox("�޷��������ļ�");  return;  }
  while (!feof (in)) {
		c1=(unsigned char ) fgetc(in);	// ת��Ϊ�޷����ַ�
		if(c1<128) continue;	// �������ֽ������ַ�
		if(c1<176) { c2=fgetc(in); continue; } // Ҳ������Ǻ����ַ�����Ҫ���һ���ֽ�
		c2=(unsigned char ) fgetc(in);	// ���뺺�ֵĵڶ����ֽ�
		id=HZ_ID(c1,c2);	// ����ú��ֵ��±�
		HZFreq[id]++;		// ���ú��ֵ�Ƶ�ȼ�1
  }
  fclose(in);	return;
}

void CMainFrame::OnSingleHz() 
{
	// ������Ƶͳ��
	for(int i=0; i<HZ_NUM; i++) HZFreq[i]=0;
	ProcessFiles(hzInFile);
	FILE *outFile;
  outFile=fopen("hzfreq.txt", "wt");
  for(int id=0; id<HZ_NUM; id++)
  	if(HZFreq[id]>0)
      fprintf(outFile, "%c%c\t%d\n", id/94+176, id%94+161, HZFreq[id]);
	fclose(outFile);	
	return;
}

CSortedPairs hzPairs; // �ٶ�����̬������Ķ������ڱ���ļ��ж���

void LoadHZFreq( )
{
	char buf[512];
	FILE *in;
	CFile inFile;

	if(inFile.Open("hzpairs.dat", CFile::modeRead)) {
	  CArchive ar(&inFile, CArchive::load, 512, buf); // ����Ϊװ��ģʽ
	  hzPairs.Serialize(ar);	// ���ļ��ж���˫���ֱ�
	  inFile.Close( );
	}

	in=fopen("hzfreq.dat", "rb");
	if(in) {
		fread(HZFreq, sizeof(int), HZ_NUM, in);
		fclose(in);
	}
	else for(int i=0; i<HZ_NUM; i++) HZFreq[i]=0;
}

void StoreHZFreq( )
{
	char buf[512];
	FILE *out;
	CFile outFile;
	if(outFile.Open("hzpairs.dat", CFile::modeWrite|CFile::modeCreate)) {
		CArchive ar(&outFile, CArchive::store, 512, buf); // ����Ϊ���ģʽ
		hzPairs.Serialize(ar);	// ��˫���ֱ�д���ļ�
	}
	out=fopen("hzfreq.dat", "wb");
	if(out) {
		fwrite(HZFreq, sizeof(int), HZ_NUM, out);
		fclose(out);
	}
}

void LoadNameZi()
{
	FILE *in;
	in=fopen("namezis.txt", "rt");
	if(!in) { AfxMessageBox("�޷����ļ� namezis.txt"); return; }
	char s[20], *p;
	for(int i=0; i<HZ_NUM && fgets(s, 20, in); i++) {
		p=strchr(s, ' ');   *p='\0';	p++; 
		namezis[i].sName=atoi(s);
		namezis[i].gName=atoi(p);
	}
	fclose(in);
}

void HZPairInFile(CString FileName)
{
  FILE *in;
  unsigned char  c1, c2;
	char zz[5];		
  int id;
  in=fopen((const char *)FileName, "rb");
  if(in==NULL) {	AfxMessageBox("�޷��������ļ�");  return;  }
	zz[0]='\0';
	while(!feof(in)) {
		c1=(unsigned char)fgetc (in);	
		if(c1<128) { zz[0]='\0'; continue; } // �����������ַ�
		else if(c1<176) { c2=fgetc(in); zz[0]='\0'; continue; } // Ҳ������Ǻ��ֵ�˫�ֽ��ַ�
		c2=(unsigned char)fgetc(in);	
		id=HZ_ID(c1, c2);	// ���㺺������Ӧ���±�
		HZFreq[id]++;		// �����ǵǼǵ�����Ƶ�������ǵǼ�˫����Ƶ
		if(zz[0]!='\0') { // �����ǰ�Ѿ�ȡ������
		  zz[2]=c1; zz[3]=c2; // ����ǰ����д�ڵڶ���λ��
	    hzPairs.Insert (zz);	// ���������Լ���д�ĺ���������˫��
		}			
		zz[0]=c1; zz[1]=c2; 	// ����ǰ����д����һ��λ��
	}
	fclose(in);	return;
}

void CMainFrame::OnDoubleHz() 
{
	// TODO: Add your command handler code here	
	int n=ProcessFiles("snt", "*.snt", HZPairInFile); // ͳ�Ƴ����ļ��е�˫��
	if(n>0) ADD_HANZI=TRUE;
}

void CMainFrame::OnSeekHz() 
{
	// TODO: Add your command handler code here
	CString key, msg;
	if(!GetData("����Ҫ�ҵĵ��ֻ�˫�֣�", key)) return;
	key.TrimRight(); 
	key.TrimLeft();
	int id,  n= key.GetLength( );
	if(n==2) {	// ������뵥��
	  id=HZ_ID((unsigned char)key[0], (unsigned char)key[1]);
		msg.Format("�ú��ֳ���%d��", HZFreq[id]);
	}
	else {	// �������˫��
		if(hzPairs.Search((const char *)key, id)) {
		  HZPair *hp=(HZPair *)hzPairs.GetAt(id);
		  msg.Format("��˫�ֳ���%d��", hp->freq);
		}
	}
	if(msg.IsEmpty( )) msg="�Ҳ����������������";
	AfxMessageBox(msg);
}

void CMainFrame::OnHzReport() 
{
	// TODO: Add your command handler code here
	int hzCount=0,	 CorpusSize=0;
	for (int id=0; id<HZ_NUM; id++) {
		if(HZFreq[id]>0) { // ֻ������ֹ��ĺ��ֵ���Ϣ
		  hzCount++;
		  CorpusSize+=HZFreq[id];
		}
	}
	CString msg;
	msg.Format("��ͳ�����Ϲ�%d�֣�\n���в�ͬ����%d����\n��ͬ˫��%d��", CorpusSize, hzCount, hzPairs.GetSize( ));
	AfxMessageBox(msg);
}

#define MaxWordLength 8  // ���ʳ�Ϊ8����4�����֣�
#define Separator " "		 // �ʽ���

CString  SegmentHzStrMM (CString s1)
{
  CString s2="";	    // ��ŷִʽ������ʼ��Ϊ�մ�
  while(!s1.IsEmpty( )) {	    // �����봮δ������ʱ
		int len=s1.GetLength( );		// �����봮�ĵ�ǰ����
		if (len > MaxWordLength) len=MaxWordLength; // ����4������ʱֻȡ4��
    CString w=s1.Left(len);   // ����߸����Ӵ�����ѡ�ʣ�
		while(len>2 &&  pDict->GetFreq(w )== -1) { 
      // ����ѡ�ʲ�ֹһ�����ֶ���ƥ��ʧ��ʱ
		  len-=2;  w=w.Left(len);  // �Ӻ�ѡ���ұ߼���һ������
		}
		s2+=w + Separator;  // ��ƥ�䵽�Ĵʣ���ʣ�µ�һ���֣�
		// ��ͬ�ʽ��Ǽӵ������ĩβ
		s1=s1.Mid(w.GetLength()); // �����봮���ȥ�������
  }
  return s2;
}

CString  SegmentSentenceMM (CString s1)
{
  CString s2=""; // �����
  int i;
  while(!s1.IsEmpty( )) {
		unsigned char ch=(unsigned char)s1[0];			
		if(ch<128) {  // �����ַ�
  	  i=1;
		  while(i<s1.GetLength() && (unsigned char)s1[i]<128) i++;
		  s2+=s1.Left(i)+Separator;
		  s1=s1.Mid(i);
		  continue;
		}
		else if(ch<176) {	// ���ı����ַ�
		  s2+=s1.Left(2)+Separator;
  	  s1=s1.Mid(2);
		  continue;
		}
		// ���´����ִ�	
		i=2;
		while((unsigned char)s1[i]>=176) i+=2;
		s2+=SegmentHzStrMM(s1.Left(i));  // �������ƥ�䷨�ִʺ���
		s1=s1.Mid(i);
  }	
  return s2;
}

void SegmentAFileMM(CString FileName)
{
	FILE *in, *out;
	in=fopen((const char *)FileName, "rt");
	if(in==NULL) { AfxMessageBox("�޷����ļ�");	return; }
	FileName = ChangeExt(FileName, "cut"); 
	out=fopen((const char *)FileName, "wt");
	if(out==NULL) { AfxMessageBox("�޷������ļ�");	fclose(in);	return; }
	CStdioFile inFile(in), outFile(out);

	char s[2048];
	CString line; 
	while(inFile.ReadString(s, 2048)) {	// ѭ������ÿһ��
		line=s;
		line=SegmentSentenceMM(line);
		outFile.WriteString(line);
	}
	inFile.Close( ); outFile.Close( );
}

void CMainFrame::OnSegmentMm() 
{
	// TODO: Add your command handler code here
	ProcessFiles("sen", "*.sen", SegmentAFileMM);
}

const int CorpusSize=200000;
const int SurNameSize=174000;
const int GivenNameSize=320000;

struct Candidate {	// ��ź�ѡ����Ϣ�Ľṹ
  short  offset, length; // ��ѡ�������봮�е���㣬����
  short  goodPrev;       // ���ǰ���ʵ����
  float fee, sumFee;   // ��ѡ�ʵķ��ã�·���ϵ��ۼƷ���
} Candidates[100];  // �ٶ����100����ѡ��

short getTmpWords(CString& s)
{
  short i=0, j, len, freq, n=s.GetLength( );
	CString w;
  for(j=0; j<n; j+=2) { // ��ÿһ������Ϊ���
    for(len=2; len<=MaxWordLength; len+=2) { // ����Ϊ1��MaxWordLength/2����
			w=s.Mid(j, len);
      freq=pDict->GetFreq(w); 
		  if(len>2 && freq==-1) continue; // ����ֹһ���Ҵʱ����Ҳ��������¼
		  if(freq==-1) freq=0; // ��Ϊ�����Ҵʱ����Ҳ���������ִ���Ϊ0
		  Candidates[i].offset=j; // �ú�ѡ���ں��ִ��е����
		  Candidates[i].length=len;	// �ú�ѡ�ʵĳ���
		  Candidates[i].fee=-log((double)(freq+1)/CorpusSize); // �ú�ѡ�ʵķ���
			// ʹ��log( )�����������ʵ��ط�����ͷ�ļ�math.h
			// CorpusSize�����Ͽ��ģ���Դ�Ϊ��λ�����˳��������ʵ��ط�����
			Candidates[i].sumFee=0.0F;  // �ó�ֵ
		  i++;
		}
	}
	return i;
}

void getPrev(short i)	
{
  if(Candidates[i].offset==0) { // ����Ǻ��ִ��е��״�
    Candidates[i].goodPrev = -1;  // ��ǰ����
    Candidates[i].sumFee = Candidates[i].fee; // �ۼƷ���Ϊ�ôʱ������
    return;
  }
  //  ����
  short j, minID = -1;  // minID�����ǰ�������
  for(j=i-1; j>=0; j--) // ����Ѱ���������ĵ�һ��ǰ����
    if(Candidates[j].offset+Candidates[j].length==Candidates[i].offset)  break;
  for(;Candidates[j].offset+Candidates[j].length==Candidates[i].offset;j--) 
    // ǰ�������������е�
    if(minID == -1 || Candidates[j].sumFee < Candidates[minID].sumFee) minID=j;
  Candidates[i].goodPrev = minID; // �Ǽ����ǰ�������
  Candidates[i].sumFee = Candidates[i].fee + Candidates[minID].sumFee;
		// �Ǽ���С�ۼƷ���
	return;
}

double sFee(CString  z)
{
  int wFreq = pDict->GetFreq (z);  // ��Ϊ���ִʵĳ��ִ���
  if(wFreq == -1) wFreq=0;
  double wFee = -log((double)(wFreq+1)/CorpusSize);  // ��Ϊ���ִʵķ���
  int id=HZ_ID((unsigned char)z[0], (unsigned char)z[1]);
  if(id>=0 && id<HZ_NUM && namezis[id].sName>0) // �����һ����������
		return -log((double)(namezis[id].sName+1)/SurNameSize) - wFee;
	else  return 20.0; // ����һ�����߷��ã�ʹ���ֲ����ܱ���Ϊ����
}

double gFee (CString  z)
{
  int wFreq = pDict->GetFreq(z);  // ��Ϊ���ִʵĳ��ִ���
  if(wFreq == -1) wFreq=0;
  double wFee = -log((double)(wFreq+1)/CorpusSize);  // ��Ϊ���ִʵķ���
  int id=HZ_ID((unsigned char)z[0], (unsigned char)z[1]);
  if(id>=0 && id<HZ_NUM) {   // ����Ǻ���
		if(namezis[id].gName>0) // �����һ����������
		  return -log((double)(namezis[id].gName+1)/GivenNameSize) - wFee;
		else return  -log10(1/GivenNameSize) - wFee;
			//  ��Ϊ�����κκ��ֶ��п�����Ϊ��������
	}
  else return 20.0; // �Ǻ��ֲ�������Ϊ��������
}

double sgFee(CString sg)
{
  double fee=pDict->GetFee(sg, TRUE); // ����ȫ��
  if(fee < 20.0) return fee;  // ����ҵ��ˣ����������
  if(sg.GetLength( )==4) {	
 		fee=pDict->GetFee(sg, FALSE); // �������ֲ��֣���"Сƽ"
   	if(fee < 20.0) return fee;	// ����ҵ��ˣ����������
  }       
  fee=sFee(sg.Left(2)) + gFee(sg.Mid(2,2)); // ���Ϻ��������ַ���
  if(sg.GetLength( )==4) fee += -log(0.37); // ���ϵ�������
  else fee += gFee(sg.Right(2)) + (-log(0.63)); 
 	// ���������ڶ��ַ��ú�˫������
  return fee ;  // �����ܷ���
}

class CMaybeName : public CObject {
public:
  short offset, length;  // ��㡢����
  double fee;		 // ����
  CMaybeName(short off, short len, double f) { offset=off; length=len; fee=f; }
} ;

#define Max2Fee   -2.14
#define Max3Fee   -0.80
BOOL  isHomoPair (CMaybeName *p1, CMaybeName *p2)
{
  if (p1->offset==p2->offset) return TRUE;
  else return FALSE;
}

BOOL  isCrossPair (CMaybeName *p1, CMaybeName *p2)
{
  if (p1->offset==p2->offset   // �����ͬԴ��
		|| p1->offset+p1->length<=p2->offset	// ����û���ص�����
		|| p2->offset+p2->length<=p1->offset)  
		return FALSE;		// �Ͳ��ǽ����
	else  return TRUE;
}

CString CheckStr (CString  s1)
{
  CObArray maybeNames;  // Ԫ��ΪCMaybeName���͵�ָ��
  CMaybeName *p, *p1, *p2;  
  int i, j, len;
  for(i=0; i<s1.GetLength( ); i+=2) {
  	for (len=4; len<=6 && i+len<=s1.GetLength(); len+=2) { // �ҳ���ѡ����
		  double fee=sgFee(s1.Mid(i, len));
		  if(len==4 && fee>=Max2Fee || len>=6 && fee>=Max3Fee) continue;
		  p=new CMaybeName(i,len,fee);
		  maybeNames.Add(p);
		}
	}
	BOOL iDeleted=FALSE;
	for(i=0; i<maybeNames.GetSize( ); ) {
		for ( j=i+1; j<=i+2 && j<maybeNames.GetSize( ); ) {
		  p1=(CMaybeName *)maybeNames[i];
		  p2=(CMaybeName *)maybeNames[j];
		  if(isHomoPair(p1, p2)) {
		    if(p1->fee > p2->fee) { // || p2->fee - p1->fee<0.2) {
					maybeNames.RemoveAt(i);  
					iDeleted=TRUE;  break;
				}
				else maybeNames.RemoveAt(j);
		  }
		  else if (isCrossPair(p1,p2)) {
				if (p1->fee <= p2->fee) maybeNames.RemoveAt(j);
				else { maybeNames.RemoveAt(i); iDeleted=TRUE; break; }
		  }
		  else j++;
		}
	  if (! iDeleted) i++;
		else iDeleted=FALSE;
	}
	// ���������µĴʴ�
	CString s2="";
	if(maybeNames.GetSize( )==0) {  // ���û�з�������
  	for(i=0; i<s1.GetLength( ); i+=2) s2 += s1.Mid(i,2)+Separator;
  	return s2;
	}

  for(i=0; i<maybeNames.GetSize( ); i++) {
		if(i==0) j=0;		else j=p->offset + p->length;  
		p=(CMaybeName *)maybeNames[i]; 
		for(; j<p->offset; j+=2) s2 += s1.Mid(j,2)+Separator;
		// ��������֮ǰ�ĵ��ִ�
		CString w= s1.Mid(p->offset, p->length);
		s2 += w+Separator; // ���ϸ�����
		CString sName=w.Left(2), gName=w.Mid(2);
		pDict->Insert(sName, gName, p->fee); // ����������
	} 
	for(j=p->offset+p->length; j<s1.GetLength( ); j+=2) 
    s2 += s1.Mid(j,2)+Separator; // �������һ������֮��ĵ��ִ�
	
	return s2;
}

CString  SegmentHzStrMP (CString  s1)
{
  int len=s1.GetLength( );
  short n=getTmpWords(s1); // ȡ��s1�е�ȫ����ѡ�ʣ�
  short minID=-1;      //����С����·�����յ�ʵ����Ϊ-1
  short i;
  for(i=0; i<n; i++) {  //ѭ������ÿһ��ѡ����:  
  	getPrev(i);   // ��д���ǰ������š���ǰ����С�ۼƷ���
  	if(Candidates[i].offset+Candidates[i].length==len) {
    // �����ǰ����s1��β�ʣ�
      if(minID==-1||Candidates[i].sumFee<Candidates[minID].sumFee) minID=i;
      //����ǵ�һ��������β�ʣ����ߵ�ǰβ�ʵ���С�ۼƷ���С���Ѿ���������
			//��һβ�ʵ���С�ۼƷ��ã�������Ÿ���minID
   	}
  }
  CString s2="";  //  �������ʼ��  
	CString tmp=""; //  ���ִʴ���ʼ��
  for(i=minID; i>=0; i=Candidates[i].goodPrev)  {
		CString w=s1.Mid(Candidates[i].offset, Candidates[i].length);
		if(w.GetLength()==2) tmp=w+tmp;  // ����ǵ��ִʣ��ӵ�tmp��ȥ
		else { // �����ȴ����ǰ��tmp
			if(tmp.GetLength()>0) {
				if(tmp.GetLength()==2) s2=tmp+Separator+s2;
				else s2=CheckStr(tmp)+Separator+s2;
				tmp="";
			}
			s2=w+Separator+s2; // ���ϵ�ǰ�ķǵ��ִ�
		}
	}	
	if(tmp.GetLength()>0) { // ����λ��s1����ߵĵ��ִʴ�
		if(tmp.GetLength()==2) s2=tmp+Separator+s2;
		else s2=CheckStr(tmp)+Separator+s2;
		tmp="";
	}
	//  ע�⣺����ȡ����Ĵ�          
  return s2;  // ��������ʴ�
}

CString  SegmentSentenceMP (CString s1)
{
  CString s2=""; // �����
  int i;
  while(!s1.IsEmpty( )) {
		unsigned char ch=(unsigned char)s1[0];			
		if(ch<128) {  // �����ַ�
  	  i=1;
		  while(i<s1.GetLength() && (unsigned char)s1[i]<128) i++;
		  s2+=s1.Left(i)+Separator;
		  s1=s1.Mid(i);
		  continue;
		}
		else if(ch<176) {	// ���ı����ַ�
		  s2+=s1.Left(2)+Separator;
  	  s1=s1.Mid(2);
		  continue;
		}
		// ���´����ִ�	
		i=2;
		while((unsigned char)s1[i]>=176) i+=2;
		s2+=SegmentHzStrMP(s1.Left(i));  // ���������ʷ��ִʺ���
		s1=s1.Mid(i);
  }	
  return s2;
}

void SegmentAFileMP(CString FileName)
{
	FILE *in, *out;
	in=fopen((const char *)FileName, "rt");
	if(in==NULL) { AfxMessageBox("�޷����ļ�");	return; }
	FileName = ChangeExt(FileName, "cut"); 
	out=fopen((const char *)FileName, "wt");
	if(out==NULL) { AfxMessageBox("�޷������ļ�");	fclose(in);	return; }
	CStdioFile inFile(in), outFile(out);

	char s[2048];
	CString line; 
	while(inFile.ReadString(s, 2048)) {	// ѭ������ÿһ��
		line=s;
		line=SegmentSentenceMP(line);
		outFile.WriteString(line);
	}
	inFile.Close( ); outFile.Close( );
}

void CMainFrame::OnSegmentMp() 
{
	// TODO: Add your command handler code here
	ProcessFiles("sen", "*.sen", SegmentAFileMP);
}

void CutSentence(CString FileName)
{  // �����ļ��ĶϾ亯��
	FILE *in, *out;
	in=fopen((const char *)FileName, "rt");
	if(in==NULL) { AfxMessageBox("�޷����ļ�");	return; }
	FileName = ChangeExt(FileName, "sen"); 
	out=fopen((const char *)FileName, "wt");
	if(out==NULL) { AfxMessageBox("�޷������ļ�");	fclose(in);	return; }
	CStdioFile inFile(in), outFile(out);

	char s[2048];
	CString line; int i, n;
	while(inFile.ReadString(s, 2048)) {	// ѭ������ÿһ��
		line=s;
		n=line.GetLength( );  // ���¸��е�ԭ�г���
		while((i=GetSentence(line))>0) { // ֻҪ�����˾���
		  outFile.WriteString(line.Left(i)+'\n'); // д������ļ�
		  line=line.Mid(i);	// ������ȥ���������
		}
		if(!line.IsEmpty( )) {	// ������л����ַ�
		  if(n==line.GetLength( ) && n<60) // ��������޾�ĩ����ҽ϶�
			  outFile.WriteString(line+'\n'); // ����һ���ޱ��ľ���
			else outFile.WriteString(line);	// ����ʣ�µ��ַ�д���ļ�
		}
	}
	inFile.Close( ); outFile.Close( );		
}

void CMainFrame::OnSegmentSentence() 
{
	// TODO: Add your command handler code here
	ProcessFiles("*", "*.*", CutSentence); // ���ö��ļ�������
}

void CMainFrame::OnBindDynamic() 
{
	// ��̬����
	CString w, msg;  CObArray a;
	if(!GetData("��������ҵĴʣ�", w)) return;
	int i, n=pDict->GetFreq(w, a);
	if(n==0) AfxMessageBox("�ʿ���û�������");
	else {
		msg=w+":\n";		CTagFreq *pt;
		for(i=0; i<n; i++) {
			pt=(CTagFreq *)a.GetAt(i);
			w.Format("��ǣ�%s�����ִ�����%d\n", pt->Tag, pt->Freq);
			msg+=w;
		}
		AfxMessageBox(msg);
	}
}

void CMainFrame::OnBindSnapshot() 
{
	// ��̬����
	CWordTagSet *pSet=new CWordTagSet;
	pSet->Open();
	if(!pSet->IsOpen()) {
		AfxMessageBox("can not open snapshot");
		return;
	}
	CString w, msg;  CObArray a;
	if(!GetData("��������ҵĴʣ�", w)) return;
	int i, n=pSet->GetFreqs(w, a);
	if(n==0) AfxMessageBox("�ʿ���û�������");
	else {
		msg=w+":\n";		CTagFreq *pt;
		for(i=0; i<n; i++) {
			pt=(CTagFreq *)a.GetAt(i);
			w.Format("��ǣ�%s�����ִ�����%d\n", pt->Tag, pt->Freq);
			msg+=w;
		}
		AfxMessageBox(msg);
	}
	delete pSet;
}

//  �ִʼ���
CString corpusName="";   		// ���Ͽ���
CStringArray texts; 			// �����ļ�������
BOOL CorpusModified=FALSE; 	// ��ʾ��ǰ���Ͽ��Ƿ��޸Ĺ�
CHzInfo hzInfo[6768];

void CMainFrame::OnCorpusCreate() 
{
	// TODO: Add your command handler code here
	CFileDialog dlg(FALSE); // ��ȡ���Ͽ�����ļ���
	if(dlg.DoModal( )!=IDOK) return;
	if(!corpusName.IsEmpty( )) OnCorpusClose( ); // �رյ�ǰ���Ͽ�
	corpusName=dlg.GetPathName( );
	OnCorpusAdd( );  // �������
}

void CMainFrame::OnCorpusClose() 
{
	// TODO: Add your command handler code here
	if(corpusName.IsEmpty( )) return; 
		// ������޴򿪵����Ͽ⣬�򷵻�	
	if(CorpusModified) { // ������Ͽ������޸�
		CFile cf; char buf[512];
		if(cf.Open((const char *)corpusName, 
         CFile::modeCreate | CFile::modeWrite)) {
			CArchive ar(&cf, CArchive::store, 512, buf );
			texts.Serialize(ar);
		}
		else { AfxMessageBox("���Ͽ��޷����̣�"); return; }
		texts.RemoveAll( ); // ������������ļ���
		CFile tf;
		CString ylkName=ChangeExt(corpusName, "@@@");
		if(tf.Open((const char *)ylkName, 
			CFile::modeCreate |CFile::modeWrite)) {
			CArchive ar(&tf, CArchive::store, 512,buf);
			for(int i=0; i<6768; i++) hzInfo[i].Serialize(ar);
		}
		else { AfxMessageBox("������Ϣ�޷����̣�"); return; }  
	}
	corpusName="";
	CorpusModified=FALSE;
}


void CMainFrame::OnCorpusBrowse() 
{
	// TODO: Add your command handler code here
	if(corpusName.IsEmpty( )) return;
	CTitlesDlg dlg;	dlg.DoModal( );
}

void AddAFile(CString FileName)
{
  int n=texts.GetSize( );	 if(n==65535) return;
	FILE *in;	 in=fopen((const char *)FileName, "rb");
	if(!in) { AfxMessageBox("�򲻿��ļ� "+FileName); return; }
	while(!feof(in)) {
	  unsigned char c1, c2;
	  c1=(unsigned char)fgetc(in);   
    if(c1<128) continue; // �����������ַ�
	  c2=(unsigned char)fgetc(in);
	  if(c1>=176) {  // ����Ǻ���
		  int id=HZ_ID(c1,c2);  if(id<0 || id>=6768) continue;
		  hzInfo[id].AddTextID(n); // �������ļ���ż����ַ��
	  }
	}
	fclose(in);
	FileName.MakeLower( );  // ���ļ����е���ĸתΪСд
	texts.Add(FileName);   // ���ļ�����ӵ��ַ�������
	CorpusModified=TRUE;   // �������Ͽ��޸ı��
}

void CMainFrame::OnCorpusAdd() 
{
	// TODO: Add your command handler code here
	if(corpusName.IsEmpty( ) || texts.GetSize( )==65535) return;
  ProcessFiles("txt", "*.txt", AddAFile);
}

void CMainFrame::OnCorpusHanzi() 
{
	// TODO: Add your command handler code here
	if(corpusName.IsEmpty( )) return;
  CHzCountDlg dlg;	
	dlg.DoModal( );
}

void CMainFrame::OnCorpusOpen() 
{
	// TODO: Add your command handler code here
	CFileDialog dlg(TRUE, "ylk", "*.ylk",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"���Ͽ��ļ�|*.ylk|�����ļ�||"); // ���Ͽ�����ļ�
	if(dlg.DoModal()!=IDOK) return;
	if(!corpusName.IsEmpty()) OnCorpusClose();
	// �����ǰ�Ѿ�����һ�����Ͽ⣬�ȹر���
	CFile cf;  char buf[512];
	if(cf.Open((const char *)(dlg.GetPathName()), CFile::modeRead)) {
		CArchive ar(&cf, CArchive::load, 512, buf);
		texts.Serialize(ar);	// �������������ļ���
	}
	else { AfxMessageBox("�޷������Ͽ⣡"); return; }

	CFile tf; 
	CString ylkName=ChangeExt(dlg.GetPathName(), "@@@");
	if(tf.Open((const char *)ylkName, CFile::modeRead)) {
		CArchive ar(&tf, CArchive::load, 512,buf);
		for(int i=0; i<6768; i++) hzInfo[i].Serialize(ar);
		// ����ÿ�����ֵ���Ϣ�����ִ����͵�ַ����
	}
	else { AfxMessageBox("�޷����뺺����Ϣ��"); return; }
	corpusName=dlg.GetPathName();	// �������Ͽ��ļ���
	CorpusModified=FALSE;  // ���Ͽ��޸ı��
}

void CMainFrame::OnUpdateCorpusAdd(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(corpusName.IsEmpty( ) ? FALSE : TRUE);	
}

void CMainFrame::OnUpdateCorpusBrowse(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(corpusName.IsEmpty( ) ? FALSE : TRUE);	
}

void CMainFrame::OnUpdateCorpusClose(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(corpusName.IsEmpty( ) ? FALSE : TRUE);	
}

void CMainFrame::OnUpdateCorpusHanzi(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(corpusName.IsEmpty( ) ? FALSE : TRUE);	
}

BOOL GoodHzStr(CString& s)
{
  int n=s.GetLength( );
  if(n==0 || n%2!=0) return FALSE; 
  for(int i=0; i<n-1; i+=2) 
	if((unsigned char)s[i]<176 || (unsigned char)s[i+1]<161) return FALSE;
  return TRUE;	
}

CWordArray *Intersection(CWordArray &wi, CWordArray &wj)
{
	  CWordArray *pw=new CWordArray;  // ����ָ��
	  for(int i=0, j=0; i<wi.GetSize( ) && j<wj.GetSize( ); ) {
		if(wi[i]==wj[j]) { pw->Add(wi[i]); i++; j++; } // ������ͬ��ַ
		else if(wi[i]<wj[j]) i++;
		else j++;
	  }
	  return pw;
}

void Retrieve(CWordArray *txtID, CString& key)
{
  if(txtID->GetSize( )==0) return;
  FILE *in, *out;	int Examples=0;
  out=fopen("output.txt", "wt");
  if(!out) { AfxMessageBox("�޷�������������ļ���"); return; }
  CStdioFile outFile(out);
  outFile.WriteString("���Һ��ִ�����");
  outFile.WriteString(key+"��\n");
  for(int i=0; i<txtID->GetSize( ); i++) {
		int id=txtID->GetAt(i); // ȡ��һ����ַ
		CString fname=texts[id];  // ȡ����Ӧ�������ļ���
		in=fopen((const char *)fname, "rt");
		if(!in) { AfxMessageBox("�Ҳ��������ļ� "+fname); continue; }
		CStdioFile inFile(in);
		char s[3000]; CString ss="", dd;
		while(inFile.ReadString(s, 3000)) // �������ļ���ÿһ��
	 	  if(key.GetLength( )>2 && strstr(s,(const char *)key)
				|| key.GetLength( )==2 && FindOneHZ(s, (const char *)key)>=0){  
			// ������иú��ֻ��ߺ��ִ�
			  Examples++;  // ���Ӹ���
			  dd.Format("��%04d�� ", Examples);
			  ss+=dd+s;  ss+='\n';		// �ӵ��������
		  }
		if(ss.GetLength( )>0) {  // ����������Ϊ��
		  outFile.WriteString(fname+":\n"); // д�ļ���
		  outFile.WriteString(ss+"\n");     // д�����
		}
		inFile.Close( ); 
	}
	outFile.Close( );
	if(Examples>0) AfxGetApp( )->OpenDocumentFile("output.txt");
		// ��Ӧ�ó����д�����ļ�
	else AfxMessageBox("�Ҳ���������ִ���"); 
}

void CMainFrame::OnRetrieveHzstr() 
{
	// TODO: Add your command handler code here
	CString key;
	if(!GetData("���Һ��ִ���", key)) return;
	key.TrimLeft( );  key.TrimRight( ); // ѹ��ǰ��ո�
	int id, id2, n=key.GetLength( );
	if(!GoodHzStr(key)) { // �������ĺϷ���
		AfxMessageBox("����ĺ��ִ��д���");
		return;
	}
	CWordArray *txtID, *tmp;
	id=HZ_ID((unsigned char)key[0],(unsigned char)key[1]);
	if(n==2) { // ���������ǵ�������
		txtID=&(hzInfo[id].TextID);
		if(txtID->GetSize( )==0) {
      AfxMessageBox("�Ҳ���������ִ�");
		  return;
		}
		Retrieve(txtID, key);  // �ڵ�txtID�������ļ��м�������key
		return;
	}
		// ���´������������ֵ����
	id2=HZ_ID((unsigned char)key[2],(unsigned char)key[3]); 
	  // �ڶ�������
	txtID=Intersection(hzInfo[id].TextID, hzInfo[id2].TextID);
		// ��ǰ�������ֵĵ�ַ���Ľ���
	int i=4;  // �ӵ��������ֿ�ʼ
	while(txtID->GetSize( )>0 && i<key.GetLength( )-1) {
		id2=HZ_ID((unsigned char)key[i],(unsigned char)key[i+1]);
		tmp=Intersection(*txtID, hzInfo[id2].TextID);
		delete txtID;  txtID=tmp;	i+=2;
	}
	if(txtID->GetSize( )==0) {  // �������Ϊ��
	  AfxMessageBox("�Ҳ���������ִ�");
	  return;
	}
	Retrieve(txtID, key);  // �ڵ�txtID�������ļ��м������ִ�key
  delete txtID; return;
}

void CMainFrame::OnUpdateRetrieveHzstr(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(corpusName.IsEmpty( ) ? FALSE : TRUE);	
}

//  TAGGING

CCoMatrix  coMatrix;

void TaggingFile(CString fileName)
{ // ��һ���ļ����д��Ա�ע
  FILE *in, *out;
  in=fopen((const char *)fileName, "rt");
  if(!in) {	AfxMessageBox("�޷��������ļ�"+fileName);	return;	}
	out=fopen((const char *)ChangeExt(fileName,"pos"), "wt");
	if(!out) { AfxMessageBox("�޷��������Ա�ע�ļ�");	fclose(in);	return;	}
	CStdioFile inFile(in), outFile(out); // ���롢����ļ�
	CSpan span; 	

	char line[2000];
	while(inFile.ReadString(line,2000)) {  //	��ÿ��һ�У�
		CString s(line); 	s.TrimLeft( ); s.TrimRight( );
		while(!s.IsEmpty( )) {
		  span.GetFrom(s);  // ��ȡ�ʴ�
		  span.Disamb( );		// �������
		  span.WriteTo(out);// ������
		  span.Reset( );		// ����
		}
		outFile.WriteString("\n");
	}  

	inFile.Close( ); outFile.Close( );
}

void CMainFrame::OnTaggingTagging() 
{
	// �ö�Ԫ�﷨��ע����
	if(!pDict) pDict=new CMyDictionary; // ��ʿ�Ҫ�õ�
	if(!coMatrix.Ready( )) OnTaggingTagset( );  // �����б�Ǽ�����
	ProcessFiles("cut", "*.cut", TaggingFile); // �Ի���ʽ
	// ProcessFiles(TaggingFile);  // ͨ�����ʽ
}

void CMainFrame::OnTaggingTagset() 
{// ��ȡ���Ա�Ǽ�
	CFileDialog dlg(TRUE, "@#$", "*.@#$",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"��Ǽ��������ƣ�|*.@#$|��Ǽ����ı���|*.*||");
	if(dlg.DoModal( )!=IDOK) return;
	coMatrix.FileName=dlg.GetPathName( );
	if(coMatrix.FileName.Right(3)=="@#$") { // ����Ƕ������ļ�
		CFile tf; char buf[512];
		if(tf.Open((const char *)coMatrix.FileName, CFile::modeRead)) {
		  CArchive ar(&tf, CArchive::load, 512, buf);
		  coMatrix.Serialize(ar); // �������л�������������
		}
		coMatrix.Modified=FALSE;
	}
	else { // ������ı��ļ�
		FILE *in;
		in=fopen((const char *)dlg.GetPathName( ),"rt");
		if(!in) { AfxMessageBox("�޷��򿪴��Ա�Ǽ��ļ���"); return;	}
		CStdioFile inFile(in);
		coMatrix.Create(inFile);  // ����Create( )���������Ǽ�
		coMatrix.FileName=ChangeExt(coMatrix.FileName, "@#$");
		// �޸ĺ�׺���Ժ��������ļ�������
	}
}

void TrainFile(CString fileName)
{
  FILE *in;
  in=fopen((const char *)fileName, "rt");
  if(!in) {	AfxMessageBox("�޷��������ļ�"+fileName);	return;	}
	CStdioFile inFile(in);
  coMatrix.AddCorpus(inFile);
}

void CMainFrame::OnTaggingTrain() 
{  // �ö�Ԫ�﷨ѵ������
  if(!pDict) pDict=new CMyDictionary; // ���ǲ�ʿ��������
	ProcessFiles("tag", "*.tag", TrainFile);
}

///////

CObArray  rules,  edges;

void CMainFrame::OnParsingBottomup() 
{	// �����Ե����ϵľ䷨����
  CFileDialog dlg(TRUE, "pos", "*.pos",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"���Ա�ע�ļ�|*.pos|�����ļ�||"); // ��ȡ�����ļ�������
  if(dlg.DoModal( )!=IDOK) return;
  FILE *rf, *in, *out;
  rf=fopen("rules1.txt", "rt"); 
  if(!rf) {
		AfxMessageBox("�޷��򿪹�����ļ�rules1.txt");
		return;
  }
  in=fopen((const char *)dlg.GetPathName( ),"rt");
  if(!in) {
		AfxMessageBox("�޷��������ļ� "+dlg.GetPathName( ));
		fclose(rf);
		return;
  }
  out=fopen((const char *)(dlg.GetPathName( )+".parse"), "wt");
  if(!out) {
		AfxMessageBox("�޷���������ļ�");
		fclose(rf);  fclose(in);
		return;
  }
  CStdioFile inFile(in), outFile(out), ruleFile(rf);

  CString line; CRule *r=NULL;
  for(int i=0; i<rules.GetSize( ); i++) 
		if(rules[i]!=NULL) delete rules[i];
  rules.RemoveAll( ); // ���ԭ�й����Ա��ڳ��������ڼ��޸Ĺ���
  while(ruleFile.ReadString(line)) {	// ����䷨����
		int i=line.Find(';');	if(i<0) continue; 
		line=line.Left(i);  line.TrimLeft( );
		r=new CRule(line);	rules.Add(r);
  }
  ruleFile.Close( );

  while(inFile.ReadString(line)) {
		line=Parsing(line); // ����һ������
		outFile.WriteString(line); // ����������
  }
  inFile.Close( );  outFile.Close( );
  AfxMessageBox("ȫ�����ӷ�����ϣ�");	
}

void CMainFrame::OnParsingPcfg() 
{
	// TODO: Add your command handler code here
	CFileDialog dlg(TRUE, "pos", "*.pos",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"���Ա�ע�ļ�|*.pos|�����ļ�||");  // ��ȡ�����ļ�������
  if(dlg.DoModal( )!=IDOK) return;
  FILE *rf, *in, *out;
  rf=fopen("rules2.txt", "rt"); 
  if(!rf) {
		AfxMessageBox("�޷��򿪹�����ļ�rules2.txt");
		return;
  }
  in=fopen((const char *)dlg.GetPathName( ),"rt");
  if(!in) {
		AfxMessageBox("�޷��������ļ� "+dlg.GetPathName( ));
		fclose(rf);
		return;
  }
  out=fopen((const char *)(dlg.GetPathName( )+".pcfg"), "wt");
  if(!out) {
		AfxMessageBox("�޷���������ļ�");
		fclose(rf);  fclose(in);
		return;
  }
  CStdioFile inFile(in), outFile(out), ruleFile(rf);

  CString line; CProbRule *r=NULL;
  for(int i=0; i<rules.GetSize( ); i++) 
		if(rules[i]!=NULL) delete rules[i];
  rules.RemoveAll( ); // ���ԭ�й����Ա��ڳ��������ڼ��޸Ĺ���
  while(ruleFile.ReadString(line)) {	// ����䷨����
		int i=line.Find(';');	if(i<0) continue; 
		line=line.Left(i);  line.TrimLeft( );
		r=new CProbRule(line);	rules.Add(r);
  }
  ruleFile.Close( );

	double sProb, sProbAddUp=0.0; // ���Ӹ��ʣ����Ӹ���֮��
  int sCnt=0;	//�����Ӹ���
  while(inFile.ReadString(line)) {
		line=ProbParsing(line, sProb); // �Ծ��������ʷ���
		sProbAddUp+=sProb;	sCnt++;
		outFile.WriteString(line);
  }
	
  CString msg;
  msg.Format("%d�����ӣ��ܸ���%7.5f��ƽ��ÿ�����%7.5f\n\n", 
    	    sCnt, sProbAddUp, sProbAddUp/sCnt);
  outFile.WriteString(msg);
  inFile.Close( );  outFile.Close( );

  GetRuleNewProb( );	// ��ȡÿ��������µĸ���ֵ
  rf=fopen("hrules2.new", "wt");
  if(!rf) {
		AfxMessageBox("�޷������µĹ����ļ�");
	return;
  }
  
  CStdioFile newRule(rf); // ��������µĹ����ļ�
  for(i=0; i<rules.GetSize( ); i++) {
    		CProbRule *r=(CProbRule *)rules[i];
    		msg.Format("%s --> %s %s %8.6f; ����������%8.6f\n", 
	  r->Ls,r->Rs1,r->Rs2,r->Prob, r->DesireCount);
    		newRule.WriteString(msg);
  }
  newRule.Close( );		
  AfxMessageBox("ȫ�����ӷ�����ϣ��������¹����ļ�rules2.new");
}
