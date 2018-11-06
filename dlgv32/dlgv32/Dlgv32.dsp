# Microsoft Developer Studio Project File - Name="dlgv32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=dlgv32 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Dlgv32.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Dlgv32.mak" CFG="dlgv32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dlgv32 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "dlgv32 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Dlgv32", NTAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dlgv32 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /GB /MD /W3 /GR /GX /O2 /Ob2 /I ".." /I "../sdtsxx" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /FD /c
# SUBTRACT CPP /WX /Fr /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\gctpc\Release\gctpc.lib ..\libtiff\Release\libtiff.lib ..\libgeotiff\Release\libgeotiff.lib ..\mvc\Release\mvc.lib ..\ProjectionLib\Release\ProjectionLib.lib wsock32.lib /nologo /subsystem:windows /incremental:yes /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libcmt.lib" /nodefaultlib:"libcd.lib" /nodefaultlib:"libcmtd.lib" /nodefaultlib:"msvcrtd.lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "dlgv32 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "./Debug"
# PROP Intermediate_Dir "./Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W2 /Gi /GR /GX /Od /Ob2 /I ".." /I "..\sdtsxx" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\gctpc\Debug\gctpc.lib ..\libtiff\Debug\libtiff.lib ..\libgeotiff\Debug\libgeotiff.lib ..\mvc\Debug\mvc.lib ..\ProjectionLib\Debug\ProjectionLib.lib wsock32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "dlgv32 - Win32 Release"
# Name "dlgv32 - Win32 Debug"
# Begin Source File

SOURCE=.\ColorListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorListBox.h
# End Source File
# Begin Source File

SOURCE=.\ColorPickerDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorPickerDialog.h
# End Source File
# Begin Source File

SOURCE=.\res\Control.ico
# End Source File
# Begin Source File

SOURCE=.\Controller.cpp
# End Source File
# Begin Source File

SOURCE=.\Controller.h
# End Source File
# Begin Source File

SOURCE=.\CoordinateTransforms.cpp
# End Source File
# Begin Source File

SOURCE=.\CoordinateTransforms.h
# End Source File
# Begin Source File

SOURCE=.\res\cur00001.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00002.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00003.cur
# End Source File
# Begin Source File

SOURCE=.\hlp\CurHelp.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Cursor.ico
# End Source File
# Begin Source File

SOURCE=.\res\cursor2.cur
# End Source File
# Begin Source File

SOURCE=.\DeveloperInfoDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\DeveloperInfoDialog.h
# End Source File
# Begin Source File

SOURCE=.\DistanceController.cpp
# End Source File
# Begin Source File

SOURCE=.\DistanceController.h
# End Source File
# Begin Source File

SOURCE=.\DistanceDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\DistanceDialog.h
# End Source File
# Begin Source File

SOURCE=.\DLG3DegLineGraphic.cpp
# End Source File
# Begin Source File

SOURCE=.\DLG3DegLineGraphic.h
# End Source File
# Begin Source File

SOURCE=.\DLG3Overlay.cpp
# End Source File
# Begin Source File

SOURCE=.\DLG3Overlay.h
# End Source File
# Begin Source File

SOURCE=.\DLG3OverlayComponent.cpp
# End Source File
# Begin Source File

SOURCE=.\DLG3OverlayComponent.h
# End Source File
# Begin Source File

SOURCE=.\DLG3PointGraphic.cpp
# End Source File
# Begin Source File

SOURCE=.\DLG3PointGraphic.h
# End Source File
# Begin Source File

SOURCE=.\DLG3PolylineGraphic.cpp
# End Source File
# Begin Source File

SOURCE=.\DLG3PolylineGraphic.h
# End Source File
# Begin Source File

SOURCE=.\DLGOCategoryPropertyPage.cpp
# End Source File
# Begin Source File

SOURCE=.\DLGOCategoryPropertyPage.h
# End Source File
# Begin Source File

SOURCE=.\DLGOControlPointsPropertyPage.cpp
# End Source File
# Begin Source File

SOURCE=.\DLGOControlPointsPropertyPage.h
# End Source File
# Begin Source File

SOURCE=.\DLGOHeaderPropertyPage.cpp
# End Source File
# Begin Source File

SOURCE=.\DLGOHeaderPropertyPage.h
# End Source File
# Begin Source File

SOURCE=.\DLGOPropertySheet.cpp
# End Source File
# Begin Source File

SOURCE=.\DLGOPropertySheet.h
# End Source File
# Begin Source File

SOURCE=.\DLGOptionsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\DLGOptionsDialog.h
# End Source File
# Begin Source File

SOURCE=.\DLGOverlay.cpp
# End Source File
# Begin Source File

SOURCE=.\DLGOverlay.h
# End Source File
# Begin Source File

SOURCE=.\DLGOverlayComponent.cpp
# End Source File
# Begin Source File

SOURCE=.\DLGOverlayComponent.h
# End Source File
# Begin Source File

SOURCE=.\DLGPointGraphic.cpp
# End Source File
# Begin Source File

SOURCE=.\DLGPointGraphic.h
# End Source File
# Begin Source File

SOURCE=.\Dlgv32.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlgv32.h
# End Source File
# Begin Source File

SOURCE=.\res\dlgv32.ico
# End Source File
# Begin Source File

SOURCE=.\Dlgv32.rc
# End Source File
# Begin Source File

SOURCE=.\Dlgv32Doc.cpp

!IF  "$(CFG)" == "dlgv32 - Win32 Release"

# ADD CPP /Od

!ELSEIF  "$(CFG)" == "dlgv32 - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Dlgv32Doc.h
# End Source File
# Begin Source File

SOURCE=.\res\dlgv32Doc.ico
# End Source File
# Begin Source File

SOURCE=.\Dlgv32View.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlgv32View.h
# End Source File
# Begin Source File

SOURCE=.\DoubleByteGridFile.cpp
# End Source File
# Begin Source File

SOURCE=.\DoubleByteGridFile.h
# End Source File
# Begin Source File

SOURCE=.\DragRectangle.cpp
# End Source File
# Begin Source File

SOURCE=.\DragRectangle.h
# End Source File
# Begin Source File

SOURCE=.\res\Finger.ico
# End Source File
# Begin Source File

SOURCE=.\GeographicOverlay.cpp
# End Source File
# Begin Source File

SOURCE=.\GeographicOverlay.h
# End Source File
# Begin Source File

SOURCE=.\GeoRegion.h
# End Source File
# Begin Source File

SOURCE=.\GeoRegionPoly.cpp
# End Source File
# Begin Source File

SOURCE=.\GeoRegionPoly.h
# End Source File
# Begin Source File

SOURCE=.\GeoTIFFOverlay.cpp
# End Source File
# Begin Source File

SOURCE=.\GeoTIFFOverlay.h
# End Source File
# Begin Source File

SOURCE=.\GeoTIFFProjectionMapper.cpp
# End Source File
# Begin Source File

SOURCE=.\GeoTIFFProjectionMapper.h
# End Source File
# Begin Source File

SOURCE=.\GeoTIFFPropertyPage.cpp
# End Source File
# Begin Source File

SOURCE=.\GeoTIFFPropertyPage.h
# End Source File
# Begin Source File

SOURCE=.\GeoTIFFVerticalMetadataPage.cpp
# End Source File
# Begin Source File

SOURCE=.\GeoTIFFVerticalMetadataPage.h
# End Source File
# Begin Source File

SOURCE=.\GraphicsObject.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphicsObject.h
# End Source File
# Begin Source File

SOURCE=.\InterpolatedIntensity.cpp
# End Source File
# Begin Source File

SOURCE=.\InterpolatedIntensity.h
# End Source File
# Begin Source File

SOURCE=.\InterpolatedRaster.cpp
# End Source File
# Begin Source File

SOURCE=.\InterpolatedRaster.h
# End Source File
# Begin Source File

SOURCE=.\LoadingDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\LoadingDialog.h
# End Source File
# Begin Source File

SOURCE=.\res\Magnify.ico
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MainPropertiesDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\MainPropertiesDialog.h
# End Source File
# Begin Source File

SOURCE=.\MaskedBitmap.cpp
# End Source File
# Begin Source File

SOURCE=.\MaskedBitmap.h
# End Source File
# Begin Source File

SOURCE=.\MC_SBAR.CPP
# End Source File
# Begin Source File

SOURCE=.\MC_SBAR.h
# End Source File
# Begin Source File

SOURCE=.\OverlayComponent.cpp
# End Source File
# Begin Source File

SOURCE=.\OverlayComponent.h
# End Source File
# Begin Source File

SOURCE=.\OverlayFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\OverlayFactory.h
# End Source File
# Begin Source File

SOURCE=.\OverlaySelector.cpp
# End Source File
# Begin Source File

SOURCE=.\OverlaySelector.h
# End Source File
# Begin Source File

SOURCE=.\OverlayTypeSelector.cpp
# End Source File
# Begin Source File

SOURCE=.\OverlayTypeSelector.h
# End Source File
# Begin Source File

SOURCE=.\PanController.cpp
# End Source File
# Begin Source File

SOURCE=.\PanController.h
# End Source File
# Begin Source File

SOURCE=.\PickController.cpp
# End Source File
# Begin Source File

SOURCE=.\PickController.h
# End Source File
# Begin Source File

SOURCE=.\PickDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\PickDialog.h
# End Source File
# Begin Source File

SOURCE=.\PolyRegionController.cpp
# End Source File
# Begin Source File

SOURCE=.\PolyRegionController.h
# End Source File
# Begin Source File

SOURCE=.\ProjectionMesh.cpp
# End Source File
# Begin Source File

SOURCE=.\ProjectionMesh.h
# End Source File
# Begin Source File

SOURCE=.\PropertySheetApplyHandler.h
# End Source File
# Begin Source File

SOURCE=.\ps_PixelShader.cpp
# End Source File
# Begin Source File

SOURCE=.\ps_PixelShader.h
# End Source File
# Begin Source File

SOURCE=.\ps_Vector.cpp
# End Source File
# Begin Source File

SOURCE=.\ps_Vector.h
# End Source File
# Begin Source File

SOURCE=.\RasterMetadataDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\RasterMetadataDialog.h
# End Source File
# Begin Source File

SOURCE=.\RasterOptionsPage.cpp
# End Source File
# Begin Source File

SOURCE=.\RasterOptionsPage.h
# End Source File
# Begin Source File

SOURCE=.\RasterOptionsSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\RasterOptionsSheet.h
# End Source File
# Begin Source File

SOURCE=.\RasterOverlay.cpp
# End Source File
# Begin Source File

SOURCE=.\RasterOverlay.h
# End Source File
# Begin Source File

SOURCE=.\RasterPluginOverlay.cpp
# End Source File
# Begin Source File

SOURCE=.\RasterPluginOverlay.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\RubberBandLine.cpp
# End Source File
# Begin Source File

SOURCE=.\RubberBandLine.h
# End Source File
# Begin Source File

SOURCE=.\SDTS_ABDFRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTS_ABDMRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTS_ACOIRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTS_AHPFRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTS_AHPRRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTS_AHPTRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTS_AHYFRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTS_AMSFRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTS_AMTFRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTS_ANVFRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTS_APLFRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTS_ARDFRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTS_ARDMRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTS_ARRFRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTS_ASCFRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTS_ASMFRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTS_AttModule.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTS_AttModule.h
# End Source File
# Begin Source File

SOURCE=.\SDTS_AttModuleFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTS_AttModuleFactory.h
# End Source File
# Begin Source File

SOURCE=.\SDTS_AttPrimaryModule.h
# End Source File
# Begin Source File

SOURCE=.\SDTS_AttRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTS_AttRecord.h
# End Source File
# Begin Source File

SOURCE=.\SDTS_BFPCRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTS_BFPSRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTS_BGRLRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTS_BMSPRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTS_BMTARecord.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTS_GenericAttRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTS_MDEFFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTS_MDEFFactory.h
# End Source File
# Begin Source File

SOURCE=.\SDTS_MDEFModule.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTS_MDEFModule.h
# End Source File
# Begin Source File

SOURCE=.\SDTS_SpatialAddr.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTS_SpatialAddr.h
# End Source File
# Begin Source File

SOURCE=.\SDTS_Utils.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTS_Utils.h
# End Source File
# Begin Source File

SOURCE=.\SDTSDEMOverlay.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTSDEMOverlay.h
# End Source File
# Begin Source File

SOURCE=.\SDTSDLG_AHDRPage.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTSDLG_AHDRPage.h
# End Source File
# Begin Source File

SOURCE=.\SDTSDLG_DataQualityPage.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTSDLG_DataQualityPage.h
# End Source File
# Begin Source File

SOURCE=.\SDTSDLG_IdenPage.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTSDLG_IdenPage.h
# End Source File
# Begin Source File

SOURCE=.\SDTSDLG_PropSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTSDLG_PropSheet.h
# End Source File
# Begin Source File

SOURCE=.\SDTSDLG_StatPage.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTSDLG_StatPage.h
# End Source File
# Begin Source File

SOURCE=.\SDTSDLGDegLineGraphic.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTSDLGDegLineGraphic.h
# End Source File
# Begin Source File

SOURCE=.\SDTSDLGOverlay.cpp

!IF  "$(CFG)" == "dlgv32 - Win32 Release"

# ADD CPP /Od

!ELSEIF  "$(CFG)" == "dlgv32 - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SDTSDLGOverlay.h
# End Source File
# Begin Source File

SOURCE=.\SDTSDLGPointGraphic.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTSDLGPointGraphic.h
# End Source File
# Begin Source File

SOURCE=.\SDTSDLGPolylineGraphic.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTSDLGPolylineGraphic.h
# End Source File
# Begin Source File

SOURCE=.\SDTSLayerDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTSLayerDialog.h
# End Source File
# Begin Source File

SOURCE=.\ShaderOptionsPage.cpp
# End Source File
# Begin Source File

SOURCE=.\ShaderOptionsPage.h
# End Source File
# Begin Source File

SOURCE=".\res\Space - Earth 1.ico"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TIFFOverlay.cpp
# End Source File
# Begin Source File

SOURCE=.\TIFFOverlay.h
# End Source File
# Begin Source File

SOURCE=.\TIFFPropertyPage.cpp
# End Source File
# Begin Source File

SOURCE=.\TIFFPropertyPage.h
# End Source File
# Begin Source File

SOURCE=.\TIFFPropertySheet.cpp
# End Source File
# Begin Source File

SOURCE=.\TIFFPropertySheet.h
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\VerticalOptionsPage.cpp
# End Source File
# Begin Source File

SOURCE=.\VerticalOptionsPage.h
# End Source File
# Begin Source File

SOURCE=.\ZoomController.cpp
# End Source File
# Begin Source File

SOURCE=.\ZoomController.h
# End Source File
# End Target
# End Project
