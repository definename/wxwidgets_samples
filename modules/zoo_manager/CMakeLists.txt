project(zoo_manager)

configure_file(src/res/nullapp.rc.cmake nullapp.rc @ONLY)

set(PROJECT_HEADERS
	include/ZooApp.h
	include/ZooAddUpdateDialog.h
	include/ZooAddUpdatePanel.h
	include/ZooFrame.h
	include/ZooFramePanel.h
	include/ZooList.h
	include/ZooTypes.h
	include/ZooUtil.h
	)
set(PROJECT_SOURCES
	src/ZooApp.cpp
	src/ZooAddUpdateDialog.cpp
	src/ZooAddUpdatePanel.cpp
	src/ZooFrame.cpp
	src/ZooFramePanel.cpp
	src/ZooList.cpp
	)
set(PROJECT_RESOURCES
	src/res/nullapp.ico
	${CMAKE_CURRENT_BINARY_DIR}/nullapp.rc
	)
set(MISC
	src/pch.h
	src/pch.cpp
	)
set_source_files_properties(
	${CMAKE_CURRENT_BINARY_DIR}/nullapp.rc PROPERTIES GENERATED 1)

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

target_include_directories(${PROJECT_NAME}
	PRIVATE
		include
		${Boost_INCLUDE_DIRS}
	)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		${wxWidgets_LIBRARIES}
		${Boost_LIBRARIES}
	)

add_dependencies(${PROJECT_NAME}
	Poco
	)

#set_target_properties(${PROJECT_NAME} PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD 1)