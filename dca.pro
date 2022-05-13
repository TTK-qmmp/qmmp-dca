include($$PWD/../../plugins.pri)
include($$PWD/common/common.pri)

TARGET = $$PLUGINS_PREFIX/Input/dca

HEADERS += decoderdcafactory.h \
           decoder_dca.h \
           dcahelper.h
    
SOURCES += decoderdcafactory.cpp \
           decoder_dca.cpp \
           dcahelper.cpp \
           libdca/parse.c \
           libdca/gettimeofday.c \
           libdca/extract_dca.c \
           libdca/downmix.c \
           libdca/bitstream.c

INCLUDEPATH += $$PWD/libdca

unix {
    target.path = $$PLUGIN_DIR/Input
    INSTALLS += target
    QMAKE_CLEAN = $$PLUGINS_PREFIX/Input/libdca.so
}
