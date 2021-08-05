
HEADERS += \
    $$PWD/honeywell.h \
    $$PWD/mcplc.h \
    $$PWD/plchelper.h \
    $$PWD/readcode.h \
    $$PWD/stripprocessor.h \
    $$PWD/xmlparser.h

SOURCES += \
    $$PWD/honeywell.cpp \
    $$PWD/mcplc.cpp \
    $$PWD/plchelper.cpp \
    $$PWD/readcode.cpp \
    $$PWD/stripprocessor.cpp \
    $$PWD/xmlparser.cpp

CONFIG(debug,  debug|release){
} else {
    LIBS += -L$$PWD/../../lib/grpc -lmvi_sdk
    LIBS += -L$$PWD/../../lib/libjpeg-turbo -lturbojpeg
    LIBS += -L$$PWD/../../lib/zip -lzip
}
