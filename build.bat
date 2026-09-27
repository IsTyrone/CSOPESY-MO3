@echo off
REM Builds csopesy.exe with static linking so it runs on any machine
REM without needing MinGW runtime DLLs (libstdc++-6-x64.dll, etc.).

setlocal
cd /d "%~dp0"

set "GXX="
where g++ >nul 2>nul && set "GXX=g++"
if not defined GXX if exist "D:\School\C_CMD\bin\g++.exe" set "GXX=D:\School\C_CMD\bin\g++.exe"
if not defined GXX goto nocompiler

"%GXX%" -std=c++17 -static -static-libgcc -static-libstdc++ -o csopesy.exe main.cpp ConsoleUI.cpp Marquee.cpp CommandInterpreter.cpp Config.cpp
if errorlevel 1 goto fail

echo.
echo Build OK: csopesy.exe
echo To run:   csopesy.exe
endlocal
exit /b 0

:nocompiler
echo g++ not found. Install MinGW (see prerequisite.md) or add it to PATH.
endlocal
exit /b 1

:fail
echo Build failed.
endlocal
exit /b 1