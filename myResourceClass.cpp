// myResourceClass.cpp : implementation file
//

#include "stdafx.h"
#include "�ִ������Զ�����.h"
#include <io.h>		// �� _findfirst( )��_findnext( )�ĺ���ԭ��
#include <direct.h> 	// �� _chdir( ) �ĺ���ԭ��
#include <errno.h> 		// ��ϵͳ���� errno
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

	UpdateData(TRUE);  // ���û���������ݶ�����Ա��������
	CString msg, Class;
	switch(m_Category) {
	case 0:	Class="����"; break;
	case 1:	Class="�Ƽ�"; break;
	case 2:	Class="�Ľ�"; break;
	case 3:	Class="����"; break;
	case 4:	Class="��ѧ"; break;
	}

	msg.Format("���ߣ�%s; ���ࣺ%s;\n������%s;\n����ʱ�䣺%d��;\n",
		(const char *)m_Author, 
		(const char *)Class, 
		(const char *)m_Newspaper, 
		m_Year);
	if(m_Sample) msg+="��Ϊ����"; else msg+="����Ϊ����";
	  AfxMessageBox(msg);

	CDialog::OnOK();
}

BOOL CFileAttributes::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_NewspaperCtrl.SetWindowText("�����ձ�");
	// ������Ͽ��еı༭���ȱʡֵ
	// Ҳ��ֱ���ڹ��캯�������ã�m_Newspaper=_T("�����ձ�");
	m_SpinYear.SetRange(1949,2050);
	// ����΢������������Χ

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
{	// ����һ���ַ���
	  CGetDataDlg dlg(Prompt); // ���öԻ�����Ĺ��캯��
	  if(dlg.DoModal( )!=IDOK) return FALSE;  // ����û�ȡ���˶Ի���
	  Data=dlg.DataString;  // ���βθ�ֵ
	  return TRUE;
}

BOOL GetData(const char *Prompt, int& Data)
{	// ����һ������
	  CGetDataDlg dlg(Prompt);
	  if(dlg.DoModal( )!=IDOK) return FALSE;
	  dlg.DataString.TrimLeft( );		// ѹ����߿ո�
	  dlg.DataString.TrimRight( );	// ѹ���ұ߿ո�
	  Data=atoi((const char *)(dlg.DataString));  // ת��Ϊ����
	  return TRUE;
}


BOOL GetData(const char *Prompt, double& Data)
{	// ����һ��ʵ��
	  CGetDataDlg dlg(Prompt);
	  if(dlg.DoModal( )!=IDOK) return FALSE;
	  dlg.DataString.TrimLeft( );
	  dlg.DataString.TrimRight( );
	  Data=atof((const char *)(dlg.DataString));
	  return TRUE;
}


int ProcessFiles(void (*ProcessAFile)(CString fileName))
{ // ֻ��һ�����������������ļ��ĺ���ָ��
  CString FileName;
  if(!GetData("�����ļ������ɺ�ͨ�������", FileName))  return 0;
  int i=FileName.ReverseFind('\\');  // ���Ƿ����·����
  if(i>0) {  // ���ָ����·����
		if(_chdir ((const char *)(FileName.Left(i)))!=0) { // ������ܽ����Ŀ¼
		  AfxMessageBox("·��������");
		  return 0;
		}
  	FileName=FileName.Mid(i+1);  // ȥ��·����
	}
	_finddata_t info;  // ���ƥ���ļ���Ϣ�Ľṹ����
	long handle=_findfirst(FileName.GetBuffer(FileName.GetLength( )), &info);
	if(errno==ENOENT) {
		AfxMessageBox("û���ҵ�ƥ���ļ���");
		return 0;
	}
	else if(errno==EINVAL) {
		AfxMessageBox("�Ƿ��ļ�����");
		return 0;
	}
	int fileCount=0;
	do {
		ProcessAFile(info.name);
		fileCount++;
  }  while (_findnext(handle, &info)==0);
	errno=0;  // �������ô����ţ�0��ʾû�д���
	AfxMessageBox("ȫ���ļ��������");
	return fileCount;
}

int ProcessFiles(char *Ext, char *Name, void (*ProcessAFile)(CString fileName))
{
	CFileDialog dlg(TRUE, Ext, Name,  OFN_ALLOWMULTISELECT);
	// �����ļ��Ի������һ����������ѡ�����ļ�
	if(dlg.DoModal( )!=IDOK) return 0;
	int fileCount=0;
	CString FileName;
	POSITION pos=dlg.GetStartPosition( ); // ��ȡ��һ���ļ��������
	while(pos!=NULL) {	// �����ļ�����ȡʱ
	  FileName=dlg.GetNextPathName(pos);	// ��ȡ�ļ��������Ƶ���һ���ļ��������
	  ProcessAFile(FileName);	// ���ô������ļ��ĺ���
	  fileCount++;
  }
	AfxMessageBox ("ȫ���ļ��������");
	return fileCount;
}

/////////////
IMPLEMENT_SERIAL(HZPair, CObject, 0)
	// ���л�����ʵ�ֺ�
void HZPair::Serialize(CArchive& ar)
{
  int i;
  if(ar.IsStoring( )) {	// ��������ļ���������
  	for(i=0;i<4;i++) ar << zz[i];
	  ar << freq;
	}
	else {	// ����Ǵ��ļ����������
		for(i=0;i<4;i++) ar >> zz[i];
		ar >> freq;
	}
}

///////////////
BOOL CSortedPairs::Search(const char *zz, int &id)
{
  HZPair *hp;
  int left=0, mid, right=GetSize( )-1, cmp;
	  // ��ʼʱ������������Ϊ���ҷ�Χ��
    // left��right�ֱ��ǲ��ҷ�Χ�ĵ�һ��Ԫ�غ����һ��Ԫ��
  while(left<=right) { // �����ҷ�Χ����
		mid=(left+right)/2;	// ������ҷ�Χ�м�Ԫ�ص����
		// ע�⣬��������������������1/2����0
		hp=(HZPair *)GetAt(mid);	// ȡ�м�Ԫ��
  	cmp=strncmp(hp->zz, zz, 4);	// �Ƚϸ�Ԫ�ص�˫���������ҵ�˫��
		if(cmp<0) left=mid+1;	
// ����м�Ԫ�ص�˫�ֽ�С�����Ұ����Ϊ�µĲ��ҷ�Χ
		else if(cmp>0) right=mid-1;
		// ����м�Ԫ�ص�˫�ֽϴ󣬰�������Ϊ�µĲ��ҷ�Χ
	  else { id=mid; return TRUE;}	// �����ȣ��Ǿ����ҵ���		
	}
	// û�ҵ�
  id=left; return FALSE; 	// left�ǲ�����Ԫ�صĺ���λ��
}

void CSortedPairs::Insert(const char *zz)
{
  HZPair *hp;  int id;
  if(Search(zz, id))  {	// ���������Լ���д�ĺ���������˫�֣�����ҵ���
		hp=(HZPair *)GetAt(id);  // ȡ����Ԫ��
	  hp->AddFreq( );	// ���ִ�����1
	}
	else {  // ���û�ҵ�
		hp=new HZPair(zz);	// ����һ��˫�ֶ���
		InsertAt(id, hp);	// �嵽����λ��
	}
}

int  FindOneHZ (const char *str,  const char *hz)
{
  char *p=(char *)str;
  while(*p!='\0') {
 	  if (*p>0) p++;  // ���������ַ�
		else 	if (*p==*hz && *(p+1)==*(hz+1)) return  p-str;  // �ҵ���
		else p+=2;
  }
	return -1;  // û�ҵ�
}

CString wordType(CString & w)
{
  int n=w.GetLength( );
  if(n==4 && w.Left(2)==w.Right(2)) return "AA"; 
  else if(n==6 && w.Left(2)==w.Right(2)) {
 		if(w.Mid(2,2)=="һ") return "AһA";
 		else if(w.Mid(2,2)=="��") return "A��A";
		else if(w.Mid(2,2)=="��") return "A��A";
		else return "";
  }
	else if(n==6 && w.Left(2)!=w.Mid(2,2) && w.Mid(2,2)==w.Right(2)) return "ABB";
	else if(n==8 && w.Left(2)==w.Mid(2,2) && w.Mid(4,2)==w.Right(2)) return "AABB";
	else if(n==8 && w.Left(2)==w.Mid(4,2) && w.Mid(2,2)==w.Right(2)) return "ABAB";
	else if(n==8 && w.Left(2)==w.Mid(4,2) && w.Mid(2,2)=="��") return "A��AB";
	else return ""; // δ֪����
}

int GetSentence(CString& s) // �����Ͼ�λ��
{
  char w[3];  // ���һ�������ַ�
  int i=0, n=s.GetLength( );
  BOOL foundSentence=FALSE;
  while(i < n ) {
		if(s[i] > 0 ) { // ����������ַ�
			if(strchr(e_puncture1, s[i])) { // ����Ǿ�ĩ���
				foundSentence=TRUE;
				i++; break; 
		  }
			else i++;	// �����������
		}
		else {	// ����������ַ�
			w[0]=s[i]; w[1]=s[i+1];  w[2]=0; // ���������ַ�
			if(strstr(c_puncture1, w)) { // ����Ǿ�ĩ���
				foundSentence=TRUE;
				i+=2; break;
			}
			else i+=2;	// �����������
		}
  }
	// ����ѭ����Ѱ�ҵ�һ����ĩ���
  if(!foundSentence) return 0; // ���û���ҵ���ĩ���
  while( i < n ) {
    if( s[i] > 0 ) {  // �����ַ�
		  if(strchr(e_puncture1, s[i]) || strchr(e_puncture2, s[i])) i++;
			// ����Ǿ�ĩ��Ż��Ҳ��ţ���������
			else return i; // �����������  
		}
		else {	// �����ַ�
			w[0]=s[i];  w[1]=s[i+1];  w[2]=0; // ���������ַ�
			if(strstr(c_puncture1, w) || strstr(c_puncture2, w)) i+=2;
			// ����Ǿ�ĩ��Ż��Ҳ��ţ���������
			else return i; // �����������
		}
	}
	// ����ѭ����Ѱ�ҼȷǾ�ĩ����ַ��Ҳ��ŵ��ַ�
  return n; // �����һ���ַ��Ǿ�ĩ��Ż��Ҳ���ʱ�����������ַ����ĳ���
}

CString ChangeExt(CString oldName, CString newExt)
{
  int i=oldName.ReverseFind('.');	// �Ӻ���ǰ����Բ��
  int j=oldName.ReverseFind('\\');	// �Ӻ���ǰ������б��
  if(i>j) return oldName.Left(i+1)+newExt; // ������к�׺�����滻
  else return oldName+"."+newExt;	// ��������º�׺
}
