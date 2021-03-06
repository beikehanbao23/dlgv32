# Microsoft Developer Studio Project File - Name="USGSDEMRasterPlugin" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=USGSDEMRasterPlugin - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "USGSDEMRasterPlugin.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "USGSDEMRasterPlugin.mak" CFG="USGSDEMRasterPlugin - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "USGSDEMRasterPlugin - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "USGSDEMRasterPlugin - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "USGSDEMRasterPlugin - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /GB /MD /W3 /GX /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "USGSDEMRasterPlugin - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comctl32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "USGSDEMRasterPlugin - Win32 Release"
# Name "USGSDEMRasterPlugin - Win32 Debug"
# Begin Source File

SOURCE=.\DEMGrid.cxx
# End Source File
# Begin Source File

SOURCE=.\DEMGrid.hxx
# End Source File
# Begin Source File

SOURCE=.\DEMHeader.cxx
# End Source File
# Begin Source File

SOURCE=.\DEMHeader.hxx
# End Source File
# Begin Source File

SOURCE=.\DEMPoint.hxx
# End Source File
# Begin Source File

SOURCE=.\DEMProfile.cxx
# End Source File
# Begin Source File

SOURCE=.\DEMProfile.hxx
# End Source File
# Begin Source File

SOURCE=.\DEMStats.cxx
# End Source File
# Begin Source File

SOURCE=.\DEMStats.hxx
# End Source File
# Begin Source File

SOURCE=.\DEMTypes.hxx
# End Source File
# Begin Source File

SOURCE=.\DEMUtil.cxx
# End Source File
# Begin Source File

SOURCE=.\DEMUtil.hxx
# End Source File
# Begin Source File

SOURCE=.\LayerFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\LayerFactory.h
# End Source File
# Begin Source File

SOURCE=.\LoadingDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\LoadingDialog.h
# End Source File
# Begin Source File

SOURCE=.\ProjectionTypes.h
# End Source File
# Begin Source File

SOURCE=.\RasterPlugin.cpp
# End Source File
# Begin Source File

SOURCE=.\RasterPlugin.h
# End Source File
# Begin Source File

SOURCE=.\RasterPluginLayer.cpp
# End Source File
# Begin Source File

SOURCE=.\RasterPluginLayer.h
# End Source File
# Begin Source File

SOURCE=.\Script1.rc
# End Source File
# Begin Source File

SOURCE=.\shortnam.hxx
# End Source File
# Begin Source File

SOURCE=.\USGSDEMLayer.cpp
# End Source File
# Begin Source File

SOURCE=.\USGSDEMLayer.h
# End Source File
# End Target
# End Project
