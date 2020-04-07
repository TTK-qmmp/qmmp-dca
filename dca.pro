include(../../plugins.pri)
include($$PWD/common/common.pri)

TARGET = $$PLUGINS_PREFIX/Input/dca

HEADERS += decoderdcafactory.h \
           decoder_dca.h \
           dcahelper.h \
           tendra.h \
           tables_vq.h \
           tables_quantization.h \
           tables_huffman.h \
           tables_fir.h \
           tables_adpcm.h \
           tables.h \
           gettimeofday.h \
           dts.h \
           dca_internal.h \
           dca.h \
           bitstream.h \
           audio_out.h
    
SOURCES += decoderdcafactory.cpp \
           decoder_dca.cpp \
           dcahelper.cpp \
           parse.c \
           gettimeofday.c \
           extract_dca.c \
           downmix.c \
           bitstream.c

unix {
    target.path = $$PLUGIN_DIR/Input
    INSTALLS += target
    QMAKE_CLEAN = $$PLUGINS_PREFIX/Input/libdca.so
}
