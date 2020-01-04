project(gauge)

include(PCHSupport)
include(CRTLinkage)

include(${wxWidgets_USE_FILE})

configure_file(src/res/project.rc.cmake project.rc @ONLY)

set(PROJECT_HEADERS
	include/ProjectFrame.h
	include/ProjectApp.h
	)

set(PROJECT_SOURCES
	src/ProjectFrame.cpp
	src/ProjectApp.cpp
	)
	
set(PROJECT_RESOURCES
	src/res/project.ico
	${CMAKE_CURRENT_BINARY_DIR}/project.rc
	)
set_source_files_properties(
	${CMAKE_CURRENT_BINARY_DIR}/project.rc PROPERTIES GENERATED 1)
	
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

include_directories(include
	${libaim_INCLUDE_DIRS}
	)
	
target_link_libraries(${PROJECT_NAME}
	${wxWidgets_LIBRARIES}
	${libaim_LIBRARIES}
	)
	
add_dependencies(${PROJECT_NAME}
	libaim
	)

#set_target_properties(${PROJECT_NAME} PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD 1)

