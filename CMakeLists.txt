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
	src/formats/autodesk.c
	src/formats/barudan.c
	src/formats/bernina.c
	src/formats/bitmap_cache.c
	src/formats/bits_and_volts.c
	src/formats/brother.c
	src/formats/colors.c
	src/formats/csv.c
	src/formats/eltac.c
	src/formats/janome.c
	src/formats/gold_thread.c
	src/formats/great_notions.c
	src/formats/melco.c
	src/formats/pfaff.c
	src/formats/sierra.c
	src/formats/singer.c
	src/formats/smoothie.c
	src/formats/toyota.c
	src/formats/svg.c
	src/formats/zsk_usa.c

	src/circle.c
	src/compress.c
	src/data.c
	src/encoding.c
	src/file.c
	src/image.c
	src/pattern.c
	src/thread_colors.c
	src/unsorted.c
)

include_directories(include)

add_library(embroidery_static STATIC ${LIBRARY_SRC})

add_library(embroidery SHARED ${LIBRARY_SRC})
target_compile_definitions(embroidery PUBLIC LIBEMBROIDERY_SHARED)

add_executable(sew src/sew.c)
target_link_libraries(sew PRIVATE embroidery_static)

if (WIN32)
else (WIN32)
    target_link_libraries(sew PRIVATE m)
endif (WIN32)

if(WIN32)

# TODO: Test this.
# https://cmake.org/cmake/help/book/mastering-cmake/chapter/Install.html
#
# Does the location get added to the Windows PATH?

install(
    FILES embroidery.h
    DESTINATION "<SystemDrive>/Program Files/<Project Name>"
)

install(
    TARGETS
       embroidery
       embroidery_static
       sew
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
       sew
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

enable_testing()

function(make_test name)
	set(execname test_${name})
	set(testname ${name}_test)
	add_executable(${execname} test/${name}.c)
	target_link_libraries(${execname} PRIVATE embroidery_static)
	if (WIN32)
	else (WIN32)
		target_link_libraries(${execname} PRIVATE m)
	endif (WIN32)
	add_test(${testname} ${execname})
endfunction()

make_test(arc)
make_test(circle)
make_test(convert)
make_test(ellipse)
make_test(fill)
make_test(format_table)
make_test(render)
make_test(thread_color)
make_test(vector)

