@echo off

set GENERATOR="%1"
set ARCHITECTURE="%2"
set LIBTYPE="%3"
set CRTTYPE="%4"
set BUILDTYPE="%5"

:: Determine CMake generator.
if %GENERATOR% == "" goto :error_param_generator
set GENERATOR_INTERNAL=""
if %GENERATOR% == "vc16" set GENERATOR_INTERNAL="Visual Studio 16 2019"
if %GENERATOR_INTERNAL% == "" goto :error_param_generator

:: Determine generator architecture.
if %ARCHITECTURE% == "" goto :error_param_architecture
set ARCHITECTURE_INTERNAL=""
if %ARCHITECTURE% == "x86" set ARCHITECTURE_INTERNAL=Win32
if %ARCHITECTURE% == "x64" set ARCHITECTURE_INTERNAL=x64
if %ARCHITECTURE_INTERNAL% == "" goto :error_param_architecture

:: Determine library type.
if %LIBTYPE% == "" goto :error_param_libtype
set LIBTYPE_INTERNAL=""
if %LIBTYPE% == "shared" set LIBTYPE_INTERNAL="shared"
if %LIBTYPE% == "static" set LIBTYPE_INTERNAL="static"
if %LIBTYPE_INTERNAL% == "" goto :error_param_libtype

:: Determine CRT type.
if %CRTTYPE% == "" goto :error_param_crttype
set CRTTYPE_INTERNAL=""
if %CRTTYPE% == "md" set CRTTYPE_INTERNAL="md"
if %CRTTYPE% == "mt" set CRTTYPE_INTERNAL="mt"
if %CRTTYPE_INTERNAL% == "" goto :error_param_crttype

:: Determine build type
if %BUILDTYPE% == "" goto :error_param_buildtype
set BUILDTYPE_INTERNAL=""
if %BUILDTYPE% == "debug" set BUILDTYPE_INTERNAL="debug"
if %BUILDTYPE% == "release" set BUILDTYPE_INTERNAL="release"
if %BUILDTYPE_INTERNAL% == "" goto :error_param_buildtype

:: Check for conflicting CRT and library type.
if %LIBTYPE_INTERNAL% == "shared" if %CRTTYPE_INTERNAL% == "mt" goto :error_crttype_conflict

:: Compose CMake parameters string.
set CMAKE_PARAMS_INTERNAL=%BUILDTYPE_INTERNAL%
if %LIBTYPE_INTERNAL% == "shared" set CMAKE_PARAMS_INTERNAL=-DBUILD_SHARED_LIBS=ON
if %LIBTYPE_INTERNAL% == "static" set CMAKE_PARAMS_INTERNAL=-DBUILD_SHARED_LIBS=OFF

if %CRTTYPE_INTERNAL% == "mt" set CMAKE_PARAMS_INTERNAL=%CMAKE_PARAMS_INTERNAL% -DBUILD_WITH_STATIC_CRT=ON
if %CRTTYPE_INTERNAL% == "md" set CMAKE_PARAMS_INTERNAL=%CMAKE_PARAMS_INTERNAL% -DBUILD_WITH_STATIC_CRT=OFF

if %BUILDTYPE_INTERNAL% == "debug" set CMAKE_PARAMS_INTERNAL=%CMAKE_PARAMS_INTERNAL% -DCMAKE_CONFIGURATION_TYPES=Debug
if %BUILDTYPE_INTERNAL% == "release" set CMAKE_PARAMS_INTERNAL=%CMAKE_PARAMS_INTERNAL% -DCMAKE_CONFIGURATION_TYPES=Release

:: Create build directory.
set BUILD_DIR=..\build\%GENERATOR%-%ARCHITECTURE_INTERNAL%-%BUILDTYPE_INTERNAL%
echo == Create build dir %BUILD_DIR%
mkdir %BUILD_DIR%
pushd %BUILD_DIR%

:: Run CMake.
set CMAKE_SOURCE_DIR=../..
set CMAKE_PARAMS=-G %GENERATOR_INTERNAL% -A %ARCHITECTURE_INTERNAL% %CMAKE_PARAMS_INTERNAL% %CMAKE_SOURCE_DIR%
echo == Cmake params %CMAKE_PARAMS%
cmake %CMAKE_PARAMS%

if errorlevel 1 goto :error_build

:: Exit
echo == Build succeeded!
popd
goto :eof

:error_param_generator
echo =! Invalid generator was given (vc16).
exit /b 1

:error_param_architecture
echo =! Invalid architecture was given (x86, x64).
exit /b 2

:error_param_libtype
echo =! Invalid lib type was given (shared, static).
exit /b 3

:error_param_crttype
echo =! Invalid crt type was given (md, mt).
exit /b 4

:error_param_buildtype
echo =! Invalid build type was given (debug, release).
exit /b 5

:error_build
echo =! Failed to build project - see above and correct.
popd
exit /b 6