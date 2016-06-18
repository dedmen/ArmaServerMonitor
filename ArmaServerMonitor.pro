#-------------------------------------------------
#
# Project created by QtCreator 2016-02-06T23:58:22
#
#-------------------------------------------------

QT       += core gui network printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ArmaServerMonitor
TEMPLATE = app
QMAKE_LFLAGS += /FS
QMAKE_CXXFLAGS +=/FS

SOURCES += main.cpp\
        mainwindow.cpp \
    asmconnector.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    asmconnector.h \
    qcustomplot.h

FORMS    += mainwindow.ui
