# Microsoft Developer Studio Project File - Name="GameJoJo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=GameJoJo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GameJoJo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GameJoJo.mak" CFG="GameJoJo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GameJoJo - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "GameJoJo - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GameJoJo - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GAMEJOJO_EXPORTS" /YX /FD /c
# ADD CPP /nologo /G5 /MD /W3 /GX /Zi /Ox /Ot /Og /Oi /Oy- /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GAME_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 user32.lib /nologo /subsystem:windows /dll /map /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying $(InputName) binaries to $(ENGINE_DIR)\Mods\StardustCrusaders\Bin
InputPath=.\Release\GameJoJo.dll
InputName=GameJoJo
SOURCE="$(InputPath)"

"$(ENGINE_DIR)\Mods\StardustCrusaders\Bin\$(InputName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy Release\$(InputName).dll $(ENGINE_DIR)\Mods\StardustCrusaders\Bin >nul 
	copy Release\$(InputName).map $(ENGINE_DIR)\Mods\StardustCrusaders\Bin >nul 
	copy Release\$(InputName).lib $(ENGINE_DIR)\Mods\StardustCrusaders\Bin >nul 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "GameJoJo - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GAMEJOJO_EXPORTS" /YX /FD /GZ  /c
# ADD CPP /nologo /G5 /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GAME_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 user32.lib /nologo /subsystem:windows /dll /map /debug /machine:I386 /out:"Debug/GameJoJoD.dll" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying $(InputName) binaries to $(ENGINE_DIR)\Mods\StardustCrusaders\Bin\Debug
InputPath=.\Debug\GameJoJoD.dll
InputName=GameJoJoD
SOURCE="$(InputPath)"

"$(ENGINE_DIR)\Mods\StardustCrusaders\Bin\Debug\$(InputName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy Debug\$(InputName).dll $(ENGINE_DIR)\Mods\StardustCrusaders\Bin\Debug >nul 
	copy Debug\$(InputName).map $(ENGINE_DIR)\Mods\StardustCrusaders\Bin\Debug >nul 
	copy Debug\$(InputName).lib $(ENGINE_DIR)\Mods\StardustCrusaders\Bin\Debug >nul 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "GameJoJo - Win32 Release"
# Name "GameJoJo - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\GameMP\Camera.cpp
# End Source File
# Begin Source File

SOURCE=..\GameMP\CompMessage.cpp
# End Source File
# Begin Source File

SOURCE=..\GameMP\CompModels.cpp
# End Source File
# Begin Source File

SOURCE=..\GameMP\Computer.cpp
# End Source File
# Begin Source File

SOURCE=..\GameMP\Console.cpp
# End Source File
# Begin Source File

SOURCE=..\GameMP\Controls.cpp
# End Source File
# Begin Source File

SOURCE=..\GameMP\Game.cpp
# End Source File
# Begin Source File

SOURCE=..\GameMP\LCDDrawing.cpp
# End Source File
# Begin Source File

SOURCE=..\GameMP\LoadingHook.cpp
# End Source File
# Begin Source File

SOURCE=..\GameMP\Map.cpp
# End Source File
# Begin Source File

SOURCE=..\GameMP\SessionProperties.cpp
# End Source File
# Begin Source File

SOURCE=..\GameMP\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\GameMP\WEDInterface.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\GameMP\Camera.h
# End Source File
# Begin Source File

SOURCE=..\GameMP\CompMessage.h
# End Source File
# Begin Source File

SOURCE=..\GameMP\Computer.h
# End Source File
# Begin Source File

SOURCE=..\GameMP\Game.h
# End Source File
# Begin Source File

SOURCE=..\GameMP\LCDDrawing.h
# End Source File
# Begin Source File

SOURCE=..\GameMP\PlayerSettings.h
# End Source File
# Begin Source File

SOURCE=..\GameMP\SEColors.h
# End Source File
# Begin Source File

SOURCE=..\GameMP\SessionProperties.h
# End Source File
# Begin Source File

SOURCE=..\GameMP\StdAfx.h
# End Source File
# End Group
# End Target
# End Project
