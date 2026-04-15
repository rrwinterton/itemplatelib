@echo off
set BUILD_DIR=..\build\windows_x64

cmake -S .. -B %BUILD_DIR% -G Ninja ^
    -DCMAKE_BUILD_TYPE=Debug ^
    -DCMAKE_C_COMPILER=clang ^
    -DCMAKE_CXX_COMPILER=clang++

cmake --build %BUILD_DIR%

:: Copy the DLL to the test folder for execution
copy %BUILD_DIR%\src\iprovider.dll %BUILD_DIR%\tests\iprovider.dll

:: Run the test
%BUILD_DIR%\tests\itemplatelib_test.exe
