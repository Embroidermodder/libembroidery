TEMPLATE = app
CONFIG -= debug_and_release qt
CONFIG += console debug
#CONFIG += console release
CONFIG -= app_bundle

TARGET = libembroidery-test

OBJECTS_DIR = .obj
MOC_DIR = .moc

INCLUDEPATH += \
../libembroidery \
../libcgeometry \
$$PWD \

SOURCES += libembroidery-test-main.c

include( ../libembroidery/libembroidery.pri )

