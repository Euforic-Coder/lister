TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

HEADERS += \
    from.h \
    messages.h \
    uforia.h \
    has.h \
    colored.h \
    random.h

DISTFILES += \
    fruits.txt
