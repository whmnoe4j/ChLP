// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ChLP.h"

#include "MainFrm.h"
#include "FileAttributes.h"

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
	ON_COMMAND(ID_TEST_GB2312, OnTestGb2312)
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

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	LoadHZFreq();
}

CMainFrame::~CMainFrame()
{
	StoreHZFreq();
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
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

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
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
	CString s,msg;
	int i;double d;
	if(GetData("输入一个字符串：",s))
		AfxMessageBox("您 输入的字符串是："+s);
	else AfxMessageBox("您没有输入字符串！");

	if(GetData("输入一个整数：",i)){
		msg.Format("输入的整数为%d",i);
		AfxMessageBox(msg);
	}
	else AfxMessageBox("您没有输入整数！");
	if(GetData("输入一个实数：",d)){
		msg.Format("输入的实数为：%7.2f",d);
		AfxMessageBox(msg);
	}
	else AfxMessageBox("您没有输入实数！");
}

void CMainFrame::OnTestGb2312() 
{
	// TODO: Add your command handler code here
	FILE*outFile;
	unsigned char i,j;
	outFile=fopen("gb2312-80.chr","wt");
	for(i=161;i<255;i++)
		for(j=161;j<255;j++)
			fprintf(outFile,"%c%c,%d,%d",i,j,i,j);
			fclose(outFile);
		AfxMessageBox("已生成国标字符集文件：gb2312-80.chr");
		return;
}
