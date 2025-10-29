cmake_minimum_required(VERSION 3.5)

project(libembroidery VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED True)

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
    -Wall
    -Wextra
#    -Werror
)
endif (WIN32)

set(LIBRARY_SRC
	src/pattern.c
	src/compress.c
	src/formats.c
	src/geometry.c
	src/script.c
	src/data.c
	src/embroidery.h
)

add_library(embroidery_static STATIC ${LIBRARY_SRC})

add_library(embroidery SHARED ${LIBRARY_SRC})
target_compile_definitions(embroidery PUBLIC LIBEMBROIDERY_SHARED)

add_executable(emb_convert src/convert.c)
target_link_libraries(emb_convert PRIVATE embroidery_static)

add_executable(emb_test src/test.c)
target_link_libraries(emb_test PRIVATE embroidery_static)

if (WIN32)
else (WIN32)
    target_link_libraries(emb_convert PRIVATE m)
    target_link_libraries(emb_test PRIVATE m)
endif (WIN32)

# add_test(emb_test emb_test)
# add_dependencies(check emb_test)
#
# add_custom_target(check COMMAND emb_test)

if(WIN32)

# TODO: Test this.
# https://cmake.org/cmake/help/book/mastering-cmake/chapter/Install.html
#
# Does the location get added to the Windows PATH?

install(
    FILES src/embroidery.h
    DESTINATION "<SystemDrive>/Program Files/<Project Name>"
)

install(
    FILES bin/needle
    DESTINATION "<SystemDrive>/Program Files/<Project Name>"
)

install(
    TARGETS
       embroidery
       embroidery_static
       emb_convert
    EXPORT embroidery
    LIBRARY DESTINATION "<SystemDrive>/Program Files/<Project Name>"
    ARCHIVE DESTINATION "<SystemDrive>/Program Files/<Project Name>"
    RUNTIME DESTINATION "<SystemDrive>/Program Files/<Project Name>"
)

else(WIN32)

include(GNUInstallDirs)

install(
    FILES src/embroidery.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    FILES bin/needle
    DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(
    TARGETS
       embroidery
       embroidery_static
       emb_convert
    EXPORT embroidery
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

endif(WIN32)

# https://cmake.org/cmake/help/book/mastering-cmake/chapter/Packaging%20With%20CPack.html

if(WIN32)
set(CPACK_GENERATOR "WIX")
set(CPACK_SOURCE_GENERATOR "WIX")
else(WIN32)
set(CPACK_GENERATOR "DEB")
set(CPACK_SOURCE_GENERATOR "DEB")
endif(WIN32)
set(CPACK_PACKAGE_DIRECTORY build)
set(CPACK_PACKAGE_VENDOR "The Embroidermodder Team")
set(CPACK_SOURCE_IGNORE_FILES .git .github)

include(CPack)
