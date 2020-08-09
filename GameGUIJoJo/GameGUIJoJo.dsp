# Microsoft Developer Studio Project File - Name="GameGUIJoJo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=GameGUIJoJo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GameGUIJoJo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GameGUIJoJo.mak" CFG="GameGUIJoJo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GameGUIJoJo - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "GameGUIJoJo - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GameGUIJoJo - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GAMEGUIJOJO_EXPORTS" /YX /FD /c
# ADD CPP /nologo /G5 /MD /W3 /GX /Zi /Ox /Ot /Og /Oi /Oy- /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GAMEGUI_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 /nologo /dll /map /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying $(InputName) binaries to $(ENGINE_DIR)\Mods\DIO\Bin
InputPath=.\Release\GameGUIJoJo.dll
InputName=GameGUIJoJo
SOURCE="$(InputPath)"

"$(ENGINE_DIR)\Mods\DIO\Bin\$(InputName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy Release\$(InputName).dll $(ENGINE_DIR)\Mods\DIO\Bin >nul 
	copy Release\$(InputName).map $(ENGINE_DIR)\Mods\DIO\Bin >nul 
	copy Release\$(InputName).lib $(ENGINE_DIR)\Mods\DIO\Bin >nul 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "GameGUIJoJo - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GAMEGUIJOJO_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /G5 /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GAMEGUI_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /dll /map /debug /machine:I386 /out:"Debug/GameGUIJoJoD.dll" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying $(InputName) binaries to $(ENGINE_DIR)\Mods\DIO\Bin\Debug
InputPath=.\Debug\GameGUIJoJoD.dll
InputName=GameGUIJoJoD
SOURCE="$(InputPath)"

"$(ENGINE_DIR)\Mods\DIO\Bin\Debug\$(InputName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy Debug\$(InputName).dll $(ENGINE_DIR)\Mods\DIO\Bin\Debug >nul 
	copy Debug\$(InputName).map $(ENGINE_DIR)\Mods\DIO\Bin\Debug >nul 
	copy Debug\$(InputName).lib $(ENGINE_DIR)\Mods\DIO\Bin\Debug >nul 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "GameGUIJoJo - Win32 Release"
# Name "GameGUIJoJo - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\GameGUIMP\ActionsListControl.cpp
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\AxisListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\ConsoleSymbolsCombo.cpp
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\DlgAudioQuality.cpp
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\DlgConsole.cpp
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\DlgEditButtonAction.cpp
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\DlgPlayerAppearance.cpp
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\DlgPlayerControls.cpp
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\DlgPlayerSettings.cpp
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\DlgRenameControls.cpp
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\DlgSelectPlayer.cpp
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\DlgVideoQuality.cpp
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\EditConsole.cpp
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\GameGUI.cpp
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\LocalPlayersList.cpp
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\PressKeyEditControl.cpp
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\GameGUIMP\ActionsListControl.h
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\AxisListCtrl.h
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\ConsoleSymbolsCombo.h
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\DlgAudioQuality.h
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\DlgConsole.h
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\DlgEditButtonAction.h
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\DlgPlayerAppearance.h
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\DlgPlayerControls.h
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\DlgPlayerSettings.h
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\DlgRenameControls.h
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\DlgSelectPlayer.h
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\DlgVideoQuality.h
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\EditConsole.h
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\GameGUI.h
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\LocalPlayersList.h
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\PressKeyEditControl.h
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\resource.h
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\GameGUIMP\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\cursor_u.bmp
# End Source File
# Begin Source File

SOURCE=..\GameGUIMP\GameGUI.rc
# End Source File
# End Group
# Begin Group "Wizard Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\GameGUIMP\GameGUIMP.clw
# End Source File
# End Group
# End Target
# End Project
