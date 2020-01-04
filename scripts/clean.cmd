@echo off

set BUILD_DIR=..\build
echo -- Remove build directory %BUILD_DIR%

rmdir /S /Q %BUILD_DIR%

exit /B