QT += core
QT -= gui

TARGET = skil1
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    xmlfile.cpp \
<<<<<<< HEAD
    requestprocessor.cpp \
    person.cpp

HEADERS += \
    xmlfile.h \
    requestprocessor.h \
    person.h
=======
    requestprocessor.cpp

HEADERS += \
    xmlfile.h \
    requestprocessor.h
>>>>>>> 94e2610407634ccc10613a5da1352a5215107d58

