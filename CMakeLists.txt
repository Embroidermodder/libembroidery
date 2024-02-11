cmake_minimum_required(VERSION 3.5)

project(libembroidery VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED True)

option( EMBROIDERY_BUILD_SHARED_LIBS "Build shared library." ON )
option( EMBROIDERY_BUILD_CLI "Build embroider command line tool." ON )
option( EMBROIDERY_TESTING "Run tests." ON )

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
#    -pedantic
#    -Wall
#    -Wextra
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
enable_testing()

add_test(
    NAME installed
    COMMAND bash ${PROJECT_SOURCE_DIR}/test/exists.sh
)

macro(emb_test)
    add_test(
        NAME ${ARGV0}
        COMMAND $<TARGET_FILE:embroider> --test ${ARGV1}
    )
    set_tests_properties(${ARGV0} PROPERTIES TIMEOUT 5)
endmacro()

macro(fill_test)
    add_test(
        NAME ${ARGV0}_FILL_SVG
        COMMAND $<TARGET_FILE:embroider> --fill demos/${ARGV0}.png 130 ${ARGV0}.svg
    )
    set_tests_properties(${ARGV0}_FILL_SVG PROPERTIES TIMEOUT 5)
endmacro()

macro(cross_test)
    add_test(
        NAME ${ARGV0}_CROSS_SVG
        COMMAND $<TARGET_FILE:embroider> --cross-stitch demos/${ARGV0}.png 130 ${ARGV0}.svg
    )
    set_tests_properties(${ARGV0}_CROSS_SVG PROPERTIES TIMEOUT 5)
endmacro()

macro(render_fill_test)
    add_test(
        NAME ${ARGV0}_FILL_RENDER
        COMMAND
    		$<TARGET_FILE:embroider> --fill demos/${ARGV0}.png 130 ${ARGV0}.csv &&
	    	$<TARGET_FILE:embroider> --fill ${ARGV0}.csv ${ARGV0}.png
    )
#    set_tests_properties(${ARGV0}_FILL_REDNER PROPERTIES TIMEOUT 5)
endmacro()

macro(render_cross_test)
    add_test(
        NAME ${ARGV0}_CROSS_RENDER
        COMMAND
		    $<TARGET_FILE:embroider> --cross-stitch demos/${ARGV0}.png 130 ${ARGV0}.csv &&
			$<TARGET_FILE:embroider> --render ${ARGV0}.csv ${ARGV0}_render.png
    )
#    set_tests_properties(${ARGV0}_CROSS_REDNER PROPERTIES TIMEOUT 5)
endmacro()

macro(test_convert)
    add_test(
        NAME CONVERT_${ARGV0}_${ARGV1}
        COMMAND
		    $<TARGET_FILE:embroider> --convert ${ARGV0} ${ARGV1}
    )    
endmacro()

emb_test(testCircle1 0)
emb_test(testCircle2 1)
emb_test(testThread 2)
emb_test(testThread3 3)
emb_test(testThread4 4)
emb_test(testThread5 5)
emb_test(testThread6 6)
emb_test(testThread7 7)
emb_test(testThread8 8)
emb_test(testThread9 9)
emb_test(testThread10 10)
emb_test(testThread11 11)
emb_test(testThread12 12)
emb_test(testThread13 13)
#emb_test(testThread14 14)

fill_test(donut 130)
fill_test(logo-spirals 130)
fill_test(berries 130)
fill_test(snow-squirrel 130)
fill_test(great-tit 130)
fill_test(owl 130)
fill_test(logo 130)

cross_test(logo)
render_fill_test(logo)
render_cross_test(logo)

endif (EMBROIDERY_TESTING)

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
