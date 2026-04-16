@echo off
setlocal
set "ROOT_DIR=%~dp0.."
set "BUILD_DIR=%ROOT_DIR%\build\windows_x64"

:: Check for clean argument
if /I "%~1"=="clean" (
    echo [Build] Cleaning %BUILD_DIR%...
    if exist "%BUILD_DIR%" rd /s /q "%BUILD_DIR%"
)

echo [Build] Configuring and building in %BUILD_DIR%...

:: Run CMake to configure and build
cmake -S "%ROOT_DIR%" -B "%BUILD_DIR%" -G Ninja ^
    -DCMAKE_BUILD_TYPE=Debug ^
    -DCMAKE_C_COMPILER=clang ^
    -DCMAKE_CXX_COMPILER=clang++

if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] CMake configuration failed.
    exit /b %ERRORLEVEL%
)

cmake --build "%BUILD_DIR%"

if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] Build failed.
    exit /b %ERRORLEVEL%
)

:: Copy the DLL to the test folder for execution
copy /y "%BUILD_DIR%\src\iprovider.dll" "%BUILD_DIR%\tests\iprovider.dll"

:: Run the test
echo.
echo [Test] Running itemplatelib.exe...
"%BUILD_DIR%\tests\itemplatelib.exe"

endlocal
