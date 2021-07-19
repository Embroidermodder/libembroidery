cmake_minimum_required(VERSION 3.5)

#include(GNUInstallDirs)

project(libembroidery VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(LIBRARY_SOURCE_FILES
    compound-file.c
    compound-file-difat.c
    compound-file-directory.c
    compound-file-fat.c
    compound-file-header.c
    emb-arc.c
    emb-circle.c
    emb-color.c
    emb-compress.c
    emb-ellipse.c
    emb-file.c
    emb-flag.c
    emb-format.c
    emb-hash.c
    emb-hoop.c
    emb-layer.c
    emb-line.c
    emb-logging.c
    emb-path.c
    emb-pattern.c
    emb-point.c
    emb-polygon.c
    emb-polyline.c
    emb-reader-writer.c
    emb-rect.c
    emb-satin-line.c
    emb-settings.c
    emb-spline.c
    emb-stitch.c
    emb-thread.c
    emb-time.c
    emb-vector.c
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
    geom-arc.c
    geom-arc.dxf
    geom-circle.c
    geom-circle.dxf
    geom-line.c
    hashtable.c
    helpers-binary.c
    helpers-misc.c
    thread-color.c
)

add_library(embroidery_static STATIC
    ${LIBRARY_SOURCE_FILES}    
)
add_library(embroidery SHARED
    ${LIBRARY_SOURCE_FILES}
)

target_include_directories(embroidery
    INTERFACE
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        include
)

target_include_directories(embroidery_static
    INTERFACE
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        include
)

add_executable(libembroidery_convert
    libembroidery-convert/libembroidery-convert-main.c
)

target_include_directories(libembroidery_convert
    INTERFACE
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        include
)

target_link_libraries(libembroidery_convert PRIVATE embroidery m)

install(
    TARGETS
       embroidery
       embroidery_static
       libembroidery_convert
    LIBRARY DESTINATION /usr/lib
    ARCHIVE DESTINATION /usr/lib
    RUNTIME DESTINATION /usr/bin/env
)

