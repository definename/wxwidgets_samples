@echo off

cmd /c call build.cmd mvs16 x86 Release static mt
if errorlevel 1 goto :error

goto :eof

:error
exit /b 1
