QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


SOURCES += \
    common.cpp \
    main.cpp \
    mainwindow.cpp \
    sensorstat.cpp

HEADERS += \
    README.h \
    TODO.h \
    common.h \
    mainwindow.h \
    sensorstat.h

FORMS += \
    mainwindow.ui \
    sensorstat.ui

DISTFILES += \
    README

