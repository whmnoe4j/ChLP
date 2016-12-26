// FileAttributes.cpp : implementation file
//

#include "stdafx.h"
#include "ChLP.h"
#include "FileAttributes.h"
#include "sortedpairs.h"
#include "hzpair.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

int HZFreq[HZ_NUM];
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
BOOL ADD_HANZI=FALSE;
CSortedPairs hzPairs;
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
