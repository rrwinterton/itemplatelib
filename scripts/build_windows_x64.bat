@echo off
set BUILD_DIR=..\build\windows_x64

cmake -S .. -B %BUILD_DIR% -G Ninja ^
    -DCMAKE_BUILD_TYPE=Debug ^
    -DCMAKE_C_COMPILER=clang ^
    -DCMAKE_CXX_COMPILER=clang++

cmake --build %BUILD_DIR%

:: Run the test
%BUILD_DIR%\tests\itemplatelib_test.exe
