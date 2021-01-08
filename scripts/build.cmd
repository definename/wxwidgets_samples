@echo off

set AND=if
set THEN=(
set ENDIF=)

set GENERATOR="%1"
if %GENERATOR% == "" goto :error_param_generator
set ARCHITECTURE="%2"
if %ARCHITECTURE% == "" goto :error_param_architecture
set BUILDTYPE="%3"
if %BUILDTYPE% == "" goto :error_param_buildtype
set LIBTYPE="%4"
if %LIBTYPE% == "" goto :error_param_libtype
set CRTTYPE="%5"
if %CRTTYPE% == "" goto :error_param_crttype

set GENERATOR_INTERNAL=""
if %GENERATOR% == "mvs16" set GENERATOR_INTERNAL="Visual Studio 16 2019"
if %GENERATOR_INTERNAL% == "" goto :error_param_generator

set ARCHITECTURE_INTERNAL=""
if %ARCHITECTURE% == "x86" set ARCHITECTURE_INTERNAL="Win32"
if %ARCHITECTURE% == "x64" set ARCHITECTURE_INTERNAL="x64"
if %ARCHITECTURE_INTERNAL% == "" goto :error_param_architecture

set BUILDTYPE_INTERNAL=""
if %BUILDTYPE% == "Debug" set BUILDTYPE_INTERNAL="Debug"
if %BUILDTYPE% == "Release" set BUILDTYPE_INTERNAL="Release"
if %BUILDTYPE_INTERNAL% == "" goto :error_param_buildtype

set LIBTYPE_INTERNAL=%LIBTYPE%
if NOT %LIBTYPE_INTERNAL% == "shared" %AND% NOT %LIBTYPE% == "static" %THEN%
	goto :error_param_libtype
%ENDIF%

set CRTTYPE_INTERNAL=%CRTTYPE%
if NOT %CRTTYPE% == "md" %AND% NOT %CRTTYPE% == "mt" %THEN%
	goto :error_param_crttype
%ENDIF%

if %LIBTYPE_INTERNAL% == "shared" %AND% %CRTTYPE_INTERNAL% == "mt" %THEN%
	goto :error_crttype_conflict
%ENDIF%

set CMAKE_PARAMS_INTERNAL=""
if %LIBTYPE_INTERNAL% == "shared" set CMAKE_PARAMS_INTERNAL=-DBUILD_SHARED_LIBS=ON
if %LIBTYPE_INTERNAL% == "static" set CMAKE_PARAMS_INTERNAL=-DBUILD_SHARED_LIBS=OFF

if %CRTTYPE_INTERNAL% == "mt" set CMAKE_PARAMS_INTERNAL=%CMAKE_PARAMS_INTERNAL% -DBUILD_WITH_STATIC_CRT=ON
if %CRTTYPE_INTERNAL% == "md" set CMAKE_PARAMS_INTERNAL=%CMAKE_PARAMS_INTERNAL% -DBUILD_WITH_STATIC_CRT=OFF

if %BUILDTYPE_INTERNAL% == "debug" set CMAKE_PARAMS_INTERNAL=%CMAKE_PARAMS_INTERNAL% -DCMAKE_CONFIGURATION_TYPES=Debug
if %BUILDTYPE_INTERNAL% == "release" set CMAKE_PARAMS_INTERNAL=%CMAKE_PARAMS_INTERNAL% -DCMAKE_CONFIGURATION_TYPES=Release

set BUILD_DIR=..\build\%GENERATOR%_%ARCHITECTURE_INTERNAL%_%BUILDTYPE_INTERNAL%
echo -- CMake build directory: %BUILD_DIR%
mkdir %BUILD_DIR%
pushd %BUILD_DIR%

set CMAKE_COMMAND=-G %GENERATOR_INTERNAL% %CMAKE_PARAMS_INTERNAL% -A %ARCHITECTURE_INTERNAL% -S ../..
echo -- CMake command: %CMAKE_COMMAND%
cmake %CMAKE_COMMAND%
if errorlevel 1 %THEN%
	goto :error_build
%ENDIF%

echo -- Build succeeded!
popd
goto :eof

:error_param_generator
echo ERROR: Build tool must be specified (mvc16).
exit /b 1

:error_param_architecture
echo ERROR: Build architecture should be set (Win32, x64)
exit /b 2

:error_param_buildtype
echo ERROR: Build type must be specified (Debug, Release)
exit /b 3

:error_param_libtype
echo ERROR: Library type must be specified (shared, static)
exit /b 4

:error_param_crttype
echo ERROR: CRT type must be specified (md, mt)
exit /b 5

:error_crttype_conflict
echo ERROR: CRT type conflict(shared and mt)
exit /b 6

:error_build
echo ERROR: Failed to build project - see above and correct
popd
exit /b 7