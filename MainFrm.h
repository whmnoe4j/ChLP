// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDataAttributes();
	afx_msg void OnTestFiles();
	afx_msg void OnTestGetData();
	afx_msg void OnGb2312();
	afx_msg void OnSingleHz();
	afx_msg void OnDoubleHz();
	afx_msg void OnSeekHz();
	afx_msg void OnHzReport();
	afx_msg void OnSegmentMm();
	afx_msg void OnSegmentMp();
	afx_msg void OnSegmentSentence();
	afx_msg void OnBindDynamic();
	afx_msg void OnBindSnapshot();
	afx_msg void OnCorpusCreate();
	afx_msg void OnCorpusClose();
	afx_msg void OnCorpusBrowse();
	afx_msg void OnCorpusAdd();
	afx_msg void OnCorpusHanzi();
	afx_msg void OnCorpusOpen();
	afx_msg void OnUpdateCorpusAdd(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCorpusBrowse(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCorpusClose(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCorpusHanzi(CCmdUI* pCmdUI);
	afx_msg void OnRetrieveHzstr();
	afx_msg void OnUpdateRetrieveHzstr(CCmdUI* pCmdUI);
	afx_msg void OnTaggingTagging();
	afx_msg void OnTaggingTagset();
	afx_msg void OnTaggingTrain();
	afx_msg void OnParsingBottomup();
	afx_msg void OnParsingPcfg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
