# Microsoft Developer Studio Project File - Name="builder" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=builder - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "builder.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "builder.mak" CFG="builder - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "builder - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "builder - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/sdtsxx/builder", UAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "builder - Win32 Release"

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
# ADD CPP /nologo /GB /MD /W3 /Gi /GR /GX /O2 /Ob2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "builder - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "builder"
# PROP Intermediate_Dir "builder"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GR /GX /Z7 /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"debug\builder.lib"

!ENDIF 

# Begin Target

# Name "builder - Win32 Release"
# Name "builder - Win32 Debug"
# Begin Source File

SOURCE=.\sb_Arc.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_Arc.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_AreaFillRep.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_AreaFillRep.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_AttAccuracy.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_AttAccuracy.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_CatalogCrossRef.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_CatalogCrossRef.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_CatalogDir.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_CatalogDir.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_CatalogSpatialDom.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_CatalogSpatialDom.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_Cell.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_Cell.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_ColorIndex.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_ColorIndex.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_Completeness.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_Completeness.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_Composite.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_Composite.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_DataDictDefn.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_DataDictDefn.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_DataDictDom.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_DataDictDom.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_DataDictSchema.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_DataDictSchema.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_DimenDefn.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_DimenDefn.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_ExtSpatialRef.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_ExtSpatialRef.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_FontIndex.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_FontIndex.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_ForeignID.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_ForeignID.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_Ident.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_Ident.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_IntSpatialRef.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_IntSpatialRef.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_Line.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_Line.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_Lineage.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_Lineage.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_LineRep.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_LineRep.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_LogicalConsis.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_LogicalConsis.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_PointNode.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_PointNode.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_Polygon.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_Polygon.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_PosAccuracy.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_PosAccuracy.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_RasterDefn.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_RasterDefn.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_RasterLayer.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_RasterLayer.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_Registration.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_Registration.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_Ring.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_Ring.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_Security.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_Security.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_SpatialAddr.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_SpatialAddr.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_SpatialDom.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_SpatialDom.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_SymbolRep.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_SymbolRep.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_TextRep.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_TextRep.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_TransferStats.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_TransferStats.hxx
# End Source File
# Begin Source File

SOURCE=.\sb_Utils.cxx
# End Source File
# Begin Source File

SOURCE=.\sb_Utils.hxx
# End Source File
# End Target
# End Project
