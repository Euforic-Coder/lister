TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

HEADERS += \
    uforia/uforia.h \
    uforia/random.h \
    uforia/messages.h \
    uforia/has.h \
    uforia/from.h \
    uforia/colored.h
