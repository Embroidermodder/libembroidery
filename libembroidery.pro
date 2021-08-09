TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS  = \
libembroidery-shared.pro \
libembroidery-static.pro \
libembroidery-convert.pro \

QMAKE_DISTCLEAN += object_script.*
