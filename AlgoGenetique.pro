TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    noteur.cpp \
    population.cpp \
    individu.cpp

HEADERS += \
    population.h \
    individu.h \
    population.h \
    noteur.h \
    general.h \
    abstractnoteur.h \
    simplexeption.h
