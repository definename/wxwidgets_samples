project(downloader_wx)

include(PCHSupport)
include(CRTLinkage)

include(${wxWidgets_USE_FILE})

set(PROJECT_SOURCES
	src/ProjectApp.cpp
	src/DownloadFrame.cpp
	src/DownloadPanel.cpp
	src/DownloadThread.cpp
	src/Installer.cpp
	)
	
set(PROJECT_HEADERS
	include/ProjectApp.h
	include/DownloadFrame.h
	include/DownloadPanel.h
	include/DownloadThread.h
	include/Installer.h
	)
	
set(MISC
	src/pch.h
	src/pch.cpp
	)
	
add_definitions(
	-DUNICODE
	-D_UNICODE
)
	
add_executable(${PROJECT_NAME} WIN32
	${PROJECT_SOURCES}
	${PROJECT_HEADERS}
	${MISC}
	)
	
add_precompiled_headers(${PROJECT_NAME} "src/")

include_directories(include
	)
	
target_link_libraries(${PROJECT_NAME}
	${wxWidgets_LIBRARIES}
	)

#set_target_properties(${PROJECT_NAME} PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD 1)

