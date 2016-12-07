// retrieval.cpp : implementation file
//

#include "stdafx.h"
#include "�ִ������Զ�����.h"
#include "retrieval.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString corpusName;
extern CStringArray texts; 			// �����ļ�������
extern CHzInfo hzInfo[6768];

void CHzInfo::AddTextID(WORD id)
{
  Count++;		// ���ӳ��ִ���
  int n=TextID.GetSize( ); // ���ж��ٸ���ַ
  if(n>0 && id==TextID[n-1]) return;
  TextID.Add(id);
}

IMPLEMENT_SERIAL(CHzInfo, CObject, 0)
void CHzInfo::Serialize(CArchive& ar)
{
  if(ar.IsStoring( )) { // ��������ݴ���
		ar << Count;  	 // д����ִ���
    Count=0;		 
    TextID.Serialize(ar);  // д���ַ��
		TextID.RemoveAll( ); // �����ַ��
  }
  else {  // �����װ������
		ar >> Count;		// װ����ִ���
    TextID.Serialize(ar); // װ���ַ��
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
  this->SetWindowText(corpusName); // ���öԻ������
  CString s, id;
  for(int i=0; i<texts.GetSize( ); i++) {
    s=texts[i];
		int j=s.ReverseFind('\\'); 
		if(j>0) s=s.Mid(j+1); // ȥ��·����
		id.Format(" %d", i);
		s+=id;		// �����ļ����
		tlist.AddString(s);  // �ӵ��б����ȥ
  }

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTitlesDlg::OnTextContent() 
{
	// TODO: Add your control notification handler code here
	int i=tlist.GetCurSel( ); // ȡ��ǰ��ѡ����б�������
  if(i==LB_ERR) return;    // ����û�û����ѡ��ͷ���
  CString s;  tlist.GetText(i, s); // ȡ��ѡ�б��������
  i=s.ReverseFind(' '); 
  s=s.Mid(i+1);  i=atoi(s);  // i Ϊ��ѡ�����ļ������ַ��������е����
  AfxGetApp( )->OpenDocumentFile(texts[i]); // �򿪸������ļ�
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
		c1=i/94+176;  c2=i%94+161; // ������������Ӧ����
		CString s;
		s.Format("%c%c    %d", c1,c2,hzInfo[i].Count);
		hzList.AddString(s); // �����ֺͳ��ִ����ӵ��б��
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
