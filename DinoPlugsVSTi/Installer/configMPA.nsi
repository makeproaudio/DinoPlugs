;NSIS Modern User Interface
;Header Bitmap Example Script
;Written by Joost Verburg

;--------------------------------
;Include Modern UI

!include "MUI2.nsh"
  
!include "UAC.nsh"

RequestExecutionLevel user ; << Required, you cannot use admin!

!macro Init thing
uac_tryagain:
!insertmacro UAC_RunElevated
${Switch} $0
${Case} 0
	${IfThen} $1 = 1 ${|} Quit ${|} ;we are the outer process, the inner process has done its work, we are done
	${IfThen} $3 <> 0 ${|} ${Break} ${|} ;we are admin, let the show go on
	${If} $1 = 3 ;RunAs completed successfully, but with a non-admin user
		MessageBox mb_YesNo|mb_IconExclamation|mb_TopMost|mb_SetForeground "This ${thing} requires admin privileges, try again" /SD IDNO IDYES uac_tryagain IDNO 0
	${EndIf}
	;fall-through and die
${Case} 1223
	MessageBox mb_IconStop|mb_TopMost|mb_SetForeground "This ${thing} requires admin privileges, aborting!"
	Quit
${Case} 1062
	MessageBox mb_IconStop|mb_TopMost|mb_SetForeground "Logon service not running, aborting!"
	Quit
${Default}
	MessageBox mb_IconStop|mb_TopMost|mb_SetForeground "Unable to elevate, error $0"
	Quit
${EndSwitch}
 
SetShellVarContext all
!macroend

Function .onInit
;!insertmacro Init "installer"
Call "GetMyDocs"
  ;MessageBox MB_OK|MB_ICONINFORMATION $0
  ;Quit
FunctionEnd
 
Function "GetMyDocs"
  ReadRegStr $0 HKCU \
             "SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\Shell Folders" \
             Personal
FunctionEnd
 
;--------------------------------
;General

  ;Name and file
  Name "Make Pro Audio VSTs"
  OutFile "Make Pro Audio VSTs Installer 64 Bit.exe"

  ;Default installation folder
  InstallDir "C:\Program Files\Steinberg\Vstplugins\"
 
  RequestExecutionLevel user

;--------------------------------
;Interface Configuration

  !define MUI_HEADERIMAGE
  !define MUI_HEADERIMAGE_BITMAP "logo.bmp" ; optional
  !define MUI_ABORTWARNING

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_DIRECTORY 
  !insertmacro MUI_PAGE_INSTFILES
  
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES

  
;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Sections

Section "Make Pro Audio VSTs" Sec1

  SetOutPath $INSTDIR
	
	File "C:\Program Files\Steinberg\VSTPlugins\FMagia.dll"
	File "C:\Program Files\Steinberg\VSTPlugins\DrumsNBass.dll"
	File "C:\Program Files\Steinberg\VSTPlugins\Lightwave.dll"
	File "C:\Program Files\Steinberg\VSTPlugins\Minimax.dll"
	File "C:\Program Files\Steinberg\VSTPlugins\B4000.dll"
	File "C:\Program Files\Steinberg\VSTPlugins\Pro12.dll"
	File "C:\Program Files\Steinberg\VSTPlugins\Prodyssey.dll"

SectionEnd