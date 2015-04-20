#-------------------------------------------------
#
# Project created by QtCreator 2015-04-13T20:42:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = stlseries_gui
TEMPLATE = app
unix|win32: LIBS += -lstlseries


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

target.path = /usr/local/bin
INSTALLS += target
