# Microsoft Developer Studio Project File - Name="libespresso" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libespresso - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libespressoVC6.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libespressoVC6.mak" CFG="libespresso - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libespresso - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libespresso - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libespresso - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "VC6Release"
# PROP Intermediate_Dir "VC6Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /O2 /I "..\include" /I "..\include\espresso" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FR /Fp"VC6Release/libespresso.pch" /Yu"stdhdr.hxx" /FD /c
# ADD BASE RSC /l 0x1809 /d "NDEBUG"
# ADD RSC /l 0x1809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"VC6Release/libespresso.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"VC6Release\libespresso.lib"

!ELSEIF  "$(CFG)" == "libespresso - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "VC6Debug"
# PROP Intermediate_Dir "VC6Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\include" /I "..\include\espresso" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /Fp"VC6Debug/libespresso.pch" /Yu"stdhdr.hxx" /FD /GZ /c
# ADD BASE RSC /l 0x1809 /d "_DEBUG"
# ADD RSC /l 0x1809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /o"VC6Debug/libespresso.bsc"
# SUBTRACT BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /out:"VC6Debug\libespressod.lib"
# SUBTRACT LIB32 /nologo

!ENDIF 

# Begin Target

# Name "libespresso - Win32 Release"
# Name "libespresso - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Internal Source Files"

# PROP Default_Filter "*.cxx"
# Begin Group "Args Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Arg.cxx
# End Source File
# Begin Source File

SOURCE=.\ArgMgr.cxx
# End Source File
# Begin Source File

SOURCE=.\ArgMgrCLI.cxx
# End Source File
# Begin Source File

SOURCE=.\Args.cxx
# End Source File
# Begin Source File

SOURCE=.\IArgMgr.cxx
# End Source File
# End Group
# Begin Source File

SOURCE=.\StopWatch.cxx
# End Source File
# Begin Source File

SOURCE=.\strings.cxx
# End Source File
# Begin Source File

SOURCE=.\sys.cxx
# End Source File
# Begin Source File

SOURCE=.\threads.cxx
# End Source File
# Begin Source File

SOURCE=.\time.cxx
# End Source File
# End Group
# Begin Source File

SOURCE=.\espresso.cxx
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\stdhdr.cxx
# ADD CPP /Yc"stdhdr.hxx"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "External Header Files"

# PROP Default_Filter "*.hxx;*.inl"
# Begin Group "Args Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\espresso\Arg.hxx
# End Source File
# Begin Source File

SOURCE=..\include\espresso\Arg.inl
# End Source File
# Begin Source File

SOURCE=..\include\espresso\ArgMgr.hxx
# End Source File
# Begin Source File

SOURCE=..\include\espresso\ArgMgrCLI.hxx
# End Source File
# Begin Source File

SOURCE=..\include\espresso\Args.hxx
# End Source File
# Begin Source File

SOURCE=..\include\espresso\IArgMgr.hxx
# End Source File
# End Group
# Begin Source File

SOURCE=..\include\espresso\StopWatch.hxx
# End Source File
# Begin Source File

SOURCE=..\include\espresso\strings.hxx
# End Source File
# Begin Source File

SOURCE=..\include\espresso\sys.hxx
# End Source File
# Begin Source File

SOURCE=..\include\espresso\threads.hxx
# End Source File
# Begin Source File

SOURCE=..\include\espresso\time.hxx
# End Source File
# End Group
# Begin Group "Internal Header Files"

# PROP Default_Filter "*.hxx"
# End Group
# Begin Source File

SOURCE=..\include\espresso.hxx
# End Source File
# Begin Source File

SOURCE=.\stdhdr.hxx
# End Source File
# End Group
# End Target
# End Project
