cmake_minimum_required(VERSION 3.5)

project(libembroidery VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED True)

option( EMBROIDERY_BUILD_SHARED_LIBS "Build shared library." ON )
option( EMBROIDERY_BUILD_CLI "Build embroider command line tool." ON )

set(C_SOURCES
	main.c
	embroidery.h
	internal.h
	array.c
	testing.c
	formats.c
	format-data.c
	pattern.c
	image.c
	fill.c
	geometry.c
	compress.c
	encoding.c
	thread-color.c
)

add_compile_options(
	-g
	-O2
	-fPIC
	-ansi
	-pedantic
	-Wall
	-Wextra
#	-Werror
)

add_library(embroidery_static STATIC ${C_SOURCES})

target_include_directories(embroidery_static INTERFACE src)

if(EMBROIDERY_BUILD_SHARED_LIBS)
add_library(embroidery SHARED ${C_SOURCES})

target_compile_definitions(embroidery PUBLIC LIBEMBROIDERY_SHARED)

target_include_directories(embroidery INTERFACE src)
endif()

if(EMBROIDERY_BUILD_CLI)
add_executable(embroider ${C_SOURCES})

target_compile_definitions(embroider PUBLIC LIBEMBROIDERY_CLI)

target_include_directories(embroider INTERFACE src)
endif()

if (WIN32)
else (WIN32)
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
