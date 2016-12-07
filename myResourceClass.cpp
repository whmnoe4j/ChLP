// myResourceClass.cpp : implementation file
//

#include "stdafx.h"
#include "现代汉语自动分析.h"
#include <io.h>		// 有 _findfirst( )、_findnext( )的函数原型
#include <direct.h> 	// 有 _chdir( ) 的函数原型
#include <errno.h> 		// 有系统变量 errno
#include "myResourceClass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileAttributes dialog


CFileAttributes::CFileAttributes(CWnd* pParent /*=NULL*/)
	: CDialog(CFileAttributes::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileAttributes)
	m_Sample = FALSE;
	m_Author = _T("");
	m_Category = 0;
	m_Newspaper = _T("");
	m_Year = 1998;
	//}}AFX_DATA_INIT
}


void CFileAttributes::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileAttributes)
	DDX_Control(pDX, IDC_NEWSPAPER, m_NewspaperCtrl);
	DDX_Control(pDX, IDC_SPIN_YEAR, m_SpinYear);
	DDX_Check(pDX, IDC_AS_SAMPLE, m_Sample);
	DDX_Text(pDX, IDC_AUTHOR, m_Author);
	DDX_Radio(pDX, IDC_CATEGORY, m_Category);
	DDX_CBString(pDX, IDC_NEWSPAPER, m_Newspaper);
	DDX_Text(pDX, IDC_YEAR, m_Year);
	DDV_MinMaxInt(pDX, m_Year, 1949, 2050);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileAttributes, CDialog)
	//{{AFX_MSG_MAP(CFileAttributes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileAttributes message handlers

void CFileAttributes::OnOK() 
{
	// TODO: Add extra validation here

	UpdateData(TRUE);  // 将用户输入的数据读到成员变量中来
	CString msg, Class;
	switch(m_Category) {
	case 0:	Class="政治"; break;
	case 1:	Class="科技"; break;
	case 2:	Class="文教"; break;
	case 3:	Class="体育"; break;
	case 4:	Class="文学"; break;
	}

	msg.Format("作者：%s; 分类：%s;\n出处：%s;\n发表时间：%d年;\n",
		(const char *)m_Author, 
		(const char *)Class, 
		(const char *)m_Newspaper, 
		m_Year);
	if(m_Sample) msg+="作为样本"; else msg+="不作为样本";
	  AfxMessageBox(msg);

	CDialog::OnOK();
}

BOOL CFileAttributes::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_NewspaperCtrl.SetWindowText("人民日报");
	// 设置组合框中的编辑框的缺省值
	// 也可直接在构造函数中设置：m_Newspaper=_T("人民日报");
	m_SpinYear.SetRange(1949,2050);
	// 设置微调器的整数范围

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
/////////////////////////////////////////////////////////////////////////////
// CGetDataDlg dialog


CGetDataDlg::CGetDataDlg(const char *Prompt, CWnd* pParent /*=NULL*/)
	: CDialog(CGetDataDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGetDataDlg)
	DataString = _T("");
	//}}AFX_DATA_INIT
	PromptStr=Prompt;
}


void CGetDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetDataDlg)
	DDX_Text(pDX, IDC_EDIT1, DataString);
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

BOOL GetData(const char *Prompt, CString& Data)
{	// 输入一个字符串
	  CGetDataDlg dlg(Prompt); // 调用对话框类的构造函数
	  if(dlg.DoModal( )!=IDOK) return FALSE;  // 如果用户取消了对话框
	  Data=dlg.DataString;  // 给形参赋值
	  return TRUE;
}

BOOL GetData(const char *Prompt, int& Data)
{	// 输入一个整数
	  CGetDataDlg dlg(Prompt);
	  if(dlg.DoModal( )!=IDOK) return FALSE;
	  dlg.DataString.TrimLeft( );		// 压缩左边空格
	  dlg.DataString.TrimRight( );	// 压缩右边空格
	  Data=atoi((const char *)(dlg.DataString));  // 转换为整数
	  return TRUE;
}


BOOL GetData(const char *Prompt, double& Data)
{	// 输入一个实数
	  CGetDataDlg dlg(Prompt);
	  if(dlg.DoModal( )!=IDOK) return FALSE;
	  dlg.DataString.TrimLeft( );
	  dlg.DataString.TrimRight( );
	  Data=atof((const char *)(dlg.DataString));
	  return TRUE;
}


int ProcessFiles(void (*ProcessAFile)(CString fileName))
{ // 只有一个参数，即处理单个文件的函数指针
  CString FileName;
  if(!GetData("输入文件名（可含通配符）：", FileName))  return 0;
  int i=FileName.ReverseFind('\\');  // 看是否包含路径名
  if(i>0) {  // 如果指定了路径名
		if(_chdir ((const char *)(FileName.Left(i)))!=0) { // 如果不能进入该目录
		  AfxMessageBox("路径名错误！");
		  return 0;
		}
  	FileName=FileName.Mid(i+1);  // 去掉路径名
	}
	_finddata_t info;  // 存放匹配文件信息的结构变量
	long handle=_findfirst(FileName.GetBuffer(FileName.GetLength( )), &info);
	if(errno==ENOENT) {
		AfxMessageBox("没有找到匹配文件！");
		return 0;
	}
	else if(errno==EINVAL) {
		AfxMessageBox("非法文件名！");
		return 0;
	}
	int fileCount=0;
	do {
		ProcessAFile(info.name);
		fileCount++;
  }  while (_findnext(handle, &info)==0);
	errno=0;  // 重新设置错误编号，0表示没有错误
	AfxMessageBox("全部文件处理完毕");
	return fileCount;
}

int ProcessFiles(char *Ext, char *Name, void (*ProcessAFile)(CString fileName))
{
	CFileDialog dlg(TRUE, Ext, Name,  OFN_ALLOWMULTISELECT);
	// 构造文件对话框类的一个对象，允许选择多个文件
	if(dlg.DoModal( )!=IDOK) return 0;
	int fileCount=0;
	CString FileName;
	POSITION pos=dlg.GetStartPosition( ); // 获取第一个文件名的起点
	while(pos!=NULL) {	// 当有文件名可取时
	  FileName=dlg.GetNextPathName(pos);	// 获取文件名，并移到下一个文件名的起点
	  ProcessAFile(FileName);	// 调用处理单个文件的函数
	  fileCount++;
  }
	AfxMessageBox ("全部文件处理完毕");
	return fileCount;
}

/////////////
IMPLEMENT_SERIAL(HZPair, CObject, 0)
	// 序列化函数实现宏
void HZPair::Serialize(CArchive& ar)
{
  int i;
  if(ar.IsStoring( )) {	// 如果是往文件里存放数据
  	for(i=0;i<4;i++) ar << zz[i];
	  ar << freq;
	}
	else {	// 如果是从文件里读出数据
		for(i=0;i<4;i++) ar >> zz[i];
		ar >> freq;
	}
}

///////////////
BOOL CSortedPairs::Search(const char *zz, int &id)
{
  HZPair *hp;
  int left=0, mid, right=GetSize( )-1, cmp;
	  // 开始时将整个数组作为查找范围，
    // left，right分别是查找范围的第一个元素和最后一个元素
  while(left<=right) { // 当查找范围不空
		mid=(left+right)/2;	// 计算查找范围中间元素的序号
		// 注意，这里是整数除法，例如1/2等于0
		hp=(HZPair *)GetAt(mid);	// 取中间元素
  	cmp=strncmp(hp->zz, zz, 4);	// 比较该元素的双字与欲查找的双字
		if(cmp<0) left=mid+1;	
// 如果中间元素的双字较小，把右半段作为新的查找范围
		else if(cmp>0) right=mid-1;
		// 如果中间元素的双字较大，把左半段作为新的查找范围
	  else { id=mid; return TRUE;}	// 如果相等，那就是找到了		
	}
	// 没找到
  id=left; return FALSE; 	// left是插入新元素的合适位置
}

void CSortedPairs::Insert(const char *zz)
{
  HZPair *hp;  int id;
  if(Search(zz, id))  {	// 调用我们自己编写的函数来查找双字，如果找到了
		hp=(HZPair *)GetAt(id);  // 取出该元素
	  hp->AddFreq( );	// 出现次数加1
	}
	else {  // 如果没找到
		hp=new HZPair(zz);	// 构造一个双字对象
		InsertAt(id, hp);	// 插到合适位置
	}
}

int  FindOneHZ (const char *str,  const char *hz)
{
  char *p=(char *)str;
  while(*p!='\0') {
 	  if (*p>0) p++;  // 遇到西文字符
		else 	if (*p==*hz && *(p+1)==*(hz+1)) return  p-str;  // 找到了
		else p+=2;
  }
	return -1;  // 没找到
}

CString wordType(CString & w)
{
  int n=w.GetLength( );
  if(n==4 && w.Left(2)==w.Right(2)) return "AA"; 
  else if(n==6 && w.Left(2)==w.Right(2)) {
 		if(w.Mid(2,2)=="一") return "A一A";
 		else if(w.Mid(2,2)=="了") return "A了A";
		else if(w.Mid(2,2)=="不") return "A不A";
		else return "";
  }
	else if(n==6 && w.Left(2)!=w.Mid(2,2) && w.Mid(2,2)==w.Right(2)) return "ABB";
	else if(n==8 && w.Left(2)==w.Mid(2,2) && w.Mid(4,2)==w.Right(2)) return "AABB";
	else if(n==8 && w.Left(2)==w.Mid(4,2) && w.Mid(2,2)==w.Right(2)) return "ABAB";
	else if(n==8 && w.Left(2)==w.Mid(4,2) && w.Mid(2,2)=="不") return "A不AB";
	else return ""; // 未知类型
}

int GetSentence(CString& s) // 搜索断句位置
{
  char w[3];  // 存放一个中文字符
  int i=0, n=s.GetLength( );
  BOOL foundSentence=FALSE;
  while(i < n ) {
		if(s[i] > 0 ) { // 如果是西文字符
			if(strchr(e_puncture1, s[i])) { // 如果是句末点号
				foundSentence=TRUE;
				i++; break; 
		  }
			else i++;	// 否则继续搜索
		}
		else {	// 如果是中文字符
			w[0]=s[i]; w[1]=s[i+1];  w[2]=0; // 拷贝中文字符
			if(strstr(c_puncture1, w)) { // 如果是句末点号
				foundSentence=TRUE;
				i+=2; break;
			}
			else i+=2;	// 否则继续搜索
		}
  }
	// 以上循环是寻找第一个句末点号
  if(!foundSentence) return 0; // 如果没有找到句末点号
  while( i < n ) {
    if( s[i] > 0 ) {  // 西文字符
		  if(strchr(e_puncture1, s[i]) || strchr(e_puncture2, s[i])) i++;
			// 如果是句末点号或右侧标号，继续搜索
			else return i; // 否则完成搜索  
		}
		else {	// 中文字符
			w[0]=s[i];  w[1]=s[i+1];  w[2]=0; // 拷贝中文字符
			if(strstr(c_puncture1, w) || strstr(c_puncture2, w)) i+=2;
			// 如果是句末点号或右侧标号，继续搜索
			else return i; // 否则完成搜索
		}
	}
	// 以上循环是寻找既非句末点号又非右侧标号的字符
  return n; // 当最后一个字符是句末点号或右侧标号时，返回整个字符串的长度
}

CString ChangeExt(CString oldName, CString newExt)
{
  int i=oldName.ReverseFind('.');	// 从后往前搜索圆点
  int j=oldName.ReverseFind('\\');	// 从后往前搜索反斜杠
  if(i>j) return oldName.Left(i+1)+newExt; // 如果已有后缀，则替换
  else return oldName+"."+newExt;	// 否则加上新后缀
}
