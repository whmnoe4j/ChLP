# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=�ִ������Զ����� - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to �ִ������Զ����� - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "�ִ������Զ����� - Win32 Release" && "$(CFG)" !=\
 "�ִ������Զ����� - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "�ִ������Զ�����.mak" CFG="�ִ������Զ����� - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "�ִ������Զ����� - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "�ִ������Զ����� - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "�ִ������Զ����� - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "�ִ������Զ����� - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\�ִ������Զ�����.exe"

CLEAN : 
	-@erase ".\Release\�ִ������Զ�����.exe"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\�ִ������Զ�����.pch"
	-@erase ".\Release\taggingPOS.obj"
	-@erase ".\Release\WordTagSet.obj"
	-@erase ".\Release\�ִ������Զ�����Doc.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\�ִ������Զ�����.obj"
	-@erase ".\Release\�ִ������Զ�����View.obj"
	-@erase ".\Release\ChildFrm.obj"
	-@erase ".\Release\myResourceClass.obj"
	-@erase ".\Release\retrieval.obj"
	-@erase ".\Release\parsing.obj"
	-@erase ".\Release\�ִ������Զ�����.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)/�ִ������Զ�����.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
RSC_PROJ=/l 0x804 /fo"$(INTDIR)/�ִ������Զ�����.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/�ִ������Զ�����.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/�ִ������Զ�����.pdb" /machine:I386 /out:"$(OUTDIR)/�ִ������Զ�����.exe" 
LINK32_OBJS= \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/taggingPOS.obj" \
	"$(INTDIR)/WordTagSet.obj" \
	"$(INTDIR)/�ִ������Զ�����Doc.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/�ִ������Զ�����.obj" \
	"$(INTDIR)/�ִ������Զ�����View.obj" \
	"$(INTDIR)/ChildFrm.obj" \
	"$(INTDIR)/myResourceClass.obj" \
	"$(INTDIR)/retrieval.obj" \
	"$(INTDIR)/parsing.obj" \
	"$(INTDIR)/�ִ������Զ�����.res"

"$(OUTDIR)\�ִ������Զ�����.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "�ִ������Զ����� - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\�ִ������Զ�����.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\�ִ������Զ�����.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\�ִ������Զ�����.exe"
	-@erase ".\Debug\�ִ������Զ�����.obj"
	-@erase ".\Debug\�ִ������Զ�����Doc.obj"
	-@erase ".\Debug\parsing.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\�ִ������Զ�����View.obj"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\ChildFrm.obj"
	-@erase ".\Debug\retrieval.obj"
	-@erase ".\Debug\WordTagSet.obj"
	-@erase ".\Debug\myResourceClass.obj"
	-@erase ".\Debug\taggingPOS.obj"
	-@erase ".\Debug\�ִ������Զ�����.res"
	-@erase ".\Debug\�ִ������Զ�����.ilk"
	-@erase ".\Debug\�ִ������Զ�����.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/�ִ������Զ�����.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x804 /fo"$(INTDIR)/�ִ������Զ�����.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/�ִ������Զ�����.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/�ִ������Զ�����.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/�ִ������Զ�����.exe" 
LINK32_OBJS= \
	"$(INTDIR)/�ִ������Զ�����.obj" \
	"$(INTDIR)/�ִ������Զ�����Doc.obj" \
	"$(INTDIR)/parsing.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/�ִ������Զ�����View.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/ChildFrm.obj" \
	"$(INTDIR)/retrieval.obj" \
	"$(INTDIR)/WordTagSet.obj" \
	"$(INTDIR)/myResourceClass.obj" \
	"$(INTDIR)/taggingPOS.obj" \
	"$(INTDIR)/�ִ������Զ�����.res"

"$(OUTDIR)\�ִ������Զ�����.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "�ִ������Զ����� - Win32 Release"
# Name "�ִ������Զ����� - Win32 Debug"

!IF  "$(CFG)" == "�ִ������Զ����� - Win32 Release"

!ELSEIF  "$(CFG)" == "�ִ������Զ����� - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "�ִ������Զ����� - Win32 Release"

!ELSEIF  "$(CFG)" == "�ִ������Զ����� - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=".\�ִ������Զ�����.cpp"
DEP_CPP_fab4d6cf=\
	".\StdAfx.h"\
	".\�ִ������Զ�����.h"\
	".\MainFrm.h"\
	".\ChildFrm.h"\
	".\�ִ������Զ�����Doc.h"\
	".\�ִ������Զ�����View.h"\
	

"$(INTDIR)\�ִ������Զ�����.obj" : $(SOURCE) $(DEP_CPP_fab4d6cf) "$(INTDIR)"\
 "$(INTDIR)\�ִ������Զ�����.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "�ִ������Զ����� - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS"\
 /Fp"$(INTDIR)/�ִ������Զ�����.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\�ִ������Զ�����.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "�ִ������Զ����� - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/�ִ������Զ�����.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\�ִ������Զ�����.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\�ִ������Զ�����.h"\
	".\myResourceClass.h"\
	".\WordTagSet.h"\
	".\retrieval.h"\
	".\taggingPOS.h"\
	".\parsing.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\�ִ������Զ�����.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ChildFrm.cpp
DEP_CPP_CHILD=\
	".\StdAfx.h"\
	".\�ִ������Զ�����.h"\
	".\ChildFrm.h"\
	

"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\�ִ������Զ�����.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=".\�ִ������Զ�����Doc.cpp"
DEP_CPP_fab4d6cfbabafab4=\
	".\StdAfx.h"\
	".\�ִ������Զ�����.h"\
	".\�ִ������Զ�����Doc.h"\
	

"$(INTDIR)\�ִ������Զ�����Doc.obj" : $(SOURCE) $(DEP_CPP_fab4d6cfbabafab4) "$(INTDIR)"\
 "$(INTDIR)\�ִ������Զ�����.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=".\�ִ������Զ�����View.cpp"
DEP_CPP_fab4d6cfbabafab4efd3baba=\
	".\StdAfx.h"\
	".\�ִ������Զ�����.h"\
	".\�ִ������Զ�����Doc.h"\
	".\�ִ������Զ�����View.h"\
	

"$(INTDIR)\�ִ������Զ�����View.obj" : $(SOURCE) $(DEP_CPP_fab4d6cfbabafab4efd3baba)\
 "$(INTDIR)" "$(INTDIR)\�ִ������Զ�����.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=".\�ִ������Զ�����.rc"
DEP_RSC_fab4d6cfbabafab4efd3babad4d7efd3=\
	".\res\�ִ������Զ�����.ico"\
	".\res\�ִ������Զ�����Doc.ico"\
	".\res\Toolbar.bmp"\
	".\res\�ִ������Զ�����.rc2"\
	

"$(INTDIR)\�ִ������Զ�����.res" : $(SOURCE)\
 $(DEP_RSC_fab4d6cfbabafab4efd3babad4d7efd3) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\myResourceClass.cpp
DEP_CPP_MYRES=\
	".\StdAfx.h"\
	".\�ִ������Զ�����.h"\
	".\myResourceClass.h"\
	

"$(INTDIR)\myResourceClass.obj" : $(SOURCE) $(DEP_CPP_MYRES) "$(INTDIR)"\
 "$(INTDIR)\�ִ������Զ�����.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\WordTagSet.cpp
DEP_CPP_WORDT=\
	".\StdAfx.h"\
	".\�ִ������Զ�����.h"\
	".\WordTagSet.h"\
	

"$(INTDIR)\WordTagSet.obj" : $(SOURCE) $(DEP_CPP_WORDT) "$(INTDIR)"\
 "$(INTDIR)\�ִ������Զ�����.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\retrieval.cpp
DEP_CPP_RETRI=\
	".\StdAfx.h"\
	".\�ִ������Զ�����.h"\
	".\retrieval.h"\
	

"$(INTDIR)\retrieval.obj" : $(SOURCE) $(DEP_CPP_RETRI) "$(INTDIR)"\
 "$(INTDIR)\�ִ������Զ�����.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\taggingPOS.cpp

!IF  "$(CFG)" == "�ִ������Զ����� - Win32 Release"

DEP_CPP_TAGGI=\
	".\StdAfx.h"\
	".\�ִ������Զ�����.h"\
	".\WordTagSet.h"\
	".\taggingPOS.h"\
	
NODEP_CPP_TAGGI=\
	".\��"\
	

"$(INTDIR)\taggingPOS.obj" : $(SOURCE) $(DEP_CPP_TAGGI) "$(INTDIR)"\
 "$(INTDIR)\�ִ������Զ�����.pch"


!ELSEIF  "$(CFG)" == "�ִ������Զ����� - Win32 Debug"

DEP_CPP_TAGGI=\
	".\StdAfx.h"\
	".\�ִ������Զ�����.h"\
	".\WordTagSet.h"\
	".\taggingPOS.h"\
	

"$(INTDIR)\taggingPOS.obj" : $(SOURCE) $(DEP_CPP_TAGGI) "$(INTDIR)"\
 "$(INTDIR)\�ִ������Զ�����.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\parsing.cpp
DEP_CPP_PARSI=\
	".\StdAfx.h"\
	".\�ִ������Զ�����.h"\
	".\parsing.h"\
	

"$(INTDIR)\parsing.obj" : $(SOURCE) $(DEP_CPP_PARSI) "$(INTDIR)"\
 "$(INTDIR)\�ִ������Զ�����.pch"


# End Source File
# End Target
# End Project
################################################################################
