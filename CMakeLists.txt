cmake_minimum_required(VERSION 3.5)

#include(GNUInstallDirs)

project(libembroidery VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(LIBRARY_SOURCE_FILES
    compress.c
    tests.c
    fills.c
    image.c
    format-100.c
    format-10o.c
    format-art.c
    format-bmc.c
    format-bro.c
    format-cnd.c
    format-col.c
    format-csd.c
    format-csv.c
    format-dat.c
    format-dem.c
    format-dsb.c
    format-dst.c
    format-dsz.c
    format-dxf.c
    format-edr.c
    format-emd.c
    format-exp.c
    format-exy.c
    format-eys.c
    format-fxy.c
    format-gc.c
    format-gnc.c
    format-gt.c
    format-hus.c
    format-inb.c
    format-inf.c
    format-jef.c
    format-ksm.c
    format-max.c
    format-mit.c
    format-new.c
    format-ofm.c
    format-pcd.c
    format-pcm.c
    format-pcq.c
    format-pcs.c
    format-pec.c
    format-pel.c
    format-pem.c
    format-pes.c
    format-phb.c
    format-phc.c
    format-plt.c
    format-rgb.c
    format-sew.c
    format-shv.c
    format-sst.c
    format-stx.c
    format-svg.c
    format-t01.c
    format-t09.c
    format-tap.c
    format-thr.c
    format-txt.c
    format-u00.c
    format-u01.c
    format-vip.c
    format-vp3.c
    format-xxx.c
    format-zsk.c
    thread-color.c
    utility.c
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic -Wall -O2")

add_library(embroidery_static STATIC
    ${LIBRARY_SOURCE_FILES}
)
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
    RUNTIME DESTINATION /usr/bin
)
