# Microsoft Developer Studio Project File - Name="ProjectionLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ProjectionLib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ProjectionLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ProjectionLib.mak" CFG="ProjectionLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ProjectionLib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ProjectionLib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/dlgv32_ws/ProjectionLib", IOCAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ProjectionLib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /GB /MD /W3 /GR /GX /O2 /Ob2 /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FD /c
# SUBTRACT CPP /Fr /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "ProjectionLib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
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
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "ProjectionLib - Win32 Release"
# Name "ProjectionLib - Win32 Debug"
# Begin Source File

SOURCE=.\AlaskaConformalProjection.cpp
# End Source File
# Begin Source File

SOURCE=.\AlaskaConformalProjection.h
# End Source File
# Begin Source File

SOURCE=.\AlbersConicProjection.cpp
# End Source File
# Begin Source File

SOURCE=.\AlbersConicProjection.h
# End Source File
# Begin Source File

SOURCE=.\AzimuthalEquidistantProjection.cpp
# End Source File
# Begin Source File

SOURCE=.\AzimuthalEquidistantProjection.h
# End Source File
# Begin Source File

SOURCE=.\AzimuthalProjection.cpp
# End Source File
# Begin Source File

SOURCE=.\AzimuthalProjection.h
# End Source File
# Begin Source File

SOURCE=.\ConicProjection.cpp
# End Source File
# Begin Source File

SOURCE=.\ConicProjection.h
# End Source File
# Begin Source File

SOURCE=.\DatumConvertor.cpp
# End Source File
# Begin Source File

SOURCE=.\DatumConvertor.h
# End Source File
# Begin Source File

SOURCE=.\EquidistantConicProjection.cpp
# End Source File
# Begin Source File

SOURCE=.\EquidistantConicProjection.h
# End Source File
# Begin Source File

SOURCE=.\EquirectangularProjection.cpp
# End Source File
# Begin Source File

SOURCE=.\EquirectangularProjection.h
# End Source File
# Begin Source File

SOURCE=.\GeographicProjection.cpp
# End Source File
# Begin Source File

SOURCE=.\GeographicProjection.h
# End Source File
# Begin Source File

SOURCE=.\GnomonicProjection.cpp
# End Source File
# Begin Source File

SOURCE=.\GnomonicProjection.h
# End Source File
# Begin Source File

SOURCE=.\HotineObliqueMercatorProjection.cpp
# End Source File
# Begin Source File

SOURCE=.\HotineObliqueMercatorProjection.h
# End Source File
# Begin Source File

SOURCE=.\LambertAzimuthalProjection.cpp
# End Source File
# Begin Source File

SOURCE=.\LambertAzimuthalProjection.h
# End Source File
# Begin Source File

SOURCE=.\LambertConformalConicProjection.cpp
# End Source File
# Begin Source File

SOURCE=.\LambertConformalConicProjection.h
# End Source File
# Begin Source File

SOURCE=.\MercatorProjection.cpp
# End Source File
# Begin Source File

SOURCE=.\MercatorProjection.h
# End Source File
# Begin Source File

SOURCE=.\MillerCylindricalProjection.cpp
# End Source File
# Begin Source File

SOURCE=.\MillerCylindricalProjection.h
# End Source File
# Begin Source File

SOURCE=.\OrthographicProjection.cpp
# End Source File
# Begin Source File

SOURCE=.\OrthographicProjection.h
# End Source File
# Begin Source File

SOURCE=.\PolarStereographicProjection.cpp
# End Source File
# Begin Source File

SOURCE=.\PolarStereographicProjection.h
# End Source File
# Begin Source File

SOURCE=.\PolyconicProjection.cpp
# End Source File
# Begin Source File

SOURCE=.\PolyconicProjection.h
# End Source File
# Begin Source File

SOURCE=.\Projection.cpp
# End Source File
# Begin Source File

SOURCE=.\Projection.h
# End Source File
# Begin Source File

SOURCE=.\ProjectionTypes.h
# End Source File
# Begin Source File

SOURCE=.\PseudocylindricalProjection.cpp
# End Source File
# Begin Source File

SOURCE=.\PseudocylindricalProjection.h
# End Source File
# Begin Source File

SOURCE=.\RobinsonProjection.cpp
# End Source File
# Begin Source File

SOURCE=.\RobinsonProjection.h
# End Source File
# Begin Source File

SOURCE=.\SinusoidalProjection.cpp
# End Source File
# Begin Source File

SOURCE=.\SinusoidalProjection.h
# End Source File
# Begin Source File

SOURCE=.\StatePlaneProjection.cpp
# End Source File
# Begin Source File

SOURCE=.\StatePlaneProjection.h
# End Source File
# Begin Source File

SOURCE=.\StereoGraphicProjection.cpp
# End Source File
# Begin Source File

SOURCE=.\StereoGraphicProjection.h
# End Source File
# Begin Source File

SOURCE=.\TransverseMercatorProjection.cpp
# End Source File
# Begin Source File

SOURCE=.\TransverseMercatorProjection.h
# End Source File
# Begin Source File

SOURCE=.\UnknownProjection.cpp
# End Source File
# Begin Source File

SOURCE=.\UnknownProjection.h
# End Source File
# Begin Source File

SOURCE=.\UTMProjection.cpp
# End Source File
# Begin Source File

SOURCE=.\UTMProjection.h
# End Source File
# Begin Source File

SOURCE=.\VanDerGrintenProjection.cpp
# End Source File
# Begin Source File

SOURCE=.\VanDerGrintenProjection.h
# End Source File
# Begin Source File

SOURCE=.\ZonedProjection.cpp
# End Source File
# Begin Source File

SOURCE=.\ZonedProjection.h
# End Source File
# End Target
# End Project
