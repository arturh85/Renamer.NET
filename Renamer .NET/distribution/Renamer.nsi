#==============================
# Includes
!include "FileFunc.nsh"
!include "WinMessages.nsh"
!include UpgradeDLL.nsh
!include "MUI.nsh"
!include WordFunc.nsh
!insertmacro VersionCompare
!include LogicLib.nsh
!include "registerExtension.nsh"

###############################################################################
# Grafiken
#!define MUI_HEADERIMAGE
#!define MUI_HEADERIMAGE_BITMAP ".\Media\header.bmp"
#!define MUI_HEADERIMAGE_RIGHT
#!define MUI_WELCOMEFINISHPAGE_BITMAP "${NSISDIR}\Contrib\Graphics\Wizard\arrow.bmp"
#!define MUI_WELCOMEFINISHPAGE_BITMAP ".\Media\ATLIS-Logo-164x314-VarC.bmp"

###############################################################################
#  GLOBALE Variablen
#VAR /GLOBAL WINSPED_ROOT

#!define DEBUG

#=============================================================================
# Optionen
name "Renamer .NET"
OutFile "Install_Renamer.exe"
InstallDir "$PROGRAMFILES\Renamer .NET"

!ifdef DEBUG
    SetCompressor zlib
    SetCompress off
    ShowInstDetails show
!else
    SetCompressor /SOLID lzma
!endif

#=============================================================================
# Pages
!define MUI_COMPONENTSPAGE_NODESC
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES

!ifndef DEBUG
     !insertmacro MUI_PAGE_FINISH
!endif


#=============================================================================
# UnInstallPages
!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_COMPONENTS

!ifdef DEBUG
    ShowUninstDetails show
!endif
!insertmacro MUI_UNPAGE_INSTFILES

!ifndef DEBUG
    !insertmacro MUI_UNPAGE_FINISH
!endif

#=============================================================================
# Sprache
#!insertmacro MUI_LANGUAGE "German"
!insertmacro MUI_LANGUAGE "English"


#=============================================================================
Function GetDotNETVersion
  Push $0
  Push $1

  System::Call "mscoree::GetCORVersion(w .r0, i ${NSIS_MAX_STRLEN}, *i) i .r1 ?u"
  StrCmp $1 0 +2
    StrCpy $0 "not found"

  Pop $1
  Exch $0
FunctionEnd

Function .onInit
#  #==============================
#  # Xml2Check - Anfang
#  ReadRegStr $0 HKCR Msxml2.DOMDocument ""
#  StrCmp $0 "" 0 +3
#    MessageBox MB_OK|MB_ICONSTOP "MSXML2 ist nicht installiert.$\n$\nDownload: http://tinyurl.com/jdz42"
#    abort
#  # Xml2Check - Ende
#  #==============================

  #==============================
  # AdminCheck - Anfang
  ClearErrors
  UserInfo::GetName
  IfErrors Win9x
  Pop $0
  UserInfo::GetAccountType
  Pop $1
  StrCmp $1 "Admin" 0 +2
    Goto done

  MessageBox MB_OK|MB_ICONSTOP "Der Benutzer '$0' ist hat keine administrativen Rechte. Das Setup wird beendet."
  abort

  Win9x:
    # This one means you don't need to care about admin or
    # not admin because Windows 9x doesn't either
    MessageBox MB_OK|MB_ICONSTOP "Diese Programm ist nicht unter Windows 9x lauffähig. Das Setup wird beendet."
    abort

  done:
  #    AdminCheck - Ende
  #==============================

  #==============================
  # .NET Check - Anfang
  Call GetDotNETVersion
  Pop $0
  ${If} $0 == "not found"
    MessageBox MB_OK|MB_ICONSTOP ".NET runtime library is not installed. Download: http://tinyurl.com/drj86"
    Abort
  ${EndIf}

  StrCpy $0 $0 "" 1 # skip "v"

  ${VersionCompare} $0 "2.0" $1
  ${If} $1 == 2
    MessageBox MB_OK|MB_ICONSTOP ".NET runtime library v2.0 or newer is required. You have $0. Download: http://tinyurl.com/drj86"
    Abort
  ${EndIf}
  # .NET Check - Ende
  #==============================
  
#  #==============================
#  # alte Installation deinstallieren - Anfang
#  ReadRegStr $0 HKLM Software\sis\Atlis Installed
#  ${If} $0 != ""
#    MessageBox MB_OKCANCEL|MB_ICONQUESTION "Vor der Installation einer neuen Version muss die alte deinstalliert werden. Soll dies jetzt geschehen?" /SD IDOK IDOK doDeInstall
#    Abort
#    doDeInstall:
#	IfSilent doExecDeInstall_Silent doExecDeInstall_Normal
#	doExecDeInstall_Silent:
#      ExecWait "$WINSPED_ROOT\bin\AtlisUnInstall.exe /S _?=$INSTDIR" $0
#	  Goto checkDeInstall
#	  
#	doExecDeInstall_Normal:
#      ExecWait "$WINSPED_ROOT\bin\AtlisUnInstall.exe _?=$INSTDIR" $0
#	
#	checkDeInstall:
#    ${If} $0 != "0"
#          MessageBox MB_OK|MB_ICONSTOP "Deinstallation nicht erfolgreich."
#          Abort
#    ${EndIf}
#  ${EndIf}

#  # alte Installation deinstallieren - Ende
#  #==============================


  SetShellVarContext All
FunctionEnd

Function .onInstSuccess
  WriteUninstaller $INSTDIR\uninstall.exe
  WriteRegStr HKLM Software\Renamer InstallDir $INSTDIR

  # http://nsis.sourceforge.net/Add_uninstall_information_to_Add/Remove_Programs
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Renamer" \
                   "DisplayName" "Renamer .NET"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Renamer" \
                   "UninstallString" "$INSTDIR\uninstall.exe"  
FunctionEnd

Section "-RenamerBinary"
  SetOutPath $INSTDIR
  File "..\..\bin\Renamer .NET.exe"
  File "..\..\Documentation\licence.txt"
  File "..\..\bin\*.dll"
  File "depends\msvcp90.dll"
  File "depends\msvcr90.dll"
  File "depends\msvcm90.dll"
SectionEnd

Section "File Association"
  ${registerExtension} "$INSTDIR\Renamer .NET.exe" ".ruleset" "Renamer .NET Ruleset File"
SectionEnd

SectionGroup /e Shortcuts
  Section Startmenu
    CreateShortCut "$SMPROGRAMS\Renamer .NET.lnk" "$INSTDIR\Renamer .NET.exe"
  SectionEnd  

  Section /o Quicklaunch
    CreateShortCut "$QUICKLAUNCH\Renamer .NET.lnk" "$INSTDIR\Renamer .NET.exe"   
  SectionEnd  

  Section /o Desktop
    CreateShortCut "$DESKTOP\Renamer .NET.lnk" "$INSTDIR\Renamer .NET.exe"   
  SectionEnd  
SectionGroupEnd


Section /o "Un.User Settings"
  # HKCU\Software\Renamer
  DeleteRegKey HKCU "Software\VB and VBA Program Settings\Renamer"
SectionEnd

Section "-Un.Remove_What_is_Left"
	#Binaries
	Delete "$INSTDIR\Renamer .NET.exe"
	Delete "$INSTDIR\*.txt"
	Delete "$INSTDIR\uninstall.exe"
	Delete "$INSTDIR\*.dll"
	RMDir $INSTDIR
  
	#Shortcuts
    SetShellVarContext All
	Delete "$SMPROGRAMS\Renamer .NET.lnk"
	Delete "$QUICKLAUNCH\Renamer .NET.lnk"
	Delete "$DESKTOP\Renamer .NET.lnk"
  
  #Registry
  DeleteRegValue HKLM Software\Renamer InstallDir
  DeleteRegKey /ifempty HKLM Software\Renamer
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Renamer"
  ${unregisterExtension} ".ruleset" "Renamer .NET Ruleset File"
SectionEnd
