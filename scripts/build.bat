@echo off
:: This is a generic wrapper to the windows build script
set "SCRIPT_DIR=%~dp0"
call "%SCRIPT_DIR%build_windows_x64.bat"
