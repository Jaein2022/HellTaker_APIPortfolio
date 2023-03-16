@echo off

if exist "%SystemRoot%\Fonts\CrimsonPro-Medium.ttf" (
exit /b
)

if not "%1"=="am_admin" (powershell start -verb runas '%0' am_admin & exit /b)

xcopy "%~dp0\Font\*.ttf"  %SystemRoot%\Fonts\% /y
reg add "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Fonts" /v "Amiri-Regular (TrueType)" /t REG_SZ /d Amiri-Regular.ttf /f
reg add "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Fonts" /v "CrimsonPro-VariableFont_wght (TrueType)" /t REG_SZ /d CrimsonPro-VariableFont_wght.ttf /f
reg add "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Fonts" /v "CrimsonPro-Italic-VariableFont_wght (TrueType)" /t REG_SZ /d CrimsonPro-Italic-VariableFont_wght.ttf /f
