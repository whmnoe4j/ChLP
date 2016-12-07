// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "现代汉语自动分析.h"
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
  if(!in) { AfxMessageBox("文件打不开！");	return; }
	int count=0;
  while(!feof(in)) {
		char ch=fgetc(in);
		if(ch=='\n') count++;
  }
	fclose(in);
  msg.Format("%s: 共有%d行", (const char *)fname, count);
	AfxMessageBox(msg);	
}

void CMainFrame::OnTestFiles() 
{
	// TODO: Add your command handler code here
	ProcessFiles(CountLinesInAFile);
	// 用通配符选择文件
	ProcessFiles("txt", "*.txt", CountLinesInAFile);
	// 用对话框选择文件
}

void CMainFrame::OnTestGetData() 
{
	// TODO: Add your command handler code here
	CString s, msg;  int i;  double d;
  if(GetData("输入一个字符串：", s)) 
	  AfxMessageBox("输入的字符串是："+s);
	else AfxMessageBox("您没有输入字符串！");
	if(GetData("输入一个整数：", i)) {
	  msg.Format("输入的整数为%d", i);
	  AfxMessageBox(msg);
	}
	else AfxMessageBox("您没有输入整数！");
	if(GetData("输入一个实数：", d)) {
	  msg.Format("输入的实数为：%7.2f", d);
	  AfxMessageBox(msg);
	}
	else AfxMessageBox("您没有输入实数！");
}

void CMainFrame::OnGb2312() 
{
	// TODO: Add your command handler code here
	// 产生国标字符集
  FILE *outFile;  // 输出文件
  unsigned char i, j;
  outFile=fopen("gb2312-80.chr", "wt");
  for ( i=161; i<255; i++)
		for ( j=161; j<255; j++)
	    fprintf ( outFile, "%c%c  %d  %d\n", i, j, i, j);
  fclose (outFile);
	AfxMessageBox("已生成国标字符集文件：gb2312-80.chr");
  return;
}

#define  HZ_NUM	6768
#define  HZ_ID(c1,c2) 	((c1)-176)*94 + ((c2)-161)
	// 计算汉字下标的宏
int  HZFreq[HZ_NUM];

struct  NameZi {
	int  sName,  gName;
} namezis[HZ_NUM];

void  hzInFile (CString FileName)
{
  FILE *in;		unsigned char  c1, c2;		int id;
  in=fopen((const char *)FileName, "rb");
  if(in==NULL) {	AfxMessageBox("无法打开输入文件");  return;  }
  while (!feof (in)) {
		c1=(unsigned char ) fgetc(in);	// 转换为无符号字符
		if(c1<128) continue;	// 不处理单字节西文字符
		if(c1<176) { c2=fgetc(in); continue; } // 也不处理非汉字字符，但要多读一个字节
		c2=(unsigned char ) fgetc(in);	// 读入汉字的第二个字节
		id=HZ_ID(c1,c2);	// 计算该汉字的下标
		HZFreq[id]++;		// 给该汉字的频度加1
  }
  fclose(in);	return;
}

void CMainFrame::OnSingleHz() 
{
	// 单字字频统计
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

CSortedPairs hzPairs; // 假定排序动态数组类的对象已在别的文件中定义

void LoadHZFreq( )
{
	char buf[512];
	FILE *in;
	CFile inFile;

	if(inFile.Open("hzpairs.dat", CFile::modeRead)) {
	  CArchive ar(&inFile, CArchive::load, 512, buf); // 设置为装载模式
	  hzPairs.Serialize(ar);	// 从文件中读出双字字表
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
		CArchive ar(&outFile, CArchive::store, 512, buf); // 设置为存放模式
		hzPairs.Serialize(ar);	// 将双字字表写回文件
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
	if(!in) { AfxMessageBox("无法打开文件 namezis.txt"); return; }
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
  if(in==NULL) {	AfxMessageBox("无法打开输入文件");  return;  }
	zz[0]='\0';
	while(!feof(in)) {
		c1=(unsigned char)fgetc (in);	
		if(c1<128) { zz[0]='\0'; continue; } // 不处理西文字符
		else if(c1<176) { c2=fgetc(in); zz[0]='\0'; continue; } // 也不处理非汉字的双字节字符
		c2=(unsigned char)fgetc(in);	
		id=HZ_ID(c1, c2);	// 计算汉字所对应的下标
		HZFreq[id]++;		// 以上是登记单字字频，以下是登记双字字频
		if(zz[0]!='\0') { // 如果此前已经取过单字
		  zz[2]=c1; zz[3]=c2; // 将当前单字写在第二字位置
	    hzPairs.Insert (zz);	// 调用我们自己编写的函数来插入双字
		}			
		zz[0]=c1; zz[1]=c2; 	// 将当前单字写到第一字位置
	}
	fclose(in);	return;
}

void CMainFrame::OnDoubleHz() 
{
	// TODO: Add your command handler code here	
	int n=ProcessFiles("snt", "*.snt", HZPairInFile); // 统计成批文件中的双字
	if(n>0) ADD_HANZI=TRUE;
}

void CMainFrame::OnSeekHz() 
{
	// TODO: Add your command handler code here
	CString key, msg;
	if(!GetData("输入要找的单字或双字：", key)) return;
	key.TrimRight(); 
	key.TrimLeft();
	int id,  n= key.GetLength( );
	if(n==2) {	// 如果输入单字
	  id=HZ_ID((unsigned char)key[0], (unsigned char)key[1]);
		msg.Format("该汉字出现%d次", HZFreq[id]);
	}
	else {	// 如果输入双字
		if(hzPairs.Search((const char *)key, id)) {
		  HZPair *hp=(HZPair *)hzPairs.GetAt(id);
		  msg.Format("该双字出现%d次", hp->freq);
		}
	}
	if(msg.IsEmpty( )) msg="找不到，或者输入错误";
	AfxMessageBox(msg);
}

void CMainFrame::OnHzReport() 
{
	// TODO: Add your command handler code here
	int hzCount=0,	 CorpusSize=0;
	for (int id=0; id<HZ_NUM; id++) {
		if(HZFreq[id]>0) { // 只报告出现过的汉字的信息
		  hzCount++;
		  CorpusSize+=HZFreq[id];
		}
	}
	CString msg;
	msg.Format("已统计语料共%d字；\n其中不同汉字%d个；\n不同双字%d种", CorpusSize, hzCount, hzPairs.GetSize( ));
	AfxMessageBox(msg);
}

#define MaxWordLength 8  // 最大词长为8（即4个汉字）
#define Separator " "		 // 词界标记

CString  SegmentHzStrMM (CString s1)
{
  CString s2="";	    // 存放分词结果，初始化为空串
  while(!s1.IsEmpty( )) {	    // 当输入串未处理完时
		int len=s1.GetLength( );		// 求输入串的当前长度
		if (len > MaxWordLength) len=MaxWordLength; // 超过4个汉字时只取4个
    CString w=s1.Left(len);   // 从左边复制子串（候选词）
		while(len>2 &&  pDict->GetFreq(w )== -1) { 
      // 当候选词不止一个汉字而且匹配失败时
		  len-=2;  w=w.Left(len);  // 从候选词右边减掉一个汉字
		}
		s2+=w + Separator;  // 将匹配到的词（或剩下的一个字）
		// 连同词界标记加到输出串末尾
		s1=s1.Mid(w.GetLength()); // 从输入串左边去掉这个词
  }
  return s2;
}

CString  SegmentSentenceMM (CString s1)
{
  CString s2=""; // 输出串
  int i;
  while(!s1.IsEmpty( )) {
		unsigned char ch=(unsigned char)s1[0];			
		if(ch<128) {  // 西文字符
  	  i=1;
		  while(i<s1.GetLength() && (unsigned char)s1[i]<128) i++;
		  s2+=s1.Left(i)+Separator;
		  s1=s1.Mid(i);
		  continue;
		}
		else if(ch<176) {	// 中文标点等字符
		  s2+=s1.Left(2)+Separator;
  	  s1=s1.Mid(2);
		  continue;
		}
		// 以下处理汉字串	
		i=2;
		while((unsigned char)s1[i]>=176) i+=2;
		s2+=SegmentHzStrMM(s1.Left(i));  // 调用最大匹配法分词函数
		s1=s1.Mid(i);
  }	
  return s2;
}

void SegmentAFileMM(CString FileName)
{
	FILE *in, *out;
	in=fopen((const char *)FileName, "rt");
	if(in==NULL) { AfxMessageBox("无法打开文件");	return; }
	FileName = ChangeExt(FileName, "cut"); 
	out=fopen((const char *)FileName, "wt");
	if(out==NULL) { AfxMessageBox("无法创建文件");	fclose(in);	return; }
	CStdioFile inFile(in), outFile(out);

	char s[2048];
	CString line; 
	while(inFile.ReadString(s, 2048)) {	// 循环读入每一行
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

struct Candidate {	// 存放候选词信息的结构
  short  offset, length; // 候选词在输入串中的起点，长度
  short  goodPrev;       // 最佳前趋词的序号
  float fee, sumFee;   // 候选词的费用，路径上的累计费用
} Candidates[100];  // 假定最多100个候选词

short getTmpWords(CString& s)
{
  short i=0, j, len, freq, n=s.GetLength( );
	CString w;
  for(j=0; j<n; j+=2) { // 以每一个汉字为起点
    for(len=2; len<=MaxWordLength; len+=2) { // 长度为1～MaxWordLength/2个字
			w=s.Mid(j, len);
      freq=pDict->GetFreq(w); 
		  if(len>2 && freq==-1) continue; // 若不止一字且词表中找不到则不予登录
		  if(freq==-1) freq=0; // 若为单字且词表中找不到则设出现次数为0
		  Candidates[i].offset=j; // 该候选词在汉字串中的起点
		  Candidates[i].length=len;	// 该候选词的长度
		  Candidates[i].fee=-log((double)(freq+1)/CorpusSize); // 该候选词的费用
			// 使用log( )函数，需在适当地方包含头文件math.h
			// CorpusSize是语料库规模（以词为单位），此常量需在适当地方定义
			Candidates[i].sumFee=0.0F;  // 置初值
		  i++;
		}
	}
	return i;
}

void getPrev(short i)	
{
  if(Candidates[i].offset==0) { // 如果是汉字串中的首词
    Candidates[i].goodPrev = -1;  // 无前趋词
    Candidates[i].sumFee = Candidates[i].fee; // 累计费用为该词本身费用
    return;
  }
  //  否则
  short j, minID = -1;  // minID是最佳前趋词序号
  for(j=i-1; j>=0; j--) // 向左寻找所遇到的第一个前趋词
    if(Candidates[j].offset+Candidates[j].length==Candidates[i].offset)  break;
  for(;Candidates[j].offset+Candidates[j].length==Candidates[i].offset;j--) 
    // 前趋词是连续排列的
    if(minID == -1 || Candidates[j].sumFee < Candidates[minID].sumFee) minID=j;
  Candidates[i].goodPrev = minID; // 登记最佳前趋词序号
  Candidates[i].sumFee = Candidates[i].fee + Candidates[minID].sumFee;
		// 登记最小累计费用
	return;
}

double sFee(CString  z)
{
  int wFreq = pDict->GetFreq (z);  // 作为单字词的出现次数
  if(wFreq == -1) wFreq=0;
  double wFee = -log((double)(wFreq+1)/CorpusSize);  // 作为单字词的费用
  int id=HZ_ID((unsigned char)z[0], (unsigned char)z[1]);
  if(id>=0 && id<HZ_NUM && namezis[id].sName>0) // 如果是一个姓氏用字
		return -log((double)(namezis[id].sName+1)/SurNameSize) - wFee;
	else  return 20.0; // 返回一个极高费用，使该字不可能被判为姓氏
}

double gFee (CString  z)
{
  int wFreq = pDict->GetFreq(z);  // 作为单字词的出现次数
  if(wFreq == -1) wFreq=0;
  double wFee = -log((double)(wFreq+1)/CorpusSize);  // 作为单字词的费用
  int id=HZ_ID((unsigned char)z[0], (unsigned char)z[1]);
  if(id>=0 && id<HZ_NUM) {   // 如果是汉字
		if(namezis[id].gName>0) // 如果是一个姓氏用字
		  return -log((double)(namezis[id].gName+1)/GivenNameSize) - wFee;
		else return  -log10(1/GivenNameSize) - wFee;
			//  因为几乎任何汉字都有可能作为人名用字
	}
  else return 20.0; // 非汉字不可能作为人名用字
}

double sgFee(CString sg)
{
  double fee=pDict->GetFee(sg, TRUE); // 查找全名
  if(fee < 20.0) return fee;  // 如果找到了，返回其费用
  if(sg.GetLength( )==4) {	
 		fee=pDict->GetFee(sg, FALSE); // 查找名字部分，如"小平"
   	if(fee < 20.0) return fee;	// 如果找到了，返回其费用
  }       
  fee=sFee(sg.Left(2)) + gFee(sg.Mid(2,2)); // 姓氏和人名首字费用
  if(sg.GetLength( )==4) fee += -log(0.37); // 加上单名费用
  else fee += gFee(sg.Right(2)) + (-log(0.63)); 
 	// 加上人名第二字费用和双名费用
  return fee ;  // 返回总费用
}

class CMaybeName : public CObject {
public:
  short offset, length;  // 起点、长度
  double fee;		 // 费用
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
  if (p1->offset==p2->offset   // 如果是同源对
		|| p1->offset+p1->length<=p2->offset	// 或者没有重叠部分
		|| p2->offset+p2->length<=p1->offset)  
		return FALSE;		// 就不是交错对
	else  return TRUE;
}

CString CheckStr (CString  s1)
{
  CObArray maybeNames;  // 元素为CMaybeName类型的指针
  CMaybeName *p, *p1, *p2;  
  int i, j, len;
  for(i=0; i<s1.GetLength( ); i+=2) {
  	for (len=4; len<=6 && i+len<=s1.GetLength(); len+=2) { // 找出候选姓名
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
	// 以下生成新的词串
	CString s2="";
	if(maybeNames.GetSize( )==0) {  // 如果没有发现姓名
  	for(i=0; i<s1.GetLength( ); i+=2) s2 += s1.Mid(i,2)+Separator;
  	return s2;
	}

  for(i=0; i<maybeNames.GetSize( ); i++) {
		if(i==0) j=0;		else j=p->offset + p->length;  
		p=(CMaybeName *)maybeNames[i]; 
		for(; j<p->offset; j+=2) s2 += s1.Mid(j,2)+Separator;
		// 加上姓名之前的单字词
		CString w= s1.Mid(p->offset, p->length);
		s2 += w+Separator; // 加上该姓名
		CString sName=w.Left(2), gName=w.Mid(2);
		pDict->Insert(sName, gName, p->fee); // 插入姓名表
	} 
	for(j=p->offset+p->length; j<s1.GetLength( ); j+=2) 
    s2 += s1.Mid(j,2)+Separator; // 加上最后一个姓名之后的单字词
	
	return s2;
}

CString  SegmentHzStrMP (CString  s1)
{
  int len=s1.GetLength( );
  short n=getTmpWords(s1); // 取出s1中的全部候选词：
  short minID=-1;      //设最小费用路径的终点词的序号为-1
  short i;
  for(i=0; i<n; i++) {  //循环，对每一候选词做:  
  	getPrev(i);   // 填写最佳前趋词序号、当前词最小累计费用
  	if(Candidates[i].offset+Candidates[i].length==len) {
    // 如果当前词是s1的尾词：
      if(minID==-1||Candidates[i].sumFee<Candidates[minID].sumFee) minID=i;
      //如果是第一个遇到的尾词，或者当前尾词的最小累计费用小于已经遇到过的
			//任一尾词的最小累计费用，则将其序号赋给minID
   	}
  }
  CString s2="";  //  输出串初始化  
	CString tmp=""; //  单字词串初始化
  for(i=minID; i>=0; i=Candidates[i].goodPrev)  {
		CString w=s1.Mid(Candidates[i].offset, Candidates[i].length);
		if(w.GetLength()==2) tmp=w+tmp;  // 如果是单字词，加到tmp中去
		else { // 否则，先处理此前的tmp
			if(tmp.GetLength()>0) {
				if(tmp.GetLength()==2) s2=tmp+Separator+s2;
				else s2=CheckStr(tmp)+Separator+s2;
				tmp="";
			}
			s2=w+Separator+s2; // 加上当前的非单字词
		}
	}	
	if(tmp.GetLength()>0) { // 处理位于s1最左边的单字词串
		if(tmp.GetLength()==2) s2=tmp+Separator+s2;
		else s2=CheckStr(tmp)+Separator+s2;
		tmp="";
	}
	//  注意：是先取后面的词          
  return s2;  // 返回这个词串
}

CString  SegmentSentenceMP (CString s1)
{
  CString s2=""; // 输出串
  int i;
  while(!s1.IsEmpty( )) {
		unsigned char ch=(unsigned char)s1[0];			
		if(ch<128) {  // 西文字符
  	  i=1;
		  while(i<s1.GetLength() && (unsigned char)s1[i]<128) i++;
		  s2+=s1.Left(i)+Separator;
		  s1=s1.Mid(i);
		  continue;
		}
		else if(ch<176) {	// 中文标点等字符
		  s2+=s1.Left(2)+Separator;
  	  s1=s1.Mid(2);
		  continue;
		}
		// 以下处理汉字串	
		i=2;
		while((unsigned char)s1[i]>=176) i+=2;
		s2+=SegmentHzStrMP(s1.Left(i));  // 调用最大概率法分词函数
		s1=s1.Mid(i);
  }	
  return s2;
}

void SegmentAFileMP(CString FileName)
{
	FILE *in, *out;
	in=fopen((const char *)FileName, "rt");
	if(in==NULL) { AfxMessageBox("无法打开文件");	return; }
	FileName = ChangeExt(FileName, "cut"); 
	out=fopen((const char *)FileName, "wt");
	if(out==NULL) { AfxMessageBox("无法创建文件");	fclose(in);	return; }
	CStdioFile inFile(in), outFile(out);

	char s[2048];
	CString line; 
	while(inFile.ReadString(s, 2048)) {	// 循环读入每一行
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
{  // 单个文件的断句函数
	FILE *in, *out;
	in=fopen((const char *)FileName, "rt");
	if(in==NULL) { AfxMessageBox("无法打开文件");	return; }
	FileName = ChangeExt(FileName, "sen"); 
	out=fopen((const char *)FileName, "wt");
	if(out==NULL) { AfxMessageBox("无法创建文件");	fclose(in);	return; }
	CStdioFile inFile(in), outFile(out);

	char s[2048];
	CString line; int i, n;
	while(inFile.ReadString(s, 2048)) {	// 循环读入每一行
		line=s;
		n=line.GetLength( );  // 记下该行的原有长度
		while((i=GetSentence(line))>0) { // 只要读到了句子
		  outFile.WriteString(line.Left(i)+'\n'); // 写入句子文件
		  line=line.Mid(i);	// 从行中去掉这个句子
		}
		if(!line.IsEmpty( )) {	// 如果行中还有字符
		  if(n==line.GetLength( ) && n<60) // 如果整行无句末标点且较短
			  outFile.WriteString(line+'\n'); // 算作一个无标点的句子
			else outFile.WriteString(line);	// 否则将剩下的字符写入文件
		}
	}
	inFile.Close( ); outFile.Close( );		
}

void CMainFrame::OnSegmentSentence() 
{
	// TODO: Add your command handler code here
	ProcessFiles("*", "*.*", CutSentence); // 调用多文件处理函数
}

void CMainFrame::OnBindDynamic() 
{
	// 动态捆绑
	CString w, msg;  CObArray a;
	if(!GetData("输入待查找的词：", w)) return;
	int i, n=pDict->GetFreq(w, a);
	if(n==0) AfxMessageBox("词库中没有这个词");
	else {
		msg=w+":\n";		CTagFreq *pt;
		for(i=0; i<n; i++) {
			pt=(CTagFreq *)a.GetAt(i);
			w.Format("标记：%s；出现次数：%d\n", pt->Tag, pt->Freq);
			msg+=w;
		}
		AfxMessageBox(msg);
	}
}

void CMainFrame::OnBindSnapshot() 
{
	// 静态捆绑
	CWordTagSet *pSet=new CWordTagSet;
	pSet->Open();
	if(!pSet->IsOpen()) {
		AfxMessageBox("can not open snapshot");
		return;
	}
	CString w, msg;  CObArray a;
	if(!GetData("输入待查找的词：", w)) return;
	int i, n=pSet->GetFreqs(w, a);
	if(n==0) AfxMessageBox("词库中没有这个词");
	else {
		msg=w+":\n";		CTagFreq *pt;
		for(i=0; i<n; i++) {
			pt=(CTagFreq *)a.GetAt(i);
			w.Format("标记：%s；出现次数：%d\n", pt->Tag, pt->Freq);
			msg+=w;
		}
		AfxMessageBox(msg);
	}
	delete pSet;
}

//  字词检索
CString corpusName="";   		// 语料库名
CStringArray texts; 			// 语料文件名集合
BOOL CorpusModified=FALSE; 	// 表示当前语料库是否修改过
CHzInfo hzInfo[6768];

void CMainFrame::OnCorpusCreate() 
{
	// TODO: Add your command handler code here
	CFileDialog dlg(FALSE); // 获取语料库存盘文件名
	if(dlg.DoModal( )!=IDOK) return;
	if(!corpusName.IsEmpty( )) OnCorpusClose( ); // 关闭当前语料库
	corpusName=dlg.GetPathName( );
	OnCorpusAdd( );  // 添加语料
}

void CMainFrame::OnCorpusClose() 
{
	// TODO: Add your command handler code here
	if(corpusName.IsEmpty( )) return; 
		// 如果并无打开的语料库，则返回	
	if(CorpusModified) { // 如果语料库已作修改
		CFile cf; char buf[512];
		if(cf.Open((const char *)corpusName, 
         CFile::modeCreate | CFile::modeWrite)) {
			CArchive ar(&cf, CArchive::store, 512, buf );
			texts.Serialize(ar);
		}
		else { AfxMessageBox("语料库无法存盘！"); return; }
		texts.RemoveAll( ); // 清除所有语料文件名
		CFile tf;
		CString ylkName=ChangeExt(corpusName, "@@@");
		if(tf.Open((const char *)ylkName, 
			CFile::modeCreate |CFile::modeWrite)) {
			CArchive ar(&tf, CArchive::store, 512,buf);
			for(int i=0; i<6768; i++) hzInfo[i].Serialize(ar);
		}
		else { AfxMessageBox("汉字信息无法存盘！"); return; }  
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
	if(!in) { AfxMessageBox("打不开文件 "+FileName); return; }
	while(!feof(in)) {
	  unsigned char c1, c2;
	  c1=(unsigned char)fgetc(in);   
    if(c1<128) continue; // 不处理西文字符
	  c2=(unsigned char)fgetc(in);
	  if(c1>=176) {  // 如果是汉字
		  int id=HZ_ID(c1,c2);  if(id<0 || id>=6768) continue;
		  hzInfo[id].AddTextID(n); // 将语料文件序号加入地址串
	  }
	}
	fclose(in);
	FileName.MakeLower( );  // 将文件名中的字母转为小写
	texts.Add(FileName);   // 将文件名添加到字符串数组
	CorpusModified=TRUE;   // 设置语料库修改标记
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
		"语料库文件|*.ylk|所有文件||"); // 语料库存盘文件
	if(dlg.DoModal()!=IDOK) return;
	if(!corpusName.IsEmpty()) OnCorpusClose();
	// 如果当前已经打开了一个语料库，先关闭它
	CFile cf;  char buf[512];
	if(cf.Open((const char *)(dlg.GetPathName()), CFile::modeRead)) {
		CArchive ar(&cf, CArchive::load, 512, buf);
		texts.Serialize(ar);	// 读入所有语料文件名
	}
	else { AfxMessageBox("无法打开语料库！"); return; }

	CFile tf; 
	CString ylkName=ChangeExt(dlg.GetPathName(), "@@@");
	if(tf.Open((const char *)ylkName, CFile::modeRead)) {
		CArchive ar(&tf, CArchive::load, 512,buf);
		for(int i=0; i<6768; i++) hzInfo[i].Serialize(ar);
		// 读入每个汉字的信息（出现次数和地址串）
	}
	else { AfxMessageBox("无法读入汉字信息！"); return; }
	corpusName=dlg.GetPathName();	// 保存语料库文件名
	CorpusModified=FALSE;  // 语料库修改标记
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
	  CWordArray *pw=new CWordArray;  // 交集指针
	  for(int i=0, j=0; i<wi.GetSize( ) && j<wj.GetSize( ); ) {
		if(wi[i]==wj[j]) { pw->Add(wi[i]); i++; j++; } // 加入相同地址
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
  if(!out) { AfxMessageBox("无法创建检索输出文件！"); return; }
  CStdioFile outFile(out);
  outFile.WriteString("查找汉字串：“");
  outFile.WriteString(key+"”\n");
  for(int i=0; i<txtID->GetSize( ); i++) {
		int id=txtID->GetAt(i); // 取出一个地址
		CString fname=texts[id];  // 取出相应的语料文件名
		in=fopen((const char *)fname, "rt");
		if(!in) { AfxMessageBox("找不到语料文件 "+fname); continue; }
		CStdioFile inFile(in);
		char s[3000]; CString ss="", dd;
		while(inFile.ReadString(s, 3000)) // 读语料文件的每一行
	 	  if(key.GetLength( )>2 && strstr(s,(const char *)key)
				|| key.GetLength( )==2 && FindOneHZ(s, (const char *)key)>=0){  
			// 如果含有该汉字或者汉字串
			  Examples++;  // 例子个数
			  dd.Format("例%04d： ", Examples);
			  ss+=dd+s;  ss+='\n';		// 加到输出串中
		  }
		if(ss.GetLength( )>0) {  // 如果输出串不为空
		  outFile.WriteString(fname+":\n"); // 写文件名
		  outFile.WriteString(ss+"\n");     // 写输出串
		}
		inFile.Close( ); 
	}
	outFile.Close( );
	if(Examples>0) AfxGetApp( )->OpenDocumentFile("output.txt");
		// 在应用程序中打开输出文件
	else AfxMessageBox("找不到这个汉字串！"); 
}

void CMainFrame::OnRetrieveHzstr() 
{
	// TODO: Add your command handler code here
	CString key;
	if(!GetData("查找汉字串：", key)) return;
	key.TrimLeft( );  key.TrimRight( ); // 压缩前后空格
	int id, id2, n=key.GetLength( );
	if(!GoodHzStr(key)) { // 检查输入的合法性
		AfxMessageBox("输入的汉字串有错误！");
		return;
	}
	CWordArray *txtID, *tmp;
	id=HZ_ID((unsigned char)key[0],(unsigned char)key[1]);
	if(n==2) { // 如果输入的是单个汉字
		txtID=&(hzInfo[id].TextID);
		if(txtID->GetSize( )==0) {
      AfxMessageBox("找不到这个汉字串");
		  return;
		}
		Retrieve(txtID, key);  // 在第txtID个语料文件中检索汉字key
		return;
	}
		// 以下处理检索多个汉字的情况
	id2=HZ_ID((unsigned char)key[2],(unsigned char)key[3]); 
	  // 第二个汉字
	txtID=Intersection(hzInfo[id].TextID, hzInfo[id2].TextID);
		// 求前两个汉字的地址串的交集
	int i=4;  // 从第三个汉字开始
	while(txtID->GetSize( )>0 && i<key.GetLength( )-1) {
		id2=HZ_ID((unsigned char)key[i],(unsigned char)key[i+1]);
		tmp=Intersection(*txtID, hzInfo[id2].TextID);
		delete txtID;  txtID=tmp;	i+=2;
	}
	if(txtID->GetSize( )==0) {  // 如果交集为空
	  AfxMessageBox("找不到这个汉字串");
	  return;
	}
	Retrieve(txtID, key);  // 在第txtID个语料文件中检索汉字串key
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
{ // 对一个文件进行词性标注
  FILE *in, *out;
  in=fopen((const char *)fileName, "rt");
  if(!in) {	AfxMessageBox("无法打开语料文件"+fileName);	return;	}
	out=fopen((const char *)ChangeExt(fileName,"pos"), "wt");
	if(!out) { AfxMessageBox("无法创建词性标注文件");	fclose(in);	return;	}
	CStdioFile inFile(in), outFile(out); // 输入、输出文件
	CSpan span; 	

	char line[2000];
	while(inFile.ReadString(line,2000)) {  //	（每句一行）
		CString s(line); 	s.TrimLeft( ); s.TrimRight( );
		while(!s.IsEmpty( )) {
		  span.GetFrom(s);  // 获取词串
		  span.Disamb( );		// 词性消岐
		  span.WriteTo(out);// 输出结果
		  span.Reset( );		// 重置
		}
		outFile.WriteString("\n");
	}  

	inFile.Close( ); outFile.Close( );
}

void CMainFrame::OnTaggingTagging() 
{
	// 用二元语法标注词性
	if(!pDict) pDict=new CMyDictionary; // 查词库要用到
	if(!coMatrix.Ready( )) OnTaggingTagset( );  // 必须有标记集可用
	ProcessFiles("cut", "*.cut", TaggingFile); // 对话框方式
	// ProcessFiles(TaggingFile);  // 通配符方式
}

void CMainFrame::OnTaggingTagset() 
{// 获取词性标记集
	CFileDialog dlg(TRUE, "@#$", "*.@#$",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"标记集（二进制）|*.@#$|标记集（文本）|*.*||");
	if(dlg.DoModal( )!=IDOK) return;
	coMatrix.FileName=dlg.GetPathName( );
	if(coMatrix.FileName.Right(3)=="@#$") { // 如果是二进制文件
		CFile tf; char buf[512];
		if(tf.Open((const char *)coMatrix.FileName, CFile::modeRead)) {
		  CArchive ar(&tf, CArchive::load, 512, buf);
		  coMatrix.Serialize(ar); // 则用序列化函数读入数据
		}
		coMatrix.Modified=FALSE;
	}
	else { // 如果是文本文件
		FILE *in;
		in=fopen((const char *)dlg.GetPathName( ),"rt");
		if(!in) { AfxMessageBox("无法打开词性标记集文件！"); return;	}
		CStdioFile inFile(in);
		coMatrix.Create(inFile);  // 调用Create( )函数读入标记集
		coMatrix.FileName=ChangeExt(coMatrix.FileName, "@#$");
		// 修改后缀，以后就用这个文件名存盘
	}
}

void TrainFile(CString fileName)
{
  FILE *in;
  in=fopen((const char *)fileName, "rt");
  if(!in) {	AfxMessageBox("无法打开语料文件"+fileName);	return;	}
	CStdioFile inFile(in);
  coMatrix.AddCorpus(inFile);
}

void CMainFrame::OnTaggingTrain() 
{  // 用二元语法训练语料
  if(!pDict) pDict=new CMyDictionary; // 这是查词库所必须的
	ProcessFiles("tag", "*.tag", TrainFile);
}

///////

CObArray  rules,  edges;

void CMainFrame::OnParsingBottomup() 
{	// 纯粹自底向上的句法分析
  CFileDialog dlg(TRUE, "pos", "*.pos",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"词性标注文件|*.pos|所有文件||"); // 获取输入文件的名字
  if(dlg.DoModal( )!=IDOK) return;
  FILE *rf, *in, *out;
  rf=fopen("rules1.txt", "rt"); 
  if(!rf) {
		AfxMessageBox("无法打开规则库文件rules1.txt");
		return;
  }
  in=fopen((const char *)dlg.GetPathName( ),"rt");
  if(!in) {
		AfxMessageBox("无法打开输入文件 "+dlg.GetPathName( ));
		fclose(rf);
		return;
  }
  out=fopen((const char *)(dlg.GetPathName( )+".parse"), "wt");
  if(!out) {
		AfxMessageBox("无法创建输出文件");
		fclose(rf);  fclose(in);
		return;
  }
  CStdioFile inFile(in), outFile(out), ruleFile(rf);

  CString line; CRule *r=NULL;
  for(int i=0; i<rules.GetSize( ); i++) 
		if(rules[i]!=NULL) delete rules[i];
  rules.RemoveAll( ); // 清除原有规则，以便在程序运行期间修改规则
  while(ruleFile.ReadString(line)) {	// 读入句法规则
		int i=line.Find(';');	if(i<0) continue; 
		line=line.Left(i);  line.TrimLeft( );
		r=new CRule(line);	rules.Add(r);
  }
  ruleFile.Close( );

  while(inFile.ReadString(line)) {
		line=Parsing(line); // 读入一个句子
		outFile.WriteString(line); // 输出分析结果
  }
  inFile.Close( );  outFile.Close( );
  AfxMessageBox("全部句子分析完毕！");	
}

void CMainFrame::OnParsingPcfg() 
{
	// TODO: Add your command handler code here
	CFileDialog dlg(TRUE, "pos", "*.pos",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"词性标注文件|*.pos|所有文件||");  // 获取输入文件的名字
  if(dlg.DoModal( )!=IDOK) return;
  FILE *rf, *in, *out;
  rf=fopen("rules2.txt", "rt"); 
  if(!rf) {
		AfxMessageBox("无法打开规则库文件rules2.txt");
		return;
  }
  in=fopen((const char *)dlg.GetPathName( ),"rt");
  if(!in) {
		AfxMessageBox("无法打开输入文件 "+dlg.GetPathName( ));
		fclose(rf);
		return;
  }
  out=fopen((const char *)(dlg.GetPathName( )+".pcfg"), "wt");
  if(!out) {
		AfxMessageBox("无法创建输出文件");
		fclose(rf);  fclose(in);
		return;
  }
  CStdioFile inFile(in), outFile(out), ruleFile(rf);

  CString line; CProbRule *r=NULL;
  for(int i=0; i<rules.GetSize( ); i++) 
		if(rules[i]!=NULL) delete rules[i];
  rules.RemoveAll( ); // 清除原有规则，以便在程序运行期间修改规则
  while(ruleFile.ReadString(line)) {	// 读入句法规则
		int i=line.Find(';');	if(i<0) continue; 
		line=line.Left(i);  line.TrimLeft( );
		r=new CProbRule(line);	rules.Add(r);
  }
  ruleFile.Close( );

	double sProb, sProbAddUp=0.0; // 句子概率，句子概率之和
  int sCnt=0;	//　句子个数
  while(inFile.ReadString(line)) {
		line=ProbParsing(line, sProb); // 对句子作概率分析
		sProbAddUp+=sProb;	sCnt++;
		outFile.WriteString(line);
  }
	
  CString msg;
  msg.Format("%d个句子，总概率%7.5f，平均每句概率%7.5f\n\n", 
    	    sCnt, sProbAddUp, sProbAddUp/sCnt);
  outFile.WriteString(msg);
  inFile.Close( );  outFile.Close( );

  GetRuleNewProb( );	// 获取每条规则的新的概率值
  rf=fopen("hrules2.new", "wt");
  if(!rf) {
		AfxMessageBox("无法创建新的规则文件");
	return;
  }
  
  CStdioFile newRule(rf); // 以下输出新的规则文件
  for(i=0; i<rules.GetSize( ); i++) {
    		CProbRule *r=(CProbRule *)rules[i];
    		msg.Format("%s --> %s %s %8.6f; 期望次数：%8.6f\n", 
	  r->Ls,r->Rs1,r->Rs2,r->Prob, r->DesireCount);
    		newRule.WriteString(msg);
  }
  newRule.Close( );		
  AfxMessageBox("全部句子分析完毕，并生成新规则文件rules2.new");
}
