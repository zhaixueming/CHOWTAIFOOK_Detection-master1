QT += core gui sql
QT += serialport
QT += serialbus
QT += network
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += /utf-8  # coding

TARGET = CHOWTAIFOOK_Detection
CONFIG += c++17

INCLUDEPATH += $$PWD/../include \
               $$PWD/../include/opencv \
               $$PWD/../include/spdlog \
               $$PWD/../include/halcon \


CONFIG(debug,  debug|release){
    DESTDIR     =   $$OUT_PWD/debug/bin
    OBJECTS_DIR =   $$OUT_PWD/debug/obj
    MOC_DIR     =   $$OUT_PWD/debug/moc
    RCC_DIR     =   $$OUT_PWD/debug/rcc
    UI_DIR      =   $$OUT_PWD/debug/ui
} else {
    DESTDIR     =   $$OUT_PWD/release/bin
    OBJECTS_DIR =   $$OUT_PWD/release/obj
    MOC_DIR     =   $$OUT_PWD/release/moc
    RCC_DIR     =   $$OUT_PWD/release/rcc
    UI_DIR      =   $$OUT_PWD/release/ui
}

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

include($$PWD/logservice/logservice.pri)
include($$PWD/vimocommon/vimocommon.pri)
include($$PWD/cameraservice/cameraservice.pri)
include($$PWD/database/database.pri)
include($$PWD/communication/communication.pri)
include($$PWD/uiframe/uiframe.pri)
include($$PWD/flow/flow.pri)

HEADERS += \
    commondef.h \
    serializer/Config.h \
    serializer/cppserializer.hpp \
    serializer/json.hpp \
    serializer/optional_json.h \
    serializer/static_reflection.h \

SOURCES += \
    main.cpp


RESOURCES += \
    CHOWTAIFOOK_Detection.qrc

win32{
    CONFIG(debug,  debug|release){
        LIBS += -L$$PWD/../lib/opencv/debug -lopencv_world420d
    } else {
        LIBS += -L$$PWD/../lib/opencv/release -lopencv_world420
        LIBS += -L$$PWD/../lib/halcon/x64-win64 -lhalcon
        LIBS += -L$$PWD/../lib/halcon/x64-win64 -lhalconcpp
        LIBS += -L$$PWD/../lib/halcon/x64-win64 -lhalconcppxl
    }

    LIBS += -ldbghelp

    CONFIG(debug,  debug|release){
        SRC_DIR = $$PWD
        OUTPUT_DIR = $$OUT_PWD/debug/bin/
        SRC_DIR = $$replace(SRC_DIR, /, \\)
        OUTPUT_DIR = $$replace(OUTPUT_DIR, /, \\)
        QMAKE_POST_LINK += copy /Y $$SRC_DIR\install_debug.bat   $$OUTPUT_DIR  && cd $$OUTPUT_DIR  && call install_debug.bat
    } else {
        SRC_DIR = $$PWD
        OUTPUT_DIR = $$OUT_PWD/release/bin/
        SRC_DIR = $$replace(SRC_DIR, /, \\)
        OUTPUT_DIR = $$replace(OUTPUT_DIR, /, \\)
        QMAKE_POST_LINK += copy /Y $$SRC_DIR\install_release.bat   $$OUTPUT_DIR  && cd $$OUTPUT_DIR && call install_release.bat
    }
}
