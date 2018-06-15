#-------------------------------------------------
#
# Project created by QtCreator 2016-12-06T23:47:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = doorpass_application
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    webview.cpp \
    browserwidget.cpp \
    webdialog.cpp \
    webpage.cpp

HEADERS  += mainwindow.h \
    webview.h \
    browserwidget.h \
    webdialog.h \
    webpage.h

FORMS    += mainwindow.ui

QT += webenginewidgets
QT += network
