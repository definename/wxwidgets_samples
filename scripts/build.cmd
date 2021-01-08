@echo off

set AND=if
set THEN=(
set ENDIF=)

set GENERATOR="%1"
set ARCHITECTURE="%2"
set BUILDTYPE="%3"
set LIBTYPE="%4"
set CRTTYPE="%5"

set GENERATOR_INTERNAL=""
if %GENERATOR% == "mvs16" set GENERATOR_INTERNAL="Visual Studio 16 2019"
if %GENERATOR_INTERNAL% == "" goto :error_param_generator

if NOT %ARCHITECTURE% == "Win32" %AND% NOT %ARCHITECTURE% == "x64" %THEN%
	goto :error_param_architecture
%ENDIF%
if NOT %BUILDTYPE% == "Debug" %AND% NOT %BUILDTYPE% == "Release" %THEN%
	goto :error_param_buildtype
%ENDIF%
if NOT %LIBTYPE% == "shared" %AND% NOT %LIBTYPE% == "static" %THEN%
	goto :error_param_libtype
%ENDIF%
if NOT %CRTTYPE% == "md" %AND% NOT %CRTTYPE% == "mt" %THEN%
	goto :error_param_crttype
%ENDIF%
if %LIBTYPE% == "shared" %AND% %CRTTYPE% == "mt" %THEN%
	goto :error_crttype_conflict
%ENDIF%

set CMAKE_PARAMS_INTERNAL=-DCMAKE_CONFIGURATION_TYPES=%BUILDTYPE%
if %LIBTYPE% == "shared" set CMAKE_PARAMS_INTERNAL=%CMAKE_PARAMS_INTERNAL% -DBUILD_SHARED_LIBS=ON
if %LIBTYPE% == "static" set CMAKE_PARAMS_INTERNAL=%CMAKE_PARAMS_INTERNAL% -DBUILD_SHARED_LIBS=OFF

if %CRTTYPE% == "mt" set CMAKE_PARAMS_INTERNAL=%CMAKE_PARAMS_INTERNAL% -DBUILD_WITH_STATIC_CRT=ON
if %CRTTYPE% == "md" set CMAKE_PARAMS_INTERNAL=%CMAKE_PARAMS_INTERNAL% -DBUILD_WITH_STATIC_CRT=OFF

set BUILD_DIR=..\build\%GENERATOR%_%ARCHITECTURE%_%BUILDTYPE%
echo -- CMake build directory: %BUILD_DIR%
mkdir %BUILD_DIR%
pushd %BUILD_DIR%

set CMAKE_COMMAND=-G %GENERATOR_INTERNAL% %CMAKE_PARAMS_INTERNAL% -A %ARCHITECTURE% -S ../..
echo -- CMake command: %CMAKE_COMMAND%
cmake %CMAKE_COMMAND%
if errorlevel 1 %THEN%
	goto :error_build
%ENDIF%

echo -- Build succeeded!
popd
goto :eof

:error_param_generator
echo ERROR: Incorrect generator was given (mvc16)
exit /B 1

:error_param_architecture
echo ERROR: Build architecture should be set (Win32, x64)
exit /B 2

:error_param_buildtype
echo ERROR: Build type must be specified (Debug, Release)
exit /B 3

:error_param_libtype
echo ERROR: Library type must be specified (shared, static)
exit /B 4

:error_param_crttype
echo ERROR: CRT type must be specified (md, mt)
exit /B 5

:error_crttype_conflict
echo ERROR: CRT type conflict(shared and mt)
exit /B 6

:error_build
echo ERROR: Failed to build project, see above and correct
popd
exit /B 7