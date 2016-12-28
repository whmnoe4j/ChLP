// FileAttributes.cpp : implementation file
//

#include "stdafx.h"
#include "ChLP.h"
#include "FileAttributes.h"
#include "sortedpairs.h"
#include "hzpair.h"
#include "dictionary.h"
#include <math.h>

#define Corpus_Size 200000

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

int HZFreq[HZ_NUM];
BOOL ADD_HANZI=FALSE;
CSortedPairs hzPairs;
CDictionary Dict;
struct Candidate Candidates[100];
NameZi namezis[HZ_NUM];
const int SurNameSize=174000;
const int GivenNameSize=320000;

// CFileAttributes dialog


CFileAttributes::CFileAttributes(CWnd* pParent /*=NULL*/)
	: CDialog(CFileAttributes::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileAttributes)
	m_Sample = FALSE;
	m_Year =2016;
	m_Author = _T("");
	m_Category = 0;
	m_Source = _T("");
	//}}AFX_DATA_INIT
}


void CFileAttributes::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileAttributes)
	DDX_Control(pDX, ID_COMBOBOX_SOURCE, m_SourceCtrl);
	DDX_Control(pDX, IDC_SPIN_YEAR, m_SpinYear);
	DDX_Check(pDX, IDC_SAMPLE, m_Sample);
	DDX_Text(pDX, IDC_EDIT_YEAR, m_Year);
	DDV_MinMaxInt(pDX, m_Year, 1949, 2050);
	DDX_Text(pDX, IDC_EDIT_AUTHOR, m_Author);
	DDV_MaxChars(pDX, m_Author, 100);
	DDX_Radio(pDX, IDC_CATEGORY, m_Category);
	DDX_CBString(pDX, ID_COMBOBOX_SOURCE, m_Source);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileAttributes, CDialog)
	//{{AFX_MSG_MAP(CFileAttributes)
	ON_BN_CLICKED(ID_OK, OnOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileAttributes message handlers

BOOL CFileAttributes::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_SourceCtrl.SetWindowText("语文课本");
	m_SpinYear.SetRange(1949,2050);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFileAttributes::OnOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString msg,Class;
	switch(m_Category){
	case 0:Class="语文"; break;
	case 1:Class="数学"; break;
	case 2:Class="英语"; break;
	case 3:Class="信息";break;
	case 4:Class="社会";break;
	}
	msg.Format("作者：%s;分类：%s;\n出处：%s;\n发表时间：%d年：\n",m_Author,Class,m_Source,m_Year);
	if(m_Sample)msg+="作为样本";else msg+="不作为样本";
	AfxMessageBox(msg);
	CDialog::OnOK();
}
/////////////////////////////////////////////////////////////////////////////
// CGetDataDlg dialog


CGetDataDlg::CGetDataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetDataDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGetDataDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CGetDataDlg::CGetDataDlg(char*Prompt,CWnd* pParent /*=NULL*/)
	: CDialog(CGetDataDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGetDataDlg)
	DataString=_T("");
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	PromptStr=Prompt;
}


void CGetDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetDataDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Text(pDX, IDC_DATA_STRING, DataString);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGetDataDlg, CDialog)
	//{{AFX_MSG_MAP(CGetDataDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetDataDlg message handlers

BOOL CGetDataDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetWindowText(PromptStr);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL /*CGetDataDlg::*/GetData(const char *Prompt, CString &Data)
{
	CGetDataDlg dlg((char*)Prompt);
	if(dlg.DoModal()!=IDOK)return FALSE;
	Data=dlg.DataString;
	return TRUE;
}
BOOL GetData(const char *Prompt, int &Data)
{
	CGetDataDlg dlg((char*)Prompt);
	if(dlg.DoModal()!=IDOK)return FALSE;
	dlg.DataString.TrimLeft();
	dlg.DataString.TrimRight();
	Data=atoi((const char*)(dlg.DataString));
	return TRUE;
}
BOOL GetData(const char *Prompt, double &Data)
{
	CGetDataDlg dlg((char*)Prompt);
	if(dlg.DoModal()!=IDOK)return FALSE;
	dlg.DataString.TrimLeft();
	dlg.DataString.TrimRight();
	Data=atof((const char*)(dlg.DataString));
	return TRUE;
}
void CountLinesInAFile(CString fname)
{	// TODO: Add your command handler code here
//	CString fname="ChLP2";
	FILE*in;
	CString msg;
	in=fopen((const char *)fname,"rb");
	if(!in){AfxMessageBox("文件打不开！");return;}
	int count=0;
	if(in->_bufsiz>1)
		count=1;
	while(!feof(in)){
		char ch=fgetc(in);
		if(ch=='\n')count++;
	}
	fclose(in);
	msg.Format("%s:共有%d行",(const char*)fname,count);
	AfxMessageBox(msg);
}
#include <io.h>
#include <direct.h>
#include <errno.h>
int ProcessFiles(void(*ProcessAFile)(CString fileName))
{
	CString FileName;
	if(!GetData("输入文件名（可含通配符）：",FileName))return 0;
	int i=FileName.ReverseFind('\\');
	if(i>0){
		if(_chdir((const char*)(FileName.Left(i)))!=0){
			AfxMessageBox("路径名错误！");
			return 0;
		}
		FileName=FileName.Mid(i+1);
	}
	_finddata_t info;
	long handle=_findfirst(FileName.GetBuffer(FileName.GetLength()),&info);
	if(errno==ENOENT){
		AfxMessageBox("没有找到匹配文件！");
		return 0;
	}
	else if(errno==EINVAL){
		AfxMessageBox("非法文件名！");
		return 0;
	}
	int fileCount=0;
	do{
		ProcessAFile(info.name);
		fileCount++;
	}
	while(_findnext(handle,&info)==0);
	errno=0;
	AfxMessageBox("全部文件处理完毕");
	return fileCount;
}
int ProcessFiles(char*Ext,char*Name,void(*ProcessAFile)(CString fileName))
{
	CFileDialog dlg(TRUE,Ext,Name,OFN_ALLOWMULTISELECT);
	if(dlg.DoModal()!=IDOK)
		return 0;
	int fileCount=0;
	CString FileName;
	POSITION pos=dlg.GetStartPosition();
	while(pos!=NULL){
		FileName=dlg.GetNextPathName(pos);
		ProcessAFile(FileName);
		fileCount++;
	}
	AfxMessageBox("全部文件处理完毕");
	return fileCount;
}

void hzInFile(CString FileName)
{
	FILE*in;
	unsigned char c1,c2;
	int id;
	in=fopen((const char*)FileName,"rb");
	if(in==NULL){AfxMessageBox("无法输入文件");return;}
	while(!feof(in)){
		c1=(unsigned char)fgetc(in);
		if(c1<128)continue;
		if(c1<176){c2=fgetc(in);continue;}
		c2=(unsigned char)fgetc(in);
		id=HZ_ID(c1,c2);
		HZFreq[id]++;
	}
	fclose(in);
	return;
}

void HZPairInFile(CString FileName)
{
	FILE *in;
	unsigned char c1,c2;
	char zz[5];
	int id;
	in=fopen((const char*)FileName,"rb");
	if(in==NULL)
	{
		AfxMessageBox("无法打开输入文件");
		return;
	}
	zz[0]='\0';
	while(!feof(in)){
		c1=(unsigned char)fgetc(in);
		if(c1<128)
		{
			zz[0]='\0';
			continue;
		}
		else if(c1>176)
		{
			c2=fgetc(in);
			zz[0]='\0';
			continue;
		}
		c2=(unsigned char)fgetc(in);
		id=HZ_ID(c1,c2);
		HZFreq[id]++;
		if(zz[0]!='\0')
		{
			zz[2]=c1;
			zz[3]=c2;
			hzPairs.Insert(zz);
		}
		zz[0]=c1;zz[1]=c2;
	}
	fclose(in);
	return;
}
void LoadHZFreq()
{
	char buf[512];
	FILE *in;
	CFile inFile;
	if(inFile.Open("hzpairs.dat",CFile::modeRead)){
		CArchive ar(&inFile,CArchive::load,512,buf);
		hzPairs.Serialize(ar);
		inFile.Close();
	}
	in=fopen("hzfreq.dat","rb");
	if(in){
		fread(HZFreq,sizeof(int),HZ_NUM,in);
		fclose(in);
	}
	else for(int i=0;i<HZ_NUM;i++)
		HZFreq[i]=0;
}
void StoreHZFreq()
{
	char buf[512];
	FILE*out;
	CFile outFile;
	if(outFile.Open("hzpairs.dat",CFile::modeWrite|CFile::modeCreate)){
		CArchive ar(&outFile,CArchive::store,512,buf);
		hzPairs.Serialize(ar);
	}
	out=fopen("hzfreq.dat","wb");
	if(out){
		fwrite(HZFreq,sizeof(int),HZ_NUM,out);
		fclose(out);
	}
}
void OnHzReport()
{
	int hzCount=0,CorpusSize=0;
	for(int id=0;id<HZ_NUM;id++){
		if(HZFreq[id]>0){
			hzCount++;
			CorpusSize+=HZFreq[id];
		}
	}
	CString msg;
	msg.Format("已经统计语料共%d字;\n其中不同汉字%d个;\n不同双字%d种",CorpusSize,hzCount,hzPairs.GetSize());
	AfxMessageBox(msg);
}
void OnSeekHz()
{
	CString key,msg;
	if(!GetData("输入要找的单字或双字：",key))
		return;
	key.TrimRight();key.TrimLeft();
	int id,n=key.GetLength();
	if(n==2){
		id=HZ_ID((unsigned char)key[0],(unsigned char)key[1]);
		msg.Format("该汉字出现%d次",HZFreq[id]);
	}
	else{
		if(hzPairs.Search((const char*)key,id)){
			HZPair*hp=(HZPair*)hzPairs.GetAt(id);
			msg.Format("该双字出现%d次",hp->freq);
		}
	}
	if(msg.IsEmpty())
		msg="找不到，或者输入错误";
	AfxMessageBox(msg);
}
int FindOneHZ(const char*str,const char*hz)
{
	char*p=(char*)str;
	while(*p!='\0'){
		if(*p>0)p++;
		else if(*p==*hz&&*(p+1)==*(hz+1))return (p-str);
		else p=p+2;
	}
	return -1;
}
CString wordType(CString &w)
{
	int n=w.GetLength();
	if(n==4&&w.Left(2)==w.Right(2))return "AA";
	else if(n==6&&w.Left(2)==w.Right(2)){
		if(w.Mid(2,2)=="一")return "A一A";
		else if(w.Mid(2,2)="了")return "A了A";
		else if(w.Mid(2,2)="不")return "A不A";
		else return"";
	}
	else if(n==6&&w.Left(2)!=w.Mid(2,2)&&w.Mid(2,2)==w.Right(2))return"ABB";
	else if(n==8&&w.Left(2)==w.Mid(2,2)&&w.Mid(4,2)==w.Right(2))return"AABB";
	else if(n==8&&w.Left(2)==w.Mid(4,2)&&w.Mid(2,2)==w.Right(2))return"ABAB";
	else return"";
}
int GetSentence(CString&s)
{
	char w[3];
	int i=0,n=s.GetLength();
	BOOL foundSentence=FALSE;
	while(i<n){
		if(s[i]>0){
			if(strchr(e_puncture1,s[i])){
				foundSentence=TRUE;
				i++;break;
			}
			else i++;
		}
		else{
			w[0]=s[i];w[1]=s[i+1];w[2]=0;
			if(strstr(c_puncture1,w)){
				foundSentence=TRUE;
				i+=2;break;
			}
			else i+=2;
		}
	}
	if(!foundSentence)
		return 0;
	else{
		while(i<n){
			if(s[i]>0){
				if(strchr(e_puncture1,s[i])||strchr(e_puncture2,s[i]))i++;
				else return i;
			}
			else{
				w[0]=s[i];w[1]=s[i+1];w[2]=0;
				if(strstr(c_puncture1,w)||strstr(c_puncture2,w))i+=2;
				else return i;
			}
		}
		return n;
	}
}
CString ChangeExt(CString oldName,CString newExt)
{
	int i=oldName.ReverseFind('.');
	int j=oldName.ReverseFind('\\');
	if(i>j)return oldName.Left(i+1)+newExt;
	else return oldName+"."+newExt;
}
void CutSentence(CString FileName)
{
	FILE*in,*out;
	in=fopen((const char*)FileName,"rt");
	if(in==NULL){AfxMessageBox("无法打开文件");return;}
	FileName=ChangeExt(FileName,"sen");
	out=fopen((const char*)FileName,"wt");
	if(out==NULL){AfxMessageBox("无法创建文件");fclose(in);return;}
	CStdioFile inFile(in),outFile(out);
	char s[2048];
	CString line;int i,n;
	while(inFile.ReadString(s,2048)){
		line=s;
		n=line.GetLength();
		while((i=GetSentence(line))>0){
			outFile.WriteString(line.Left(i)+'\n');
			line=line.Mid(i);
		}
		if(!line.IsEmpty()){
			if(n==line.GetLength()&&n<60)
				outFile.WriteString(line+'\n');
			else outFile.WriteString(line);
		}
	}
	inFile.Close();
	outFile.Close();
}
void OnSentenceInFiles()
{
	ProcessFiles("*","*.*",CutSentence);
}

CString SegmentHzStrMM(CString s1)
{
	CString s2="";
	while(!s1.IsEmpty()){
		int len=s1.GetLength();
		if(len>MaxWordLength)len=MaxWordLength;
		CString w=s1.Left(len);
		while(len>2&&Dict.GetFreq(w)==-1){
			len-=2;w=w.Left(len);
		}
		s2+=w+Separator;
		s1=s1.Mid(w.GetLength());
	}
	return s2;
}

CString SegmentSentenceMM(CString s1)
{
	CString s2="";
	int i;
	while(!s1.IsEmpty()){
		unsigned char ch=(unsigned char)s1[0];
		if(ch<128){
			i=1;
			while(i<s1.GetLength()&&(unsigned char)s1[i]<128)i++;
			s2+=s1.Left(i)+Separator;
			s1=s1.Mid(i);
			continue;
		}
		else if(ch<176){
			s2+=s1.Left(2)+Separator;
			s1=s1.Mid(2);
			continue;
		}
		i=2;
		while((unsigned char)s1[i]>=176)i+=2;
		s2+=SegmentHzStrMM(s1.Left(i));
		s1=s1.Mid(i);
	}
	return s2;
}

void SegmentAFileMM(CString FileName)
{
	FILE*in,*out;
	in=fopen((const char*)FileName,"rt");
	if(in==NULL){
		AfxMessageBox("无法打开文件");
		return;
	}
	FileName=ChangeExt(FileName,"cut");
	out=fopen((const char*)FileName,"wt");
	if(out==NULL){
		AfxMessageBox("无法创建文件");
		fclose(in);
		return;
	}
	CStdioFile inFile(in),outFile(out);

	char s[2048];
	CString line;
	while(inFile.ReadString(s,2048));{
		line=s;
		line=SegmentSentenceMM(line);
		outFile.WriteString(line);
	}
	inFile.Close();
	outFile.Close();
}


CString SegmentHzStrMP(CString s1)
{
	int len=s1.GetLength();
	long n=getTmpWords(s1);
	long minID=-1;
	long i;
	for(i=0;i<n;i++){
		getPrev(i);
		if(Candidates[i].offset+Candidates[i].length==len){
			if(minID==-1||Candidates[i].sumFee<Candidates[minID].sumFee)minID=i;
		}
	}
	CString s2="";
	CString tmp="";
	for(i=minID;i>=0;i=Candidates[i].goodPrev){
		CString w=s1.Mid(Candidates[i].offset,Candidates[i].length);
		if(w.GetLength()==2)
			tmp=w+tmp;
		else{
			if(tmp.GetLength()>0){
				//s2=s1.Mid(Candidates[i].offset,Candidates[i].length)+Separator+s2;
				if(tmp.GetLength()==2)
					s2=tmp+Separator+s2;
				else
					s2=CheckStr(tmp)+Separator+s2;
				tmp="";
			}
			s2=w+Separator+s2;
		}
	}
	if(tmp.GetLength()>0){
		if(tmp.GetLength()==2)
			s2=tmp+Separator+s2;
		else
			s2=CheckStr(tmp)+Separator+s2;
		tmp="";
	}
	return s2;
}
long getTmpWords(CString&s)
{
	long i=0,j,len,freq,n=s.GetLength();
	CString w;
	for(j=0;j<n;j+=2){
		for(len=2;len<=MaxWordLength;len+=2){
			w=s.Mid(j,len);
			freq=Dict.GetFreq(w);
			if(len>2&&freq==-1)continue;
			if(freq==-1)freq=0;
			Candidates[i].offset=j;
			Candidates[i].length=len;
			Candidates[i].fee=-log((double)(freq+1)/Corpus_Size);
			Candidates[i].sumFee=0.0F;
			i++;
		}
	}
	return i;
}

void getPrev(long i)
{
	if(Candidates[i].offset==0){
		Candidates[i].goodPrev=-1;
		Candidates[i].sumFee=Candidates[i].fee;
		return;
	}
	long j,minID=-1;
	for(j=i-1;j>=0;j--)
		if(Candidates[j].offset+Candidates[j].length==Candidates[i].offset)
			break;
		for(;Candidates[j].offset+Candidates[j].length==Candidates[i].offset;j--)
			if(minID==-1||Candidates[j].sumFee<Candidates[minID].sumFee)
				minID=j;
			Candidates[i].goodPrev=minID;
			Candidates[i].sumFee=Candidates[i].fee+Candidates[minID].sumFee;
			return;
}
CString SegmentSentenceMP(CString s1)
{
	CString s2;
	return s2;
}
void SegmentAFileMP(CString FileName)
{
}
double sFee(CString z)
{
	int wFreq=Dict.GetFreq(z);
	if(wFreq==-1)
		wFreq=0;
	double wFee=-log((double)(wFreq+1)/Corpus_Size);
	int id=HZ_ID((unsigned char)z[0],(unsigned char)z[1]);
	if(id>=0&&id<HZ_NUM&&namezis[id].sName>0)
		return -log((double)(namezis[id].sName+1)/SurNameSize)-wFee;
	else
		return 20.0;
}
double gFee(CString z)
{
	int wFreq=Dict.GetFreq(z);
	if(wFreq==-1)
		wFreq=0;
	double wFee=-log((double)(wFreq+1)/Corpus_Size);
	int id=HZ_ID((unsigned char)z[0],(unsigned char)z[1]);
	if(id>=0&&id<HZ_NUM){
		if(namezis[id].gName>0)
			return -log((double)(namezis[id].gName+1)/GivenNameSize)-wFee;
		else
			return -log(1/GivenNameSize)-wFee;
	}
	else
		return 20.0;
}
double sgFee(CString sg)
{
	double fee=Dict.GetFee(sg,TRUE);
	if(fee<20.0)
		return fee;
	if(sg.GetLength()==4){
		fee=Dict.GetFee(sg,FALSE);
		if(fee<20.0)
			return fee;
	}
	fee=sFee(sg.Left(2))+gFee(sg.Mid(2,2));
	if(sg.GetLength()==4)
		fee+=-log(0.37);
	else
		fee+=gFee(sg.Right(2))+(-log(0.63));
	return fee;
}
CString CheckStr(CString s1)
{
	CObArray maybeNames;
	CMaybeName*p,*p1,*p2;
	int i,j,len;
	for(i=0;i<s1.GetLength();i+=2){
		for(len=4;len<=6&&i+len<=s1.GetLength();len+=2){
			double fee=sgFee(s1.Mid(i,len));
			if(len==4&&fee>=Max2Fee||len>=6&&fee>=Max3Fee)continue;
			p=new CMaybeName(i,len,fee);
			maybeNames.Add(p);
		}
	}
	BOOL iDeleted=FALSE;
	for(i=0;i<maybeNames.GetSize();){
		for(j=i+1;j<=i+2&&j<maybeNames.GetSize();){
			p1=(CMaybeName*)maybeNames[i];
			p2=(CMaybeName*)maybeNames[j];
			if(isHomoPair(p1,p2)){
				if(p1->fee>p2->fee){
					maybeNames.RemoveAt(i);
					iDeleted=TRUE;
					break;
				}
				else maybeNames.RemoveAt(j);
			}
			else if(isCrossPair(p1,p2)){
				if(p1->fee<=p2->fee)
					maybeNames.RemoveAt(j);
				else{
					maybeNames.RemoveAt(i);
					iDeleted=TRUE;
					break;
				}
				else j++;
			}
			if(!iDeleted)
				i++;
			else
				iDeleted=FALSE;
		}
		//以下生成新的词串
	CString s2;
	if(maybeNames.GetSize()==0){
		for(i=0;i<s1.GetLength();i+=2)
			s2+=s1.Mid(i,2)+Separator;
		return s2;
	}
	for(i=0;i<maybeNames.GetSize();i++){
		if(i==0)
			j=0;
		else
			j=p->offset+p->length;
		p=(CMaybeName*)maybeName[i];
		for(;j<p->offset;j+=2)
			s2+=s1.Mid(j,2)+Separator;
		CString w=s1.Mid(p->offset,p->length);
		s2+=w+Separator;
		CString sName=w.Left(2),gName=w.Mid(2);
		Dict.Insert(sName,gName,p->fee);
	}
	for(j=p->offset+p->length;j<s1.GetLength();j+=2)
		s2+=s1.Mid(j,2)+Separator;
	return s2;
}