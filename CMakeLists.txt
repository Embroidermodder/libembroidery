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

    src/formats/format_10o.c
    src/formats/format_100.c
    src/formats/format_art.c
    src/formats/format_bmc.c
    src/formats/format_bro.c
    src/formats/format_cnd.c
    src/formats/format_col.c
    src/formats/format_csd.c
    src/formats/format_csv.c
    src/formats/format_dat.c
    src/formats/format_dem.c
    src/formats/format_dsb.c
    src/formats/format_dst.c
    src/formats/format_dsz.c
    src/formats/format_dxf.c
    src/formats/format_edr.c
    src/formats/format_emd.c
    src/formats/format_exp.c
    src/formats/format_exy.c
    src/formats/format_eys.c
    src/formats/format_fxy.c
    src/formats/format_gc.c
    src/formats/format_gnc.c
    src/formats/format_gt.c
    src/formats/format_hus.c
    src/formats/format_inb.c
    src/formats/format_inf.c
    src/formats/format_jef.c
    src/formats/format_ksm.c
    src/formats/format_max.c
    src/formats/format_mit.c
    src/formats/format_new.c
    src/formats/format_ofm.c
    src/formats/format_pcd.c
    src/formats/format_pcm.c
    src/formats/format_pcq.c
    src/formats/format_pcs.c
    src/formats/format_pec.c
    src/formats/format_pel.c
    src/formats/format_pem.c
    src/formats/format_pes.c
    src/formats/format_phb.c
    src/formats/format_phc.c
    src/formats/format_plt.c
    src/formats/format_rgb.c
    src/formats/format_sew.c
    src/formats/format_shv.c
    src/formats/format_sst.c
    src/formats/format_stx.c
    src/formats/format_svg.c
    src/formats/format_t01.c
    src/formats/format_t09.c
    src/formats/format_tap.c
    src/formats/format_thr.c
    src/formats/format_txt.c
    src/formats/format_u00.c
    src/formats/format_u01.c
    src/formats/format_vip.c
    src/formats/format_vp3.c
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
install(
    FILES src/embroidery.h
    DESTINATION .
)

install(
    TARGETS
       embroidery
       embroidery_static
       embroider
    LIBRARY DESTINATION .
    ARCHIVE DESTINATION .
    RUNTIME DESTINATION .
)
endif()

include(cpack.cmake)
