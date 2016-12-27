// ChLPDoc.cpp : implementation of the CChLPDoc class
//

#include "stdafx.h"
#include "ChLP.h"

#include "ChLPDoc.h"
#include "fileattributes.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int HZFreq[HZ_NUM];
/////////////////////////////////////////////////////////////////////////////
// CChLPDoc

IMPLEMENT_DYNCREATE(CChLPDoc, CDocument)

BEGIN_MESSAGE_MAP(CChLPDoc, CDocument)
//{{AFX_MSG_MAP(CChLPDoc)
ON_COMMAND(ID_FILE_ADD_LINE_NUMBER, OnFileAddLineNumber)
ON_COMMAND(ID_FILE_CLASS, OnFileClass)
ON_COMMAND(ID_FILE_BINARY, OnFileBinary)
ON_COMMAND(ID_FILE_CFILE, OnFileCfile)
ON_COMMAND(ID_FILE_LINES, OnFileLines)
ON_COMMAND(ID_FILE_BATCH, OnFileBatch)
ON_COMMAND(ID_STATISTICS_SINGLE, OnStatisticsSingle)
ON_COMMAND(ID_STATISTICS_DOUBLE, OnStatisticsDouble)
	ON_COMMAND(ID_MAXIMUM_MATCH, OnMaximumMatch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChLPDoc construction/destruction

CChLPDoc::CChLPDoc()
{
	// TODO: add one-time construction code here
	
}

CChLPDoc::~CChLPDoc()
{
}

BOOL CChLPDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChLPDoc serialization

void CChLPDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CChLPDoc diagnostics

#ifdef _DEBUG
void CChLPDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CChLPDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChLPDoc commands

void CChLPDoc::OnFileAddLineNumber() 
{
	// TODO: Add your command handler code here
	FILE *in,*out;
	//in=fopen("ChLP1","rt");
	CFileDialog fileDlg(true);
	if(fileDlg.DoModal()==IDOK){
		in=fopen(fileDlg.GetFileName(),"rt");
		if(in==(FILE*)0xcccccccc){
			AfxMessageBox("未能打开文件");
			return;
		}
		CFileDialog fileSaveDlg(false);
		//fileSaveDlg.(fileDlg.GetFileName());
		if(fileSaveDlg.DoModal()==IDOK){
			out=fopen(fileSaveDlg.GetFileName(),"wt");//fopen("example.txt.sav","wt");
			if(out==NULL){
				AfxMessageBox("无法创建文件");
				return;
			}
			char s[1000];
			int i=1;
			while(fgets(s,1000,in)){
				fprintf(out,"%4d %s",i,s);
				i++;
			}
			fclose(out);
		}
		fclose(in);
	}
	return;
}

void CChLPDoc::OnFileClass() 
{
	// TODO: Add your command handler code here
	FILE*in,*out;
	CFileDialog fileDlg(true),saveDlg(false);
	if(fileDlg.DoModal()==IDOK&&saveDlg.DoModal()==IDOK){
		in=fopen(fileDlg.GetFileName(),"rt");//in=fopen("ChLP1","rt");
		out=fopen(saveDlg.GetFileName(),"wt");//out=fopen("Chlp2","wt");
		if(in==NULL||out==NULL)
		{
			AfxMessageBox("无法打开或创建文件");
			return;
		}
		CStdioFile inFile(in),outFile(out);
		CString s,numString;
		int i=1;
		while(inFile.ReadString(s)){
			numString.Format("%5d",i);
			outFile.WriteString(numString+s+"\n");
			i++;
		}
		inFile.Close();
		outFile.Close();
	}
}

void CChLPDoc::OnFileBinary() 
{
	// TODO: Add your command handler code here
	struct wordFreq{char word[10];int freq;} w;
	strcpy(w.word,"计算机");w.freq=100;
	FILE*in,*out;
	CFileDialog outDlg(false);
	if(outDlg.DoModal()==IDOK){
		out=fopen(outDlg.GetFileName(),"wb");	//out=fopen("wordfreq.dat","wb");
		if(out==NULL){AfxMessageBox("无法创建文件！");return;}
		for(int i=0;i<10;i++)
		fwrite(&w,sizeof(w),1,out);
		fclose(out);
		
		CFileDialog inDlg(true);
		if(inDlg.DoModal()==IDOK){
			strcpy(w.word,"");
			w.freq=0;
			in=fopen(inDlg.GetFileName(),"rb");
			//in=fopen("wordfreq.dat","rb");
			if(in==NULL){AfxMessageBox("无法打开文件！");return;}
			int i=0;
			while(i<10){
				fread(&w,sizeof(w),1,in);
				CString msg;
				msg.Format("词语：%s；词频：%d",w.word,w.freq);
				AfxMessageBox(msg);
				i++;
			}
			fclose(in);
		}
	}
	return;
}

void CChLPDoc::OnFileCfile() 
{
	// TODO: Add your command handler code here
	struct wordFreq{ char word[10];int freq;}w;
	CFile in,out;
	/*strcpy(w.word,"计算机");
	w.freq=100;
	
	  if(!out.Open("wordfreq.dat",CFile::modeWrite|CFile::modeCreate)){
	  AfxMessageBox("无法创建文件！");
	  return;
	  }
	  out.Write(&w,sizeof(w));
	  out.Close();
	  strcpy(w.word,"");
	w.freq=0;*/
	if(!in.Open("wordfreq.dat",CFile::modeRead)){
		AfxMessageBox("无法打开文件！");
		return;
	}
	in.Read(&w,sizeof(w));
	in.Close();
	CString msg;
	msg.Format("词语：%s;        词频：%d",w.word,w.freq);
	AfxMessageBox(msg);
	return;
}

void CChLPDoc::OnFileLines() 
{
	// TODO: Add your command handler code here
	CString fname;//="ChLP2";
//	FILE*in;
	CString msg;
	CFileDialog fileDlg(true);
	if(fileDlg.DoModal()==IDOK){
		fname=fileDlg.GetFileName();
		CountLinesInAFile(fname);
	}
}


void CChLPDoc::OnFileBatch() 
{
	// TODO: Add your command handler code here
	ProcessFiles(CountLinesInAFile);
	//ProcessFiles("txt","*.txt",CountLinesInAFile);
	
}


void CChLPDoc::OnStatisticsSingle() 
{
	// TODO: Add your command handler code here
	for(int i=0;i<HZ_NUM;i++)
		HZFreq[i]=0;
	ProcessFiles(hzInFile);
	FILE*outFile;
	outFile=fopen("hzfreq.txt","wt");
	for(int id=0;id<HZ_NUM;id++)
		if(HZFreq[id]>0)
			fprintf(outFile,"%c%c\t%d\n",id/94+176,id%94+161,HZFreq[id]);
		fclose(outFile);
		return;
}


void CChLPDoc::OnStatisticsDouble() 
{
	extern ADD_HANZI;
	// TODO: Add your command handler code here
	int n=ProcessFiles("txt","*.txt",HZPairInFile);
	if(n>0)
		ADD_HANZI=TRUE;
}

void CChLPDoc::OnMaximumMatch() 
{
	// TODO: Add your command handler code here
	ProcessFiles("sen","*.sen",SegmentAFileMM);
}
