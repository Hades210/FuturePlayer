TEMPLATE = lib
CONFIG += plugin link_pkgconfig

QT += widgets

DESTDIR = ../../../app/lib/qmplay2/modules

QMAKE_LIBDIR += ../../../app/lib
LIBS += -lqmplay2
PKGCONFIG += libpulse-simple

RCC_DIR = build/rcc
OBJECTS_DIR = build/obj
MOC_DIR = build/moc

RESOURCES += icon.qrc

INCLUDEPATH += . ../../qmplay2/headers
DEPENDPATH += . ../../qmplay2/headers

HEADERS += PulseAudio.hpp PulseAudioWriter.hpp Pulse.hpp
SOURCES += PulseAudio.cpp PulseAudioWriter.cpp Pulse.cpp
