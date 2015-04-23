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
    testthread.cpp \
    HexamiteRS232PortClass.cpp \
    rs232.c \
    UltrasonicTagClass.cpp \
    UltrasonicThread.cpp

HEADERS  += mainwindow.h \
    debug_configurations.hpp \
    testthread.hpp \
    HexamiteRS232PortClass.h \
    rs232.h \
    UltrasonicTagClass.hpp \
    UltrasonicThread.hpp

FORMS    += mainwindow.ui

IMAGES += madeingermany.png

