// retrieval.cpp : implementation file
//

#include "stdafx.h"
#include "现代汉语自动分析.h"
#include "retrieval.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString corpusName;
extern CStringArray texts; 			// 语料文件名集合
extern CHzInfo hzInfo[6768];

void CHzInfo::AddTextID(WORD id)
{
  Count++;		// 增加出现次数
  int n=TextID.GetSize( ); // 看有多少个地址
  if(n>0 && id==TextID[n-1]) return;
  TextID.Add(id);
}

IMPLEMENT_SERIAL(CHzInfo, CObject, 0)
void CHzInfo::Serialize(CArchive& ar)
{
  if(ar.IsStoring( )) { // 如果是数据存盘
		ar << Count;  	 // 写入出现次数
    Count=0;		 
    TextID.Serialize(ar);  // 写入地址串
		TextID.RemoveAll( ); // 清除地址串
  }
  else {  // 如果是装入数据
		ar >> Count;		// 装入出现次数
    TextID.Serialize(ar); // 装入地址串
  }
}

/////////////////////////////////////////////////////////////////////////////
// CTitlesDlg dialog


CTitlesDlg::CTitlesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTitlesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTitlesDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTitlesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTitlesDlg)
	DDX_Control(pDX, IDC_LIST1, tlist);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTitlesDlg, CDialog)
	//{{AFX_MSG_MAP(CTitlesDlg)
	ON_BN_CLICKED(ID_TEXT_CONTENT, OnTextContent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTitlesDlg message handlers

BOOL CTitlesDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if(corpusName.IsEmpty( )) return TRUE;
  this->SetWindowText(corpusName); // 设置对话框标题
  CString s, id;
  for(int i=0; i<texts.GetSize( ); i++) {
    s=texts[i];
		int j=s.ReverseFind('\\'); 
		if(j>0) s=s.Mid(j+1); // 去掉路径名
		id.Format(" %d", i);
		s+=id;		// 加上文件序号
		tlist.AddString(s);  // 加到列表框中去
  }

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTitlesDlg::OnTextContent() 
{
	// TODO: Add your control notification handler code here
	int i=tlist.GetCurSel( ); // 取当前所选择的列表项的序号
  if(i==LB_ERR) return;    // 如果用户没有作选择就返回
  CString s;  tlist.GetText(i, s); // 取所选列表项的内容
  i=s.ReverseFind(' '); 
  s=s.Mid(i+1);  i=atoi(s);  // i 为所选语料文件名在字符串数组中的序号
  AfxGetApp( )->OpenDocumentFile(texts[i]); // 打开该语料文件
}
/////////////////////////////////////////////////////////////////////////////
// CHzCountDlg dialog


CHzCountDlg::CHzCountDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHzCountDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHzCountDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CHzCountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHzCountDlg)
	DDX_Control(pDX, IDC_LIST_HZ, hzList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHzCountDlg, CDialog)
	//{{AFX_MSG_MAP(CHzCountDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHzCountDlg message handlers


BOOL CHzCountDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetWindowText(corpusName);
	for(int i=0; i<6768; i++) {
		if(hzInfo[i].Count==0) continue;
		unsigned char c1,c2;
		c1=i/94+176;  c2=i%94+161; // 根据序号求出相应汉字
		CString s;
		s.Format("%c%c    %d", c1,c2,hzInfo[i].Count);
		hzList.AddString(s); // 将汉字和出现次数加到列表框
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
