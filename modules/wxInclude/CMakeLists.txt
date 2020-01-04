project(wxInclude)

include(PCHSupport)
include(CRTLinkage)

set(PROJECT_HEADERS
	)

set(PROJECT_SOURCES
	src/wxInclude.cpp
	)

set(MISC
	src/pch.h
	src/pch.cpp
	)

add_definitions(
	#-DUNICODE
	#-D_UNICODE
	-D_MBCS
	)

source_group("Header Files" FILES ${PROJECT_HEADERS})
source_group("Source Files" FILES ${PROJECT_SOURCES})
source_group("" FILES ${MISC})
	
add_executable(${PROJECT_NAME}
	${PROJECT_HEADERS}
	${PROJECT_SOURCES}
	${MISC}
	)

add_precompiled_headers(${PROJECT_NAME} "src/")

include_directories(
	include
	)

#target_link_libraries(${PROJECT_NAME}
#	)

#set_target_properties(${PROJECT_NAME} PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD 1)

