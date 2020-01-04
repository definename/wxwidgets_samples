project(software_list)

include(PCHSupport)
include(CRTLinkage)

include(${wxWidgets_USE_FILE})

configure_file(src/res/nullapp.rc.cmake nullapp.rc @ONLY)

set(PROJECT_HEADERS
	include/NullApp.h
	include/NullFrame.h
	include/SoftListCtrl.h
	include/SoftPanel.h
	include/SoftScanner.h
	include/Types.h
	include/Utils.h
	)

set(PROJECT_SOURCES
	src/NullApp.cpp
	src/NullFrame.cpp
	src/SoftListCtrl.cpp
	src/SoftPanel.cpp
	src/SoftScanner.cpp
	src/Utils.cpp
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
	${libaim_INCLUDE_DIRS}
	)

target_link_libraries(${PROJECT_NAME}
	${wxWidgets_LIBRARIES}
	${POCO_LIBRARIES}
	${libaim_LIBRARIES}
	)

add_dependencies(${PROJECT_NAME}
	Poco
	libaim
	)

#set_target_properties(${PROJECT_NAME} PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD 1)

