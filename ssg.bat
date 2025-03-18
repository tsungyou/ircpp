@echo off
REM 設定編譯器與參數
set CXX=g++
set CXXFLAGS=-std=c++17 -Wall -Wno-unused-variable -Wno-unused-parameter
set COMMON_SRC=src\DatabaseHandler.cpp src\StockSignalGenerator.cpp

REM 確保使用者提供 main.cpp 檔案
if "%~1"=="" (
    echo [error] Please input the correct .cpp file;
    echo usage: ssg.bat src\example.cpp
    exit /b 1
)

set MAIN_FILE=%~1

REM 檢查檔案是否存在
if not exist "%MAIN_FILE%" (    echo [error] File %MAIN_FILE% not found!
    exit /b 1
)

REM 確保 bin 目錄存在
if not exist bin mkdir bin

REM 取得輸出檔案名稱
for %%F in (%MAIN_FILE%) do set OUT_FILE=bin\%%~nF.exe

REM 編譯
%CXX% %CXXFLAGS% %MAIN_FILE% %COMMON_SRC% -o %OUT_FILE% -lpqxx -lpq

REM 檢查是否成功編譯
if %ERRORLEVEL% equ 0 (
    echo [successful] Compilation finished. Running %OUT_FILE%...
    %OUT_FILE%
) else (
    echo [error] Compilation failed!
)
