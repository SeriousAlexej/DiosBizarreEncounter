# Microsoft Developer Studio Project File - Name="EntitiesJoJo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=EntitiesJoJo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "EntitiesJoJo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "EntitiesJoJo.mak" CFG="EntitiesJoJo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "EntitiesJoJo - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "EntitiesJoJo - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ENTITIESJOJO_EXPORTS" /YX /FD /c
# ADD CPP /nologo /G5 /MD /W3 /GX /Zi /Ox /Ot /Og /Oi /Oy- /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /FR /Yu"StdH.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 opengl32.lib /nologo /subsystem:windows /dll /map /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying $(InputName) binaries to $(ENGINE_DIR)\Mods\StardustCrusaders\Bin
InputPath=.\Release\EntitiesJoJo.dll
InputName=EntitiesJoJo
SOURCE="$(InputPath)"

"$(ENGINE_DIR)\Mods\StardustCrusaders\Bin\$(InputName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy Release\$(InputName).dll $(ENGINE_DIR)\Mods\StardustCrusaders\Bin >nul 
	copy Release\$(InputName).map $(ENGINE_DIR)\Mods\StardustCrusaders\Bin >nul 
	copy Release\$(InputName).lib $(ENGINE_DIR)\Mods\StardustCrusaders\Bin >nul 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ENTITIESJOJO_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /G5 /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"StdH.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 OpenGL32.lib /nologo /subsystem:windows /dll /map /debug /machine:I386 /out:"Debug/EntitiesJoJoD.dll" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying $(InputName) binaries to $(ENGINE_DIR)\Mods\StardustCrusaders\Bin\Debug
InputPath=.\Debug\EntitiesJoJoD.dll
InputName=EntitiesJoJoD
SOURCE="$(InputPath)"

"$(ENGINE_DIR)\Mods\StardustCrusaders\Bin\Debug\$(InputName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy Debug\$(InputName).dll $(ENGINE_DIR)\Mods\StardustCrusaders\Bin\Debug >nul 
	copy Debug\$(InputName).map $(ENGINE_DIR)\Mods\StardustCrusaders\Bin\Debug >nul 
	copy Debug\$(InputName).lib $(ENGINE_DIR)\Mods\StardustCrusaders\Bin\Debug >nul 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "EntitiesJoJo - Win32 Release"
# Name "EntitiesJoJo - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Common sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\EntitiesMP\Common\Common.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Common\EmanatingParticles.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Common\HUD.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Common\Particles.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Common\PathFinding.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\StdH\StdH.cpp
# ADD CPP /Yc"StdH.h"
# End Source File
# End Group
# Begin Group "JoJo"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\dllmain.cpp
# End Source File
# Begin Source File

SOURCE=.\entitycast.cpp
# End Source File
# Begin Source File

SOURCE=.\event_factory.cpp
# End Source File
# Begin Source File

SOURCE=.\graphics_exports.cpp
# End Source File
# Begin Source File

SOURCE=.\jojo_events.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\EntitiesMP\AirElemental.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\AirShockwave.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\AmmoItem.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\AmmoPack.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\AnimationChanger.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\AnimationHub.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\AreaMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ArmorItem.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\BackgroundViewer.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\BasicEffects.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Beast.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\BigHead.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\BlendController.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\BloodSpray.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Boneman.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Bouncer.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Bullet.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Camera.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\CameraMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\CannonBall.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\CannonRotating.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\CannonStatic.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ChainsawFreak.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Copier.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Counter.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\CrateBus.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\CrateRider.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\CreditsHolder.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Damager.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Debris.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\DebugEntityStatesDisplay.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Demon.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\DestroyableArchitecture.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Devil.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\DevilMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\DevilProjectile.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\DoorController.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EffectMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Effector.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Elemental.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnemyBase.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnemyCounter.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnemyDive.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnemyFly.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnemyMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnemyRunInto.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnemySpawner.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnvironmentBase.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnvironmentMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnvironmentParticlesHolder.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Eruptor.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ExotechLarva.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ExotechLarvaBattery.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ExotechLarvaCharger.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Eyeman.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Fireworks.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Fish.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Flame.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\FogMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Gizmo.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Global.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\GradientMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\GravityMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\GravityRouter.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Grunt.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\GruntSka.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Guffy.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\HazeMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Headman.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\HealthItem.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\HudPicHolder.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Item.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\KeyItem.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\LarvaOffspring.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Light.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Lightning.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Marker.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\MessageHolder.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\MessageItem.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\MeteorShower.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\MirrorMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ModelDestruction.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ModelHolder.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ModelHolder2.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ModelHolder3.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\MovingBrush.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\MovingBrushMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\MusicChanger.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\MusicHolder.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\NavigationMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ParticlesHolder.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Pendulum.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PhotoAlbum.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Player.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PlayerActionMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PlayerAnimator.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PlayerMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PlayerView.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PlayerWeapons.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PlayerWeaponsEffects.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PowerUpItem.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Projectile.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PyramidSpaceShip.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PyramidSpaceShipMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Reminder.cpp
# End Source File
# Begin Source File

SOURCE=.\RodaRollaDa.cpp
# End Source File
# Begin Source File

SOURCE=.\RodaRollaDebris.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\RollingStone.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Santa.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Scorpman.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ScrollHolder.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\SeriousBomb.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Ship.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ShipMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Shooter.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\SoundHolder.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\SpawnerProjectile.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Spinner.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\StormController.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Summoner.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\SummonerMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Switch.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\TacticsChanger.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\TacticsHolder.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Teleport.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\TextFXHolder.cpp
# End Source File
# Begin Source File

SOURCE=.\TheWorld.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\TimeController.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\TouchField.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Trigger.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Twister.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\VoiceHolder.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Walker.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Watcher.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\WatchPlayers.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Water.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\WeaponItem.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Werebull.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Woman.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\WorldBase.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\WorldLink.cpp
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\WorldSettingsController.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Common headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\EntitiesMP\Common\Common.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Common\Flags.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Common\GameInterface.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Common\Particles.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Common\PathFinding.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\StdH\StdH.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Common\WeaponPositions.h
# End Source File
# End Group
# Begin Group "JoJo headers"

# PROP Default_Filter ""
# Begin Group "uthash"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\uthash\uthash.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\entitycast.h
# End Source File
# Begin Source File

SOURCE=.\event_factory.h
# End Source File
# Begin Source File

SOURCE=.\graphics_exports.h
# End Source File
# Begin Source File

SOURCE=.\jojo_events.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\EntitiesMP\AirElemental.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\AirElemental_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\AirShockwave.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\AirShockwave_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\AmmoItem.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\AmmoItem_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\AmmoPack.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\AmmoPack_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\AnimationChanger.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\AnimationChanger_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\AnimationHub.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\AnimationHub_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\AreaMarker.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\AreaMarker_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ArmorItem.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ArmorItem_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\BackgroundViewer.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\BackgroundViewer_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\BasicEffects.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\BasicEffects_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Beast.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Beast_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\BigHead.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\BigHead_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\BlendController.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\BlendController_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\BloodSpray.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\BloodSpray_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Boneman.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Boneman_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Bouncer.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Bouncer_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Bullet.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Bullet_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Camera.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Camera_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\CameraMarker.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\CameraMarker_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\CannonBall.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\CannonBall_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\CannonRotating.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\CannonRotating_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\CannonStatic.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\CannonStatic_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ChainsawFreak.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ChainsawFreak_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Copier.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Copier_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Counter.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Counter_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\CrateBus.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\CrateBus_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\CrateRider.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\CrateRider_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\CreditsHolder.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\CreditsHolder_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Damager.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Damager_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Debris.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Debris_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\DebugEntityStatesDisplay.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\DebugEntityStatesDisplay_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Demon.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Demon_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\DestroyableArchitecture.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\DestroyableArchitecture_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Devil.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Devil_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\DevilMarker.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\DevilMarker_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\DevilProjectile.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\DevilProjectile_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\DoorController.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\DoorController_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EffectMarker.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EffectMarker_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Effector.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Effector_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Elemental.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Elemental_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnemyBase.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnemyBase_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnemyCounter.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnemyCounter_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnemyDive.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnemyDive_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnemyFly.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnemyFly_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnemyMarker.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnemyMarker_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnemyRunInto.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnemyRunInto_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnemySpawner.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnemySpawner_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnvironmentBase.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnvironmentBase_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnvironmentMarker.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnvironmentMarker_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnvironmentParticlesHolder.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnvironmentParticlesHolder_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Eruptor.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Eruptor_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ExotechLarva.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ExotechLarva_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ExotechLarvaBattery.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ExotechLarvaBattery_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ExotechLarvaCharger.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ExotechLarvaCharger_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Eyeman.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Eyeman_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Fireworks.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Fireworks_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Fish.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Fish_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Flame.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Flame_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\FogMarker.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\FogMarker_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Gizmo.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Gizmo_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Global.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Global_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\GradientMarker.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\GradientMarker_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\GravityMarker.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\GravityMarker_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\GravityRouter.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\GravityRouter_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Grunt.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Grunt_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\GruntSka.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\GruntSka_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Guffy.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Guffy_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\HazeMarker.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\HazeMarker_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Headman.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Headman_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\HealthItem.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\HealthItem_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\HudPicHolder.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\HudPicHolder_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Item.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Item_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\KeyItem.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\KeyItem_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\LarvaOffspring.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\LarvaOffspring_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Light.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Light_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Lightning.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Lightning_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Marker.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Marker_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\MessageHolder.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\MessageHolder_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\MessageItem.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\MessageItem_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\MeteorShower.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\MeteorShower_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\MirrorMarker.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\MirrorMarker_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ModelDestruction.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ModelDestruction_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ModelHolder.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ModelHolder2.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ModelHolder2_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ModelHolder3.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ModelHolder3_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ModelHolder_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\MovingBrush.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\MovingBrush_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\MovingBrushMarker.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\MovingBrushMarker_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\MusicChanger.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\MusicChanger_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\MusicHolder.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\MusicHolder_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\NavigationMarker.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\NavigationMarker_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ParticlesHolder.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ParticlesHolder_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Pendulum.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Pendulum_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PhotoAlbum.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PhotoAlbum_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Player.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Player_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PlayerActionMarker.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PlayerActionMarker_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PlayerAnimator.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PlayerAnimator_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PlayerMarker.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PlayerMarker_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PlayerView.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PlayerView_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PlayerWeapons.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PlayerWeapons_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PlayerWeaponsEffects.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PlayerWeaponsEffects_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PowerUpItem.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PowerUpItem_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Projectile.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Projectile_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PyramidSpaceShip.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PyramidSpaceShip_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PyramidSpaceShipMarker.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PyramidSpaceShipMarker_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Reminder.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Reminder_tables.h
# End Source File
# Begin Source File

SOURCE=.\RodaRollaDa.h
# End Source File
# Begin Source File

SOURCE=.\RodaRollaDa_tables.h
# End Source File
# Begin Source File

SOURCE=.\RodaRollaDebris.h
# End Source File
# Begin Source File

SOURCE=.\RodaRollaDebris_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\RollingStone.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\RollingStone_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Santa.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Santa_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Scorpman.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Scorpman_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ScrollHolder.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ScrollHolder_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\SeriousBomb.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\SeriousBomb_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Ship.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Ship_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ShipMarker.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ShipMarker_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Shooter.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Shooter_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\SoundHolder.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\SoundHolder_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\SpawnerProjectile.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\SpawnerProjectile_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Spinner.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Spinner_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\StormController.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\StormController_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Summoner.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Summoner_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\SummonerMarker.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\SummonerMarker_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Switch.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Switch_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\TacticsChanger.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\TacticsChanger_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\TacticsHolder.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\TacticsHolder_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Teleport.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Teleport_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\TextFXHolder.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\TextFXHolder_tables.h
# End Source File
# Begin Source File

SOURCE=.\TheWorld.h
# End Source File
# Begin Source File

SOURCE=.\TheWorld_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\TimeController.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\TimeController_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\TouchField.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\TouchField_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Trigger.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Trigger_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Twister.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Twister_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\VoiceHolder.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\VoiceHolder_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Walker.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Walker_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Watcher.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Watcher_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\WatchPlayers.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\WatchPlayers_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Water.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Water_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\WeaponItem.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\WeaponItem_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Werebull.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Werebull_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Woman.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Woman_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\WorldBase.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\WorldBase_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\WorldLink.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\WorldLink_tables.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\WorldSettingsController.h
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\WorldSettingsController_tables.h
# End Source File
# End Group
# Begin Group "Class Files"

# PROP Default_Filter "es"
# Begin Group "Brushes"

# PROP Default_Filter "es"
# Begin Source File

SOURCE=..\EntitiesMP\Bouncer.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Bouncer.es
InputName=Bouncer

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Bouncer.es
InputName=Bouncer

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\DestroyableArchitecture.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\DestroyableArchitecture.es
InputName=DestroyableArchitecture

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\DestroyableArchitecture.es
InputName=DestroyableArchitecture

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\MovingBrush.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\MovingBrush.es
InputName=MovingBrush

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\MovingBrush.es
InputName=MovingBrush

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\MovingBrushMarker.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\MovingBrushMarker.es
InputName=MovingBrushMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\MovingBrushMarker.es
InputName=MovingBrushMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Pendulum.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Pendulum.es
InputName=Pendulum

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Pendulum.es
InputName=Pendulum

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Ship.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Ship.es
InputName=Ship

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Ship.es
InputName=Ship

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ShipMarker.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\ShipMarker.es
InputName=ShipMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\ShipMarker.es
InputName=ShipMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\WorldBase.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\WorldBase.es
InputName=WorldBase

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\WorldBase.es
InputName=WorldBase

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Weapons"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\EntitiesMP\AirShockwave.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\AirShockwave.es
InputName=AirShockwave

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\AirShockwave.es
InputName=AirShockwave

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\AirWave.es
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Bullet.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Bullet.es
InputName=Bullet

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Bullet.es
InputName=Bullet

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\CannonBall.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\CannonBall.es
InputName=CannonBall

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\CannonBall.es
InputName=CannonBall

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\DevilProjectile.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\DevilProjectile.es
InputName=DevilProjectile

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\DevilProjectile.es
InputName=DevilProjectile

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Flame.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Flame.es
InputName=Flame

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Flame.es
InputName=Flame

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\GhostBusterRay.es
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\LarvaOffspring.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\LarvaOffspring.es
InputName=LarvaOffspring

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\LarvaOffspring.es
InputName=LarvaOffspring

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Pipebomb.es
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Projectile.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Projectile.es
InputName=Projectile

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Projectile.es
InputName=Projectile

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RodaRollaDa.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesJoJo/$(InputName).es
InputPath=.\RodaRollaDa.es
InputName=RodaRollaDa

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesJoJo/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesJoJo/$(InputName).es
InputPath=.\RodaRollaDa.es
InputName=RodaRollaDa

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesJoJo/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RodaRollaDebris.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesJoJo/$(InputName).es
InputPath=.\RodaRollaDebris.es
InputName=RodaRollaDebris

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesJoJo/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesJoJo/$(InputName).es
InputPath=.\RodaRollaDebris.es
InputName=RodaRollaDebris

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesJoJo/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\SeriousBomb.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\SeriousBomb.es
InputName=SeriousBomb

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\SeriousBomb.es
InputName=SeriousBomb

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\SpawnerProjectile.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\SpawnerProjectile.es
InputName=SpawnerProjectile

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\SpawnerProjectile.es
InputName=SpawnerProjectile

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Twister.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Twister.es
InputName=Twister

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Twister.es
InputName=Twister

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Water.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Water.es
InputName=Water

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Water.es
InputName=Water

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Tools"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\EntitiesMP\AnimationChanger.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\AnimationChanger.es
InputName=AnimationChanger

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\AnimationChanger.es
InputName=AnimationChanger

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\AnimationHub.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\AnimationHub.es
InputName=AnimationHub

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\AnimationHub.es
InputName=AnimationHub

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\AreaMarker.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\AreaMarker.es
InputName=AreaMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\AreaMarker.es
InputName=AreaMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\BackgroundViewer.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\BackgroundViewer.es
InputName=BackgroundViewer

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\BackgroundViewer.es
InputName=BackgroundViewer

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Camera.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Camera.es
InputName=Camera

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Camera.es
InputName=Camera

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\CameraMarker.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\CameraMarker.es
InputName=CameraMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\CameraMarker.es
InputName=CameraMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Copier.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Copier.es
InputName=Copier

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Copier.es
InputName=Copier

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Counter.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Counter.es
InputName=Counter

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Counter.es
InputName=Counter

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\CreditsHolder.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\CreditsHolder.es
InputName=CreditsHolder

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\CreditsHolder.es
InputName=CreditsHolder

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Damager.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Damager.es
InputName=Damager

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Damager.es
InputName=Damager

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\DebugEntityStatesDisplay.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\DebugEntityStatesDisplay.es
InputName=DebugEntityStatesDisplay

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\DebugEntityStatesDisplay.es
InputName=DebugEntityStatesDisplay

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\DoorController.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\DoorController.es
InputName=DoorController

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\DoorController.es
InputName=DoorController

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Eruptor.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Eruptor.es
InputName=Eruptor

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Eruptor.es
InputName=Eruptor

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\FogMarker.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\FogMarker.es
InputName=FogMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\FogMarker.es
InputName=FogMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\GradientMarker.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\GradientMarker.es
InputName=GradientMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\GradientMarker.es
InputName=GradientMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\GravityMarker.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\GravityMarker.es
InputName=GravityMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\GravityMarker.es
InputName=GravityMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\GravityRouter.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\GravityRouter.es
InputName=GravityRouter

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\GravityRouter.es
InputName=GravityRouter

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\HazeMarker.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\HazeMarker.es
InputName=HazeMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\HazeMarker.es
InputName=HazeMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\HudPicHolder.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\HudPicHolder.es
InputName=HudPicHolder

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\HudPicHolder.es
InputName=HudPicHolder

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Light.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Light.es
InputName=Light

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Light.es
InputName=Light

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Marker.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Marker.es
InputName=Marker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Marker.es
InputName=Marker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\MessageHolder.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\MessageHolder.es
InputName=MessageHolder

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\MessageHolder.es
InputName=MessageHolder

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\MirrorMarker.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\MirrorMarker.es
InputName=MirrorMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\MirrorMarker.es
InputName=MirrorMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ModelDestruction.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\ModelDestruction.es
InputName=ModelDestruction

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\ModelDestruction.es
InputName=ModelDestruction

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ModelHolder.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\ModelHolder.es
InputName=ModelHolder

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\ModelHolder.es
InputName=ModelHolder

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ModelHolder2.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\ModelHolder2.es
InputName=ModelHolder2

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\ModelHolder2.es
InputName=ModelHolder2

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ModelHolder3.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\ModelHolder3.es
InputName=ModelHolder3

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\ModelHolder3.es
InputName=ModelHolder3

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\MusicChanger.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\MusicChanger.es
InputName=MusicChanger

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\MusicChanger.es
InputName=MusicChanger

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\MusicHolder.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\MusicHolder.es
InputName=MusicHolder

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\MusicHolder.es
InputName=MusicHolder

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ParticlesHolder.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\ParticlesHolder.es
InputName=ParticlesHolder

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\ParticlesHolder.es
InputName=ParticlesHolder

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ScrollHolder.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\ScrollHolder.es
InputName=ScrollHolder

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\ScrollHolder.es
InputName=ScrollHolder

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\SoundHolder.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\SoundHolder.es
InputName=SoundHolder

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\SoundHolder.es
InputName=SoundHolder

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Switch.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Switch.es
InputName=Switch

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Switch.es
InputName=Switch

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Teleport.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Teleport.es
InputName=Teleport

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Teleport.es
InputName=Teleport

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\TextFXHolder.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\TextFXHolder.es
InputName=TextFXHolder

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\TextFXHolder.es
InputName=TextFXHolder

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\TouchField.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\TouchField.es
InputName=TouchField

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\TouchField.es
InputName=TouchField

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Trigger.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Trigger.es
InputName=Trigger

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Trigger.es
InputName=Trigger

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\VoiceHolder.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\VoiceHolder.es
InputName=VoiceHolder

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\VoiceHolder.es
InputName=VoiceHolder

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\WorldLink.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\WorldLink.es
InputName=WorldLink

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\WorldLink.es
InputName=WorldLink

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Players"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\EntitiesMP\Player.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Player.es
InputName=Player

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Player.es
InputName=Player

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PlayerActionMarker.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\PlayerActionMarker.es
InputName=PlayerActionMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\PlayerActionMarker.es
InputName=PlayerActionMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PlayerAnimator.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\PlayerAnimator.es
InputName=PlayerAnimator

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\PlayerAnimator.es
InputName=PlayerAnimator

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PlayerMarker.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\PlayerMarker.es
InputName=PlayerMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\PlayerMarker.es
InputName=PlayerMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PlayerView.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\PlayerView.es
InputName=PlayerView

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\PlayerView.es
InputName=PlayerView

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PlayerWeapons.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\PlayerWeapons.es
InputName=PlayerWeapons

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\PlayerWeapons.es
InputName=PlayerWeapons

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PlayerWeaponsEffects.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\PlayerWeaponsEffects.es
InputName=PlayerWeaponsEffects

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\PlayerWeaponsEffects.es
InputName=PlayerWeaponsEffects

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TheWorld.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesJoJo/$(InputName).es
InputPath=.\TheWorld.es
InputName=TheWorld

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesJoJo/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesJoJo/$(InputName).es
InputPath=.\TheWorld.es
InputName=TheWorld

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesJoJo/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Items"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\EntitiesMP\AmmoItem.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\AmmoItem.es
InputName=AmmoItem

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\AmmoItem.es
InputName=AmmoItem

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\AmmoPack.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\AmmoPack.es
InputName=AmmoPack

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\AmmoPack.es
InputName=AmmoPack

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ArmorItem.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\ArmorItem.es
InputName=ArmorItem

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\ArmorItem.es
InputName=ArmorItem

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\HealthItem.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\HealthItem.es
InputName=HealthItem

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\HealthItem.es
InputName=HealthItem

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Item.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Item.es
InputName=Item

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Item.es
InputName=Item

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\KeyItem.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\KeyItem.es
InputName=KeyItem

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\KeyItem.es
InputName=KeyItem

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\MessageItem.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\MessageItem.es
InputName=MessageItem

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\MessageItem.es
InputName=MessageItem

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PowerUpItem.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\PowerUpItem.es
InputName=PowerUpItem

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\PowerUpItem.es
InputName=PowerUpItem

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\WeaponItem.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\WeaponItem.es
InputName=WeaponItem

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\WeaponItem.es
InputName=WeaponItem

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Environment"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\EntitiesMP\EnvironmentBase.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\EnvironmentBase.es
InputName=EnvironmentBase

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\EnvironmentBase.es
InputName=EnvironmentBase

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnvironmentMarker.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\EnvironmentMarker.es
InputName=EnvironmentMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\EnvironmentMarker.es
InputName=EnvironmentMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnvironmentParticlesHolder.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\EnvironmentParticlesHolder.es
InputName=EnvironmentParticlesHolder

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\EnvironmentParticlesHolder.es
InputName=EnvironmentParticlesHolder

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Enemies"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\EntitiesMP\AirElemental.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\AirElemental.es
InputName=AirElemental

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\AirElemental.es
InputName=AirElemental

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Beast.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Beast.es
InputName=Beast

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Beast.es
InputName=Beast

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\BigHead.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\BigHead.es
InputName=BigHead

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\BigHead.es
InputName=BigHead

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Boneman.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Boneman.es
InputName=Boneman

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Boneman.es
InputName=Boneman

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\CannonRotating.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\CannonRotating.es
InputName=CannonRotating

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\CannonRotating.es
InputName=CannonRotating

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\CannonStatic.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\CannonStatic.es
InputName=CannonStatic

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\CannonStatic.es
InputName=CannonStatic

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Catman.es
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ChainsawFreak.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\ChainsawFreak.es
InputName=ChainsawFreak

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\ChainsawFreak.es
InputName=ChainsawFreak

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\CrateBus.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\CrateBus.es
InputName=CrateBus

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\CrateBus.es
InputName=CrateBus

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\CrateRider.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\CrateRider.es
InputName=CrateRider

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\CrateRider.es
InputName=CrateRider

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Cyborg.es
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\CyborgBike.es
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Demon.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Demon.es
InputName=Demon

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Demon.es
InputName=Demon

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Devil.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Devil.es
InputName=Devil

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Devil.es
InputName=Devil

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\DevilMarker.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\DevilMarker.es
InputName=DevilMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\DevilMarker.es
InputName=DevilMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Dragonman.es
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Elemental.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Elemental.es
InputName=Elemental

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Elemental.es
InputName=Elemental

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnemyBase.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\EnemyBase.es
InputName=EnemyBase

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\EnemyBase.es
InputName=EnemyBase

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnemyCounter.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\EnemyCounter.es
InputName=EnemyCounter

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\EnemyCounter.es
InputName=EnemyCounter

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnemyDive.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\EnemyDive.es
InputName=EnemyDive

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\EnemyDive.es
InputName=EnemyDive

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnemyFly.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\EnemyFly.es
InputName=EnemyFly

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\EnemyFly.es
InputName=EnemyFly

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnemyMarker.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\EnemyMarker.es
InputName=EnemyMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\EnemyMarker.es
InputName=EnemyMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnemyRunInto.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\EnemyRunInto.es
InputName=EnemyRunInto

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\EnemyRunInto.es
InputName=EnemyRunInto

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EnemySpawner.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\EnemySpawner.es
InputName=EnemySpawner

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\EnemySpawner.es
InputName=EnemySpawner

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ExotechLarva.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\ExotechLarva.es
InputName=ExotechLarva

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\ExotechLarva.es
InputName=ExotechLarva

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ExotechLarvaBattery.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\ExotechLarvaBattery.es
InputName=ExotechLarvaBattery

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\ExotechLarvaBattery.es
InputName=ExotechLarvaBattery

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\ExotechLarvaCharger.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\ExotechLarvaCharger.es
InputName=ExotechLarvaCharger

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\ExotechLarvaCharger.es
InputName=ExotechLarvaCharger

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Eyeman.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Eyeman.es
InputName=Eyeman

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Eyeman.es
InputName=Eyeman

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Fish.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Fish.es
InputName=Fish

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Fish.es
InputName=Fish

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Fishman.es
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Gizmo.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Gizmo.es
InputName=Gizmo

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Gizmo.es
InputName=Gizmo

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Grunt.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Grunt.es
InputName=Grunt

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Grunt.es
InputName=Grunt

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\GruntSka.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\GruntSka.es
InputName=GruntSka

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\GruntSka.es
InputName=GruntSka

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Guffy.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Guffy.es
InputName=Guffy

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Guffy.es
InputName=Guffy

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Headman.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Headman.es
InputName=Headman

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Headman.es
InputName=Headman

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Huanman.es
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Mamut.es
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Mamutman.es
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Mantaman.es
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\RobotDriving.es
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\RobotFixed.es
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\RobotFlying.es
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Santa.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Santa.es
InputName=Santa

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Santa.es
InputName=Santa

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Scorpman.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Scorpman.es
InputName=Scorpman

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Scorpman.es
InputName=Scorpman

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Shooter.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Shooter.es
InputName=Shooter

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Shooter.es
InputName=Shooter

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Summoner.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Summoner.es
InputName=Summoner

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Summoner.es
InputName=Summoner

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\SummonerMarker.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\SummonerMarker.es
InputName=SummonerMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\SummonerMarker.es
InputName=SummonerMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Walker.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Walker.es
InputName=Walker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Walker.es
InputName=Walker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Werebull.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Werebull.es
InputName=Werebull

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Werebull.es
InputName=Werebull

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Woman.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Woman.es
InputName=Woman

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Woman.es
InputName=Woman

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Effects"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\EntitiesMP\BasicEffects.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\BasicEffects.es
InputName=BasicEffects

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\BasicEffects.es
InputName=BasicEffects

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\BlendController.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\BlendController.es
InputName=BlendController

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\BlendController.es
InputName=BlendController

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\BloodSpray.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\BloodSpray.es
InputName=BloodSpray

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\BloodSpray.es
InputName=BloodSpray

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Debris.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Debris.es
InputName=Debris

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Debris.es
InputName=Debris

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\EffectMarker.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\EffectMarker.es
InputName=EffectMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\EffectMarker.es
InputName=EffectMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Effector.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Effector.es
InputName=Effector

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Effector.es
InputName=Effector

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Fireworks.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Fireworks.es
InputName=Fireworks

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Fireworks.es
InputName=Fireworks

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Lightning.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Lightning.es
InputName=Lightning

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Lightning.es
InputName=Lightning

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\MeteorShower.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\MeteorShower.es
InputName=MeteorShower

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\MeteorShower.es
InputName=MeteorShower

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PhotoAlbum.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\PhotoAlbum.es
InputName=PhotoAlbum

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\PhotoAlbum.es
InputName=PhotoAlbum

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PyramidSpaceShip.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\PyramidSpaceShip.es
InputName=PyramidSpaceShip

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\PyramidSpaceShip.es
InputName=PyramidSpaceShip

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\PyramidSpaceShipMarker.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\PyramidSpaceShipMarker.es
InputName=PyramidSpaceShipMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\PyramidSpaceShipMarker.es
InputName=PyramidSpaceShipMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\RollingStone.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\RollingStone.es
InputName=RollingStone

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\RollingStone.es
InputName=RollingStone

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\StormController.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\StormController.es
InputName=StormController

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\StormController.es
InputName=StormController

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\TimeController.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\TimeController.es
InputName=TimeController

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\TimeController.es
InputName=TimeController

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\WorldSettingsController.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\WorldSettingsController.es
InputName=WorldSettingsController

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\WorldSettingsController.es
InputName=WorldSettingsController

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "AI"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\EntitiesMP\NavigationMarker.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\NavigationMarker.es
InputName=NavigationMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\NavigationMarker.es
InputName=NavigationMarker

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Reminder.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Reminder.es
InputName=Reminder

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Reminder.es
InputName=Reminder

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Spinner.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Spinner.es
InputName=Spinner

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Spinner.es
InputName=Spinner

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\TacticsChanger.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\TacticsChanger.es
InputName=TacticsChanger

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\TacticsChanger.es
InputName=TacticsChanger

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\TacticsHolder.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\TacticsHolder.es
InputName=TacticsHolder

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\TacticsHolder.es
InputName=TacticsHolder

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\Watcher.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Watcher.es
InputName=Watcher

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Watcher.es
InputName=Watcher

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\WatchPlayers.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\WatchPlayers.es
InputName=WatchPlayers

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\WatchPlayers.es
InputName=WatchPlayers

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=..\EntitiesMP\Global.es

!IF  "$(CFG)" == "EntitiesJoJo - Win32 Release"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Global.es
InputName=Global

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EntitiesJoJo - Win32 Debug"

# Begin Custom Build - EntitiesMP/$(InputName).es
InputPath=..\EntitiesMP\Global.es
InputName=Global

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd             ..\  
	ecc EntitiesMP/$(InputName).es 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\EntitiesMP\LastFileID.txt
# End Source File
# End Group
# End Target
# End Project
