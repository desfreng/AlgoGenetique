TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=gnu++11

SOURCES += main.cpp \
    noteur.cpp \
    population.cpp \
    individu.cpp \
    guiclass.cpp

HEADERS += \
    population.h \
    individu.h \
    population.h \
    noteur.h \
    general.h \
    abstractnoteur.h \
    guiclass.h
