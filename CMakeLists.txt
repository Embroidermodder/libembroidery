cmake_minimum_required(VERSION 3.5)

#include(GNUInstallDirs)

project(libembroidery VERSION 1.0.0 LANGUAGES C CXX ASM_NASM)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(LIBRARY_SOURCE_FILES libembroidery.c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic -Wall -O2")

add_library(embroidery_static STATIC
    ${LIBRARY_SOURCE_FILES}
)

add_custom_command(OUTPUT libembroidery_data.bin
                   COMMAND  nasm -f bin -o libembroidery_data.bin -l libembroidery_data.lst ${CMAKE_CURRENT_SOURCE_DIR}/libembroidery_data.asm
)
add_executable(testdata test.c)
add_custom_target(datafile
                  DEPENDS libembroidery_data.bin)
add_dependencies(testdata datafile)

#compile SWIG if requested
add_subdirectory(experimental)

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

target_include_directories(embroider
    INTERFACE
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        include
)

# These link against the static libraries
# so we know that it is the current build that they're
# linked against.
if(WIN32)
target_link_libraries(embroider PRIVATE embroidery_static)
else(WIN32)
target_link_libraries(embroider PRIVATE embroidery_static m)
endif(WIN32)

install(
    TARGETS
       embroidery
       embroidery_static
       embroider
    LIBRARY DESTINATION /usr/lib
    ARCHIVE DESTINATION /usr/lib
    RUNTIME DESTINATION /usr/bin/env
)
