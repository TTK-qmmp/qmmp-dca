
include($$PWD/common/common.pri)

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

CONFIG += warn_on plugin link_pkgconfig c++11

TEMPLATE = lib

QMAKE_CLEAN += lib$${TARGET}.so

unix {
  CONFIG += link_pkgconfig
  PKGCONFIG += qmmp

  QMMP_PREFIX = $$system(pkg-config qmmp --variable=prefix)
  PLUGIN_DIR = $$system(pkg-config qmmp --variable=plugindir)/Input
  LOCAL_INCLUDES = $${QMMP_PREFIX}/include
  LOCAL_INCLUDES -= $$QMAKE_DEFAULT_INCDIRS
  INCLUDEPATH += $$LOCAL_INCLUDES

  plugin.path = $${PLUGIN_DIR}
  plugin.files = lib$${TARGET}.so
  INSTALLS += plugin
}
