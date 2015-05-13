#-------------------------------------------------
#
# Project created by QtCreator 2015-04-16T10:15:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RoboNaviKali
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    HexamiteRS232PortClass.cpp \
    UltrasonicTagClass.cpp \
    UltrasonicThread.cpp \
    TextFileClass.cpp \
    MeasurementPointClass.cpp \
    CalibrationMeasurementClass.cpp \
    RS232Library.c \
    MsgQueueClass.cpp

HEADERS  += mainwindow.h \
    HexamiteRS232PortClass.h \
    UltrasonicTagClass.hpp \
    UltrasonicThread.hpp \
    TextFileClass.h \
    MeasurementPointClass.h \
    CalibrationMeasurementClass.h \
    RS232Library.h \
    MsgQueueClass.hpp

FORMS    += mainwindow.ui

RESOURCES += \
            picturefile.qrc

CONFIG += c++11

