TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    game.cpp \
    point.cpp

HEADERS += \
    game.h \
    point.h \
    definitions.h \
    coordinate_equal_pred.h

