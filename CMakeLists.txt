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
	src/array.c
	src/compress.c
	src/data.c
	src/encoding.c
	src/file.c
	src/fill.c
	src/geometry.c
	src/image.c
	src/pattern.c
	src/string.c
	src/thread_colors.c
	src/thread.c

	src/formats/100.c
	src/formats/10o.c
	src/formats/art.c
	src/formats/bmc.c
	src/formats/bro.c
	src/formats/cnd.c
	src/formats/col.c
	src/formats/csd.c
	src/formats/csv.c
	src/formats/dat.c
	src/formats/dsb.c
	src/formats/dst.c
	src/formats/dsz.c
	src/formats/dxf.c
	src/formats/edr.c
	src/formats/emd.c
	src/formats/exy.c
	src/formats/eys.c
	src/formats/fxy.c
	src/formats/gc.c
	src/formats/gnc.c
	src/formats/gt.c
	src/formats/hus.c
	src/formats/inb.c
	src/formats/jef.c
	src/formats/ksm.c
	src/formats/mit.c
	src/formats/new.c
	src/formats/ofm.c
	src/formats/pcd.c
	src/formats/pcm.c
	src/formats/pcq.c
	src/formats/pcs.c
	src/formats/pes.c
	src/formats/plt.c
	src/formats/rgb.c
	src/formats/sew.c
	src/formats/shv.c
	src/formats/sst.c
	src/formats/stx.c
	src/formats/svg.c
	src/formats/t09.c
	src/formats/tap.c
	src/formats/thr.c
	src/formats/txt.c
	src/formats/u00.c
	src/formats/u01.c
	src/formats/vip.c
	src/formats/vp3.c
	src/formats/xxx.c
	src/formats/zsk.c

	src/geometry/arc.c
	src/geometry/circle.c
	src/geometry/ellipse.c
	src/geometry/line.c
	src/geometry/polygon.c
	src/geometry/vector.c

	src/test/test.c
	src/test/arc.c
	src/test/circle.c
	src/test/convert.c
	src/test/ellipse.c
	src/test/fill.c
	src/test/format_table.c
	src/test/render.c
	src/test/thread_color.c
	src/test/vector.c
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
