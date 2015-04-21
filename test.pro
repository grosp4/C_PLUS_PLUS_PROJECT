#-------------------------------------------------
#
# Project created by QtCreator 2015-04-16T10:15:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    testthread.cpp

HEADERS  += mainwindow.h \
    debug_configurations.hpp \
    testthread.hpp

FORMS    += mainwindow.ui

IMAGES += madeingermany.png

