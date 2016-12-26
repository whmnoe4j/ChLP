// ChLPView.cpp : implementation of the CChLPView class
//

#include "stdafx.h"
#include "ChLP.h"

#include "ChLPDoc.h"
#include "ChLPView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChLPView

IMPLEMENT_DYNCREATE(CChLPView, CEditView)

BEGIN_MESSAGE_MAP(CChLPView, CEditView)
	//{{AFX_MSG_MAP(CChLPView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChLPView construction/destruction

CChLPView::CChLPView()
{
	// TODO: add construction code here

}

CChLPView::~CChLPView()
{
}

BOOL CChLPView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CChLPView drawing

void CChLPView::OnDraw(CDC* pDC)
{
	CChLPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CChLPView printing

BOOL CChLPView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CChLPView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CChLPView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CChLPView diagnostics

#ifdef _DEBUG
void CChLPView::AssertValid() const
{
	CEditView::AssertValid();
}

void CChLPView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CChLPDoc* CChLPView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChLPDoc)));
	return (CChLPDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChLPView message handlers
