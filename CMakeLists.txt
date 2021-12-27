cmake_minimum_required(VERSION 3.5)

#include(GNUInstallDirs)

project(libembroidery VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option( EMBROIDERY_BUILD_SHARED_LIBS "Build shared libary." ON )

set(CMAKE_C_FLAGS "-fPIC")
set(LIBRARY_SOURCE_FILES
    compress.c
    fills.c
    image.c
    embroidery.h
    encoding.c
    formats.c
    tests.c
    thread-color.c
    parsers.c
    generators.c
    utility.c
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic -Wall -g -O2")

if(EMBROIDERY_BUILD_SHARED_LIBS)
add_library(embroidery SHARED
    ${LIBRARY_SOURCE_FILES}
)

target_include_directories(embroidery
    INTERFACE
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    PRIVATE
        include
)
target_compile_definitions(embroidery PUBLIC LIBEMBROIDERY_SHARED)
endif()

add_library(embroidery_static STATIC
    ${LIBRARY_SOURCE_FILES}
)

target_include_directories(embroidery_static
    INTERFACE
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    PRIVATE
        include
)

add_executable(embroider
    embroider-main.c
)

if(EMBROIDERY_BUILD_SHARED_LIBS)
target_include_directories(embroider
    INTERFACE
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        include
)
endif()

# These link against the static libraries
# so we know that it is the current build that they're
# linked against.
if (WIN32)
target_link_libraries(embroider PRIVATE embroidery_static)
else(WIN32)
target_link_libraries(embroider PRIVATE embroidery_static m)
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
