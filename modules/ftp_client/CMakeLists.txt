project(ftp_client)

configure_file(src/res/nullapp.rc.cmake nullapp.rc @ONLY)

set(PROJECT_HEADERS
	include/FTPApp.h
	include/FTPClient.h
	include/FTPFrame.h
	include/FTPList.h
	include/FTPListLocal.h
	include/FTPListRemote.h
	include/FTPPanel.h
	include/Images.h
	include/SplitterWindow.h
	include/TextControl.h
	include/VolumeController.h
	)

set(PROJECT_SOURCES
	src/FTPApp.cpp
	src/FTPClient.cpp
	src/FTPFrame.cpp
	src/FTPList.cpp
	src/FTPListLocal.cpp
	src/FTPListRemote.cpp
	src/FTPPanel.cpp
	src/SplitterWindow.cpp
	src/TextControl.cpp
	src/VolumeController.cpp
	)

set(PROJECT_RESOURCES
	src/res/nullapp.ico
	${CMAKE_CURRENT_BINARY_DIR}/nullapp.rc
	)
set_source_files_properties(
	${CMAKE_CURRENT_BINARY_DIR}/nullapp.rc PROPERTIES GENERATED 1)

set(MISC
	src/pch.h
	src/pch.cpp
	)

add_definitions(
	-DUNICODE
	-D_UNICODE
	)

source_group("Header Files" FILES ${PROJECT_HEADERS})
source_group("Source Files" FILES ${PROJECT_SOURCES})
source_group("Resource Files" FILES ${PROJECT_RESOURCES})
source_group("" FILES ${MISC})
	
add_executable(${PROJECT_NAME} WIN32
	${PROJECT_HEADERS}
	${PROJECT_SOURCES}
	${PROJECT_RESOURCES}
	${MISC}
	)

add_precompiled_headers(${PROJECT_NAME} "src/")

include_directories(
	include
	${POCO_INCLUDE_DIR}
	)

target_link_libraries(${PROJECT_NAME}
	${wxWidgets_LIBRARIES}
	${POCO_LIBRARIES}
	Ws2_32.lib
	Iphlpapi.lib
	)

add_dependencies(${PROJECT_NAME}
	Poco
	)

#set_target_properties(${PROJECT_NAME} PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD 1)

