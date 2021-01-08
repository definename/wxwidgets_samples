cmake_minimum_required(VERSION 3.19)

project(wxwidgets_samples)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
option(BUILD_WITH_STATIC_CRT "Use static run-time libraries (/MT or /MTd linker flags)" OFF)
option(BUILD_SHARED_LIBS "Build shared libraries (.dll) instead of static ones (.lib)" OFF)

option(BUILD_WITH_POCO "Build with poco support" ON)
option(BUILD_WITH_BOOST "Build with boost support" ON)

include(PCHSupport)
# include(CRTLinkage)
include(ExternalProject)

if (${BUILD_WITH_STATIC_CRT})
	if (${CMAKE_CONFIGURATION_TYPES} STREQUAL "Debug")
		add_compile_options(/MTd)
	elseif(${CMAKE_CONFIGURATION_TYPES} STREQUAL "Release")
		add_compile_options(/MT)
	else()
		message(WARNING ${CMAKE_CONFIGURATION_TYPES})
	endif()
endif()

###########################################################
# Version #################################################

set(VERSION_MAJOR "1")
set(VERSION_MINOR "0")
set(VERSION_BUILD "0")
set(REVISION_COUNT "0")

find_package(Git)
if(GIT_FOUND)
	execute_process(
		COMMAND ${GIT_EXECUTABLE} rev-list HEAD --count
		OUTPUT_VARIABLE DESCRIBE_BUILD
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		OUTPUT_STRIP_TRAILING_WHITESPACE)
	string(REGEX MATCH "[0-9]+" REVISION_COUNT ${DESCRIBE_BUILD})
endif()

set(VERSION_REVISION "${REVISION_COUNT}")
set(VERSION_FILE_REVISION "${REVISION_COUNT}")
set(VERSION_COMPANY_NAME "Carrot Farm")
set(VERSION_COPYRIGHT "Copyright (C) 2020 ${VERSION_COMPANY_NAME}")

# Todo. Remove this hard code.
# set(VERSION_MAJOR "1")
# set(VERSION_MINOR "0")
# set(VERSION_BUILD "0")
# set(VERSION_FILE_REVISION "0")

# Sets executable output folder
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
# External directory path
set(EXTERNAL_PATH ${CMAKE_SOURCE_DIR}/external)
# Patch directory path
set(PATCH_PATH ${EXTERNAL_PATH}/patches)
# External install directory path
set(EXTERNAL_INSTALL_PATH ${CMAKE_BINARY_DIR}/external)
# Poco root directory
set(POCO_ROOT ${EXTERNAL_INSTALL_PATH}/Poco)

###########################################################
# Boost ###################################################

if(BUILD_WITH_BOOST)
	cmake_policy(SET CMP0074 NEW)
	set(Boost_USE_STATIC_LIBS ON)
	set(Boost_USE_MULTITHREADED ON)
	set(Boost_USE_STATIC_RUNTIME ${BUILD_WITH_STATIC_CRT})
	find_package(Boost REQUIRED COMPONENTS serialization)
endif()

###########################################################
# wxWidgets ###############################################

set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base adv net webview REQUIRED)
include(${wxWidgets_USE_FILE})

###########################################################
# Poco ####################################################

if(BUILD_WITH_POCO)
	ExternalProject_Add(
		Poco
		URL "${EXTERNAL_PATH}/poco-1.7.0-all.zip"
		URL_MD5 C5F0EEC1EEDF84323E0991E911465D8D
		CMAKE_ARGS
			-DENABLE_XML:BOOL=ON
			-DENABLE_JSON:BOOL=ON
			-DENABLE_MONGODB:BOOL=OFF			
			-DENABLE_PDF:BOOL=OFF
			-DENABLE_UTIL:BOOL=ON
			-DENABLE_NET:BOOL=ON
			-DENABLE_NETSSL:BOOL=ON
			-DENABLE_NETSSL_WIN:BOOL=OFF
			-DENABLE_CRYPTO:BOOL=ON
			-DENABLE_DATA:BOOL=OFF
			-DENABLE_SEVENZIP:BOOL=OFF
			-DENABLE_ZIP:BOOL=OFF
			-DENABLE_CPPPARSER:BOOL=OFF
			-DENABLE_POCODOC:BOOL=OFF
			-DENABLE_PAGECOMPILER:BOOL=OFF
			-DENABLE_PAGECOMPILER_FILE2PAGE:BOOL=OFF
			-DPOCO_STATIC:BOOL=ON
			-DPOCO_UNBUNDLED:BOOL=OFF
			-DPOCO_MT:BOOL=ON
			-DENABLE_MSVC_MP:BOOL=ON
			-DCMAKE_INSTALL_PREFIX:PATH=${POCO_ROOT}
		PATCH_COMMAND
			${CMAKE_COMMAND} -P ${PATCH_PATH}/poco-1.7.0-all.patches/patch.cmake ${CMAKE_SOURCE_DIR}
		)
	set(POCO_INCLUDE_DIR ${POCO_ROOT}/include)
	set(POCO_LIBRARIES
		# ${POCO_ROOT}/lib/PocoCrypto.lib
		${POCO_ROOT}/lib/PocoFoundation.lib
		${POCO_ROOT}/lib/PocoJSON.lib
		${POCO_ROOT}/lib/PocoNet.lib
		${POCO_ROOT}/lib/PocoUtil.lib
		# ${POCO_ROOT}/lib/PocoNetSSL.lib
		${POCO_ROOT}/lib/PocoXML.lib
		)
SET_PROPERTY(TARGET Poco PROPERTY FOLDER "External")
endif()


#Set PCH memory limit
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zm257")

SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

# add_subdirectory(modules/downloader_boost)
# add_subdirectory(modules/downloader_wx)
# add_subdirectory(modules/downloader_boost_progress)
add_subdirectory(modules/ftp_client)
add_subdirectory(modules/zoo_manager)
add_subdirectory(modules/game_peace_and_war)
# add_subdirectory(modules/gauge)
add_subdirectory(modules/null_app)
# add_subdirectory(modules/null_console)
# add_subdirectory(modules/panel_border)
# add_subdirectory(modules/wxInclude)
# add_subdirectory(modules/software_list)