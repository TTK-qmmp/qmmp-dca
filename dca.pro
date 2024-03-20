include($$PWD/common/common.pri)

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

#CONFIG += BUILD_PLUGIN_INSIDE
contains(CONFIG, BUILD_PLUGIN_INSIDE){
    include($$PWD/../../plugins.pri)
    TARGET = $$PLUGINS_PREFIX/Input/dca

    unix{
        target.path = $$PLUGIN_DIR/Input
        INSTALLS += target
    }
}else{
    CONFIG += warn_off plugin lib thread link_pkgconfig c++11
    TEMPLATE = lib

    unix{
        equals(QT_MAJOR_VERSION, 5){
            QMMP_PKG = qmmp-1
        }else:equals(QT_MAJOR_VERSION, 6){
            QMMP_PKG = qmmp
        }else{
            error("Unsupported Qt version: 5 or 6 is required")
        }
        
        PKGCONFIG += $${QMMP_PKG}

        PLUGIN_DIR = $$system(pkg-config $${QMMP_PKG} --variable=plugindir)/Input
        INCLUDEPATH += $$system(pkg-config $${QMMP_PKG} --variable=prefix)/include

        plugin.path = $${PLUGIN_DIR}
        plugin.files = lib$${TARGET}.so
        INSTALLS += plugin
    }
}
