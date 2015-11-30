QT += core
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
    interface.cpp

HEADERS += \
    xmlfile.h \
    requestprocessor.h \
    person.h \
    interface.h
    requestprocessor.cpp

HEADERS += \
    xmlfile.h \
    requestprocessor.h

