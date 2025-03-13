@echo off
REM set the compiler
set CXX=g++
set CXXFLAGS=-std=c++11 -Wall -Wno-unused-variable -Wno-unused-parameter
set SRC_FILES=main.cpp StockSignalGenerator.cpp
set OUT_FILE=my_program.exe

REM compile and connect(o)
echo start compiling and connecting...
%CXX% %CXXFLAGS% %SRC_FILES% -o %OUT_FILE%

REM check if works
if %ERRORLEVEL% equ 0 (
    echo compilation successful, start running...
    %OUT_FILE%
) else (
    echo compilation failed!
)
