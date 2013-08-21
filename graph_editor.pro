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
    graphitem.cpp \
    graphedge.cpp \
    graphcomment.cpp \
    graphscene.cpp \
    graphview.cpp

HEADERS  += mainwindow.h \
    graphitem.h \
    graphedge.h \
    graphcomment.h \
    graphscene.h \
    graphview.h

FORMS    += mainwindow.ui

RESOURCES += \
    icons.qrc
