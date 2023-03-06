cmake_minimum_required(VERSION 3.5)

project(libembroidery VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED True)

option( EMBROIDERY_BUILD_SHARED_LIBS "Build shared library." ON )
option( EMBROIDERY_BUILD_CLI "Build embroider command line tool." ON )

set(C_SOURCES
    src/geometry/arc.c
    src/geometry/circle.c
    src/geometry/ellipse.c
    src/geometry/functions.c
    src/geometry/line.c
	src/geometry/path.c
	src/geometry/polygon.c
	src/geometry/polyline.c
	src/geometry/rect.c
	src/geometry/text.c
	src/geometry/vector.c

    src/formats/format_xxx.c
    src/formats/format_zsk.c

    src/main.c
	src/array.c
	src/embroidery.h
	src/embroidery_internal.h
	src/formats.c
	src/geometry.c
	src/pattern.c
	src/image.c
	src/fill.c
	src/compress.c
	src/encoding.c
	src/thread-color.c
)

add_compile_options(
	-g
	-O2
	-fPIC
	-std=c99
	-pedantic
	-Wall
	-Wextra
#	-Werror
)

include_directories(src)

add_library(embroidery_static STATIC ${C_SOURCES})

if(EMBROIDERY_BUILD_SHARED_LIBS)
add_library(embroidery SHARED ${C_SOURCES})

target_compile_definitions(embroidery PUBLIC LIBEMBROIDERY_SHARED)
endif()

if(EMBROIDERY_BUILD_CLI)
add_executable(embroider ${C_SOURCES})

target_compile_definitions(embroider PUBLIC LIBEMBROIDERY_CLI)

if (WIN32)
else (WIN32)
target_link_libraries(embroider PRIVATE m)
endif (WIN32)
endif()

if(EMBROIDERY_BUILD_SHARED_LIBS)
if(APPLE)
install(
    FILES
        src/embroidery.h
    DESTINATION /usr/local/include
)

install(
    TARGETS
       embroidery
       embroidery_static
       embroider
    LIBRARY DESTINATION /usr/local/lib
    ARCHIVE DESTINATION /usr/local/lib
    RUNTIME DESTINATION /usr/bin
)
else()
install(
    FILES
        src/embroidery.h
    DESTINATION /usr/include
)

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
endif()
