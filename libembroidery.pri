INCLUDEPATH += ../libembroidery

msvc {
QMAKE_CFLAGS += /Za #equivalent of -pedantic-errors
}

!msvc {
#Ensure anything that does not strictly adhere to C89 is treated as an error
QMAKE_CFLAGS += -std=c89 -pedantic-errors
QMAKE_CFLAGS += -fvisibility=hidden #Check exported symbols using: nm -C -D libembroidery.so | grep ' T '

#Ensure all implicit function declarations are errors rather than warnings
QMAKE_CFLAGS_WARN_ON += -Werror=implicit-function-declaration
}

#Uncomment line below to consider all warnings as errors
#QMAKE_CFLAGS_WARN_ON += -Werror

#Uncomment lines below to hide various warnings
#QMAKE_CFLAGS_WARN_ON += -Wno-unused-parameter
#QMAKE_CFLAGS_WARN_ON += -Wno-unused-but-set-variable
#QMAKE_CFLAGS_WARN_ON += -Wno-unused-variable

SOURCES += \
../compound-file.c \
../compound-file-difat.c \
../compound-file-directory.c \
../compound-file-fat.c \
../compound-file-header.c \
../emb-arc.c \
../emb-circle.c \
../emb-compress.c \
../emb-color.c \
../emb-ellipse.c \
../emb-file.c \
../emb-flag.c \
../emb-format.c \
../emb-hash.c \
../emb-hoop.c \
../emb-layer.c \
../emb-line.c \
../emb-logging.c \
../emb-path.c \
../emb-pattern.c \
../emb-point.c \
../emb-polygon.c \
../emb-polyline.c \
../emb-reader-writer.c \
../emb-rect.c \
../emb-satin-line.c \
../emb-settings.c \
../emb-spline.c \
../emb-stitch.c \
../emb-thread.c \
../emb-time.c \
../emb-vector.c \
../hashtable.c \
../helpers-binary.c \
../helpers-misc.c \
../thread-color.c \
../format-10o.c \
../format-100.c \
../format-art.c \
../format-bmc.c \
../format-bro.c \
../format-cnd.c \
../format-col.c \
../format-csd.c \
../format-csv.c \
../format-dat.c \
../format-dem.c \
../format-dsb.c \
../format-dst.c \
../format-dsz.c \
../format-dxf.c \
../format-edr.c \
../format-emd.c \
../format-exp.c \
../format-exy.c \
../format-eys.c \
../format-fxy.c \
../format-gc.c  \
../format-gnc.c \
../format-gt.c  \
../format-hus.c \
../format-inb.c \
../format-inf.c \
../format-jef.c \
../format-ksm.c \
../format-max.c \
../format-mit.c \
../format-new.c \
../format-ofm.c \
../format-pcd.c \
../format-pcm.c \
../format-pcq.c \
../format-pcs.c \
../format-pec.c \
../format-pel.c \
../format-pem.c \
../format-pes.c \
../format-phb.c \
../format-phc.c \
../format-plt.c \
../format-rgb.c \
../format-sew.c \
../format-shv.c \
../format-sst.c \
../format-stx.c \
../format-svg.c \
../format-t01.c \
../format-t09.c \
../format-tap.c \
../format-thr.c \
../format-txt.c \
../format-u00.c \
../format-u01.c \
../format-vip.c \
../format-vp3.c \
../format-xxx.c \
../format-zsk.c \

HEADERS += \
../api-start.h \
../api-stop.h \
../compound-file.h \
../compound-file-common.h \
../compound-file-difat.h \
../compound-file-directory.h \
../compound-file-fat.h \
../compound-file-header.h \
../emb-arc.h \
../emb-circle.h \
../emb-compress.h \
../emb-color.h \
../emb-ellipse.h \
../emb-file.h \
../emb-flag.h \
../emb-format.h \
../emb-hash.h \
../emb-hoop.h \
../emb-layer.h \
../emb-line.h \
../emb-logging.h \
../emb-path.h \
../emb-pattern.h \
../emb-point.h \
../emb-polygon.h \
../emb-polyline.h \
../emb-reader-writer.h \
../emb-rect.h \
../emb-satin-line.h \
../emb-settings.h \
../emb-spline.h \
../emb-stitch.h \
../emb-thread.h \
../emb-time.h \
../emb-vector.h \
../hashtable.h \
../helpers-binary.h \
../helpers-misc.h \
../helpers-unused.h \
../thread-color.h \
../formats.h \
../format-10o.h \
../format-100.h \
../format-art.h \
../format-bmc.h \
../format-bro.h \
../format-cnd.h \
../format-col.h \
../format-csd.h \
../format-csv.h \
../format-dat.h \
../format-dem.h \
../format-dsb.h \
../format-dst.h \
../format-dsz.h \
../format-dxf.h \
../format-edr.h \
../format-emd.h \
../format-exp.h \
../format-exy.h \
../format-eys.h \
../format-fxy.h \
../format-gc.h  \
../format-gnc.h \
../format-gt.h  \
../format-hus.h \
../format-inb.h \
../format-inf.h \
../format-jef.h \
../format-ksm.h \
../format-max.h \
../format-mit.h \
../format-new.h \
../format-ofm.h \
../format-pcd.h \
../format-pcm.h \
../format-pcq.h \
../format-pcs.h \
../format-pec.h \
../format-pel.h \
../format-pem.h \
../format-pes.h \
../format-phb.h \
../format-phc.h \
../format-plt.h \
../format-rgb.h \
../format-sew.h \
../format-shv.h \
../format-sst.h \
../format-stx.h \
../format-svg.h \
../format-t01.h \
../format-t09.h \
../format-tap.h \
../format-thr.h \
../format-txt.h \
../format-u00.h \
../format-u01.h \
../format-vip.h \
../format-vp3.h \
../format-xxx.h \
../format-zsk.h 

