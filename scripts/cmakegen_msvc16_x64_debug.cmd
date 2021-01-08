@echo off

cmd /c call build.cmd mvs16 x64 Debug static mt
if errorlevel 1 goto :error

goto :eof

:error
exit /b 1
