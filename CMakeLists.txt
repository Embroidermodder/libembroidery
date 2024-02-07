cmake_minimum_required(VERSION 3.5)

project(libembroidery VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED True)

option( EMBROIDERY_BUILD_SHARED_LIBS "Build shared library." ON )
option( EMBROIDERY_BUILD_CLI "Build embroider command line tool." ON )
option( EMBROIDERY_TESTING "Run tests." ON )
option( EMBROIDERY_EXPERIMENTAL_TESTING "Run experimental tests." OFF )

if (WIN32)
#add_compile_options(
#    -O2
#)
else (WIN32)
add_compile_options(
    -g
    -O2
    -fPIC
    -std=c99
    -pedantic
    -Wall
    -Wextra
#    -Werror
)
endif (WIN32)

add_library(embroidery_static STATIC embroidery.c embroidery.h)

if(EMBROIDERY_BUILD_SHARED_LIBS)
add_library(embroidery SHARED embroidery.c embroidery.h)

target_compile_definitions(embroidery PUBLIC LIBEMBROIDERY_SHARED)
endif()

if(EMBROIDERY_BUILD_CLI)
add_executable(embroider main.c)

target_compile_definitions(embroider PUBLIC LIBEMBROIDERY_CLI)

if (WIN32)
else (WIN32)
target_link_libraries(embroider PRIVATE m)
endif (WIN32)
endif()

if(EMBROIDERY_BUILD_SHARED_LIBS)
if(WIN32)

# TODO: Test this.
# https://cmake.org/cmake/help/book/mastering-cmake/chapter/Install.html

install(
    FILES embroidery.h
    DESTINATION "<SystemDrive>/Program Files/<Project Name>"
)

install(
    TARGETS
       embroidery
       embroidery_static
       embroider
    EXPORT embroidery
    LIBRARY DESTINATION "<SystemDrive>/Program Files/<Project Name>"
    ARCHIVE DESTINATION "<SystemDrive>/Program Files/<Project Name>"
    RUNTIME DESTINATION "<SystemDrive>/Program Files/<Project Name>"
)

else(WIN32)

include(GNUInstallDirs)

install(
    FILES embroidery.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    TARGETS
       embroidery
       embroidery_static
       embroider
    EXPORT embroidery
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
endif(WIN32)
endif()

if (EMBROIDERY_TESTING)
include(testing.cmake)
endif (EMBROIDERY_TESTING)

if (EMBROIDERY_EXPERIMENTAL_TESTING)
include(experimental.cmake)
endif (EMBROIDERY_EXPERIMENTAL_TESTING)

include(cpack.cmake)
