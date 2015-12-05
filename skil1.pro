QT += core
QT += sql
QT -= gui

TARGET = skil1
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11

TEMPLATE = app

SOURCES += main.cpp \
    xmlfile.cpp \
    requestprocessor.cpp \
    person.cpp \
    interface.cpp \
    dbmanager.cpp \
    computer.cpp \
    relation.cpp \
    computerxpersons.cpp \
    personxcomputers.cpp

HEADERS += \
    xmlfile.h \
    requestprocessor.h \
    person.h \
    interface.h \
    dbmanager.h \
    computer.h \
    relation.h \
    computerxpersons.h \
    personxcomputers.h
    requestprocessor.cpp

