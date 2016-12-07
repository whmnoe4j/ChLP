; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "现代汉语自动分析.h"
LastPage=0

ClassCount=11
Class1=CMyApp
Class2=CMyDoc
Class3=CMyView
Class4=CMainFrame

ResourceCount=7
Resource1=IDD_GET_DATA
Resource2=IDD_HZ_COUNT_DLG
Resource3=IDD_FILE_ATTRIBUTES
Class5=CAboutDlg
Class6=CChildFrame
Resource4=IDD_TITLES_DLG
Class7=CFileAttributes
Class8=CGetData
Class9=CWordTagSet
Resource5=IDR_MYTYPE
Resource6=IDD_ABOUTBOX
Class10=CTitlesDlg
Class11=CHzCountDlg
Resource7=IDR_MAINFRAME

[CLS:CMyApp]
Type=0
HeaderFile=现代汉语自动分析.h
ImplementationFile=现代汉语自动分析.cpp
Filter=N

[CLS:CMyDoc]
Type=0
HeaderFile=现代汉语自动分析Doc.h
ImplementationFile=现代汉语自动分析Doc.cpp
Filter=N

[CLS:CMyView]
Type=0
HeaderFile=现代汉语自动分析View.h
ImplementationFile=现代汉语自动分析View.cpp
Filter=C
LastObject=CMyView

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CMDIFrameWnd
VirtualFilter=fWC
LastObject=ID_SEGMENT_MM


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M

[CLS:CAboutDlg]
Type=0
HeaderFile=现代汉语自动分析.cpp
ImplementationFile=现代汉语自动分析.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_DATA_ATTRIBUTES
Command9=ID_TEST_GET_DATA
Command10=ID_TEST_FILES
Command11=ID_GB2312
Command12=ID_BIND_SNAPSHOT
Command13=ID_BIND_DYNAMIC
Command14=ID_SINGLE_HZ
Command15=ID_DOUBLE_HZ
Command16=ID_HZ_REPORT
Command17=ID_SEEK_HZ
Command18=ID_CORPUS_CREATE
Command19=ID_CORPUS_OPEN
Command20=ID_CORPUS_ADD
Command21=ID_RETRIEVE_HZSTR
Command22=ID_CORPUS_BROWSE
Command23=ID_CORPUS_HANZI
Command24=ID_CORPUS_CLOSE
Command25=ID_SEGMENT_SENTENCE
Command26=ID_SEGMENT_MM
Command27=ID_SEGMENT_MP
Command28=ID_TAGGING_TAGSET
Command29=ID_TAGGING_TRAIN
Command30=ID_TAGGING_TAGGING
Command31=ID_PARSING_BOTTOMUP
Command32=ID_PARSING_PCFG
Command33=ID_APP_ABOUT
CommandCount=33

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MYTYPE]
Type=1
Class=CMyView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_EDIT_FIND
Command16=ID_EDIT_REPLACE
Command17=ID_DATA_ATTRIBUTES
Command18=ID_TEST_GET_DATA
Command19=ID_TEST_FILES
Command20=ID_VIEW_TOOLBAR
Command21=ID_VIEW_STATUS_BAR
Command22=ID_WINDOW_NEW
Command23=ID_WINDOW_CASCADE
Command24=ID_WINDOW_TILE_HORZ
Command25=ID_WINDOW_ARRANGE
Command26=ID_APP_ABOUT
CommandCount=26

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_FILE_ATTRIBUTES]
Type=1
Class=CFileAttributes
ControlCount=17
Control1=IDC_CATEGORY,button,1342308361
Control2=IDC_RADIO2,button,1342177289
Control3=IDC_RADIO3,button,1342177289
Control4=IDC_RADIO4,button,1342177289
Control5=IDC_RADIO5,button,1342177289
Control6=IDC_AS_SAMPLE,button,1342242819
Control7=IDC_AUTHOR,edit,1350631552
Control8=IDC_NEWSPAPER,combobox,1344340226
Control9=IDC_YEAR,edit,1350639744
Control10=IDC_SPIN_YEAR,msctls_updown32,1342177458
Control11=IDOK,button,1342242817
Control12=IDCANCEL,button,1342242816
Control13=IDC_STATIC,button,1342177287
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,button,1342177287

[CLS:CFileAttributes]
Type=0
HeaderFile=myResourceClass.h
ImplementationFile=myResourceClass.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CFileAttributes

[DLG:IDD_GET_DATA]
Type=1
Class=CGetData
ControlCount=3
Control1=IDC_EDIT1,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816

[CLS:CGetData]
Type=0
HeaderFile=myresourceclass.h
ImplementationFile=myresourceclass.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CGetData

[CLS:CWordTagSet]
Type=0
HeaderFile=WordTagSet.h
ImplementationFile=WordTagSet.cpp
BaseClass=CDaoRecordset
Filter=N
VirtualFilter=x
LastObject=CWordTagSet

[DB:CWordTagSet]
DB=1
DBType=DAO
ColumnCount=7
Column1=[poss].[wid], 4, 4
Column2=[pos], 12, 4
Column3=[pfreq], 4, 4
Column4=[pid], 4, 4
Column5=[word], 12, 10
Column6=[wfreq], 4, 4
Column7=[words].[wid], 4, 4

[DB:CNameSet]
DB=1
DBType=DAO
ColumnCount=3
Column1=[sname], 12, 2
Column2=[gname], 12, 4
Column3=[fee], 8, 8

[DLG:IDD_TITLES_DLG]
Type=1
Class=CTitlesDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=ID_TEXT_CONTENT,button,1342242816
Control3=IDC_LIST1,listbox,1352728835

[CLS:CTitlesDlg]
Type=0
HeaderFile=retrieval.h
ImplementationFile=retrieval.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CTitlesDlg

[DLG:IDD_HZ_COUNT_DLG]
Type=1
Class=CHzCountDlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_LIST_HZ,listbox,1352728833

[CLS:CHzCountDlg]
Type=0
HeaderFile=retrieval.h
ImplementationFile=retrieval.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CHzCountDlg

