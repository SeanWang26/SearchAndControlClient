#-------------------------------------------------
#
# Project created by QtCreator 2014-05-29T22:58:28
#
#-------------------------------------------------

QT       += core gui
QT      += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QSearch
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    configdialog.cpp \
    page.cpp

HEADERS  += mainwindow.h \
    configdialog.h \
    page.h

FORMS    += mainwindow.ui
