; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChLPDoc
LastTemplate=COleDocument
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "chlp.h"
LastPage=0

ClassCount=9
Class1=CChildFrame
Class2=CChLPApp
Class3=CAboutDlg
Class4=CChLPDoc
Class5=CChLPView
Class6=CFileAttributes
Class7=CMainFrame

ResourceCount=5
Resource1=IDR_MAINFRAME
Resource2=IDD_FILE_ATTRIBUTES
Resource3=IDD_ABOUTBOX
Resource4=IDD_GET_DATA
Class8=CGetDataDlg
Class9=HZPair
Resource5=IDR_CHLPTYPE

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp

[CLS:CChLPApp]
Type=0
BaseClass=CWinApp
HeaderFile=ChLP.h
ImplementationFile=ChLP.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=ChLP.cpp
ImplementationFile=ChLP.cpp
LastObject=ID_DATA_ATTRIBUTES

[CLS:CChLPDoc]
Type=0
BaseClass=CDocument
HeaderFile=ChLPDoc.h
ImplementationFile=ChLPDoc.cpp
Filter=N
VirtualFilter=DC
LastObject=CChLPDoc

[CLS:CChLPView]
Type=0
BaseClass=CEditView
HeaderFile=ChLPView.h
ImplementationFile=ChLPView.cpp

[CLS:CFileAttributes]
Type=0
BaseClass=CDialog
HeaderFile=FileAttributes.h
ImplementationFile=FileAttributes.cpp
LastObject=ID_DATA_ATTRIBUTES

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=ID_FILE_TEST

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_FILE_ATTRIBUTES]
Type=1
Class=CFileAttributes
ControlCount=17
Control1=IDC_CATEGORY,button,1342308361
Control2=1001,button,1342177289
Control3=1002,button,1342177289
Control4=1003,button,1342177289
Control5=1004,button,1342177289
Control6=IDC_SAMPLE,button,1342242819
Control7=IDC_EDIT_AUTHOR,edit,1350631552
Control8=ID_COMBOBOX_SOURCE,combobox,1344340226
Control9=IDC_EDIT_YEAR,edit,1350639744
Control10=IDC_SPIN_YEAR,msctls_updown32,1342177458
Control11=ID_OK,button,1342242817
Control12=ID_CANCEL,button,1342242816
Control13=65535,button,1342177287
Control14=65535,static,1342308352
Control15=65535,static,1342308352
Control16=65535,static,1342308352
Control17=65535,button,1342177287

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_CHLPTYPE]
Type=1
Class=?
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
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_FILE_ADD_LINE_NUMBER
Command22=ID_FILE_CLASS
Command23=ID_FILE_BINARY
Command24=ID_FILE_CFILE
Command25=ID_FILE_LINES
Command26=ID_FILE_BATCH
Command27=ID_STATISTICS_SINGLE
Command28=ID_STATISTICS_DOUBLE
Command29=ID_DATA_ATTRIBUTES
Command30=ID_TEST_GB2312
Command31=ID_APP_ABOUT
CommandCount=31

[ACL:IDR_MAINFRAME]
Type=1
Class=?
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

[DLG:IDD_GET_DATA]
Type=1
Class=CGetDataDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_DATA_STRING,edit,1350631552

[CLS:CGetDataDlg]
Type=0
HeaderFile=fileattributes.h
ImplementationFile=fileattributes.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CGetDataDlg

[CLS:HZPair]
Type=0
HeaderFile=HZPair.h
ImplementationFile=HZPair.cpp
BaseClass=COleDocument
Filter=N
