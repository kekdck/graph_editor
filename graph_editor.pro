#-------------------------------------------------
#
# Project created by QtCreator 2013-07-24T16:33:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = graph_editor
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    graphitem.cpp

HEADERS  += mainwindow.h \
    graphitem.h

FORMS    += mainwindow.ui
