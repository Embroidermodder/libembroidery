cmake_minimum_required(VERSION 3.5)

project(libembroidery VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED True)

option( EMBROIDERY_BUILD_SHARED_LIBS "Build shared library." ON )
option( EMBROIDERY_BUILD_CLI "Build embroider command line tool." ON )

set(C_SOURCES
	main.c
	embroidery.h
	embroidery-internal.h
	array.c
	testing.c
	formats.c
	pattern.c
	image.c
	fill.c
	geometry.c
	compress.c
	thread-color.c
)

add_library(embroidery_static STATIC ${C_SOURCES})

if(EMBROIDERY_BUILD_SHARED_LIBS)
add_library(embroidery SHARED ${C_SOURCES})

target_compile_definitions(embroidery PUBLIC LIBEMBROIDERY_SHARED)

target_include_directories(embroidery INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
endif()

if(EMBROIDERY_BUILD_CLI)
add_executable(embroider ${C_SOURCES})

target_compile_definitions(embroider PUBLIC LIBEMBROIDERY_CLI)
endif()

if (WIN32)
add_compile_options(
	-fPIC
	-pedantic
	-Wall
	$<$<CONFIG:DEBUG>:-g>
	$<$<CONFIG:DEBUG>:-Wextra>
	$<$<CONFIG:DEBUG>:-ansi>
	$<$<CONFIG:DEBUG>:-Werror>
)
else(WIN32)
add_compile_options(
	-fPIC
	-pedantic
	-Wall
	-O2
	$<$<CONFIG:DEBUG>:-g>
	$<$<CONFIG:DEBUG>:-Wextra>
	$<$<CONFIG:DEBUG>:-ansi>
	$<$<CONFIG:DEBUG>:-Werror>
)

target_link_libraries(embroider PRIVATE m)
endif (WIN32)

if(EMBROIDERY_BUILD_SHARED_LIBS)
install(
    TARGETS
       embroidery
       embroidery_static
       embroider
    LIBRARY DESTINATION /usr/lib
    ARCHIVE DESTINATION /usr/lib
    RUNTIME DESTINATION /usr/bin
)
endif()
