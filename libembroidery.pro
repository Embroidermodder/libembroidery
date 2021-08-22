TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS  = \
libembroidery-shared.pro \
libembroidery-static.pro \
embroider.pro \

QMAKE_DISTCLEAN += object_script.*
