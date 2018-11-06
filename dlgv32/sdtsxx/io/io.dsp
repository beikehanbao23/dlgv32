# Microsoft Developer Studio Project File - Name="io" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=io - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "io.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "io.mak" CFG="io - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "io - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "io - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/sdtsxx/io", XDAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "io - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /GB /MD /W3 /GR /GX /O2 /Ob2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /FD /TP /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "io - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "io___Win"
# PROP BASE Intermediate_Dir "io___Win"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GR /GX /Z7 /Od /I "..\\" /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /FD /TP /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "io - Win32 Release"
# Name "io - Win32 Debug"
# Begin Source File

SOURCE=.\formatparser_tab.c
# End Source File
# Begin Source File

SOURCE=.\lex.sio_8211_yy.c
# End Source File
# Begin Source File

SOURCE=.\sio_8211Converter.cpp
# End Source File
# Begin Source File

SOURCE=.\sio_8211Converter.h
# End Source File
# Begin Source File

SOURCE=.\sio_8211DDR.cpp
# End Source File
# Begin Source File

SOURCE=.\sio_8211DDR.h
# End Source File
# Begin Source File

SOURCE=.\sio_8211DDRField.cpp
# End Source File
# Begin Source File

SOURCE=.\sio_8211DDRField.h
# End Source File
# Begin Source File

SOURCE=.\sio_8211DDRLeader.cpp
# End Source File
# Begin Source File

SOURCE=.\sio_8211DDRLeader.h
# End Source File
# Begin Source File

SOURCE=.\sio_8211Directory.cpp
# End Source File
# Begin Source File

SOURCE=.\sio_8211Directory.h
# End Source File
# Begin Source File

SOURCE=.\sio_8211DirEntry.cpp
# End Source File
# Begin Source File

SOURCE=.\sio_8211DirEntry.h
# End Source File
# Begin Source File

SOURCE=.\sio_8211DR.cpp
# End Source File
# Begin Source File

SOURCE=.\sio_8211DR.h
# End Source File
# Begin Source File

SOURCE=.\sio_8211DRLeader.cpp
# End Source File
# Begin Source File

SOURCE=.\sio_8211DRLeader.h
# End Source File
# Begin Source File

SOURCE=.\sio_8211Field.cpp
# End Source File
# Begin Source File

SOURCE=.\sio_8211Field.h
# End Source File
# Begin Source File

SOURCE=.\sio_8211FieldArea.cpp
# End Source File
# Begin Source File

SOURCE=.\sio_8211FieldArea.h
# End Source File
# Begin Source File

SOURCE=.\sio_8211FieldFormat.cpp
# End Source File
# Begin Source File

SOURCE=.\sio_8211FieldFormat.h
# End Source File
# Begin Source File

SOURCE=.\sio_8211Leader.cpp
# End Source File
# Begin Source File

SOURCE=.\sio_8211Leader.h
# End Source File
# Begin Source File

SOURCE=.\sio_8211Record.cpp
# End Source File
# Begin Source File

SOURCE=.\sio_8211Record.h
# End Source File
# Begin Source File

SOURCE=.\sio_8211SubfieldFormat.cpp
# End Source File
# Begin Source File

SOURCE=.\sio_8211SubfieldFormat.h
# End Source File
# Begin Source File

SOURCE=.\sio_8211Utils.cpp
# End Source File
# Begin Source File

SOURCE=.\sio_8211Utils.h
# End Source File
# Begin Source File

SOURCE=.\sio_Buffer.cpp
# End Source File
# Begin Source File

SOURCE=.\sio_Buffer.h
# End Source File
# Begin Source File

SOURCE=.\sio_Converter.cpp
# End Source File
# Begin Source File

SOURCE=.\sio_Converter.h
# End Source File
# Begin Source File

SOURCE=.\sio_Error.cpp
# End Source File
# Begin Source File

SOURCE=.\sio_Error.h
# End Source File
# Begin Source File

SOURCE=.\sio_Reader.cpp
# End Source File
# Begin Source File

SOURCE=.\sio_Reader.h
# End Source File
# Begin Source File

SOURCE=.\sio_SeqReader.h
# End Source File
# Begin Source File

SOURCE=.\sio_Utils.cpp
# End Source File
# Begin Source File

SOURCE=.\sio_Utils.h
# End Source File
# Begin Source File

SOURCE=.\sio_Writer.cpp
# End Source File
# Begin Source File

SOURCE=.\sio_Writer.h
# End Source File
# Begin Source File

SOURCE=.\y.tab.h
# End Source File
# End Target
# End Project
